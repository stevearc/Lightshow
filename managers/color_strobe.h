#include "controllers/strobe.h"

#ifndef COLOR_STROBE_H
#define COLOR_STROBE_H

class ColorStrobe : public LightManager {
public:
  ColorStrobe(uint32_t origColors[], uint8_t numColors)
  : numColors(numColors) {
    colors = new uint32_t[numColors];
    memcpy(colors, origColors, numColors*sizeof(uint32_t));
  }

  virtual ~ColorStrobe() {
    delete[] colors;
  }

  virtual void setColor(Controller *controller, uint8_t n, uint32_t now) override {
    controller->setPixelColor(n, colors[pos]);
  }

  virtual void step() override {
    pos = (pos + 1) % numColors;
  }

private:
  uint32_t *colors;
  uint8_t numColors;
  uint8_t pos;
};
#endif /* end of include guard: COLOR_STROBE_H */
