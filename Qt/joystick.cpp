#include "joystick.h"

#define qint16_MAX 32767
#define qint16_MIN -32768
#define qint16_MIN_ABS 32768
#define UINT16_MAX_F 65535.0

float axisRawToFloat(qint16 val) {
    val += qint16_MIN_ABS;
    return ((float (val)) / UINT16_MAX_F) - 1.0;
}

Joystick::Joystick(int joystickId) :
    m_joystickId(joystickId) {

}

Joystick::~Joystick() {
    SDL_JoystickClose(m_joystick);
    deleteLater();
}

QString* Joystick::init() {
    m_joystick = SDL_JoystickOpen(m_joystickId);
    if (m_joystick == NULL) {
        open = false;
        QString* error = new QString(SDL_GetError());
        return error;
    }
    int numAxes = getNumAxes();
    int numButtons = getNumButtons();
    for (int i = 0; i < numAxes; i++) {
        m_axes.append(0);
    }
    for (int i = 0; i < numButtons; i++) {
        ButtonState state;
        state.lastState = false;
        state.currentState = false;
        m_buttons.append(state);
        m_rawButtons.append(false);
    }
    open = true;
    return NULL;
}

qint16 Joystick::getAxis(int axisId) {
    if (axisId < m_axes.length() && axisId > 0) {
        return m_axes.at(axisId);
    }
    return 0;
}

float Joystick::getAxisF(int axisId) {
    return axisRawToFloat(getAxis(axisId));
}

bool Joystick::getButtonState(int buttonId) {
    if (buttonId < m_buttons.length() && buttonId > 0) {
        return m_buttons.at(buttonId).currentState;
    }
    return false;
}

bool Joystick::getHasButtonJustBeenReleased(int buttonId) {
    if (buttonId < m_buttons.length() && buttonId >= 0) {
        ButtonState state = m_buttons.at(buttonId);
        return !state.currentState && state.lastState;
    }
    return false;
}

bool Joystick::getHasButtonJustBeenPressed(int buttonId) {
    if (buttonId < m_buttons.length() && buttonId >= 0) {
        ButtonState state = m_buttons.at(buttonId);
        return state.currentState && !state.lastState;
    }
    return false;
}

int Joystick::getNumAxes() {
    return SDL_JoystickNumAxes(m_joystick);
}

int Joystick::getNumButtons() {
    return SDL_JoystickNumButtons(m_joystick);
}

void Joystick::poll() {
    SDL_JoystickUpdate();
    int numAxes = getNumAxes();
    int numButtons = getNumButtons();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_JOYBUTTONDOWN:
            m_rawButtons[event.jbutton.button] = true;
            break;
        case SDL_JOYBUTTONUP:
            m_rawButtons[event.jbutton.button] = false;
            break;
        }
    }
    for (int i = 0; i < numAxes; i++) {
        qint16 oldVal = m_axes[i];
        qint16 newVal = SDL_JoystickGetAxis(m_joystick, i);
        m_axes[i] = newVal;
        if (oldVal != newVal) {
            emit axisChanged(i, newVal, newVal - oldVal);
            emit axisChanged(i, axisRawToFloat(newVal), axisRawToFloat(newVal - oldVal));
        }
    }
    for (int i = 0; i < numButtons; i++) {
        ButtonState state;
        state.lastState = m_buttons.at(i).currentState;
        state.currentState = m_rawButtons.at(i);
        m_buttons[i] = state;
        //  Pressed
        if (state.currentState && !state.lastState) {
            emit buttonPressed(i);
        }
        //  Released
        if(!state.currentState && state.lastState) {
            emit buttonReleased(i);
        }
    }
}

bool Joystick::isOpen() {
    return open;
}

QString* Joystick::initSDL() {
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        QString* error = new QString(SDL_GetError());
        return error;
    }
    return NULL;
}

int Joystick::numberOfJoysticks() {
    return SDL_NumJoysticks();
}

QString Joystick::getJoystickName(int index) {
    if (index < 0 || index >= numberOfJoysticks()) {
        return QString("INVALID");
    }
    return QString(SDL_JoystickNameForIndex(index));
}

