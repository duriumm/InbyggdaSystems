#include "led.h"
#include <avr/io.h>

void init_led(int indexInRegistry){
    DDRB |= (1 << indexInRegistry);     // Set a 1 to index PB1(second index) in the DDRB registry and thereby configuring the pin as output
}

void activate_led(int indexInRegistry){
    PORTB |= (1 << indexInRegistry);    // We set the second bit(PB1) in PORTB registry to 1 if the second bit(PB1) ALREADY is 1 or 0
}

void deactivate_led(int indexInRegistry){
    PORTB &= ~(1 << indexInRegistry);   // We set the second bit (PB1) in PORTB registry to ~1(inverted 1 that becomes 0) IF the second bit(PB1) ALREADY is 1
}