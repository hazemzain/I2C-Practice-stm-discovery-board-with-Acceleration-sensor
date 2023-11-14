#include "uart.h"

void UART5_Init(void)
{
	/*0-Enable CLoc For PATH that have UART5 (APB1)*/
	RCC->CR|=(1U<<0);
	/*2-Enable RCC for Pin that allow to UART5 */
	RCC->AHB1ENR|=(1<<2);
	RCC->AHB1ENR|=(1<<3);

	/*3-Enable Altrante Funcation for this Pin RX-TX(pc12 ==TX)(PD2==RX)*/
	GPIOC->MODER|=(2<<24);
	
	GPIOC->AFR[1]|=(8<<16);

	
	GPIOD->MODER|=(2<<4);
	//CLR_BIT(GPIOD->MODER,4);
	//SET_BIT(GPIOD->MODER,5);
	GPIOD->AFR[0]|=(8<<8);

	/*1-Enable RCC for UART5*/
	RCC->APB1ENR|=(1<<20);
	/*4-Configration for UART5*/
	
			/*Word lengthWord length*/
				UART5->CR1&=~(1<<12);
				/*sampling by 16*/
				UART5->CR1&=~(1<<15);
			/* Parity control enable*/
				UART5->CR1|=(1<<10);
			/*: Parity selection*/
				UART5->CR1|=(1<<9);
			/*STOP: STOP bits one*/
				UART5->CR2&=~(1<<12);
				UART5->CR2&=~(1<<13);
			/*–PSC[4:0]: Prescaler value*/
			UART5->BRR=0x0683;
			/* TE: Transmitter enable*/
			UART5->CR1|=(1<<3);
			/* RE: Receiver enable*/
			UART5->CR1|=(1<<2);
/*: USART enable*/
		UART5->CR1|=(1<<13);
			
}
void UART5_SendCharachter(char Copy_Var)
{
	
	while(!(UART5->SR&(1<<7)));
	UART5->DR&=0;
	UART5->DR=(Copy_Var);
	//while(GET_BIT(UART5->SR,6)==0);
}
void UART5_SendString(char *arr)
{
	int i=0;
	while(arr[i]!='\0')
		{
			UART5_SendCharachter(arr[i]);
			i++;
		}
}

