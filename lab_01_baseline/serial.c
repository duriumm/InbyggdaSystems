#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "led.h"

void uart_init( unsigned int ubrr){         // Init uart by setting (calculated) baudrate and enabling RX and TX

UBRR0H = (unsigned char)(ubrr>>8);          // Set baudrate here, ubrr the parameter for your calculated baudrate //
UBRR0L = (unsigned char)ubrr;

UCSR0B = (1<<RXEN0)|(1<<TXEN0);             // Enable Receiver(RXEN0) & Enable Transmitter(TXE0) //

//UCSR0C = (1<<USBS0)|(3<<UCSZ00);          // Set frame format med 8N2 som innebär          //
                                            // 8 Databits, N = No parityt, 2 = Two stopbits. //
                                            // Default är 8N1 så vi använder inte denna      //
                                            // och då sätts frame format till 8N1.           //
}

void uart_print_currentEnumState(STATES currentEnumState){  // Prints current enum state as string based on current enum state :)
   
    if(currentEnumState == ON_STATE){
        uart_putstr("LIGHT STATE ON\n");
    }
    else if(currentEnumState == OFF_STATE){
        uart_putstr("LIGHT STATE OFF\n");
    }
    else{
        uart_putstr("Light state is not 1 or 2... it must be fucked up!!!");
    }
}

void uart_get_string_from_user(unsigned char * stringInMain){ // Gets input from user with uart_getchar() 
                                                              // until read character is \n, then null terminates
                                                              // the string and saves it to stringInMain.

    char character = 'a';

    int i = 0;
    while(character != '\n'){
        character = uart_getchar();
        stringInMain[i] = character;
        i++;
    }
    stringInMain[i] = '\0'; // Null terminate string
}

void uart_check_if_string_is_ON_or_OFF(unsigned char * stringToCheck, STATES *currentEnumState){ // Checks string saved in main.c and then changes
                                                                                                 // enum state based on what the string contains.
                                                                                                 // Then sets the string to "".

    if (strcmp(stringToCheck, "ON\r\n") == 0 && *currentEnumState != ON_STATE){ 
        strcpy(stringToCheck, "");             // Empty the string for next use //
        *currentEnumState = ON_STATE;
        uart_putstr("Led is on!\n");
    }
    else if(strcmp(stringToCheck, "OFF\r\n") == 0 && *currentEnumState != OFF_STATE){ 
        strcpy(stringToCheck, "");
        *currentEnumState = OFF_STATE;
        uart_putstr("Led is off!\n");
    }
    else{
        uart_putstr("Invalid input try the following commands below.\n"
        "1. Enter ON when the led is OFF \n2. Enter OFF when the led is ON\n");
        strcpy(stringToCheck, "");            
    }
}

void uart_echo(void){                       // Prints out what we enter in our terminal, see uart_getchar() below for more info.
    uart_putchar(uart_getchar());           
}

void uart_putchar( unsigned char data ){    // Sends one character unless it is a \n, then it sends \r
                                            
    if(data == '\n'){                       
        while (!( UCSR0A & (1<<UDRE0)));   
        UDR0 = '\r';
    }
    
    while (!( UCSR0A & (1<<UDRE0)));        // Wait for empty transmit buffer      //
    UDR0 = data;                            //Put data into buffer, sends the data //    
}

void uart_putstr(const char *str){          // Takes a "string" and loops through it untill char is 0
                                            // for every char in the loop it sends it out with uart_putchar() and then increments char in string
    int i = 0;
    while (str[i] != 0)                     // While the string is not null??            
    {
        uart_putchar(str[i]);               // Print out every char of the string
        i++;                                   
    }
}

unsigned char uart_getchar( void ){         // Returns a single char for example when user inputs in serial monitor.
    while (!(UCSR0A & (1<<RXC0)));             // Wait for data to be received //
    
    return UDR0;                               // Get and return received data from buffer //
}




