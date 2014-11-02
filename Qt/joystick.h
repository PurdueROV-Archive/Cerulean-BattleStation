#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QList>
#include <QDebug>
#include "SDL.h"
#undef main

struct ButtonState {
    bool lastState;
    bool currentState;
};

class Joystick : public QObject
{
    Q_OBJECT
public:
    Joystick(int joystickId);
    ~Joystick();

    QString* init();

    Sint16 getAxis(int axisId);
    bool getButtonState(int buttonId);
    bool getHasButtonJustBeenReleased(int buttonId);
    bool getHasButtonJustBeenPressed(int buttonId);
    int getNumAxes();
    int getNumButtons();
    bool isOpen();
    void poll();

    static QString* initSDL();
    static int numberOfJoysticks();
    static QString getJoystickName(int index);

private:
    QList<Sint16> m_axes;
    QList<ButtonState> m_buttons;
    QList<bool> m_rawButtons;
    const int m_joystickId;
    SDL_Joystick* m_joystick;
    bool open;

signals:

public slots:

};

#endif // JOYSTICK_H
