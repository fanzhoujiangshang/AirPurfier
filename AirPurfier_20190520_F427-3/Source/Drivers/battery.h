#ifndef __BATTERY_H
#define __BATTERY_H

#include "afx.h"

typedef struct
{
	uint8_t cell;			/* 电芯数量 */
	uint16_t adc;			/* ADC转换值 */
	uint16_t voltage;		/* 电池电压 */
	uint16_t percent;		/* 电量百分比 */
	uint8_t level;			/* 低电等级 */
	uint8_t low_voltage_1;	/* 1级低电判断百分比 */
	uint8_t low_voltage_2;	/* 2级低电判断百分比 */
	uint8_t charged;	    /* 充电状态检测 */
}  __attribute__((packed)) _battery_t;

void batteryInit(void);
uint16_t batteryGetVoltage(uint16_t _adc);
uint16_t batteryGetPercent(uint16_t _voltage);
void batteryMonitor(void);

extern _battery_t battery;

#endif /* __BATTERY_H */

/* end of file */
