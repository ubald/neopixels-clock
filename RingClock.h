#ifndef RING_CLOCK_H
#define RING_CLOCK_H

#include "application.h"
#include "Time.h"
#include "ClockPattern.h"
#include "PatternCreator.h"

class RingClock {
	public:
		RingClock(
			unsigned long leds[][3],
			unsigned int ledCount,
			unsigned int displayedHours,
			PatternCreator patterns[],
			unsigned int patternCount
		);
		~RingClock();
		void init();
		void tick();
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
		bool initializing = true;
		bool calculating = false;
		bool ready = false;
		bool firstRun = true;
		int lastSecond = 0;
		unsigned long lastMilliseconds = 0;
		unsigned long  millisecondsOffset = 0;
		float lostMillisecondsMultiplicator = 1.0;
};

#endif
