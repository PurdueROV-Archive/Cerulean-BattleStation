#include "serial.h"


void serial::initSerial(QString device) {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << info.description();
        if (info.description() == device) {
            serialDevice.setPort(info);
            serialDevice.setBaudRate(115200);
        }
    }

    serialDevice.open(QIODevice::ReadWrite);
//    serialDevice.set

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
    if ((quint8) data.at(i) == d) {
        return true;
    } else {
        qDebug() << i << "INVALID GOT " << b << "EXPECTED" << d;
        return false;
    }
}

bool serial::MotorSet(quint8 m1, quint8 m2, quint8 m3, quint8 m4, quint8 m5, quint8 m6, quint8 m7, quint8 m8) {
    return set(1, m1) && set(2, m2) && set(3, m3) && set(4, m4) && set(5, m5) && set(6, m6) && set(7, m7) && set(8, m8);
}

bool serial::send() {


    //make a copy
    QByteArray sendArray = data;

    //do crc8 on checksum byte
    sendArray[sendArray.size()-2] = crc8(sendArray);

    //print(data);
    //qDebug() << "\nNew packet\n";
    //print(sendArray);

    if (serialDevice.isWritable()) {

//        qDebug() << "Moo";
        QByteArray copy  = QByteArray(sendArray);
        serialDevice.write(copy);
        serialDevice.flush();

//        qint64 toWrite = serialDevice.bytesToWrite();
//        if (toWrite > 0) {
//            qDebug() << "out" << serialDevice.bytesToWrite();
//        }
        bool worked = serialDevice.waitForBytesWritten(50);
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
