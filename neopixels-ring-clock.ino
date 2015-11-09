#include "./Adafruit_NeoPixel.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "RingClock.h"
#include "DemoPattern.h"

// NeoPixels Pin
#define PIN 6
#define LED_COUNT 60
#define DISPLAYED_HOURS 12

#define PATTERN_COUNT 2
PatternCreator patterns[PATTERN_COUNT] {
  createPattern<DemoPattern>,
  createPattern<DemoPattern>
};

// LED values array
unsigned long leds[LED_COUNT][3];

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

// RingClock
RingClock ringClock = RingClock(leds, LED_COUNT, DISPLAYED_HOURS, patterns, PATTERN_COUNT );

// Setup
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  // If analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

  // Initialize strip
  strip.begin();
  // Set all to black
  strip.show();

  // Initialize the clock
  ringClock.init();

  // Start serial port for debug
  Serial.begin(57600);
}

// Loop
void loop() {
  // Update values
  ringClock.tick( millis() + 1446878819 );
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
