//=============================================================================
// S E N S I R I O N AG, Laubisruetistr. 50, CH-8712 Staefa, Switzerland
//=============================================================================
// Project : SHT3x Sample Code (V1.1) 
// File : i2c_hal.c (V1.1) 
// Author : RFU // Date : 6-Mai-2015 
// Controller: STM32F100RB 
// IDE : μVision V5.12.0.0 
// Compiler : Armcc 
// Brief : I2C hardware abstraction layer 
//=============================================================================

//-- Includes -----------------------------------------------------------------
#include "i2c_hal.h"

//-- Defines ------------------------------------------------------------------ 
// I2C IO-Pins /* -- adapt the defines for your uC -- */

// SDA on port B, bit 11
#define SDA_LOW() (GPIOD->BSRRH = GPIO_Pin_11) // set SDA to low
#define SDA_OPEN() (GPIOD->BSRRL = GPIO_Pin_11) // set SDA to open-drain
#define SDA_READ (GPIOD->IDR & GPIO_Pin_11) // read SDA

// SCL on port B, bit 10            /* -- adapt the defines for your uC -- */ 
#define SCL_LOW() (GPIOD->BSRRH = GPIO_Pin_10) // set SCL to low 
#define SCL_OPEN() (GPIOD->BSRRL = GPIO_Pin_10) // set SCL to open-drain 
#define SCL_READ (GPIOD->IDR & GPIO_Pin_10) // read SCL

//-- Static function prototypes -----------------------------------------------
static etError I2c_WaitWhileClockStreching(u8t timeout);

//----------------------------------------------------------------------------- 
void I2c_Init(void) /* -- adapt the init for your uC -- */ 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	SDA_OPEN(); // I2C-bus idle mode SDA released 
	SCL_OPEN(); // I2C-bus idle mode SCL released

	// SDA on port D, bit 11 
	// SCL on port D, bit 10 
//	GPIOD->CRH &= 0xFFFF00FF; // set open-drain output for SDA and SCL 
//	GPIOD->CRH |= 0x00005500; // 
	
	  GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//----------------------------------------------------------------------------- 
void I2c_StartCondition(void)
{
	SDA_OPEN();
	DelayMicroSeconds(10);
	SCL_OPEN();
	DelayMicroSeconds(10);
	SDA_LOW();
	DelayMicroSeconds(30); // hold time start condition (t_HD;STA)
	SCL_LOW();
	DelayMicroSeconds(30);
}

//-----------------------------------------------------------------------------
void I2c_StopCondition(void)
{
	SCL_LOW();
	DelayMicroSeconds(1);
	SDA_LOW();
	DelayMicroSeconds(1);
	SCL_OPEN();
	DelayMicroSeconds(10); // set-up time stop condition (t_SU;STO)
	SDA_OPEN();
	DelayMicroSeconds(10);
}

//----------------------------------------------------------------------------- 
etError I2c_WriteByte(u8t txByte)
{
	etError error = NO_ERROR;
	u8t mask;

	for (mask = 0x80; mask > 0; mask >>= 1)// shift bit for masking (8 times) 
	{
		if ((mask & txByte) == 0)
		{
			SDA_LOW(); // masking txByte, write bit to SDA-Line
		}
		else
		{
			SDA_OPEN();
		}

		DelayMicroSeconds(5); // data set-up time (t_SU;DAT)
		SCL_OPEN(); // generate clock pulse on SCL 
		DelayMicroSeconds(10); // SCL high time (t_HIGH)
		SCL_LOW(); 
		DelayMicroSeconds(5); // data hold time(t_HD;DAT)
	}
	SDA_OPEN(); // release SDA-line
	SCL_OPEN(); // clk #9 for ack
	DelayMicroSeconds(200); // data set-up time (t_SU;DAT)

	if (SDA_READ)
	{
		error = ACK_ERROR; // check ack from i2c slave
	}

	SCL_LOW();
	DelayMicroSeconds(20); // wait to see byte package on scope 

	return error; // return error code
}

//-----------------------------------------------------------------------------
etError I2c_ReadByte(u8t *rxByte, etI2cAck ack, u8t timeout)
{
	etError error = NO_ERROR;
	u8t mask;
	*rxByte = 0x00;
	SDA_OPEN(); // release SDA-line
	for (mask = 0x80; mask > 0; mask >>= 1) // shift bit for masking (8 times)
	{
		SCL_OPEN(); // start clock on SCL-line
		DelayMicroSeconds(5); // clock set-up time (t_SU;CLK)
		error = I2c_WaitWhileClockStreching(timeout);// wait while clock streching 
		DelayMicroSeconds(10); // SCL high time (t_HIGH)

		if (SDA_READ)
		{
			*rxByte |= mask; // read bit
		}

		SCL_LOW(); DelayMicroSeconds(5); // data hold time(t_HD;DAT)
	}
	if (ack == ACK)
	{
		SDA_LOW(); // send acknowledge if necessary
	}
	else
	{
		SDA_OPEN();
	}

	DelayMicroSeconds(5); // data set-up time (t_SU;DAT)
	SCL_OPEN(); // clk #9 for ack
	DelayMicroSeconds(10); // SCL high time (t_HIGH)
	SCL_LOW();
	SDA_OPEN(); // release SDA-line
	DelayMicroSeconds(20); // wait to see byte package on scope

	return error; // return with no error
}

//-----------------------------------------------------------------------------
etError I2c_GeneralCallReset(void)
{
	etError error;
	I2c_StartCondition();
	error = I2c_WriteByte(0x00);

	if (error == NO_ERROR)
	{
		error = I2c_WriteByte(0x06);
	}

	return error;
}

//----------------------------------------------------------------------------- 
static etError I2c_WaitWhileClockStreching(u8t timeout) 
{
	etError error = NO_ERROR;

	while (SCL_READ == 0)
	{
		if (timeout-- == 0) 
		{
			return TIMEOUT_ERROR; 
		}

		DelayMicroSeconds(1000);
	}
	return error; 
}
