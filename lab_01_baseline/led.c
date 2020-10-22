#include "led.h"
#include <avr/io.h>
#include "serial.h"
#include "stateHandler.h"

void init_led(int indexInRegistry){         // Init led as "output" 

    DDRB |= (1 << indexInRegistry);     // Set a 1 to index PB1(second index) in the DDRB registry and thereby configuring the pin as output
}

void activate_led(int indexInRegistry){     // Turn the led ON
    PORTB |= (1 << indexInRegistry);    // We set the second bit(PB1) in PORTB registry to 1 if the second bit(PB1) ALREADY is 1 or 0
}

void deactivate_led(int indexInRegistry){   // Turn the led OFF
    PORTB &= ~(1 << indexInRegistry);   // We set the second bit (PB1) in PORTB registry to ~1(inverted 1 that becomes 0) IF the second bit(PB1) ALREADY is 1
}

void change_led_ON_or_OFF_based_on_state(STATES currentEnumstate){ // Turns led OFF if enum state is ON_STATE
                                                                   // Turns led OFF if enum state is OFF_STATE
    if(currentEnumstate == ON_STATE){
        activate_led(PB1);
    }
    else if(currentEnumstate == OFF_STATE){
        deactivate_led(PB1);
    }
    else{
        uart_putstr("Something went to the shitter!!! Inside led function\n");
    }
}