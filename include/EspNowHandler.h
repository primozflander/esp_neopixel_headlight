#pragma once
#include <espnow.h>
#include <ESP8266WiFi.h>
#include "GlobalVariables.h"
#include "Functions.h"

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus)
{
    Serial.print("Receiver " + String(*mac_addr) + " packet send status: ");
    if (sendStatus == 0)
    {
        Serial.println("Delivery success");
    }
    else
    {
        Serial.println("Delivery fail");
    }
}

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
    memcpy(&settingsToSync, incomingData, sizeof(settingsToSync));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("First flag color: ");
    Serial.println(settingsToSync.firstFlagColor);
    Serial.print("Second flag color: ");
    Serial.println(settingsToSync.secondFlagColor);
    Serial.print("Third flag color: ");
    Serial.println(settingsToSync.thirdFlagColor);
    Serial.print("Led brightness: ");
    Serial.println(settingsToSync.ledBrightness);
    Serial.print("Main light mode: ");
    Serial.println(settingsToSync.mainLightMode);
    Serial.print("LToR animation: ");
    Serial.println(settingsToSync.isLeftToRightAnimation);
    Serial.print("Startup animation delay: ");
    Serial.println(settingsToSync.startupAnimationDelay);
    Serial.print("Indicator animation delay: ");
    Serial.println(settingsToSync.indicatorAnimationDelay);
    Serial.print("Animation seq delay: ");
    Serial.println(settingsToSync.animationSeqDelay);
    Serial.print("Animation LToR delay: ");
    Serial.println(settingsToSync.animationLeftToRightDelay);
    firstFlagColor = settingsToSync.firstFlagColor;
    secondFlagColor = settingsToSync.secondFlagColor;
    thirdFlagColor = settingsToSync.thirdFlagColor;
    ledBrightness = settingsToSync.ledBrightness;
    mainLightMode = settingsToSync.mainLightMode;
    isLeftToRightAnimation = settingsToSync.isLeftToRightAnimation;
    startupAnimationDelay = settingsToSync.startupAnimationDelay;
    indicatorAnimationDelay = settingsToSync.indicatorAnimationDelay;
    animationSeqDelay = settingsToSync.animationSeqDelay;
    animationLeftToRightDelay = settingsToSync.animationLeftToRightDelay;
    saveConfig();
}

void syncSettingsViaESPNow()
{
    settingsToSync.firstFlagColor = firstFlagColor;
    settingsToSync.secondFlagColor = secondFlagColor;
    settingsToSync.thirdFlagColor = thirdFlagColor;
    settingsToSync.ledBrightness = ledBrightness;
    settingsToSync.mainLightMode = mainLightMode;
    settingsToSync.isLeftToRightAnimation = isLeftToRightAnimation;
    settingsToSync.startupAnimationDelay = startupAnimationDelay;
    settingsToSync.indicatorAnimationDelay = indicatorAnimationDelay;
    settingsToSync.animationSeqDelay = animationSeqDelay;
    settingsToSync.animationLeftToRightDelay = animationLeftToRightDelay;
    for (size_t i = 0; i < (sizeof(espReceiverAddresses) / sizeof(espReceiverAddresses[0])); i++)
    {
        esp_now_send(espReceiverAddresses[i], (uint8_t *)&settingsToSync, sizeof(settingsToSync));
    }
}

void initESPNow()
{
    Serial.println(String("MAC: ") + WiFi.macAddress());
    if (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
#ifdef SENDER
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(OnDataSent);
    for (size_t i = 0; i < (sizeof(espReceiverAddresses) / sizeof(espReceiverAddresses[0])); i++)
    {
        esp_now_add_peer(espReceiverAddresses[i], ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
        Serial.println("Adding peer " + String(i));
    }
#endif
#ifdef RECEIVER
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(OnDataRecv);
#endif
}
