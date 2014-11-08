#include "serial.h"


void serial::initSerial(QString device) {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.description() == device) {
            serialDevice.setPort(info);
        }
    }
}


bool serial::send(char bytes[]) {
    if (serialDevice.open(QIODevice::ReadWrite) && serialDevice.isWritable()) {
        QByteArray data = QByteArray::fromRawData(bytes, sizeof(bytes));
        serialDevice.write(data);
        return serialDevice.flush();
    }

    return false;
}



