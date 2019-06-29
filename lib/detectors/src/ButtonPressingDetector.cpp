//
// Created by Artur Krysiak on 2019-06-25.
//

#include "ButtonPressingDetector.h"

class UpState : public etl::fsm_state<ButtonPressingDetector, UpState, ButtonState::UP_STATE, ButtonDownMessage> {
public:
    etl::fsm_state_id_t on_event(etl::imessage_router &sender, const ButtonDownMessage &event) {
        return ButtonState::DOWN_STATE;
    }

    etl::fsm_state_id_t on_event_unknown(etl::imessage_router &sender, const etl::imessage &event) {
        return STATE_ID;
    }
};

class DownState : public etl::fsm_state<ButtonPressingDetector, DownState, ButtonState::DOWN_STATE, ButtonUpMessage> {
private:
    unsigned long downTimestamp;
public:
    DownState() {
        this->downTimestamp = 0;
    }

    etl::fsm_state_id_t on_event(etl::imessage_router &sender, const ButtonUpMessage &event) {
        return ButtonState::UP_STATE;
    }

    etl::fsm_state_id_t on_enter_state() override {
        this->downTimestamp = get_fsm_context().currentTimestamp();
        return STATE_ID;
    }

    void on_exit_state() override {
        get_fsm_context().emitButtonPressed(get_fsm_context().currentTimestamp() - this->downTimestamp);
    }

    etl::fsm_state_id_t on_event_unknown(etl::imessage_router &sender, const etl::imessage &event) {
        return STATE_ID;
    }
};

ButtonPressingDetector::ButtonPressingDetector(etl::imessage_bus &bus) : fsm(1) {
    this->bus = &bus;
    this->states[0] = new UpState();
    this->states[1] = new DownState();
    this->set_states(this->states, etl::size(this->states));
    this->start(false);

}

ButtonPressingDetector::~ButtonPressingDetector() {
    delete (UpState*)this->states[0];
    delete (DownState*)this->states[1];
}

unsigned long ButtonPressingDetector::currentTimestamp() {
    return 10;
}

void ButtonPressingDetector::emitButtonPressed(unsigned long duration) {
    etl::send_message(*this->bus, ButtonPressedMessage::of(this->currentTimestamp(), duration));
}
