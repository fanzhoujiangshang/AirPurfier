#include "touch.h"
//#include "i2c_ft.h"
#include "timer.h"
#include "i2c.h"
#include "ui.h"
#include "filter_net.h"
#include "motor.h"
#include "st7789.h"

#include "eeprom.h"
#include "parameter.h"
#include "supervisor.h"
#include "methanal.h"


touchStruct_t touchData;

/* 触摸屏IC为 FT32X7 */

/* 数据更新频率100Hz */
/* 三种工作模式
   ? Active Mode
    ? Monitor Mode
    ? Sleep Mode
*/

/* 测试
touch-event: 1-按中间 2-按左边 3-按右边 4-长按 */
    uint8_t test_data = 0;
void touchInit(void)
{
    /*  引脚定义
     *  PE1:  RST-L     PE0:  INT-L     PB8:  SCL-L     PB9:  SDA-L
     *  PE12: RST-R     PE13: INT-R     PB10: SCL-R     PB11: SDA-R
     */

    /* I2C Configuration ---------------------------------------------------------------------*/
    i2cInit();
	
	i2c2Init();
}
void touchRead(void)
{	

}

void touchHandle(void)
{
		if(touchData.leftEvent == 4)
		{
			uiData.leftMode = UI_LEFT_STANDBY;
			uiData.leftDisplay = 0;
			uiData.rightDisplay = 0;
			GPIOA->BSRRH = GPIO_Pin_8;
			TIM3->CCR2 = 0;
			touchData.leftEvent = touchEvent_None;
		}
	
    if (touchData.leftEvent != touchEvent_None)
    {
        switch (uiData.leftMode)
        {
        case UI_LEFT_POWER_OFF:
            if (touchData.leftEvent == touchEvent_Middle) /* 检测开机动作 */
            {
//								motorData.autoModeEnable = 1;
                uiData.leftMode = UI_LEFT_POWER_ON;
                uiData.rightMode = UI_RIGHT_AQI;
								rightLast = 0;	
								LCD_WR_REG(LCD2, 0x29);
                
                motorData.timeLeft = 0xffffffff;
                uiData.rightDisplay = 1;
                
//                motorData.setSpeedLevel = 1;
//                motorData.setTimeLevel = 0;
							
								GPIOA->BSRRL = GPIO_Pin_8;
								uiData.leftDisplay = 1;
								uiData.rightDisplay = 1;
								LCD_BL_1;
								LCD2_BL_1;
//								methanalInit(); /* 甲醛传感器 */
            }
            break;
        
        case UI_LEFT_POWER_ON:
            if (touchData.leftEvent == touchEvent_Middle) /* 检测关机动作 */
            {
							LCD_Default(LCD2);
                uiData.leftMode = UI_LEFT_POWER_OFF;
                uiData.rightMode = UI_RIGHT_POWER_OFF;
							TIM3->CCR2 = 0;
							LCD_WR_REG(LCD2, 0x28);
                
                motorData.timeLeft = 0;
                uiData.rightDisplay = 0;
						sysledofftimes = 0;
				
            }
            break;
            
        case UI_LEFT_AUTO:
            if (touchData.leftEvent == touchEvent_Middle)
            {
                /* 启动自动调节功能 */
                motorData.autoModeEnable = 1;
            }
            break;
        
        case UI_LEFT_AIR_SPEED: /* 设置风速级别 <1-4>级 */
						motorData.autoModeEnable = 0;
            if (touchData.leftEvent == touchEvent_Middle)
            {
                motorData.autoModeEnable = 0;
            }
            else if (touchData.leftEvent == touchEvent_Left)
            {
                if (motorData.setSpeedLevel > 1)
                {
                    motorData.setSpeedLevel--;
                    uiData.leftUpdateReq = 1;
//										EE_WriteVariable(PARAM_MOTOR_LEVEL, (u16)motorData.setSpeedLevel);
                }
            }
            else if (touchData.leftEvent == touchEvent_Right)
            {
                if (motorData.setSpeedLevel < 4)
                {
                    motorData.setSpeedLevel++;
                    uiData.leftUpdateReq = 1;
//										EE_WriteVariable(PARAM_MOTOR_LEVEL, (u16)motorData.setSpeedLevel);
                }
            }
            break;
        
        case UI_LEFT_TIMING: /* 2h—4h—6h—8h (对应1-4)*/
            if (touchData.leftEvent == touchEvent_Middle)
            {
							uiData.leftUpdateReq = 1;
							if(motorData.setTimeLevel ==0)
							{
								motorData.timeLeft = 0xffffffff;
							}
							else
							{
								motorData.timeLeft = 3600 * 1000 * 1 * motorData.setTimeLevel;
							}
											
            }
            else if (touchData.leftEvent == touchEvent_Left)
            {
                if (motorData.setTimeLevel > 0)
                {
                    motorData.setTimeLevel--;
                    uiData.leftUpdateReq = 1;
                }
                motorData.timeLeft = 3600 * 1000 * 1 * motorData.setTimeLevel;
																
				if(motorData.setTimeLevel ==0)
				{
					motorData.timeLeft = 0xffffffff;
				}
            }
            else if (touchData.leftEvent == touchEvent_Right)
            {
                if (motorData.setTimeLevel < 8)
                {
                    motorData.setTimeLevel++;
                    uiData.leftUpdateReq = 1;
                }
                motorData.timeLeft = 3600 * 1000 * 1 * motorData.setTimeLevel;
				motorData.timeLeftHours = motorData.timeLeft/3600000;
            }
            break;
        
        case UI_LEFT_SLEEP:
            if (touchData.leftEvent == touchEvent_Middle)
            {
								//uiData.leftMode = UI_LEFT_POWER_OFF;
								//uiData.rightMode = UI_RIGHT_POWER_OFF;
                /* 进入睡眠模式，两屏熄灭 */
                uiData.leftDisplay = 0;
                uiData.rightDisplay = 0;
				LCD_Default(LCD2);
				LCD_Default(LCD1);
			//	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
				//GPIOA->BRR = GPIO_Pin_8;
//							PWR_WakeUpPinCmd(ENABLE);
//							PWR_EnterSTANDBYMode();
				//	uiData.rightMode = UI_RIGHT_POWER_OFF;
	//关闭电机
				//TIM3->CCR2 = 160;
				TIM3->CCR2 = 90;
							
            }
            break;
            
        default:
            break;
        }
        
        touchData.leftEvent = touchEvent_None;
    }
        
    if (touchData.rightEvent != touchEvent_None)
    {
        switch (uiData.rightMode)
        {
        case UI_RIGHT_FILTER:
            if (touchData.rightEvent == touchEvent_MiddleLong)
            {
				test_percent = 100;
				filterNetData.hours = 0;
				//FlashWrite(STARTADDR ,test_percent);
				
				EE_WriteVariable(PARAM_FITER_TIME_L, filterNetData.hours & 0xffff);
				EE_WriteVariable(PARAM_FITER_TIME_H, filterNetData.hours >> 16);
				
				/* 长按3秒清除滤网时间 */
				filterNetData.useTime = 0;
            }
            break;
        
        default:
            break;
        }
        
        touchData.rightEvent = touchEvent_None;
    }
}

/* end of file */
