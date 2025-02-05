#ifndef SMOOTH_PATTERN_H
#define SMOOTH_PATTERN_H

#include "ClockPattern.h"
#include "RingClock.h"

class SmoothPattern : public ClockPattern {
	using ClockPattern::ClockPattern;
	public:
		void init() override;
		void tick() override;
	private:
};

#endif
