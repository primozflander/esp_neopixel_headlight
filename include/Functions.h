#pragma once
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

void showFlagColorsSeq(int wait)
{
    setColorSeq(firstFlagColor, wait);
    setColorSeq(secondFlagColor, wait);
    setColorSeq(thirdFlagColor, wait);
    delay(FLAG_DELAY);
}

void showFlagColorsFromLeftToRight(int wait)
{
    setColorFromLeftToRight(firstFlagColor, wait);
    setColorFromLeftToRight(secondFlagColor, wait);
    setColorFromLeftToRight(thirdFlagColor, wait);
    delay(FLAG_DELAY);
}

bool loadConfig()
{
    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile)
    {
        Serial.println("Failed to open config file");
        return false;
    }
    size_t size = configFile.size();
    if (size > 1024)
    {
        Serial.println("Config file size is too large");
        return false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonDocument<300> doc;
    auto error = deserializeJson(doc, buf.get());
    if (error)
    {
        Serial.println("Failed to parse config file");
        return false;
    }
    firstFlagColor = doc["firstFlagColor"];
    secondFlagColor = doc["secondFlagColor"];
    thirdFlagColor = doc["thirdFlagColor"];
    ledBrightness = doc["ledBrightness"];
    isLeftToRightAnimation = doc["isLeftToRightAnimation"];
    startupAnimationDelay = doc["startupAnimationDelay"];
    indicatorAnimationDelay = doc["indicatorAnimationDelay"];
    animationSeqDelay = doc["animationSeqDelay"];
    animationLeftToRightDelay = doc["animationLeftToRightDelay"];
    Serial.println("Loaded parameters: ");
    Serial.println(firstFlagColor);
    Serial.println(secondFlagColor);
    Serial.println(thirdFlagColor);
    Serial.println(ledBrightness);
    Serial.println(isLeftToRightAnimation);
    Serial.println(startupAnimationDelay);
    Serial.println(indicatorAnimationDelay);
    Serial.println(animationSeqDelay);
    Serial.println(animationLeftToRightDelay);
    return true;
}

void readConfigAndSetVariables()
{
    // !saveConfig() ? Serial.println("Failed to save config") : Serial.println("Config saved");
    !loadConfig() ? Serial.println("Failed to load config") : Serial.println("Config loaded");
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
    readConfigAndSetVariables();
    LedStrip.setBrightness(ledBrightness);
    LedStrip.begin();
    Serial.println("Setup complete");
}

bool saveConfig()
{
    StaticJsonDocument<300> doc;
    doc["firstFlagColor"] = firstFlagColor;
    doc["secondFlagColor"] = secondFlagColor;
    doc["thirdFlagColor"] = thirdFlagColor;
    doc["ledBrightness"] = ledBrightness;
    doc["isLeftToRightAnimation"] = false;
    doc["startupAnimationDelay"] = startupAnimationDelay;
    doc["indicatorAnimationDelay"] = indicatorAnimationDelay;
    doc["animationSeqDelay"] = animationSeqDelay;
    doc["animationLeftToRightDelay"] = animationLeftToRightDelay;
    File configFile = LittleFS.open("/config.json", "w");
    if (!configFile)
    {
        Serial.println("Failed to open config file for writing");
        return false;
    }
    serializeJson(doc, configFile);
    return true;
}

uint32_t convertColorNameToValue(String color)
{
    if (color == "white")
    {
        return white;
    }
    else if (color == "red")
    {
        return red;
    }
    else if (color == "blue")
    {
        return blue;
    }
    else if (color == "green")
    {
        return green;
    }
    else if (color == "cyan")
    {
        return cyan;
    }
    else if (color == "yellow")
    {
        return yellow;
    }
    else if (color == "magenta")
    {
        return magenta;
    }
    else if (color == "amber")
    {
        return amber;
    }
    else
    {
        return noColor;
    }
}
