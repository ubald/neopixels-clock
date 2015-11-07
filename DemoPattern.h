#ifndef DEMO_PATTERN_H
#define DEMO_PATTERN_H

#include "ClockPattern.h"
#include "RingClock.h"

enum PatternState { LOOP, MINUTE_CHANGE, HOUR_CHANGE };

class DemoPattern : public ClockPattern {
	using ClockPattern::ClockPattern;
	public:
		void init() override;
		void tick() override;
	private:
		void doPatternLoop_test( );
		void doPatternLoop();
		void doPatternMinuteChange();
		void doPatternHourChange();
		PatternState patternState = LOOP;
};

#endif