#ifndef DEMO_PATTERN_H
#define DEMO_PATTERN_H

#include "ClockPattern.h"
#include "RingClock.h"



class DemoPattern : public ClockPattern {
	using ClockPattern::ClockPattern;
	public:
		void init() override;
		void tick() override;
		enum PatternState { LOOP, MINUTE_CHANGE, HOUR_CHANGE };

	private:
		void loopyLoop();
		void minuteChange();
		void hourChange();
		PatternState patternState = LOOP;
};

#endif