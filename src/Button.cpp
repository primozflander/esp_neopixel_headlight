#include "Button.h"
Button::Button(uint8_t pin, unsigned long debounceDelay)
{
    this->pin = pin;
    this->debounceDelay = debounceDelay;
    lastReading = LOW;
    init();
}

void Button::init()
{
    pinMode(pin, INPUT);
    update();
}

void Button::update()
{
    int newReading = digitalRead(pin);
    if (newReading != lastReading)
    {
        lastDebounceTime = millis();
    }
    if (millis() - lastDebounceTime > debounceDelay)
    {
        state = newReading;
    }
    lastReading = newReading;
}

int Button::getState()
{
    update();
    return state;
}

bool Button::isPressed()
{
    return (getState() == HIGH);
}
