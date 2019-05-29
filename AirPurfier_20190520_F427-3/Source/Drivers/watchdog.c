#include "watchdog.h"
#include "timer.h"

void WatchDogMonitor(void)
{
	static uint32_t dogfeed_tick = 0;
	
	/* 100msι��һ��, ����1s��ι��λ��Ƭ�� */
    if (uwTick - dogfeed_tick > 100)
	{
		WatchDogFeed();
	}
}

/**
 * ι�������Ź�
 */
static void IWDGInit(void)
{	
	/* ����1s��ι������λ��Ƭ��  32KHz / 128 * 255 = 1Hz */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	/* ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����*/
    IWDG_SetPrescaler(IWDG_Prescaler_128);    		/* ����IWDGԤ��Ƶֵ:����IWDGԤ��Ƶֵ*/
    IWDG_SetReload(0xff);		/* ����IWDG��װ��ֵ*/
    IWDG_ReloadCounter();		/* ����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������*/
    IWDG_Enable();				/* ʹ��IWDG*/
}

static void IWDGFeed(void)
{
    IWDG_ReloadCounter();    /*reload*/
}

#ifdef USE_WWDG
/* ι�� */
static void WWDGInit(void)
{
	/* ���ڿ��Ź� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	WWDG_SetPrescaler(WWDG_Prescaler_8);                         
	WWDG_SetWindowValue(0x00);        
	WWDG_Enable(0x40);
}

static void WWDGFeed(void)
{
	WWDG_SetCounter(127);
}
#endif /* USE_WWDG */

/* ���Ź���ʼ�� */
void WatchDogInit(void)
{
	IWDGInit();
	
#ifdef USE_WWDG
	WWDGInit();
#endif /* USE_WWDG */
}

void WatchDogFeed(void)
{
	/* ���ض������Ź� */
	IWDGFeed();
	
#ifdef USE_WWDG
	/* ���ش��ڿ��Ź� */
	WWDGFeed();
#endif /* USE_WWDG */
}

/* end of file */
