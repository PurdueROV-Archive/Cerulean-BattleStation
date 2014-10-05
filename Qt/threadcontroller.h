#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QThread>
#include "tickclock.h"

class ThreadController : public QObject {
    Q_OBJECT
    QThread mainThread;
    TickClock* ticker;
public :
    ThreadController(TickClock* tc);

    ~ThreadController();

signals:
    void start();
    void stop();
public slots:
    void startThread();
    void stopThread();
};

#endif // MAINCONTROLLER_H
