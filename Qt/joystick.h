#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include "SDL.h"

class Joystick : public QObject {
    Q_OBJECT

public:
    Joystick();
    ~Joystick();

private:
    SDL_Joystick* stick;

};

#endif // JOYSTICK_H
