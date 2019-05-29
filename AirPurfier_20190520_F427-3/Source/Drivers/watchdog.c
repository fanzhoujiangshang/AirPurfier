#include "watchdog.h"
#include "timer.h"

void WatchDogMonitor(void)
{
	static uint32_t dogfeed_tick = 0;
	
	/* 100ms喂狗一次, 超过1s不喂则复位单片机 */
    if (uwTick - dogfeed_tick > 100)
	{
		WatchDogFeed();
	}
}

/**
 * 喂独立看门狗
 */
static void IWDGInit(void)
{	
	/* 超过1s不喂狗，复位单片机  32KHz / 128 * 255 = 1Hz */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	/* 使能对寄存器IWDG_PR和IWDG_RLR的写操作*/
    IWDG_SetPrescaler(IWDG_Prescaler_128);    		/* 设置IWDG预分频值:设置IWDG预分频值*/
    IWDG_SetReload(0xff);		/* 设置IWDG重装载值*/
    IWDG_ReloadCounter();		/* 按照IWDG重装载寄存器的值重装载IWDG计数器*/
    IWDG_Enable();				/* 使能IWDG*/
}

static void IWDGFeed(void)
{
    IWDG_ReloadCounter();    /*reload*/
}

#ifdef USE_WWDG
/* 喂狗 */
static void WWDGInit(void)
{
	/* 窗口看门狗 */
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

/* 看门狗初始化 */
void WatchDogInit(void)
{
	IWDGInit();
	
#ifdef USE_WWDG
	WWDGInit();
#endif /* USE_WWDG */
}

void WatchDogFeed(void)
{
	/* 重载独立看门狗 */
	IWDGFeed();
	
#ifdef USE_WWDG
	/* 重载窗口看门狗 */
	WWDGFeed();
#endif /* USE_WWDG */
}

/* end of file */
