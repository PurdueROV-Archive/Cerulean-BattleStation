#ifndef MAINTICKER_H
#define MAINTICKER_H

#include "tickclock.h"
#include "inputhandler.h"
#include <QQmlContext>

class MainTicker : public TickClock {

    void doTick();

    InputHandler* m_inputHandler;

public:
    MainTicker(quint64 targetTicksPerSec);
    ~MainTicker();

    void registerInContext(QQmlContext* context);

signals:


public slots:


};

#endif // MAINTICKER_H
