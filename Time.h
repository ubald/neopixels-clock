#ifndef CLOCK_H
#define CLOCK_H

const unsigned long SECOND = 1000;
const unsigned long SECONDS_PER_MINUTE = 60;
const unsigned long MINUTE = SECONDS_PER_MINUTE * SECOND;
const unsigned long MINUTES_PER_HOUR = 60;
const unsigned long HOUR = MINUTES_PER_HOUR * MINUTE;
const unsigned long HOURS_PER_DAY = 24;
const unsigned long HOURS_ON_CLOCK = 12;

struct time_t {
  unsigned long hours24;
  unsigned long hours12;
  unsigned long minutes;
  unsigned long seconds;
  unsigned long milliseconds;

  float percentDay;
  float percentClock;
  float percentHour;
  float percentMinute;
  float percentSecond;
};

#endif