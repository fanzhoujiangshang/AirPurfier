#ifndef __encoder_h
#define __encoder_h

#include "afx.h"

typedef struct
{
    int8_t left;
    int8_t right;
//    uint8_t leftFlag;
//    uint8_t rightFlag;
    uint32_t leftUpdateTick;
    uint32_t rightUpdateTick;
} encoderStruct_t;

void encoderInit(void);
void encoderUpdate(void);
extern void encoderUpdate_ledUp(void);

extern encoderStruct_t encoderData;

#endif /* __encoder_h */

/* end of file */
