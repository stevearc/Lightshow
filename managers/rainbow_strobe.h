#include "controllers/strobe.h"
#include "util/colorwheel.h"

#ifndef RAINBOW_STROBE_H
#define RAINBOW_STROBE_H

class RainbowStrobe : public LightManager {
public:
  RainbowStrobe(uint8_t fadeSpeed = 0, uint8_t colorDistance = 85,
      uint8_t maxColors = 3, uint16_t pixelColorOffset = 0,
      uint8_t startColor = 0)
  : pixelColorOffset(pixelColorOffset),
  fadeSpeed(fadeSpeed), colorDistance(colorDistance), maxColors(maxColors),
  wheelPos(startColor) { }

  virtual void setColor(Controller *controller, uint8_t n, uint32_t now) override {
      controller->setPixelColor(n, wheel(255 & (wheelPos + currentColorOffset + n * pixelColorOffset)));
  }
  virtual void step() override {
    currentColorOffset += colorDistance;
    if (maxColors > 0 and currentColorOffset / colorDistance >= maxColors) {
      currentColorOffset = 0;
    }
    if (currentColorOffset < colorDistance) {
      wheelPos += fadeSpeed;
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

