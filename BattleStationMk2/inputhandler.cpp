#include "inputhandler.h"
#include "xboxjoystick.h"

InputHandler::InputHandler(QObject *parent) : QObject(parent)
{
    m_main_joystick = NULL;
}

InputHandler::~InputHandler()
{
    if (m_main_joystick != NULL) {
        m_main_joystick->deleteLater();
    }
}

void InputHandler::Tick() {


}

void InputHandler::SetMainJoystick(QString* name) {
    if (m_main_joystick != NULL) {
        m_main_joystick->deleteLater();
    }
    //  TODO Determine joystick based on name
    int joystickId = 0;

    m_main_joystick = new XboxJoystick(joystickId);
    m_main_joystick->InitJoystick();
}

