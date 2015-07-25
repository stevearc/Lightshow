#include "controllers/strobe.h"

#ifndef BLING_H
#define BLING_H

const uint32_t BLING_RANDOM_RANGE = 10000;

class Bling : public StrobeController {
public:
  Bling(uint32_t baseColor, uint32_t blingColor = 0xFFFFFF, uint16_t onTime = 20, uint16_t offTime = 20, uint8_t blingsPerMinute = 120)
  : StrobeController(onTime, offTime), baseColor(baseColor), blingColor(blingColor), blingsPerMinute(blingsPerMinute) { }

  virtual void setup() override {
    uint32_t flashesPerMinute = numPixels();
    flashesPerMinute = flashesPerMinute * 60 * 1000 / (getOnTime() + getOffTime());
    threshold = BLING_RANDOM_RANGE * blingsPerMinute / flashesPerMinute;
  }

  virtual void strobeOn(uint32_t now) override {
    randomSeed(now);
    for (uint16_t i = 0; i < numPixels(); i++) {
      int32_t rand = random(BLING_RANDOM_RANGE);
      if (rand < threshold) {
        setPixelColor(i, blingColor);
      } else {
        setPixelColor(i, baseColor);
      }
    }
  }

private:
  uint32_t baseColor;
  uint32_t blingColor;
  uint8_t blingsPerMinute;
  uint32_t threshold;
};

#endif /* end of include guard: BLING_H */
