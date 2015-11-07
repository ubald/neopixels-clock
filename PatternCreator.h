#ifndef PATTERN_CREATOR_H
#define PATTERN_CREATOR_H

#include "RingClock.h"
#include "ClockPattern.h";

template< typename T > ClockPattern * createPattern(const RingClock * clock) {
    return new T(clock);
}
typedef ClockPattern * (*PatternCreator)(const RingClock * clock);

#endif