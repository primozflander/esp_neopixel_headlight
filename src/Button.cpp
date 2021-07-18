#include "Button.h"
Button::Button(uint8_t pin)
{
    this->pin = pin;
    lastReading = LOW;
    init();
}

void Button::init()
{
    pinMode(pin, INPUT_PULLUP);
    update();
}

void Button::update()
{
    int newReading = !digitalRead(pin);
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
