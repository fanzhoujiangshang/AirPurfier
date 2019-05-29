#include "rtc.h"
#include "timer.h"

_calendar_obj calendar;//时钟结构体 

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
	 				    
//判断是否是闰年函数
//月份   1  2  3  4  5  6  7  8  9  10 11 12
//闰年   31 29 31 30 31 30 31 31 30 31 30 31
//非闰年 31 28 31 30 31 30 31 31 30 31 30 31
//输入:年份
//输出:该年份是不是闰年.1,是.0,不是
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //必须能被4整除
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}

//设置时钟
//把输入的时钟转换为秒钟
//以1970年1月1日为基准
//1970~2099年为合法年份
//返回值:0,成功;其他:错误代码.
//月份数据表											 
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	  
//平年的月份日期表
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	return 0;	    
}
//得到当前的时间
//返回值:0,成功;其他:错误代码.
u8 RTC_Get(void)
{
	return 0;
}

//RTC时钟中断
//每秒触发一次  
//extern u16 tcnt; 
void RTC_IRQHandler(void)
{		 
//	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//秒钟中断
//	{							
//		RTC_Get();//更新时间   
// 	}
//    
//	if (RTC_GetITStatus(RTC_IT_ALR)!= RESET)//闹钟中断
//	{
//		RTC_ClearITPendingBit(RTC_IT_ALR);		//清闹钟中断	  	   
//  	}

//	RTC_ClearITPendingBit(RTC_IT_SEC | RTC_IT_OW);		//清闹钟中断
//	RTC_WaitForLastTask();	  	    						 	   	 
}
