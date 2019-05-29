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
    
    rtcInit();              /* RTKʱ�ӳ�ʼ�� */
    timerInit();            /* ��ʱ��ʵʼ��, ������/���PWM */
    
    ec20Init();             /* 4G GSMģ���ʼ�� */
        
    supervisorInit();       /* ϵͳ�������, ���������� */
	
		uiInit();               /* UI */
	
	vTaskDelete(NULL);		/* ɾ����ʼ������ */
}

void ResetCheck(void)
{
	/* ��λ��� */
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
