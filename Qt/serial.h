#ifndef SERIAL_H
#define SERIAL_H

#include <QtCore/QDebug>
#include <QByteArray>
#include <QtWidgets/QComboBox>
#include <QString>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


static QSerialPort serialDevice;

class serial
{
public:
    static void initSerial(QString device);
    static bool send(quint8 bytes[], quint8 size);
    static quint8 crc8(quint8 bytes[], quint8 size);
    static void print(quint8 bytes[], quint8 size);
};

#endif // SERIAL_H
