#ifndef __ec20_h
#define __ec20_h

#include "afx.h"

#include "serial.h"

#define E20_PWR_H GPIO_SetBits(GPIOD,GPIO_Pin_12);
#define E20_PWR_L GPIO_ResetBits(GPIOD,GPIO_Pin_12);

typedef struct
{
  serialPort_t *serialPort;
  uint8_t enabled;
	uint32_t lastReceviedTick;
	uint32_t lastReceviedTick1;
	uint32_t StatusSendTick;
	uint8_t recCnt;
	uint8_t recBuf[256];
} ec20TaskStruct_t;

void ec20Init(void);

extern ec20TaskStruct_t ec20TaskData;

#endif /* __ec20_h */

/* end of file */
