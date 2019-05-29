#include "power.h"
#include "digital.h"
#include "timer.h"

uint32_t rc_power_tick = 0;

void powerButtonInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = PWR_ANDROID_CHECK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_Init(PWR_ANDROID_CHECK_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = BTN_PWR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_Init(BTN_PWR_PORT, &GPIO_InitStructure);
}

void delay(volatile uint32_t tick)
{
    while (tick--);
}

uint32_t cnt = 0;

void powerPinInit(void)
{
    powerButtonInit();
    
    digitalInit(PWR_RC_PORT, PWR_RC_PIN, 1);
    
    digitalInit(LED_POWER_PORT, LED_POWER_PIN, 1);
    
    // delay(0xffff);
    
    while (BTN_PWR_PORT->IDR & BTN_PWR_PIN);
    
    delay(0xfff);
    digitalInit(GPIOC, GPIO_Pin_7, 1);
    
    while (1)
    {
        cnt = 0;
        while ((BTN_PWR_PORT->IDR & BTN_PWR_PIN) == 0)
        {
            cnt++;
            
            if (cnt > 0x1fffff)
            {
                GPIO_ResetBits(PWR_RC_PORT, PWR_RC_PIN);
            }
        }
        
        cnt = 0;
        
        while (BTN_PWR_PORT->IDR & BTN_PWR_PIN)
        {
            cnt++;
            
            if (cnt > 0x1fffff)
            {
                GPIO_SetBits(PWR_RC_PORT, PWR_RC_PIN);
                break;
            }
        }
        
        if (cnt > 0x1fffff)
        {
            break;
        }
    }
    
    /* 安卓关机解发信号脚 */
    digitalInit(PWR_ANDROID_TRIGGER_PORT, PWR_ANDROID_TRIGGER_PIN, 0);
    
    /* 初始化系统电源控制引脚、数传电源控制引脚、图传电源控制引脚、安卓板电源 */
    digitalInit(PWR_RADIO_PORT, PWR_RADIO_PIN, 1);
    
	digitalInit(PWR_VIDEO_PORT, PWR_VIDEO_PIN, 1);
    digitalInit(PWR_ANDROID_PORT, PWR_ANDROID_PIN, 1);
//    powerButtonInit();
//    
//    digitalInit(PWR_RC_PORT, PWR_RC_PIN, 1);
//    
//    digitalInit(LED_POWER_PORT, LED_POWER_PIN, 1);
//    
//    delay(0xfffff);
//    
//    while (GPIOD->IDR & GPIO_Pin_4);
//    
//    delay(0xfff);
//    digitalInit(GPIOD, GPIO_Pin_14, 1);
//    
//    while (1)
//    {
//        while ((GPIOD->IDR & GPIO_Pin_4) == 0)
//        {
//            cnt++;
//            
//            if (cnt > 0x1fffff)
//            {
//                GPIO_ResetBits(GPIOD, GPIO_Pin_5);
//            }
//        }
//        
//        cnt = 0;
//        
//        while (GPIOD->IDR & GPIO_Pin_4)
//        {
//            cnt++;
//            
//            if (cnt > 0x1fffff)
//            {
//                GPIO_SetBits(GPIOD, GPIO_Pin_5);
//                break;
//            }
//        }
//        
//        if (cnt > 0x1fffff)
//        {
//            break;
//        }
//    }
//    
//    digitalInit(GPIOD, GPIO_Pin_0, 0);
//    
//    /* 初始化系统电源控制引脚、数传电源控制引脚、图传电源控制引脚、安卓板电源 */
//    digitalInit(PWR_RADIO_PORT, PWR_RADIO_PIN, 1);
//    
//	digitalInit(PWR_VIDEO_PORT, PWR_VIDEO_PIN, 1);
//    digitalInit(PWR_ANDROID_PORT, PWR_ANDROID_PIN, 1);
}

inline void powerSystemHold(void)
{
    GPIO_ResetBits(PWR_RC_PORT, PWR_RC_PIN);
}

inline void powerSystemHalt(void)
{
    GPIO_SetBits(PWR_RC_PORT, PWR_RC_PIN);
}

inline void powerRadioHold(void)
{
    GPIO_SetBits(PWR_RADIO_PORT, PWR_RADIO_PIN);
}

inline void powerRadioHalt(void)
{
    GPIO_ResetBits(PWR_RADIO_PORT, PWR_RADIO_PIN);
}

inline void powerVideoHold(void)
{
    GPIO_SetBits(PWR_VIDEO_PORT, PWR_VIDEO_PIN);
}

inline void powerVideoHalt(void)
{
    GPIO_ResetBits(PWR_VIDEO_PORT, PWR_VIDEO_PIN);
}

void directBoot(void)
{
    digitalInit(PWR_RC_PORT, PWR_RC_PIN, 1);
    digitalInit(PWR_ANDROID_TRIGGER_PORT, PWR_ANDROID_TRIGGER_PIN, 0);
    
    /* 初始化系统电源控制引脚、数传电源控制引脚、图传电源控制引脚、安卓板电源 */
    digitalInit(PWR_RADIO_PORT, PWR_RADIO_PIN, 1);
    
	digitalInit(PWR_VIDEO_PORT, PWR_VIDEO_PIN, 1);
    digitalInit(PWR_ANDROID_PORT, PWR_ANDROID_PIN, 1);
}

void androidWorkMonitor(void)
{
    /* 检测到安卓已正常关机，则系统掉电 */
    if ((PWR_ANDROID_CHECK_PORT->IDR & PWR_ANDROID_CHECK_PIN) == 0 && (uwTick > 20000) && ((BTN_PWR_PORT->IDR & BTN_PWR_PIN) == 0))
    {
        GPIO_ResetBits(PWR_ANDROID_PORT, PWR_ANDROID_PIN);
        GPIO_ResetBits(PWR_RC_PORT, PWR_RC_PIN);
    }
}

void androidShutdownTrigger(void)
{
    /* 维持一秒以上的高电平，触发安卓关机 */
    if (rc_power_tick + 1000 < uwTick)
    {
        GPIO_ResetBits(PWR_ANDROID_TRIGGER_PORT, PWR_ANDROID_TRIGGER_PIN);
    }
}

/* end of file */
