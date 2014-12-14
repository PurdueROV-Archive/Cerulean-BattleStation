#include "mainticker.h"
#include "tickclock.h"
#include "serial.h"

void MainTicker::doTick() {
    m_inputHandler->tick(this);
//    quint8 val = 0xF0;
    //quint64 t = getTickCount();
   //if (t % 2 == 0) {
//        if ((t / 2) % 4 == 0) {
//            val = 0x08;
//        }
//        qDebug() << val;
//        if(!serial::MotorSet(val, val, val, val, val, val, val, val)) {
//            qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
//        }
        serial::send();
   //}
}

MainTicker::MainTicker(quint64 targetTicksPerSec) :
    TickClock(targetTicksPerSec) {
    m_inputHandler = new InputHandler();
}

MainTicker::~MainTicker() {
}

void MainTicker::registerInContext(QQmlContext* context) {
    context->setContextProperty("c_inputHandler", m_inputHandler);
}
