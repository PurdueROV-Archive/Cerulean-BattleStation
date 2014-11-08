#include "interpolator.h"

Interpolator::Interpolator(Sint32 maxDelta, int millSecsPerTick) :
    msecsPerTick(millSecsPerTick) {
    this->maxDelta = maxDelta;
    current = 0;
    target = 0;
}

Sint16 Interpolator::lerp() {
    //  Short circuit (don't actually) if we're where we want to be.
    if (current == target) {
        return current;
    }
    //  If we're falling towards zero do it instantly
    if ((target > 0 && current > target) ||
            (target < 0 && current < target)) {
        current = target;
        return current;
    }
    //  Otherwise start incrementing towards the target
    //  But cap at sign(delta) * maxDelta
    Sint32 delta = target - current;
    if (abs(delta) > maxDelta) {
        delta = sign(delta) * maxDelta;
    }
    current += delta;
    return current;
}