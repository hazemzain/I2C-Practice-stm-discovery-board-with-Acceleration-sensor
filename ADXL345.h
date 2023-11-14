#ifndef __ADXL345_H
#define  __ADXL345_H
#include "i2c.h" 
#include <stdint.h> 
#include <stdio.h> 
#define DEVICE_R  0x00

#define SLAVE_ADDRESS  0x53
#define DATA_READ_FORMAT_REG 0x31
#define POWER_CTR_REG 0x2D
#define DATA_START_ADD_R_REG 0x32

#define FOUR_G 0x01
#define RESET 0x00
#define SET_MEASURE_B 0x08

void ADXL_Read_Address(uint8_t REG);
void ADXL_Write_Address(uint8_t REG, char value );
void ADXL_Read(uint8_t REG );
void ADXL_Init( );
#endif