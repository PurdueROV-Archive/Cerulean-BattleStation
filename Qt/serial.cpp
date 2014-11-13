#include "serial.h"


void serial::initSerial(QString device) {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << info.description();
        if (info.description() == device) {
            serialDevice.setPort(info);
        }
    }
}


bool serial::send(char bytes[], size_t size) {

    if (serialDevice.open(QIODevice::ReadWrite) && serialDevice.isWritable()) {
        QByteArray data = QByteArray::fromRawData(bytes, size);
        serialDevice.write(data);
        return serialDevice.flush();
    }

    return false;
}



