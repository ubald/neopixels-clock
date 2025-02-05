#include "Particle.h"
#include "Time.h"
#include "particle/neopixel.h"
#include "RingClock.h"
#include "patterns/SimplePattern.h"
#include "patterns/DemoPattern.h"
#include "patterns/SmoothPattern.h"
#include "patterns/FillPattern.h"

// Debug mode, time flies!
#define DEBUG false

// NeoPixels Pin
#define PIN D2

// LED Ring Configuration
#define LED_COUNT 60

// Clock Configuration
#define DISPLAYED_HOURS 12

// Patterns Configuration
#define PATTERN_COUNT 1
PatternCreator patterns[PATTERN_COUNT] {
    //createPattern<SimplePattern>,
    createPattern<DemoPattern>,
    //createPattern<SmoothPattern>,
    //createPattern<FillPattern>
};

// LED values array
unsigned long leds[LED_COUNT][3];

// NeoPixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, WS2812B);

// RingClock
RingClock ringClock = RingClock(leds, LED_COUNT, DISPLAYED_HOURS);

// Setup
void setup() {

#if DEBUG
    Serial.begin(9600);
#endif

    // If analog input pin 0 is unconnected, random analog
    // noise will cause the call to randomSeed() to generate
    // different seed numbers each time the sketch runs.
    // randomSeed() will then shuffle the random function.
    randomSeed(analogRead(A0));

    // TODO: Make configurable
    Time.zone(-5);

    // Initialize strip
    strip.begin();
    // Set all to black
    strip.show();

    // Initialize the clock
    ringClock.init();
}

// Timekeeping
int lastDay = 0;

// Loop
float framerate = 60.0;
float interval = 1000.0 / framerate;

unsigned long lastFrame = 0;
unsigned long lastPatternChange = 0;

int lastSecond = 0;
unsigned long lastMillisecond = 0;
unsigned long millisecondsOffset = 0;
float accumulator = 0;
int steps = 0;

float fastMillisecond = 0;

bool initializing = true;
bool calculating = false;
bool ready = false;

clock_time_t now;

void loop() {
    unsigned long milliseconds = millis();
    if ( milliseconds - lastFrame >= interval ) {
        lastFrame = milliseconds;

        // Check for new day, if the day changed, sync time with the cloud
        int day = Time.day();
        if ( day != lastDay ) {
            Particle.syncTime();
            lastDay = day;
        }

        // Get time, do it here since we might change microprocessor at one point
        // and the method might change

        int seconds = Time.second();
        if ( initializing || seconds != lastSecond ) {
            lastSecond = seconds;
            if ( initializing ) {
                initializing = false;
                calculating = true;
                return;
              }

            // Reset the ms accumulator
            accumulator = 0;

            // millis() must be offset on second change since it's from device
            // power on and we don't have a relaible millis() function.
            millisecondsOffset = milliseconds;

            // NeoPixel library stops some vital interupts that leave millis() pretty
            // slow so we find out how much time has really passed in the last second
            // and use that to speed up millis()
            if ( steps != 0 ) {
                //fastMillisecond = 1000. / (float) lastMillisecond;
                fastMillisecond = 1000. / (float) steps;
            }

            // Reset the steps counter
            steps = 0;

            if (calculating) {
                // First loop con't render anything since we haven't got our deltas yet
                calculating = false;
                return;
            }

            if ( !ready ) {
                selectRandomPattern();
                ready = true;
            }

            if ( milliseconds - lastPatternChange >= 10000 ) {
                selectRandomPattern();
                lastPatternChange = milliseconds;
            }
        }

        // Steps counter
        steps++;
        // Fake ms time
        lastMillisecond = milliseconds - millisecondsOffset;
        // Simulated ms time
        accumulator += fastMillisecond;

#if DEBUG
        accumulator = ((milliseconds+1239350) * 200);
        now.timestamp = accumulator;
        now.milliseconds = accumulator % 1000;
        now.seconds = ((accumulator / SECOND) % SECONDS_PER_MINUTE);
        now.minutes = ((accumulator / MINUTE) % MINUTES_PER_HOUR);
        now.hours24 = ((accumulator / HOUR ) % HOURS_PER_DAY);
        now.hours12 = ( now.hours24 >= HOURS_ON_CLOCK ) ? now.hours24 - HOURS_ON_CLOCK : now.hours24;
#else
        //unsigned long ms = lastMillisecond * fastMillisecond;
        now.timestamp += accumulator;
        now.milliseconds = accumulator;
        Serial.print(now.timestamp);
        Serial.print(" ");
        Serial.println(now.milliseconds);
        now.seconds = (unsigned long) seconds;
        now.minutes = (unsigned long) Time.minute();
        now.hours24 = (unsigned long) Time.hour();
        now.hours12 = (unsigned long) Time.hourFormat12();
#endif
        // Time as percents, easier to work with
        now.percentSecond = (float)now.milliseconds / SECOND;
        now.percentMinute = ((float)now.seconds / SECONDS_PER_MINUTE) + ((float)now.percentSecond / SECONDS_PER_MINUTE);
        now.percentHour = ((float)now.minutes / MINUTES_PER_HOUR) + ((float)now.percentMinute / MINUTES_PER_HOUR);
        now.percentClock = ((float)now.hours12 / HOURS_ON_CLOCK) + ((float)now.percentHour / HOURS_ON_CLOCK );
        now.percentDay = ((float)now.hours24 / HOURS_PER_DAY) + ((float)now.percentHour / HOURS_PER_DAY );

        // Update values
        ringClock.tick(now);

        // Set pixels color and reset our array of values
        for ( unsigned int i = 0; i < LED_COUNT; i++ ) {
            strip.setPixelColor( i, min(leds[i][0],255), min(leds[i][1],255), min(leds[i][2],255) );
            leds[i][0] = 0;
            leds[i][1] = 0;
            leds[i][2] = 0;
        }

        // Output
        strip.show();
    }
}


void selectRandomPattern() {
    /*if ( currentPattern ) {
    delete currentPattern;
    }
    currentPattern = patternCreators[random(patternCount)](this);
    currentPattern->init();*/
    ringClock.setPattern(patterns[random(PATTERN_COUNT)](&ringClock));
}
