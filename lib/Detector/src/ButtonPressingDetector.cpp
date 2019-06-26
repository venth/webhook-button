//
// Created by Artur Krysiak on 2019-06-25.
//

#include "ButtonPressingDetector.h"

ButtonPressingDetector::ButtonPressingDetector(etl::imessage_bus &bus) : message_router(0) {
    this->bus = &bus;
}

void ButtonPressingDetector::on_receive(etl::imessage_router &sender, const ButtonUpMessage &msg) {

}

void ButtonPressingDetector::on_receive(etl::imessage_router &sender, const ButtonDownMessage &msg) {

}

void ButtonPressingDetector::on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg) {

}
