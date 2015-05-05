#include "inputhandler.h"
#include "serial.h"

#define updateJoystickActive emit joystickActiveChanged(m_joystickActive);

#define SINT16_MAX 32767
#define SINT16_MIN -32768
#define UINT16_MAX 65535

#define DEADZONE 2500
#define MAX_CHANGE 20

#define XBOX
//#define LOGITECH
//define MAC_XBOX

InputHandler::InputHandler() {
    interpolators = new Interpolator*[8];
    quint32 delta = (quint32) UINT16_MAX * 0.03;
    for (int i = 0; i < 8; i++) {
        interpolators[i] = new Interpolator(delta, 100);
    }
    m_joystickActive = false;
    m_joystick = NULL;
    setJoystick(0);
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

    t1MaxSpeed = root->findChild<QObject*>("t1Control");
    t2MaxSpeed = root->findChild<QObject*>("t2Control");
    t3MaxSpeed = root->findChild<QObject*>("t3Control");
    t4MaxSpeed = root->findChild<QObject*>("t4Control");

    t5MaxSpeed = root->findChild<QObject*>("t5Control");
    t6MaxSpeed = root->findChild<QObject*>("t6Control");
    t7MaxSpeed = root->findChild<QObject*>("t7Control");
    t8MaxSpeed = root->findChild<QObject*>("t8Control");


}

QList<JoystickInfo> InputHandler::listJoysticks() {
    return m_joysticks;
}

void applyDeadzone(qint32 &val) {
    if (abs(val) < DEADZONE) {
        val = 0;
    }
}

void InputHandler::scale(qint32 thrusters[]) {
    int values[8] = {0,0,0,0,0,0,0,0};

    values[0] = t1MaxSpeed->property("value").toInt();
    values[1] = t2MaxSpeed->property("value").toInt();
    values[2] = t3MaxSpeed->property("value").toInt();
    values[3] = t4MaxSpeed->property("value").toInt();

    values[4] = t5MaxSpeed->property("value").toInt();
    values[5] = t6MaxSpeed->property("value").toInt();
    values[6] = t7MaxSpeed->property("value").toInt();
    values[7] = t8MaxSpeed->property("value").toInt();

    for(int i = 0; i < 8; i++) {
        thrusters[i] = (int) ((thrusters[i]) * (values[i]/100.0));
    }

}


void normalize(qint32 values[], int size) {
    qint32 valuesMax = 0;
    qint32 max = SINT16_MAX;

    //get Max value
    for (int i = 0; i < size; i++) {
        if (abs(values[i]) > max) {
            valuesMax = abs(values[i]);
        }
    }

    if (valuesMax > max) {
        //Normalize the values based off max
        float n = ((float) max) / ((float) valuesMax);
        for (int i = 0; i < size; i++) {
            values[i] = (qint32) (n * values[i]);
        }
    }
}

void swap(qint32 thrusters[], int t1, int t2) {
    qint32 temp = thrusters[t1-1];
    thrusters[t1-1] = thrusters[t2-1];
    thrusters[t2-1] = temp;
}


void remap(qint32 thrusters[]) {
    qint32 oldMap[8] = {0,0,0,0,0,0,0,0};
    for (int i = 0; i < 8; i++) {
        oldMap[i] = thrusters[i];
    }

    thrusters[6] = oldMap[0];
    thrusters[1] = oldMap[1];
    thrusters[4] = oldMap[2];
    thrusters[3] = oldMap[3];

    thrusters[7] = -1*oldMap[4];
    thrusters[5] = oldMap[5];
    thrusters[0] = oldMap[6];
    thrusters[2] = oldMap[7];
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

        #ifdef MAC_XBOX
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
        velZ -= 1000;
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
        //roll += 1300;

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


        normalize(lateralThrusters, 4);
        normalize(verticalThrusters, 4);

        //do linear interpolation (so we don't ramp up/down too fast)
        for (int i = 0; i < 8; i++) {
            thrusters[i] = interpolators[i]->lerp(thrusters[i]);
        }

        //scale thrusters by slider value
        scale(thrusters);


        remap(thrusters);

        //do conversion to packet values
        //This is thrusters with a capital T (naming conventions yeah...)
        quint8 Thrusters[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 8; ++i) {
            Thrusters[i] = convert(thrusters[i]);
        }

        //Thrusters[0] = 60; Thrusters[1] = 60; Thrusters[2] = 60; Thrusters[3] = 60;
        //Thrusters[4] = 60; Thrusters[5] = 60; Thrusters[6] = 60; Thrusters[7] = 60;
        if (!serial::MotorSet((quint8*) Thrusters)) {
            serial::open();
            qDebug("disconnect");
        }


        //Debug statement
        //qDebug("%d, %d, %d, %d, %d, %d", m_joystick->getAxis(0), m_joystick->getAxis(1), m_joystick->getAxis(2), m_joystick->getAxis(3),
        //       m_joystick->getAxis(4), m_joystick->getAxis(5));


        if (m_joystick->getButtonState(CONT_BUTTON_X_ID)) claw--;
        if (m_joystick->getButtonState(CONT_BUTTON_B_ID)) claw++;

        if (claw >= 254) claw = 254;
        if (claw <= 1) claw = 1;
        serial::ClawSet(claw);


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
