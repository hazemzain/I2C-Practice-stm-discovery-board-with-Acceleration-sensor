#include "i2c.h" 
/*******************************************************************/
/*******************ENG.HAZEM ZAIN**********************************/
/***********I2C DRIVER FOR ADCL245 ACCELERATION SENSOR**************/
/*******************************************************************/
#define I2C_100KHZ  80
#define SD_MAX_RISE_TIME 17
void I2C_Init()
{
	/* 	i2c scl ===PB8
			I2C SDA==PB9  
			AF4
	*/
	/**********enable clock for port B *********************/
	RCC->AHB1ENR|=(1<<1);
	/*********enable altrant func for pin 8,9 in port b*****/
	GPIOB->MODER|=(2<<16);
	GPIOB->MODER|=(2<<18);
	
	/*****enable open drain mode for this pin***************/
	GPIOB->OTYPER|=(1<<8);
	GPIOB->OTYPER|=(1<<9);
	
	/*****enale pull up for this pin************************/
	GPIOB->PUPDR|=(1<<16);
	GPIOB->PUPDR|=(1<<18);
	
	/*****cofigure ALF reg for i2c pin *********************/
	GPIOB->AFR[1]|=(4<<0);
	GPIOB->AFR[1]|=(4<<4);
	
	/*****enale clock for i2c ********************************/
	RCC->APB1ENR|=(1<<21);
	/********connfigure i2c1***********************************/
	/****cofigre i2c under reset********************************/
	I2C1->CR1|=(1<<15);
	I2C1->CR1&=~(1<<15);
	/**********set i2c ferq to 16 MZ***************************/
	I2C1->CR2=(1<<4);
	/****set i2c for stander mode***************************/
	I2C1->CCR=I2C_100KHZ;
	I2C1->TRISE=SD_MAX_RISE_TIME;
	/***********enable  i2c1 ******************************/
	I2C1->CR1|=(1<<0);
}
void I2C_Read_Byte(char address,char memory_address,char *result )
{
	
	volatile int temp=0;
	/***********busyy wait for bus free******************/
	/*
		Bit 1 BUSY: Bus busy
		0: No communication on the bus
		1: Communication ongoing on the bus
		– Set by hardware on detection of SDA or SCL low
	*/
	while (I2C1->SR2 &(1<<1));
	/*****genrate start condition************************/
	/*Bit 8 START: Start generation
		This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
		In Master Mode:
		0: No Start generation
		1: Repeated start generation
		In Slave mode:
		0: No Start generation
		1: Start generation when the bus is free
	*/
	I2C1->CR1|=(1<<8);
	/***wait utill start condition is genrated*****************/
	/*
		Bit 0 SB: Start bit (Master mode)
		0: No Start condition
		1: Start condition generated.
		– Set when a Start condition generated.
		– Cleared by software by reading the SR1 register followed by writing the DR register, or by 
		hardware when PE=
	*/
	while(!(I2C1->SR1 &(1<<0)));
	
	/**transmit address************/
	I2C1->DR=(address<<1);
	/****check the slave address is transmit or not****************/
	/*
				Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
			This bit is cleared by software reading SR1 register followed reading SR2, or by hardware 
			when PE=0.
			Address matched (Slave)
			0: Address mismatched or not received.
			1: Received address matched.
			– Set by hardware as soon as the received slave address matched with the OAR registers 
			content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert 
			is recognized. (when enabled depending on configuration).
	*/
	while(!(I2C1->SR1 &(1<<1)));
	/***** to clear this bit is cleared y software by reading sr1 reg***************/
	temp=I2C1->SR1;
	
	/*****************after that sed memory address register************************/
	I2C1->DR=memory_address;
	/*****wait until trasmit reg i empty****************************/
	/*
		Bit 7 TxE: Data register empty (transmitters) 
		0: Data register not empty
		1: Data register empty
	*/	
	while(!(I2C1->SR1&(1<<7)));
	/********after that gennerate anther start condition********/
	I2C1->CR1|=(1<<8);
	while(!(I2C1->SR1 &(1<<0)));
	/*******after that en lave address with read bit*************/
	I2C1->DR=(address<<1)|1;
	while(!(I2C1->SR1&(1<<7))){}
	
	/***wait for ack from slave***********************/
   I2C1->CR1&=~(1<<10);
	 temp=I2C1->SR2;
	 
	 
	 /*****stop conition***********/
	 I2C1->CR1|=(1<<9);
		
		while(!(I2C1->SR1&(1<<6))){}
			
		*result++=I2C1->DR;
	
	
}

void I2C_MORE_BYTE_READ(char address,char memory_address,int n_size,char *result )
{
	volatile int temp=0;
	while (I2C1->SR2 &(1<<1));
	I2C1->CR1|=(1<<8);
	/***wait utill start condition is genrated*****************/
	/*
		Bit 0 SB: Start bit (Master mode)
		0: No Start condition
		1: Start condition generated.
		– Set when a Start condition generated.
		– Cleared by software by reading the SR1 register followed by writing the DR register, or by 
		hardware when PE=
	*/
	while(!(I2C1->SR1 &(1<<0)));
	/**transmit address************/
	I2C1->DR=(address<<1);
	/****check the slave address is transmit or not****************/
	/*
				Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
			This bit is cleared by software reading SR1 register followed reading SR2, or by hardware 
			when PE=0.
			Address matched (Slave)
			0: Address mismatched or not received.
			1: Received address matched.
			– Set by hardware as soon as the received slave address matched with the OAR registers 
			content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert 
			is recognized. (when enabled depending on configuration).
	*/
	while(!(I2C1->SR1 &(1<<1)));
	/***** to clear this bit is cleared y software by reading sr1 reg***************/
	temp=I2C1->SR1;
	while(!(I2C1->SR1&(1<<7)));
	I2C1->DR=memory_address;
	while(!(I2C1->SR1&(1<<7)));
	I2C1->CR1|=(1<<8);
	while(!(I2C1->SR1 &(1<<0)));
	I2C1->DR=(address<<1)|1;
	while(!(I2C1->SR1&(1<<7))){}
	temp=I2C1->SR2;
	I2C1->CR1|=(1<<10);
		while (n_size>0)
		{
			if(n_size==1)
			{
				/****disable ack********/
				I2C1->CR1&=~(1<<10);
				/****generate stop condition************/
				I2C1->CR1|=(1<<9);
				while(!(I2C1->SR1&(1<<6))){}
					*result++=I2C1->DR;
					
					break;
			}else
			{
				while(!(I2C1->SR1&(1<<6))){}
					*result++=I2C1->DR;
					n_size--;
				
			}
		}
}


void I2C_MORE_BYTE_WRITE(char address,char memory_address,int n_size,char *data ){
	volatile int temp=0;
	while (I2C1->SR2 &(1<<1));
	I2C1->CR1|=(1<<8);
	while(!(I2C1->SR1 &(1<<0)));
	I2C1->DR=(address<<1);
	while(!(I2C1->SR1 &(1<<1)));
	/***** to clear this bit is cleared y software by reading sr1 reg***************/
	temp=I2C1->SR1;
	while(!(I2C1->SR1&(1<<7)));
	I2C1->DR=memory_address;
	for(int i=0;i<n_size;i++){
	while(!(I2C1->SR1&(1<<7))){}
		I2C1->DR= *data++;
		
	}
	while(!(I2C1->SR1&(1<<2))){}
		I2C1->CR1|=(1<<9);
}