//
// Created by Artur Krysiak on 2019-07-01.
//

#include "ButtonPressedForWebHookDetector.h"

ButtonPressedForWebHookDetector::ButtonPressedForWebHookDetector(etl::imessage_bus &bus) : message_router(1) {
    this->bus = &bus;
}

void ButtonPressedForWebHookDetector::on_receive(etl::imessage_router &sender, const ButtonPressedMessage &msg) {
    if (msg.duration >= SHORTEST_PRESSING_DURATION_IN_MILLIS && msg.duration <= LONGEST_PRESSING_DURATION_IN_MILLIS) {
        etl::send_message(*bus, WebHookCallRequestedMessage::of(nowInMills()));
    }
}

void ButtonPressedForWebHookDetector::on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg) {

}
