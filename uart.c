#include"uart.h"
void uart_init(void)
{
  /*PINS INITAILIZATION*/
  SYSCTL->RCGCUART=(1<<0);                      //ENABLE CLOCK GATING FOR UART0
  SYSCTL->RCGCGPIO|=(1<<0);                     //ENABLE CLOCK GATING FOR PORTA
  GPIOA->AFSEL=(1<<0)|(1<<1);                   //ENABLE ALTERNATE FUNCTION
  GPIOA->DEN=(1<<0)|(1<<1);                     //ENABLE DIGITAL ENABLE
  GPIOA->PCTL=0X00000011;                       //ENABLE UART FOR A0 AND A1 =(1<<0)|(1<<4);
  
  /*UART INITALIZATION*/
  UART0->CTL&=~(1<<0);                          //DIASABLE UART
  UART0->IBRD=104;                              //INTERGER VALUE FOR BDR BR:9600
  UART0->FBRD=11;                               //FRACTION VALUE FOR BDR BR:9600
  UART0->LCRH=(1<<6)|(1<<5);                   //WORDLENGHT=8,FIFO DISABLED, NO PARITY
  UART0->CC=0X00;                                //CLOCK SOURCE:SYSTEM CLOCK
  UART0->CTL|=(1<<0);                           //ENABLE UART
}
void uart_send_char(unsigned char number)
{
  while((UART0->FR&(1<<3)));
  UART0->DR&=0xffffff00;
  UART0->DR=number;
}
unsigned char uart_receive_char(void)
{
  unsigned char number;
  while(UART0->FR&(1<<4));
  number=UART0->DR;
  return number;
}
void uart_send_string(unsigned char* arr)
{
  int i=0;
  while(arr[i]!='\0')
  {
  uart_send_char(arr[i++]);
  }
}
