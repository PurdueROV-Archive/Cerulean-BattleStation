#ifndef MAINTICKER_H
#define MAINTICKER_H

#include "tickclock.h"

class MainTicker : public TickClock {

    void doTick();

public:
    MainTicker(quint64 targetTicksPerSec);

    ~MainTicker();
};

#endif // MAINTICKER_H
