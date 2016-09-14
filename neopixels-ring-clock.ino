#include "particle/neopixel.h"
#include "RingClock.h"
#include "patterns/DemoPattern.h"

// NeoPixels Pin
#define PIN D2
#define LED_COUNT 60
#define DISPLAYED_HOURS 12

#define PATTERN_COUNT 2
PatternCreator patterns[PATTERN_COUNT] {
  createPattern<DemoPattern>,
  createPattern<DemoPattern>
};

// LED values array
unsigned long leds[LED_COUNT][3];

// NeoPixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, WS2812B);

// RingClock
RingClock ringClock = RingClock(leds, LED_COUNT, DISPLAYED_HOURS, patterns, PATTERN_COUNT );

// Setup
void setup() {
  // If analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(A0));

  Time.zone(-5);
  //Particle.syncTime() once per day

  // Initialize strip
  strip.begin();
  // Set all to black
  strip.show();

  // Initialize the clock
  ringClock.init();
}

// Loop
float framerate = 60.0;
float interval = 1000.0 / framerate;
unsigned long lastFrame = 0;

void loop() {
  unsigned long now = millis();
  if ( now - lastFrame >= interval ) {
    lastFrame = now;

    // Update values
    ringClock.tick( );

    // Set pixels color
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
