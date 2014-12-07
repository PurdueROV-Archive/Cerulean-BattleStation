#include "inputhandler.h"
#include "serial.h"

#define updateJoystickActive emit joystickActiveChanged(m_joystickActive);

#define SINT16_MAX 32767
#define SINT16_MIN -32768
#define UINT16_MAX 65535

#define DEADZONE 500

InputHandler::InputHandler() {
    interpolators = new Interpolator*[8];
    for (int i = 0; i < 8; i++) {
        interpolators[i] = new Interpolator(3000, 50);
    }
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
        qDebug() << Joystick::getJoystickName(index) << "now the active joystick with" <<
                    m_joystick->getNumAxes() << "axes and" << m_joystick->getNumButtons() << "buttons";
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

void applyDeadzone(qint32 &val) {
    if (abs(val) < DEADZONE) {
        val = 0;
    }
}

//convert from raw value to packet version
quint8 convert(qint32 val) {
    quint8 ret = 0;
    bool negative = (val < 0) ? true : false;
    ret = (quint8) abs(val/256);

    if (negative) ret |= 0b10000000;

    return ret;
}

void InputHandler::tick(TickClock* clock) {

    if (m_joystick != NULL) {
        /*
         * Control Scheme
         * LeftJoystick
         *  Up      Forward (-Z)
         *  Down    Reverse (+Z)
         *  Left    Yaw CCW
         *  Right   Yaw CW
         * RightJoystick
         *  Up      Pitch forward (nose down)
         *  Down    Pitch back  (nose up)
         *  Left    Roll CCW (right goes up)
         *  Right   Roll CW (left goes up)
         * RB   Strafe right (+X)
         * LB   Strafe left  (-X)
         * RT   Ascend  (+Y)
         * LT   Descend (-Y)
         */
        m_joystick->poll();        

        //strafe computation - left and right buttons (set to 80%)
        bool rb = m_joystick->getButtonState(XBOX_BUTTON_RB_ID);
        bool lb = m_joystick->getButtonState(XBOX_BUTTON_LB_ID);
        qint32 velX = 0;
        if (rb != lb) {
            velX = rb ? SINT16_MIN * 0.8 : SINT16_MAX * 0.8;
        }


        //compute Z (forward and backward) - left joystick Y axis
        qint32 velZ = m_joystick->getAxis(XBOX_AXIS_LJ_Y_ID);
        applyDeadzone(velZ);

        //ascend and descend computation - left and right triggers
        //Since the triggers return SINT16_MIN for neutral position and SINT16_MAX for max pull
        //We need to remap each to [0, SINT16_MAX], so we do some promotion magic
        qint32 partialYRight = (((qint32) m_joystick->getAxis(XBOX_AXIS_RTRIGG)) + -(SINT16_MIN)) / 2;
        qint32 partialYLeft = (((qint32) m_joystick->getAxis(XBOX_AXIS_LTRIGG)) + -(SINT16_MIN)) / 2;
        qint32 velY = partialYRight - partialYLeft;
        applyDeadzone(velY);

        //compute yaw - left joystick X axis
        qint32 yaw = m_joystick->getAxis(XBOX_AXIS_LJ_X_ID);
        applyDeadzone(yaw);

        //compute pitch - right joystick Y axis
        qint32 pitch = m_joystick->getAxis(XBOX_AXIS_RJ_Y_ID);
        applyDeadzone(pitch);

        //compute roll - right joystick X axis
        qint32 roll = m_joystick->getAxis(XBOX_AXIS_RJ_X_ID);
        //X axis on this joystick is a bit sketchy, so adjust
        roll += 1300;
        applyDeadzone(roll);

        //qDebug() << velX << velY << velZ << pitch << roll << yaw;

        qint32 thrusters [8] = {0, 0, 0, 0, 0, 0, 0, 0};
        //Lateral Thrusters going left to right, then down, from top left
        //Vertical Thrusters going left to right, then down, from top left
        //Useful subarray views
        qint32* lateralThrusters = thrusters;
        qint32* verticalThrusters = thrusters + 4;


        lateralThrusters[0] += velX;
        lateralThrusters[1] -= velX;
        lateralThrusters[2] += velX;
        lateralThrusters[3] -= velX;

        verticalThrusters[0] += velY;
        verticalThrusters[1] += velY;
        verticalThrusters[2] += velY;
        verticalThrusters[3] += velY;

        lateralThrusters[0] += velZ;
        lateralThrusters[1] += velZ;
        lateralThrusters[2] -= velZ;
        lateralThrusters[3] -= velZ;

        verticalThrusters[0] += pitch;
        verticalThrusters[1] += pitch;
        verticalThrusters[2] -= pitch;
        verticalThrusters[3] -= pitch;

        lateralThrusters[0] -= yaw;
        lateralThrusters[1] += yaw;
        lateralThrusters[2] += yaw;
        lateralThrusters[3] -= yaw;

        verticalThrusters[0] += roll;
        verticalThrusters[1] -= roll;
        verticalThrusters[2] += roll;
        verticalThrusters[3] -= roll;

        //scale down values to SINT16_MAX if greater than SINT16_MAX (somehow magically happened)
        qint32 maxAbsVal = 0;

        for (int i = 0; i < 8; i++) {
            if (abs(thrusters[i]) > maxAbsVal) {
                maxAbsVal = abs(thrusters[i]);
            }
        }

        if (maxAbsVal > SINT16_MAX) {
            //Normalize the values
            float n = (float)SINT16_MAX / (float)maxAbsVal;
            for (int i = 0; i < 8; i++) {
                thrusters[i] = (qint32) (n * thrusters[i]);
            }
        }


        //do linear interpolation (so we don't ramp up/down too fast)
        for (int i = 0; i < 8; i++) {
            thrusters[i] = interpolators[i]->lerp(thrusters[i]);
        }


        //do conversion to packet values
        //This is thrusters with a capital T (naming conventions yeah...)
        quint8 Thrusters[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 8; ++i) {
            Thrusters[i] = convert(thrusters[i]);
        }

        qDebug("0x01: %+04d  0x02: %+04d  0x03: %+04d  0x04: %+04d  0x05: %+04d  0x06: %+04d  0x07: %+04d  0x08: %+04d",
               (qint8) Thrusters[0], (qint8) Thrusters[1], (qint8) Thrusters[2], (qint8) Thrusters[3],
               (qint8) Thrusters[4], (qint8) Thrusters[5], (qint8) Thrusters[6], (qint8) Thrusters[7]);

        //set values in serial buffer
        serial::MotorSet((quint8*) thrusters);

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
