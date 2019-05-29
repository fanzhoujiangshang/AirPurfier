//============================================================================= 
// S E N S I R I O N AG, Laubisruetistr. 50, CH-8712 Staefa, Switzerland //============================================================================= 
// Project : SHT3x Sample Code (V1.1) 
// File : i2c_hal.h (V1.1) 
// Author : RFU // Date : 6-Mai-2015 
// Controller: STM32F100RB 
// IDE : ¦ÌVision V5.12.0.0 
// Compiler : Armcc 
// Brief : I2C hardware abstraction layer //=============================================================================

#ifndef I2C_FT_H
#define I2C_FT_H

//-- Includes -----------------------------------------------------------------
#include "system.h"

//=============================================================================
void I2c_FT_Init(void); 
//=============================================================================
// Initializes the ports for I2C interface. 
//-----------------------------------------------------------------------------

//=============================================================================
void I2c_FT_StartCondition(void);

//============================================================================= 
// Writes a start condition on I2C-Bus. 
//----------------------------------------------------------------------------- 
// remark: Timing (delay) may have to be changed for different microcontroller.
//            _____ 
// SDA: _____|
//          _______ 
// SCL: ___|

//=============================================================================
void I2c_FT_StopCondition(void);
//=============================================================================
// Writes a stop condition on I2C-Bus.
//----------------------------------------------------------------------------- 
// remark: Timing (delay) may have to be changed for different microcontroller.
//            _____
// SDA: _____|
//          _______
// SCL: ___|
//=============================================================================

//=============================================================================
etError I2c_FT_WriteByte(u8t txByte); 
//=============================================================================
// Writes a byte to I2C-Bus and checks acknowledge. 
//----------------------------------------------------------------------------- 
// input: txByte transmit byte
// // return: error: ACK_ERROR = no acknowledgment from sensor 
// NO_ERROR = no error 
// 
// remark: Timing (delay) may have to be changed for different microcontroller.

//=============================================================================
etError I2c_FT_ReadByte(u8t *rxByte, etI2cAck ack, u8t timeout);

etError I2c_FT_GeneralCallReset(void);

etError I2c_FT_WriteData(u8t _i2cAddress, u8t reg, u8t data);

etError I2c_FT_ReadData(u8t _i2cAddress, u8t reg, u8t *data);

etError I2c_FT_ReadMultiData(u8t _i2cAddress, u8t Reg, u8t *Buf, u8t num);

#endif
