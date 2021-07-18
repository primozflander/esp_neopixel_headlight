#include <Arduino.h>
#include <StateMachine.h>
#include <Adafruit_NeoPixel.h>
#include "Led.h"
#include "Button.h"
// #include "OTA.h"

#define LED_STRIP_PIN D1
#define IS_ALIVE_LED_PIN D4
#define LED_PIN D0
#define HEADLIGHTS_SWITCH_PIN D5
#define INDICATOR_SWITCH_PIN D6

#define STATE_DELAY 100
#define SEQ_DELAY 20
#define LED_COUNT 64
#define BRIGHTNESS 50 // max = 255
#define ANIMATE_LEFTTORIGHT

#define WHITE LedStrip.Color(255, 255, 255)
#define AMBER LedStrip.Color(255, 191, 0)
#define RED LedStrip.Color(0, 255, 0)
#define GREEN LedStrip.Color(255, 0, 0)
#define BLUE LedStrip.Color(0, 0, 255)
#define NO_COLOR LedStrip.Color(0, 0, 0)

// bool isAliveLedState = false;

StateMachine states = StateMachine();
Adafruit_NeoPixel LedStrip(LED_COUNT, LED_STRIP_PIN, NEO_GRB);
Led isAliveLed(IS_ALIVE_LED_PIN);
Led onboardLed(LED_PIN, true);

bool areLightsOn = false;

void setColorFromLeftToRightSingleRing(uint32_t color, int wait, int numLeds, int offset = 0)
{
    if (numLeds % 2 == 1)
    {
        Serial.println("Error, numLeds must be even!");
        return;
    }
    for (int i = 0; i < numLeds / 2; i++)
    {
        LedStrip.setPixelColor(i + offset, color);
        LedStrip.setPixelColor(numLeds - 1 - i + offset, color);
        LedStrip.show();
        delay(wait);
        Serial.println(String(i + offset) + " " + String(numLeds - 1 - i + offset));
    }
}

void setColorFromLeftToRight(uint32_t color, int wait)
{
    setColorFromLeftToRightSingleRing(color, wait, 16, 0);
    setColorFromLeftToRightSingleRing(color, wait, 16, 16);
    setColorFromLeftToRightSingleRing(color, wait, 16, 32);
    setColorFromLeftToRightSingleRing(color, wait, 16, 48);
}

void setColorSeq(uint32_t color, int wait)
{
    for (int i = 0; i < LedStrip.numPixels(); i++)
    {
        LedStrip.setPixelColor(i, color);
        LedStrip.show();
        delay(wait);
    }
}

void setColor(uint32_t color)
{
    for (int i = 0; i < LedStrip.numPixels(); i++)
    {
        LedStrip.setPixelColor(i, color);
    }
    LedStrip.show();
}

void showItalianFlagColorsSeq()
{
    setColorSeq(RED, SEQ_DELAY);
    setColorSeq(WHITE, SEQ_DELAY);
    setColorSeq(GREEN, SEQ_DELAY);
}

void showItalianFlagColorsFromLeftToRight()
{
    setColorFromLeftToRight(RED, SEQ_DELAY);
    setColorFromLeftToRight(WHITE, SEQ_DELAY);
    setColorFromLeftToRight(GREEN, SEQ_DELAY);
}

// void blinkIfALive()
// {
//     digitalWrite(IS_ALIVE_LED_PIN, isAliveLedState);
//     isAliveLedState = !isAliveLedState;
// }

void state0()
{
    if (states.executeOnce)
    {
        Serial.println("State0, Lights Off");
        #ifdef ANIMATE_LEFTTORIGHT
        setColorFromLeftToRight(NO_COLOR, SEQ_DELAY);
        #else
        setColorSeq(NO_COLOR, SEQ_DELAY);
        #endif
        onboardLed.off();
        areLightsOn = false;
    }
    Serial.print(".");
}

bool transitionS0S1()
{
    if (digitalRead(HEADLIGHTS_SWITCH_PIN) == LOW)
    {
        Serial.println("Ignition on");
        return true;
    }
    return false;
}


bool transitionS0S3()
{
    if (digitalRead(INDICATOR_SWITCH_PIN) == LOW)
    {
        Serial.println("Indicator on");
        return true;
    }
    return false;
}

void state1()
{
    if (states.executeOnce)
    {
        Serial.println("State1, welcome sequence");
        #ifdef ANIMATE_LEFTTORIGHT
        showItalianFlagColorsFromLeftToRight();
        #else
        showItalianFlagColorsSeq();
        #endif
    }
    Serial.print(".");
}

bool transitionS1S2()
{
    Serial.println("Transition S1S2");
    return true;
}

void state2()
{
    if (states.executeOnce)
    {
        Serial.println("State2, lights on");
        #ifdef ANIMATE_LEFTTORIGHT
        setColorFromLeftToRight(WHITE, SEQ_DELAY);
        #else
        setColorSeq(WHITE, SEQ_DELAY);
        #endif
        onboardLed.on();
        areLightsOn = true;
    }
    Serial.print(".");
}

bool transitionS2S3()
{
    if (digitalRead(INDICATOR_SWITCH_PIN) == LOW)
    {
        Serial.println("Indicator on");
        return true;
    }
    return false;
}

bool transitionS2S4()
{
    if (digitalRead(HEADLIGHTS_SWITCH_PIN) == HIGH)
    {
        Serial.println("Ignition off");
        return true;
    }
    return false;
}

void state3()
{
    if (states.executeOnce)
    {
        Serial.println("State 3, indicator on");
    }
    Serial.println("amber");
    #ifdef ANIMATE_LEFTTORIGHT
    setColorFromLeftToRight(AMBER, SEQ_DELAY);
    setColorFromLeftToRight(NO_COLOR, SEQ_DELAY);
    #else
    setColorSeq(NO_COLOR, SEQ_DELAY);
    setColorSeq(AMBER, SEQ_DELAY);
    #endif
    Serial.println("no color");
}

bool transitionS3S2()
{
    if (digitalRead(INDICATOR_SWITCH_PIN) == HIGH && areLightsOn)
    {
        Serial.println("Indicator off");
        return true;
    }
    return false;
}

bool transitionS3S4()
{
    if (digitalRead(HEADLIGHTS_SWITCH_PIN) == HIGH && areLightsOn)
    {
        Serial.println("Ignition off");
        return true;
    }
    return false;
}

bool transitionS3S0()
{
    if (digitalRead(INDICATOR_SWITCH_PIN) == HIGH)
    {
        Serial.println("Indicator off");
        return true;
    }
    return false;
}

void state4()
{
    if (states.executeOnce)
    {
        Serial.println("State4, goodbye sequence");
        #ifdef ANIMATE_LEFTTORIGHT
        showItalianFlagColorsFromLeftToRight();
        #else
        showItalianFlagColorsSeq();
        #endif
    }
}

bool transitionS4S0()
{
    Serial.println("Transition S4S0");
    return true;
}

State *S0 = states.addState(&state0);
State *S1 = states.addState(&state1);
State *S2 = states.addState(&state2);
State *S3 = states.addState(&state3);
State *S4 = states.addState(&state4);

void setup()
{
    Serial.begin(9600);

    // pinMode(IS_ALIVE_LED_PIN, OUTPUT);
    // pinMode(LED_PIN, OUTPUT);
    pinMode(HEADLIGHTS_SWITCH_PIN, INPUT_PULLUP);
    pinMode(INDICATOR_SWITCH_PIN, INPUT_PULLUP);

    S0->addTransition(&transitionS0S1, S1);
    S0->addTransition(&transitionS0S3, S3);
    S1->addTransition(&transitionS1S2, S2);
    S2->addTransition(&transitionS2S3, S3);
    S2->addTransition(&transitionS2S4, S4);
    S3->addTransition(&transitionS3S2, S2);
    S3->addTransition(&transitionS3S0, S0);
    S3->addTransition(&transitionS3S4, S4);
    S4->addTransition(&transitionS4S0, S0);

    LedStrip.begin();
    LedStrip.setBrightness(BRIGHTNESS);
    // strip.show();
    // strip.clear();
    // setColor(NO_COLOR);
    Serial.println("Setup complete");
    // setupOTA();
}

void loop()
{
    // ArduinoOTA.handle();
    states.run();
    delay(STATE_DELAY);
    isAliveLed.blinkMs(500);
}
