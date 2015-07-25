#include "dimmer.h"

#ifndef SLAM_H
#define SLAM_H

class Slam : public Dimmer {
public:
  Slam(uint8_t minBrightness = 0, uint8_t maxBrightness = 255, uint32_t bpm = 60,
      uint32_t transition = 200)
  : minBrightness(minBrightness), maxBrightness(maxBrightness) {
    // milliseconds per pulse
    period = 1000L * 60 / bpm;
    a = 2.0 * ((int16_t) minBrightness - (int16_t) maxBrightness) / (float) transition;
    b = minBrightness - a * period / 2L;
  }

  void step() {
    uint32_t x = millis() % (period);
    // Make x go from 0->period/2->0 instead of 0->period
    if (x > period / 2) {
      x = period - x;
    }
    brightness = min(maxBrightness, a * x + b);
  }

private:
  uint8_t minBrightness;
  uint8_t maxBrightness;
  uint32_t period;
  float a;
  float b;
};


#endif /* end of include guard: SLAM_H */
