#ifndef SPLASH_PATTERN_H
#define SPLASH_PATTERN_H

#include "ClockPattern.h"
#include "RingClock.h"

class SplashPattern : public ClockPattern {
	using ClockPattern::ClockPattern;
	public:
		void init() override;
		void tick() override;
  private:
    int step = 0;
};

#endif
