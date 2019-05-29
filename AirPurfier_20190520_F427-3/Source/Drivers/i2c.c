/**
  ******************************************************************************
  * @file    i2c.c
  * @author  Waveshare Team
  * @version V1.0
  * @date    29-August-2014
  * @brief   This file provides all the I2C firmware functions.

  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */


#include "i2c.h"

i2cPort_t *i2cPort1 = NULL;

/**
  * @brief  Initializes I2C 
  * @param  None
  * @retval None
  */

int i2cInit(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
 
	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //     GPIO_Mode_Out_PP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //     GPIO_Mode_Out_PP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //     GPIO_Mode_Out_PP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(RST_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = INT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //     GPIO_Mode_Out_PP
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(INT_PORT, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	I2C_SCL_Set();
	I2C_SDA_Set();
	/* RST Pin configuration -------------------------------------------------------------------*/
	
	RST_PORT->BSRRH = RST_PIN;  //低电平
	Delay_ms(50);
	
	RST_PORT->BSRRL = RST_PIN;  //高电平
	Delay_ms(50);
	

    
    return 0;
}

int i2c2Init(void)
{
//	GPIO_InitTypeDef   GPIO_InitStructure;
//	EXTI_InitTypeDef   EXTI_InitStructure;
//	NVIC_InitTypeDef   NVIC_InitStructure;
//	
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef   EXTI_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    /* RST Pin configuration -------------------------------------------------------------------*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = I2C2_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);
        
    GPIO_InitStructure.GPIO_Pin = I2C2_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //     GPIO_Mode_Out_PP
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* Configure PE.00 PE.13  pin as input floating */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* Connect EXTI13 Line to PE.13 pin */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource13);

    /* Configure EXTI13 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    /* Enable and set EXTI15_10 Interrupt to the lowest priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Generate software interrupt: simulate a falling edge applied on EXTI0 and EXTI13 line */
//    EXTI_GenerateSWInterrupt(EXTI_Line13);
	
	I2C2_SCL_Set();
	I2C2_SDA_Set();
	/* RST Pin configuration -------------------------------------------------------------------*/
	
	RST2_PORT->BSRRH = RST2_PIN;
	Delay_ms(50);
	
	/* 低电平复位 */
	RST2_PORT->BSRRL = RST2_PIN;
	Delay_ms(50);
	

	
	return 0;
}

/**
  * @brief  Configures SDA in input/output mode 
  * @param  Mode
 *                   @arg 0: SDA in input mode
  *                  @arg 1: SDA in output mode
  * @retval None
  */

void I2C_SDAMode(uint8_t Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
	if (Mode)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    }
	else
    {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    }	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void I2C2_SDAMode(uint8_t Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = I2C2_SDA_PIN;
	if (Mode)
    {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    }
	else
    {
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    }	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief   Generates I2C communication START condition.
  *         
  * @param  None
  *         
  * @retval  None
**/

void I2C_Start(void)
{
	I2C_SDAMode(I2C_SDA_OUT);
	I2C_SDA_Set();
	I2C_SCL_Set();
	Delay_us(3);
	I2C_SDA_Clr();
	Delay_us(3);
	I2C_SCL_Clr();
	Delay_us(3);
}

void I2C2_Start(void)
{
	I2C2_SDAMode(I2C_SDA_OUT);
	I2C2_SDA_Set();
	I2C2_SCL_Set();
	Delay_us(3);
	I2C2_SDA_Clr();
	Delay_us(3);
	I2C2_SCL_Clr();
	Delay_us(3);
}

/**
  * @brief  Generates I2C communication STOP condition.
  *         
  * @param  None
  *         
  * @retval  None
**/

void I2C_Stop(void)
{
	I2C_SDAMode(I2C_SDA_OUT);
	Delay_us(3);
	I2C_SCL_Clr();
	I2C_SDA_Clr();
	I2C_SCL_Set();
	Delay_us(3);
	I2C_SDA_Set();
}

void I2C2_Stop(void)
{
	I2C2_SDAMode(I2C_SDA_OUT);
	Delay_us(3);
	I2C2_SCL_Clr();
	I2C2_SDA_Clr();
	I2C2_SCL_Set();
	Delay_us(3);
	I2C2_SDA_Set();
}

/**
  * @brief  I2C is waiting for an ACK
  *         
  * @param  None
  *         
  * @retval  I2C ACK status
  *              @arg 0:I2C has not waited an ACK
  *              @arg 1:I2C has  waited an ACK
**/

bool I2C_WaitForAck(void)
{
	u8 data;
	I2C_SDAMode(I2C_SDA_IN);
	I2C_SDA_Set();
	Delay_us(3);
    I2C_SCL_Set();
	Delay_us(3);
	if(I2C_SDA_Get())
	{
		data = 1;
	}
	else 
	{
		data = 0;
	}
	I2C_SCL_Clr();
	Delay_us(3);
	return data;
}

bool I2C2_WaitForAck(void)
{
	u8 data;
	I2C2_SDAMode(I2C_SDA_IN);
	I2C2_SDA_Set();
	Delay_us(3);
    I2C2_SCL_Set();
	Delay_us(3);
	if(I2C2_SDA_Get())
	{
		data = 1;
	}
	else 
	{
		data = 0;
	}
	I2C2_SCL_Clr();
	Delay_us(3);
	return data;
}

/**
  * @brief  I2C responds an ACK
  *         
  * @param  None
  *         
  * @retval  None
**/

void I2C_Ack(void)
{
	I2C_SDAMode(I2C_SDA_OUT);
	I2C_SDA_Clr();
	Delay_us(3);
	I2C_SCL_Set();
	Delay_us(3);
	I2C_SCL_Clr();
	Delay_us(3);
	I2C_SDA_Set();
}

/**
  * @brief  I2C responds an NACK
  *         
  * @param  None
  *         
  * @retval  None
**/
void I2C_NAck(void)
{
	I2C_SDAMode(I2C_SDA_OUT);
	I2C_SDA_Set();
	Delay_us(3);
	I2C_SCL_Set();
	Delay_us(3);
	I2C_SCL_Clr();
}

void I2C2_NAck(void)
{
	I2C2_SDAMode(I2C_SDA_OUT);
	I2C2_SDA_Set();
	Delay_us(3);
	I2C2_SCL_Set();
	Delay_us(3);
	I2C2_SCL_Clr();
}

/**
  * @brief  Write one bit to I2C bus
  *         
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device
  * @param BitNum:  which bit of the byte that  would be writen to
  * @param Data: bit value(0 or 1)
  *         
  * @retval  true: writen one bit succeed
**/

//bool I2C_WriteOneBit(uint8_t DevAddr, uint8_t RegAddr, uint8_t BitNum, uint8_t Data)
//{
//    uint8_t Dat;
//    
//    if (!I2C_ReadOneByte(DevAddr, RegAddr, &Dat)) return false;
//    Dat = (Data != 0) ? (Dat | (1 << BitNum)) : (Dat & ~(1 << BitNum));
//    if (!I2C_WriteOneByte(DevAddr, RegAddr, Dat)) return false;
//    
//    return true;
//}


/**
  * @brief  Write couplesof bits to I2C bus
  *         
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device
  * @param BitStart: the first bit of the several bits would be to writen
  * @param Data: the data would be writen      
  * @retval  writen couples of bits succeed
**/

//bool I2C_WriteBits(uint8_t DevAddr, uint8_t RegAddr, uint8_t BitStart, uint8_t Length, uint8_t Data)
//{

//    uint8_t Dat, Mask;
//    
//	if (!I2C_ReadOneByte(DevAddr, RegAddr, &Dat)) return false;
//    Mask = (0xFF << (BitStart + 1)) | 0xFF >> ((8 - BitStart) + Length - 1);
//    Data <<= (8 - Length);
//    Data >>= (7 - BitStart);
//    Dat &= Mask;
//    Dat |= Data;
//    if (!I2C_WriteOneByte(DevAddr, RegAddr, Dat)) return false;
//    
//    return true;
//}


/**
  * @brief write an byte to I2C bus
  *         
  * @param Data: the data would be writen
  *         
  * @retval  None
**/

void I2C_WriteByte(uint8_t Data)
{
	uint8_t i;
	Delay_us(3);
	I2C_SDAMode(I2C_SDA_OUT);
    
	for (i = 0; i < 8; i ++)
	{   
		if (Data & 0x80)
        {
			I2C_SDA_Set();
        }
		else
        {
			I2C_SDA_Clr();
        }
		Delay_us(3);
		I2C_SCL_Set();
		Delay_us(3);
		I2C_SCL_Clr();
		if(i == 7)
		{
			I2C_SDA_Set();
		}
		Data <<= 1;
		Delay_us(3);
	}
}

void I2C2_WriteByte(uint8_t Data)
{
	uint8_t i;
	Delay_us(3);
	I2C2_SDAMode(I2C_SDA_OUT);
    
	for (i = 0; i < 8; i ++)
	{   
		if (Data & 0x80)
        {
			I2C2_SDA_Set();
        }
		else
        {
			I2C2_SDA_Clr();
        }
		Delay_us(3);
		I2C2_SCL_Set();
		Delay_us(3);
		I2C2_SCL_Clr();
		if(i == 7)
		{
			I2C2_SDA_Set();
		}
		Data <<= 1;
		Delay_us(3);
	}
}

/**
  * @brief  Write an byte to the specified device address through I2C bus.
  *         
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device
 * @param  Data: the data would be writen to the specified device address       
  * @retval  None
**/

bool I2C_WriteOneByte( uint8_t RegAddr,uint8_t Data)
{
	I2C_Start();
	I2C_WriteByte(FT_WRITE);
	I2C_WaitForAck();
	I2C_WriteByte(RegAddr);
	I2C_WaitForAck();
	I2C_WriteByte(Data);
	I2C_WaitForAck();
	I2C_Stop();	
	return true;
}

/**
  * @brief Write a buffer specified sizes  to the specified device address through I2C bus.
  *
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device       
  * @param Num: the sizes of the specified buffer
  * @param pBuff: point to a the specified buffer that would be writen       
  * @retval  false: paramter error
  *                true: Write a buffer succeed
**/

bool I2C_WriteBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff)
{
	uint8_t i;	
	I2C_Start();
	I2C_WriteByte(FT_WRITE);
	I2C_WaitForAck();
	I2C_WriteByte(RegAddr);
	I2C_WaitForAck();
	for(i = 0;i < Num;i++)
	{
		I2C_WriteByte(*(pBuff + i));
		I2C_WaitForAck();
	}
	I2C_Stop();	
	
	return true;
	
}

/**
  * @brief read an byte from I2C bus
  *         
  * @param  Ack: send an ACK/NACK to I2C bus after read an byte
  *              @arg 0: ACK
  *              @arg 1:NACK         
  * @retval  None
**/

uint8_t I2C_ReadByte(void)
{
	uint8_t i, RecDat = 0;
	I2C_SDAMode(I2C_SDA_IN);
	Delay_us(3);
	for(i = 0; i < 8; i ++)
	{
		RecDat <<= 1;
		I2C_SCL_Set();
		Delay_us(3);
		if(I2C_SDA_Get())
		{
			RecDat |= 0x01;
		}
		else
		{
			RecDat &= ~0x01;
		}
		I2C_SCL_Clr();
		Delay_us(3);
	}
	return RecDat;
}

uint8_t I2C2_ReadByte(void)
{
	uint8_t i, RecDat = 0;
	I2C2_SDAMode(I2C_SDA_IN);
	Delay_us(3);
	for(i = 0; i < 8; i ++)
	{
		RecDat <<= 1;
		I2C2_SCL_Set();
		Delay_us(3);
		if(I2C2_SDA_Get())
		{
			RecDat |= 0x01;
		}
		else
		{
			RecDat &= ~0x01;
		}
		I2C2_SCL_Clr();
		Delay_us(3);
	}
	return RecDat;
}



/**
  * @brief Read an byte from the specified device address through I2C bus.
  *         
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device  
  *         
  * @retval  the byte read from I2C bus
**/

bool I2C_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Val)
{
	uint8_t TempVal = 0;
	I2C_Start();
	I2C_WriteByte(FT_WRITE);
	I2C_WaitForAck();
	I2C_WriteByte(RegAddr);
	I2C_WaitForAck();
	I2C_Start();
	I2C_WriteByte(FT_READ);
	TempVal = I2C_ReadByte();
	I2C_NAck();
	I2C_Stop();	
	*Val = TempVal;
	return true;
}

bool I2C2_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Val)
{
	uint8_t TempVal = 0;
	I2C2_Start();
	I2C2_WriteByte(FT_WRITE);
	I2C2_WaitForAck();
	I2C2_WriteByte(RegAddr);
	I2C2_WaitForAck();
	I2C2_Start();
	I2C2_WriteByte(FT_READ);
	TempVal = I2C2_ReadByte();
	I2C2_NAck();
	I2C2_Stop();	
	*Val = TempVal;
	return true;
}

/**
  * @brief Read couples of bytes  from the specified device address through I2C bus.
  *
  * @param DevAddr: The address byte of the slave device
  * @param RegAddr: The address byte of  register of the slave device       
  * @param Num: the sizes of the specified buffer
  * @param pBuff: point to a the specified buffer that would read bytes from I2C bus      
  * @retval  false: paramter error
  *                true: read a buffer succeed
**/

bool I2C_ReadBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff)
{
	uint8_t i;
	I2C_Start();
	I2C_WriteByte(FT_WRITE);
	I2C_WaitForAck();
	I2C_WriteByte(RegAddr);
	I2C_WaitForAck();
	I2C_Start();
	I2C_WriteByte(FT_READ);
	for(i = 0;i<Num;i++)
	{
		if(i == Num - 1)
		{
			*(pBuff + i) = I2C_ReadByte();
			I2C_Ack();
		}
		else 
		{
			*(pBuff + i) = I2C_ReadByte();
			I2C_NAck();
		}
	}
	I2C_Stop();	
	return true;
}

/**
  * @brief   Delay some times.
  *         
  * @param  Time
  *         
  * @retval  None
**/

void Delay_us(uint16_t Time)
{
	u8 i;
	while (Time --)
    {
		for(i = 0; i < 4; i ++);
		{
		
		}
//        __nop();
    }
}


/**
  * @brief   Delay some times.
  *         
  * @param  Time
  *         
  * @retval  None
**/

void Delay_ms(uint16_t Time)
{
	while (Time --)
    {
        Delay_us(1000);
    }
}



/******************* (C) COPYRIGHT 2014 Waveshare *****END OF FILE*******************/

