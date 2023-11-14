#ifndef _UART_H
#define _UART_H
#include "stm32f4xx.h"  

 #define SET__BIT(REG , BITNUM) REG |= 1U<<BITNUM
 #define CLR_BIT(REG , BITNUM) REG &= ~(1U<<BITNUM)
 #define TOG_BIT(REG , BITNUM) REG ^= 1U<<BITNUM
 #define GET_BIT(REG , BITNUM) ( (REG >> BITNUM) & 1U )
void UART5_Init(void);
void UART5_SendCharachter(char Copy_Var);
void UART5_SendString(char *arr);


#endif
