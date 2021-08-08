#pragma once
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

String ledState;
AsyncWebServer server(80);

String processor(const String &var)
{
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
    ledBrightness = request->getParam(4)->value().toInt();
    startupAnimationDelay = request->getParam(5)->value().toInt();
    indicatorAnimationDelay = request->getParam(6)->value().toInt();
    animationSeqDelay = request->getParam(7)->value().toInt();
    animationLeftToRightDelay = request->getParam(8)->value().toInt();
    saveConfig();
}

void initServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", String(), false, processor); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/style.css", "text/css"); });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  //   int paramsNr = request->params();
                  //   Serial.println(paramsNr);
                  //   for (int i = 0; i < paramsNr; i++)
                  //   {
                  //       AsyncWebParameter *p = request->getParam(i);
                  //       Serial.print("Param name: ");
                  //       Serial.println(p->name());
                  //       Serial.print("Param value: ");
                  //       Serial.println(p->value());
                  //       Serial.println("------");
                  //   }
                  updateConfiguration(request);
                  request->send(LittleFS, "/index.html", String(), false, processor);
              });

    server.onNotFound(notFound);
    server.begin();
}