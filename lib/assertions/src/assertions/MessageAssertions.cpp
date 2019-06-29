//
// Created by Artur Krysiak on 2019-06-26.
//

#include <unity.h>
#include <sstream>
#include <iostream>

#include "assertions/MesssageAssertions.h"

#include "button_messages.h"

namespace assertions {

    MessageAssertions::MessageAssertions(etl::ilist<const etl::imessage *> *messages) {
        this->messages = messages;
    }

    std::ostream &MessageAssertions::dumpMessages(std::ostream &os) {
        os << "Messages: [ ";
        for (const auto &message : *this->messages) {
            os << *message <<" , ";
        }
        os << " ]";

        return os;
    }

    MessageAssertions &MessageAssertions::received(etl::imessage &expectedMessage) {
        bool matched = false;

        for (auto &item : *this->messages) {
            if (*item == expectedMessage) {
                matched = true;
                break;
            }
        }

        std::ostringstream os;
        os << "Expected: " << expectedMessage << " Got: " << *this;
        TEST_ASSERT_TRUE_MESSAGE(matched, os.str().c_str());

        return *this;
    }

    MessageAssertions &MessageAssertions::receivedNoMessagesOfType(MessageType expectedMessageType) {
        return this->receivedMessagesOfType(0, expectedMessageType);
    }

    MessageAssertions &MessageAssertions::receivedMessagesOfType(long count, MessageType expectedMessageType) {
        long matched = false;
        for (const auto &item : *this->messages) {
            if (item->message_id == expectedMessageType) {
                matched++;
            }
        }

        std::ostringstream os;
        os << "Expected receiving " << count << " messages. Was: " << matched;
        TEST_ASSERT_EQUAL_MESSAGE(count, matched, os.str().c_str());
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, MessageAssertions s) {
        return s.dumpMessages(os);
    }

}
