#ifndef GODHEADER
#define GODHEADER

#include <QObject>

struct SerialControlPacket {
    const int size = 16;
    const quint8 header = 0x12;
    quint8 motorHTL;
    quint8 motorHTR;
    quint8 motorHBR;
    quint8 motorHBL;
    quint8 motorVTL;
    quint8 motorVTR;
    quint8 motorVBR;
    quint8 motorVBL;
    quint16 toolBits;
    quint8 red;
    quint8 blue;
    quint8 green;
    quint8 crc8;
    const quint8 footer = 0x13;
};



#endif // GODHEADER

