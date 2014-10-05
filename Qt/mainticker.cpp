#include "mainticker.h"
#include "tickclock.h"


void MainTicker::doTick() {
    //  TODO Impl

}

MainTicker::MainTicker(quint64 targetTicksPerSec) :
    TickClock(targetTicksPerSec) {
    //  Do nothing (yet)
}

MainTicker::~MainTicker() {
    //  Nothing to destroy (yet)
}
