#include "serial.h"

#define BAUD_RATE 19200

Serial::Serial(QObject *parent) : QObject(parent)
{

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
    return QSerialPort::NoError;
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

void Serial::EnqueueToolEvent(quint16 value, quint16 mask) {
    QMutexLocker locker(&m_tool_mutex);   //  Mutex auto releases when funct returns
    m_tool_events.enqueue((mask << 16) | value);
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

            int size = m_control_packet.size;
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
            char bytes[/*control_packet_.size*/ 16];
            bytes[0] = m_control_packet.header;
            for (int i = 0; i < 8; ++i) {
                int newId = m_motor_mapping[i];
                bytes[1 + newId] = motors[i];
            }
            bytes[9] = (m_control_packet.toolBits & 0xFF00) >> 8;
            bytes[10] = m_control_packet.toolBits & 0xFF;
            bytes[11] = m_control_packet.red;
            bytes[12] = m_control_packet.green;
            bytes[13] = m_control_packet.blue;
            bytes[14] = crc8(bytes, size);
            bytes[15] = m_control_packet.footer;
            locker.unlock();    //  Early release so we don't hold while writing
            m_serial_port->write(bytes, size);
        }
    }
}


