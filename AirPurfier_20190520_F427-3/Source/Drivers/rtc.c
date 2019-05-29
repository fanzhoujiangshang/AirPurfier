#include "rtc.h"
#include "timer.h"

_calendar_obj calendar;//ʱ�ӽṹ�� 

// Sakamoto's algorithm (modified)
// return Day of Week, 1 == Monday, 7 == Sunday
int rtcDow(int y, int m, int d)
{
    const uint8_t t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    y -= m < 3;
    return ((y + y/4 - y/100 + y/400 + t[m-1] + d - 1) % 7) + 1;
}

uint8_t rtcInit(void)
{
	return 0; //ok
}

/* end of file */

void set_clock(u16 divx)
{ 									  
}	   
	 				    
//�ж��Ƿ������꺯��
//�·�   1  2  3  4  5  6  7  8  9  10 11 12
//����   31 29 31 30 31 30 31 31 30 31 30 31
//������ 31 28 31 30 31 30 31 31 30 31 30 31
//����:���
//���:������ǲ�������.1,��.0,����
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //�����ܱ�4����
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400���� 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}

//����ʱ��
//�������ʱ��ת��Ϊ����
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//����ֵ:0,�ɹ�;����:�������.
//�·����ݱ�											 
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�	  
//ƽ����·����ڱ�
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	return 0;	    
}
//�õ���ǰ��ʱ��
//����ֵ:0,�ɹ�;����:�������.
u8 RTC_Get(void)
{
	return 0;
}

//RTCʱ���ж�
//ÿ�봥��һ��  
//extern u16 tcnt; 
void RTC_IRQHandler(void)
{		 
//	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//�����ж�
//	{							
//		RTC_Get();//����ʱ��   
// 	}
//    
//	if (RTC_GetITStatus(RTC_IT_ALR)!= RESET)//�����ж�
//	{
//		RTC_ClearITPendingBit(RTC_IT_ALR);		//�������ж�	  	   
//  	}

//	RTC_ClearITPendingBit(RTC_IT_SEC | RTC_IT_OW);		//�������ж�
//	RTC_WaitForLastTask();	  	    						 	   	 
}
