#ifndef COLORWHEEL_H
#define COLORWHEEL_H

uint32_t wheel(uint8_t wheelPos) {
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
   return Adafruit_NeoPixel::Color(255 - wheelPos * 3, 0, wheelPos * 3);
  } else if(wheelPos < 170) {
    wheelPos -= 85;
   return Adafruit_NeoPixel::Color(0, wheelPos * 3, 255 - wheelPos * 3);
  } else {
   wheelPos -= 170;
   return Adafruit_NeoPixel::Color(wheelPos * 3, 255 - wheelPos * 3, 0);
  }
}

#endif /* end of include guard: COLORWHEEL_H */
