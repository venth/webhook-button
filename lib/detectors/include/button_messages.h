//
// Created by Artur Krysiak on 2019-06-25.
//

#ifndef WEBHOOK_BUTTON_MESSAGES_H
#define WEBHOOK_BUTTON_MESSAGES_H

#include <etl/message.h>
#include <chrono>
#include <string>
#include <stdio.h>

enum MessageType {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_PRESSED,

    LOOP_INITIATED,
    WEBHOOK_CALL_REQUESTED,
    WIFI_CONFIGURATION_REQUESTED,
    WIFI_CLIENT_DISCONNECTED,
    WIFI_CLIENT_CONNECTED,
    WIFI_ACCESS_POINT_ACTIVATED,
    WIFI_ACCESS_POINT_DE_ACTIVATED,
};

template<const MessageType MT_>
class BaseMessage : public etl::message<MT_> {
public:
    unsigned long timestamp;

    explicit BaseMessage(unsigned long timestamp) {
        this->timestamp = timestamp;
    }
};

struct WiFiAccessPointActivatedMessage : public BaseMessage<MessageType::WIFI_ACCESS_POINT_ACTIVATED> {
    explicit WiFiAccessPointActivatedMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static WiFiAccessPointActivatedMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto obj = new WiFiAccessPointActivatedMessage(timestampInMillis.count());
        return *obj;
    }

    static WiFiAccessPointActivatedMessage &of(unsigned long timestamp) {
        auto obj = new WiFiAccessPointActivatedMessage(timestamp);
        return *obj;
    }
};

struct WiFiAccessPointDeActivatedMessage : public BaseMessage<MessageType::WIFI_ACCESS_POINT_DE_ACTIVATED> {
    explicit WiFiAccessPointDeActivatedMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static WiFiAccessPointDeActivatedMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto obj = new WiFiAccessPointDeActivatedMessage(timestampInMillis.count());
        return *obj;
    }

    static WiFiAccessPointDeActivatedMessage &of(unsigned long timestamp) {
        auto obj = new WiFiAccessPointDeActivatedMessage(timestamp);
        return *obj;
    }
};

struct WiFiClientDisconnectedMessage : public BaseMessage<MessageType::WIFI_CLIENT_DISCONNECTED> {
    explicit WiFiClientDisconnectedMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static WiFiClientDisconnectedMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto obj = new WiFiClientDisconnectedMessage(timestampInMillis.count());
        return *obj;
    }

    static WiFiClientDisconnectedMessage &of(unsigned long timestamp) {
        auto obj = new WiFiClientDisconnectedMessage(timestamp);
        return *obj;
    }
};

struct WiFiClientConnectedMessage : public BaseMessage<MessageType::WIFI_CLIENT_CONNECTED> {
    explicit WiFiClientConnectedMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static WiFiClientConnectedMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto obj = new WiFiClientConnectedMessage(timestampInMillis.count());
        return *obj;
    }

    static WiFiClientConnectedMessage &of(unsigned long timestamp) {
        auto obj = new WiFiClientConnectedMessage(timestamp);
        return *obj;
    }
};

struct WifiConfigurationRequestedMessage : public BaseMessage<MessageType::WIFI_CONFIGURATION_REQUESTED> {
    explicit WifiConfigurationRequestedMessage(unsigned long timestamp) : BaseMessage(timestamp) {}

    static WifiConfigurationRequestedMessage &of(std::chrono::system_clock::time_point &timestamp) {
        auto timestampInMillis = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp.time_since_epoch());
        auto obj = new WifiConfigurationRequestedMessage(timestampInMillis.count());
        return *obj;
    }

    static WifiConfigurationRequestedMessage &of(unsigned long timestamp) {
        auto obj = new WifiConfigurationRequestedMessage(timestamp);
        return *obj;
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
        case MessageType::WIFI_ACCESS_POINT_ACTIVATED:
            sprintf(buffer, "%ld", reinterpret_cast<const LoopInitiatedMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("WiFiAccessPointActivatedMessage { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

        case MessageType::WIFI_ACCESS_POINT_DE_ACTIVATED:
            sprintf(buffer, "%ld", reinterpret_cast<const LoopInitiatedMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("WiFiAccessPointDeActivatedMessage { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

        case MessageType::WIFI_CLIENT_CONNECTED:
            sprintf(buffer, "%ld", reinterpret_cast<const LoopInitiatedMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("WiFiClientConnectedMessage { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

        case MessageType::WIFI_CLIENT_DISCONNECTED:
            sprintf(buffer, "%ld", reinterpret_cast<const LoopInitiatedMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("WiFiClientDisconnectedMessage { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

        case MessageType::WIFI_CONFIGURATION_REQUESTED:
            sprintf(buffer, "%ld", reinterpret_cast<const LoopInitiatedMessage *>(&s)->timestamp);
            timestamp = std::string(buffer);
            return os
                    .append("WifiConfigurationRequestedMessage { message_id: ")
                    .append(msgId)
                    .append(", timestamp: ")
                    .append(timestamp)
                    .append(" }");

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
        case MessageType::WIFI_ACCESS_POINT_DE_ACTIVATED:
            return reinterpret_cast<const WiFiAccessPointDeActivatedMessage *>(&l)->timestamp ==
                   reinterpret_cast<const WiFiAccessPointDeActivatedMessage *>(&r)->timestamp;

        case MessageType::WIFI_ACCESS_POINT_ACTIVATED:
            return reinterpret_cast<const WiFiAccessPointActivatedMessage *>(&l)->timestamp ==
                   reinterpret_cast<const WiFiAccessPointActivatedMessage *>(&r)->timestamp;

        case MessageType::WIFI_CLIENT_CONNECTED:
            return reinterpret_cast<const WiFiClientConnectedMessage *>(&l)->timestamp ==
                   reinterpret_cast<const WiFiClientConnectedMessage *>(&r)->timestamp;

        case MessageType::WIFI_CLIENT_DISCONNECTED:
            return reinterpret_cast<const WiFiClientDisconnectedMessage *>(&l)->timestamp ==
                   reinterpret_cast<const WiFiClientDisconnectedMessage *>(&r)->timestamp;

        case MessageType::WIFI_CONFIGURATION_REQUESTED:
            return reinterpret_cast<const WifiConfigurationRequestedMessage *>(&l)->timestamp ==
                   reinterpret_cast<const WifiConfigurationRequestedMessage *>(&r)->timestamp;

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
