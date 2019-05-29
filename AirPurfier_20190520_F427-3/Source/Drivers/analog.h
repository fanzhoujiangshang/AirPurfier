#ifndef __ANALOG_H
#define __ANALOG_H

#include "afx.h"

typedef struct
{
	volatile uint16_t value[ADC_NUM];
}_adc_t;

void analogInit(void);
uint16_t batteryGetADC(void);

extern _adc_t adc;

#endif /* __ANALOG_H */

/* end of file */
