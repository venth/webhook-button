//
// Created by Artur Krysiak on 2019-06-26.
//

#ifndef WEBHOOK_BUTTON_MESSSAGEASSERTIONS_H
#define WEBHOOK_BUTTON_MESSSAGEASSERTIONS_H

#include <etl/message.h>
#include <etl/list.h>

#include "button_messages.h"

namespace assertions {

    class MessageAssertions {
    private:
        etl::ilist<const etl::imessage *> *messages;

    protected:
        std::ostream &dumpMessages(std::ostream & os);
    public:
        explicit MessageAssertions(etl::ilist<const etl::imessage*> *);

        MessageAssertions& receivedNoMessagesOfType(MessageType expectedMessageType);
        MessageAssertions& receivedMessagesOfType(long count, MessageType expectedMessageType);
        MessageAssertions& received(etl::imessage &expectedMessage);

        friend std::ostream &operator<<(std::ostream &os, MessageAssertions s);
    };
}

#endif //WEBHOOK_BUTTON_MESSSAGEASSERTIONS_H
