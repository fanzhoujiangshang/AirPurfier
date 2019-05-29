#include "exti_irq.h"
#include "timer.h"
#include "encoder.h"
#include "voc.h"
#include "motor.h"
#include "i2c.h"
#include "st7789.h"
#include "touch.h"
#include "sensor.h"
#include "ui.h"
#include "supervisor.h"

/**
  * @brief  This function handles External lines 0 interrupt request.
  * @param  None
  * @retval None
  */
  
u8 Reg_Addr = 0x03;
// 小于40 是左 大于80是右 其他是中间
u32 poweron_count;
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
		I2C_ReadOneByte(FT_ADDR,Reg_Addr,&TF1touchdata.temp_data[0]);
		I2C_ReadOneByte(FT_ADDR,Reg_Addr + 1,&TF1touchdata.temp_data[1]);
		TF1touchdata.x_position = ((TF1touchdata.temp_data[0]&0x0f)<<8)|TF1touchdata.temp_data[1];
		I2C_ReadOneByte(FT_ADDR,Reg_Addr + 2,&TF1touchdata.temp_data[2]);
		I2C_ReadOneByte(FT_ADDR,Reg_Addr + 3,&TF1touchdata.temp_data[3]);
		TF1touchdata.y_position = ((TF1touchdata.temp_data[2]&0x0f)<<8)|TF1touchdata.temp_data[3];
		I2C_ReadOneByte(FT_ADDR,Reg_Addr + 4,&TF1touchdata.temp_data[4]);
		I2C_ReadOneByte(FT_ADDR,Reg_Addr + 5,&TF1touchdata.temp_data[5]);
		
		if((TF1touchdata.temp_data[0]>>6)==0)
		{
			if(TF1touchdata.status_press == false)
			{
				TF1touchdata.status_up = false;
				TF1touchdata.status_down = true;
				TF1touchdata.status_press = false;
				TF1touchdata.press_times = uwTick;
			}
			else 
			{
				TF1touchdata.status_up = true;
				TF1touchdata.status_down = false;
				TF1touchdata.status_press = false;
				
				if(uwTick - TF1touchdata.press_times >= 3000)
				{
					touchData.leftEvent = touchEvent_MiddleLong;
				}
				
				if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
				{
						GPIOA->BSRRL = GPIO_Pin_8;
						if(uiData.leftMode == UI_LEFT_SLEEP)
						{
							uiData.leftMode = UI_LEFT_POWER_ON;
							uiData.rightMode = UI_RIGHT_AQI;
						}
						else if(uiData.leftMode == UI_LEFT_POWER_OFF)
						{
							SystemInit();
							uiData.leftMode = UI_LEFT_POWER_OFF;
							uiData.rightMode = UI_RIGHT_POWER_OFF;
						}
//						methanalInit(); /* 甲醛传感器 */
						uiData.leftDisplay = 1;
						uiData.rightDisplay = 1;
						LCD_BL_1;
						LCD2_BL_1;
						rightLast = 0;
						leftLast = 0;
				}
				
				else if (TF1touchdata.x_position < 40)
				{
					//touchData.leftEvent = 1;
					touchData.leftEvent = touchEvent_Left;
				}
				else if (TF1touchdata.x_position > 80)
				{
					touchData.leftEvent = touchEvent_Right;
				}
				else
				{
					touchData.leftEvent = touchEvent_Middle;
				}
			}
			TF1touchdata.temp_data[0] = 0;
		}
		else if((TF1touchdata.temp_data[0]>>6)==1)
		{
			TF1touchdata.status_up = false;
			TF1touchdata.status_down = false;
			TF1touchdata.status_press = true;
			TF1touchdata.temp_data[0] = 1;
			if(uwTick - TF1touchdata.press_times >= 3000)
			{
				touchData.leftEvent = touchEvent_MiddleLong;
			}
		}
        /* Clear the EXTI line 0 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
		sysledofftimes = 0;
}


/**
  * @brief  This function handles External line 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line8) != RESET)
    {
        motorData.pulseCount++;
			
			  if (uwTick - motorData.lastCalTick >= 1000) /* 100ms */
				{
						motorData.lastCalTick = uwTick;
						
						motorData.rpm = motorData.pulseCount/12;
						motorData.pulseCount = 0;
				}
			
//				if(motorData.seq)
//				{
//					motorData.raisingHDTick2 = uwTick;
//					motorData.seq = false;
//					if(motorData.raisingHDTick2 > motorData.raisingHDTick1 + 5)
//					{
//						motorData.rpm = 60*1000 /((motorData.raisingHDTick2 - motorData.raisingHDTick1)*12);
//						if(motorData.rpm > 800)
//						{
//							motorData.rpm = motorData.rpm;
//						}
//					}
//				}	
//				else
//				{
//					motorData.raisingHDTick1 = uwTick;
//					motorData.seq = true;
//				}
//        
        /* Clear the EXTI line 0 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
    else if (EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9))
        {
            vocData.raisingHDTick = TIM4->CNT;
        }
        else 
        {
            vocData.fallingHDTick = TIM4->CNT;
					
						if(vocData.fallingHDTick > vocData.raisingHDTick)
						{
							vocData.deltaHDTick = vocData.fallingHDTick - vocData.raisingHDTick;
						}
            else if(vocData.fallingHDTick < vocData.raisingHDTick)
						{
							vocData.deltaHDTick = 0xffff - vocData.raisingHDTick + vocData.fallingHDTick;
						}
						else
						{
							vocData.deltaHDTick = 200;
						}
            //vocData.deltaHDTick = fabs(vocData.fallingHDTick - vocData.raisingHDTick);
						if(vocData.deltaHDTick <= 102)
						{
							vocData.deltaHDTick = 102;
						}
        
            vocData.level = (vocData.deltaHDTick / 100.0 - 2);
						vocData.val = ((vocData.deltaHDTick / 100.0 - 2))/10;

            vocData.lastUpdateTick = uwTickISR;
						
						if(vocData.val > 10)
						{
						vocData.val = vocData.val;
						}
						if(uiData.rightDisplay == 1)
						{
							poweron_count++;
						}
						else
						{
							poweron_count = 0;
						}
						if(poweron_count > 300)
						{
							if(vocData.val >= 25)
							{
								sensorData.overload[2] = 1; 
							}
							else
							{
								sensorData.overload[2] = 0; 
							}
						}

        }

        /* Clear the EXTI line 0 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
	else if (EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
		{
			if((uiData.leftMode == UI_LEFT_POWER_OFF)&&(uwTick > 5000))
			{
				SystemInit();
				sysledofftimes = 0;
				uiData.leftDisplay = 1;
				uiData.rightDisplay = 1;
				LCD_BL_1;
				LCD2_BL_1;
			}
		}
	
		
		 EXTI_ClearITPendingBit(EXTI_Line7);
	}
    else if (EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
//        encoderData.leftFlag = 1;
//        encoderData.leftUpdateTick = uwTickISR;
			if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
			{
				if((uiData.leftMode == UI_LEFT_POWER_OFF)&&(uwTick > 5000))
				{
					SystemInit();
					sysledofftimes = 0;
					uiData.leftDisplay = 1;
					uiData.rightDisplay = 1;
					LCD_BL_1;
					LCD2_BL_1;
				}
			}
        /* Clear the EXTI line 0 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
}

/**
  * @brief  This function handles External lines 15 to 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
		I2C2_ReadOneByte(FT_ADDR,Reg_Addr,&TF2touchdata.temp_data[0]);
		I2C2_ReadOneByte(FT_ADDR,Reg_Addr + 1,&TF2touchdata.temp_data[1]);
		TF2touchdata.x_position = ((TF2touchdata.temp_data[0]&0x0f)<<8)|TF2touchdata.temp_data[1];
		I2C2_ReadOneByte(FT_ADDR,Reg_Addr + 2,&TF2touchdata.temp_data[2]);
		I2C2_ReadOneByte(FT_ADDR,Reg_Addr + 3,&TF2touchdata.temp_data[3]);
		TF2touchdata.y_position = ((TF2touchdata.temp_data[2]&0x0f)<<8)|TF2touchdata.temp_data[3];
		I2C2_ReadOneByte(FT_ADDR,Reg_Addr + 4,&TF2touchdata.temp_data[4]);
		I2C2_ReadOneByte(FT_ADDR,Reg_Addr + 5,&TF2touchdata.temp_data[5]);
		
		if((TF2touchdata.temp_data[0]>>6)==0)
		{
			if(TF2touchdata.status_press == false)
			{
				TF2touchdata.status_up = false;
				TF2touchdata.status_down = true;
				TF2touchdata.status_press = false;
				TF2touchdata.press_times = uwTick;
			}
			else 
			{
				TF2touchdata.status_up = true;
				TF2touchdata.status_down = false;
				TF2touchdata.status_press = false;
				
				if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
				{
						GPIOA->BSRRL = GPIO_Pin_8;
						if(uiData.leftMode == UI_LEFT_SLEEP)
						{
							uiData.leftMode = UI_LEFT_POWER_ON;
							uiData.rightMode = UI_RIGHT_AQI;
						}
						else if(uiData.leftMode == UI_LEFT_POWER_OFF)
						{
							SystemInit();
							uiData.leftMode = UI_LEFT_POWER_OFF;
							uiData.rightMode = UI_RIGHT_POWER_OFF;
						}
//						methanalInit(); /* 甲醛传感器 */
						uiData.leftDisplay = 1;
						uiData.rightDisplay = 1;
						LCD_BL_1;
						LCD2_BL_1;
						rightLast = 0;
						leftLast = 0;
				}
				
				if (TF2touchdata.x_position < 40)
				{
					touchData.rightEvent = touchEvent_Left;
				}
				else if (TF2touchdata.x_position > 80)
				{
					touchData.rightEvent = touchEvent_Right;
				}
				else
				{
					touchData.rightEvent = touchEvent_Middle;
				}
				
				if(uwTick - TF2touchdata.press_times >= 3000)
				{
					touchData.rightEvent = touchEvent_MiddleLong;
				}
				
				if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
				{
					uiData.leftMode = UI_LEFT_POWER_ON;
					uiData.rightMode = UI_RIGHT_AQI;
					uiData.leftDisplay = 1;
					uiData.rightDisplay = 1;
					LCD_BL_1;
					LCD2_BL_1;
				}
			}
			TF2touchdata.temp_data[0] = 0;
			}
			else if((TF2touchdata.temp_data[0]>>6)==1)
			{
				TF2touchdata.status_up = false;
				TF2touchdata.status_down = false;
				TF2touchdata.status_press = true;
				TF2touchdata.temp_data[0] = 1;
			}
			sysledofftimes = 0;
					/* Clear the EXTI line 13 pending bit */
			EXTI_ClearITPendingBit(EXTI_Line13);
			
    }
		
		if (EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
			if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
			{
				if((uiData.leftMode == UI_LEFT_POWER_OFF)&&(uwTick > 5000))
				{
					SystemInit();
					sysledofftimes = 0;
					uiData.leftDisplay = 1;
					uiData.rightDisplay = 1;
					LCD_BL_1;
					LCD2_BL_1;
				}
			}
			EXTI_ClearITPendingBit(EXTI_Line14);
		}
		
		if (EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
			if((uiData.leftDisplay == 0)&&(uiData.rightDisplay == 0))
			{
				if((uiData.leftMode == UI_LEFT_POWER_OFF)&&(uwTick > 5000))
				{
					SystemInit();
					sysledofftimes = 0;
					uiData.leftDisplay = 1;
					uiData.rightDisplay = 1;
					LCD_BL_1;
					LCD2_BL_1;
				}
			}
			EXTI_ClearITPendingBit(EXTI_Line15);
		}
}

/* end of file */
