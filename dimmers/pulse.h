#include "dimmer.h"

#ifndef PULSE_H
#define PULSE_H

class Pulse : public Dimmer {
public:

  Pulse(uint8_t minBrightness = 0, uint8_t maxBrightness = 255, uint32_t bpm = 120)
  : minBrightness(minBrightness), maxBrightness(maxBrightness) {
    // milliseconds per pulse
    period = 1000L * 60 / bpm;
  }

  void step() {
    // modifier will range from 0-2
    float modifier = 2 * (millis() % (period + 1)) / (float) period;
    // Make the modifier go from 0->1->0 instead of 0->2
    if (modifier > 1) {
      modifier = 2 - modifier;
    }
    brightness = minBrightness + modifier * (maxBrightness - minBrightness);
  }

private:
  uint8_t minBrightness;
  uint8_t maxBrightness;
  uint32_t period;
};


#endif /* end of include guard: PULSE_H */
