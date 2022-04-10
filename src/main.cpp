#include "GlobalVariables.h"
#include "States.h"
#include "Functions.h"
#include "WebServer.h"
#include "OTA.h"
#include "EspNowHandler.h"

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

// #include <Arduino.h>
// #include <Adafruit_NeoPixel.h>
// #include "GlobalVariables.h"

// class Strip
// {
// public:
//     uint8_t effect;
//     uint8_t effects;
//     uint16_t effStep;
//     unsigned long effStart;
//     Adafruit_NeoPixel strip;
//     Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype)
//     {
//         effect = -1;
//         effects = toteffects;
//         Reset();
//     }
//     void Reset()
//     {
//         effStep = 0;
//         effect = (effect + 1) % effects;
//         effStart = millis();
//     }
// };

// struct Loop
// {
//     uint8_t currentChild;
//     uint8_t childs;
//     bool timeBased;
//     uint16_t cycles;
//     uint16_t currentTime;
//     Loop(uint8_t totchilds, bool timebased, uint16_t tottime)
//     {
//         currentTime = 0;
//         currentChild = 0;
//         childs = totchilds;
//         timeBased = timebased;
//         cycles = tottime;
//     }
// };

// Strip strip_0(210, D8, 210, NEO_GRB + NEO_KHZ800);
// struct Loop strip0loop0(1, false, 1);

// //[GLOBAL_VARIABLES]

// void strip0_loop0_eff0()
// {
//     // Strip ID: 0 - Effect: Rainbow - LEDS: 210
//     // Steps: 189 - Delay: 26
//     // Colors: 3 (255.0.0, 255.255.255, 0.255.0)
//     // Options: rainbowlen=210, toLeft=true,
//     // if (millis() < 26 * (strip_0.effStep))
//     //     return 0x00;
//     static unsigned int effStep = 0;
//     float factor1, factor2;
//     uint16_t ind;
//     for (uint16_t j = 0; j < 100; j++)
//     {
//         ind = effStep + j * 0.9;
//         switch ((int)((ind % 189) / 63))
//         {
//         case 0:
//             factor1 = 1.0 - ((float)(ind % 189 - 0 * 63) / 63);
//             factor2 = (float)((int)(ind - 0) % 189) / 63;
//             // strip_0.strip.setPixelColor(j, 255 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2);
//             rightStrip.setPixelColor(j, 255 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 255 * factor2);
//             break;
//         case 1:
//             factor1 = 1.0 - ((float)(ind % 189 - 1 * 63) / 63);
//             factor2 = (float)((int)(ind - 63) % 189) / 63;
//             // strip_0.strip.setPixelColor(j, 255 * factor1 + 0 * factor2, 255 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2);
//             rightStrip.setPixelColor(j, 255 * factor1 + 0 * factor2, 255 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2);

//             break;
//         case 2:
//             factor1 = 1.0 - ((float)(ind % 189 - 2 * 63) / 63);
//             factor2 = (float)((int)(ind - 126) % 189) / 63;
//             // strip_0.strip.setPixelColor(j, 0 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 0 * factor2);
//             rightStrip.setPixelColor(j, 0 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 0 * factor2);

//             break;
//         }
//     }
//     // if (strip_0.effStep >= 189)
//     // {
//     //     strip_0.Reset();
//     //     return 0x03;
//     // }
//     // else
//         effStep++;
//         delay(26);
//         rightStrip.show();
// }

// // uint8_t strip0_loop0()
// // {
// //     uint8_t ret = 0x00;
// //     switch (strip0loop0.currentChild)
// //     {
// //     case 0:
// //         ret = strip0_loop0_eff0();
// //         break;
// //     }
// //     if (ret & 0x02)
// //     {
// //         ret &= 0xfd;
// //         if (strip0loop0.currentChild + 1 >= strip0loop0.childs)
// //         {
// //             strip0loop0.currentChild = 0;
// //             if (++strip0loop0.currentTime >= strip0loop0.cycles)
// //             {
// //                 strip0loop0.currentTime = 0;
// //                 ret |= 0x02;
// //             }
// //         }
// //         else
// //         {
// //             strip0loop0.currentChild++;
// //         }
// //     };
// //     return ret;
// // }

// // void strips_loop()
// // {
// //     // if (strip0_loop0() & 0x01)
// //     // {
// //         strip0_loop0();
// //         // strip_0.strip.show();
// //         rightStrip.show();
// //     // }
// // }

// void setup()
// {

//     // Your setup here:

//     strip_0.strip.begin();
//     rightStrip.begin();
// }

// void loop()
// {

//     // Your code here:

//         // strip0_loop0();
//         strip0_loop0_eff0();
//         // strip_0.strip.show();
//         // rightStrip.show();
// }
