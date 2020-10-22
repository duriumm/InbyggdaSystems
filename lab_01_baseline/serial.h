#ifndef SERIAL_H_
#define SERIAL_H_
#include "stateHandler.h"


void uart_init(unsigned int ubbr);

void uart_putchar(unsigned char chr);

void uart_putstr(const char *str);

unsigned char uart_getchar(void);

void uart_echo(void);

void uart_check_if_string_is_ON_or_OFF( unsigned char * stringToCheck, STATES *currentEnumState);

void uart_get_string_from_user(unsigned char * stringToCheck);

void uart_print_currentEnumState(STATES currentEnumState);

#endif

