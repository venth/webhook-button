//
// Created by Artur Krysiak on 2019-06-25.
//

#ifndef WEBHOOK_BUTTON_BUTTONPRESSINGDETECTOR_HA
#define WEBHOOK_BUTTON_BUTTONPRESSINGDETECTOR_HA

#include <etl/fsm.h>
#include <etl/message_bus.h>

#include "button_messages.h"

enum ButtonState {
    UP_STATE,
    DOWN_STATE,
    NUMBER_OF_STATES,
};

class ButtonPressingDetector : public etl::fsm {
private:
    etl::imessage_bus *bus;
    etl::ifsm_state **states;
    unsigned long downTimestamp;
public:
    explicit ButtonPressingDetector(etl::imessage_bus &bus);
    ~ButtonPressingDetector() override;

    unsigned long currentTimestamp();
    void emitButtonPressed(unsigned long upTimestamp);
    void setDownTimestamp(unsigned long downTimestamp);
};


#endif //WEBHOOK_BUTTON_BUTTONPRESSINGDETECTOR_HA
