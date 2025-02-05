#ifndef FILL_PATTERN_H
#define FILL_PATTERN_H

#include "ClockPattern.h"
#include "RingClock.h"

class FillPattern : public ClockPattern {
	using ClockPattern::ClockPattern;
	public:
		void init() override;
		void tick() override;
	private:
};

#endif
