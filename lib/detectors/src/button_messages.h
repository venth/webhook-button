//
// Created by Artur Krysiak on 2019-06-25.
//

#ifndef WEBHOOK_BUTTON_MESSAGES_H
#define WEBHOOK_BUTTON_MESSAGES_H

#include <etl/message.h>
#include <iostream>
#include <chrono>

enum MessageType {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_PRESSED,

    UNKNOWN,
};

template<const MessageType MT_>
class BaseMessage : public etl::message<MT_> {
public:
    unsigned long timestamp;

    explicit BaseMessage(unsigned long timestamp) {
        this->timestamp = timestamp;
    }
};

struct ButtonUpMessage : public BaseMessage<MessageType::BUTTON_UP> {

    explicit ButtonUpMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static ButtonUpMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto obj = new ButtonUpMessage(timestampInMillis.count());
        return *obj;
    }

    static ButtonUpMessage &of(unsigned long timestamp) {
        auto obj = new ButtonUpMessage(timestamp);
        return *obj;
    }

};

struct ButtonDownMessage : public BaseMessage<MessageType::BUTTON_DOWN> {

    explicit ButtonDownMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static ButtonDownMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto *obj = new ButtonDownMessage(timestampInMillis.count());
        return *obj;
    }

    static ButtonDownMessage &of(unsigned long timestamp) {
        auto *obj = new ButtonDownMessage(timestamp);
        return *obj;
    }
};

struct ButtonPressedMessage : public BaseMessage<MessageType::BUTTON_PRESSED> {
    unsigned long duration;

    ButtonPressedMessage(unsigned long timestamp, unsigned long duration) : BaseMessage(0) {
        this->duration = duration;
    }

    static ButtonPressedMessage &
    of(std::chrono::system_clock::time_point &timestamp, std::chrono::milliseconds &duration) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto *obj = new ButtonPressedMessage(timestampInMillis.count(), duration.count());
        return *obj;
    }

    static ButtonPressedMessage &
    of(unsigned long timestamp, unsigned long duration) {
        auto *obj = new ButtonPressedMessage(timestamp, duration);
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


typedef unsigned long (*TimestampSupplierFunc)();

static unsigned long chronoTimestampSupplier() {
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch());
    return timestamp.count();
}

#endif //WEBHOOK_BUTTON_MESSAGES_H
