#pragma once
#include <Arduino.h>
class Button {
  private:
    uint8_t pin;
    int state;
    int lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 100;
  public:
    Button(uint8_t pin, unsigned long debounceDelay = 100);
    void init();
    void update();
    int getState();
    bool isPressed();
};