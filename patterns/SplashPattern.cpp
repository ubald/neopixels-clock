#include "SplashPattern.h"
#include "math.h"

void SplashPattern::init() {
	ClockPattern::init();
  step = 0;
}

void SplashPattern::tick() {
	ClockPattern::tick();

  step++;

  for ( unsigned int i = 0; i < clock->ledCount; i++ ) {
    int val = (step%60) == i ? 255 : 0;
    clock->leds[i][0] += val;
    clock->leds[i][1] += val;
    clock->leds[i][2] += val;
  }
}
