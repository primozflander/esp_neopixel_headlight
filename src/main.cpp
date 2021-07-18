#include "GlobalVariables.h"
#include "States.h"
#include "Functions.h"

void setup()
{
    initIO();
    initStates();
}

void loop()
{
    // ArduinoOTA.handle();
    states.run();
    delay(STATE_DELAY);
    isAliveLed.blinkMs(500);
}
