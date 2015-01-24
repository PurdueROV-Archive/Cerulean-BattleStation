#include "serial.h"
#include <QDateTime>
#include <QQuickView>
#include <QQuickItem>


quint64 lastTime = 0;

/*
 * Initialize serial
 * root: root qml object for setting thruster values in GUI
 * device: string that matches device name given by QSerialPortInfo
 */
void serial::initSerial(QObject* root, QString device) {

    //Find t1 through t8 in QML, and add to thrusterVals(array where we can update the GUI values)
    for (int i = 1; i <= 8; i++) {
        QString t = QString("t");
        thrusterVals[i-1] = root->findChild<QObject*>(t.append(t.number(i)));
    }

    //Match the serial device with teh device string and set approriate info
    //TODO: Redo this so it can be seleceted somehow in the GUI and have more configuration
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << info.description();
        if (info.description() == device) {
            serialDevice.setPort(info);
            serialDevice.setBaudRate(19200);
        }
    }

    serialDevice.open(QIODevice::ReadWrite);

    //Byte array that is changed each time
    data = QByteArray(size, 0x00);
    data[0] = 0x12; data[data.size()-2] = 0xC5; data[data.size()-1] = 0x13;

}


//Setter for setting a byte at a position
//Should only be used internally
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

//Public function to set motor values based an an array of values
bool serial::MotorSet(quint8 thrusters[]) {

    bool worked = true;
    QString text = QString();

    for (int i = 0; i < 8; ++i) {
        set(i, thrusters[i]) && worked;
        if (worked) {
            qint8 num = (thrusters[i] & 0x80) ? (-100*(0x7F & thrusters[i]))/128 : (100*(0x7F & thrusters[i]))/128;
            text = text.number(num);
            thrusterVals[i]->setProperty("value", text);
        }
    }



    return worked;
}

bool serial::send() {


    //make a copy
    //TODO: Decide on if we should make a copy or not each time
    QByteArray sendArray = QByteArray(data);

    //Set the checksum byte to a crc8 of the array
    //this includes C5 is the checksum byte going in and why we make a copy
    sendArray[sendArray.size()-2] = crc8(sendArray);


    if (serialDevice.isWritable()) {

        //Check if time is weirdly off, mostly for debugging
        quint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        if (currentTime-lastTime > 20) {
            qDebug("Time off by: %d", currentTime-lastTime-20);
        }

        lastTime = currentTime;


        serialDevice.write(sendArray);
        bool worked = serialDevice.flush();
        return worked;

        //seems to cause issues if we wait, so seems to be best if
        //we don't use this
        //bool worked = serialDevice.waitForBytesWritten(50);
    }

    return false;
}


//Does crc8 on an QByteArray
quint8 serial::crc8(QByteArray data) {

    quint8 crc = 0;
    int size = data.size();

    for (int i = 1; i < size-2; ++i) {

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

//Prints the values in the array for debug
void serial::print(QByteArray data) {

    int size = data.size();
    qDebug("Size: %d", size);
    for (int i = 0; i < size; ++i) {
        qDebug("[%02x]: [%d]", (quint8) data.at(i), (quint8) data.at(i));
    }


}
