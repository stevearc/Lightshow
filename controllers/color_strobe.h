#include "controllers/strobe.h"

#ifndef COLOR_STROBE_H
#define COLOR_STROBE_H

class ColorStrobe : public StrobeController {
public:
  ColorStrobe(uint32_t origColors[], uint8_t numColors, uint16_t onTime = 20, uint16_t offTime = 20)
  : StrobeController(onTime, offTime), numColors(numColors) {
    colors = new uint32_t[numColors];
    memcpy(colors, origColors, numColors*sizeof(uint32_t));
  }

  virtual ~ColorStrobe() {
    delete[] colors;
  }

  virtual void strobeOn(uint32_t now) override {
    for (uint16_t i = 0; i < numPixels(); i++) {
      setPixelColor(i, colors[pos]);
    }
  }
  virtual void postStep(bool state) override {
    if (state) {
      pos = (pos + 1) % numColors;
    }
  }

private:
  uint32_t *colors;
  uint8_t numColors;
  uint8_t pos;
};
#endif /* end of include guard: COLOR_STROBE_H */
