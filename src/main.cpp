#include "GlobalVariables.h"
#include "States.h"
#include "Functions.h"
#include "WebServer.h"
#include "OTA.h"

void setup()
{
    initIO();
    initStates();
    readConfigAndSetVariables();
    initServer();
}

void loop()
{
    ArduinoOTA.handle();
    states.run();
    delay(STATE_DELAY);
    isAliveLed.blinkMs(500);
}
