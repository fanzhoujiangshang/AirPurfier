#ifndef __methanal_h
#define __methanal_h

#include "serial.h"

typedef enum {
    methanalMode_Active = 0,
    methanalMode_Passive = 1
} methanalMode_t;

typedef struct
{
    serialPort_t *serialPort;
    uint8_t enabled;
    methanalMode_t mode;
    float mmol;
    
    uint32_t updateTick;

    uint8_t receiveBuf[9];
    uint8_t checkByte;
    uint8_t parseStatus;
    uint8_t packetType;
    
    uint8_t level;
} methanalStruct_t;

void methanalInit(void);
void methanalUpdate(void);

extern methanalStruct_t methanalData;

#endif /* __methanal_h */

/* end of file */
