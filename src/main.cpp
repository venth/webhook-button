#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "hardware/ButtonHardwareDetector.h"
#include "hardware/WiFiConfigurationRequestHandler.h"
#include "ButtonPressedForWebHookDetector.h"
#include "ButtonPressedForWifiConfigurationDetector.h"
#include "ButtonPressingDetector.h"
#include "InLoopProcessor.h"
#include "MessageDumper.h"


etl::message_bus<6> bus;
InLoopProcessor inLoopProcessor(bus);
hardware::ButtonHardwareDetector buttonHardwareDetector(bus);
ButtonPressingDetector buttonPressingDetector(bus);
ButtonPressedForWebHookDetector buttonPressedForWebHookDetector(bus);
ButtonPressedForWifiConfigurationDetector buttonPressedForWifiConfigurationDetector(bus);

//it starts an access point
//and goes into a blocking loop awaiting configuration
std::string apName = std::string("webhook-button") + std::string(String(ESP.getChipId()).c_str());
std::string apPassword = std::string("72ad2cc8-5756-4804-b4d8-ae5cbacfab31");
IPAddress apAddress(192, 168, 100, 1);
IPAddress apCidr(255, 255, 255, 0);

hardware::WiFiConfigurationRequestHandler wiFiConfigurationRequestHandler(bus, apName, apPassword, apAddress, apCidr);


MessageDumper messageDumper;

SoftwareSerial ESPserial(2, 3); // RX | TX

static const uint8_t ARDUINO_NODECMU_V3_BUILT_IN_LED = D4;

static const boolean WORKING_PROGRAM = true;

void setup() {
    if (!WORKING_PROGRAM) {
        return;
    }

    //   ***  Additional Code that fixed my problem  ****
    Serial.begin(9600);
    ESPserial.begin(9600);

    Serial.println("Ready");
    ESPserial.println("AT+GMR");

// ***   End of additional code

    bus.subscribe(messageDumper);
    bus.subscribe(buttonHardwareDetector);
    bus.subscribe(buttonPressingDetector);
    bus.subscribe(buttonPressedForWebHookDetector);
    bus.subscribe(buttonPressedForWifiConfigurationDetector);
    bus.subscribe(wiFiConfigurationRequestHandler);

    pinMode(D2, INPUT);
}

void loop() {
    if (!WORKING_PROGRAM) {
        return;
    }

    inLoopProcessor.processIt();
}