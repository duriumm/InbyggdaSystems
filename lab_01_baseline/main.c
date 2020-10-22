#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include "led.h"
#include <string.h>
#include "stateHandler.h"

#define FOSC 16000000                   // Clockfrequency for the ATMegan
#define BAUD 38400                      // The baudrate I want 
#define MYUBRR ((FOSC / 16) / BAUD) -1  // Calculation to get the correct Baudrate for this clockfrequency

char stringInputFromUser[50] = "";

int main () {

  uart_init(MYUBRR);      // MYUBRR is the calculated and finished baudrate ready for use. Enabling rx/tx. 
  init_led(PB1);          // Init led 
  STATES currentEnumState = OFF_STATE;

  while (1) {   

      uart_get_string_from_user(stringInputFromUser); // Get the text string from user, one char at a time //
      //uart_putstr(stringInputFromUser);               // Print out what you just typed in //
  
      uart_check_if_string_is_ON_or_OFF(stringInputFromUser, &currentEnumState); // Enum state = ON_STATE if string == "ON"   //
                                                                                 // Enum state = OFF_STATE if string == "OFF" //
      //uart_print_currentEnumState(currentEnumState);                           // Prints out the current Enum state         //
      change_led_ON_or_OFF_based_on_state(currentEnumState);                     // Turns the led ON or OFF based on the current enum state //
      
  }
  return 0;
}


