#ifndef MAINTICKER_H
#define MAINTICKER_H

#include "tickclock.h"
#include "SDL.h"
#include "joystick.h"

class MainTicker : public TickClock {

    void doTick();
    void initJoystick();

    Joystick* joystick;
    bool firstJoyInitTry;


public:
    MainTicker(quint64 targetTicksPerSec);

    ~MainTicker();
};

#endif // MAINTICKER_H
