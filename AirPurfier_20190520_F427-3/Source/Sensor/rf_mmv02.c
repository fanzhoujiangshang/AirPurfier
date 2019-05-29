#include "rf_mmv02.h"
rf_mmv02Struct_t rf_mmv02Data;

/* ��������104ms������ǰ����X ms������Ⱦ����ΪX-2 */
/* �����ⲿ�жϼ�¼�����غ��½��ص�ʱ�� */
void rf_mmv02Init(void)
{
    /* PC9��TIM3 CH4 */
    EXTI_InitTypeDef   EXTI_InitStructure;
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    
    /* Enable GPIOE and AFIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

    /* Configure PC.09 pin as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Connect EXTI9 Line to PC.09 pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);

    /* Configure EXTI9_5 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line9;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Generate software interrupt: simulate a falling edge applied on EXTI9_5 line */
//    EXTI_GenerateSWInterrupt(EXTI_Line9);
}
