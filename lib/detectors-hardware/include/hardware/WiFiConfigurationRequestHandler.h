//
// Created by Artur Krysiak on 2019-07-13.
//

#ifndef WEBHOOK_BUTTON_WIFICONFIGURATIONREQUESTHANDLER_H
#define WEBHOOK_BUTTON_WIFICONFIGURATIONREQUESTHANDLER_H

#include <etl/message_router.h>
#include <etl/message_bus.h>
#include <IPAddress.h>

#include "button_messages.h"

namespace hardware {

    class WiFiConfigurationRequestHandler
            : public etl::message_router<WiFiConfigurationRequestHandler, WifiConfigurationRequestedMessage> {
    private:
        etl::imessage_bus *bus;
        std::string *apName;
        std::string *apPassword;
        IPAddress *apAddress;
        IPAddress *apCidr;
    public:
        WiFiConfigurationRequestHandler(etl::imessage_bus &bus,
                                                 std::string &apName,
                                                 std::string &apPassword,
                                                 IPAddress &apAddress,
                                                 IPAddress &apCidr);

        ~WiFiConfigurationRequestHandler() override = default;

        void on_receive(etl::imessage_router &sender, const WifiConfigurationRequestedMessage &msg);

        void on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg);

    };
}

#endif //WEBHOOK_BUTTON_WIFICONFIGURATIONREQUESTHANDLER_H
