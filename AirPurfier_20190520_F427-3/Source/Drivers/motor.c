#include "motor.h"
#include "timer.h"
#include "methanal.h"
#include "granule.h"
#include "voc.h"
#include "sensor.h"
#include "ui.h"

motorStruct_t motorData;
pid_para motor_pid;

#define Moter_Rpm1_PWM 145
#define Moter_Rpm2_PWM 220
#define Moter_Rpm3_PWM 315
#define Moter_Rpm4_PWM 400

#define Motor_Step     0.05f

void pid_Init(void)
{
	motor_pid.kp = 0.5;  //0.5
	motor_pid.ki = 0.2; //0.01
	motor_pid.kd = 0.1;  //0.1
	motor_pid._imax = 400.0;
}

void motorSensorInit(void)
{
    /* VSP PC7 TIM3 CH2;
       FG  PC8 采用外部中断计数
    */
    EXTI_InitTypeDef   EXTI_InitStructure;
    GPIO_InitTypeDef   GPIO_InitStructure;
    
    /* Enable GPIOE and AFIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Configure PC.08 pin as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Connect EXTI8 Line to PC.08 pin */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);

    /* Configure EXTI9_5 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line8;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
		
//		motorData.setSpeedLevel = 1;

    /* Generate software interrupt: simulate a falling edge applied on EXTI9_5 line */
//    EXTI_GenerateSWInterrupt(EXTI_Line8);
}


//sleep 183/min 1 level 230/min  2 level 415/min 3 level 550/min  4 level 635/min
void motorSensorUpdate(void)
{
    if (uwTick - motorData.lastCalTick >= 1000) /* 100ms */
    {
        motorData.lastCalTick = uwTick;
        
        motorData.rpm = motorData.pulseCount;
        motorData.pulseCount = 0;
    }
}

int32_t Get_Pid(pid_para *pid_t, signed short err, float dtime)
{
	signed int p_part,i_part,d_part;
	float _derivative;

	//比例部分
	p_part = err * pid_t->kp;
	pid_t->p_out = p_part;
	//积分部分
	if((fabs(pid_t->ki)>1e-7) && (fabs(dtime)>1e-7))
	{
		pid_t->_integrator += ((float)err * pid_t->ki)*dtime;
		pid_t->_integrator = constrain(pid_t->_integrator, -pid_t->_imax, pid_t->_imax);
		i_part = pid_t->_integrator;		
	}
	else
	{
		i_part = 0;
	}
	pid_t->i_out = i_part;
	//微分部分
	if((fabs(pid_t->kd)>1e-7) && (fabs(dtime)>1e-7))
	{
		_derivative = ((float)(err - pid_t->_last_input))/dtime;
		_derivative = (_derivative + pid_t->_last_derivative)*0.5f;
		pid_t->_last_input = err;
		pid_t->_last_derivative = _derivative;
		d_part = (signed short)(pid_t->kd * _derivative);	
	}
	else
	{
		d_part = 0;
	}
	pid_t->d_out = d_part;
	return (p_part + i_part + d_part);
}

float moter_test_number;

void motorControl(void)
{
		motorData.air_quality = (granuleData.ugm3 + methanalData.mmol + vocData.val);
		sensorData.aqi        =	motorData.air_quality;
    if (motorData.autoModeEnable == false)
    {
        switch (motorData.setSpeedLevel)
        {
            case 1:
                motorData.setPoint = Moter_Rpm1_PWM;
                break;
            
            case 2:
                motorData.setPoint = Moter_Rpm2_PWM;
                break;
            
            case 3:
                motorData.setPoint = Moter_Rpm3_PWM;
                break;
            
            case 4:
                motorData.setPoint = Moter_Rpm4_PWM;
                break;
						
            default: motorData.setPoint  = 0;
                break;
        }
    }
    else
    {
			if(motorData.air_quality <= 35)
			{
				/* 根据污染情况，计算给定 */
					if(motorData.setSpeedLevel > 1)
					{
						if(motorData.air_quality < 25)
						{
							motorData.setSpeedLevel = 1;
							motorData.setPoint = Moter_Rpm1_PWM;
						}
					}
					else
					{
						motorData.setSpeedLevel = 1;
						motorData.setPoint = Moter_Rpm1_PWM;
					}

			}
			else if(motorData.air_quality <= 75)
			{
				if(motorData.setSpeedLevel >2)
				{
					if(motorData.air_quality < 70)
					{
						motorData.setSpeedLevel = 2;
						motorData.setPoint = Moter_Rpm2_PWM;
					}
				}
				else
				{
					motorData.setSpeedLevel = 2;
					motorData.setPoint = Moter_Rpm2_PWM;
				}
			}
			else if(motorData.air_quality <= 115)
			{
				if(motorData.setSpeedLevel >4)
				{
					if(motorData.air_quality < 100)
					{
						motorData.setSpeedLevel = 3;
						motorData.setPoint = Moter_Rpm3_PWM;
					}
				}
				else
				{
					motorData.setSpeedLevel = 3;
					motorData.setPoint = Moter_Rpm3_PWM;
				}
			}
			else 
			{
				motorData.setSpeedLevel = 4;
				motorData.setPoint = Moter_Rpm4_PWM;
			}
    }
        
    if ((motorData.setPoint == 0)||(uiData.leftMode == UI_LEFT_POWER_OFF))
    {
        TIM3->CCR2 = 0;
    }
    else
    {
			 //motorData.output = motorData.setPoint; 
    }
		
//		if(motorData.output != motorData.setPoint)
		if(fabs(motorData.output - motorData.setPoint) >= 1)
		{
			if(motorData.output < motorData.setPoint)
			{
				motorData.output = motorData.output + 0.2f;
				motorData.outputreal = motorData.output;
			}
			else if(motorData.output > motorData.setPoint)
			{
				motorData.output = motorData.output - 0.2f;
				motorData.outputreal = motorData.output;
			}
			else
			{
				
			}
		}
		else
		{
			if(uiData.leftMode != UI_LEFT_POWER_OFF)
			{
				if(motorData.setPoint == 0)
				{
					motorData.outputreal = 0;
				}
				else if(motorData.setPoint == Moter_Rpm1_PWM)
				{
	//				motorData.error = 217 - motorData.rpm; 
	//				motorData.outputreal = Get_Pid(&motor_pid,motorData.error,0.05f);
					//motorData.outputreal = constrain(motorData.outputreal,175,185);
					//motorData.outputreal = 90;
					//motorData.outputreal = constrain(motorData.outputreal,175,185);
					
					if(motorData.rpm < 6)
					{
						motorData.outputreal += Motor_Step;
					}
					else if(motorData.rpm > 6)
					{
						motorData.outputreal -= Motor_Step;
					}
					else 
					{
					
					}
					//motorData.outputreal = 145;
				}
				else if(motorData.setPoint == Moter_Rpm2_PWM)
				{
	//				motorData.error = 416 - motorData.rpm; 
	//				motorData.outputreal = Get_Pid(&motor_pid,motorData.error,0.05f);

						//motorData.outputreal = constrain(motorData.outputreal,240,250);
						//motorData.outputreal = 220;
					if(motorData.rpm < 9)
					{
						motorData.outputreal += Motor_Step;
					}
					else if(motorData.rpm > 9)
					{
						motorData.outputreal -= Motor_Step;
					}
					else 
					{
					
					}
				
				}
				else if(motorData.setPoint == Moter_Rpm3_PWM)
				{
	//				motorData.error = 555 - motorData.rpm; 
	//				motorData.outputreal = Get_Pid(&motor_pid,motorData.error,0.05f);
					//motorData.outputreal = constrain(motorData.outputreal,340,355);
					//motorData.outputreal = 315;
					if(motorData.rpm < 13)
					{
						motorData.outputreal += Motor_Step;
					}
					else if(motorData.rpm > 13)
					{
						motorData.outputreal -= Motor_Step;
					}
					else 
					{
					
					}
			
				}
				else if(motorData.setPoint == Moter_Rpm4_PWM)
				{
	//				motorData.error = 650 - motorData.rpm; 
	//				motorData.outputreal = Get_Pid(&motor_pid,motorData.error,0.05f);
					//motorData.outputreal = constrain(motorData.outputreal,430,450);
					//motorData.outputreal = 400;
					if(motorData.rpm < 16)
					{
						motorData.outputreal += Motor_Step;
					}
					else if(motorData.rpm > 16)
					{
						motorData.outputreal -= Motor_Step;
					}
					else 
					{
					
					}
				
				}
				else
				{
				
				}
			}
		}
		//rpm s 4  1 6  2 9  3 13  4 16 
		
		//4 400 3 315  2 220 1 145
		//sleep 40  1 90 2 132 3 225 4 300
//		if(motorData.output > motorData.outputreal)
//		{
//			motorData.outputreal += 1; 
//		}
//		else if(motorData.output < motorData.outputreal)
//		{
//			motorData.outputreal -= 1;
//		}
//		else 
//		{
//		
//		}
		
		if(motorData.outputreal  <= 0)
		{
			motorData.outputreal = 0;
		}
		else if(motorData.outputreal >= 800)
		{
			motorData.outputreal = 800;
		}
		
		if(uiData.leftMode == UI_LEFT_SLEEP)
		{
				if(motorData.rpm < 4)
				{
					motorData.outputreal += 0.05f;
				}
				else if(motorData.rpm > 4)
				{
					motorData.outputreal -= 0.05f;
				}
				else 
				{
				
				}
		}
	
		
//    if(uiData.leftDisplay !=0)
//		{
			TIM3->CCR2 = (u32)motorData.outputreal;
//		}

   if((uiData.leftMode == UI_LEFT_POWER_OFF)||(uiData.leftMode == UI_LEFT_STANDBY))
	 {
			TIM3->CCR2 = 0;
	 }

//		  TIM3->CCR2 = moter_test_number;
}
