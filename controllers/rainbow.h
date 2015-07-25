#include "controllers/strobe.h"

#ifndef RAINBOW_H
#define RAINBOW_H

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

class Rainbow : public StrobeController {
public:
  Rainbow(uint16_t onTime = 20, uint8_t speed = 1, uint16_t pixelColorOffset = 0, uint16_t offTime = 0)
  : StrobeController(onTime, offTime), speed(speed), pixelColorOffset(pixelColorOffset) { }

  virtual void strobeOn(uint32_t now) override {
    for (uint16_t i = 0; i < numPixels(); i++) {
      setPixelColor(i, wheel(255 & (wheelPos + i * pixelColorOffset)));
    }
  }
  virtual void postStep(bool state) override {
    if (state) {
      wheelPos = (wheelPos + speed) & 255;
    }
  }

private:
  uint16_t pixelColorOffset;
  uint8_t wheelPos;
  uint8_t speed;
};

#endif /* end of include guard: RAINBOW_H */
