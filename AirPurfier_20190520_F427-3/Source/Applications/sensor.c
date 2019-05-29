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
	
    filterNetInit();/* ������ǩ */
    methanalInit(); /* ��ȩ������ */
    granuleInit();  /* ���������� */
    humidityInit(); /* ��ʪ�ȴ����� */
    vocInit();      /* ��ζŨ�ȴ����� */
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
