#include "platform.h"
#include "math.h"
#include "ClockPattern.h"
#include "RingClock.h"

ClockPattern::ClockPattern(const RingClock * clock) : clock{clock} {}

void ClockPattern::init() {}

void ClockPattern::tick() {}

float ClockPattern::distance(float a, float b) {
    float distance = a - b;

    // Don't allow distance to be greater than half the clock, so
    // calculate distances before and after the needle.
    float halfClock = clock->ledCount / 2;
    if (distance >= halfClock) {
        distance -= clock->ledCount;
    } else if (distance <= -halfClock) {
        distance += clock->ledCount;
    }

    return distance;
}

float ClockPattern::fadeLin(float distance, float head, float tail) {
    float length = distance >= 0 ? head : tail;
    return length == 0. ? 0. : 1.0 - (fmin(length, fabs(distance)) / length);
}

float ClockPattern::fadePow(float distance, float head, float tail, float p) {
    float length = distance >= 0 ? head : tail;
    return length == 0. ? 0. : 1.0 - pow((fmin(length, fabs(distance)) / length), p);
}
