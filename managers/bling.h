#include "controllers/strobe.h"

#ifndef BLING_H
#define BLING_H

const uint32_t BLING_RANDOM_RANGE = 10000;

class Bling : public LightManager {
public:
  Bling(uint32_t baseColor = 0xFF0000, uint32_t blingColor = 0xFFFFFF, uint8_t blingsPerMinute = 30)
  : baseColor(baseColor), blingColor(blingColor), blingsPerMinute(blingsPerMinute) { }

  virtual void setup(StrobeController *controller) override {
    if (threshold > 0) {
      return;
    }
    uint32_t flashesPerMinute = 60 * 1000 / (controller->getOnTime() + controller->getOffTime());
    threshold = BLING_RANDOM_RANGE * blingsPerMinute / flashesPerMinute;
  }

  virtual void setColor(Controller *controller, uint8_t n, uint32_t now) override {
    randomSeed(now);
    for (uint8_t i = 0; i < n; ++i) {
      random();
    }
    int32_t rand = random(BLING_RANDOM_RANGE);
    if (rand < threshold) {
      controller->setPixelColor(n, blingColor);
    } else {
      controller->setPixelColor(n, baseColor);
    }
  }

private:
  uint32_t baseColor;
  uint32_t blingColor;
  uint8_t blingsPerMinute;
  uint32_t threshold;
};

#endif /* end of include guard: BLING_H */
