#ifndef GENERICJOYSTICK_H
#define GENERICJOYSTICK_H

#include <QObject>
#include "SDL.h"

enum Button {
    A,
    B,
    X,
    Y,
    BACK,
    SELECT,
    RIGHT_BUMPER,
    LEFT_BUMPER,
    DPAD_UP,
    DPAD_DOWN,
    DPAD_RIGHT,
    DPAD_LEFT,
    RIGHT_JOY_PRESS,
    LEFT_JOY_PRESS
};

enum Axis {
    RIGHT_JOY_X,
    RIGHT_JOY_Y,
    LEFT_JOY_X,
    LEFT_JOY_Y,
    TRIGGER_TOTAL,
    RIGHT_TRIGGER,
    LEFT_TRIGGER
};

struct ButtonState {
    bool is_down;
    bool was_down;
};

class GenericJoystick : public QObject
{
    Q_OBJECT



public:
    explicit GenericJoystick(QObject *parent = 0);
    ~GenericJoystick();

    virtual float GetAxis(Axis axis) = 0;
    virtual ButtonState GetButtonState(Button button) = 0;


signals:

public slots:
};

#endif // GENERICJOYSTICK_H
