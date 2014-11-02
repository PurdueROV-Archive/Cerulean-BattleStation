#ifndef SERIAL_H
#define SERIAL_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class serial
{
public:
    static void initSerial();
    static bool send(QSerialPort* serial, char bytes[]);
};

#endif // SERIAL_H
