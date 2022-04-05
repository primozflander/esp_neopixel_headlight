#pragma once
#include <Arduino.h>
#include <StateMachine.h>
#include <Adafruit_NeoPixel.h>
#include "Led.h"
#include "Button.h"

#define LED_STRIP_RIGHT_PIN D1
#define LED_STRIP_LEFT_PIN D2
#define IS_ALIVE_LED_PIN D4
#define LED_PIN D0
#define IGNITION_SWITCH_PIN D5
#define INDICATOR_SWITCH_RIGHT_PIN D6
#define INDICATOR_SWITCH_LEFT_PIN D7
#define POWER_HOLD_PIN D3
#define STATE_DELAY 100
#define INDICATOR_TURN_OFF_COUNTER 0
#define LED_COUNT 4
#define FLAG_DELAY 100

StateMachine states = StateMachine();
Adafruit_NeoPixel rightStrip(LED_COUNT, LED_STRIP_RIGHT_PIN, NEO_GRB);
Adafruit_NeoPixel leftStrip(LED_COUNT, LED_STRIP_LEFT_PIN, NEO_GRB);
Led isAliveLed(IS_ALIVE_LED_PIN);
Led onboardLed(LED_PIN, true);
Button ignitionSwitch(IGNITION_SWITCH_PIN);
Button indicatorSwitchRight(INDICATOR_SWITCH_RIGHT_PIN);
Button indicatorSwitchLeft(INDICATOR_SWITCH_LEFT_PIN);

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
  bool isLeftToRightAnimation;
  unsigned int startupAnimationDelay;
  unsigned int indicatorAnimationDelay;
  unsigned int animationSeqDelay;
  unsigned int animationLeftToRightDelay;
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

uint32_t white = rightStrip.Color(255, 255, 255);
uint32_t red = rightStrip.Color(0, 255, 0);
uint32_t blue = rightStrip.Color(0, 0, 255);
uint32_t green = rightStrip.Color(255, 0, 0);
uint32_t cyan = rightStrip.Color(255, 0, 255);
uint32_t yellow = rightStrip.Color(255, 255, 0);
uint32_t magenta = rightStrip.Color(0, 255, 255);
uint32_t amber = rightStrip.Color(255, 191, 0);
uint32_t noColor = rightStrip.Color(0, 0, 0);
uint32_t firstFlagColor = red;
uint32_t secondFlagColor = white;
uint32_t thirdFlagColor = green;
