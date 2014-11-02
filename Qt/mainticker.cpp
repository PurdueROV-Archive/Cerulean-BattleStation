#include "mainticker.h"
#include "tickclock.h"

void MainTicker::doTick() {
    m_inputHandler->tick(this);
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
