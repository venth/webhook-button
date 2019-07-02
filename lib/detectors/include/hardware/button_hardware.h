//
// Created by Artur Krysiak on 2019-06-30.
//

#ifndef WEBHOOK_BUTTON_BUTTON_HARDWARE_H
#define WEBHOOK_BUTTON_BUTTON_HARDWARE_H

#if defined(ARDUINO)

#include <Arduino.h>

#define HARDWARE_BUTTON_UP HIGH
#define HARDWARE_BUTTON_DOWN LOW

namespace hardware {
    static const uint8_t BUTTON_PIN   = D2;


}

#endif

#endif //WEBHOOK_BUTTON_BUTTON_HARDWARE_H
