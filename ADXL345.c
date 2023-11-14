

#include "ADXL345.h"
char result=0;
 uint8_t data[6];
void ADXL_Read_Address(uint8_t REG)
{
	
	 I2C_Read_Byte(SLAVE_ADDRESS,REG,&result );
}

void ADXL_Write(uint8_t REG, char value )
{
	 I2C_MORE_BYTE_WRITE(SLAVE_ADDRESS,REG,1,&value );
}

void ADXL_Read(uint8_t REG )
{
	I2C_MORE_BYTE_READ(SLAVE_ADDRESS,REG,6,(char *)data );
}

void ADXL_Init( )
{
	   I2C_Init();
	 ADXL_Read_Address(DEVICE_R);
	ADXL_Write(DATA_READ_FORMAT_REG, FOUR_G );
	ADXL_Write(POWER_CTR_REG, RESET );
	ADXL_Write(POWER_CTR_REG, SET_MEASURE_B );
}