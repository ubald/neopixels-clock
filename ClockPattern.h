#ifndef CLOCK_PATTERN_H
#define CLOCK_PATTERN_H

#include "Time.h"
#include "Color.h"

class RingClock;

class ClockPattern {
	public:
		ClockPattern(RingClock * clock);
		virtual void init();
		virtual void tick();
	protected:
		RingClock * clock;
};

#endif
