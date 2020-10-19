#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

#define FOSC 16000000                   // Clockfrequency for the ATMegan
#define BAUD 38400                      // The baudrate I want 
#define MYUBRR ((FOSC / 16) / BAUD) -1  // Calculation to get the correct Baudrate for this clockfrequency
int main () {
    uart_init(MYUBRR);      // MYUBRR is the calculated and finished baudrate ready for use.

   
    DDRB |= (1 << PB1);     // Set a 1 to index PB1(second index) in the DDRB registry and thereby configuring the pin as output
                            

    while (1) {   
        /*
        _delay_ms(500);
        uart_putchar('h');
        _delay_ms(500);
        uart_putchar('\n');
        */
        _delay_ms(500);
        uart_putstr("Lasse\n"); 


        /*       
        PORTB |= (1 << PB1);    // We set the second bit(PB1) in PORTB registry to 1 if the second bit(PB1) ALREADY is 1 or 0
        _delay_ms(500);
                                // We set the secibd biut (PB1) in PORTB registry to ~1(inverted 1 that becomes 0) IF the second bit(PB1) ALREADY is 1
        PORTB &= ~(1 << PB1);  
        _delay_ms(500);
        */
    }
    return 0;
}


