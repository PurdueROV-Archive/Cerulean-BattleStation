#include "serial.h"
#include <QDateTime>


quint64 lastTime = 0;


void serial::initSerial(QString device) {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << info.description();
        if (info.description() == device) {
            serialDevice.setPort(info);
            serialDevice.setBaudRate(115200);
        }
    }

    serialDevice.open(QIODevice::ReadWrite);

    //set up official data array
    data = QByteArray(size, 0x00);
    data[0] = 0x12; data[data.size()-2] = 0xC5; data[data.size()-1] = 0x13;
}

bool serial::set(quint8 i, quint8 d) {

    //don't let us change header
    if (i <= 0) return false;
    //don't let us change checksum or tail
    if (i >= size-2) return false;

    data[i] = d;
    quint8 b = data.at(i);
    if (b == d) {
        return true;
    } else {
        qDebug("Invalid set at %d: %d  Expected: %d", i, b, d);
        return false;
    }
}

bool serial::MotorSet(quint8 thrusters[]) {
    bool worked = true;
    for (int i = 0; i < 8; ++i) {
        set(i, thrusters[i]) && worked;
    }
    return worked;
}

bool serial::send() {


    //make a copy
    QByteArray sendArray = QByteArray(data);

    //do crc8 on checksum byte
    sendArray[sendArray.size()-2] = crc8(sendArray);


    if (serialDevice.isWritable()) {

        quint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        if (currentTime-lastTime > 15) {
            qDebug("Time off by: %d", currentTime-lastTime-10);
        }

        lastTime = currentTime;

        serialDevice.write(sendArray);
        bool worked = serialDevice.flush();
        //bool worked = serialDevice.waitForBytesWritten(50);
        return worked;
    }

    return false;
}


quint8 serial::crc8(QByteArray data) {

    quint8 crc = 0;
    int size = data.size();

    for (int i = 0; i < size; ++i) {

        quint8 inbyte = data.at(i);

        for (int i = 8; i; i--) {
          quint8 mix = (crc ^ inbyte) & 0x01;
          crc >>= 1;
          if (mix) crc ^= 0xD5;
          inbyte >>= 1;
        }

      }

    return crc;
}

void serial::print(QByteArray data) {

    int size = data.size();
    qDebug("Size: %d", size);
    for (int i = 0; i < size; ++i) {
        qDebug("[%02x]: [%d]", (quint8) data.at(i), (quint8) data.at(i));
    }


}
