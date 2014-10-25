#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include "SDL.h"

class Joystick : public QObject {
    Q_OBJECT

public:
    Joystick(int id);
    ~Joystick();

    QString* init();
    int getCurrentJoystickId();
    QString getJoystickName();
    int getNumberOfAxes();
    int getNumberOfButtons();
    SDL_Joystick* getStick();

    bool isOpen() {
        return open;
    }

    Sint16 getAxis(int axis);
    bool getButton(int button);

    void update();


    static QString* initSDL();
private:
    int joystickId;
    SDL_Joystick* stick;
    bool open;

};

#endif // JOYSTICK_H
