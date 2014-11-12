#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <QObject>

class Interpolator : public QObject
{
    Q_OBJECT
    qint16 current;
    qint16 target;
    qint32 maxDelta;

public:

    const int msecsPerTick;

    Interpolator(qint32 maxDelta, int millSecsPerTick);

    /**
     * Lerp() assumes you call it once and only once per tick to calculate
     * a new value.
     * @return The interpolated value capped by maxDelta
     */
    qint16 lerp(qint16 newTarget);

    /**
     * Calls lerp() with no change in target
     * @return
     */
    qint16 lerp() {
        return lerp(target);
    }

    qint16 getCurrent() {
        return current;
    }

    qint16 getTarget() {
        return target;
    }

    qint32 getMaxDelta() {
        return maxDelta;
    }
};

#endif // INTERPOLATOR_H
