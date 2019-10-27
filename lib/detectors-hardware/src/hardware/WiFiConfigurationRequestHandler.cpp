//
// Created by Artur Krysiak on 2019-07-13.
//

#include <ESP8266WiFi.h>

#include "hardware/WiFiConfigurationRequestHandler.h"

namespace hardware {
    WiFiConfigurationRequestHandler::WiFiConfigurationRequestHandler(etl::imessage_bus &bus,
                                                                     std::string &apName,
                                                                     std::string &apPassword,
                                                                     IPAddress &apAddress,
                                                                     IPAddress &apCidr)
            : message_router(1) {
        this->bus = &bus;
        this->apName = &apName;
        this->apPassword = &apPassword;
        this->apAddress = &apAddress;
        this->apCidr = &apCidr;
    }

    void WiFiConfigurationRequestHandler::on_receive(etl::imessage_router &sender,
                                                     const WifiConfigurationRequestedMessage &msg) {
        WiFi.persistent(false);
        WiFi.disconnect(true);
        etl::send_message(*this->bus, WiFiDisconnectedMessage::of(nowInMills()));
        WiFi.mode(WIFI_AP);
        WiFi.softAPConfig(*this->apAddress, *this->apAddress, *this->apCidr);
        WiFi.softAP(this->apName->c_str(), this->apPassword->c_str());
        WiFi.begin();
    }

    void WiFiConfigurationRequestHandler::on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg) {

    }
}