#ifndef UTIL_H
#define UTIL_H

// TODO: long vs short press

class Button {
public:
  Button(uint8_t pin, uint16_t delay = 20, bool invert = false) : pin(pin), delay(delay), invert(invert) { }

  void setup() const {
    pinMode(pin, INPUT);
  }

  void step() {
    uint32_t now = millis();
    if (lastChange + delay > now) {
      return;
    }
    bool newState = digitalRead(pin);
    if (newState != state) {
      state = newState;
      // state XOR invert
      if (state != invert) {
        lastChange = now;
        pressed = true;
      }
    }
  }

  bool wasPressed() {
    if (pressed) {
      pressed = false;
      return true;
    }
    return false;
  }

private:
  uint8_t pin;
  bool state;
  bool pressed;
  bool invert;
  uint16_t delay;
  uint32_t lastChange;
};


#endif /* end of include guard: UTIL_H */

