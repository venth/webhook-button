//
// Created by Artur Krysiak on 2019-07-01.
//

#ifndef WEBHOOK_BUTTON_INLOOPPROCESSOR_H
#define WEBHOOK_BUTTON_INLOOPPROCESSOR_H

#include <etl/message_bus.h>

class InLoopProcessor {
private:
    etl::imessage_bus *bus;
public:
    explicit InLoopProcessor(etl::imessage_bus &bus);
    ~InLoopProcessor() = default;

    void processIt();
};


#endif //WEBHOOK_BUTTON_INLOOPPROCESSOR_H
