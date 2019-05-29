#ifndef __BATTERY_H
#define __BATTERY_H

#include "afx.h"

typedef struct
{
	uint8_t cell;			/* ��о���� */
	uint16_t adc;			/* ADCת��ֵ */
	uint16_t voltage;		/* ��ص�ѹ */
	uint16_t percent;		/* �����ٷֱ� */
	uint8_t level;			/* �͵�ȼ� */
	uint8_t low_voltage_1;	/* 1���͵��жϰٷֱ� */
	uint8_t low_voltage_2;	/* 2���͵��жϰٷֱ� */
	uint8_t charged;	    /* ���״̬��� */
}  __attribute__((packed)) _battery_t;

void batteryInit(void);
uint16_t batteryGetVoltage(uint16_t _adc);
uint16_t batteryGetPercent(uint16_t _voltage);
void batteryMonitor(void);

extern _battery_t battery;

#endif /* __BATTERY_H */

/* end of file */
