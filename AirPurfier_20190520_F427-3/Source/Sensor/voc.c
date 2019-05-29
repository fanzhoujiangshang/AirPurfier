#include "voc.h"
#include "timer.h"

vocStruct_t vocData;

void vocInit(void)
{
    /* rf_mmv02输出脉宽周期104ms，若当前脉宽X ms，则污染级别为X-2 */
    /* 采用外部中断记录上升沿和下降沿的时刻 */
    
    /* PC9，TIM3 CH4 */
    EXTI_InitTypeDef   EXTI_InitStructure;
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    
    /* Enable GPIOE and AFIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
    /* Configure PC.09 pin as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Connect EXTI9 Line to PC.09 pin */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource9);

    /* Configure EXTI9_5 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line9;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    //    /* Enable and set EXTI9_5 Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Generate software interrupt: simulate a falling edge applied on EXTI9_5 line */
//    EXTI_GenerateSWInterrupt(EXTI_Line9);
}

void vocUpdate(void)
{
    if (vocData.lastUpdateTick + 1000 < uwTick)
    {
        if (vocData.val < 0.6f)
        {
            vocData.level = 0;
        }
        else if (vocData.val < 3.0f)
        {
            vocData.level = 1;
        }
        else if (vocData.val < 25.0f)
        {
            vocData.level = 2;
        }
        else
        {
            vocData.level = 3;
        }
    }
}

/* end of file */
