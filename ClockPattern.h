#ifndef CLOCK_PATTERN_H
#define CLOCK_PATTERN_H

#include "Time.h"

class RingClock;

class ClockPattern {
	public:
		ClockPattern(const RingClock * clock);
		virtual void init();
		virtual void tick();
	protected:
		const RingClock * clock;
};

#endif
