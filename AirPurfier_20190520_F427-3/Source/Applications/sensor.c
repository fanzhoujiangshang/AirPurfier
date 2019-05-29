#include "sensor.h"
#include "methanal.h"
#include "granule.h"
#include "humidity.h"
#include "voc.h"
#include "filter_net.h"
#include "motor.h"

sensorStruct_t sensorData;

void sensorInit(void)
{
    sensorData.aqi = 0;
	
    filterNetInit();/* 滤网标签 */
    methanalInit(); /* 甲醛传感器 */
    granuleInit();  /* 颗粒传感器 */
    humidityInit(); /* 温湿度传感器 */
    vocInit();      /* 气味浓度传感器 */
    motorSensorInit();
}

void sensorUpdate(void)
{
    methanalUpdate();
    granuleUpdate();
    humidityUpdate();
    vocUpdate();
//    motorSensorUpdate();
//		motorControl();
}

/* end of file */
