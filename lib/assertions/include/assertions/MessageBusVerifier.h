//
// Created by Artur Krysiak on 2019-06-26.
//

#ifndef WEBHOOK_BUTTON_MESSAGEBUSVERIFIER_H
#define WEBHOOK_BUTTON_MESSAGEBUSVERIFIER_H

#include <etl/message_router.h>
#include <etl/list.h>

#include "assertions/MesssageAssertions.h"

namespace assertions {

    struct SomeMessage : public etl::message<MessageType::UNKNOWN> {};

    class MessageBusVerifier : public etl::message_router<MessageBusVerifier, SomeMessage> {
    private:
        etl::list<const etl::imessage*, 40> *messages;
    public:
        MessageBusVerifier();
        ~MessageBusVerifier() override;

        MessageAssertions& assertThat();

        bool accepts(etl::message_id_t id) const override;

        void on_receive(etl::imessage_router& sender, const ButtonUpMessage& msg);
        void on_receive(etl::imessage_router& sender, const SomeMessage& msg);
        void on_receive_unknown(etl::imessage_router& sender, const etl::imessage& msg);
    };

    MessageAssertions& assertThat(MessageBusVerifier&);
    MessageAssertions& assertThat(MessageBusVerifier*);

}


#endif //WEBHOOK_BUTTON_MESSAGEBUSVERIFIER_H
