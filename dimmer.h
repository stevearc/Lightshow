#ifndef DIMMER_H
#define DIMMER_H

class Dimmer {
public:
  virtual void step() = 0;
  virtual uint8_t getBrightness() {
    return brightness;
  }

protected:
  uint8_t brightness;
};

#endif /* end of include guard: DIMMER_H */
