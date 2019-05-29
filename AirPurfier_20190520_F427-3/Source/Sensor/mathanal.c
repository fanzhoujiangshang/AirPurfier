#include "methanal.h"
#include "timer.h"
#include "sensor.h"

/* 甲醛模块通信分为主动上传式和问答式，出厂默认主动上传,每间隔1S发送一次浓度值 */
const uint8_t methanalModeActiveWord[9] = { 
    0xff, 0x01, 0x78, 0x40, 0x00, 0x00, 0x00, 0x00, 0x47 }; /* 主动上报命令字 */
const uint8_t methanalModePassiveWord[9] = { 
    0xff, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46 }; /* 被动问答命令字 */
const uint8_t methanalRequstWord[9] = { 
    0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 }; /* 读传感器 */

methanalStruct_t methanalData;

/* 甲醇传感器模块 主动上报/被动问答 模式设置 */
void methanalSetMode(methanalMode_t mode)
{
    uint8_t *cmd = NULL;
    
    methanalData.mode = mode;

    if (mode == methanalMode_Active)
    {
        cmd = (uint8_t *)methanalModeActiveWord;
    }
    else if (mode == methanalMode_Passive)
    {
        cmd = (uint8_t *)methanalModePassiveWord;
    }
    
    serialWriteBlock(methanalData.serialPort, cmd, 9);
}

/* 甲醇传感器模块 被动问答模式下请求传感器数据 */
void methanalRequest(void)
{
    uint8_t *cmd = NULL;
    
    if (methanalData.mode == methanalMode_Passive)
    {
        cmd = (uint8_t *)methanalRequstWord;
        serialWriteBlock(methanalData.serialPort, cmd, 9);
    }
}

/* 甲醇传感器模块 数据包校验 */
uint8_t methanalCheckSum(uint8_t *buf, uint8_t length)
{
    uint8_t checkByte = 0;

    for (uint8_t i = 1; i < (length - 1); i++)
    {
        checkByte += buf[i];
    }
    checkByte = (~checkByte)+1;
    
    return checkByte;
}

/* 甲醇传感器模块 数据解析 */
void methanalParseChar(uint8_t data)
{
//    methanalData.mmol = 1.0f;
    
    methanalData.receiveBuf[methanalData.parseStatus] = data;
    
    switch (methanalData.parseStatus)
    {
    case 0:
        if (data == 0xff)
        {
            methanalData.parseStatus = 1;
        }
        break;
        
    case 1:
        if (data == 0x86) /* 被动请求包 */
        {
            methanalData.parseStatus = 2;
            methanalData.packetType = 1;
        }
        else if (data == 0x17) /* 主动上报包 */
        {
            methanalData.parseStatus = 2;
            methanalData.packetType = 2;
        }
        else
        {
            methanalData.parseStatus = 0;
        }
        break;
        
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        methanalData.parseStatus++;
        break;
    
    case 8:
        methanalData.parseStatus = 0;
        methanalData.checkByte = methanalCheckSum(methanalData.receiveBuf, 9);
    
        if (methanalData.checkByte == data) /* 检验成功 */
        {
            if (methanalData.packetType == 1) /* 被动请求包 */
            {
                methanalData.mmol = (float)((methanalData.receiveBuf[6] << 8) + methanalData.receiveBuf[7])/10000;
                methanalData.updateTick = uwTick;
            }
            else if (methanalData.packetType == 2) /* 主动上报包 */
            {
                methanalData.mmol = (float)((methanalData.receiveBuf[4] << 8) + methanalData.receiveBuf[5])/10000;
                methanalData.updateTick = uwTick;
            }
        }
        break;
    }   
	if(methanalData.mmol >= 0.2f)
	{
//		sensorData.overload[1] = 1; 
	}
	else
	{
		sensorData.overload[1] = 0; 
	}
}

void methanalUpdate(void)
{
    serialPort_t *s = methanalData.serialPort;
    
    while (serialAvailable(s))
    {
        methanalParseChar(serialRead(s));
        
        if (methanalData.updateTick + 2000 < uwTick)
        {
            /* 甲醛等级：良好：0-0.04；合格:0.04-0.08；超标：0.08-0.2；严重超标：0.2以上 */
            if (methanalData.mmol < 0.04f)
            {
                methanalData.level = 0;
            }
            else if (methanalData.mmol < 0.08f)
            {
                methanalData.level = 1;
            }
            else if (methanalData.mmol < 0.2f)
            {
                methanalData.level = 2;
            }
            else 
            {
                methanalData.level = 3;
            }
        }
    }
}

void methanalInit(void)
{
    /* 甲醛模组(串口) Methanal */
    methanalData.serialPort = serialOpen(METHANAL_UART, METHANAL_UART_BAUD, \
        USART_HardwareFlowControl_None, 128, 128);
    
    /* 设置为主动式 */
    methanalSetMode(methanalMode_Active);
}

/* end of file */
