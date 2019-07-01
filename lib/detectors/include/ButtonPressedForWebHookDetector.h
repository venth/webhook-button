//
// Created by Artur Krysiak on 2019-07-01.
//

#ifndef WEBHOOK_BUTTON_BUTTONPRESSEDFORWEBHOOKDETECTOR_H
#define WEBHOOK_BUTTON_BUTTONPRESSEDFORWEBHOOKDETECTOR_H

#include <etl/message_router.h>
#include <etl/message_bus.h>

#include "button_messages.h"

class ButtonPressedForWebHookDetector
        : public etl::message_router<ButtonPressedForWebHookDetector, ButtonPressedMessage> {
private:
    etl::imessage_bus *bus;
public:
    explicit ButtonPressedForWebHookDetector(etl::imessage_bus &bus);

    ~ButtonPressedForWebHookDetector() override = default;

    void on_receive(etl::imessage_router &sender, const ButtonPressedMessage &msg);

    void on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg);

};


#endif //WEBHOOK_BUTTON_BUTTONPRESSEDFORWEBHOOKDETECTOR_H
