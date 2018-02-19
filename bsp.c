/* Board Support Package */
#include "TM4C123GH6PM.h"
#include "bsp.h"

__attribute__((naked)) void assert_failed (char const *file, int line) {
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}

void SysTick_Handler(void) {
    GPIOF_AHB->DATA_Bits[LED_BLUE] ^= LED_BLUE;
}

void delay(long number)
{
    SysTick->LOAD=number;
    SysTick->VAL=0;
    SysTick->CTRL=(1<<0)|(1<<2);
    while(!(SysTick->CTRL&(1<<16)));
    SysTick->LOAD=0;
    SysTick->CTRL=0X00;
}
