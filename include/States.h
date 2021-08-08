#pragma once
// #include "GlobalVariables.h"
#include "Functions.h"

void state0()
{
    if (states.executeOnce)
    {
        Serial.println("State0, lights Off");
        isLeftToRightAnimation ? setColorFromLeftToRight(noColor, animationLeftToRightDelay)
                               : setColorSeq(noColor, animationLeftToRightDelay);
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
        isLeftToRightAnimation ? showFlagColorsFromLeftToRight(animationLeftToRightDelay)
                               : showFlagColorsSeq(animationSeqDelay);
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
        isLeftToRightAnimation ? setColorFromLeftToRight(white, animationLeftToRightDelay)
                               : setColorSeq(white, animationLeftToRightDelay);
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
    if (isLeftToRightAnimation)
    {
        setColorFromLeftToRight(amber, animationLeftToRightDelay);
        setColorFromLeftToRight(noColor, animationLeftToRightDelay);
    }
    else
    {
        setColorSeq(amber, animationSeqDelay);
        setColorSeq(noColor, animationSeqDelay);
    }
    !indicatorSwitch.isPressed() ? indicatorOffCounter++ : indicatorOffCounter = 0;
}

bool transitionS3S0()
{
    if (!indicatorSwitch.isPressed() && !isLightOn && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Indicator off");
        digitalWrite(POWER_HOLD_PIN, LOW);
        indicatorOffCounter = 0;
        return true;
    }
    return false;
}

bool transitionS3S2()
{
    if (!indicatorSwitch.isPressed() && isLightOn && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Indicator off");
        return true;
    }
    return false;
}

bool transitionS3S4()
{
    if (!ignitionSwitch.isPressed() && isLightOn && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
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
        isLeftToRightAnimation ? showFlagColorsFromLeftToRight(animationLeftToRightDelay)
                               : showFlagColorsSeq(animationSeqDelay);
    }
}

bool transitionS4S0()
{
    Serial.println("Transition S4S0");
    digitalWrite(POWER_HOLD_PIN, LOW);
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