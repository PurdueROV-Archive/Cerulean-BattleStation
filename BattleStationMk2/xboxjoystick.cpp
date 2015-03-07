#include "xboxjoystick.h"

XboxJoystick::XboxJoystick(int joystick_id, QObject *parent) :
    GenericJoystick(joystick_id, parent) {

}

XboxJoystick::~XboxJoystick() {

}

void XboxJoystick::InitJoystick() {
    m_sdl_joystick = SDL_JoystickOpen(m_joystick_id);
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        ButtonState state;
        state.button_id = i;
        state.is_down = false;
        state.was_down = false;
        m_buttons[i] = state;
    }

    for (int i = 0; i < NUM_AXES; ++i) {
        m_axes[i] = 0.0;
    }
}

float XboxJoystick::GetAxis(Axis axis) {
    switch (axis) {
    case LEFT_JOY_X:
        return m_axes[XBOX_AXIS_LJ_X];
    case LEFT_JOY_Y:
        return m_axes[XBOX_AXIS_LJ_Y];
    case RIGHT_JOY_X:
        return m_axes[XBOX_AXIS_RJ_X];
    case RIGHT_JOY_Y:
        return m_axes[XBOX_AXIS_RJ_Y];
    case LEFT_TRIGGER:
        return m_axes[XBOX_AXIS_LTRIGG];
    case RIGHT_TRIGGER:
        return m_axes[XBOX_AXIS_RTRIGG];
    case TRIGGER_TOTAL:
        return GetAxis(RIGHT_TRIGGER) -
                GetAxis(LEFT_TRIGGER);
    default:
        return 0.0;
    }
}

ButtonState XboxJoystick::GetButtonState(Button button) {
    switch (button) {
    case A:
        return m_buttons[XBOX_BUTTON_A];
    case B:
        return m_buttons[XBOX_BUTTON_B];
    case X:
        return m_buttons[XBOX_BUTTON_X];
    case Y:
        return m_buttons[XBOX_BUTTON_Y];
    case BACK:
        return m_buttons[XBOX_BUTTON_BACK];
    case SELECT:
        return m_buttons[XBOX_BUTTON_SELECT];
    case RIGHT_BUMPER:
        return m_buttons[XBOX_BUTTON_RB];
    case LEFT_BUMPER:
        return m_buttons[XBOX_BUTTON_LB];
    case DPAD_UP:
        return m_buttons[XBOX_BUTTON_LP_UP];
    case DPAD_DOWN:
        return m_buttons[XBOX_BUTTON_LP_DOWN];
    case DPAD_LEFT:
        return m_buttons[XBOX_BUTTON_LP_LEFT];
    case DPAD_RIGHT:
        return m_buttons[XBOX_BUTTON_LP_RIGHT];
    case RIGHT_JOY_PRESS:
        return m_buttons[XBOX_BUTTON_LJ];
    case LEFT_JOY_PRESS:
        return m_buttons[XBOX_BUTTON_RJ];
    default:
        return ButtonState();
    }
}

void XboxJoystick::Tick() {
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        ButtonState state = m_buttons[i];
        state.was_down = state.is_down;
        state.is_down = SDL_JoystickGetButton(m_sdl_joystick, i) != 0;
        if (state.pressed()) {
            //  TODO: Emit button pressed signal
            //  I really don't want to switch over IDs
            //  So we may end up having a more sane way to
            //  do this. Until we figure out what that way is,
            //  we just won't emit a signal
        }
        if (state.released()) {
            //  TODO: Emit button released signal, see previous
        }
    }
    for (int i = 0; i < NUM_AXES; ++i) {
        float old = m_axes[i];
        qint16 raw = SDL_JoystickGetAxis(m_sdl_joystick, i);
        float f = 0.0;
        if (raw < 0) {
            f = (float) raw / 32768.0;  //  -SINT16_MIN
        } else {
            f = (float) raw / 32767.0;  //  SINT16_MAX
        }
        m_axes[i] = f;
        if (abs(old - m_axes[i]) > 0.001) {
            //  TODO: Emit axis changed signal, see previous
        }
    }
}
