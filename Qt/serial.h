#ifndef SERIAL_H
#define SERIAL_H

#include <QtCore/QDebug>
#include <QByteArray>
#include <QtWidgets/QComboBox>
#include <QString>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "battlestation.h"


static QSerialPort serialDevice;
static QObject* thrusterVals[8];

//packet size
static int size = 16;
static QByteArray data;


class serial
{
public:
    static void initSerial(QObject* root, QString device);
    static bool set(quint8 i, quint8 d);
    static bool MotorSet(quint8 thrusters[]);
    static bool send();
    static quint8 crc8(QByteArray data);
    static void print(QByteArray data);
};

#endif // SERIAL_H
