# webhook-button

## Overview
The goal is to create a button that when pushed calls a configured http(s) url.
The idea, hardware setup has developed by my colleague - Aleksander Iwański. 

## How will it work?

The webhook button is powered up by a battery. When the webhook button is powered up WiFi is enabled. 
The button exposes following services:
- /wifi
   
   a html service that allows configuration of wifi connection to an access point.
- [GET] /webhook

    return current configuration of http(s) url address that is called when the button is pushed
    
- [POST] /webhook

    {
        url: `url address to be called`
        headers: [] `array of headers that are passed along the request`
        method: `valid http method like GET, POST, PUT, ...`
        payload: `a string that represents payload`
    } 

When the webhook button is pushed then it calls the configured url accordingly to the configuration

# Setup

* Software
    * [platformio](https://platformio.org)
    * [CLion](https://www.jetbrains.com/clion/)
* Hardware
    * Arduino NodeMCU v3 (used to ease development of targeted ESP8266)
    * ESP8266
    
![hardware setup](hardware_setup.jpg)
   
## Preparation of the environment

1. Install platformio
   
    `brew install platformio`

1. Prepare project's dir

    Create project's directory and within the directory execute command:
    `platformio init --ide clion --board nodemcuv2` 

1. Compile project

    `platformio run`
    
1. Connect arduino to computer with USB port
1. Upload program

    `platformio run --target upload`
1. [Optional] reset arduino (stop blinking)
    
    Set `constant WORKING_PROGRAM   = false;`
    compile by `platformio run` and upload `platformio run --target upload`

# Appendix
## Lectures
* [Setup CLion and Arduino](https://www.instructables.com/id/Setup-JetBrains-Clion-for-Arduino-Development/)
* [Clion, Arduino and platformio combo setup](https://stuetzpunkt.wordpress.com/2017/06/26/a-first-program-with-esp8266esp-01-clion-and-platformio/)
* [Platformio Documentation](http://docs.platformio.org/en/stable/index.html)
* [Wifi Manager](https://github.com/tzapu/WiFiManager/wiki/API-reference)
* [aRest](https://github.com/marcoschwartz/aREST/blob/master/README.md)
* [ESP8266 HTTPClient examples](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/BasicHttpsClient/BasicHttpsClient.ino)
* [ESP8266 Decoding / Encoding JSON](https://randomnerdtutorials.com/decoding-and-encoding-json-with-arduino-or-esp8266/)
* [Why doesn't the built led work for Arduino NodeMCU v3](https://arduino.stackexchange.com/questions/38477/does-the-node-mcu-v3-lolin-not-have-a-builtin-led)
* [How do properly call a https call using ESP8266 HTTPClient](https://medium.com/@dfa_31434/doing-ssl-requests-on-esp8266-correctly-c1f60ad46f5e)