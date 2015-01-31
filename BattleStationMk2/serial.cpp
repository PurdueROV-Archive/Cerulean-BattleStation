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

}

void Serial::EnqueueToolEvent(quint16 value, quint16 mask) {

}

quint8 crc8(quint8 bytes[], int size) {
    quint8 crc = 0;
    quint8 val;
    quint8 mix;
    for (int i = 1; i < size - 2; ++i) {
        val = packet[i];
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
            quint8 bytes[control_packet_.size];
            bytes[0] = control_packet_.header;
            bytes[1] = control_packet_.motorHTL;
            bytes[2] = control_packet_.motorHTR;
            bytes[3] = control_packet_.motorHBR;
            bytes[4] = control_packet_.motorHBL;
            bytes[5] = control_packet_.motorVTL;
            bytes[6] = control_packet_.motorVTR;
            bytes[7] = control_packet_.motorVBR;
            bytes[8] = control_packet_.motorVBL;
            bytes[9] = (control_packet_.toolBits & 0xFF00) >> 8;
            bytes[10] = control_packet_.toolBits & 0xFF;
            bytes[11] = control_packet_.red;
            bytes[12] = control_packet_.green;
            bytes[13] = control_packet_.blue;
            bytes[14] = crc8(bytes, control_packet_.size);
            bytes[15] = control_packet_.footer;
            serial_port_->write(bytes, control_packet_.size);
        }
    }
}


