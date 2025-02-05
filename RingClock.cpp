#include "RingClock.h"
#include "patterns/SplashPattern.h"

RingClock::RingClock(
  unsigned long leds[][3],
  unsigned int ledCount,
  unsigned int displayedHours
) :
    leds{leds},
    ledCount{ledCount},
    displayedHours{displayedHours},
    ledsPerHour{ledCount/displayedHours}
{}

RingClock::~RingClock() {
    delete currentPattern;
}

void RingClock::init() {
    currentPattern = new SplashPattern(this);
    currentPattern->init();
}

void RingClock::setPattern(ClockPattern * pattern) {
    if ( currentPattern ) {
        delete currentPattern;
    }
    currentPattern = pattern;
    currentPattern->init();
}

void RingClock::tick(const clock_time_t time) {
    now = time;

    // Copy now to last for the first run
    if ( firstRun ) {
        last = now;
        firstRun = false;
    }

    // Update the current clock pattern
    currentPattern->tick();

    // Save last time to detect changes in the pattern classes
    last = now;
}
