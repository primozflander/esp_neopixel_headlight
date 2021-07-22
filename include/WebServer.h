#pragma once
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>



// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String getTemperature()
{
    float temperature = 0;
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //float t = dht.readTemperature(true);
    Serial.println(temperature);
    return String(temperature);
}

String getHumidity()
{
    float humidity = 0;
    Serial.println(humidity);
    return String(humidity);
}

String getPressure()
{
    float pressure = 0;
    Serial.println(pressure);
    return String(pressure);
}

// Replaces placeholder with LED state value
String processor(const String &var)
{
    Serial.println(var);
    if (var == "STATE")
    {
        if (digitalRead(LED_PIN))
        {
            ledState = "ON";
        }
        else
        {
            ledState = "OFF";
        }
        Serial.print(ledState);
        return ledState;
    }
    else if (var == "TEMPERATURE")
    {
        return getTemperature();
    }
    else if (var == "HUMIDITY")
    {
        return getHumidity();
    }
    else if (var == "PRESSURE")
    {
        return getPressure();
    }
    return String();
}

void initServer()
{
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", String(), false, processor); });

    // Route to load style.css file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/style.css", "text/css"); });

    // Route to set GPIO to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  digitalWrite(LED_PIN, HIGH);
                  request->send(LittleFS, "/index.html", String(), false, processor);
              });

    // Route to set GPIO to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  digitalWrite(LED_PIN, LOW);
                  request->send(LittleFS, "/index.html", String(), false, processor);
              });

    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/plain", getTemperature().c_str()); });

    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/plain", getHumidity().c_str()); });

    server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/plain", getPressure().c_str()); });

    // Start server
    server.begin();
}