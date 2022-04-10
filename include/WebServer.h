#pragma once
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include "EspNowHandler.h"

AsyncWebServer server(80);

String isColorSelected(uint32_t selectedColor, uint32_t color)
{
    return (selectedColor == color) ? "selected" : "";
}

String generateColorSelectionPlaceholder(uint32_t flagColorPosition)
{
    String output = "<option value=\"white\"" + isColorSelected(flagColorPosition, white) + ">White</option>";
    output += "<option value=\"red\"" + isColorSelected(flagColorPosition, red) + ">Red</option>";
    output += "<option value=\"blue\"" + isColorSelected(flagColorPosition, blue) + ">Blue</option>";
    output += "<option value=\"green\"" + isColorSelected(flagColorPosition, green) + ">Green</option>";
    output += "<option value=\"cyan\"" + isColorSelected(flagColorPosition, cyan) + ">Cyan</option>";
    output += "<option value=\"yellow\"" + isColorSelected(flagColorPosition, yellow) + ">Yellow</option>";
    output += "<option value=\"magenta\"" + isColorSelected(flagColorPosition, magenta) + ">Magenta</option>";
    output += "<option value=\"amber\"" + isColorSelected(flagColorPosition, amber) + ">Amber</option>";
    output += "<option value=\"noColor\"" + isColorSelected(flagColorPosition, noColor) + ">No color</option>";
    return output;
}

String processor(const String &var)
{
    if (var == "FIRSTFLAGCOLORPLACEHOLDER")
    {
        return generateColorSelectionPlaceholder(firstFlagColor);
    }
    else if (var == "SECONDFLAGCOLORPLACEHOLDER")
    {
        return generateColorSelectionPlaceholder(secondFlagColor);
    }
    else if (var == "THIRDFLAGCOLORPLACEHOLDER")
    {
        return generateColorSelectionPlaceholder(thirdFlagColor);
    }
    else if (var == "ANIMATIONTYPEPLACEHOLDER")
    {
        String output = "<option value=0" + String(!isLeftToRightAnimation ? " selected" : "") + ">Sequential</option>";
        output += "<option value=1" + String(isLeftToRightAnimation ? " selected" : "") + ">From left to right</option>";
        return output;
    }
    else if (var == "MAINLIGHTSPLACEHOLDER")
    {
        String output = "<option value=0" + String(mainLightMode == 0 ? " selected" : "") + ">Disabled</option>";
        output += "<option value=1" + String(mainLightMode == 1 ? " selected" : "") + ">Enabled</option>";
        output += "<option value=2" + String(mainLightMode == 2 ? " selected" : "") + ">Light show</option>";
        return output;
    }
    else if (var == "LEDBRIGHTNESSPLACEHOLDER")
    {
        String output = "<option value=0" + String((ledBrightness == 0) ? " selected" : "") + ">Zero</option>";
        output += "<option value=64" + String((ledBrightness == 64) ? " selected" : "") + ">Dark</option>";
        output += "<option value=128" + String((ledBrightness == 128) ? " selected" : "") + ">Middle</option>";
        output += "<option value=196" + String((ledBrightness == 196) ? " selected" : "") + ">Bright</option>";
        output += "<option value=255" + String((ledBrightness == 255) ? " selected" : "") + ">Maximum</option>";
        return output;
    }
    else if (var == "DELAYSPLACEHOLDER")
    {
        String output = "<label>Startup/goodbye animation delay</label>";
        output += "<input name=\"startupAnimationDelay\" id=\"startupAnimationDelay\" type=\"number\" min=\"1\" max=\"10000\" value=" + String(startupAnimationDelay) + ">";
        output += "<label>Indicator animation delay</label>";
        output += "<input name=\"indicatorAnimationDelay\" id=\"indicatorAnimationDelay\" type=\"number\" min=\"1\" max=\"10000\" value=" + String(indicatorAnimationDelay) + ">";
        output += "<label>Sequential animation delay</label>";
        output += "<input name=\"animationSeqDelay\" id=\"animationSeqDelay\" type=\"number\" min=\"1\" max=\"10000\" value=" + String(animationSeqDelay) + ">";
        output += "<label>Animation delay</label>";
        output += "<input name=\"animationLeftToRightDelay\" id=\"animationLeftToRightDelay\" type=\"number\" min=\"1\" max=\"10000\" value=" + String(animationLeftToRightDelay) + ">";
        return output;
    }
    return String();
}

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void updateConfiguration(AsyncWebServerRequest *request)
{
    firstFlagColor = convertColorNameToValue(request->getParam(0)->value());
    secondFlagColor = convertColorNameToValue(request->getParam(1)->value());
    thirdFlagColor = convertColorNameToValue(request->getParam(2)->value());
    isLeftToRightAnimation = request->getParam(3)->value().toInt() ? true : false;
    mainLightMode = request->getParam(4)->value().toInt();
    ledBrightness = request->getParam(5)->value().toInt();
    startupAnimationDelay = request->getParam(6)->value().toInt();
    indicatorAnimationDelay = request->getParam(7)->value().toInt();
    animationSeqDelay = request->getParam(8)->value().toInt();
    animationLeftToRightDelay = request->getParam(9)->value().toInt();
    rightStrip.setBrightness(ledBrightness);
    leftStrip.setBrightness(ledBrightness);
    saveConfig();
    syncSettingsViaESPNow();
}

void initServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", String(), false, processor); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/style.css", "text/css"); });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                    int paramsNr = request->params();
                    for (int i = 0; i < paramsNr; i++)
                    {
                        AsyncWebParameter *p = request->getParam(i);
                        Serial.print("Param name: ");
                        Serial.println(p->name());
                        Serial.print("Param value: ");
                        Serial.println(p->value());
                        Serial.println("------");
                    }
                    request->send(LittleFS, "/index.html", String(), false, processor);
                    updateConfiguration(request); });

    server.onNotFound(notFound);
    server.begin();
}
