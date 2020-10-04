//
// Created by Artur Krysiak on 24/11/2019.
//

#include "hardware/WebHookRestServerActivator.h"

namespace hardware {

    WebHookRestServerActivator::WebHookRestServerActivator() : message_router(1) {
        server = new ESP8266WebServer(IP_ADDR_ANY, 80);
        server->onNotFound([&]() { this->handleNotFound(); });
    }

    WebHookRestServerActivator::~WebHookRestServerActivator() {
        delete server;
    }

    void WebHookRestServerActivator::on_receive(etl::imessage_router &sender, const WiFiClientConnectedMessage &msg) {
        server->stop();
        server->begin();
    }

    void
    WebHookRestServerActivator::on_receive(etl::imessage_router &sender, const WiFiClientDisconnectedMessage &msg) {
        server->stop();
    }

    void WebHookRestServerActivator::on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg) {
    }

    void WebHookRestServerActivator::handleNotFound() {
        server->send(404, "application/json; charset=utf-8",
                     R"({ "error": { "code": "404", "message": "There is not such resource" }})");
    }
}
