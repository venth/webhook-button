//
// Created by Artur Krysiak on 2019-07-02.
//

#ifndef WEBHOOK_BUTTON_BUTTONPRESSEDFORWIFICONFIGURATIONDETECTOR_H
#define WEBHOOK_BUTTON_BUTTONPRESSEDFORWIFICONFIGURATIONDETECTOR_H

#include <etl/message_router.h>
#include <etl/message_bus.h>

#include "button_messages.h"

class ButtonPressedForWifiConfigurationDetector : public etl::message_router<ButtonPressedForWifiConfigurationDetector, ButtonPressedMessage> {
private:
    etl::imessage_bus *bus;
public:
    static const unsigned long SHORTEST_PRESSING_DURATION_IN_MILLIS = 2500;
    static const unsigned long LONGEST_PRESSING_DURATION_IN_MILLIS = 14500;

    explicit ButtonPressedForWifiConfigurationDetector(etl::imessage_bus &bus);
    ~ButtonPressedForWifiConfigurationDetector() override = default;

    void on_receive(etl::imessage_router &sender, const ButtonPressedMessage &msg);

    void on_receive_unknown(etl::imessage_router &sender, const etl::imessage &msg);
};


#endif //WEBHOOK_BUTTON_BUTTONPRESSEDFORWIFICONFIGURATIONDETECTOR_H
