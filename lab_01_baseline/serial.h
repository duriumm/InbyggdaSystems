#ifndef SERIAL_H_
#define SERIAL_H_

//void uart_init(void);
void uart_init(unsigned int ubbr);

void uart_putchar(unsigned char chr);
void uart_putstr(const char *str);

unsigned char uart_getchar(void);

void uart_echo(void);

unsigned char uart_getstr(void);

void uart_savechar(const char * stringToSaveInto, unsigned char inputChar);

void uart_test_with_string( unsigned char data, char * stringTest);

void uart_checkForON( unsigned char * stringToCheck);

#endif

