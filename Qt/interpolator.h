#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <QObject>

class Interpolator : public QObject
{
    Q_OBJECT
    Sint16 current;
    Sint16 target;
    Sint32 maxDelta;

public:

    const int msecsPerTick;

    Interpolator(Sint32 maxDelta, int millSecsPerTick);

    /**
     * Lerp() assumes you call it once and only once per tick to calculate
     * a new value.
     * @return The interpolated value capped by maxDelta
     */
    Sint16 lerp();

    Sint16 getCurrent() {
        return current;
    }

    Sint16 getTarget() {
        return target;
    }

    Sinte32 getMaxDelta() {
        return maxDelta;
    }
};

#endif // INTERPOLATOR_H
