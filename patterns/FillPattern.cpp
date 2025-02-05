#include "FillPattern.h"
#include "math.h"
#include "platform.h"

void FillPattern::init() {
	ClockPattern::init();
}

void FillPattern::tick() {
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
		float ledPos = (float) i / (float) clock->ledCount;

		unsigned int r = 0;
		unsigned int g = 0;
		unsigned int b = 0;

		if (i == clock->now.seconds) {
			g += 255;
		} else {

			float rotation = 0;
			float delta = 0;
			float wave = 0;
			float largest = max(clock->now.percentClock, clock->now.percentHour);

			// Hour
			if (clock->now.percentClock > clock->now.percentHour) {
				r += ledPos <= clock->now.percentClock && ledPos >= clock->now.percentHour ? 255 : 0;
			} else {
				r += ledPos <= clock->now.percentClock ? 255 : 0;
			}

			// Minutes
			if (clock->now.percentHour > clock->now.percentClock) {
				b += ledPos <= clock->now.percentHour && ledPos >= clock->now.percentClock ? 255 : 0;
			} else {
				b += ledPos <= clock->now.percentHour ? 255 : 0;
			}
			/*if (ledPos <= largest) {
				rotation = -2.*PI*(clock->now.timestamp / 120000.);
				delta = 4.*PI*ledPos;
				wave = cos(rotation+delta);
				b += wave > 0 ? wave * 16 : wave * 127;
			}*/

			if (ledPos <= largest) {
				rotation = -2.*PI*(clock->now.timestamp / 120000.);
				delta = 4.*PI*ledPos;
				wave = sin(rotation+delta);
				g += wave > 0 ? wave * (r>0?64:255) : 0;
				b -= wave > 0 ? wave * 127 : 0;
			}
		}

		clock->leds[i][0] += r;
		clock->leds[i][1] += g;
		clock->leds[i][2] += b;

	}
}
