#include "mainticker.h"
#include "tickclock.h"

void MainTicker::doTick() {
    //  Retry every 20 ticks if it isn't open
    if(!joystick->isOpen() && getTickCount() % 20 == 0) {
        initJoystick();
    }
    joystick->poll();
    for (int i = 0; i < joystick->getNumButtons(); i++) {
        if (joystick->getHasButtonJustBeenPressed(i)) {
            qDebug() << "button" << i << "has been pressed";
        }
        if (joystick->getHasButtonJustBeenReleased(i)) {
                qDebug() << "button" << i << "has been released";
        }
    }

}

MainTicker::MainTicker(quint64 targetTicksPerSec) :
    TickClock(targetTicksPerSec) {
    firstJoyInitTry = false;
    initJoystick();
}

void MainTicker::initJoystick() {
    joystick = new Joystick(0);
    QString* result = joystick->init();
    if (result != NULL) {
        if (!firstJoyInitTry) {
            qWarning() << "Failed to initialize joystick! " << *result;
        }
    }
    firstJoyInitTry = true;
}

MainTicker::~MainTicker() {
    //  Nothing to destroy (yet)
}
