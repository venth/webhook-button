#include <unity.h>

#include <etl/message_bus.h>

#include "ButtonPressingDetector.h"
#include "assertions/MessageBusVerifier.h"

ButtonPressingDetector *detector;
etl::imessage_bus *bus;
assertions::MessageBusVerifier *busVerifier;

void dont_emit_pressed_message_when_it_is_newly_created_and_button_is_up() {

    // when button is up
    ButtonUpMessage upMessage;
    upMessage.timestamp = 10;
    etl::send_message(*bus, upMessage);

    // then nothing was emitted to the bus
    assertions::assertThat(busVerifier)
        .dumpMessages()
        .receivedNoMessages();
}

void dont_emit_pressed_message_when_it_is_newly_created_and_button_is_down() {

    // when button is down
    etl::send_message(*bus, ButtonDownMessage::of(10));

    // then nothing was emitted to the bus
    assertions::assertThat(busVerifier)
            .receivedNoMessages();
}

void emits_pressed_message_when_button_is_released_after_first_is_down() {
    // given button is down
    etl::send_message(*bus, ButtonDownMessage::of(10));

    // when button is up
    etl::send_message(*bus, ButtonUpMessage::of(20));

    // then emits pressed message
    assertions::assertThat(busVerifier)
            .emittedNumberOfMessages(1)
            .emittedMessageType(MessageType::BUTTON_PRESSED);

}

void calculates_duration_of_pressed_message_between_time_when_button_is_up_and_first_occurrence_when_button_was_down() {
    // given button is down
    etl::send_message(*bus, ButtonDownMessage::of(10));

    // when button is up
    etl::send_message(*bus, ButtonUpMessage::of(20));

    // then calculates duration of pressed message between up and first down message appearance
    assertions::assertThat(busVerifier)
            .emittedNumberOfMessages(1)
            .emitted(ButtonPressedMessage::of(10, 10));

}

void setUp() {
    bus = new etl::message_bus<2>();
    detector = new ButtonPressingDetector(*bus);
    busVerifier = new assertions::MessageBusVerifier();

    bus->subscribe(*detector);
    bus->subscribe(*busVerifier);
}

void tearDown() {
    delete detector;
    delete busVerifier;
    delete bus;
}

void execute_tests() {
    UNITY_BEGIN();

    RUN_TEST(dont_emit_pressed_message_when_it_is_newly_created_and_button_is_up);
    RUN_TEST(dont_emit_pressed_message_when_it_is_newly_created_and_button_is_down);
    RUN_TEST(emits_pressed_message_when_button_is_released_after_first_is_down);
    RUN_TEST(calculates_duration_of_pressed_message_between_time_when_button_is_up_and_first_occurrence_when_button_was_down);

    UNITY_END();
}


#ifdef ARDUINO

#include <Arduino.h>

void setup() {
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
