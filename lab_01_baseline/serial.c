#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"


void uart_init( unsigned int ubrr){

UBRR0H = (unsigned char)(ubrr>>8);          // Set baudrate here, ubrr the parameter for your calculated baudrate //
UBRR0L = (unsigned char)ubrr;

UCSR0B = (1<<RXEN0)|(1<<TXEN0);             // Enable Receiver(RXEN0) & Enable Transmitter(TXE0) //

UCSR0C = (1<<USBS0)|(3<<UCSZ00);            // Set frame format med 8N1 som innebär //
                                            // 8 databits, N = No parityt, 1 = One stopbit. //
}

void uart_echo(void){
    uart_putchar(uart_getchar());           // Here we simply print out whatever we type in.
}


void uart_putchar( unsigned char data ){    
    /*if(data == '\r'){                     // If char 'data' == \r (which is enter key on putty) we give additional \n to make a new line //
        while (!( UCSR0A & (1<<UDRE0)));    // Wait for empty transmit buffer      //
        UDR0 = '\n';                        // Function not used at the moment, we are only looking for \n
    }
    */
    if(data == '\n'){                       // If char 'data' == \n (which is general new line char) we give additional \r to make a new line??? //
        while (!( UCSR0A & (1<<UDRE0)));    // Wait for empty transmit buffer      //
        UDR0 = '\r';
    }

    while (!( UCSR0A & (1<<UDRE0)));        // Wait for empty transmit buffer      //
    UDR0 = data;                            //Put data into buffer, sends the data //                           
}


void uart_putstr(const char *str){        
    int i = 0;
    while (str[i] != 0)                     // While the string is not null??            
    {
        uart_putchar(str[i]);               // Print out every char of the string
    i++;                                   
    }
}

unsigned char uart_getchar( void ){
    while (!(UCSR0A & (1<<RXC0)));             // Wait for data to be received //
    
    return UDR0;                               // Get and return received data from buffer //
}

/*
void USART_Flush( void ){
 unsigned char dummy;
 while ( UCSR0A & (1<<RXC) ) dummy = UDR0;
}
*/


