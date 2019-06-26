//
// Created by Artur Krysiak on 2019-06-25.
//

#ifndef WEBHOOK_BUTTON_MESSAGES_H
#define WEBHOOK_BUTTON_MESSAGES_H

#include <etl/message.h>

enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_PRESSED,
};

struct ButtonUpMessage : public etl::message<BUTTON_UP> {
    unsigned long timestamp;
};

struct ButtonDownMessage : public etl::message<BUTTON_DOWN> {
    unsigned long timestamp;
};

struct ButtonDownPressed : public etl::message<BUTTON_PRESSED> {
    unsigned long timestamp;
    unsigned long duration;
};


#endif //WEBHOOK_BUTTON_MESSAGES_H
