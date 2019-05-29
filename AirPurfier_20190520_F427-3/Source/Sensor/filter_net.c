#include "filter_net.h"
#include "string.h"
#include "ui.h"

#include "eeprom.h"
#include "parameter.h"
#include "st7789.h"
#include "supervisor.h"
#include "motor.h"

#include "digital.h"
#include "timer.h"

#include "motor.h"
#include "granule.h"
#include "humidity.h"
#include "voc.h"
#include "sensor.h"
#include "methanal.h"
filterNetStruct_t filterNetData;

void filterNetInit(void)
{
//	unsigned char filter_array[4];
	
	uint16_t filter_timer_L = 0;
	uint16_t filter_timer_H = 0;
	
	uint16_t motor_level;
	
    /* Tag标签 TTL电平 PD13, 低电平滤网有效 */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    /* General GPIO */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
//	while(GPIOD->IDR & GPIO_Pin_13)	
//	{
//		
//	}
//	FlashRead(STARTADDR,filter_array,4);
//	test_percent = filter_array[0];
	if ((EE_ReadVariable(PARAM_FITER_TIME_L, &filter_timer_L) == 0) && (EE_ReadVariable(PARAM_FITER_TIME_H, &filter_timer_H) == 0))
	{
		filterNetData.hours = filter_timer_L | (filter_timer_H << 16);
	}
	else 
	{
		filterNetData.hours = 0;
	}
	test_percent = 100 - filterNetData.hours/27;	
	test_percent = constrain(test_percent,0,100);
	
	if ((EE_ReadVariable(PARAM_MOTOR_LEVEL, &motor_level) == 0))
	{
		motorData.setSpeedLevel = (u8)motor_level;
	}
	if ((EE_ReadVariable(PARAM_MOTOR_MODE, &motor_level) == 0))
	{
		if(motor_level)
		{
			motorData.autoModeEnable = 1;
		}
		else
		{
			motorData.autoModeEnable = 0;
		}
	}
	
}

void filterNetUpdate(void)
{
	if(uwTick > 5000)
	{
    if (GPIOD->IDR & GPIO_Pin_13)
    {
			 filterNetData.NoFilterCount++;
			if(filterNetData.NoFilterCount > 100)
			{
				filterNetData.enabled = 0;
				uiData.leftMode = UI_LEFT_POWER_OFF;
				uiData.rightMode = UI_RIGHT_POWER_OFF;
				//关闭电机
				TIM3->CCR2 = 0;
				if(uiData.leftDisplay == 1)
				{
					if(uwTick - filterNetData.times < 500)
					{
						LCD_Default(LCD1);
						LCD_Default(LCD2);
					}
					else if(uwTick - filterNetData.times < 1000)
					{
						lcdDrawIcon(LCD1, 90, 80, POWER_ON_OFF, 72, 70, RED);
					}
					else
					{
						filterNetData.times = uwTick;
					}
				}
			}
    }
    else
    {
			filterNetData.NoFilterCount = 0;
//			if(filterNetData.enabled == 0)
//			{
//				sysledofftimes = 0;
//				lcdDrawIcon(LCD1, 90, 80, POWER_ON_OFF, 72, 70, RED);
//			}
      filterNetData.enabled = 1;
			
//			if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0)&&(uiData.leftMode != UI_LEFT_SLEEP))
//			{
//				if(uiData.leftMode != UI_LEFT_POWER_OFF)
//				{
//					uiData.leftMode = UI_LEFT_POWER_OFF;
//					uiData.rightMode = UI_RIGHT_POWER_OFF;
//				}
//    
//				uiData.leftDisplay = 1;
//				uiData.rightDisplay = 0;
//				LCD_Default(LCD2);
//				LCD_BL_1;
//				LCD2_BL_1;
//				motorData.setSpeedLevel = 0;
//				motorData.outputreal = 0;
////				leftLcdChange(uiData.leftMode);
////				rightLcdChange(uiData.rightMode);
//			}
    }
	}
}

/* end of file */
