#include <QtCore/QDebug>
#include <QByteArray>
#include <QtWidgets/QComboBox>


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "serial.h"


void serial::initSerial() {

        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            qDebug() << "Name        : " << info.portName();
            qDebug() << "Description : " << info.description();

            // Example use QSerialPort
            QSerialPort serial;
            serial.setPort(info);
            serial.setBaudRate(QSerialPort::Baud9600);
            if (serial.open(QIODevice::ReadWrite) && serial.isWritable()) {
                char bytes[4] = {0x12, 150, 50, 0x13 };
                send(&serial, bytes);
                qDebug() << "data has been sent";
                serial.close();
            }
        }
}


bool serial::send(QSerialPort* serial, char bytes[])  {
    QByteArray data = QByteArray::fromRawData(bytes, sizeof(bytes));
    serial->write(data);
    return serial->flush();
}



