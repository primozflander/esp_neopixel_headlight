#pragma once
#include "Functions.h"

void state0()
{
    static bool isFirstTime = true;
    if (states.executeOnce)
    {
        Serial.println("State0, lights Off");
        if (!isFirstTime)
        {
            isLeftToRightAnimation ? setColorFromLeftToRight(noColor, animationLeftToRightDelay)
                                   : setColorSeq(noColor, animationLeftToRightDelay);
            isFirstTime = false;
        }
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
    if (indicatorSwitchRight.isPressed())
    {
        Serial.println("Right indicator on");
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
        if (isMainLightEnabled)
        {
            Serial.println("State2, lights on");
            isLeftToRightAnimation ? setColorFromLeftToRight(white, animationLeftToRightDelay)
                                   : setColorSeq(white, animationLeftToRightDelay);
        }
        else
        {
            Serial.println("State2, main lights disabled");
        }
        onboardLed.on();
        isLightOn = true;
    }
    showMode(1);
}

bool transitionS2S3()
{
    if (indicatorSwitchRight.isPressed() && isMainLightEnabled)
    {
        Serial.println("Right indicator on");
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
        Serial.println("State 3, right indicator on");
    }
    if (isLeftToRightAnimation)
    {
        setColorFromLeftToRight(0, amber, indicatorAnimationDelay);
        setColorFromLeftToRight(0, noColor, indicatorAnimationDelay);
    }
    else
    {
        setColorSeq(0, amber, indicatorAnimationDelay);
        setColorSeq(0, noColor, indicatorAnimationDelay);
    }
    !indicatorSwitchRight.isPressed() ? indicatorOffCounter++ : indicatorOffCounter = 0;
}

bool transitionS3S0()
{
    if (!indicatorSwitchRight.isPressed() && !isLightOn && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Right indicator off");
        digitalWrite(POWER_HOLD_PIN, LOW);
        indicatorOffCounter = 0;
        return true;
    }
    return false;
}

bool transitionS3S2()
{
    if (!indicatorSwitchRight.isPressed() && isLightOn && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Right indicator off");
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
        if (isLeftToRightAnimation)
        {
            showFlagColorsFromLeftToRight(animationLeftToRightDelay);
            setColorFromLeftToRight(noColor, animationLeftToRightDelay);
        }
        else
        {
            showFlagColorsSeq(animationSeqDelay);
            setColorSeq(noColor, animationSeqDelay);
        }
    }
}

bool transitionS4S0()
{
    Serial.println("Transition S4S0");
    digitalWrite(POWER_HOLD_PIN, LOW);
    return true;
}

void state5()
{
    if (states.executeOnce)
    {
        Serial.println("State 5, left indicator on");
    }
    if (isLeftToRightAnimation)
    {
        setColorFromLeftToRight(1, amber, indicatorAnimationDelay);
        setColorFromLeftToRight(1, noColor, indicatorAnimationDelay);
    }
    else
    {
        setColorSeq(1, amber, indicatorAnimationDelay);
        setColorSeq(1, noColor, indicatorAnimationDelay);
    }
    !indicatorSwitchLeft.isPressed() ? indicatorOffCounter++ : indicatorOffCounter = 0;
}

bool transitionS0S5()
{
    if (indicatorSwitchLeft.isPressed())
    {
        Serial.println("Left indicator on");
        return true;
    }
    return false;
}

bool transitionS2S5()
{
    if (indicatorSwitchLeft.isPressed() && isMainLightEnabled)
    {
        Serial.println("Left indicator on");
        return true;
    }
    return false;
}

bool transitionS5S0()
{
    if (!indicatorSwitchLeft.isPressed() && !isLightOn && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Left indicator off");
        digitalWrite(POWER_HOLD_PIN, LOW);
        indicatorOffCounter = 0;
        return true;
    }
    return false;
}

bool transitionS5S2()
{
    if (!indicatorSwitchLeft.isPressed() && isLightOn && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Left indicator off");
        return true;
    }
    return false;
}

bool transitionS5S4()
{
    if (!ignitionSwitch.isPressed() && isLightOn && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Ignition off");
        return true;
    }
    return false;
}

void state6()
{
    if (states.executeOnce)
    {
        Serial.println("State 6, Hazard indicators on");
    }
    if (isLeftToRightAnimation)
    {
        setColorFromLeftToRight(amber, indicatorAnimationDelay);
        setColorFromLeftToRight(noColor, indicatorAnimationDelay);
    }
    else
    {
        setColorSeq(amber, indicatorAnimationDelay);
        setColorSeq(noColor, indicatorAnimationDelay);
    }
    (!indicatorSwitchLeft.isPressed() || !indicatorSwitchRight.isPressed()) ? indicatorOffCounter++ : indicatorOffCounter = 0;
}

bool transitionS3S6()
{
    if (indicatorSwitchLeft.isPressed())
    {
        Serial.println("Left indicator on");
        return true;
    }
    return false;
}

bool transitionS5S6()
{
    if (indicatorSwitchRight.isPressed())
    {
        Serial.println("Right indicator on");
        return true;
    }
    return false;
}

bool transitionS6S3()
{
    if (!indicatorSwitchLeft.isPressed() && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Left indicator off");
        return true;
    }
    return false;
}

bool transitionS6S5()
{
    if (!indicatorSwitchRight.isPressed() && indicatorOffCounter > INDICATOR_TURN_OFF_COUNTER)
    {
        Serial.println("Right indicator off");
        return true;
    }
    return false;
}

State *S0 = states.addState(&state0);
State *S1 = states.addState(&state1);
State *S2 = states.addState(&state2);
State *S3 = states.addState(&state3);
State *S4 = states.addState(&state4);
State *S5 = states.addState(&state5);
State *S6 = states.addState(&state6);

void initStates()
{
    S0->addTransition(&transitionS0S1, S1);
    S0->addTransition(&transitionS0S3, S3);
    S0->addTransition(&transitionS0S5, S5);
    S1->addTransition(&transitionS1S2, S2);
    S2->addTransition(&transitionS2S3, S3);
    S2->addTransition(&transitionS2S4, S4);
    S2->addTransition(&transitionS2S5, S5);
    S3->addTransition(&transitionS3S0, S0);
    S3->addTransition(&transitionS3S2, S2);
    S3->addTransition(&transitionS3S4, S4);
    S4->addTransition(&transitionS4S0, S0);
    S5->addTransition(&transitionS5S0, S0);
    S5->addTransition(&transitionS5S2, S2);
    S5->addTransition(&transitionS5S4, S4);
    S3->addTransition(&transitionS3S6, S6);
    S5->addTransition(&transitionS5S6, S6);
    S6->addTransition(&transitionS6S3, S3);
    S6->addTransition(&transitionS6S5, S5);
}
