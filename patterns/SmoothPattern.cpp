#include "SmoothPattern.h"
#include "math.h"
#include "platform.h"

void SmoothPattern::init() {
	ClockPattern::init();
}

void SmoothPattern::tick() {
	ClockPattern::tick();

	float hourPosition = (clock->now.percentClock * clock->ledCount);
	float minutePosition = (clock->now.percentHour * clock->ledCount);
	float secondPosition = (clock->now.percentMinute * clock->ledCount);
	float millisecondPosition = (clock->now.percentSecond * clock->ledCount) + secondPosition;

	float millisecondWidth = 1.0;
	float secondWidth = 1.0;
	float minuteWidth = 1.5;
	float hourWidth = 2.5;

	float glow = 255 * ( 1. - pow(clock->now.percentSecond, 0.5) );
	float kick = 255 * pow(clock->now.percentSecond, 0.25);

	for ( unsigned int i = 0; i < clock->ledCount; i++ ) {
		unsigned int r = 0;
		unsigned int g = 0;
		unsigned int b = 0;

		// Hour
		r += round(fadeLin(distance(i, hourPosition), hourWidth, hourWidth) * 255.0);
		g += round(fadeLin(distance(i, hourPosition), hourWidth-1, hourWidth-1) * 127.0);

		// Minutes
		g += round(fadeLin(distance(i, minutePosition), minuteWidth, minuteWidth) * 255.0);
		b += round(fadeLin(distance(i, minutePosition), minuteWidth+1, minuteWidth+1) * 127.0);

		// Seconds
		float secondValue = fadeLin(distance(i, secondPosition), 1, 2);
		r += round(secondValue * glow);
		g += round(secondValue * kick);
		b += round(secondValue * 255.);

		// Milliseconds
		r += round(fadeLin(distance(i, millisecondPosition), 1, 3) * 127.0);
		g += round(fadeLin(distance(i, millisecondPosition), 0, 2) * 127.0);
		b += round(fadeLin(distance(i, millisecondPosition), 1, 4) * 127.0);

		clock->leds[i][0] += r;
		clock->leds[i][1] += g;
		clock->leds[i][2] += b;

	}
}
