#include "joystick.h"
#include <QDebug>

Joystick::Joystick() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

    stick = SDL_JoystickOpen(0);
    qDebug() << SDL_JoystickNumAxes(stick);
}

Joystick::~Joystick() {

}


