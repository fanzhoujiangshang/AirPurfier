#include "supervisor.h"
#include "sensor.h"
#include "encoder.h"

#include "motor.h"
#include "touch.h"
#include "filter_net.h"
#include "timer.h"
#include "st7789.h"

#include "ui.h"

#include "eeprom.h"
#include "parameter.h"
#include "ec20.h"

/* Macros ------------------------------------------------------------------------------------- */
#define TASK_SUPERVISOR_PRIORITY	(tskIDLE_PRIORITY + 4)	/* 系统监测任务优先级 */

/* 所有串口任务 */
static xTaskHandle taskSupervisorHandle;						/* 系统监测任务 */

TaskStatus_t pxTaskStatusArray[10];
volatile UBaseType_t uxArraySize;
uint32_t ulTotalRunTime;

uint32_t syssleeptimes;
uint32_t sysautocontroltimes;
uint32_t sysledofftimes;
uint32_t sysSleepDefualtFlag;
uint32_t sysRightUiChangtimes;

char temp_mode = 2;
char temp_speed_level = 5;

void rtosSupervisor(void)
{
    uxArraySize = uxTaskGetNumberOfTasks();
	uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);
}

void afxSupervisorTask(void *pvParameters)
{
	portTickType xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();
	
	for ( ;; )
	{
        /* 喂狗 */
        /* 系统监测 */
        rtosSupervisor();
        
 //       touchRead();
        touchHandle();
		
		filterNetUpdate();
		
		motorControl();
		
        if (uiData.leftMode == UI_LEFT_POWER_OFF)
        {
					encoderUpdate_ledUp();
				}
        /* 仅在开机条件下使用更新传感器 */
        if (uiData.leftMode != UI_LEFT_POWER_OFF)
        {
            /* 传感器数据更新 */
            sensorUpdate();
					
            encoderUpdate();
					
            if (motorData.setTimeLevel ==0)
            {
									motorData.timeLeft = 0xffffffff;
									motorData.timeLeftHours = 0;
						}
						else
						{
							if (motorData.timeLeft > 10)
							{
									motorData.timeLeft -= 10;
									if(motorData.timeLeftHours != motorData.timeLeft/3600000 + 1)
									{
										motorData.timeLeftHours = motorData.timeLeft/3600000 + 1;
										uiData.leftUpdateReq = 1;
									}
							}
							else
							{
									motorData.timeLeft = 0;
									motorData.timeLeftHours = 0;
							}
						}
						if(motorData.timeLeft == 0)
						{
							uiData.leftMode = UI_LEFT_POWER_OFF;
							uiData.rightMode = UI_RIGHT_POWER_OFF;
							uiData.leftDisplay = 0;
							uiData.rightDisplay = 0;
							motorData.output = 0;
							TIM3->CCR2 = motorData.output;
							LCD_Default(LCD2);
							//关闭电机
						}
            
            /* 滤网计算方法 
            1. HEPA滤网: 开机情况下,滤网寿命=机器实际工作时间*风速指数*颗粒物污染程度指数,初定寿命为3000h.
             风速指数1-5档分别为: 0.4,  0.6,  0.8，1，1.2
             所有计时以1小时为单位,?断电记忆, 故小于1小时的断电将不做记时
            2.待机滤网寿命总时长为3年，约27000小时，待机寿命时间和开机寿命时间比为：27000/3000=9
            3.滤网寿命=开机滤网时间+待机滤网时间
            */
			// 寿命  972000000 = 3600 * 100 *2700   2700h
			// 3600 * 10  = 1h
            if (motorData.output > 0)
            {
								if(motorData.setSpeedLevel == 1)
								{
									filterNetData.useTime = filterNetData.useTime + 0.6f;
								}
								else if(motorData.setSpeedLevel == 2)
								{
									filterNetData.useTime = filterNetData.useTime + 0.8f;
								}
								else if(motorData.setSpeedLevel == 3)
								{
									filterNetData.useTime = filterNetData.useTime + 1.0f;
								}
								else if(motorData.setSpeedLevel == 4)
								{
									filterNetData.useTime = filterNetData.useTime + 1.2f;
								}
								if(filterNetData.useTime >= 3600*100)
//								if(filterNetData.useTime >= 100)
								{
									filterNetData.useTime = 0;
									filterNetData.hours++;
									// FlashWrite(STARTADDR ,test_percent);
									

									EE_WriteVariable(PARAM_FITER_TIME_L, filterNetData.hours & 0xffff);
									EE_WriteVariable(PARAM_FITER_TIME_H, filterNetData.hours >> 16);
									test_percent = 100 - filterNetData.hours/27;
									test_percent = constrain(test_percent,0,100);
								}
            }
						//自动进入睡眠和自动模式
						if(uiData.leftMode == UI_LEFT_SLEEP)
						{
							
							if((uwTick - syssleeptimes >= 3000)&&(filterNetData.enabled == 1))
							{
								//uiData.leftMode = UI_LEFT_POWER_OFF;
								//uiData.rightMode = UI_RIGHT_POWER_OFF;
								/* 进入睡眠模式，两屏熄灭 */
                uiData.leftDisplay = 0;
                uiData.rightDisplay = 0;
								if(sysSleepDefualtFlag == false)
								{
									sysSleepDefualtFlag = true;
									LCD_Default(LCD2);
									LCD_Default(LCD1);
								}
								//关闭电机

								rightLast = 0;
								motorData.output = 120;
							}
						}
						else
						{
							sysSleepDefualtFlag = false;
							syssleeptimes = uwTick;
						}
						if(uiData.leftMode == UI_LEFT_AUTO)
						{
							if(uwTick - sysautocontroltimes >= 3000)
							{
								motorData.autoModeEnable = 1;
							}
						}
						else
						{
//							motorData.autoModeEnable = 0;
								sysautocontroltimes  = uwTick;
						}

        }
				
				//在待机模式下五秒钟自动熄灭  
				if(uiData.leftMode == UI_LEFT_POWER_OFF)
				{
					sysledofftimes++;
					if((sysledofftimes >= 5*100)&&(filterNetData.enabled == 1))
					{
						motorData.output = 0;
						//sysledofftimes = 5*100;
						uiData.leftDisplay = 0;
						uiData.rightDisplay = 0;
						LCD_BL_0;
						LCD2_BL_0;
						GPIOA->BSRRH = GPIO_Pin_8;
						if((sysledofftimes == 5*100)&&(uwTick > 5000))
						{
//							E20_PWR_L;
//							yield(1000);
							PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
						}

					}
				}
				else
				{
					sysledofftimes = 0;
				}
				
				if((temp_mode != motorData.autoModeEnable)||(temp_speed_level != motorData.setSpeedLevel))
				{
					temp_mode = motorData.autoModeEnable;
					temp_speed_level = motorData.setSpeedLevel;
					EE_WriteVariable(0x5557, temp_mode);
					EE_WriteVariable(0x5558, temp_speed_level);
				}
        
		/* 执行周期10Hz */
		vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_RATE_MS));
	}
}

void supervisorInit(void)
{
    sensorInit();           /* 传感器初始化 */
    encoderInit();          /* 编码器旋钮初始化 */
    touchInit();
    
	xTaskCreate(afxSupervisorTask, "Monitor", configMINIMAL_STACK_SIZE * 2, \
        NULL, TASK_SUPERVISOR_PRIORITY, &taskSupervisorHandle);
}

/* end of file */
