//============================================================================= 
// S E N S I R I O N AG, Laubisruetistr. 50, CH-8712 Staefa, Switzerland
//=============================================================================
// Project : SHT3x Sample Code (V1.1)
// File : system.h (V1.1)
// Author : RFU
// Date : 6-Mai-2015
// Controller: STM32F100RB
// IDE : μVision V5.12.0.0
// Compiler : Armcc
// Brief : System functions, global definitions
//=============================================================================

#ifndef SYSTEM_H
#define SYSTEM_H

//-- Includes -----------------------------------------------------------------
#include "stm32f4xx.h" // controller register definitions
#include "typedefs.h" // type definitions

//-- Enumerations -------------------------------------------------------------
// Error codes
typedef enum {
	NO_ERROR = 0x00, // no error 
	ACK_ERROR = 0x01, // no acknowledgment error 
	CHECKSUM_ERROR = 0x02, // checksum mismatch error 
	TIMEOUT_ERROR = 0x04, // timeout error 
	PARM_ERROR = 0x80, // parameter out of range error 
} etError;

// I2C acknowledge
typedef enum {
	ACK = 0,
	NACK = 1, 
} etI2cAck;

//=============================================================================
void SystemInit(void);
//=============================================================================
// Initializes the system
//-----------------------------------------------------------------------------

//=============================================================================
void DelayMicroSeconds(u32t nbrOfUs);
//=============================================================================
// Wait function for small delays.
//-----------------------------------------------------------------------------
// input: nbrOfUs wait x times approx. one micro second (fcpu = 8MHz)
// return: -
// remark: smallest delay is approx. 15us due to function call

#endif
