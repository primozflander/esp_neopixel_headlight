#include "GlobalVariables.h"
#include "States.h"
#include "Functions.h"
#include "WebServer.h"
#include "OTA.h"

void setup()
{
    readConfigAndSetVariables();
    initIO();
    initStates();
    initOTA();
    initServer();
}

void loop()
{
    ArduinoOTA.handle();
    states.run();
    delay(STATE_DELAY);
    isAliveLed.blinkMs(500);
}
