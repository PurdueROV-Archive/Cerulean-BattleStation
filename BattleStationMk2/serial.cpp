#include "serial.h"

Serial::Serial(QObject *parent) : QObject(parent)
{

}

Serial::~Serial()
{

}

void Serial::Init() {

}

void Serial::SetMotorValues(quint8 values[]) {
    QMutexLocker locker(&packet_mutex_);  //  Mutex auto releases when funct returns
    control_packet_.motorHTL = values[0];
    control_packet_.motorHTR = values[1];
    control_packet_.motorHBR = values[2];
    control_packet_.motorHBL = values[3];
    control_packet_.motorVTL = values[4];
    control_packet_.motorVTR = values[5];
    control_packet_.motorVBR = values[6];
    control_packet_.motorVBL = values[7];
}

void Serial::EnqueueToolEvent(quint16 value, quint16 mask) {
    QMutexLocker locker(&tool_mutex_);   //  Mutex auto releases when funct returns
    tool_events_.enqueue((mask << 16) | value);
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
    if (serial_port_ == NULL) {


    } else {
        if (serial_port_->isWritable()) {
            QMutexLocker locker(&packet_mutex_);
            QMutexLocker tool_locker(&tool_mutex_);
            quint16 change_mask = 0;
            quint32 item;
            quint16 mask;
            quint16 val;
            while (!tool_events_.empty()) {
                item = tool_events_.head();
                mask = (item >> 16) & 0xFFFF;
                val = item & 0xFFFF;
                //  If we have overlap then we're done for now
                if (change_mask & mask) {
                    break;
                }
                tool_events_.dequeue();
                //  Mark those bits as changed
                change_mask |= mask;
                //  Apply change
                control_packet_.toolBits |= mask & val;
            }
            tool_locker.unlock();

            int size = control_packet_.size;
            quint8 motors[8];
            motors[0] = control_packet_.motorHTL;
            motors[1] = control_packet_.motorHTR;
            motors[2] = control_packet_.motorHBR;
            motors[3] = control_packet_.motorHBL;
            motors[4] = control_packet_.motorVTL;
            motors[5] = control_packet_.motorVTR;
            motors[6] = control_packet_.motorVBR;
            motors[7] = control_packet_.motorVBL;
            //  Remapping
            //  Some compilers don't realize that size is a const and makes a fuss
            char bytes[/*control_packet_.size*/ 16];
            bytes[0] = control_packet_.header;
            for (int i = 0; i < 8; ++i) {
                int newId = motor_mapping_[i];
                bytes[1 + newId] = motors[i];
            }
            bytes[9] = (control_packet_.toolBits & 0xFF00) >> 8;
            bytes[10] = control_packet_.toolBits & 0xFF;
            bytes[11] = control_packet_.red;
            bytes[12] = control_packet_.green;
            bytes[13] = control_packet_.blue;
            bytes[14] = crc8(bytes, size);
            bytes[15] = control_packet_.footer;
            locker.unlock();    //  Early release so we don't hold while writing
            serial_port_->write(bytes, size);
        }
    }
}


