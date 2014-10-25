#include "joystick.h"
#include <QDebug>

QString* Joystick::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        QString* error = new QString(SDL_GetError());
        qWarning() << "SDL Init Error: " << *error;
        return error;
    }
    qDebug() << "SDL initialized successfully.";
    return NULL;
}

Joystick::Joystick(int id) {
    joystickId = id;
}

QString* Joystick::init() {
    stick = SDL_JoystickOpen(joystickId);
    if(stick == NULL) {
        QString* error = new QString(SDL_GetError());
//        qWarning() << "Unable to open joystick: " << *error;
        open = false;
        return error;
    }
    open = true;
    return NULL;
}

void Joystick::update() {
    SDL_JoystickUpdate();
}

Sint16 Joystick::getAxis(int axis) {
    return SDL_JoystickGetAxis(stick, axis);
}

bool Joystick::getButton(int button) {
    return SDL_JoystickGetButton(stick, button);
}

int Joystick::getCurrentJoystickId() {
    return joystickId;
}

QString Joystick::getJoystickName() {
    return QString(SDL_JoystickName(stick));
}

int Joystick::getNumberOfAxes() {
    return SDL_JoystickNumAxes(stick);
}

int Joystick::getNumberOfButtons() {
    return SDL_JoystickNumButtons(stick);
}

SDL_Joystick* Joystick::getStick() {
    return stick;
}

Joystick::~Joystick() {
    SDL_JoystickClose(stick);
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    this->deleteLater();
}


