#include "uart.h"
#include <stdio.h>
#include "ADXL345.h"
extern uint8_t data[6];
int16_t x,y,z;
int main(){
	
	char arr[]="hello hazem cosoooo = ";
	UART5_Init();
	ADXL_Init();
	
	while(1)
			{
				//UART5_SendCharachter(var);
				//UART5_SendString(arr);
				ADXL_Read(DATA_START_ADD_R_REG );
				x=(data[1]<<8)|data[0];
				y=(data[3]<<8)|data[2];
				z=(data[5]<<8)|data[4];
				
			}
}

