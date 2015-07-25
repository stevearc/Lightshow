#include "controller.h"

#ifndef STROBE_H
#define STROBE_H

#define REFRESH_TIME 5

class StrobeController;

class LightManager {
public:
  virtual void setup(StrobeController *controller) { };
  virtual void setColor(Controller *controller, uint8_t n, uint32_t now) = 0;
  virtual void step() { };
};

class StrobeController : public Controller {
public:
  StrobeController(uint16_t onTime = 20, uint16_t offTime = 20)
  : onTime(onTime), offTime(offTime) { }

  ~StrobeController() {
    delete[] managers;
    managers = 0;
  }

  virtual void setup() override {
    managers = new LightManager*[numPixels()];
  };
  void setManager(uint8_t n, LightManager *manager) {
    managers[n] = manager;
    manager->setup(this);
  }
  void setManagerAll(LightManager *manager) {
    for (uint8_t i = 0; i < numPixels(); ++i) {
      setManager(i, manager);
    }
  }
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
      stepManagers();
    }
    nextRefresh = now + REFRESH_TIME;
  }

  uint16_t getOnTime() const {
    return onTime;
  }
  uint16_t getOffTime() const {
    return offTime;
  }
  bool getState() const {
    return state;
  }

private:
  LightManager **managers;
  uint16_t onTime;
  uint16_t offTime;
  uint32_t lastStep;
  uint32_t nextStep;
  uint32_t nextRefresh;
  bool state;

  void stepManagers() {
    for (uint8_t i = 0; i < numPixels(); ++i) {
      LightManager *m = managers[i];
      bool alreadyStepped = false;
      for (uint8_t j = 0; j < i; ++j) {
        if (m == managers[j]) {
          alreadyStepped = true;
          break;
        }
      }
      if (!alreadyStepped && m) {
        m->step();
      }
    }
  }

  void strobeOn(uint32_t now) {
    for (uint16_t i = 0; i < numPixels(); i++) {
      if (managers[i]) {
        managers[i]->setColor(this, i, now);
      }
    }
  }

  void strobeOff(uint32_t now) {
    for (uint16_t i = 0; i < numPixels(); ++i) {
      setPixelColor(i, 0);
    }
  }

};

#endif /* end of include guard: STROBE_H */
