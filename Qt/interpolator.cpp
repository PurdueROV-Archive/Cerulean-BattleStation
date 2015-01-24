#include "interpolator.h"

//#define FALL_FAST

Interpolator::Interpolator(qint32 maxDelta, int millSecsPerTick) :
    msecsPerTick(millSecsPerTick) {
    this->maxDelta = maxDelta;
    current = 0;
    target = 0;
}

qint16 Interpolator::lerp(qint16 newTarget) {
    target = newTarget;
    //  Short circuit (don't actually) if we're where we want to be.
    if (current == target) {
        return current;
    }

    // Start incrementing towards the value we want
    // But cap at sign(delta) * maxDelta
    qint32 delta = target - current;
    if (abs(delta) > maxDelta) {
        qint32 sign = delta > 0 ? 1 : -1;
        delta = sign * maxDelta;
    }
    current += delta;
    return current;
}
