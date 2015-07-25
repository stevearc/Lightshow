#include "controllers/strobe.h"
#include "util/colorwheel.h"

#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow : public LightManager {
public:
  Rainbow(uint8_t speed = 1, uint16_t pixelColorOffset = 0)
  : speed(speed), pixelColorOffset(pixelColorOffset) { }

  virtual void setColor(Controller *controller, uint8_t n, uint32_t now) override {
    controller->setPixelColor(n, wheel(255 & (wheelPos + n * pixelColorOffset)));
  }
  virtual void step() override {
    wheelPos = (wheelPos + speed) & 255;
  }

private:
  uint16_t pixelColorOffset;
  uint8_t wheelPos;
  uint8_t speed;
};

#endif /* end of include guard: RAINBOW_H */
