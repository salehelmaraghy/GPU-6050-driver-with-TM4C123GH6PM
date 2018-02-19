#ifndef __UART_H__
#define __UART_H__
#include"TM4C123GH6PM.h"

void uart_init(void);
void uart_send_char(unsigned char);
void uart_send_string(unsigned char* arr);
unsigned char uart_receive_char(void);

#endif