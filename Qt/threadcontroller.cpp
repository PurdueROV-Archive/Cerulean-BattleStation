#include "threadcontroller.h"
#include "tickclock.h"

ThreadController::ThreadController(TickClock* tc) {
    ticker = tc;
    ticker->moveToThread(&mainThread);
    connect(&mainThread, &QThread::finished, ticker, &QObject::deleteLater);
    connect(&mainThread, &QThread::finished, &mainThread, &QObject::deleteLater);
    connect(this, &ThreadController::start, ticker, &TickClock::run);
    connect(this, &ThreadController::stop, ticker, &TickClock::stop);
    mainThread.start();
}

ThreadController::~ThreadController() {
    mainThread.quit();
    mainThread.wait();
}

void ThreadController::startThread()  {
    emit start();
}

void ThreadController::stopThread()  {
    emit stop();
}
