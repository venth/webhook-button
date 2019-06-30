//
// Created by Artur Krysiak on 2019-06-30.
//

#ifndef WEBHOOK_BUTTON_BUTTONHARDWAREDETECTOR_H
#define WEBHOOK_BUTTON_BUTTONHARDWAREDETECTOR_H

#if defined(ARDUINO)

#include <etl/message_bus.h>
#include <etl/message_router.h>

#include "button_messages.h"
#include "hardware/button_hardware.h"

class ButtonHardwareDetector : public etl::message_router<ButtonHardwareDetector, LoopInitiatedMessage> {
private:
    etl::imessage_bus *bus;
public:
    explicit ButtonHardwareDetector(etl::imessage_bus &bus);
    ~ButtonHardwareDetector() override = default;

    void on_receive(etl::imessage_router &sender, const LoopInitiatedMessage &msg);

    void on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg);
};

#endif

#endif //WEBHOOK_BUTTON_BUTTONHARDWAREDETECTOR_H
