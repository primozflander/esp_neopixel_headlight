#pragma once
#include <Arduino.h>
#include <StateMachine.h>
#include <Adafruit_NeoPixel.h>
#include "Led.h"
#include "Button.h"

#define LED_STRIP_PIN D1
#define IS_ALIVE_LED_PIN D4
#define LED_PIN D0
#define IGNITION_SWITCH_PIN D5
#define INDICATOR_SWITCH_PIN D6
#define POWER_HOLD_PIN D3

#define STATE_DELAY 100
#define INDICATOR_TURN_OFF_COUNTER 0
#define LED_COUNT 4
#define FLAG_DELAY 100

StateMachine states = StateMachine();
Adafruit_NeoPixel LedStrip(LED_COUNT, LED_STRIP_PIN, NEO_GRB);
Led isAliveLed(IS_ALIVE_LED_PIN);
Led onboardLed(LED_PIN, true);
Button ignitionSwitch(IGNITION_SWITCH_PIN);
Button indicatorSwitch(INDICATOR_SWITCH_PIN);

uint8_t espReceiverAddresses[][6] = {
  {0xB4, 0xE6, 0x2D, 0x17, 0xEC, 0x67},
  {0x84, 0xF3, 0xEB, 0x0A, 0x48, 0x14}
};

typedef struct struct_settings
{
  uint32_t firstFlagColor;
  uint32_t secondFlagColor;
  uint32_t thirdFlagColor;
  int ledBrightness;
  bool isMainLightEnabled;
} struct_settings;
struct_settings settingsToSync;

bool isLightOn = false;
unsigned long indicatorOffCounter = 0;
const char *SSID = "NeoPixel_Headlights_AP";
const char *PASSWORD = "Esp32!_x";
bool isLeftToRightAnimation = true;
bool isMainLightEnabled = true;
unsigned int ledBrightness = 64;
unsigned int startupAnimationDelay = 20;
unsigned int indicatorAnimationDelay = 15;
unsigned int animationSeqDelay = 10;
unsigned int animationLeftToRightDelay = 20;

uint32_t white = LedStrip.Color(255, 255, 255);
uint32_t red = LedStrip.Color(0, 255, 0);
uint32_t blue = LedStrip.Color(0, 0, 255);
uint32_t green = LedStrip.Color(255, 0, 0);
uint32_t cyan = LedStrip.Color(255, 0, 255);
uint32_t yellow = LedStrip.Color(255, 255, 0);
uint32_t magenta = LedStrip.Color(0, 255, 255);
uint32_t amber = LedStrip.Color(255, 191, 0);
uint32_t noColor = LedStrip.Color(0, 0, 0);
uint32_t firstFlagColor = red;
uint32_t secondFlagColor = white;
uint32_t thirdFlagColor = green;
