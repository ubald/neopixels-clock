#include "RingClock.h"
#include "patterns/SplashPattern.h"

RingClock::RingClock(
  unsigned long leds[][3],
  unsigned int ledCount,
  unsigned int displayedHours,
  PatternCreator patternCreators[],
  unsigned int patternCount
) :
  leds{leds},
  ledCount{ledCount},
  displayedHours{displayedHours},
  ledsPerHour{ledCount/displayedHours},
  patternCreators{patternCreators},
  patternCount{patternCount}
{}

RingClock::~RingClock() {
  delete currentPattern;
}

void RingClock::init() {
  currentPattern = new SplashPattern(this);
  currentPattern->init();
}

void RingClock::tick() {
  int second = Time.second();
  unsigned long milliseconds = millis();

  if ( initializing || second != lastSecond ) {
    lastSecond = second;
    if ( initializing ) {
      initializing = false;
      calculating = true;
      return;
    }

    // millis() must be offset on second change since it's from device power on
    millisecondsOffset = milliseconds;

    // NeoPixel library stops some vital interupts that leave millis() pretty slow
    // so we find out how much time has to be made up for here and use that to speed up millis()
    if ( lastMilliseconds != 0 ) {
      lostMillisecondsMultiplicator = 1000.0 / (float)lastMilliseconds;
    }

    if (calculating) {
      calculating = false;
      return;
    }

    if ( !ready ) {
      selectRandomPattern();
      ready = true;
    }
  }

  lastMilliseconds = milliseconds - millisecondsOffset;
  now.milliseconds = (unsigned long) lastMilliseconds * lostMillisecondsMultiplicator;//(timestamp % SECOND);
  now.seconds = (unsigned long) second;//((timestamp / SECOND) % SECONDS_PER_MINUTE);
  now.minutes = (unsigned long) Time.minute();//((timestamp / MINUTE) % MINUTES_PER_HOUR);
  now.hours24 = (unsigned long) Time.hour();//((timestamp / HOUR ) % HOURS_PER_DAY);
  now.hours12 = (unsigned long) Time.hourFormat12();//( now.hours24 >= HOURS_ON_CLOCK ) ? now.hours24 - HOURS_ON_CLOCK : now.hours24;

  // Time as percents, easier to work with
  now.percentSecond = (float)now.milliseconds / SECOND;
  now.percentMinute = ((float)now.seconds / SECONDS_PER_MINUTE) + ((float)now.percentSecond / SECONDS_PER_MINUTE);
  now.percentHour = ((float)now.minutes / MINUTES_PER_HOUR) + ((float)now.percentMinute / MINUTES_PER_HOUR);
  now.percentClock = ((float)now.hours12 / HOURS_ON_CLOCK) + ((float)now.percentHour / HOURS_ON_CLOCK );
  now.percentDay = ((float)now.hours24 / HOURS_PER_DAY) + ((float)now.percentHour / HOURS_PER_DAY );

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

void RingClock::selectRandomPattern() {
  if ( currentPattern ) {
    delete currentPattern;
  }
  currentPattern = patternCreators[random(patternCount)](this);
  currentPattern->init();
}
