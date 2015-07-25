#include "controllers/strobe.h"

#ifndef BLINK_H
#define BLINK_H

class Blink : public LightManager {
public:
  Blink(uint32_t color=0xFFFFFF) : color(color) { }

  virtual void setColor(Controller *controller, uint8_t n, uint32_t now) override {
    controller->setPixelColor(n, color);
  }

private:
  uint32_t color;
};

#endif /* end of include guard: BLINK_H */
