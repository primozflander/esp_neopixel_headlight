#pragma once
// #include "GlobalVariables.h"
#include "States.h"
#include <ArduinoJson.h>
#include "FS.h"
#include <LittleFS.h>

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
        // Serial.println(String(i + offset) + " " + String(numLeds - 1 - i + offset));
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

void showFlagColorsSeq()
{
    setColorSeq(RED, SEQ_DELAY);
    setColorSeq(WHITE, SEQ_DELAY);
    setColorSeq(GREEN, SEQ_DELAY);
}

void showFlagColorsFromLeftToRight()
{
    setColorFromLeftToRight(RED, SEQ_DELAY);
    setColorFromLeftToRight(WHITE, SEQ_DELAY);
    setColorFromLeftToRight(GREEN, SEQ_DELAY);
}

void initIO()
{
    pinMode(POWER_HOLD_PIN, OUTPUT);
    digitalWrite(POWER_HOLD_PIN, HIGH);
    Serial.begin(9600);
    if (!LittleFS.begin())
    {
        Serial.println("Failed to mount file system");
    }
    LedStrip.begin();
    LedStrip.setBrightness(BRIGHTNESS);
    Serial.println("Setup complete");
}

bool loadConfig() {
  File configFile = LittleFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  StaticJsonDocument<200> doc;
  auto error = deserializeJson(doc, buf.get());
  if (error) {
    Serial.println("Failed to parse config file");
    return false;
  }

  const char* serverName = doc["serverName"];
  const char* accessToken = doc["accessToken"];

  // Real world application would store these values in some variables for
  // later use.

  Serial.print("Loaded serverName: ");
  Serial.println(serverName);
  Serial.print("Loaded accessToken: ");
  Serial.println(accessToken);
  return true;
}

bool saveConfig() {
  StaticJsonDocument<200> doc;
  doc["serverName"] = "api.example.com";
  doc["accessToken"] = "128du9as8du12eoue8da98h123ueh9h98";

  File configFile = LittleFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  serializeJson(doc, configFile);
  return true;
}

void readConfigAndSetVariables()
{
    // if (!saveConfig())
    // {
    //     Serial.println("Failed to save config");
    // }
    // else
    // {
    //     Serial.println("Config saved");
    // }

    if (!loadConfig())
    {
        Serial.println("Failed to load config");
    }
}
