//
// Created by Artur Krysiak on 2019-07-18.
//

#ifndef WEBHOOK_BUTTON_WIFISTATELISTENER_H
#define WEBHOOK_BUTTON_WIFISTATELISTENER_H

#include <etl/message_bus.h>
#include "button_messages.h"

namespace hardware {

    class WiFiStateListener {
    private:
        etl::imessage_bus *bus;

        void handleOnStationModeGotIP(const WiFiEventStationModeGotIP& event);
        void handleOnStationModeDisconnected(const WiFiEventStationModeDisconnected& event);
        void handleOnSoftAPModeStationConnected(const WiFiEventSoftAPModeStationConnected& event);
        void handleOnSoftAPModeStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& event);
    public:
        explicit WiFiStateListener(etl::imessage_bus &bus);
        ~WiFiStateListener() = default;

    };

}

#endif //WEBHOOK_BUTTON_WIFISTATELISTENER_H
