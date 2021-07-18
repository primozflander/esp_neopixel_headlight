#pragma once
#include "GlobalVariables.h"

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
    Serial.begin(9600);
    LedStrip.begin();
    LedStrip.setBrightness(BRIGHTNESS);
    Serial.println("Setup complete");
    // setupOTA();
}