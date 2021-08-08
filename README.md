# ESP8266 Neopixel Headlights

Repository consists of software and brief description of how to set up the project.

**Table of Contents**

- [ESP8266 Neopixel Headlights](#ESP8266-Neopixel-Headlights)
  * [About The Project](#about-the-project)
    + [Built With](#built-with)
  * [Getting Started](#getting-started)
    + [Prerequisites](#prerequisites)
  * [Set up](#installation)
    + [Uploading web server files](#uploading-web-server-files)
    + [Uploading firmware](#uploading-firmware)
    + [Accessing the server](#accessing-the-server)
  * [Contact](#contact)
  * [Acknowledgements](#acknowledgements)

## About The Project

A custom controller was developed for controlling NeoPixel LEDs inside the car headlights. It consists of ESP8266 controller which monitors ignition and indicator inputs and controls Neopixel LEDs. ESP8266 is hosting web server which enables configuration of the parameters over Wi-Fi. Firmware update via OTA is supported.

It features:
* Hello/goodbye animation
* Two types of animations
* User can select between eight different colors
* Server AP for changing configuration
* OTA - over the air update

### Built With

* [Visual Studio Code](https://code.visualstudio.com)
* [PlatformIO](https://platformio.org)

## Getting Started

Follow this steps to set-up you board. Recommended board: NodeMCU 1.0 (ESP-12E)

### Prerequisites

* PlatformIO


## Set up

### Uploading web server files

1. Open project with [PlatformIO](https://platformio.org)
2. From side menu select `Build Filesystem Image`
3. From side menu select `Upload Filesystem Image` to upload image to the SPIFFS

### Uploading firmware

1. From side menu select `Upload` to upload firmware

![pio](docs/images/spiffs.png)

### Accessing the server

1. Default server IP: `192.168.4.1`

![server](docs/images/server.png)

## Contact

Primoz Flander: primoz.flander@gmail.com

Project Link: [NeoPixel Headlights](https://github.com/primozflander/esp_neopixel_headlight)



## Acknowledgements
* Craig Robinson
