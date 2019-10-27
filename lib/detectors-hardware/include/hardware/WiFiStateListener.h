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
    public:
        explicit WiFiStateListener(etl::imessage_bus &bus);
        ~WiFiStateListener() = default;

    };

}

#endif //WEBHOOK_BUTTON_WIFISTATELISTENER_H
