//=============================================================================
// S E N S I R I O N AG, Laubisruetistr. 50, CH-8712 Staefa, Switzerland
//=============================================================================
// Project : SHT3x Sample Code (V1.1) 
// File : i2c_hal.c (V1.1) 
// Author : RFU // Date : 6-Mai-2015 
// Controller: STM32F100RB 
// IDE : ��Vision V5.12.0.0 
// Compiler : Armcc 
// Brief : I2C hardware abstraction layer 
//=============================================================================

//-- Includes -----------------------------------------------------------------
#include "i2c_ft.h"

//-- Defines ------------------------------------------------------------------ 
// I2C IO-Pins /* -- adapt the defines for your uC -- */

// SDA on port B, bit 9
#define SDA_FT_LOW() (GPIOB->BSRRH = GPIO_Pin_9) // set SDA to low
#define SDA_FT_OPEN() (GPIOB->BSRRL = GPIO_Pin_9) // set SDA to open-drain
#define SDA_FT_READ (GPIOB->IDR & GPIO_Pin_9) // read SDA

// SCL on port B, bit 8            /* -- adapt the defines for your uC -- */ 
#define SCL_FT_LOW() (GPIOB->BSRRH = GPIO_Pin_8) // set SCL to low 
#define SCL_FT_OPEN() (GPIOB->BSRRL = GPIO_Pin_8) // set SCL to open-drain 
#define SCL_FT_READ (GPIOB->IDR & GPIO_Pin_8) // read SCL

//-- Static function prototypes -----------------------------------------------
static etError I2c_FT_WaitWhileClockStreching(u8t timeout);

//----------------------------------------------------------------------------- 
void I2c_FT_Init(void) /* -- adapt the init for your uC -- */ 
{
	RCC->APB2ENR |= 0x00000008; // I/O port B clock enabled

	SDA_FT_OPEN(); // I2C-bus idle mode SDA released 
	SCL_FT_OPEN(); // I2C-bus idle mode SCL released

	// SDA on port B, bit 11 
	// SCL on port B, bit 10 
//	GPIOB->CRH &= 0xFFFFFF00; // set open-drain output for SDA and SCL 
//	GPIOB->CRH |= 0x00000055; //
}

//----------------------------------------------------------------------------- 
void I2c_FT_StartCondition(void)
{
	SDA_FT_OPEN();
	DelayMicroSeconds(1);
	SCL_FT_OPEN();
	DelayMicroSeconds(1);
	SDA_FT_LOW();
	DelayMicroSeconds(10); // hold time start condition (t_HD;STA)
	SCL_FT_LOW();
	DelayMicroSeconds(10);
}

//-----------------------------------------------------------------------------
void I2c_FT_StopCondition(void)
{
	SCL_FT_LOW();
	DelayMicroSeconds(1);
	SDA_FT_LOW();
	DelayMicroSeconds(1);
	SCL_FT_OPEN();
	DelayMicroSeconds(10); // set-up time stop condition (t_SU;STO)
	SDA_FT_OPEN();
	DelayMicroSeconds(10);
}

//----------------------------------------------------------------------------- 
etError I2c_FT_WriteByte(u8t txByte)
{
	etError error = NO_ERROR;
	u8t mask;

	for (mask = 0x80; mask > 0; mask >>= 1)// shift bit for masking (8 times) 
	{
		if ((mask & txByte) == 0)
		{
			SDA_FT_LOW(); // masking txByte, write bit to SDA-Line
		}
		else
		{
			SDA_FT_OPEN();
		}

		DelayMicroSeconds(1); // data set-up time (t_SU;DAT)
		SCL_FT_OPEN(); // generate clock pulse on SCL 
		DelayMicroSeconds(5); // SCL high time (t_HIGH)
		SCL_FT_LOW(); 
		DelayMicroSeconds(1); // data hold time(t_HD;DAT)
	}
	SDA_FT_OPEN(); // release SDA-line
	SCL_FT_OPEN(); // clk #9 for ack
	DelayMicroSeconds(1); // data set-up time (t_SU;DAT)

	if (SDA_FT_READ)
	{
		error = ACK_ERROR; // check ack from i2c slave
	}

	SCL_FT_LOW();
	DelayMicroSeconds(20); // wait to see byte package on scope 

	return error; // return error code
}

//-----------------------------------------------------------------------------
etError I2c_FT_ReadByte(u8t *rxByte, etI2cAck ack, u8t timeout)
{
	etError error = NO_ERROR;
	u8t mask;
	*rxByte = 0x00;
	SDA_FT_OPEN(); // release SDA-line
	for (mask = 0x80; mask > 0; mask >>= 1) // shift bit for masking (8 times)
	{
		SCL_FT_OPEN(); // start clock on SCL-line
		DelayMicroSeconds(1); // clock set-up time (t_SU;CLK)
		error = I2c_FT_WaitWhileClockStreching(timeout);// wait while clock streching 
		DelayMicroSeconds(3); // SCL high time (t_HIGH)

		if (SDA_FT_READ)
		{
			*rxByte |= mask; // read bit
		}

		SCL_FT_LOW(); 
        DelayMicroSeconds(1); // data hold time(t_HD;DAT)
	}
	if (ack == ACK)
	{
		SDA_FT_LOW(); // send acknowledge if necessary
	}
	else
	{
		SDA_FT_OPEN();
	}

	DelayMicroSeconds(1); // data set-up time (t_SU;DAT)
	SCL_FT_OPEN(); // clk #9 for ack
	DelayMicroSeconds(5); // SCL high time (t_HIGH)
	SCL_FT_LOW();
	SDA_FT_OPEN(); // release SDA-line
	DelayMicroSeconds(20); // wait to see byte package on scope

	return error; // return with no error
}

//----------------------------------------------------------------------------- 
static etError I2c_FT_WaitWhileClockStreching(u8t timeout) 
{
	etError error = NO_ERROR;

	while (SCL_FT_READ == 0)
	{
		if (timeout-- == 0) 
		{
			return TIMEOUT_ERROR; 
		}

		DelayMicroSeconds(1000);
	}
	return error; 
}

etError I2c_FT_WriteData(u8t _i2cAddress, u8t reg, u8t data)
{
    etError error; // error code
    
    // write a start condition
    I2c_FT_StartCondition();

	// write the sensor I2C address with the write flag
	error = I2c_FT_WriteByte(_i2cAddress << 1);
    
    // write the upper 8 bits of the command to the sensor
	error = I2c_FT_WriteByte(reg);

	// write the lower 8 bits of the command to the sensor
	error |= I2c_FT_WriteByte(data);
    
    // write a stop condition
	I2c_FT_StopCondition();
    
    return error;
}

etError I2c_FT_ReadData(u8t _i2cAddress, u8t reg, u8t *data)
{
    etError error; // error code

	// write a start condition
	I2c_FT_StartCondition();
    
    // write the sensor I2C address with the write flag
	error = I2c_FT_WriteByte(_i2cAddress << 1);
    
    // write the upper 8 bits of the command to the sensor
	error = I2c_FT_WriteByte(reg);
    
    // write a start condition
	I2c_FT_StartCondition();

	// write the sensor I2C address with the read flag
	error = I2c_FT_WriteByte(_i2cAddress << 1 | 0x01);
    
    I2c_FT_ReadByte(data, ACK, 0);
    
    // write a stop condition
	I2c_FT_StopCondition();
    
    return error;
}

etError I2c_FT_ReadMultiData(u8t _i2cAddress, u8t reg, u8t *buf, u8t num)
{
    etError error; // error code
    uint8_t i = 0;

	// write a start condition
	I2c_FT_StartCondition();
    
    // write the sensor I2C address with the write flag
	error = I2c_FT_WriteByte(_i2cAddress << 1);
    
    // write the upper 8 bits of the command to the sensor
	error = I2c_FT_WriteByte(reg);
    
    // write a start condition
	I2c_FT_StartCondition();

	// write the sensor I2C address with the read flag
	error = I2c_FT_WriteByte(_i2cAddress << 1 | 0x01);
    
    for (i = 0; i < num; i++)
    {
        I2c_FT_ReadByte(buf + i, ACK, 0);
    }
    
    // write a stop condition
	I2c_FT_StopCondition();
    
    return error;
}
