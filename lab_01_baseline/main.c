#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

int main () {
    // Här sätter vi en 1 på index PB1(index 1) i DDRB registret därmed konfigurerar vi pinnen som utgång
    DDRB |= (1 << PB1);

    while (1) {
        // Vi sätter andra BITEN(PB1) i PORTB registret till 1 om andra BITEN(PB1) redan är 1 ELLER 0
        PORTB |= (1 << PB1);
        _delay_ms(500);
        // Vi sätter andra BITEN(PB1) i PORTB registret till ~1(inverterad 1 som blir 0) om andra BITEN(PB1) redan är 1
        PORTB &= ~(1 << PB1);
        _delay_ms(500);
    }
    return 0;
}
/*
//C Code Example//
#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
void main( void )
{
 ...
 USART_Init(MYUBRR)
 ...
}
void USART_Init( unsigned int ubrr)
{
 //Set baud rate//
 UBRR0H = (unsigned char)(ubrr>>8);
 UBRR0L = (unsigned char)ubrr;
 //Enable receiver and transmitter//
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 //Set frame format: 8data, 2stop bit//
 UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
*/