#ifndef SERIAL_H
#define SERIAL_H

#include <QtCore/QDebug>
#include <QByteArray>
#include <QtWidgets/QComboBox>
#include <QString>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


static QSerialPort serialDevice;

//packet size
static int size = 11;
static QByteArray data;


class serial
{
public:
    static void initSerial(QString device);
    static bool set(quint8 i, quint8 d);
    static bool MotorSet(quint8 thrusters[]);
    static bool send();
    static quint8 crc8(QByteArray data);
    static void print(QByteArray data);
};

#endif // SERIAL_H
