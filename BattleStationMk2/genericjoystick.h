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
    int button_id;
    bool is_down;
    bool was_down;
};

class GenericJoystick : public QObject
{
    Q_OBJECT

protected:
    const int m_joystick_id;\
    SDL_Joystick * m_sdl_joystick;

public:
    explicit GenericJoystick(int joystick_id, QObject *parent = 0);
    ~GenericJoystick();

    virtual float GetAxis(Axis axis) = 0;
    virtual ButtonState GetButtonState(Button button) = 0;

    virtual void Tick() = 0;

signals:
    void ButtonPressed(Button button);
    void ButtonReleased(Button button);
    void AxisChanged(Axis axis, float new_val, float delta);
public slots:

};

#endif // GENERICJOYSTICK_H
