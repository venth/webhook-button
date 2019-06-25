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
    
1. Clone this project
    
    `git clone https://github.com/venth/webhook-button.git` 

1. Go to freshly created directory "webhook-button" and prepare project's for CLion

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

## Daily things

* adding library
    * add entry in platformio.ini file to `lib_deps` property
    * update CLion project settings by executing command: `platformio init --ide clion --board nodemcuv2`
    
## Fighting diary

* failing tests

    ```
    Please wait...
    ar: no archive members specified
    usage:  ar -d [-TLsv] archive file ...
    ar -m [-TLsv] archive file ...
    ar -m [-abiTLsv] position archive file ...
    ar -p [-TLsv] archive [file ...]
    ar -q [-cTLsv] archive file ...
    ar -r [-cuTLsv] archive file ...
    ar -r [-abciuTLsv] position archive file ...
    ar -t [-TLsv] archive [file ...]
    ar -x [-ouTLsv] archive [file ...]
    *** [.pioenvs/native/lib0be/libEmbedded Template Library.a] Error 1
    In file included from .piolibdeps/WifiManager_ID567/WiFiManager.cpp:13:
    .piolibdeps/WifiManager_ID567/WiFiManager.h:16:10: fatal error: 'ESP8266WiFi.h' file not found
    #include <ESP8266WiFi.h>
    ```
    
    There are two issue in the aforementioned comment. First - `platformio' cannot create archive and 
    second - on the native platform we try to compile embedded library.
    
    To fix the first issue the code that contains references to embedded library is excluded in the native section of the platformio.ini file:
    `src_filter = +<*> -<main.cpp>` 
    
    The second issue is also corrected by change in the configuration. Adding `lib_archive = false` made platformio to omit
    archive creation.
    
* [Embedded Template Library](https://www.etlcpp.com) compilation issues
    
    In the first approach `lib_deps =` section contained just the name of library, which caused installation of the most
    recently compiled library for the os. Unfortunately OSX compilation is quite old. To fix the issue installation
    by library name is replaced by installation by github repository url along with version (`https://github.com/ETLCPP/etl.git#14.26.7`).
    
    The next issue is caused by ecl_timer.c file. The fix is to use script executed before build that removes ecl_timer
    files. The script name: `clean_timer.py` and configuration in the platformio.ini: `extra_scripts = pre:clean_timer.py`

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
* [Embedded Template Library](https://www.etlcpp.com)
* [Arduino official documentation](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/)
* [Nodemcu pinout](https://circuits4you.com/2017/12/31/nodemcu-pinout/)
