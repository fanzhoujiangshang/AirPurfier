#ifndef __sensor_h
#define __sensor_h

#include "afx.h"

typedef struct
{
    uint16_t aqi;
    uint8_t overload[3];
} sensorStruct_t;

void sensorInit(void);
void sensorUpdate(void);

extern sensorStruct_t sensorData;;

#endif /* __sensor_h */
