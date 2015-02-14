#ifndef GODHEADER
#define GODHEADER

#include "serial.h"
#include "genericjoystick.h"
#include "qmlbattlestationcontext.h"

#include <QObject>

struct Interpolator {
    float current;
    float target;
    float max_delta_per_tick;

    float lerp(float new_target) {
        target = new_target;
        if (current == target) {
            return current;
        }
        float delta = target - current;
        if (abs(delta) > maxDelta) {
            delta = (delta < 0 ? -1.0 : 1.0) * max_delta_per_tick;
        }
        current += delta;
        return current;
    }

    float lerp() {
        return lerp(target);
    }
};



#endif // GODHEADER

