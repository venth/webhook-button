//
// Created by Artur Krysiak on 2019-07-02.
//

#ifndef WEBHOOK_BUTTON_MESSAGEDUMPER_H
#define WEBHOOK_BUTTON_MESSAGEDUMPER_H

#include <etl/message_router.h>

#include "button_messages.h"

class MessageDumper : public etl::message_router<MessageDumper, ButtonUpMessage> {
public:
    MessageDumper();
    ~MessageDumper() override = default;

    bool accepts(etl::message_id_t id) const override;

    void on_receive(etl::imessage_router &sender, const ButtonUpMessage &msg);

    void on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg);
};


#endif //WEBHOOK_BUTTON_MESSAGEDUMPER_H
