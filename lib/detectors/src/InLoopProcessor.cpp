//
// Created by Artur Krysiak on 2019-07-01.
//


#include "InLoopProcessor.h"

#include "button_messages.h"

InLoopProcessor::InLoopProcessor(etl::imessage_bus &bus) {
    this->bus = &bus;
}

void InLoopProcessor::processIt() {
    etl::send_message(*this->bus, LoopInitiatedMessage::of(nowInMills()));
}
