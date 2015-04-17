#include "serial.h"

#define BAUD_RATE 19200

Serial::Serial(QObject *parent) : QObject(parent)
{
    memset(&m_control_packet, 0, sizeof(m_control_packet));
    m_control_packet.header = SERIAL_CTL_HEADER;
    m_control_packet.footer = SERIAL_CTL_FOOTER;
}

Serial::~Serial()
{
    if (m_serial_port->isOpen()) {
        m_serial_port->close();
    }
    m_tool_events.clear();
}

bool Serial::Open(QString deviceName) {
    bool found = false;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.description() == deviceName) {
            m_serial_port->setPort(info);
            m_serial_port->setBaudRate(BAUD_RATE);
            found = true;
            break;
        }
    }
    return m_serial_port->open(QIODevice::ReadWrite);
}

QSerialPort::SerialPortError Serial::GetError() {
    return m_serial_port->error();
}

void Serial::SetMotorValues(quint8 values[]) {
    QMutexLocker locker(&m_packet_mutex);  //  Mutex auto releases when funct returns
    m_control_packet.motorHTL = values[0];
    m_control_packet.motorHTR = values[1];
    m_control_packet.motorHBR = values[2];
    m_control_packet.motorHBL = values[3];
    m_control_packet.motorVTL = values[4];
    m_control_packet.motorVTR = values[5];
    m_control_packet.motorVBR = values[6];
    m_control_packet.motorVBL = values[7];
}

void Serial::SetFootTurner(quint8 value) {
    QMutexLocker locker(&m_packet_mutex);  //  Mutex auto releases when funct returns
    m_control_packet.footTurner = value;
}

void Serial::EnqueueToolEvent(quint8 value, quint8 mask) {
    QMutexLocker locker(&m_tool_mutex);   //  Mutex auto releases when funct returns
    m_tool_events.enqueue((mask << 16) | value);
}

void Serial::SetLedValues(quint8 values[], quint8 color) {
    QMutexLocker locker(&m_packet_mutex);  //  Mutex auto releases when funct returns
    m_control_packet.led1 = values[0];
    m_control_packet.led2 = values[1];
    m_control_packet.led3 = values[2];
    m_control_packet.led4 = values[3];
    m_control_packet.led5 = values[4];
    m_control_packet.ledColor = color;
}

quint8 crc8(char bytes[], int size) {
    quint8 crc = 0;
    quint8 val;
    quint8 mix;
    for (int i = 1; i < size - 2; ++i) {
        val = bytes[i];
        for (int j = 8; j; --j) {
            mix = (crc ^ val) & 0x01;
            crc >>= 1;
            if (mix) {
                crc ^= 0xD5;
            }
            val >>= 1;
        }
    }
    return crc;
}

void Serial::NetworkTick() {
    if (m_serial_port == NULL) {
        //  TODO
    } else {
        if (m_serial_port->isWritable()) {
            QMutexLocker locker(&m_packet_mutex);
            QMutexLocker tool_locker(&m_tool_mutex);
            quint16 change_mask = 0;
            quint32 item;
            quint16 mask;
            quint16 val;
            while (!m_tool_events.empty()) {
                item = m_tool_events.head();
                mask = (item >> 16) & 0xFFFF;
                val = item & 0xFFFF;
                //  If we have overlap then we're done for now
                if (change_mask & mask) {
                    break;
                }
                m_tool_events.dequeue();
                //  Mark those bits as changed
                change_mask |= mask;
                //  Apply change
                m_control_packet.toolBits |= mask & val;
            }
            tool_locker.unlock();

            const int size = 20;
            quint8 motors[8];
            motors[0] = m_control_packet.motorHTL;
            motors[1] = m_control_packet.motorHTR;
            motors[2] = m_control_packet.motorHBR;
            motors[3] = m_control_packet.motorHBL;
            motors[4] = m_control_packet.motorVTL;
            motors[5] = m_control_packet.motorVTR;
            motors[6] = m_control_packet.motorVBR;
            motors[7] = m_control_packet.motorVBL;
            //  Remapping
            //  Some compilers don't realize that size is a const and makes a fuss
            char bytes[size];
            bytes[0] = m_control_packet.header;
            for (int i = 0; i < 8; ++i) {
                int newId = m_motor_mapping[i];
                bytes[1 + newId] = motors[i];
            }
            //  TODO Protocol has changed from here on out, need to redo
            bytes[9] = m_control_packet.footTurner;
            bytes[10] = m_control_packet.toolBits;
            bytes[11] = m_control_packet.laserStepper;
            bytes[12] = m_control_packet.led1;
            bytes[13] = m_control_packet.led2;
            bytes[14] = m_control_packet.led3;
            bytes[15] = m_control_packet.led4;
            bytes[16] = m_control_packet.led5;
            bytes[17] = m_control_packet.ledColor;
            bytes[18] = crc8(bytes, size);
            bytes[19] = m_control_packet.footer;
            locker.unlock();    //  Early release so we don't hold while writing
            m_serial_port->write(bytes, size);
        }
    }
}

void Serial::SetActiveSerialDevice(QString name) {
    bool ok = Open(name);
    emit SerialDeviceChanged(ok);
}


