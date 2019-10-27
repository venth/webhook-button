//
// Created by Artur Krysiak on 2019-07-18.
//

#include <ESP8266WiFi.h>

#include "hardware/WiFiStateListener.h"

namespace hardware {

    WiFiStateListener::WiFiStateListener(etl::imessage_bus &bus) {
        this->bus = &bus;

        //WiFi.onSoftAPModeStationConnected();
    }
}
