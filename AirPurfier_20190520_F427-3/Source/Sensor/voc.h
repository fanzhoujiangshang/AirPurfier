#ifndef __voc_h
#define __voc_h

#include "stm32f4xx.h"

typedef struct
{
    uint16_t raisingHDTick;
    uint16_t fallingHDTick;
    uint16_t deltaHDTick;
    float val;
    uint8_t level;
    uint32_t lastUpdateTick;
} vocStruct_t;

void vocInit(void);
void vocUpdate(void);

extern vocStruct_t vocData;

#endif /* __voc_h */

/* end of file */
