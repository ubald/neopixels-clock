#ifndef SIMPLE_PATTERN_H
#define SIMPLE_PATTERN_H

#include "ClockPattern.h"
#include "RingClock.h"

/**
 * Simple Clock Pattern
 */
class SimplePattern : public ClockPattern {
	using ClockPattern::ClockPattern;
	public:
		void init() override;
		void tick() override;
	private:
};

#endif
