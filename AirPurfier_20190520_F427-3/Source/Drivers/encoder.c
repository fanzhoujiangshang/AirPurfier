#include "encoder.h"
#include "timer.h"
#include "ui.h"
#include "st7789.h"
#include "supervisor.h"

encoderStruct_t encoderData = {
    .left = 0,
    .right = 0,
//    .leftFlag = 0,
//    .rightFlag = 0,
    .leftUpdateTick = 0,
    .rightUpdateTick = 0
};

uint8_t lastPin[4] = { 0 };
uint8_t lastPin1[4] = { 0 };

/* 15个脉冲/360度, 采用外部中断的方式来，捕捉A段信号上升沿，并检测此时B信号的电平。若为高电平，则反转；否则正转 */
void encoderInit(void)
{
    /* 引脚定义
       BC-L: PE5
       AC-L: PE6
       BC-R: PE14
       AC-R: PE15
    */
    
//    EXTI_InitTypeDef   EXTI_InitStructure;
//    GPIO_InitTypeDef   GPIO_InitStructure;
//    NVIC_InitTypeDef   NVIC_InitStructure;
//    
//    /* Enable GPIOE and AFIO clock */
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

//    /* Configure PE.05 PE.06 PE.14 PE15 pin as input floating */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_14 | GPIO_Pin_15;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//    GPIO_Init(GPIOE, &GPIO_InitStructure);
//	
//	  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);
//		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
//		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource14);
//		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource15);
//    /* Configure EXTI13 line */
//    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//		
//		EXTI_InitStructure.EXTI_Line = EXTI_Line6;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//		
//		EXTI_InitStructure.EXTI_Line = EXTI_Line14;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//		
//		EXTI_InitStructure.EXTI_Line = EXTI_Line15;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//    
//    /* Enable and set EXTI15_10 Interrupt to the lowest priority */
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//	
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

//    lastPin[0] = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);
//    lastPin[1] = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6);
//    lastPin[2] = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14);
//    lastPin[3] = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15);

    EXTI_InitTypeDef   EXTI_InitStructure;
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;
    
    /* Enable GPIOE and AFIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* Configure PE.05 PE.06 PE.14 PE15 pin as input floating */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource7);
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource6);
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource14);
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource15);
    /* Configure EXTI13 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
		
		EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
		
		EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
		
		EXTI_InitStructure.EXTI_Line = EXTI_Line15;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    /* Enable and set EXTI15_10 Interrupt to the lowest priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    lastPin[0] = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);
    lastPin[1] = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6);
    lastPin[2] = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14);
    lastPin[3] = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15);
}

void encoderUpdate(void)
{
    uint8_t a = 0, b = 0;
    
    /* 直接用查询的方式 */
    /* 若状态发生变化, 则根据两引脚电平是否一至, 从而判断正转或反转 */
    a = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);
    b = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6);
    
    if (lastPin[0] != a)
    {
				
        uiData.leftDisplay = 1;
        uiData.rightDisplay = 1;
		
				LCD_BL_1;
				LCD2_BL_1;
				sysledofftimes = 0; //重新计时
				syssleeptimes = uwTick;
				//rightLast = 0;
				leftLast = 0;
        
        if (a == b)
        {
            encoderData.left--;
            
            if (uiData.leftMode != UI_LEFT_POWER_OFF)
            {
								encoderData.leftUpdateTick = uwTick;
                if (uiData.leftMode == UI_LEFT_POWER_ON)
                {
                    uiData.leftMode = UI_LEFT_SLEEP;
                }
                else
                {
                    uiData.leftMode--;
                }
//				if (uiData.leftMode == UI_LEFT_POWER_ON)
//                {
//                    uiData.leftMode = UI_LEFT_FILTER;
//                }
//                else
//                {
//                    uiData.leftMode--;
//                }
            }
            yield(100);
        }
        else
        {
            encoderData.left++;
            
            if (uiData.leftMode != UI_LEFT_POWER_OFF)
            {
								encoderData.leftUpdateTick = uwTick;
                if (uiData.leftMode == UI_LEFT_SLEEP)
                {
                    uiData.leftMode = UI_LEFT_POWER_ON;
                }
                else
                {
                    uiData.leftMode++;
                }
            }
					yield(100);
        }
        
        lastPin[0] = a;
        lastPin[1] = b;
//        encoderData.leftUpdateTick = uwTick;
    }
    
    a = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14);
    b = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15);
    
    if (lastPin[2] != a)
    {		
        uiData.leftDisplay = 1;
        uiData.rightDisplay = 1;
		
				LCD_BL_1;
				LCD2_BL_1;
				sysledofftimes = 0; //重新计时
				syssleeptimes = uwTick;
			
				rightLast = 0;
				//leftLast = 0;
        
        uiData.warnModeRun = 0;
			
				if(uiData.leftMode == UI_LEFT_SLEEP)
				{
					uiData.leftMode = UI_LEFT_POWER_ON;
				}
        
        if (a == b)
        {
            encoderData.right--;
            
            if (uiData.rightMode != UI_RIGHT_POWER_OFF)
            {
								encoderData.rightUpdateTick = uwTick;
                if (uiData.rightMode == UI_RIGHT_AQI)
                {
                    uiData.rightMode = UI_RIGHT_FILTER;
                }
                else
                {
                    uiData.rightMode--;
                }
            }
            yield(100);
        }
        else
        {
            encoderData.right++;
            
            if (uiData.rightMode != UI_RIGHT_POWER_OFF)
            {
								encoderData.rightUpdateTick = uwTick;
                if (uiData.rightMode == UI_RIGHT_FILTER)
                {
                    uiData.rightMode = UI_RIGHT_AQI;
                }
                else
                {
                    uiData.rightMode++;
                }
            }
            yield(100);
        }
        
        lastPin[2] = a;
        lastPin[3] = b;
//        encoderData.rightUpdateTick = uwTick;
    }

//    if ((encoderData.leftFlag) && (uwTick - encoderData.leftUpdateTick > 3))
//    {
//        encoderData.leftFlag = 0;
//        
//        a = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);
//        b = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6);
//        
//        if (a == b)
//        {
//            encoderData.left++;
//        }
//        else
//        {
//            encoderData.left--;
//        }
//    }
//    
//    if ((encoderData.rightFlag) && (uwTick - encoderData.rightUpdateTick > 3))
//    {
//        encoderData.rightFlag = 0;
//        
//        a = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14);
//        b = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15);
//        
//        if (a == b)
//        {
//            encoderData.right++;
//        }
//        else
//        {
//            encoderData.right--;
//        }
//    }
}

void encoderUpdate_ledUp(void)
{
 uint8_t a = 0, b = 0;
    
    /* 直接用查询的方式 */
    /* 若状态发生变化, 则根据两引脚电平是否一至, 从而判断正转或反转 */
    a = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7);
    b = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6);
    
    if (lastPin1[0] != a)
    {
//				if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
//				{
//					if((uiData.leftMode == UI_LEFT_POWER_OFF)&&(uwTick > 5000))
//					{
//						SystemInit();
//						sysledofftimes = 0;
//					}
//				}
				uiData.leftMode = UI_LEFT_POWER_OFF;
				uiData.rightMode = UI_RIGHT_POWER_OFF;
        uiData.leftDisplay = 1;
        uiData.rightDisplay = 1;
		
				LCD_BL_1;
				LCD2_BL_1;
				sysledofftimes = 0; //重新计时
        
        lastPin1[0] = a;
        lastPin1[1] = b;
        encoderData.leftUpdateTick = uwTick;
    }
    
    a = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14);
    b = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15);
    
    if (lastPin1[2] != a)
    {
//				if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
//				{
//					if((uiData.leftMode == UI_LEFT_POWER_OFF)&&(uwTick > 5000))
//					{
//						SystemInit();
//						sysledofftimes = 0;
//					}
//				}
				uiData.leftMode = UI_LEFT_POWER_OFF;
				uiData.rightMode = UI_RIGHT_POWER_OFF;
        uiData.leftDisplay = 1;
        uiData.rightDisplay = 1;
		
				LCD_BL_1;
				LCD2_BL_1;
				sysledofftimes = 0; //重新计时
        
        uiData.warnModeRun = 0;
        
        lastPin1[2] = a;
        lastPin1[3] = b;
        encoderData.rightUpdateTick = uwTick;
    }

}

/* end of file */
