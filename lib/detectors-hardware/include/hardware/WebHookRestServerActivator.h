//
// Created by Artur Krysiak on 24/11/2019.
//

#ifndef WEBHOOK_BUTTON_WEBHOOKRESTSERVERACTIVATOR_H
#define WEBHOOK_BUTTON_WEBHOOKRESTSERVERACTIVATOR_H

#include <etl/message_router.h>
#include <ESP8266WebServer.h>

#include "button_messages.h"


namespace hardware {
    class WebHookRestServerActivator
            : public etl::message_router<WebHookRestServerActivator, WiFiClientConnectedMessage, WiFiClientDisconnectedMessage> {
    private:
        ESP8266WebServer *server;
    public:
        explicit WebHookRestServerActivator();
        ~WebHookRestServerActivator() override;

        void on_receive(etl::imessage_router &sender, const WiFiClientConnectedMessage &msg);
        void on_receive(etl::imessage_router &sender, const WiFiClientDisconnectedMessage &msg);

        void on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg);

    private:
        void handleNotFound();
    };
}

#endif //WEBHOOK_BUTTON_WEBHOOKRESTSERVERACTIVATOR_H
