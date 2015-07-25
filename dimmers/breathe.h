#include "dimmer.h"

#ifndef BREATHE_H
#define BREATHE_H

class Breathe : public Dimmer {
public:

  Breathe(uint8_t minBrightness = 0, uint8_t maxBrightness = 255, float speed = 1)
  : minBrightness(minBrightness), speed(speed) {
    amplitude = (maxBrightness - minBrightness)/2;
  }

  void step() {
    float seconds = millis() / 1000.0;
    brightness = minBrightness + (1 + sin(PI * speed * seconds)) * amplitude;
  }

private:
  uint8_t minBrightness;
  float speed;
  uint8_t amplitude;
};

#endif /* end of include guard: BREATHE_H */
