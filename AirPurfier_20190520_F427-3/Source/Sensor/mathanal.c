#include "methanal.h"
#include "timer.h"
#include "sensor.h"

/* ��ȩģ��ͨ�ŷ�Ϊ�����ϴ�ʽ���ʴ�ʽ������Ĭ�������ϴ�,ÿ���1S����һ��Ũ��ֵ */
const uint8_t methanalModeActiveWord[9] = { 
    0xff, 0x01, 0x78, 0x40, 0x00, 0x00, 0x00, 0x00, 0x47 }; /* �����ϱ������� */
const uint8_t methanalModePassiveWord[9] = { 
    0xff, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46 }; /* �����ʴ������� */
const uint8_t methanalRequstWord[9] = { 
    0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 }; /* �������� */

methanalStruct_t methanalData;

/* �״�������ģ�� �����ϱ�/�����ʴ� ģʽ���� */
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

/* �״�������ģ�� �����ʴ�ģʽ�����󴫸������� */
void methanalRequest(void)
{
    uint8_t *cmd = NULL;
    
    if (methanalData.mode == methanalMode_Passive)
    {
        cmd = (uint8_t *)methanalRequstWord;
        serialWriteBlock(methanalData.serialPort, cmd, 9);
    }
}

/* �״�������ģ�� ���ݰ�У�� */
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

/* �״�������ģ�� ���ݽ��� */
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
        if (data == 0x86) /* ��������� */
        {
            methanalData.parseStatus = 2;
            methanalData.packetType = 1;
        }
        else if (data == 0x17) /* �����ϱ��� */
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
    
        if (methanalData.checkByte == data) /* ����ɹ� */
        {
            if (methanalData.packetType == 1) /* ��������� */
            {
                methanalData.mmol = (float)((methanalData.receiveBuf[6] << 8) + methanalData.receiveBuf[7])/10000;
                methanalData.updateTick = uwTick;
            }
            else if (methanalData.packetType == 2) /* �����ϱ��� */
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
            /* ��ȩ�ȼ������ã�0-0.04���ϸ�:0.04-0.08�����꣺0.08-0.2�����س��꣺0.2���� */
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
    /* ��ȩģ��(����) Methanal */
    methanalData.serialPort = serialOpen(METHANAL_UART, METHANAL_UART_BAUD, \
        USART_HardwareFlowControl_None, 128, 128);
    
    /* ����Ϊ����ʽ */
    methanalSetMode(methanalMode_Active);
}

/* end of file */
