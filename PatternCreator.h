#ifndef PATTERN_CREATOR_H
#define PATTERN_CREATOR_H

#include "RingClock.h"
#include "ClockPattern.h"

template< typename T > ClockPattern createPattern(RingClock * clock) {
    return T(clock);
}

typedef ClockPattern (*PatternCreator)(RingClock * clock);

#endif
