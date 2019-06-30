//
// Created by Artur Krysiak on 2019-06-26.
//

#include <unity.h>
#include <sstream>
#include <string>

#include "assertions/MesssageAssertions.h"

#include "button_messages.h"

namespace assertions {

    MessageAssertions::MessageAssertions(etl::ilist<const etl::imessage *> *messages) {
        this->messages = messages;
    }

    MessageAssertions &MessageAssertions::received(etl::imessage &expectedMessage) {
        bool matched = false;

        for (auto &item : *this->messages) {
            if (*item == expectedMessage) {
                matched = true;
                break;
            }
        }

        std::string msg;
        msg
                .append("Expected: ")
                .append(message_to_string(expectedMessage))
                .append(" Got: ");

        for (auto &item : *this->messages) {
            msg
                    .append(message_to_string(*item))
                    .append(", ");
        }


        TEST_ASSERT_TRUE_MESSAGE(matched, msg.c_str());

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

        char buffer[40];
        std::string msg = "Expected receiving ";
        sprintf(buffer, "%ld", count);
        msg.append(buffer);
        msg.append(" messages. Was: ");
        sprintf(buffer, "%ld", matched);
        msg.append(buffer);
        msg.append(" Collected messages: ");
        for (auto &item : *this->messages) {
            msg
                    .append(message_to_string(*item))
                    .append(", ");
        }

        TEST_ASSERT_EQUAL_MESSAGE(count, matched, msg.c_str());
        return *this;
    }
}
