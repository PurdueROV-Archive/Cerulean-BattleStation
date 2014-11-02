#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include "joystick.h"
#include "tickclock.h"

class InputHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<JoystickInfo> joysticks READ listJoysticks NOTIFY joysticksChanged)
    Q_PROPERTY(bool joystickActive READ joystickActive NOTIFY joystickActiveChanged)

    Joystick* m_joystick;
    bool m_joystickActive;
    QList<JoystickInfo> m_joysticks;
public:
    InputHandler();
    ~InputHandler();

    Q_INVOKABLE void setJoystick(int index);
    QList<JoystickInfo> listJoysticks();
    void tick(TickClock* clock);

    bool joystickActive() const {
        return m_joystickActive;
    }

public slots:

signals:
    void joysticksChanged(QList<JoystickInfo> list);
    void joystickActiveChanged(bool newVal);

};

#endif // INPUTHANDLER_H
