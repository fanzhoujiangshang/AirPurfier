#ifndef __granule_h
#define __granule_h

#include "digital.h"
#include "serial.h"

typedef enum {
    granuleMode_Active = 0,
    granuleMode_Passive = 1
} granuleMode_t;

typedef struct
{
    serialPort_t *serialPort;
    uint8_t enabled;
    granuleMode_t mode;
    float mmol;
	float ugm3;
	
	float temp_ugm3;
    
    uint16_t data[12];
    uint8_t version;
    uint8_t errCode;

    uint8_t receiveBuf[32];
    uint8_t checkByte[2];
    uint8_t parseStatus;
    uint8_t packetType;
    
    uint8_t level;
    float pm25;
} granuleStruct_t;

void granuleInit(void);
void granuleUpdate(void);

extern granuleStruct_t granuleData;

#endif /* __granule_h */

/* end of file */
