#include "RingClock.h"
#include "Arduino.h";

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
  selectRandomPattern();
}

void RingClock::tick(unsigned long timestamp) {
  // Absolute time
  now.milliseconds = (unsigned long) (timestamp % SECOND);
  now.seconds = (unsigned long) ((timestamp / SECOND) % SECONDS_PER_MINUTE);
  now.minutes = (unsigned long) ((timestamp / MINUTE) % MINUTES_PER_HOUR);
  now.hours24 = (unsigned long) ((timestamp / HOUR ) % HOURS_PER_DAY);
  now.hours12 = ( now.hours24 >= HOURS_ON_CLOCK ) ? now.hours24 - HOURS_ON_CLOCK : now.hours24;

  // Time as percents, easier to work with
  now.percentSecond = (float)now.milliseconds / SECOND;
  now.percentMinute = ((float)now.seconds / SECONDS_PER_MINUTE) + ((float)now.percentSecond / SECONDS_PER_MINUTE);
  now.percentHour = ((float)now.minutes / MINUTES_PER_HOUR) + ((float)now.percentMinute / MINUTES_PER_HOUR);
  now.percentClock = ((float)now.hours12 / HOURS_ON_CLOCK) + ((float)now.percentHour / HOURS_ON_CLOCK );
  now.percentDay = ((float)now.hours24 / HOURS_PER_DAY) + ((float)now.percentHour / HOURS_PER_DAY );

  Serial.print(now.percentDay);
  Serial.print(' ');
  Serial.print(now.percentClock);
  Serial.print(' ');
  Serial.print(now.percentHour);
  Serial.print(' ');
  Serial.print(now.percentMinute);
  Serial.print(' ');
  Serial.print(now.percentSecond);
  Serial.print(' ');
  Serial.print(now.hours24);
  Serial.print(' ');
  Serial.print(now.hours12);
  Serial.print(' ');
  Serial.print(now.minutes);
  Serial.print(' ');
  Serial.print(now.seconds);
  Serial.print(' ');
  Serial.println(now.milliseconds);

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