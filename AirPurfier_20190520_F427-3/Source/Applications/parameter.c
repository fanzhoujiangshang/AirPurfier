#include "parameter.h"
#include "eeprom.h"

const uint16_t VirtAddVarTab[NB_OF_VAR] = { PARAM_FITER_TIME_L, PARAM_FITER_TIME_H, 0x5557, 0x5558, 0x5559, 0x555a, 0x555b, 0x555c, \
    0x555d, 0x555e, 0x555f, 0x5560, 0x5561, 0x5562, 0x5563 };

uint32_t mcuID[3] = { 0 };

void systemReadID(void)
{
	mcuID[0] = *(volatile uint32_t *)(0x1ffff7e8);
	mcuID[1] = *(volatile uint32_t *)(0x1ffff7ec);
	mcuID[2] = *(volatile uint32_t *)(0x1ffff7f0);
}

void parameterInit(void)
{
	/* 读取单片机唯一编号 */
	systemReadID();
    
    /* 读取遥控器通道数据 */
}

/* end of file */
