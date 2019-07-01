#include <unity.h>

#include <etl/message_bus.h>
#include "button_messages.h"

#include "hardware/ButtonHardwareDetector.h"
#include "assertions/MessageBusVerifier.h"

ButtonHardwareDetector *inLoopProcessor;
etl::imessage_bus *bus;
assertions::MessageBusVerifier *busVerifier;

void test_emits_UP_MESSAGE_when_pin_indicates_that_button_is_up() {
    // given signals via pin that button is up
    digitalWrite(hardware::BUTTON_PIN, HARDWARE_BUTTON_UP);

    // when loop is initiated
    etl::send_message(*bus, LoopInitiatedMessage::of(0));

    // then emits button up
    assertions::assertThat(busVerifier)
            .receivedMessagesOfType(1, MessageType::BUTTON_UP)
            .receivedNoMessagesOfType(MessageType::BUTTON_DOWN);
}

void test_emits_DOWN_MESSAGE_when_pin_indicates_that_button_is_down() {
    // given signals via pin that button is down
    digitalWrite(hardware::BUTTON_PIN, HARDWARE_BUTTON_DOWN);

    // when loop is initiated
    etl::send_message(*bus, LoopInitiatedMessage::of(0));
    // then emits button down
    assertions::assertThat(busVerifier)
            .receivedMessagesOfType(1, MessageType::BUTTON_DOWN)
            .receivedNoMessagesOfType(MessageType::BUTTON_UP);
}

void setUp() {
    bus = new etl::message_bus<2>();
    inLoopProcessor = new ButtonHardwareDetector(*bus);
    busVerifier = new assertions::MessageBusVerifier();

    bus->subscribe(*inLoopProcessor);
    bus->subscribe(*busVerifier);
}

#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3); // RX | TX

void execute_tests() {
    UNITY_BEGIN();

    RUN_TEST(test_emits_UP_MESSAGE_when_pin_indicates_that_button_is_up);
    RUN_TEST(test_emits_DOWN_MESSAGE_when_pin_indicates_that_button_is_down);

    UNITY_END();
}


void setup() {
    //   ***  Additional Code that fixed my problem  ****
    Serial.begin(9600);
    ESPserial.begin(9600);
    delay(1000);

    Serial.println("Ready");
    ESPserial.println("AT+GMR");

    pinMode(hardware::BUTTON_PIN, INPUT);
    pinMode(hardware::BUTTON_PIN, OUTPUT);

    execute_tests();
}

void loop() {
}
