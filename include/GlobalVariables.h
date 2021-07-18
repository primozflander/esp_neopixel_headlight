#pragma once
#include <Arduino.h>
#include <StateMachine.h>
#include <Adafruit_NeoPixel.h>
#include "Led.h"
#include "Button.h"
// #include "OTA.h"

#define LED_STRIP_PIN D1
#define IS_ALIVE_LED_PIN D4
#define LED_PIN D0
#define IGNITION_SWITCH_PIN D5
#define INDICATOR_SWITCH_PIN D6

#define STATE_DELAY 100
#define SEQ_DELAY 20
#define INDICATOR_SEQ_DELAY 20
#define LED_COUNT 64
#define BRIGHTNESS 50 // max = 255
#define ANIMATE_LEFTTORIGHT

#define WHITE LedStrip.Color(255, 255, 255)
#define AMBER LedStrip.Color(255, 191, 0)
#define RED LedStrip.Color(0, 255, 0)
#define GREEN LedStrip.Color(255, 0, 0)
#define BLUE LedStrip.Color(0, 0, 255)
#define NO_COLOR LedStrip.Color(0, 0, 0)

StateMachine states = StateMachine();
Adafruit_NeoPixel LedStrip(LED_COUNT, LED_STRIP_PIN, NEO_GRB);
Led isAliveLed(IS_ALIVE_LED_PIN);
Led onboardLed(LED_PIN, true);
Button ignitionSwitch(IGNITION_SWITCH_PIN);
Button indicatorSwitch(INDICATOR_SWITCH_PIN);

bool isLightOn = false;