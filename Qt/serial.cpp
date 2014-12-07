#include "serial.h"


void serial::initSerial(QString device) {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << info.description();
        if (info.description() == device) {
            serialDevice.setPort(info);
        }
    }
}


bool serial::send(quint8 bytes[], quint8 size) {

    //print(bytes, size);
    //qDebug() << "\nNew packet\n";
    //bytes[size-2] = crc8(bytes, size);
    //print(bytes, size);

    //do crc8 on checksum byte
    bytes[size-2] = crc8(bytes, size);

    if (serialDevice.open(QIODevice::ReadWrite) && serialDevice.isWritable()) {
        QByteArray data = QByteArray::fromRawData((char*) bytes, size);
        serialDevice.write(data);
        return serialDevice.flush();
    }

    return false;
}


quint8 serial::crc8(quint8 bytes[], quint8 size) {

    quint8 crc = 0;

    for (int i = 0; i < size; ++i) {

        quint8 inbyte = bytes[i];

        for (int i = 8; i; i--) {
          quint8 mix = (crc ^ inbyte) & 0x01;
          crc >>= 1;
          if (mix) crc ^= 0xD5;
          inbyte >>= 1;
        }

      }

    return crc;
}

void serial::print(quint8 bytes[], quint8 size) {

    for (int i = 0; i < size; ++i) {
        bytes[i] = bytes[i] & 0xFF;
        qDebug("[%x]: [%d]", bytes[i], bytes[i]);
    }

}
