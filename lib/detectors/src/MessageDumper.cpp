//
// Created by Artur Krysiak on 2019-07-02.
//

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <iostream>
#endif


#include "MessageDumper.h"

MessageDumper::MessageDumper() : message_router(1) {

}

bool MessageDumper::accepts(etl::message_id_t id) const {
    return true;
}

void MessageDumper::on_receive(etl::imessage_router &sender, const ButtonUpMessage &msg) {
#if defined(ARDUINO)
    Serial.print("Received message: ");
    Serial.println(message_to_string(msg).c_str());
#else
    std::cout << "Received message: " << message_to_string(msg) << std::endl;
#endif
}

void MessageDumper::on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg) {
#if defined(ARDUINO)
    Serial.print("Received message: ");
    Serial.println(message_to_string(msg).c_str());
#else
    std::cout << "Received message: " << message_to_string(msg) << std::endl;
#endif
}
