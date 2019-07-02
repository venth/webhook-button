//
// Created by Artur Krysiak on 2019-07-02.
//

#include "ButtonPressedForWifiConfigurationDetector.h"

ButtonPressedForWifiConfigurationDetector::ButtonPressedForWifiConfigurationDetector(etl::imessage_bus &bus)
        : message_router(1) {
    this->bus = &bus;
}

void
ButtonPressedForWifiConfigurationDetector::on_receive(etl::imessage_router &sender, const ButtonPressedMessage &msg) {
    if (msg.duration >= ButtonPressedForWifiConfigurationDetector::SHORTEST_PRESSING_DURATION_IN_MILLIS &&
        msg.duration <= ButtonPressedForWifiConfigurationDetector::LONGEST_PRESSING_DURATION_IN_MILLIS) {
        etl::send_message(*bus, WifiConfigurationRequestedMessage::of(nowInMills()));
    }
}

void
ButtonPressedForWifiConfigurationDetector::on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg) {

}
