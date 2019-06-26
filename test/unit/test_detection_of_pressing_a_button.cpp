#include <unity.h>

#include <etl/message_bus.h>

#include "button_messages.h"
#include "ButtonPressingDetector.h"
#include "assertions/MessageBusVerifier.h"

ButtonPressingDetector *detector;
etl::imessage_bus *bus;
assertions::MessageBusVerifier *busVerifier;

void dont_emit_pressing_message_when_it_is_newly_created_and_button_was_released() {

    // when button is released
    ButtonUpMessage upMessage;
    upMessage.timestamp = 10;
    etl::send_message(*bus, upMessage);

    // then nothing was emitted to the bus
    assertions::assertThat(busVerifier)
        .receivedNoMessages();
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

    RUN_TEST(dont_emit_pressing_message_when_it_is_newly_created_and_button_was_released);

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
