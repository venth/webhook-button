//
// Created by Artur Krysiak on 2019-06-26.
//

#include "assertions/MessageBusVerifier.h"
#include <etl/message_router.h>


namespace assertions {

    MessageBusVerifier::MessageBusVerifier() : message_router(1) {
        this->messages = new etl::list<const etl::imessage *, 40>();
    }

    MessageBusVerifier::~MessageBusVerifier() {
        delete this->messages;
    }


    MessageAssertions &MessageBusVerifier::assertThat() {
        return *(new MessageAssertions(this->messages));
    }

    void MessageBusVerifier::on_receive(etl::imessage_router &sender, const SomeMessage &msg) {
        this->messages->push_back(&msg);
    }

    void MessageBusVerifier::on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg) {
        this->messages->push_back(&msg);
    }

    void MessageBusVerifier::on_receive(etl::imessage_router &sender, const ButtonUpMessage &msg) {
        this->messages->push_back(&msg);
    }

    bool MessageBusVerifier::accepts(etl::message_id_t id) const {
        return true;
    }

    MessageAssertions &assertThat(MessageBusVerifier &busVerifier) {
        return busVerifier.assertThat();
    }

    MessageAssertions &assertThat(MessageBusVerifier *busVerifier) {
        return assertThat(*busVerifier);
    }
}