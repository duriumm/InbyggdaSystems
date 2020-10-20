#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "led.h"


void uart_init( unsigned int ubrr){

UBRR0H = (unsigned char)(ubrr>>8);          // Set baudrate here, ubrr the parameter for your calculated baudrate //
UBRR0L = (unsigned char)ubrr;

UCSR0B = (1<<RXEN0)|(1<<TXEN0);             // Enable Receiver(RXEN0) & Enable Transmitter(TXE0) //

UCSR0C = (1<<USBS0)|(3<<UCSZ00);            // Set frame format med 8N1 som innebär // default är 8n1 //
                                            // 8 databits, N = No parityt, 1 = One stopbit. //
}

void uart_compare_string_with_ON(unsigned char * stringToCheck){

     if (strcmp(stringToCheck, "ON\n\r") == 0){
         activate_led(PB1);
         uart_putstr("TADAAA den tändes!!");
     }
     else{
         uart_putstr("strengen e skum...!");
         //uart_putstr(stringToCheck);        // string here turns out empty.. and fucks program up with putty
     }

}

void uart_echo(void){
    uart_putchar(uart_getchar());           // Here we simply print out whatever we type in.
}


void uart_putchar( unsigned char data ){  

    if(data == '\r'){                     // If char 'data' == \r (which is enter key on putty) we give additional \n to make a new line //
        while (!( UCSR0A & (1<<UDRE0)));    // Wait for empty transmit buffer      //
        UDR0 = '\n';                        // Function not used at the moment, we are only looking for \n
    }
    
    /*
    if(data == '\n'){                       // If char 'data' == \n (which is general new line char) we give additional \r to make a new line??? //
        while (!( UCSR0A & (1<<UDRE0)));    // Wait for empty transmit buffer      //
        UDR0 = '\r';
    }
    */

    while (!( UCSR0A & (1<<UDRE0)));        // Wait for empty transmit buffer      //
    UDR0 = data;                            //Put data into buffer, sends the data //  
    
}

void uart_test_with_string( unsigned char character , char * string){  
 
    if(character == '\r'){                  // If char 'data' == \r (which is enter key on putty) we give additional \n to make a new line //
        while (!( UCSR0A & (1<<UDRE0)));    // BEHÖVS DENNA ENS???? testade utan och det funkade bra
        //strncat(string, '\n', 1);           // Add \n to string, so should look line str + /n + /r now    //   
        

        if (strcmp(string, "\rkorv") == 0){ // WITH ONLY \R IT WORKS!! IF I TRY TO DD \N LIKE ABOVE (ROW 60) IT DOESNT WORK!! //
            activate_led(PB1);
            uart_putstr("TADAAA den tändes!!");
        }
        else if(strcmp(string, "\rburger") == 0){ 
            deactivate_led(PB1);
            uart_putstr("Lampis e av!!");
        }
        else{
         uart_putstr("strengen e skum...!");
         uart_putstr(string);               // string here turns out empty.. and fucks program up with putty
        }
        //UDR0 = '\n';                      // IF i have this enabled i get double new lines
        strcpy(string, "");                 // Erase the string so next time its clean
    }
    /*
    else if(character == '\n'){             // If char 'data' == \n (which is general new line char) we give additional \r to make a new line??? //
        while (!( UCSR0A & (1<<UDRE0)));    // Wait for empty transmit buffer      //
        strncat(string, '\r', 1); 
        UDR0 = '\r';
        uart_putstr("inne i slash n funktion!");
    }
    */

    while (!( UCSR0A & (1<<UDRE0)));         // BEHÖVS DENNA ENS???? testade utan och det funkade bra
    strncat(string, &character, 1);         // DENNA LÄGGER FAKTISKT TILL DOM I originalSTRÄNGEN testString i main               
    UDR0 = character;                       // Put data into buffer, sends the data //  
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

void uart_savechar(const char * stringToSaveInto, unsigned char inputChar){

    strcat(stringToSaveInto, inputChar);
}

/*
unsigned char uart_getstr()
{
    char testString[] = "";
    strcpy(testString, "");
    uart_getchar();

    return temporaryString;
}
*/

/*
void USART_Flush( void ){
 unsigned char dummy;
 while ( UCSR0A & (1<<RXC) ) dummy = UDR0;
}
*/


