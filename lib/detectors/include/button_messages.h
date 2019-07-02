//
// Created by Artur Krysiak on 2019-06-25.
//

#ifndef WEBHOOK_BUTTON_MESSAGES_H
#define WEBHOOK_BUTTON_MESSAGES_H

#include <etl/message.h>
#include <chrono>
#include <string>

enum MessageType {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_PRESSED,

    LOOP_INITIATED,
    WEBHOOK_CALL_REQUESTED,
};

template<const MessageType MT_>
class BaseMessage : public etl::message<MT_> {
public:
    unsigned long timestamp;

    explicit BaseMessage(unsigned long timestamp) {
        this->timestamp = timestamp;
    }
};

struct WebHookCallRequestedMessage : public BaseMessage<MessageType::WEBHOOK_CALL_REQUESTED> {
    explicit WebHookCallRequestedMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static WebHookCallRequestedMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto obj = new WebHookCallRequestedMessage(timestampInMillis.count());
        return *obj;
    }

    static WebHookCallRequestedMessage &of(unsigned long timestamp) {
        auto obj = new WebHookCallRequestedMessage(timestamp);
        return *obj;
    }
};

struct LoopInitiatedMessage : public BaseMessage<MessageType::LOOP_INITIATED> {
    explicit LoopInitiatedMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static LoopInitiatedMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto obj = new LoopInitiatedMessage(timestampInMillis.count());
        return *obj;
    }

    static LoopInitiatedMessage &of(unsigned long timestamp) {
        auto obj = new LoopInitiatedMessage(timestamp);
        return *obj;
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


inline std::string message_to_string(const etl::imessage &s) {
    char buffer[50];
    sprintf(buffer, "%d", s.message_id);
    auto msgId = std::string(buffer);
    std::string timestamp = "";
    std::string duration = "";
    std::string os = "";
    switch (s.message_id) {
        case MessageType::WEBHOOK_CALL_REQUESTED:
            sprintf(buffer, "%ld", reinterpret_cast<const LoopInitiatedMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("WebHookCallRequested { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

        case MessageType::LOOP_INITIATED:
            sprintf(buffer, "%ld", reinterpret_cast<const LoopInitiatedMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("LoopInitiatedMessage { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

        case MessageType::BUTTON_UP:
            sprintf(buffer, "%ld", reinterpret_cast<const ButtonUpMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("ButtonUpMessage { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

        case MessageType::BUTTON_DOWN:
            sprintf(buffer, "%ld", reinterpret_cast<const ButtonDownMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("ButtonDownMessage { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

        case MessageType::BUTTON_PRESSED:
            sprintf(buffer, "%ld", reinterpret_cast<const ButtonPressedMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            sprintf(buffer, "%ld", reinterpret_cast<const ButtonPressedMessage *>(&s)->duration);
            duration = std::string(buffer);
            return os
                    .append("ButtonPressedMessage { message_id: ")
                    .append(msgId)
                    .append(", timstamp: ")
                    .append(timestamp)
                    .append(", duration: ")
                    .append(duration)
                    .append(" }");
        default:
            return os.append("");
    }
}

inline bool operator==(const etl::imessage &l, const etl::imessage &r) {
    if (l.message_id != r.message_id) {
        return false;
    }
    switch (l.message_id) {
        case MessageType::WEBHOOK_CALL_REQUESTED:
            return reinterpret_cast<const WebHookCallRequestedMessage *>(&l)->timestamp ==
                   reinterpret_cast<const WebHookCallRequestedMessage *>(&r)->timestamp;

        case MessageType::LOOP_INITIATED:
            return reinterpret_cast<const LoopInitiatedMessage *>(&l)->timestamp ==
                   reinterpret_cast<const LoopInitiatedMessage *>(&r)->timestamp;

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

inline unsigned long nowInMills() {
    auto timestamp = std::chrono::high_resolution_clock::now();
    auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
    return timestampInMillis.count();
}

#endif //WEBHOOK_BUTTON_MESSAGES_H
