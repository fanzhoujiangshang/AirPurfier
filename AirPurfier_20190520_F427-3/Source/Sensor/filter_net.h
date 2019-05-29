#ifndef __filter_net_h
#define __filter_net_h

#include "stm32f4xx.h"


// STM32C8T6 64KB FLASH,20KB RAM,1???1KB,????0x8000000
#define STARTADDR    ((uint32_t)0x08070000)


typedef struct
{
    uint8_t enabled;
    float useTime;
	unsigned short hours;
	unsigned char NoFilterCount;
	unsigned int times;
} filterNetStruct_t;

void filterNetInit(void);
void filterNetUpdate(void);

extern filterNetStruct_t filterNetData;

typedef enum
{ 
  FLASH_FAILURE = 0,
  FLASH_SUCCESS,
} flash_status_t;


flash_status_t FlashErase(uint32_t addr, uint8_t count);
extern void FlashWrite(uint32_t WriteAddress, int32_t WriteData);
extern uint32_t FlashRead(uint32_t addr, uint8_t *buffer, uint32_t length);

#endif /* __filter_net_h */

/* end of file */
