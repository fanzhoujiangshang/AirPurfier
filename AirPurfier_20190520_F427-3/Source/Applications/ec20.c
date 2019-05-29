#include "ec20.h"
#include "digital.h"
#include "timer.h"
#include "cJSON.H"
#include "aes.h"
#include "base64.h"
#include "version.h"
#include "motor.h"
#include "filter_net.h"
#include "granule.h"
#include "humidity.h"
#include "voc.h"
#include "sensor.h"
#include "methanal.h"
#include "filter_net.h"
#include "ui.h"
#include "st7789.h"
#include "eeprom.h"
#include "parameter.h"

extern unsigned char decode_output[4096]; 
extern uint32_t sysledofftimes;

#define TASK_EC20_PRIORITY              (tskIDLE_PRIORITY + 4)
#define TASK_EC20_STACK_SIZE	        (configMINIMAL_STACK_SIZE*4)

static xTaskHandle taskEC20Handle;

ec20TaskStruct_t ec20TaskData;
extern uiStruct_t uiData;
extern filterNetStruct_t filterNetData;

uint32_t a = 0xfffffff0;

void ec20Print(const char *str)
{
    serialPrint(ec20TaskData.serialPort, str);
    yield(500);
}

void ec20_send_datas(unsigned char *str,unsigned short len)
{
	unsigned short i ;
	for(i=0;i<len;i++)
	{
		serialWrite(ec20TaskData.serialPort, *(str++));      //?????  ????       
	}
}
char number;

char servers_ip_port0[128] = "AT+QIOPEN=1,0,\"TCP\",\"121.40.115.131\",18807,0,2\r\n";
char out[256] =  "{\"action\":\"m_discover\",\"id\":1,\"nema\":\"sk300\",\"imei\":\"89860402101701597070\"}";
//char airpurifier_status[256] = "{\"action\":\"m_update\",\"id\":1,\"speed\":\"0\",\"timing\":\"0\",\"lifetime\":\"0\",\"IAQ\":\"0\",\"PM2_5\":\"0\",\"TVOC\":\"0\",\"HCHO\":\"0\",\"tem\":\"0\",\"hum\":\"0\"}";
char airpurifier_status[512] = {0};
char m_info_out[256] = "{\"action\":\"m_info\",\"id\":1,\"name\":\"SK300\",\"imei\":\"1234456789abcdef\",\"sim\":{\"iccid\":\"0\",\"imsi\":\"0\"}}";
char out_aes[256] = { 0 };
char out_aes1[256] = {0};
char key_temp[128] = {0};
unsigned char key_real[16] = {0};
char out1[256];
char out2[512];
char out3[256];
char out4[256];
char out5[256];
char imei_sequence[15] = {0};
u32  time_cnt1,time_cnt2;
char servers_ip[32] = {0};
char servers_port[16] = {0};
char receive_flag = 0;
char endstr[1] = {0x1a};

void EC20PowerKeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
}

////void afxEC20Task(void *pvParameters)
////{
////	uint32_t len,len1,len2,len3,len4;
////	unsigned char i;
////	char *json_sj2;
////	cJSON *json_sjjm;

////	uint8_t rec_cnt = 0;
////	
////    serialPort_t *s = ec20TaskData.serialPort;
//////	E20_PWR_H;
//////	yield(3000);
////	E20_PWR_L;
////	yield(2500);
////	E20_PWR_H;
//////    yield(20000);
////    yield(100);
////	ec20Print("AT\r\n");
////	ec20Print("AT+CPIN?\r\n");
////	ec20Print("AT+CREG?\r\n");
////	while (serialAvailable(s))
////	{
////		serialRead(s);
////	}
////	ec20Print("AT+GSN\r\n");
////	while (serialAvailable(s))
////	{
////		if (rec_cnt < 255)
////		{
////			out2[rec_cnt++] = serialRead(s);
////		}
////		else
////		{
////			break;
////		}
////	}
////	for(i=0;i<15;i++)
////	{
////		imei_sequence[i] = out2[9+i];
////	}
////	/*configure a context*/
////	ec20Print("AT+QICSGP=1,1,\"UNINET\",\"\",\"\"1\r\n");
////	/*activate a context*/
////	ec20Print("AT+QIACT=1\r\n");
////	ec20Print("AT+QIACT?\r\n");
////	/*deactivate a context*/
//////	ec20Print("AT+QIDEACT=1\r\n");
////	ec20Print("AT+QICLOSE=0\r\n");
////	/*TCP Client Works in Buffer Access Mode*/
//////	ec20Print("AT+QIOPEN=1,0,\"TCP\",\"121.40.115.131\",18807,0,2\r\n");
////	ec20Print("AT+QIOPEN=1,0,\"TCP\",\"xwmw.yifangzn.com\",18807,0,2\r\n");

////	
////	// cJSON_m_discover();
////	
//////	time_cnt1 = uwTickHD;
//////	for (uint32_t i = 0; i < 100; i++)
//////	{
//////		memcpy(out_aes, out, 256);
//////		len  = device_aes_encrypt(local_key,(unsigned char *)out_aes ,strlen(out));
//////		len1 = base64_encode((unsigned char *)out_aes, len,(unsigned char *)out1);
//////		time_cnt2 = uwTickHD - time_cnt1;
//////	}

////		sprintf(m_info_out, "{\"action\":\"m_info\",\"id\":1,\"name\":\"SK300\",\"imei\":\"%s\",\"sim\":{\"iccid\":\"0\",\"imsi\":\"0\"}}",imei_sequence);

////		memcpy(out_aes, out, 256);
////		len  = device_aes_encrypt(local_key,(unsigned char *)out_aes ,strlen(out));
////		len1 = base64_encode((unsigned char *)out_aes, len,(unsigned char *)out1);

////		/* 清空接收缓存 */
////		while (serialAvailable(s))
////		{
////			serialRead(s);
////		}
////		
////		/* 数据发送 */
////		ec20_send_datas((unsigned char *)out1,len1);
////		ec20Print("\r\n");
////		
////		yield(1000);
////		
////		rec_cnt = 0;
////		while (serialAvailable(s))
////		{
////			if (rec_cnt < 255)
////			{
////				out2[rec_cnt++] = serialRead(s);
////			}
////			else
////			{
////				break;
////			}
////		}
////		
////		out2[rec_cnt] = 0;
////		
////		len2 = base64_decode((unsigned char *)out2, (unsigned char *)out3);  
////		device_aes_decrypt(AES_iv,(unsigned char  *)out3, len2);
////		
////		cJSON *json = cJSON_Parse(out3);
////		cJSON * pSub = cJSON_GetObjectItem(json, "ip");
////		number = pSub->valueint;
////		
////		json_sjjm=cJSON_GetObjectItem(json,"ip");
////		json_sj2=json_sjjm->valuestring;
////		strncpy (servers_ip,json_sj2,strlen(json_sj2));
////		
////		json_sjjm=cJSON_GetObjectItem(json,"port");
////		json_sj2=json_sjjm->valuestring;
////		strncpy (servers_port,json_sj2,strlen(json_sj2));
////		
////		cJSON_Delete(json);
////		sprintf(servers_ip_port0, "AT+QIOPEN=1,0,\"TCP\",\"%s\",%s,0,2\r\n", servers_ip,servers_port);
////		
////		ec20Print("AT\r\n");
////		ec20Print("AT+CPIN?\r\n");
////		ec20Print("AT+CREG?\r\n");
////		
////		ec20Print("AT+QICSGP=1,1,\"UNINET\",\"\",\"\"1\r\n");
////		/*activate a context*/
////		ec20Print("AT+QIACT=1\r\n");
////		ec20Print("AT+QIACT?\r\n");
////		/*deactivate a context*/
////	//	ec20Print("AT+QIDEACT=1\r\n");

////		ec20Print("AT+QICLOSE=0\r\n");
////		ec20Print((char *)&servers_ip_port0);
////		
////		
////		memset(out_aes,0,256);
////		memset(out1,0,256);
////		memset(out2,0,256);
////		memset(out3,0,256);
////		memcpy(out_aes, m_info_out, 256);
////		/* 清空接收缓存 */

////		len  = device_aes_encrypt(local_key,(unsigned char *)out_aes ,strlen(m_info_out));
////		len1 = base64_encode((unsigned char *)out_aes, len,(unsigned char *)out1);
////		while (serialAvailable(s))
////		{
////			serialRead(s);
////		}
////		ec20_send_datas((unsigned char *)out1,len1);
////		ec20Print("\r\n");
////		
////		yield(1000);
////		rec_cnt = 0;
////		while (serialAvailable(s))
////		{
////			if (rec_cnt < 255)
////			{
////				out2[rec_cnt++] = serialRead(s);
////			}
////			else
////			{
////				break;
////			}
////		}
////		out2[rec_cnt] = 0;
////		
////		len2 = base64_decode((unsigned char *)out2, (unsigned char *)out3);  
////		device_aes_decrypt(AES_iv,(unsigned char  *)out3, len2);
////		
//////		cJSON *
////		json = cJSON_Parse(out3);
////		
////		json_sjjm=cJSON_GetObjectItem(json,"key");
////		json_sj2=json_sjjm->valuestring;
////		strncpy (key_temp,json_sj2,strlen(json_sj2));
////		
////		len3 = base64_decode((unsigned char *)key_temp, (unsigned char *)key_real);
////		
////		cJSON_Delete(json);
////		
////		memset(out2,0,256);
////		memset(out_aes1,0,256);
////		memset(out4,0,256);

////		////sprintf(out, "{\"action\":\"m_discover\",\"id\":1,\"nema\":\"sk300\",\"imei\":\"%x\"}", chipUniqueID[2]);
////		sprintf(airpurifier_status,"{\"action\":\"m_update\",\"id\":1,\"speed\":%x,\"timing\":%d,\"lifetime\":%d,\"IAQ\":%d,\"PM2_5\":%d,\"TVOC\":%.1f,\"HCHO\":%.1f,\"tem\":%.1f\,\"hum\":%.1f}",\
////		motorData.setSpeedLevel,motorData.timeLeft/1000,filterNetData.useTime,sensorData.aqi,granuleData.data[1],vocData.val,methanalData.mmol,temperature,humidity);
////		
////		memcpy(out_aes1, airpurifier_status, 256);
////		len3  = device_aes_encrypt(key_real,(unsigned char *)out_aes1 ,strlen(airpurifier_status));
////		len4 = base64_encode((unsigned char *)out_aes1, len3,(unsigned char *)out4);
////		
////		ec20_send_datas((unsigned char *)out4,len4);
////		ec20Print("\r\n");
////		ec20_send_datas((unsigned char *)out4,len4);
////		ec20Print("\r\n");
////		ec20_send_datas((unsigned char *)out4,len4);
////		ec20Print("\r\n");
////		ec20_send_datas((unsigned char *)out4,len4);
////		ec20Print("\r\n");
////		ec20_send_datas((unsigned char *)out4,len4);
////		ec20Print("\r\n");
////	
////	for ( ;; )
////    {
////     yield(5);
////		
////		if(uwTick - ec20TaskData.StatusSendTick > 10)
////		{
////			
////			ec20TaskData.StatusSendTick = uwTick;
////			//memset(out2,0,256);
////			memset(out_aes1,0,256);
////			memset(out4,0,256);

////			////sprintf(out, "{\"action\":\"m_discover\",\"id\":1,\"nema\":\"sk300\",\"imei\":\"%x\"}", chipUniqueID[2]);
////			sprintf(airpurifier_status,"{\"action\":\"m_update\",\"id\":1,\"speed\":%x,\"timing\":%d,\"lifetime\":%d,\"IAQ\":%d,\"PM2_5\":%d,\"TVOC\":%.1f,\"HCHO\":%.1f,\"tem\":%.1f\,\"hum\":%.1f}",\
////			motorData.setSpeedLevel,motorData.timeLeft/1000,filterNetData.useTime,sensorData.aqi,granuleData.data[1],vocData.val,methanalData.mmol,temperature,humidity);
////			
////			memcpy(out_aes1, airpurifier_status, 256);
////			len3  = device_aes_encrypt(key_real,(unsigned char *)out_aes1 ,strlen(airpurifier_status));
////			len4 = base64_encode((unsigned char *)out_aes1, len3,(unsigned char *)out4);
//////			
//////			len5 = base64_decode((unsigned char *)out4, (unsigned char *)out5);  
//////			device_aes_decrypt(AES_iv,(unsigned char  *)out5, len5);
////			
//////			memset(out_aes1,0,256);
//////			memcpy(out_aes1, m_info_out, 256);
//////			len  = device_aes_encrypt(local_key,(unsigned char *)out_aes1 ,strlen(m_info_out));
//////			len1 = base64_encode((unsigned char *)out_aes1, len,(unsigned char *)out4);
////			
////					/* 清空接收缓存 */
//////			while (serialAvailable(s))
//////			{
//////				serialRead(s);
//////			}
//////		
////		/* 数据发送 */
////			ec20_send_datas((unsigned char *)out4,len4);
////			ec20Print("\r\n");
////			
////			while (serialAvailable(s))
////			{
////				if(rec_cnt == 0xff)
////				{
////					rec_cnt = 0;
////				}
////			if (rec_cnt < 255)
////			{
////				out2[rec_cnt++] = serialRead(s);
////			}
////			else
////			{
////				break;
////			}
////			}

////		}
////		

//////	#if 0
//////		/* 上报状态 */
//////		while (serialAvailable(s))
//////		{
//////			ec20TaskData.lastReceviedTick = uwTick;
//////			
//////			if (ec20TaskData.recCnt < 256)
//////			{
//////				ec20TaskData.recBuf[ec20TaskData.recCnt++] = serialRead(s);
//////			}
//////			else
//////			{
//////				break;
//////			}
//////			
//////            /* AT指令 */
//////            if (1)
//////            {
//////                
//////            }
//////            else
//////            {
//////                /* 结束透传 */
//////                ec20Print("+++\r\n");
//////                
//////                /* 断开TCP连接 */
//////                ec20Print("AT+QICLOSE=0\r\n");
//////            }
//////		}
//////		
//////		if (uwTick - ec20TaskData.lastReceviedTick > 50)
//////		{
//////			if (ec20TaskData.recCnt != 0)
//////			{
//////				/* parse */
//////				/* ec20TaskData.recBuf */
//////				cJSON *json = cJSON_Parse(ec20TaskData.recBuf);
//////				cJSON * pSub = cJSON_GetObjectItem(json, "id");
////////	int number = cJSON_GetObjectItem(pSub, "id")->valueint;
//////				number = pSub->valueint;
//////				cJSON_Delete(json);
//////				ec20TaskData.recCnt = 0;
//////			}
//////		}
//////		
//////		
//////		if (send_flag == 1)
//////		{
//////			send_flag = 0;
//////			memset(ec20TaskData.serialPort->rxBuf, 0, 512);
//////			
//////			ec20Print("AT+QICLOSE=0\r\n");
//////	/*TCP Client Works in Buffer Access Mode*/
//////			ec20Print("AT+QIOPEN=1,0,\"TCP\",\"121.40.115.131\",18807,0,2\r\n");
//////			cJSON_m_discover();
//////			
////////			ec20Print(send_buf);
//////		}
//////    #endif
////	}
////}
uint8_t len,len1,len2,len3,len4;
uint16_t len5;
void afxEC20Task(void *pvParameters)
{
	
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	char *p;
	char *p1;
	unsigned char i;
	char *json_sj2;
	cJSON *json_sjjm;
//	uint32_t len,len1,len2,len3,len4;
	uint8_t rec_cnt = 0;
	char powerswitch;
	char workmode;
	
    serialPort_t *s = ec20TaskData.serialPort;
//	E20_PWR_H;
//	yield(3000);
	
	restart:
	E20_PWR_L;
	yield(3000);
	E20_PWR_H;
  yield(3000);
	rec_cnt = 0;
	memset(out2,0,256);
	while (serialAvailable(s))
	{
		ec20TaskData.lastReceviedTick = uwTick;
		ec20TaskData.lastReceviedTick1 = uwTick;
		out2[rec_cnt++] = serialRead(s);
	}
	rec_cnt = 0;
	memset(out2,0,256);
	ec20Print("AT+NRB\r\n");
  yield(10000);
	while (serialAvailable(s))
	{
		ec20TaskData.lastReceviedTick = uwTick;
		ec20TaskData.lastReceviedTick1 = uwTick;
		out2[rec_cnt++] = serialRead(s);
	}
	rec_cnt = 0;
	memset(out2,0,256);
	ec20Print("AT\r\n");
	yield(1000);
	while (serialAvailable(s))
	{
		ec20TaskData.lastReceviedTick = uwTick;
		ec20TaskData.lastReceviedTick1 = uwTick;
		out2[rec_cnt++] = serialRead(s);
	}
	memset(out2,0,256);
	ec20Print("AT+CPSMS=0\r\n");
	ec20Print("AT+QSCLK=0\",0,0,1\r\n");
	rec_cnt = 0;
	memset(out2,0,256);
	ec20Print("AT+CSQ\r\n");
	yield(1000);
	while (serialAvailable(s))
	{
		ec20TaskData.lastReceviedTick = uwTick;
		ec20TaskData.lastReceviedTick1 = uwTick;
		out2[rec_cnt++] = serialRead(s);
	}
	ec20Print("AT+QMTCFG=\"recv/mode\",0,0,1\r\n");
	yield(1000);
	rec_cnt = 0;
	memset(out2,0,256);
	ec20Print("AT+QMTCFG=\"aliauth\",0,\"a1EfxtqrsRV\",\"zSSY9YVF9uM50NMW9wfJ\",\"fnYZNBl3L6KC0dxiAox5EyU79t9CqCl3\"\r\n");
	yield(1000);
	while (serialAvailable(s))
	{
		ec20TaskData.lastReceviedTick = uwTick;
		ec20TaskData.lastReceviedTick1 = uwTick;
		out2[rec_cnt++] = serialRead(s);
	}
	ec20Print("AT+QMTOPEN=?\r\n");
	yield(1000);
	//http://alPUPCoxxxx.iot-as-mqtt.cn-shanghai.aliyuncs.com
//	ec20Print("AT+QMTOPEN=0,\"a1EfxtqrsRV.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883\r\n");
	rec_cnt = 0;
	memset(out2,0,256);
	ec20Print("AT+QMTOPEN=0,\"iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883\r\n");
	yield(2000);
	while (serialAvailable(s))
	{
		ec20TaskData.lastReceviedTick = uwTick;
		ec20TaskData.lastReceviedTick1 = uwTick;
		out2[rec_cnt++] = serialRead(s);
	}
	if((out2[134] == 0x30)&&(out2[136] == 0x30))
	{

	}
	else
	{
		goto restart;
	}
	ec20Print("AT+QMTOPEN?\r\n");
	yield(1000);
	ec20Print("AT+QMTCONN=?\r\n");
	yield(1000);
	rec_cnt = 0;
	memset(out2,0,256);	
	ec20Print("AT+QMTCONN=0,\"clientExample\"\r\n");
	yield(1000);
	while (serialAvailable(s))
	{
		ec20TaskData.lastReceviedTick = uwTick;
		ec20TaskData.lastReceviedTick1 = uwTick;
		out2[rec_cnt++] = serialRead(s);
	}
	if(strstr(out2,"ERROR"))
	{
		goto restart;
	}

	ec20Print("AT+QMTSUB=?\r\n");
	yield(1000);
	
	//  /sys/a1EfxtqrsRV/zSSY9YVF9uM50NMW9wfJ/thing/event/property/post 发布 设备属性上报
	//  /sys/a1EfxtqrsRV/zSSY9YVF9uM50NMW9wfJ/thing/service/property/set 订阅 设备属性设置 
	
	rec_cnt = 0;
	memset(out2,0,256);
	ec20Print("AT+QMTSUB=0,1,\"/sys/a1EfxtqrsRV/zSSY9YVF9uM50NMW9wfJ/thing/service/property/set\",2\r\n");
	yield(1000);
	while (serialAvailable(s))
	{
		ec20TaskData.lastReceviedTick = uwTick;
		ec20TaskData.lastReceviedTick1 = uwTick;
		out2[rec_cnt++] = serialRead(s);
	}
	if(strstr(out2,"ERROR"))
	{
		goto restart;
	}
//	ec20Print("AT+QMTSUB=0,1,\"topic/pub\",0\r\n");
//	yield(100);
//	ec20Print("AT+QMTUNS=0,2,\"topic/example\"\r\n");
//	yield(100);
//	ec20Print("AT+QMTPUBEX=?\r\n");
//	yield(100);
//	ec20Print("AT+QMTPUBEX=0,0,0,0,\"/sys/a1EfxtqrsRV/zSSY9YVF9uM50NMW9wfJ/thing/event/property/post\"\r\n");
//	yield(1000);
//	while (serialAvailable(s))
//	{
//		ec20TaskData.lastReceviedTick = uwTick;
//		ec20TaskData.lastReceviedTick1 = uwTick;
//		out2[rec_cnt++] = serialRead(s);
//	}
//	ec20Print("AT+QMTDISC=0\r\n");
//	yield(100);
	memset(out2,0,256);
	rec_cnt = 0;
	
//	ec20Print("carlo.peng\r\n");
//	while (serialAvailable(s))
//	{
//		serialRead(s);
//	}
	
	for(;;)
	{
//		yield(5);
//		sprintf(airpurifier_status,"{\"action\":\"m_update\",\"id\":1,\"speed\":%x,\"timing\":%d,\"lifetime\":%d,\"IAQ\":%d,\"PM2_5\":%d,\"TVOC\":%.1f,\"HCHO\":%.1f,\"tem\":%.1f\,\"hum\":%.1f}",\
//		motorData.setSpeedLevel,motorData.timeLeft/1000,filterNetData.useTime,sensorData.aqi,granuleData.data[1],vocData.val,methanalData.mmol,temperature,humidity);
//		ec20_send_datas((unsigned char *)airpurifier_status,strlen(airpurifier_status));
//		
		
  	if(uwTick - ec20TaskData.StatusSendTick > 10000)
		{
			ec20TaskData.StatusSendTick = uwTick;
//			sprintf(airpurifier_status,"{\"action\":\"m_update\",\"id\":1,\"speed\":%x,\"timing\":%d,\"lifetime\":%d,\"IAQ\":%d,\"PM2_5\":%d,\"TVOC\":%.1f,\"HCHO\":%.1f,\"tem\":%.1f\,\"hum\":%.1f}",\
//			motorData.setSpeedLevel,motorData.timeLeft/1000,filterNetData.useTime,sensorData.aqi,granuleData.data[1],vocData.val,methanalData.mmol,temperature,humidity);
			
			if(uiData.leftMode == UI_LEFT_POWER_OFF)
			{
				powerswitch = 0;
				workmode = 0;
			}
			else 
			{
				powerswitch = 1;
			}
			if(uiData.leftMode == UI_LEFT_AUTO)
			{
				workmode = 0;
			}
			else if(uiData.leftMode == UI_LEFT_SLEEP)
			{
				workmode = 2;
			}
			else if(uiData.leftMode == UI_LEFT_POWER_ON)
			{
				workmode =1;
			}
			else
			{
				
			}
//			sprintf(airpurifier_status,"{\"actionType\":\"upstream\",\"messageMethod\":\"\"thing.event.property.post\"\",\"messageID\":\"\"123\"\",\"messageParams\":\"{\"PM25Level\":1,\"TVOC\":%.1f,\"CurrentHumidity\":%.1f,\"HCHO\":%.1f,\"PowerSwitch\":%d,\"PM25\":%d,\"CurrentTemperature\":%.1f,\"WindSpeed\":%x,\"FilterLifeTimePercent_1\":%d,\"WorkMode\":%d},\"topic\":\"/sys/a1EfxtqrsRV/J1khEkDfzsMYcfgXl2yP/thing/event/property/post\",\"uniMsgId\":\"4514692839661821952\",\"version\":\"1.0\"}\",\"messageResult\":\"200\",\"logTime\":\"1557931637\"}",\
//			vocData.val,humidity,methanalData.mmol,powerswitch,granuleData.data[1],temperature,motorData.setSpeedLevel,test_percent,workmode);
			memset(out2,0,512);
			rec_cnt = 0;
//			sprintf(airpurifier_status,"{\"actionType\":\"upstream\",\"messageMethod\":\"thing.event.property.post\",\"messageID\":\"123\",\"messageParams\":{\"PM25Level\":1,\"TVOC\":%.1f,\"CurrentHumidity\":%.1f,\"HCHO\":%.1f,\"PowerSwitch\":%d,\"PM25\":%d,\"CurrentTemperature\":%.1f,\"WindSpeed\":%x,\"FilterLifeTimePercent_1\":%d,\"WorkMode\":%d},\"topic\":\"/sys/a1EfxtqrsRV/J1khEkDfzsMYcfgXl2yP/thing/event/property/post\",\"uniMsgId\":\"4514692839661821952\",\"version\":\"1.0\"}",\
//			vocData.val,humidity,methanalData.mmol,powerswitch,granuleData.data[1],temperature,motorData.setSpeedLevel,test_percent,workmode);
	
			if(motorData.setSpeedLevel == 0)
			{
				motorData.setSpeedLevel = 1;
			}
				
			sprintf(airpurifier_status," {\"id\":\"123\",\"params\": {\"PM25Level\":1,\"TVOC\":%.1f,\"CurrentHumidity\":%d,\"HCHO\":%.1f,\"PowerSwitch\":%d,\"PM25\":%d,\"CurrentTemperature\":%.1f,\"WindSpeed\":%x,\"FilterLifeTimePercent_1\":%d,\"WorkMode\":%d},\"method\": \"thing.event.property.post\"}",\
			vocData.val,(unsigned char)humidity,methanalData.mmol,powerswitch,granuleData.data[1],temperature,motorData.setSpeedLevel,test_percent,workmode);			
			len5 = strlen(airpurifier_status);
			ec20Print("AT+QMTPUB=0,0,0,0,\"/sys/a1EfxtqrsRV/zSSY9YVF9uM50NMW9wfJ/thing/event/property/post\"\r\n");
//			yield(100);
//			ec20_send_datas((unsigned char *)airpurifier_status,strlen(airpurifier_status));
			ec20_send_datas((unsigned char *)airpurifier_status,strlen(airpurifier_status));
//			yield(100);
			ec20_send_datas((unsigned char *)endstr,strlen(endstr));
//			yield(100);
//			char out1[256] = "{\"WindSpeed\":2}";
//			ec20_send_datas((unsigned char *)out1,strlen(out1));
//			ec20TaskData.StatusSendTick = uwTick;
			
		}
		while (serialAvailable(s))
		{
			ec20TaskData.lastReceviedTick = uwTick;
			ec20TaskData.lastReceviedTick1 = uwTick;
			out2[rec_cnt++] = serialRead(s);
			receive_flag = true;
		}
		
		if((uwTick - ec20TaskData.lastReceviedTick > 100)&&(receive_flag == true))
		{
			ec20TaskData.lastReceviedTick = uwTick;
			receive_flag = false;
			p = out2;
			char *p=strstr(out2,"WindSpeed");
			if(p)
			{
				len1 = p - out2;
				
				len2 = len1 + 11;
				
//				if(out2[len2] == 0x32)
//				{
//					motorData.setSpeedLevel =2;
//				}
				
				len3  = (char) out2[len2];
				switch(out2[len2])
				{
					case 48: motorData.autoModeEnable = true;
						break;
					case 49: motorData.setSpeedLevel =1;
									 motorData.autoModeEnable = false;
						break;
					case 50: motorData.setSpeedLevel =2;
									 motorData.autoModeEnable = false;
						break;
					case 51: motorData.setSpeedLevel =3;
									 motorData.autoModeEnable = false;
						break;
					case 52: motorData.setSpeedLevel =4;
									 motorData.autoModeEnable = false;
						break;
					default:break;
				}
			}

			p = out2;
			p = strstr(out2,"CurrentHumidity");
			if(p)
			{
				len1 = p - out2;
			}
			p = out2;
			p = strstr(out2,"CurrentTemperature");
			if(p)
			{
				len1 = p - out2;
			}
			p = out2;
			p = strstr(out2,"HCHO");
			if(p)
			{
				len1 = p - out2;
			}
			p = out2;		
			p = strstr(out2,"FilterLifeTimePercent_1");
			if(p)
			{
				len1 = p - out2;
			}
			p = out2;
			p = strstr(out2,"TVOC");
			if(p)
			{
				len1 = p - out2;
			}
			p = out2;
			p = strstr(out2,"WorkMode");
			if(p)
			{
				len1 = p - out2;
				switch(out2[len1+10])
				{
					case 48:	
						if(uiData.leftMode == UI_LEFT_SLEEP)
						{
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
						}
						else
						{
						
						}
						if(uiData.leftMode != UI_LEFT_POWER_OFF)
						{
							motorData.autoModeEnable = true;
						}
						break;
					case 49:	
						if(uiData.leftMode == UI_LEFT_SLEEP)
						{
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
							uiData.leftMode = UI_LEFT_POWER_ON;
						}
						else
						{
						
						}
						
						if(uiData.leftMode != UI_LEFT_POWER_OFF)
						{
							motorData.autoModeEnable = false;
						}
						break;
					case 50: uiData.leftMode = UI_LEFT_SLEEP;
						break;
					default:break;
				}
			}
			p = out2;
			p = strstr(out2,"PM25");
			if(p)
			{
				len1 = p - out2;
			}
			p = out2;
			p = strstr(out2,"PM25Level");
			if(p)
			{
				len1 = p - out2;
			}
			p = out2;
			p = strstr(out2,"PM25Level");
			if(p)
			{
				len1 = p - out2;
			}
			p = out2;
			p = strstr(out2,"PowerSwitch");
			if(p)
			{
				len1 = p - out2;
				switch(out2[len1+13])
				{
					case 48:							
							LCD_Default(LCD2);
							if( uiData.leftMode != UI_LEFT_POWER_OFF)
							{
									uiData.leftMode = UI_LEFT_POWER_OFF;
									uiData.rightMode = UI_RIGHT_POWER_OFF;
									TIM3->CCR2 = 0;
									LCD_WR_REG(LCD2, 0x28);
										
										motorData.timeLeft = 0;
										uiData.rightDisplay = 0;
									sysledofftimes = 0;
							}
						break;
					case 49:	     
								if(uiData.leftMode == UI_LEFT_POWER_OFF)
								{
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
								}
						break;
					default: break;
				}
			}

			p = out2;
			p = strstr(out2,"Error");
			if(p)
			{
				len1 = p - out2;
			}
//			ec20TaskData.lastReceviedTick = uwTick;
			
			memset(out2,0,256);
			rec_cnt = 0;
		}
		
		
//		if(uwTick - ec20TaskData.lastReceviedTick1 > 1000)
//		{		
//			memset(out2,0,256);
//			rec_cnt = 0;
//			ec20TaskData.lastReceviedTick1 = uwTick;
//		}

		vTaskDelayUntil(&xLastWakeTime, (10 / portTICK_RATE_MS));

	}
	
	
//	ec20Print("AT\r\n");
//	ec20Print("AT+CPIN?\r\n");
//	ec20Print("AT+CREG?\r\n");
//	while (serialAvailable(s))
//	{
//		serialRead(s);
//	}
//	ec20Print("AT+GSN\r\n");
//	while (serialAvailable(s))
//	{
//		if (rec_cnt < 255)
//		{
//			out2[rec_cnt++] = serialRead(s);
//		}
//		else
//		{
//			break;
//		}
//	}
//	for(i=0;i<15;i++)
//	{
//		imei_sequence[i] = out2[9+i];
//	}
//	/*configure a context*/
//	ec20Print("AT+QICSGP=1,1,\"UNINET\",\"\",\"\"1\r\n");
//	/*activate a context*/
//	ec20Print("AT+QIACT=1\r\n");
//	ec20Print("AT+QIACT?\r\n");
//	/*deactivate a context*/
////	ec20Print("AT+QIDEACT=1\r\n");
//	ec20Print("AT+QICLOSE=0\r\n");
//	/*TCP Client Works in Buffer Access Mode*/
////	ec20Print("AT+QIOPEN=1,0,\"TCP\",\"121.40.115.131\",18807,0,2\r\n");
//	ec20Print("AT+QIOPEN=1,0,\"TCP\",\"xwmw.yifangzn.com\",18807,0,2\r\n");

//	
//	// cJSON_m_discover();
//	
////	time_cnt1 = uwTickHD;
////	for (uint32_t i = 0; i < 100; i++)
////	{
////		memcpy(out_aes, out, 256);
////		len  = device_aes_encrypt(local_key,(unsigned char *)out_aes ,strlen(out));
////		len1 = base64_encode((unsigned char *)out_aes, len,(unsigned char *)out1);
////		time_cnt2 = uwTickHD - time_cnt1;
////	}

//		sprintf(m_info_out, "{\"action\":\"m_info\",\"id\":1,\"name\":\"SK300\",\"imei\":\"%s\",\"sim\":{\"iccid\":\"0\",\"imsi\":\"0\"}}",imei_sequence);

//		memcpy(out_aes, out, 256);
//		len  = device_aes_encrypt(local_key,(unsigned char *)out_aes ,strlen(out));
//		len1 = base64_encode((unsigned char *)out_aes, len,(unsigned char *)out1);

//		/* 清空接收缓存 */
//		while (serialAvailable(s))
//		{
//			serialRead(s);
//		}
//		
//		/* 数据发送 */
//		ec20_send_datas((unsigned char *)out1,len1);
//		ec20Print("\r\n");
//		
//		yield(1000);
//		
//		rec_cnt = 0;
//		while (serialAvailable(s))
//		{
//			if (rec_cnt < 255)
//			{
//				out2[rec_cnt++] = serialRead(s);
//			}
//			else
//			{
//				break;
//			}
//		}
//		
//		out2[rec_cnt] = 0;
//		
//		len2 = base64_decode((unsigned char *)out2, (unsigned char *)out3);  
//		device_aes_decrypt(AES_iv,(unsigned char  *)out3, len2);
//		
//		cJSON *json = cJSON_Parse(out3);
//		cJSON * pSub = cJSON_GetObjectItem(json, "ip");
//		number = pSub->valueint;
//		
//		json_sjjm=cJSON_GetObjectItem(json,"ip");
//		json_sj2=json_sjjm->valuestring;
//		strncpy (servers_ip,json_sj2,strlen(json_sj2));
//		
//		json_sjjm=cJSON_GetObjectItem(json,"port");
//		json_sj2=json_sjjm->valuestring;
//		strncpy (servers_port,json_sj2,strlen(json_sj2));
//		
//		cJSON_Delete(json);
//		sprintf(servers_ip_port0, "AT+QIOPEN=1,0,\"TCP\",\"%s\",%s,0,2\r\n", servers_ip,servers_port);
//		
//		ec20Print("AT\r\n");
//		ec20Print("AT+CPIN?\r\n");
//		ec20Print("AT+CREG?\r\n");
//		
//		ec20Print("AT+QICSGP=1,1,\"UNINET\",\"\",\"\"1\r\n");
//		/*activate a context*/
//		ec20Print("AT+QIACT=1\r\n");
//		ec20Print("AT+QIACT?\r\n");
//		/*deactivate a context*/
//	//	ec20Print("AT+QIDEACT=1\r\n");

//		ec20Print("AT+QICLOSE=0\r\n");
//		ec20Print((char *)&servers_ip_port0);
//		
//		
//		memset(out_aes,0,256);
//		memset(out1,0,256);
//		memset(out2,0,256);
//		memset(out3,0,256);
//		memcpy(out_aes, m_info_out, 256);
//		/* 清空接收缓存 */

//		len  = device_aes_encrypt(local_key,(unsigned char *)out_aes ,strlen(m_info_out));
//		len1 = base64_encode((unsigned char *)out_aes, len,(unsigned char *)out1);
//		while (serialAvailable(s))
//		{
//			serialRead(s);
//		}
//		ec20_send_datas((unsigned char *)out1,len1);
//		ec20Print("\r\n");
//		
//		yield(1000);
//		rec_cnt = 0;
//		while (serialAvailable(s))
//		{
//			if (rec_cnt < 255)
//			{
//				out2[rec_cnt++] = serialRead(s);
//			}
//			else
//			{
//				break;
//			}
//		}
//		out2[rec_cnt] = 0;
//		
//		len2 = base64_decode((unsigned char *)out2, (unsigned char *)out3);  
//		device_aes_decrypt(AES_iv,(unsigned char  *)out3, len2);
//		
////		cJSON *
//		json = cJSON_Parse(out3);
//		
//		json_sjjm=cJSON_GetObjectItem(json,"params");
//		json_sj2=json_sjjm->valuestring;
//		strncpy (key_temp,json_sj2,strlen(json_sj2));
//		
//		len3 = base64_decode((unsigned char *)key_temp, (unsigned char *)key_real);
//		
//		cJSON_Delete(json);
//		
//		memset(out2,0,256);
//		memset(out_aes1,0,256);
//		memset(out4,0,256);

//		////sprintf(out, "{\"action\":\"m_discover\",\"id\":1,\"nema\":\"sk300\",\"imei\":\"%x\"}", chipUniqueID[2]);
//		sprintf(airpurifier_status,"{\"action\":\"m_update\",\"id\":1,\"speed\":%x,\"timing\":%d,\"lifetime\":%d,\"IAQ\":%d,\"PM2_5\":%d,\"TVOC\":%.1f,\"HCHO\":%.1f,\"tem\":%.1f\,\"hum\":%.1f}",\
//		motorData.setSpeedLevel,motorData.timeLeft/1000,filterNetData.useTime,sensorData.aqi,granuleData.data[1],vocData.val,methanalData.mmol,temperature,humidity);
//		
//		memcpy(out_aes1, airpurifier_status, 256);
//		len3  = device_aes_encrypt(key_real,(unsigned char *)out_aes1 ,strlen(airpurifier_status));
//		len4 = base64_encode((unsigned char *)out_aes1, len3,(unsigned char *)out4);
//		
//		ec20_send_datas((unsigned char *)out4,len4);
//		ec20Print("\r\n");
//		ec20_send_datas((unsigned char *)out4,len4);
//		ec20Print("\r\n");
//		ec20_send_datas((unsigned char *)out4,len4);
//		ec20Print("\r\n");
//		ec20_send_datas((unsigned char *)out4,len4);
//		ec20Print("\r\n");
//		ec20_send_datas((unsigned char *)out4,len4);
//		ec20Print("\r\n");
//	
//		for ( ;; )
//    {
//     yield(5);
//		
//		if(uwTick - ec20TaskData.StatusSendTick > 10)
//		{
//			
//			ec20TaskData.StatusSendTick = uwTick;
//			//memset(out2,0,256);
//			memset(out_aes1,0,256);
//			memset(out4,0,256);

//			////sprintf(out, "{\"action\":\"m_discover\",\"id\":1,\"nema\":\"sk300\",\"imei\":\"%x\"}", chipUniqueID[2]);
//			sprintf(airpurifier_status,"{\"action\":\"m_update\",\"id\":1,\"speed\":%x,\"timing\":%d,\"lifetime\":%d,\"IAQ\":%d,\"PM2_5\":%d,\"TVOC\":%.1f,\"HCHO\":%.1f,\"tem\":%.1f\,\"hum\":%.1f}",\
//			motorData.setSpeedLevel,motorData.timeLeft/1000,filterNetData.useTime,sensorData.aqi,granuleData.data[1],vocData.val,methanalData.mmol,temperature,humidity);
//			
//			memcpy(out_aes1, airpurifier_status, 256);
//			len3  = device_aes_encrypt(key_real,(unsigned char *)out_aes1 ,strlen(airpurifier_status));
//			len4 = base64_encode((unsigned char *)out_aes1, len3,(unsigned char *)out4);
//		/* 数据发送 */
//			ec20_send_datas((unsigned char *)out4,len4);
//			ec20Print("\r\n");
//			
//			while (serialAvailable(s))
//			{
//				if(rec_cnt == 0xff)
//				{
//					rec_cnt = 0;
//				}
//			if (rec_cnt < 255)
//			{
//				out2[rec_cnt++] = serialRead(s);
//			}
//			else
//			{
//				break;
//			}
//			}

//		}
//	}

}

void ec20Init(void)
{
    /* Sleep status PD14 控制4G模块 AP Ready */
    /* ON/OFF PD12 控制4G模块 PWRKEY */
    /* RESET PD15 控制4G模块 RESET-N */
    //digitalInit(GPIOD, GPIO_Pin_12, 0);
//    digitalInit(GPIOD, GPIO_Pin_15, 1);
	  EC20PowerKeyInit();
    ec20TaskData.serialPort = serialOpen(EC20_UART, EC20_UART_BAUD, USART_HardwareFlowControl_None, 512, 512);
    
    xTaskCreate(afxEC20Task, "EC20", TASK_EC20_STACK_SIZE, NULL, TASK_EC20_PRIORITY, &taskEC20Handle);
}

/* end of file */
