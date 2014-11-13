#ifndef SERIAL_H
#define SERIAL_H

#include <QtCore/QDebug>
#include <QByteArray>
#include <QtWidgets/QComboBox>


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


static QSerialPort serialDevice;

class serial
{
public:
    static void initSerial(QString device);
    static bool send(char bytes[], size_t size);
};

#endif // SERIAL_H
