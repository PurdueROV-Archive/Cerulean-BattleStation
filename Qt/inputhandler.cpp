#include "inputhandler.h"

#define updateJoystickActive emit joystickActiveChanged(m_joystickActive);

InputHandler::InputHandler() {
    m_joystickActive = false;
    m_joystick = NULL;
    setJoystick(0);
}

InputHandler::~InputHandler() {

}

void InputHandler::setJoystick(int index) {
    if (m_joystick != NULL) {
        delete m_joystick;
        m_joystickActive = false;
        updateJoystickActive
    }
    m_joystick = new Joystick(index);
    QString* result = m_joystick->init();
    if (result == NULL) {
        m_joystickActive = true;
        qDebug() << Joystick::getJoystickName(index) << "now the active joystick";
        updateJoystickActive
    } else {
        qWarning() << "Failed to initialize joystick! " << *result;
        m_joystickActive = false;
        updateJoystickActive
    }
}

QList<JoystickInfo> InputHandler::listJoysticks() {
    return m_joysticks;
}

void InputHandler::tick(TickClock* clock) {
    if (m_joystick != NULL) {
        m_joystick->poll();
        //  TODO Handle input


//        for (int i = 0; i < m_joystick->getNumButtons(); i++) {
//            if (m_joystick->getHasButtonJustBeenPressed(i)) {
//                qDebug() << "button" << i << "has been pressed";
//            }
//            if (m_joystick->getHasButtonJustBeenReleased(i)) {
//                    qDebug() << "button" << i << "has been released";
//            }
//        }
    }
    //  Every ten seconds update the list of joysticks
    if (clock->getTickCount() % clock->secondsToTicks(10.0) == 0) {
        m_joysticks.clear();
        int numSticks = Joystick::numberOfJoysticks();
        for (int i = 0; i < numSticks; i++) {
            JoystickInfo info;
            info.joystickId = i;
            info.name = Joystick::getJoystickName(i);
            m_joysticks.append(info);
        }
        emit joysticksChanged(m_joysticks);
    }

}
