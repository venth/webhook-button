#include <Arduino.h>

static const uint8_t ARDUINO_NODECMU_V3_BUILT_IN_LED   = D4;

static const boolean WORKING_PROGRAM   = true;

void setup()
{
    // initialize LED digital pin as an output.
    if (WORKING_PROGRAM) {
        pinMode(ARDUINO_NODECMU_V3_BUILT_IN_LED, OUTPUT);
    }
}

void loop()
{
    if (WORKING_PROGRAM) {
        // turn the LED off (HIGH is the voltage level)
        digitalWrite(ARDUINO_NODECMU_V3_BUILT_IN_LED, HIGH);
        Serial.println("Turned off");
        // wait for a second
        delay(1000);
        // turn the LED on by making the voltage LOW
        digitalWrite(ARDUINO_NODECMU_V3_BUILT_IN_LED, LOW);
        Serial.println("Turned on");
        // wait for a second
        delay(1000);
    }
}