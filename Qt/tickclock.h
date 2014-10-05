#ifndef TICKCLOCK_H
#define TICKCLOCK_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>
#include <QCoreApplication>

class TickClock : public QObject
{
    Q_OBJECT

    //  Assuming a tick rate of 20 t/s (50 ms long ticks),
    //  an unsigned 32-bit integer can hold us over for
    //  about 7 years of uninterrupted usage, but an unsigned
    //  16-bit integer only holds 54 minutes. We're on modern
    //  hardware so we honestly don't care about 4 vs 2 bytes.
    quint32 tickCount;
    quint64 lastTickMillis;
    quint16 cantKeepUpTicks;

    virtual void doTick() = 0;

    bool isRunning() {
        QMutexLocker locker(mutex);
        return running;
    }

    void setRunning(bool val) {
        QMutexLocker locker(mutex);
        running = val;
    }

public slots:
    void run() {
        setRunning(true);
        qDebug() << "Loop starting";
        while(isRunning()) {
            QCoreApplication::processEvents();
            tickAndWait();
        }
        qDebug() << "Stopped.";
    }

    void stop() {
        qDebug() << "Requesting stop...";
        setRunning(false);
    }

public:
    TickClock(quint64 targetTicksPerSec) :
        targetTPS(targetTicksPerSec),
        tickLenMillis(1000 / targetTicksPerSec),
        tickLengthSecs(1.0 / (float) targetTicksPerSec)
    {
        tickCount = 0;
        lastTickMillis = QDateTime::currentMSecsSinceEpoch ();
        cantKeepUpTicks = 0;
        mutex = new QMutex();
    }

    void tickAndWait() {
        //  Perform tick action
        doTick();
        quint64 currentTime = QDateTime::currentMSecsSinceEpoch ();
        if(currentTime < lastTickMillis) {
            qWarning() << "Time went backwards!";
            //  Prevent this preposterousness
            currentTime = lastTickMillis;
        }
        quint64 deltaTime = currentTime - lastTickMillis;
        qint64 diff = tickLenMillis - (qint64) deltaTime;
        if(diff > 0) {
            cantKeepUpTicks = 0;

            QThread::msleep(diff);
        } else {
            //  Only print every second at most and not on the first tick
            if(cantKeepUpTicks != 0 &&
                    (cantKeepUpTicks % secondsToTicks(1.0) == 0 || -diff > 1000)) {
                qDebug() << "Can't keeep up! Behind by " << -diff << "ms";
            }
            cantKeepUpTicks++;
        }
        tickCount++;
        lastTickMillis = QDateTime::currentMSecsSinceEpoch ();
    }

    quint64 getTickCount() {
        return tickCount;
    }

    quint64 secondsToTicks(float secs) {
        return (quint64)(secs * targetTPS);
    }

    float ticksToSeconds(quint64 ticks) {
        return ticks * tickLengthSecs;
    }

    const quint64 targetTPS;
    const quint64 tickLenMillis;
    const float tickLengthSecs;
    QMutex* mutex;
    bool running;
};



#endif // TICKCLOCK_H
