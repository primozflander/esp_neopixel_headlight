#pragma once
#include "States.h"
#include <ArduinoJson.h>
#include "FS.h"
#include <LittleFS.h>

void showMode(int stepDelay = 26)
{
    static unsigned int effStep = 0;
    float factor1, factor2;
    uint16_t ind;
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
        ind = effStep + i * 0.9;
        switch ((int)((ind % 189) / 63))
        {
        case 0:
            factor1 = 1.0 - ((float)(ind % 189 - 0 * 63) / 63);
            factor2 = (float)((int)(ind - 0) % 189) / 63;
            rightStrip.setPixelColor(i, 255 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2);
            leftStrip.setPixelColor(i, 255 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2);
            break;
        case 1:
            factor1 = 1.0 - ((float)(ind % 189 - 1 * 63) / 63);
            factor2 = (float)((int)(ind - 63) % 189) / 63;
            rightStrip.setPixelColor(i, 255 * factor1 + 0 * factor2, 255 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2);
            leftStrip.setPixelColor(i, 255 * factor1 + 0 * factor2, 255 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2);
            break;
        case 2:
            factor1 = 1.0 - ((float)(ind % 189 - 2 * 63) / 63);
            factor2 = (float)((int)(ind - 126) % 189) / 63;
            rightStrip.setPixelColor(i, 0 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 0 * factor2);
            leftStrip.setPixelColor(i, 0 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 0 * factor2);
            break;
        }
    }
    effStep++;
    delay(stepDelay);
    rightStrip.show();
    leftStrip.show();
}

void setColorFromLeftToRightSingleRing(bool side, uint32_t color, int wait, int numLeds, int offset = 0, int numLedsSimultaneously = NUMLEDSEQ)
{
    if (numLeds % 2 == 1)
    {
        Serial.println("Error, numLeds must be even!");
        return;
    }
    if (side == 0)
    {
        for (int i = 0; i < numLeds / 2; i += numLedsSimultaneously)
        {
            for (int j = 0; j < numLedsSimultaneously; j++)
            {
                rightStrip.setPixelColor(i + j + offset, color);
                rightStrip.setPixelColor(numLeds - 1 - i - j + offset, color);
            }
            rightStrip.show();
            delay(wait);
        }
    }
    else
    {
        for (int i = 0; i < numLeds / 2; i += numLedsSimultaneously)
        {
            for (int j = 0; j < numLedsSimultaneously; j++)
            {
                leftStrip.setPixelColor(i + j + offset, color);
                leftStrip.setPixelColor(numLeds - 1 - i - j + offset, color);
            }
            leftStrip.show();
            delay(wait);
        }
    }
}

void setColorFromLeftToRightSingleRing(uint32_t color, int wait, int numLeds, int offset = 0, int numLedsSimultaneously = NUMLEDSEQ)
{
    if (numLeds % 2 == 1)
    {
        Serial.println("Error, numLeds must be even!");
        return;
    }
    for (int i = 0; i < numLeds / 2; i += numLedsSimultaneously)
    {
        for (int j = 0; j < numLedsSimultaneously; j++)
        {
            rightStrip.setPixelColor(i + j + offset, color);
            rightStrip.setPixelColor(numLeds - 1 - i - j + offset, color);
            leftStrip.setPixelColor(i + j + offset, color);
            leftStrip.setPixelColor(numLeds - 1 - i - j + offset, color);
        }
        rightStrip.show();
        leftStrip.show();
        delay(wait);
    }
}

void setColorFromLeftToRight(bool side, uint32_t color, int wait)
{
    // setColorFromLeftToRightSingleRing(side, color, wait, 16, 0);
    // setColorFromLeftToRightSingleRing(side, color, wait, 16, 16);
    // setColorFromLeftToRightSingleRing(side, color, wait, 16, 32);
    // setColorFromLeftToRightSingleRing(side, color, wait, 16, 48);

    setColorFromLeftToRightSingleRing(side, color, wait, 210, 0);
}

void setColorFromLeftToRight(uint32_t color, int wait)
{
    // setColorFromLeftToRightSingleRing(color, wait, 16, 0);
    // setColorFromLeftToRightSingleRing(color, wait, 16, 16);
    // setColorFromLeftToRightSingleRing(color, wait, 16, 32);
    // setColorFromLeftToRightSingleRing(color, wait, 16, 48);

    setColorFromLeftToRightSingleRing(color, wait, 210, 0);
}

void setColorSeq(bool side, uint32_t color, int wait, int numLedsSimultaneously = NUMLEDSEQ)
{
    if (side == 0)
    {
        for (int i = 0; i < rightStrip.numPixels(); i += numLedsSimultaneously)
        {
            for (int j = 0; j < numLedsSimultaneously; j++)
            {
                rightStrip.setPixelColor(i + j, color);
            }
            rightStrip.show();
            delay(wait);
        }
    }
    else
    {
        for (int i = 0; i < leftStrip.numPixels(); i += numLedsSimultaneously)
        {
            for (int j = 0; j < numLedsSimultaneously; j++)
            {
                leftStrip.setPixelColor(i + j, color);
            }
            leftStrip.show();
            delay(wait);
        }
    }
}

void setColorSeq(uint32_t color, int wait, int numLedsSimultaneously = NUMLEDSEQ)
{
    for (int i = 0; i < rightStrip.numPixels(); i += numLedsSimultaneously)
    {
        for (int j = 0; j < numLedsSimultaneously; j++)
        {
            rightStrip.setPixelColor(i + j, color);
            leftStrip.setPixelColor(i + j, color);
        }
        rightStrip.show();
        leftStrip.show();
        delay(wait);
    }
}

void showFlagColorsSeq(int wait)
{
    setColorSeq(firstFlagColor, wait);
    setColorSeq(secondFlagColor, wait);
    setColorSeq(thirdFlagColor, wait);
    setColorSeq(noColor, wait);
    delay(FLAG_DELAY);
}

void showFlagColorsFromLeftToRight(int wait)
{
    setColorFromLeftToRight(firstFlagColor, wait);
    setColorFromLeftToRight(secondFlagColor, wait);
    setColorFromLeftToRight(thirdFlagColor, wait);
    setColorFromLeftToRight(noColor, wait);
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
    mainLightMode = doc["mainLightMode"];
    isLeftToRightAnimation = doc["isLeftToRightAnimation"];
    startupAnimationDelay = doc["startupAnimationDelay"];
    indicatorAnimationDelay = doc["indicatorAnimationDelay"];
    animationSeqDelay = doc["animationSeqDelay"];
    animationLeftToRightDelay = doc["animationLeftToRightDelay"];
    // Serial.println("Loaded parameters: ");
    // Serial.println(firstFlagColor);
    // Serial.println(secondFlagColor);
    // Serial.println(thirdFlagColor);
    // Serial.println(ledBrightness);
    // Serial.println(mainLightMode);
    // Serial.println(isLeftToRightAnimation);
    // Serial.println(startupAnimationDelay);
    // Serial.println(indicatorAnimationDelay);
    // Serial.println(animationSeqDelay);
    // Serial.println(animationLeftToRightDelay);
    return true;
}

bool saveConfig()
{
    StaticJsonDocument<300> doc;
    doc["firstFlagColor"] = firstFlagColor;
    doc["secondFlagColor"] = secondFlagColor;
    doc["thirdFlagColor"] = thirdFlagColor;
    doc["ledBrightness"] = ledBrightness;
    doc["mainLightMode"] = mainLightMode;
    doc["isLeftToRightAnimation"] = isLeftToRightAnimation;
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

void readConfigAndSetVariables()
{
    !loadConfig() ? Serial.println("Failed to load config") : Serial.println("Config loaded");
}

void initIO()
{
    pinMode(POWER_HOLD_PIN, OUTPUT);
    digitalWrite(POWER_HOLD_PIN, HIGH);
    Serial.begin(115200);
    if (!LittleFS.begin())
    {
        Serial.println("Failed to mount file system");
    }
    readConfigAndSetVariables();
    rightStrip.setBrightness(ledBrightness);
    leftStrip.setBrightness(ledBrightness);
    rightStrip.begin();
    leftStrip.begin();
    Serial.println("Setup complete");
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
