#include "SimplePattern.h"

void SimplePattern::init() {
	ClockPattern::init();
}

void SimplePattern::tick() {
	ClockPattern::tick();
	for ( unsigned int i = 0; i < clock->ledCount; i++ ) {
		unsigned int hourPosition = (clock->now.percentClock * clock->ledCount);
		unsigned int minutePosition = (clock->now.percentHour * clock->ledCount);
		unsigned int secondPosition = (clock->now.percentMinute * clock->ledCount);

		clock->leds[i][0] += (i == hourPosition ? 255 : 0);
		clock->leds[i][1] += (i == minutePosition ? 255 : 0);
		clock->leds[i][2] += (i == secondPosition ? 255 : 0);
	}
}
