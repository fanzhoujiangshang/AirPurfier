/**
*******************************************************************************
* @file      digital.c
* @version   V1.0
* @date      2016.11.23
* @brief     数字量读入驱动
*******************************************************************************
* @copy
*
* @author	
*******************************************************************************
*/

/*---------------------------- Include ---------------------------------------*/
#include "digital.h"

#define PERIPH2BB(addr, bit)        ((uint32_t *)(PERIPH_BB_BASE + ((addr) - PERIPH_BASE) * 32 + ((bit) * 4)))

uint32_t *digitalInit(GPIO_TypeDef* port, const uint16_t pin, uint8_t initial) {
    GPIO_InitTypeDef GPIO_InitStructure;
    uint32_t *bbAddr;
    uint16_t myPin = pin;
    uint8_t bit;

    bit = 0;
    while (myPin >>= 1)
        bit++;

    if (bit < 8)
        bbAddr = PERIPH2BB((uint32_t)port + 0x14, bit);
    else
        bbAddr = PERIPH2BB((uint32_t)port + 0x15, bit-8);

    *bbAddr = initial;

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(port, &GPIO_InitStructure);

    return bbAddr;
}
