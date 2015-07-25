#include "controllers/strobe.h"

#ifndef BLINK_H
#define BLINK_H

class Blink : public StrobeController {
public:
  Blink(uint32_t color=0xFFFFFF, uint16_t onTime = 1000, uint16_t offTime = 1000)
  : StrobeController(onTime, offTime), color(color) { }

  virtual void strobeOn(uint32_t now) override {
    for (uint16_t i = 0; i < numPixels(); i++) {
      setPixelColor(i, color);
    }
  }

private:
  uint32_t color;
};

#endif /* end of include guard: BLINK_H */
