#include "afx_init.h"
#include "timer.h"
#include "version.h"
#include "eeprom.h"
#include "parameter.h"

#include "rtc.h"

#include "ec20.h"
#include "sensor.h"
#include "motor.h"
#include "ui.h"
#include "supervisor.h"

void afxInitTask(void *pvParameter)
{
    versionInit();          /* ????? */
		pid_Init();
    FLASH_Unlock();
    EE_Init();				/* ??EEPROM??? */
    parameterInit();        /* ??????? */
    
    rtcInit();              /* RTK时钟初始化 */
    timerInit();            /* 定时器实始化, 蜂鸣器/电机PWM */
    
    ec20Init();             /* 4G GSM模块初始化 */
        
    supervisorInit();       /* 系统监测任务, 传感器更新 */
	
		uiInit();               /* UI */
	
	vTaskDelete(NULL);		/* 删除初始化任务 */
}

void ResetCheck(void)
{
	/* 复位检测 */
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		RCC_ClearFlag();
	}
	
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET)
	{
		RCC_ClearFlag();
	}
}

void vApplicationMallocFailedHook(void)
{
    while (1);
}

/* end of file */
