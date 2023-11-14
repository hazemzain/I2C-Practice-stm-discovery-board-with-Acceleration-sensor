#ifndef __I2C_H
#define __I2C_H

#include "stm32f4xx.h"
void I2C_Init();
void I2C_Read_Byte(char address,char memory_address,char *result );
void I2C_MORE_BYTE_READ(char address,char memory_address,int n_size,char *result );
void I2C_MORE_BYTE_WRITE(char address,char memory_address,int n_size,char *data );
#endif