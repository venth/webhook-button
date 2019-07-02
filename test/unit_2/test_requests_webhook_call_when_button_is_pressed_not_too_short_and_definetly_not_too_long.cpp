#include <unity.h>

#include <etl/message_bus.h>
#include <ButtonPressedForWebHookDetector.h>
#include "button_messages.h"

#include "assertions/MessageBusVerifier.h"

ButtonPressedForWebHookDetector *buttonPressedForWebHookDetector;
etl::imessage_bus *bus;
assertions::MessageBusVerifier *busVerifier;

void emits_webhook_call_reuqest_when_duration_is_at_beginning_of_the_duration_pressing_range() {
    // when presses button for at at least 50 milliseconds
    etl::send_message(*bus, ButtonPressedMessage::of(0, SHORTEST_PRESSING_DURATION_IN_MILLIS));

    // then
    assertions::assertThat(busVerifier)
        .receivedMessagesOfType(1, MessageType::WEBHOOK_CALL_REQUESTED);
}

void emits_webhook_call_request_when_pressing_duration_is_at_most_at_the_end_of_the_duration_pressing_range() {
    // when presses button for for a time that fits in pressing duration range
    etl::send_message(*bus, ButtonPressedMessage::of(0, LONGEST_PRESSING_DURATION_IN_MILLIS));

    // then
    assertions::assertThat(busVerifier)
        .receivedMessagesOfType(1, MessageType::WEBHOOK_CALL_REQUESTED);
}

void dont_emit_webhook_call_request_when_pressing_duration_is_shorter_than_the_beginning_of_the_duration_pressing_range() {
    // when presses button for for a time that fits in pressing duration range
    etl::send_message(*bus, ButtonPressedMessage::of(0, SHORTEST_PRESSING_DURATION_IN_MILLIS - 1));

    // then
    assertions::assertThat(busVerifier)
        .receivedNoMessagesOfType(MessageType::WEBHOOK_CALL_REQUESTED);
}

void dont_emit_webhook_call_request_when_pressing_duration_is_longer_than_the_the_duration_pressing_range() {
    // when presses button for for a time that fits in pressing duration range
    etl::send_message(*bus, ButtonPressedMessage::of(0, LONGEST_PRESSING_DURATION_IN_MILLIS + 1));

    // then
    assertions::assertThat(busVerifier)
        .receivedNoMessagesOfType(MessageType::WEBHOOK_CALL_REQUESTED);
}


void setUp() {
    bus = new etl::message_bus<2>();
    buttonPressedForWebHookDetector = new ButtonPressedForWebHookDetector(*bus);
    busVerifier = new assertions::MessageBusVerifier();

    bus->subscribe(*busVerifier);
    bus->subscribe(*buttonPressedForWebHookDetector);
}

void tearDown() {
    delete buttonPressedForWebHookDetector;
    delete busVerifier;
    delete bus;
}

void execute_tests() {
    UNITY_BEGIN();

    RUN_TEST(emits_webhook_call_reuqest_when_duration_is_at_beginning_of_the_duration_pressing_range);
    RUN_TEST(emits_webhook_call_request_when_pressing_duration_is_at_most_at_the_end_of_the_duration_pressing_range);
    RUN_TEST(dont_emit_webhook_call_request_when_pressing_duration_is_shorter_than_the_beginning_of_the_duration_pressing_range);
    RUN_TEST(dont_emit_webhook_call_request_when_pressing_duration_is_longer_than_the_the_duration_pressing_range);

    UNITY_END();
}

#ifdef ARDUINO

#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(2, 3); // RX | TX

void setup() {
    //   ***  Additional Code that fixed my problem  ****
    Serial.begin(9600);
    ESPserial.begin(9600);
    delay(1000);

    Serial.println("Ready");
    ESPserial.println("AT+GMR");

    execute_tests();
}

void loop() {
}

#else

int main(int argc, char **argv) {
    execute_tests();
    return 0;
}

#endif
