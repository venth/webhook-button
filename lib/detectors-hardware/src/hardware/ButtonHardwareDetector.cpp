//
// Created by Artur Krysiak on 2019-06-30.
//

#if defined(ARDUINO)

#include <Arduino.h>

#include "hardware/ButtonHardwareDetector.h"

namespace hardware {
    ButtonHardwareDetector::ButtonHardwareDetector(etl::imessage_bus &bus) : message_router(1) {
        this->bus = &bus;
    }

    void ButtonHardwareDetector::on_receive(etl::imessage_router &sender, const LoopInitiatedMessage &msg) {
        if (digitalRead(hardware::BUTTON_PIN) == HARDWARE_BUTTON_UP) {
            etl::send_message(*bus, ButtonUpMessage::of(nowInMills()));
        } else {
            etl::send_message(*bus, ButtonDownMessage::of(nowInMills()));
        }
    }

    void ButtonHardwareDetector::on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg) {

    }
}

#endif
