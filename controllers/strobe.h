#include "controller.h"

#ifndef STROBE_H
#define STROBE_H

#define REFRESH_TIME 5

class StrobeController : public Controller {
public:
  StrobeController(uint16_t onTime = 20, uint16_t offTime = 20)
  : onTime(onTime), offTime(offTime) { }

  virtual void strobeOn(uint32_t now) {
    for (uint16_t i = 0; i < numPixels(); i++) {
      setPixelColor(i, 0xFFFFFF);
    }
  }

  virtual void strobeOff(uint32_t now) {
    for (uint16_t i = 0; i < numPixels(); ++i) {
      setPixelColor(i, 0);
    }
  }

  virtual void postStep(bool state) { }

  virtual void innerStep() override {
    uint32_t now = millis();
    if (now < nextStep) {
      if (state and now >= nextRefresh) {
        strobeOn(lastStep);
        nextRefresh = now + REFRESH_TIME;
      }
      return;
    }
    lastStep = now;
    if (state and offTime > 0) {
      strobeOff(lastStep);
      state = false;
      nextStep = now + offTime;
    } else {
      strobeOn(lastStep);
      state = true;
      nextStep = now + onTime;
    }
    nextRefresh = now + REFRESH_TIME;
    postStep(state);
  }

  virtual uint16_t getOnTime() const {
    return onTime;
  }
  virtual uint16_t getOffTime() const {
    return offTime;
  }
  virtual bool getState() const {
    return state;
  }

private:
  uint16_t onTime;
  uint16_t offTime;
  uint32_t lastStep;
  uint32_t nextStep;
  uint32_t nextRefresh;
  bool state;
};

#endif /* end of include guard: STROBE_H */
