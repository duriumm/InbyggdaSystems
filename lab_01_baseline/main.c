#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include "led.h"
#include <string.h>

#define FOSC 16000000                   // Clockfrequency for the ATMegan
#define BAUD 38400                      // The baudrate I want 
#define MYUBRR ((FOSC / 16) / BAUD) -1  // Calculation to get the correct Baudrate for this clockfrequency

char testString[20] = "NILSSON";

int main () {

    //unsigned char testString[20];
    uart_init(MYUBRR);      // MYUBRR is the calculated and finished baudrate ready for use.
    init_led(PB1);
                            

    while (1) {   
        /*
        _delay_ms(500);
        uart_putchar('h');
        _delay_ms(500);
        uart_putchar('\n');
        */
        //_delay_ms(500);




        //uart_putchar(uart_getchar());

        uart_test_with_string(uart_getchar(),testString);  // jag returnerar inget här, därför uppdateras inte värdet på testString
        //uart_echo();



        





        //uart_compare_string_with_ON(testString);
        /*
        PORTB |= (1 << PB1);    // We set the second bit(PB1) in PORTB registry to 1 if the second bit(PB1) ALREADY is 1 or 0
        _delay_ms(500);
                                
        PORTB &= ~(1 << PB1);  // We set the secibd biut (PB1) in PORTB registry to ~1(inverted 1 that becomes 0) IF the second bit(PB1) ALREADY is 1
        _delay_ms(500);
        */
        
    }
    return 0;
}


