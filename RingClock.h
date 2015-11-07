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
			unsigned int displayedHours, 
			PatternCreator patterns[], 
			unsigned int patternCount
		);
		~RingClock();
		void init();
		void tick( unsigned long timestamp );
		unsigned long (*leds)[3];
		unsigned int ledCount;
		unsigned int displayedHours;
		unsigned int ledsPerHour;
		time_t now;
		time_t last;

	private:
		void selectRandomPattern();
		unsigned int patternCount;
		PatternCreator * patternCreators;
		ClockPattern * currentPattern;
		bool firstRun = true;
};

#endif