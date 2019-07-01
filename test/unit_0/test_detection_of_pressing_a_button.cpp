#include <unity.h>

#include <etl/message_bus.h>
#include "button_messages.h"

#include "ButtonPressingDetector.h"
#include "assertions/MessageBusVerifier.h"

ButtonPressingDetector *inLoopProcessor;
etl::imessage_bus *bus;
assertions::MessageBusVerifier *busVerifier;

void emits_loop_initiated_message_every_time_during_loop_iteration() {

    // when button is up
    etl::send_message(*bus, ButtonUpMessage::of(10));

    // then nothing was received to the bus
    assertions::assertThat(busVerifier)
            .receivedNoMessagesOfType(MessageType::BUTTON_PRESSED);
}

void dont_emit_pressed_message_when_it_is_newly_created_and_button_is_down() {

    // when button is down
    etl::send_message(*bus, ButtonDownMessage::of(10));

    // then nothing was received to the bus
    assertions::assertThat(busVerifier)
            .receivedNoMessagesOfType(MessageType::BUTTON_PRESSED);
}

void emits_pressed_message_when_button_is_released_after_first_is_down() {
    // given button is down
    etl::send_message(*bus, ButtonDownMessage::of(10));

    // when button is up
    etl::send_message(*bus, ButtonUpMessage::of(20));

    // then emits pressed message
    assertions::assertThat(busVerifier)
            .receivedMessagesOfType(1, MessageType::BUTTON_PRESSED);

}

void calculates_duration_of_pressed_message_between_time_when_button_is_up_and_first_occurrence_when_button_was_down() {
    // given button is down
    etl::send_message(*bus, ButtonDownMessage::of(10));

    // when button is up
    etl::send_message(*bus, ButtonUpMessage::of(30));

    // then calculates duration of pressed message between up and first down message appearance
    assertions::assertThat(busVerifier)
            .receivedMessagesOfType(1, MessageType::BUTTON_PRESSED)
            .received(ButtonPressedMessage::of(10, 20));
}

void calculates_duration_of_pressed_message_between_time_when_button_is_up_and_first_occurrence_when_button_was_down_despite_of_many_down_after_first() {
    // given button is down
    etl::send_message(*bus, ButtonDownMessage::of(10));

    // and button is down
    etl::send_message(*bus, ButtonDownMessage::of(12));

    // and button is down
    etl::send_message(*bus, ButtonDownMessage::of(14));

    // and button is down
    etl::send_message(*bus, ButtonDownMessage::of(20));

    // when button is up
    etl::send_message(*bus, ButtonUpMessage::of(30));

    // then calculates duration of pressed message between up and first down message appearance
    assertions::assertThat(busVerifier)
            .receivedMessagesOfType(1, MessageType::BUTTON_PRESSED)
            .received(ButtonPressedMessage::of(10, 20));
}

void setUp() {
    bus = new etl::message_bus<2>();
    inLoopProcessor = new ButtonPressingDetector(*bus);
    busVerifier = new assertions::MessageBusVerifier();

    bus->subscribe(*inLoopProcessor);
    bus->subscribe(*busVerifier);
}

void tearDown() {
    delete inLoopProcessor;
    delete busVerifier;
    delete bus;
}

void execute_tests() {
    UNITY_BEGIN();

    RUN_TEST(emits_loop_initiated_message_every_time_during_loop_iteration);
    RUN_TEST(dont_emit_pressed_message_when_it_is_newly_created_and_button_is_down);
    RUN_TEST(emits_pressed_message_when_button_is_released_after_first_is_down);
    RUN_TEST(calculates_duration_of_pressed_message_between_time_when_button_is_up_and_first_occurrence_when_button_was_down);
    RUN_TEST(calculates_duration_of_pressed_message_between_time_when_button_is_up_and_first_occurrence_when_button_was_down_despite_of_many_down_after_first);

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
