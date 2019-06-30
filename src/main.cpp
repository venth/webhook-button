#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include <Arduino.h>

#include <SoftwareSerial.h>


SoftwareSerial ESPserial(2, 3); // RX | TX

static const uint8_t ARDUINO_NODECMU_V3_BUILT_IN_LED = D4;

static const boolean WORKING_PROGRAM = true;

//gets called when WiFiManager enters configuration mode
void configModeCallback(WiFiManager *myWiFiManager) {
    Serial.println("Entered config mode");
    Serial.println(WiFi.softAPIP());
    //if you used auto generated SSID, print it
    Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
    if (!WORKING_PROGRAM) {
        return;
    }

    //   ***  Additional Code that fixed my problem  ****
    Serial.begin(9600);
    ESPserial.begin(9600);
    delay(1000);

    Serial.println("Ready");
    ESPserial.println("AT+GMR");

// ***   End of additional code
/*
    unsigned long startedAt = millis();

    WiFi.printDiag(Serial); //Remove this line if you do not want to see WiFi password printed
    Serial.println("Opening configuration portal");
    //Local initialization. Once its business is done, there is no need to keep it around

    WiFiManager wifiManager;
    //sets timeout in seconds until configuration portal gets turned off.
    wifiManager.setTimeout(120);

    //If not specified device will remain in configuration mode until
    //switched off via webserver.
    if (WiFi.SSID() != "")
        wifiManager.setConfigPortalTimeout(60); //If no access point name has been previously entered disable timeout.

    //it starts an access point
    //and goes into a blocking loop awaiting configuration
    //Delete these two parameters if you do not want a WiFi password on your configuration access point
    String apName = "webhook-button" + String(ESP.getChipId());
    const char *password = "72ad2cc8-5756-4804-b4d8-ae5cbacfab31";
    if (wifiManager.startConfigPortal(apName.c_str(), password)) {
        //if you get here you have connected to the WiFi
        Serial.println("connected...yeey :)");
    } else {
        Serial.println("Not connected to WiFi but continuing anyway.");
    }
    // For some unknown reason webserver can only be started once per boot up
    // so webserver can not be used again in the sketch.

    Serial.print("After waiting ");
    int connRes = WiFi.waitForConnectResult();
    float waited = (millis() - startedAt);
    Serial.print(waited / 1000);
    Serial.print(" secs in setup() connection result is ");
    Serial.println(connRes);
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("failed to connect, finishing setup anyway");
    } else {
        Serial.print("local ip: ");
        Serial.println(WiFi.localIP());
    }
*/
    pinMode(D2, INPUT);
}

void loop() {
    if (!WORKING_PROGRAM) {
        return;
    }

    Serial.print("PIN READ: ");
    Serial.println(digitalRead(D2));
}