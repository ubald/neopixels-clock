#include "DemoPattern.h"
#include "Arduino.h"

void DemoPattern::init() {
	ClockPattern::init();
}

void DemoPattern::tick() {
	ClockPattern::tick();

	if ( clock->now.hours != clock->last.hours ) {
      patternState = HOUR_CHANGE;
    } else if ( clock->now.minutes != clock->last.minutes ) {
      patternState = MINUTE_CHANGE;
    }


Serial.println(clock->now.seconds);

    switch ( patternState ) {
	    case LOOP:
	    Serial.println("A");
	      doPatternLoop( );
	      break;
	    case MINUTE_CHANGE:
	    Serial.println("B");
	      doPatternMinuteChange( );
	      break;
	    case HOUR_CHANGE:
	    Serial.println("C");
	      doPatternHourChange( );
	      break;
  }

	
}

void DemoPattern::doPatternLoop_test( ) {

  Serial.print(clock->now.percentClock);
  Serial.print(' ');
  Serial.print(clock->now.percentHour);
  Serial.print(' ');
  Serial.print(clock->now.percentMinute);
  Serial.print(' ');
  Serial.print(clock->now.percentSecond);
  Serial.println(' ');

	for ( unsigned int i = 0; i< clock->ledCount; i++) {
		clock->leds[i] = Color::fromRGB(
			i <= clock->now.percentHour * clock->ledCount ? 255 : 0, 
			i == clock->now.hours * HOURS_ON_CLOCK ? 127 : 0, 
			i > clock->now.percentHour * clock->ledCount ? clock->now.percentHour * 255 : 0
		);
	}
}

void DemoPattern::doPatternLoop() {

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

Serial.println(clock->now.percentClock);


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

	clock->leds[i] = Color::fromRGB( min(r, 255), min(g, 255), min(b, 255) );

    /*byte hourValue = 0;
	if ( i == hourPosition ) {
		hourValue = 255;
	} else if ( i == pre_hour1 || i == post_hour1 ) {
		hourValue = 64;
	} else if ( i == pre_hour2 || i == post_hour2 ) {
		hourValue = 16;
	}

	byte minuteValue = 65;
	if ( i == minutePosition ) {
		minuteValue = 255;
	} else if ( i == pre_minute1 || i == post_minute1 ) {
		minuteValue = 32;
	}

	byte tailValue = 0;
	if ( i == tail1 ) {
		tailValue = 32;
	} else if ( i == tail2 ) {
		tailValue = 16;
	} else if ( i == tail3 ) {
		tailValue = 8;
	}

	color = Color::fromRGB( isHour ? hourValue : ( isSecond ? glow : 0 ), isMinute ? minuteValue : ( isSecond ? glow : 0 ), isSecond ? 255 : tailValue );
    */
	//clock->leds[i] = color;
  }
}

void DemoPattern::doPatternMinuteChange() {
  /*colorWipe(Color(255, 0, 0), 50);
  colorWipe(Color(0, 255, 0), 50);
  colorWipe(Color(0, 0, 255), 50);*/
  patternState = LOOP;
}

void DemoPattern::doPatternHourChange() {
  patternState = LOOP;
}