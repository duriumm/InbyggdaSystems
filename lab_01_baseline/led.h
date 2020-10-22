#ifndef SERIAL_H_
#define SERIAL_H_
#include "stateHandler.h"

void init_led(int indexInRegistry);

void activate_led(int indexInRegistry);

void deactivate_led(int ledToDeactivate);

void change_led_ON_or_OFF_based_on_state(STATES currentEnumState);

#endif