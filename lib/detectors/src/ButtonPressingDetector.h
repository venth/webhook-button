//
// Created by Artur Krysiak on 2019-06-25.
//

#ifndef WEBHOOK_BUTTON_BUTTONPRESSINGDETECTOR_H
#define WEBHOOK_BUTTON_BUTTONPRESSINGDETECTOR_H

#include <etl/message_router.h>
#include <etl/message_bus.h>

#include "button_messages.h"

class ButtonPressingDetector : public etl::message_router<ButtonPressingDetector, ButtonUpMessage, ButtonDownMessage> {
private:
    etl::imessage_bus *bus;

public:
    explicit ButtonPressingDetector(etl::imessage_bus &bus);

    void on_receive(etl::imessage_router& sender, const ButtonUpMessage& msg);
    void on_receive(etl::imessage_router& sender, const ButtonDownMessage& msg);

    void on_receive_unknown(etl::imessage_router& sender, const etl::imessage& msg);
};


#endif //WEBHOOK_BUTTON_BUTTONPRESSINGDETECTOR_H
