#include "DemoPattern.h"
#include "Arduino.h"

void DemoPattern::init() {
	ClockPattern::init();
}

void DemoPattern::tick() {
	ClockPattern::tick();

	// Detect the changes we are interested in reacting to
	if ( clock->now.hours12 != clock->last.hours12 ) {
      patternState = DemoPattern::HOUR_CHANGE;
    } else if ( clock->now.minutes != clock->last.minutes ) {
      patternState = DemoPattern::MINUTE_CHANGE;
    }
loopyLoop();
return;
    // Pseudo state machine
    switch ( patternState ) {
	    case DemoPattern::LOOP:
	      loopyLoop( );
	      break;
	    case DemoPattern::MINUTE_CHANGE:
	      minuteChange( );
	      break;
	    case DemoPattern::HOUR_CHANGE:
	      hourChange( );
	      break;
  }
}

void DemoPattern::loopyLoop() {

  unsigned int tail = ((clock->now.percentSecond * clock->ledCount) + (clock->now.percentMinute * clock->ledCount));
  unsigned int tail1 = tail % clock->ledCount;
  unsigned int tail2 = (clock->ledCount + tail - 1) % clock->ledCount;
  unsigned int tail3 = (clock->ledCount + tail - 2) % clock->ledCount;

  unsigned int hourPosition = (clock->now.percentClock * clock->ledCount);
  unsigned int pre_hour1 = (clock->ledCount + hourPosition - 1) % clock->ledCount;
  unsigned int pre_hour2 = (clock->ledCount + hourPosition - 2) % clock->ledCount;
  unsigned int post_hour1 = (hourPosition + 1) % clock->ledCount;
  unsigned int post_hour2 = (hourPosition + 2) % clock->ledCount;

  unsigned int minutePosition = (clock->now.percentHour * clock->ledCount);
  unsigned int pre_minute1 = (clock->ledCount + minutePosition - 1) % clock->ledCount;
  unsigned int post_minute1 = (minutePosition + 1) % clock->ledCount;

  unsigned int glow = 255 * ( 1. - pow(clock->now.percentSecond, 0.25) );

  for ( unsigned int i = 0; i < clock->ledCount; i++ ) {
    // Bounds loop around edges, so check individually
    bool isHour = i == pre_hour2 || i == pre_hour1 || i == hourPosition || i == post_hour1 || i == post_hour2;
    bool isMinute = i == pre_minute1 || i == minutePosition || i == post_minute1;
    bool isSecond = i == clock->now.seconds;

	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;

	if ( i == hourPosition ) {
		r += 255;
		g += 16;
	} else if ( i == pre_hour1 || i == post_hour1 ) {
		r += 64;
		g += 16;
	} else if ( i == pre_hour2 || i == post_hour2 ) {
		r += 16;
		g += 8;
	}

	if ( i == minutePosition ) {
		g += 255;
		b += 16;
	} else if ( i == pre_minute1 || i == post_minute1 ) {
		g += 32;
		b += 16;
	}

	if ( i == tail1 ) {
		r += 16;
		b += 32;
	} else if ( i == tail2 ) {
		r += 16;
		b += 16;
	} else if ( i == tail3 ) {
		r += 16;
		b += 8;
	}

	if ( isSecond ) {
		r += glow;
		g += glow;
		b += 255;
	}

	//clock->leds[i] = Color::fromRGB( min(r, 255), min(g, 255), min(b, 255) );
	clock->leds[i][0] += r;
	clock->leds[i][1] += g;
	clock->leds[i][2] += b;

  }
}

void DemoPattern::minuteChange() {
  patternState = DemoPattern::LOOP;
}

void DemoPattern::hourChange() {
  patternState = DemoPattern::LOOP;
}