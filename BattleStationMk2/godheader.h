#ifndef GODHEADER
#define GODHEADER

#include "serial.h"
#include "genericjoystick.h"
#include "qmlbattlestationcontext.h"
#include "inputhandler.h"

#include <QObject>

//  LOGGING CONSTS
#define LOG_OK "[OK  ]"
#define LOG_WARN "[WARN]"
#define LOG_ERROR "[ERR ]"

#define MAX_DELTA 25


struct Interpolator {
    float current;
    float target;

    float lerp(float new_target) {
        target = new_target;
        if (current == target) {
            return current;
        }
        float delta = target - current;
        if (abs(delta) > MAX_DELTA) {
            delta = (delta < 0 ? -1.0 : 1.0) * MAX_DELTA;
        }
        current += delta;
        return current;
    }

    float lerp() {
        return lerp(target);
    }
};



#endif // GODHEADER

