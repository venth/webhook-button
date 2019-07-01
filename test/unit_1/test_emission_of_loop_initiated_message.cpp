#include <unity.h>

#include <etl/message_bus.h>
#include "button_messages.h"

#include "InLoopProcessor.h"
#include "assertions/MessageBusVerifier.h"

InLoopProcessor *inLoopProcessor;
etl::imessage_bus *bus;
assertions::MessageBusVerifier *busVerifier;

void emits_loop_initiated_message_every_time_during_loop_iteration() {
    // given some iterations
    long numberOfIterations = 20;

    // when executes loop
    for (long i = 0; i < numberOfIterations; i++) {
        inLoopProcessor->processIt();
    }

    // then emits the same number of messages as loop was executed
    assertions::assertThat(busVerifier)
            .receivedMessagesOfType(numberOfIterations, MessageType::LOOP_INITIATED);
}


void setUp() {
    bus = new etl::message_bus<2>();
    inLoopProcessor = new InLoopProcessor(*bus);
    busVerifier = new assertions::MessageBusVerifier();

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
