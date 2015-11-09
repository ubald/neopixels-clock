#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

class Color {

public:

  inline static uint32_t fromRGB(uint8_t r, uint8_t g, uint8_t b) {
  	return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  }

  static uint32_t Wheel(uint8_t pos)
  {
    if (pos < 85) {
     return fromRGB(pos * 3, 255 - pos * 3, 0);
    } else if (pos < 170) {
     pos -= 85;
     return fromRGB(255 - pos * 3, 0, pos * 3);
    } else {
     pos -= 170; 
     return fromRGB(0, pos * 3, 255 - pos * 3);
    }
  }

};

#endif
