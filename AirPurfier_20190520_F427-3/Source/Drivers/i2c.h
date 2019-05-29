/**
  ******************************************************************************
  * @file    I2C.h
  * @author  Waveshare Team
  * @version V1.0
  * @date    29-August-2014
  * @brief   This file contains all the functions prototypes for the I2C firmware 
  *          library.

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


#ifndef _I2C_H_
#define _I2C_H_

#include "afx.h"
#include <stdbool.h>

typedef struct
{
    uint8_t enabled;
} i2cPort_t;

#define I2C_SCL_PORT    GPIOB
#define I2C_SCL_PIN     GPIO_Pin_8
#define I2C_SDA_PORT    GPIOB
#define I2C_SDA_PIN     GPIO_Pin_9
#define RST_PORT        GPIOE
#define RST_PIN         GPIO_Pin_1
#define INT_PORT        GPIOE
#define INT_PIN         GPIO_Pin_0
#define FT_WRITE		0x70
#define FT_READ 		0x71
#define FT_ADDR         0x38

#define I2C2_SCL_PORT    GPIOB
#define I2C2_SCL_PIN     GPIO_Pin_10
#define I2C2_SDA_PORT    GPIOB
#define I2C2_SDA_PIN     GPIO_Pin_11
#define RST2_PORT        GPIOE
#define RST2_PIN         GPIO_Pin_12
#define INT2_PORT        GPIOE
#define INT2_PIN         GPIO_Pin_13
#define FT_WRITE		0x70
#define FT_READ 		0x71
#define FT_ADDR         0x38

#define I2C_SCL_Set()  GPIO_WriteBit(I2C_SCL_PORT, I2C_SCL_PIN, Bit_SET)
#define I2C_SCL_Clr()  GPIO_WriteBit(I2C_SCL_PORT, I2C_SCL_PIN, Bit_RESET)

#define I2C_SDA_Set()  GPIO_WriteBit(I2C_SDA_PORT, I2C_SDA_PIN, Bit_SET)
#define I2C_SDA_Clr()  GPIO_WriteBit(I2C_SDA_PORT, I2C_SDA_PIN, Bit_RESET)

#define I2C_SDA_Get()  GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)


#define I2C2_SCL_Set()  GPIO_WriteBit(I2C2_SCL_PORT, I2C2_SCL_PIN, Bit_SET)
#define I2C2_SCL_Clr()  GPIO_WriteBit(I2C2_SCL_PORT, I2C2_SCL_PIN, Bit_RESET)

#define I2C2_SDA_Set()  GPIO_WriteBit(I2C2_SDA_PORT, I2C2_SDA_PIN, Bit_SET)
#define I2C2_SDA_Clr()  GPIO_WriteBit(I2C2_SDA_PORT, I2C2_SDA_PIN, Bit_RESET)

#define I2C2_SDA_Get()  GPIO_ReadInputDataBit(I2C2_SDA_PORT, I2C2_SDA_PIN)

#ifndef I2C_Direction_Transmitter
	#define  I2C_Direction_Transmitter      ((uint8_t)0x00)
#endif

#ifndef I2C_Direction_Receiver
	#define  I2C_Direction_Receiver         ((uint8_t)0x01)
#endif

enum {
    I2C_SDA_IN,
	I2C_SDA_OUT
};

enum {
	I2C_ACK,
	I2C_NACK
};

extern void I2C_SDAMode(uint8_t Mode);
extern void I2C_Start(void);
extern void I2C_Stop(void);
extern bool I2C_WaitForAck(void);
extern void I2C_Ack(void);
extern void I2C_NAck(void);
extern bool I2C_WriteOneBit(uint8_t DevAddr, uint8_t RegAddr, uint8_t BitNum, uint8_t Data);
extern bool I2C_WriteBits(uint8_t DevAddr, uint8_t RegAddr, uint8_t BitStart, uint8_t Length, uint8_t Data);
extern void I2C_WriteByte(uint8_t Data);
extern void I2C2_WriteByte(uint8_t Data);
extern uint8_t I2C_ReadByte(void);
extern bool I2C_WriteOneByte( uint8_t RegAddr,uint8_t Data);
extern bool I2C_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Val);
extern bool I2C2_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t *Val);
extern bool I2C_WriteBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff);
extern bool I2C_ReadBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff);

extern int i2cInit(void);
extern int i2c2Init(void);
extern void Delay_us(uint16_t Time);
extern void Delay_ms(uint16_t Time);

extern void I2C_Start(void);
extern void I2C_Stop(void);

extern i2cPort_t *i2cPort1;

#endif

/******************* (C) COPYRIGHT 2014 Waveshare *****END OF FILE*******************/

