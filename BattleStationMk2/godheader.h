#ifndef GODHEADER
#define GODHEADER

#include <QObject>

struct SerialControlPacket {
    quint8 header;
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
    quint8 footer;
};



#endif // GODHEADER

