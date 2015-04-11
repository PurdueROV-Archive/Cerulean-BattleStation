#ifndef GENERICJOYSTICK_H
#define GENERICJOYSTICK_H

#include <QObject>
#include "SDL.h"
#undef main

/**
 * An enumeration of all standard buttons. Implementations should remap raw button IDs to
 * these enumerations
 */
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
    LEFT_JOY_PRESS,
    INVALID
};

/**
 * An enumeration of all standard axes. Implementations should remap raw axis IDs to
 * these enumerations
 */
enum Axis {
    RIGHT_JOY_X,
    RIGHT_JOY_Y,
    LEFT_JOY_X,
    LEFT_JOY_Y,
    /** The composite of the two triggers. Positive is more RIGHT pull, negative LEFT */
    TRIGGER_TOTAL,
    /** Trigger values are 0.0-1.0 **/
    RIGHT_TRIGGER,
    /** Trigger values are 0.0-1.0 **/
    LEFT_TRIGGER,
    INVALID
};

/**
 * A struct to track an individual button's current and previous state
 */
struct ButtonState {
    /** The ID of the button in question */
    int button_id;
    /** Whether or not the button is currently down */
    bool is_down;
    /** Whether or not the button was down the last time it was polled */
    bool was_down;

    /**
     * Returns true if the button has just been released
     */
    bool released() {
        return !is_down && was_down;
    }

    /**
     * Returns true if the button has just been pressed down
     */
    bool pressed() {
        return !was_down && is_down;
    }
};

class GenericJoystick : public QObject
{
    Q_OBJECT

protected:
    /** The joystick's device ID */
    const int m_joystick_id;

    /** The SDL joystick object used to actually access the joystick */
    SDL_Joystick * m_sdl_joystick;

public:
    explicit GenericJoystick(int joystick_id, QObject *parent = 0);
    ~GenericJoystick();

    /**
     * Initializes the joystick after creation (opens the device, assigns values, etc).
     * Call GetSDLError() to check for failure afterwords.
     */
    virtual void InitJoystick() = 0;

    /**
     * Gets the last updated value for the given Axis
     */
    virtual float GetAxis(Axis axis) = 0;
    /**
     * Gets the last updated ButtonState for the given Button
     */
    virtual ButtonState GetButtonState(Button button) = 0;

    /**
     * Performs polling/event handling. Call from the primary ticking thread.
     */
    virtual void Tick() = 0;

    /**
     * Gets the last error SDL had.
     */
    QString GetSDLError();

signals:
    /** Signalled when a button has been pressed down */
    void ButtonPressed(Button button);

    /** Signalled when a button has been released */
    void ButtonReleased(Button button);

    /** Signalled when an axis' value has changed */
    void AxisChanged(Axis axis);

public slots:

};

#endif // GENERICJOYSTICK_H
