//
// Created by Artur Krysiak on 2019-06-25.
//

#include "ButtonPressingDetector.h"
#include <chrono>

class UpState : public etl::fsm_state<ButtonPressingDetector, UpState, ButtonState::UP_STATE, ButtonDownMessage> {
public:
    etl::fsm_state_id_t on_event(etl::imessage_router &sender, const ButtonDownMessage &event) {
        get_fsm_context().setDownTimestamp(event.timestamp);
        return ButtonState::DOWN_STATE;
    }

    etl::fsm_state_id_t on_event_unknown(etl::imessage_router &sender, const etl::imessage &event) {
        return STATE_ID;
    }
};

class DownState : public etl::fsm_state<ButtonPressingDetector, DownState, ButtonState::DOWN_STATE, ButtonUpMessage> {
public:
    etl::fsm_state_id_t on_event(etl::imessage_router &sender, const ButtonUpMessage &event) {
        get_fsm_context().emitButtonPressed(event.timestamp);
        return ButtonState::UP_STATE;
    }

    etl::fsm_state_id_t on_event_unknown(etl::imessage_router &sender, const etl::imessage &event) {
        return STATE_ID;
    }
};

ButtonPressingDetector::ButtonPressingDetector(etl::imessage_bus &bus) : fsm(1) {
    this->timestampSupplier = chronoTimestampSupplier;
    this->bus = &bus;
    this->states = new etl::ifsm_state *[ButtonState::NUMBER_OF_STATES];
    this->states[0] = new UpState();
    this->states[1] = new DownState();
    this->set_states(this->states, ButtonState::NUMBER_OF_STATES);
    this->start(false);
}

ButtonPressingDetector::ButtonPressingDetector(etl::imessage_bus &bus, TimestampSupplierFunc timestampSupplier) : fsm(1) {
    this->timestampSupplier = timestampSupplier;
    this->bus = &bus;
    this->states = new etl::ifsm_state *[ButtonState::NUMBER_OF_STATES];
    this->states[0] = new UpState();
    this->states[1] = new DownState();
    this->set_states(this->states, ButtonState::NUMBER_OF_STATES);
    this->start(false);
}

ButtonPressingDetector::~ButtonPressingDetector() {
    delete (UpState *) this->states[0];
    delete (DownState *) this->states[1];
    delete this->states;
}

unsigned long ButtonPressingDetector::currentTimestamp() {
    return this->timestampSupplier();
}

void ButtonPressingDetector::emitButtonPressed(unsigned long upTimestamp) {
    etl::send_message(*this->bus, ButtonPressedMessage::of(this->currentTimestamp(), upTimestamp - downTimestamp));
}

void ButtonPressingDetector::setDownTimestamp(unsigned long timestamp) {
    this->downTimestamp = timestamp;

}
