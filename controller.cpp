#include "controller.h"

void Controller::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  setPixelColor(n, r, g, b, brightness);
}

void Controller::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t manualBrightness) {
  r = (r * manualBrightness) >> 8;
  g = (g * manualBrightness) >> 8;
  b = (b * manualBrightness) >> 8;
  pixels->setPixelColor(n, r, g, b);
}

void Controller::setPixelColor(uint16_t n, uint32_t c) {
  setPixelColor(n, c, brightness);
}

void Controller::setPixelColor(uint16_t n, uint32_t c, uint8_t manualBrightness) {
  uint8_t
    r = (uint8_t)(c >> 16),
      g = (uint8_t)(c >>  8),
      b = (uint8_t)c;
  setPixelColor(n, r, g, b, manualBrightness);
}
