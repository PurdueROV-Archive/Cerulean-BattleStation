#ifndef MAINTICKER_H
#define MAINTICKER_H

#include "tickclock.h"
#include "inputhandler.h"
#include <QQmlContext>

class MainTicker : public TickClock {

    void doTick();



public:
    MainTicker(quint64 targetTicksPerSec);
    ~MainTicker();

    void registerInContext(QQmlContext* context);

    InputHandler* m_inputHandler;

signals:


public slots:


};

#endif // MAINTICKER_H
