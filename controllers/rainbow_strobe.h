#include "controllers/strobe.h"

#ifndef RAINBOW_STROBE_H
#define RAINBOW_STROBE_H

class RainbowStrobe : public StrobeController {
public:
  RainbowStrobe(uint16_t onTime = 20, uint16_t offTime = 20,
      uint8_t fadeSpeed = 0, uint8_t colorDistance = 85,
      uint8_t maxColors = 0, uint16_t pixelColorOffset = 0,
      uint8_t startColor = 0)
  : StrobeController(onTime, offTime), pixelColorOffset(pixelColorOffset),
  fadeSpeed(fadeSpeed), colorDistance(colorDistance), maxColors(maxColors),
  wheelPos(startColor) { }

  virtual void strobeOn(uint32_t now) override {
    for (uint16_t i = 0; i < numPixels(); i++) {
      setPixelColor(i, wheel(255 & (wheelPos + currentColorOffset + i * pixelColorOffset)));
    }
  }
  virtual void postStep(bool state) override {
    if (state) {
      currentColorOffset += colorDistance;
      if (maxColors > 0 and currentColorOffset / colorDistance >= maxColors) {
        currentColorOffset = 0;
      }
      if (currentColorOffset < colorDistance) {
        wheelPos += fadeSpeed;
      }
    }
  }

private:
  uint16_t pixelColorOffset;
  uint8_t colorDistance;
  uint8_t fadeSpeed;
  uint8_t wheelPos;
  uint8_t currentColorOffset;
  uint8_t maxColors;
};


#endif /* end of include guard: RAINBOW_STROBE_H */

