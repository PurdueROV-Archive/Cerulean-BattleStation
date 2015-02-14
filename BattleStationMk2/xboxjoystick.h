#ifndef XBOXJOYSTICK_H
#define XBOXJOYSTICK_H
#include "genericjoystick.h"
#include <QObject>

#define XBOX_BUTTON_A 10
#define XBOX_BUTTON_B 11
#define XBOX_BUTTON_X 12
#define XBOX_BUTTON_Y 13
#define XBOX_BUTTON_LB 8
#define XBOX_BUTTON_RB 9
#define XBOX_BUTTON_BACK 5
#define XBOX_BUTTON_SELECT 4
#define XBOX_BUTTON_LJ 6
#define XBOX_BUTTON_RJ 7
#define XBOX_BUTTON_LP_UP 0
#define XBOX_BUTTON_LP_DOWN 1
#define XBOX_BUTTON_LP_LEFT 2
#define XBOX_BUTTON_LP_RIGHT 3
#define XBOX_AXIS_LJ_X 0
#define XBOX_AXIS_LJ_Y 1
#define XBOX_AXIS_RJ_X 2
#define XBOX_AXIS_RJ_Y 3
#define XBOX_AXIS_LTRIGG 4
#define XBOX_AXIS_RTRIGG 5

#define NUM_BUTTONS 14
#define NUM_AXES 6

class XboxJoystick : public GenericJoystick
{
    ButtonState m_buttons[NUM_BUTTONS];
    float m_axes[NUM_AXES];

public:
    explicit XboxJoystick(int joystick_id, QObject *parent = 0);
    ~XboxJoystick();

    void InitJoystick();
    float GetAxis(Axis axis);
    ButtonState GetButtonState(Button button);
    void Tick();

};

#endif // XBOXJOYSTICK_H
