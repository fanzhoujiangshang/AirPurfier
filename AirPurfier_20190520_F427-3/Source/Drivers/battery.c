#include "FreeRTOS.h"
#include "task.h"
#include "battery.h"
#include "afx_math.h"

/* 全局变量 */
_battery_t battery = {
	.cell = BATTERY_CELL_NUM,
	.adc = 0,
	.voltage = 42 * BATTERY_CELL_NUM,
	.percent = 100,
	.level = 0,
	.low_voltage_1 = 30,
	.low_voltage_2 = 15,
	.charged = 0
};

void rcBatteryTask(void *pvParameters);
uint16_t batteryGetVoltage(uint16_t _adc);
uint16_t batteryGetPercent(uint16_t _voltage);

void batteryMonitor(void)
{
	static uint32_t battery_tick = 0;
	
	battery.adc = batteryGetADC();

    /* 电量计算频率10Hz */
	if (TimInterval(&battery_tick, 100))
	{
        /* 检测充电状态 */
        if (GPIOE->IDR & GPIO_Pin_8)
        {
            battery.charged = 1;
        }
        else
        {
            battery.charged = 0;
        }
    
		if (battery.adc > 1000) /* 低于1000为异常 */
		{
			battery.voltage = batteryGetVoltage(battery.adc);
			battery.percent = batteryGetPercent(battery.voltage);
			
			/* 电压等级计算 */
            if (battery.percent > battery.low_voltage_1)
            {
                battery.level = 0;
            }
            else if (battery.percent > battery.low_voltage_2)
            {
                battery.level = 1;
            }
            else
            {
                battery.level = 2;
			}
		}
	}
}

void chargePortInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void batteryInit(void)
{
	chargePortInit();
}

uint16_t _adc_array[64]; 
uint32_t _adc_array_sum = 0;

uint16_t batteryGetVoltage(uint16_t _adc)
{
	static uint8_t _filter_init_flag = 1;
	static uint8_t _index = 0;
	
	uint16_t _voltage = 0;
	uint16_t _adc_filter = 0;
	uint16_t i = 0;
	
	/* 填充滑动滤波器初始化数据, 滤波器长度为50 */
	if (_filter_init_flag == 1)
	{
		_filter_init_flag = 0;
		
		for (i = 0; i < 64; i++)
		{
			_adc_array[i] = _adc;
		}
		
		_adc_array_sum = _adc << 6;
	}
	
	/* 记录新数据，删除旧数据，完成滑动滤波 */
	_adc_array_sum = _adc_array_sum + _adc - _adc_array[_index];
//    
//    _adc_array_sum = 0;
//    
//    for (i = 0; i < 64; i++)
//    {
//        _adc_array_sum += _adc_array[i];
//    }
	_adc_filter = _adc_array_sum >> 6;
	_adc_array[_index] = _adc;
	
	_index++;
	if (_index >= 64)
	{
		_index = 0;
	}
	
	/* 根据平滑后的ADC值，计算实际电压值 电阻分压 27/(100+27) */
	_voltage = _adc_filter / 4095.0f * 3300.0f / 0.2107f;//0.2126f;
	
	return _voltage;
}

uint16_t batteryGetPercent(uint16_t _voltage)
{
	int16_t _percent = 0;
    
    _percent = (_voltage / battery.cell - 3500) / 7.0f;

	_percent = constrain(_percent, 0, 100);
	
	return (uint16_t)_percent;
}

/* end of file */
