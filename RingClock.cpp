#include "RingClock.h"
#include "Arduino.h";

RingClock::RingClock(
  unsigned long leds[], 
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
{

}

RingClock::~RingClock() {
  delete currentPattern;
}

void RingClock::init() {
  if ( currentPattern ) {
    delete currentPattern;
  }
  currentPattern = patternCreators[0](this);
  currentPattern->init();
}

void RingClock::tick(unsigned long timestamp) {
  now.milliseconds = (unsigned long) (timestamp % SECOND);
  now.seconds = (unsigned long) ((timestamp / SECOND) % SECONDS_PER_MINUTE);
  now.minutes = (unsigned long) ((timestamp / MINUTE) % MINUTES_PER_HOUR) + 16;
  now.hours = (unsigned long) ((timestamp / HOUR ) % HOURS_PER_DAY);
  if ( now.hours >= HOURS_ON_CLOCK ) now.hours -= HOURS_ON_CLOCK;

  now.percentSecond = (float)now.milliseconds / SECOND;
  now.percentMinute = ((float)now.seconds / SECONDS_PER_MINUTE) + ((float)now.percentSecond / SECONDS_PER_MINUTE);
  now.percentHour = ((float)now.minutes / MINUTES_PER_HOUR) + ((float)now.percentMinute / MINUTES_PER_HOUR);
  now.percentClock = ((float)now.hours / HOURS_ON_CLOCK) + ((float)now.percentHour / HOURS_ON_CLOCK );

  /*Serial.print(now.percentClock);
  Serial.print(' ');
  Serial.print(now.percentHour);
  Serial.print(' ');
  Serial.print(now.percentMinute);
  Serial.print(' ');
  Serial.print(now.percentSecond);
  Serial.print(' ');
  Serial.print(now.hours);
  Serial.print(' ');
  Serial.print(now.minutes);
  Serial.print(' ');
  Serial.print(now.seconds);
  Serial.print(' ');
  Serial.println(now.milliseconds);*/

  if ( !ready ) {
    last = now;
  }

  currentPattern->tick();

  last = now;

  ready = true;
}