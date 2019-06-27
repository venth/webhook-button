//
// Created by Artur Krysiak on 2019-06-26.
//

#include <unity.h>
#include <iostream>
#include <sstream>

#include "assertions/MesssageAssertions.h"

#include "button_messages.h"

namespace assertions {

    MessageAssertions::MessageAssertions(etl::ilist<const etl::imessage *> *messages) {
        this->messages = messages;
    }

    MessageAssertions &MessageAssertions::receivedNoMessages() {
        std::ostringstream os;
        os << "Expected receiving none messages. Was: " << this->messages->size();
        TEST_ASSERT_EQUAL_MESSAGE(0, this->messages->size(), os.str().c_str());
        return *this;
    }

    MessageAssertions &MessageAssertions::dumpMessages() {
        std::cout << "Messages: [ ";
        for (const auto &message : *this->messages) {
            std::cout << *message <<" , ";
        }
        std::cout << " ]" << std::endl;

        return *this;
    }

    MessageAssertions &MessageAssertions::emittedNumberOfMessages(unsigned int expectedNumberOfMessages) {
        std::ostringstream os;
        os << "Expected receiving: " << expectedNumberOfMessages << " messages. Was: " << this->messages->size();
        TEST_ASSERT_EQUAL_MESSAGE(expectedNumberOfMessages, this->messages->size(), os.str().c_str());
        return *this;
    }

    MessageAssertions &MessageAssertions::emittedMessageType(MessageType expectedMessageType) {
        std::ostringstream os;
        os << "Expected message type: " << expectedMessageType << ". Was: " << this->messages->front()->message_id;
        TEST_ASSERT_EQUAL_MESSAGE(expectedMessageType, this->messages->front()->message_id, os.str().c_str());
        return *this;
    }

    MessageAssertions &MessageAssertions::emitted(etl::imessage &expectedMessage) {
        std::ostringstream os;
        os << "Expected: " << expectedMessage << " Got: " << *this->messages->front();
        TEST_ASSERT_TRUE_MESSAGE(expectedMessage == *this->messages->front(), os.str().c_str());

        return *this;
    }

}
