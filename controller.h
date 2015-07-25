#include <Adafruit_NeoPixel.h>
#include "dimmer.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
public:
  Controller()
    : brightness(255) { }
  virtual ~Controller() {
    if (ownsPixels) {
      delete pixels;
    }
    pixels = 0;
  }
  Controller(const Controller& that) = delete;
  void begin(uint16_t n, uint8_t p, uint8_t t=NEO_GRB + NEO_KHZ800) {
    pixels = new Adafruit_NeoPixel(n, p, t);
    ownsPixels = true;
    pixels->begin();
    setup();
  }
  void begin(Adafruit_NeoPixel *_pixels) {
    pixels = _pixels;
    setup();
  }
  void setDimmer(Dimmer *newDimmer) {
    dimmer = newDimmer;
  }
  virtual void setup() { };
  void step() {
    if (dimmer) {
      dimmer->step();
      setBrightness(dimmer->getBrightness());
    }
    innerStep();
  };
  virtual void innerStep() = 0;

  void setBrightness(uint8_t newBrightness) {
    brightness = newBrightness;
  }
  uint8_t getBrightness() const {
    return brightness;
  }
  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t manualBrightness);
  void setPixelColor(uint16_t n, uint32_t c);
  void setPixelColor(uint16_t n, uint32_t c, uint8_t manualBrightness);
  uint16_t numPixels() const {
    return pixels->numPixels();
  };
  void show() const {
    pixels->show();
  }

protected:
  Adafruit_NeoPixel *pixels;

private:
  Dimmer *dimmer;
  uint8_t brightness;
  bool ownsPixels;
};

#endif /* end of include guard: CONTROLLER_H */
