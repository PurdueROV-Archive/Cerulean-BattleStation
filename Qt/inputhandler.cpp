#include "inputhandler.h"
#include "serial.h"

#define updateJoystickActive emit joystickActiveChanged(m_joystickActive);

#define SINT16_MAX 32767
#define SINT16_MIN -32768
#define UINT16_MAX 65535

#define DEADZONE 500
#define MAX_CHANGE 50

#define XBOX
//#define LOGITECH

InputHandler::InputHandler() {
    interpolators = new Interpolator*[8];
    quint32 delta = (quint32) UINT16_MAX / (100 / MAX_CHANGE);
    qDebug("%d", delta);
    for (int i = 0; i < 8; i++) {
        interpolators[i] = new Interpolator(delta, 100);
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

void InputHandler::setSliders(QObject *root) {
    horizontalSlider = root->findChild<QObject*>("horizontalSlider");
    verticalSlider = root->findChild<QObject*>("verticalSlider");
    pitchRollSlider = root->findChild<QObject*>("pitchRollSlider");
    strafeSlider = root->findChild<QObject*>("strafeSlider");
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

    if (negative){
        ret |= 0x80; // 0b10000000
    }
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

        qint32 horizontalLimit = (qint32) horizontalSlider->property("value").toInt();
        qint32 verticalLimit = (qint32) verticalSlider->property("value").toInt();
        qint32 strafeLimit = (qint32) strafeSlider->property("value").toInt();
        qint32 pitchRollLimit = (qint32) pitchRollSlider->property("value").toInt();

        //strafe computation - left and right buttons (set to 80%)
        int rbButton = CONT_BUTTON_RB_ID;
        int lbButton = CONT_BUTTON_LB_ID;

        bool rb = m_joystick->getButtonState(rbButton);
        bool lb = m_joystick->getButtonState(lbButton);
        qint32 velX = 0;
        if (rb != lb) {
            velX = rb ? SINT16_MIN : SINT16_MAX;
        }

        //Scale to strafe limit
        velX = (qint32) velX * (strafeLimit/100.0);

        //ascend and descend computation - left and right triggers
        //Since the triggers return SINT16_MIN for neutral position and SINT16_MAX for max pull
        //We need to remap each to [0, SINT16_MAX], so we do some promotion magic
#ifdef XBOX
        qint32 partialYRight = (((qint32) m_joystick->getAxis(CONT_AXIS_RTRIGG)) + -(SINT16_MIN)) / 2;
        qint32 partialYLeft = (((qint32) m_joystick->getAxis(CONT_AXIS_LTRIGG)) + -(SINT16_MIN)) / 2;
        qint32 velY = partialYRight - partialYLeft;
#endif
#ifdef LOGITECH
        //  TODO Logitech controller unifies the two triggers to one axis

#endif
        //scale to vertical limit
        velY = (qint32) velY * (verticalLimit/100.0);
        applyDeadzone(velY);


        //compute Z (forward and backward) - left joystick Y axis
        qint32 velZ = m_joystick->getAxis(CONT_AXIS_LJ_Y_ID);
        velZ = (qint32) velZ * (horizontalLimit/100.0);
        applyDeadzone(velZ);

        //compute yaw - left joystick X axis
        qint32 yaw = m_joystick->getAxis(CONT_AXIS_LJ_X_ID);
        yaw = (qint32) yaw * (horizontalLimit/100.0);
        applyDeadzone(yaw);

        //compute pitch - right joystick Y axis
        qint32 pitch = m_joystick->getAxis(CONT_AXIS_RJ_Y_ID);
        pitch = (qint32) pitch * (pitchRollLimit/100.0);
        applyDeadzone(pitch);

        //compute roll - right joystick X axis
        qint32 roll = m_joystick->getAxis(CONT_AXIS_RJ_X_ID);
        //X axis on this joystick is a bit sketchy, so adjust
        roll += 1300;

        roll = (qint32) roll * (pitchRollLimit/100.0);
        applyDeadzone(roll);


        qint32 thrusters [8] = {0, 0, 0, 0, 0, 0, 0, 0};
        //Lateral Thrusters go clockwise from top left
        //Vertical Thrusters go clockwise from top left
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
            float n = ((float) SINT16_MAX) / ((float) maxAbsVal);
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


        //set values in serial buffer
        bool success = serial::MotorSet((quint8*) Thrusters);

        if (!success) {
            //serial::open;
            qDebug("disconnect");
        }


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
