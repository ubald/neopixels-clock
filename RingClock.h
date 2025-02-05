#ifndef RING_CLOCK_H
#define RING_CLOCK_H

#include "Time.h"
#include "ClockPattern.h"
#include "PatternCreator.h"

class RingClock {
	public:
		RingClock(
			unsigned long leds[][3],
			unsigned int ledCount,
			unsigned int displayedHours
		);
		~RingClock();
		void init();
		void tick(const clock_time_t time);
		void setPattern(ClockPattern * pattern);
		unsigned long (*leds)[3];
		unsigned int ledCount;
		unsigned int displayedHours;
		unsigned int ledsPerHour;
		clock_time_t now;
		clock_time_t last;

	private:
		void selectRandomPattern();
		unsigned int patternCount;
		PatternCreator * patternCreators;
		ClockPattern * currentPattern;
		bool firstRun = true;
};
#endif
