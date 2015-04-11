#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include "genericjoystick.h"

class InputHandler : public QObject
{
    Q_OBJECT

    /** The main joystick */
    GenericJoystick* m_main_joystick;


public:
    explicit InputHandler(QObject *parent = 0);
    ~InputHandler();

    /** Performs on-tick operations, namely handling input for controlling the ROV. */
    void Tick();

signals:
    /** Signalled when motor values change (at the end of Tick()). */
    void MotorValuesChanged(quint8 values[]);

    /** Signalled when a tool update is posted */
    void PostToolUpdate(quint16 value, quint16 mask);

public slots:
    /**
     * Sets the given joystick name as the active main joystick. If no such joystick exists then this
     * does nothing.
     */
    void SetMainJoystick(QString* name);


};

#endif // INPUTHANDLER_H
