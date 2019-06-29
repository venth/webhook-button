//
// Created by Artur Krysiak on 2019-06-25.
//

#ifndef WEBHOOK_BUTTON_MESSAGES_H
#define WEBHOOK_BUTTON_MESSAGES_H

#include <etl/message.h>
#include <iostream>

enum MessageType {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_PRESSED,

    UNKNOWN,
};

struct ButtonUpMessage : public etl::message<MessageType::BUTTON_UP> {
    unsigned long timestamp;

    static ButtonUpMessage &of(unsigned long timestamp) {
        auto obj = new ButtonUpMessage();
        obj->timestamp = timestamp;
        return *obj;
    }

};

struct ButtonDownMessage : public etl::message<MessageType::BUTTON_DOWN> {
    unsigned long timestamp;

    static ButtonDownMessage &of(unsigned long timestamp) {
        auto *obj = new ButtonDownMessage();
        obj->timestamp = timestamp;
        return *obj;
    }
};

struct ButtonPressedMessage : public etl::message<MessageType::BUTTON_PRESSED> {
    unsigned long timestamp;
    unsigned long duration;

    static ButtonPressedMessage &of(unsigned long timestamp, unsigned long duration) {
        auto *obj = new ButtonPressedMessage();
        obj->timestamp = timestamp;
        obj->duration = duration;
        return *obj;
    }
};

inline std::ostream &operator<<(std::ostream &os, const etl::imessage &s) {
    switch (s.message_id) {
        case MessageType::BUTTON_UP:
            return (os << "ButtonUpMessage { message_id: " << atoi((const char *) &(s.message_id)) << ", timestamp: "
                       << reinterpret_cast<const ButtonUpMessage *>(&s)->timestamp << " }");

        case MessageType::BUTTON_DOWN:
            return (os << "ButtonDownMessage { message_id: " << atoi((const char *) &(s.message_id)) << ", timestamp: "
                       << reinterpret_cast<const ButtonDownMessage *>(&s)->timestamp << " }");

        case MessageType::BUTTON_PRESSED:
            return (os << "ButtonPressedMessage { message_id: " << atoi((const char *) &(s.message_id))
                       << ", timstamp: "
                       << reinterpret_cast<const ButtonPressedMessage *>(&s)->timestamp
                       << ", duration: "
                       << reinterpret_cast<const ButtonPressedMessage *>(&s)->duration
                       << " }");
        default:
            return os;
    }
}

inline bool operator==(const etl::imessage &l, const etl::imessage &r) {
    if (l.message_id != r.message_id) {
        return false;
    }
    switch (l.message_id) {
        case MessageType::BUTTON_UP:
            return reinterpret_cast<const ButtonUpMessage *>(&l)->timestamp ==
                   reinterpret_cast<const ButtonUpMessage *>(&r)->timestamp;

        case MessageType::BUTTON_DOWN:
            return reinterpret_cast<const ButtonDownMessage *>(&l)->timestamp ==
                   reinterpret_cast<const ButtonDownMessage *>(&r)->timestamp;

        case MessageType::BUTTON_PRESSED:
            return reinterpret_cast<const ButtonPressedMessage *>(&l)->timestamp ==
                   reinterpret_cast<const ButtonPressedMessage *>(&r)->timestamp &&
                   reinterpret_cast<const ButtonPressedMessage *>(&l)->duration ==
                   reinterpret_cast<const ButtonPressedMessage *>(&r)->duration;
        default:
            return false;
    }
}


#endif //WEBHOOK_BUTTON_MESSAGES_H
