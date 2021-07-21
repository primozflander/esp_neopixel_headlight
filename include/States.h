#pragma once
// #include "GlobalVariables.h"
#include "Functions.h"

void state0()
{
    if (states.executeOnce)
    {
        Serial.println("State0, lights Off");
        #ifdef ANIMATE_LEFTTORIGHT
        setColorFromLeftToRight(NO_COLOR, SEQ_DELAY);
        #else
        setColorSeq(NO_COLOR, SEQ_DELAY);
        #endif
        onboardLed.off();
        isLightOn = false;
    }
}

bool transitionS0S1()
{
    if (ignitionSwitch.isPressed())
    {
        Serial.println("Ignition on");
        return true;
    }
    return false;
}


bool transitionS0S3()
{
    if (indicatorSwitch.isPressed())
    {
        Serial.println("Indicator on");
        return true;
    }
    return false;
}

void state1()
{
    if (states.executeOnce)
    {
        Serial.println("State1, welcome sequence");
        #ifdef ANIMATE_LEFTTORIGHT
        showFlagColorsFromLeftToRight();
        #else
        showFlagColorsSeq();
        #endif
    }
}

bool transitionS1S2()
{
    Serial.println("Transition S1S2");
    return true;
}

void state2()
{
    if (states.executeOnce)
    {
        Serial.println("State2, lights on");
        #ifdef ANIMATE_LEFTTORIGHT
        setColorFromLeftToRight(WHITE, SEQ_DELAY);
        #else
        setColorSeq(WHITE, SEQ_DELAY);
        #endif
        onboardLed.on();
        isLightOn = true;
    }
}

bool transitionS2S3()
{
    if (indicatorSwitch.isPressed())
    {
        Serial.println("Indicator on");
        return true;
    }
    return false;
}

bool transitionS2S4()
{
    if (!ignitionSwitch.isPressed())
    {
        Serial.println("Ignition off");
        return true;
    }
    return false;
}

void state3()
{
    if (states.executeOnce)
    {
        Serial.println("State 3, indicator on");
    }
    Serial.println("amber");
    #ifdef ANIMATE_LEFTTORIGHT
    setColorFromLeftToRight(AMBER, SEQ_DELAY);
    setColorFromLeftToRight(NO_COLOR, SEQ_DELAY);
    #else
    setColorSeq(NO_COLOR, SEQ_DELAY);
    setColorSeq(AMBER, SEQ_DELAY);
    #endif
    Serial.println("no color");
}

bool transitionS3S0()
{
    if (!indicatorSwitch.isPressed() && !isLightOn)
    {
        Serial.println("Indicator off");
        return true;
    }
    return false;
}

bool transitionS3S2()
{
    if (!indicatorSwitch.isPressed() && isLightOn)
    {
        Serial.println("Indicator off");
        return true;
    }
    return false;
}

bool transitionS3S4()
{
    if (!ignitionSwitch.isPressed() && isLightOn)
    {
        Serial.println("Ignition off");
        return true;
    }
    return false;
}

void state4()
{
    if (states.executeOnce)
    {
        Serial.println("State4, goodbye sequence");
        #ifdef ANIMATE_LEFTTORIGHT
        showFlagColorsFromLeftToRight();
        #else
        showFlagColorsSeq();
        #endif
    }
}

bool transitionS4S0()
{
    Serial.println("Transition S4S0");
    return true;
}

State *S0 = states.addState(&state0);
State *S1 = states.addState(&state1);
State *S2 = states.addState(&state2);
State *S3 = states.addState(&state3);
State *S4 = states.addState(&state4);

void initStates()
{
    S0->addTransition(&transitionS0S1, S1);
    S0->addTransition(&transitionS0S3, S3);
    S1->addTransition(&transitionS1S2, S2);
    S2->addTransition(&transitionS2S3, S3);
    S2->addTransition(&transitionS2S4, S4);
    S3->addTransition(&transitionS3S2, S2);
    S3->addTransition(&transitionS3S0, S0);
    S3->addTransition(&transitionS3S4, S4);
    S4->addTransition(&transitionS4S0, S0);
}