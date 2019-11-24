//
// Created by Artur Krysiak on 2019-07-18.
//

#include <ESP8266WiFi.h>

#include "hardware/WiFiStateListener.h"
#include <button_messages.h>

namespace hardware {

    WiFiStateListener::WiFiStateListener(etl::imessage_bus &bus) {
        this->bus = &bus;

        WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP& event) { this->handleOnStationModeGotIP(event); });
        WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected& event) { this->handleOnStationModeDisconnected(event); });
        WiFi.onSoftAPModeStationConnected([this](const WiFiEventSoftAPModeStationConnected& event) { this->handleOnSoftAPModeStationConnected(event); });
        WiFi.onSoftAPModeStationDisconnected([this](const WiFiEventSoftAPModeStationDisconnected& event) { this->handleOnSoftAPModeStationDisconnected(event); });
    }

    void WiFiStateListener::handleOnStationModeGotIP(const WiFiEventStationModeGotIP& event) {
        etl::send_message(*bus, WiFiClientConnectedMessage::of(nowInMills()));
    }

    void WiFiStateListener::handleOnStationModeDisconnected(const WiFiEventStationModeDisconnected& event) {
        etl::send_message(*bus, WiFiClientDisconnectedMessage::of(nowInMills()));
    }

    void WiFiStateListener::handleOnSoftAPModeStationConnected(const WiFiEventSoftAPModeStationConnected& event) {

    }

    void WiFiStateListener::handleOnSoftAPModeStationDisconnected(const WiFiEventSoftAPModeStationDisconnected &event){

    }
}
