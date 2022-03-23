#include "GlobalVariables.h"
#include "States.h"
#include "Functions.h"
#include "WebServer.h"
#include "OTA.h"
#include "EspNow.h"

void setup()
{
    initIO();
    initStates();
    initOTA();
    #ifdef SENDER
    initServer();
    #endif
    initESPNow();
}

void loop()
{
    ArduinoOTA.handle();
    states.run();
    delay(STATE_DELAY);
    isAliveLed.blinkMs(500);
}
