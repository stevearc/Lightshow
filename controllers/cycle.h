#include "controller.h"
#include "button.h"

#ifndef CYCLE_H
#define CYCLE_H

class Cycle : public Controller {
public:
  Cycle(Controller *controllers[], uint8_t numControllers, uint32_t transitionTime = 10000, int8_t nextPin = -1)
  : controllers(controllers), numControllers(numControllers), transitionTime(transitionTime) {
    if (nextPin >= 0) {
      nextBtn = new Button(nextPin);
    }
  }

  ~Cycle() {
    if (nextBtn) {
      delete nextBtn;
      nextBtn = 0;
    }
  }

  virtual void setup() override {
    for (uint8_t i=0; i < numControllers; i++) {
      controllers[i]->begin(pixels);
    }
    if (nextBtn) {
      nextBtn->setup();
    }
    if (transitionTime > 0) {
      next();
      index = 0;
    }
  }

  void next() {
    index = (index + 1) % numControllers;
    nextStep = millis() + transitionTime;
  }

  virtual void innerStep() override {
    controllers[index]->setBrightness(getBrightness());
    controllers[index]->step();
    if (nextBtn) {
      nextBtn->step();
      if (nextBtn->wasPressed()) {
        next();
        return;
      }
    }
    if (millis() >= nextStep && transitionTime > 0) {
      next();
    }
  }

private:
  Controller **controllers;
  uint8_t numControllers;
  uint32_t transitionTime;
  Button *nextBtn;
  uint32_t nextStep;
  uint8_t index;
};

#endif /* end of include guard: CYCLE_H */
