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

    MessageAssertions &MessageAssertions::dumpMessages() {
        std::cout << "Messages: [ ";
        for (const auto &message : *this->messages) {
            std::cout << *message <<" , ";
        }
        std::cout << " ]" << std::endl;

        return *this;
    }

    MessageAssertions &MessageAssertions::received(etl::imessage &expectedMessage) {
        std::ostringstream os;
        os << "Expected: " << expectedMessage << " Got: " << *this->messages->front();
        TEST_ASSERT_TRUE_MESSAGE(expectedMessage == *this->messages->front(), os.str().c_str());

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

}
