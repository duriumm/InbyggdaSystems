#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

int main () {
    
    DDRB |= (1 << PB1);

    while (1) {
        PORTB |= (1 << PB1);
        _delay_ms(500);
        PORTB &= ~(1 << PB1);
        _delay_ms(500);
    }
    return 0;
}
