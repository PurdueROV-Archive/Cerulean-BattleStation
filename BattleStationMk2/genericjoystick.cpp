
#include "genericjoystick.h"

GenericJoystick::GenericJoystick(int joystick_id, QObject *parent) :
    QObject(parent), m_joystick_id(joystick_id) {

}

GenericJoystick::~GenericJoystick() {

}

QString GenericJoystick::GetSDLError() {
    return QString(SDL_GetError());
}
