//
// Created by Artur Krysiak on 2019-06-26.
//

#include <unity.h>

#include "assertions/MesssageAssertions.h"

namespace assertions {

    MessageAssertions::MessageAssertions(etl::ilist<const etl::imessage *> *messages) {
        this->messages = messages;
    }

    MessageAssertions &MessageAssertions::receivedNoMessages() {
        TEST_ASSERT_EQUAL(0, this->messages->size());
        return *this;
    }


}
