#include "granule.h"
#include "string.h"
#include "sensor.h"

/* ����ģ��ͨ�ŷ�Ϊ�����ϴ�ʽ���ʴ�ʽ������Ĭ�������ϴ�,ÿ���1S����һ��Ũ��ֵ */
const uint8_t granuleModeActiveWord[7] = { 
    0x42, 0x4d, 0xe1, 0x00, 0x01, 0x00, 0x00, }; /* �����ϱ������� */
const uint8_t granuleModePassiveWord[7] = { 
    0x42, 0x4d, 0xe1, 0x00, 0x00, 0x00, 0x00, }; /* �����ʴ������� */
const uint8_t granuleRequstWord[7] = { 
    0x42, 0x4d, 0xe2, 0x00, 0x00, 0x00, 0x00 }; /* �������� */

granuleStruct_t granuleData;

/* ����������ģ�� �����ϱ�/�����ʴ� ģʽ���� */
void granuleSetMode(granuleMode_t mode)
{
    uint8_t *cmd = NULL;
    
    granuleData.mode = mode;

    if (mode == granuleMode_Active)
    {
        cmd = (uint8_t *)granuleModeActiveWord;
    }
    else if (mode == granuleMode_Passive)
    {
        cmd = (uint8_t *)granuleModePassiveWord;
    }
    
    serialWriteBlock(granuleData.serialPort, cmd, 9);
}

/* ����������ģ�� �����ʴ�ģʽ�����󴫸������� */
void granuleRequest(void)
{
    uint8_t *cmd = NULL;
    
    if (granuleData.mode == granuleMode_Passive)
    {
        cmd = (uint8_t *)granuleRequstWord;
        serialWriteBlock(granuleData.serialPort, cmd, 9);
    }
}

/* ����������ģ�� ���ݰ�У�� */
uint16_t granuleCheckSum(uint8_t *buf, uint8_t length)
{
    uint16_t checkSum = 0;

    for (uint8_t i = 0; i < length; i++)
    {
        checkSum += buf[i];
    }
    
    return checkSum;
}

float granuleExchange(float data)
{
	float temp_data;
//	if(data <= 50)
//	{
//		temp_data =  data;
//	}
//	else if(data <= 100)
//	{
//		temp_data = data + 10; 
//	}
//	else if(data <= 130)
//	{
//		temp_data = data + 20;
//	}
//	else if(data <= 250)
//	{
//		temp_data = data + 40;
//	}
//	else if(data <= 300)
//	{
//		temp_data = data + 70;
//	}
//	else if(data <= 350)
//	{
//		temp_data = data + 80;
//	}
//	else if(data <= 400)
//	{
//		temp_data = data + 100;
//	}
//	else if(data <= 450)
//	{
//		temp_data = data + 150;
//	}
//	else if(data <= 500)
//	{
//		temp_data = data + 200
//	}
//	else 
//	{
//		temp_data = data + 250;
//	}

	temp_data = data*1.2f;
	return temp_data;
}

/* ����������ģ�� ���ݽ��� */
void granuleParseChar(uint8_t data)
{
    uint8_t i;
    uint16_t checkSum = 0;
    
//    granuleData.mmol = 1.0f;
    
    granuleData.receiveBuf[granuleData.parseStatus] = data;
    
    if (granuleData.parseStatus == 0)
    {
        if (data == 0x42)
        {
            granuleData.parseStatus++;
        }
    }
    else if (granuleData.parseStatus == 1)
    {
        if (data == 0x4d)
        {
            granuleData.parseStatus++;
        }
        else
        {
            granuleData.parseStatus = 0;
        }
    }
    else if (granuleData.parseStatus == 2)
    {
        granuleData.parseStatus++;
    }
    else if (granuleData.parseStatus == 3)
    {
        if (data == 28)
        {
            granuleData.parseStatus++;
        }
        else 
        {
            granuleData.parseStatus = 0;
        }
    }
    else if (granuleData.parseStatus < 31)
    {
        granuleData.parseStatus++;
    }
    else
    {
        granuleData.parseStatus = 0;
        checkSum = granuleCheckSum(granuleData.receiveBuf, 30);
        
        granuleData.checkByte[0] = checkSum >> 8;
        granuleData.checkByte[1] = checkSum & 0xff;
        if (granuleData.checkByte[0] == granuleData.receiveBuf[30] && granuleData.checkByte[1] == granuleData.receiveBuf[31]) /* ����ɹ� */
        {
            for (i = 0; i < 12; i++)
            {
							
							granuleData.data[i] = (unsigned short)((float)((granuleData.receiveBuf[4 + 2 * i] << 8) + granuleData.receiveBuf[5 + 2 * i]));
							
							if(granuleData.data[i] < 500)
							{
                granuleData.data[i] = (unsigned short)((float)((granuleData.receiveBuf[4 + 2 * i] << 8) + granuleData.receiveBuf[5 + 2 * i]));
							}
							else if(granuleData.data[i] < 600)
							{
								granuleData.data[i] =(unsigned short) ((((float)granuleData.data[i])/500)*granuleData.data[i]);
							}
							else 
							{
								granuleData.data[i] = (unsigned short)((float)((granuleData.receiveBuf[4 + 2 * i] << 8) + granuleData.receiveBuf[5 + 2 * i])*1.2f);
							}
            }
			
//			granuleData.ugm3 = (granuleData.receiveBuf[6]*0xff) + granuleData.receiveBuf[7];
						granuleData.ugm3 = (granuleData.receiveBuf[6]*0xff) + granuleData.receiveBuf[7];
//						granuleData.ugm3      =  granuleExchange(granuleData.temp_ugm3);
			
            granuleData.version = granuleData.receiveBuf[28];
            granuleData.errCode = granuleData.receiveBuf[29];
			
			
        }
				
			
		
		if(granuleData.ugm3 >= 115)
		{
			sensorData.overload[0] = 1; 
		}
		else
		{
			sensorData.overload[0] = 0;
		}
    }

}

void granuleUpdate(void)
{
    serialPort_t *s = granuleData.serialPort;
    
    while (serialAvailable(s))
    {
        granuleParseChar(serialRead(s));
    }
}

/* ����������ģ�� ��ʼ�� */
void granuleInit(void)
{
    /* PD2 PC12���� PA8ģʽѡ�� ��������9600 */
    digitalInit(GPIOA, GPIO_Pin_8, 1);
    
    /* ���ڳ�ʼ�� */
    granuleData.serialPort = serialOpen(GRANULE_UART, GRANULE_UART_BAUD, \
        USART_HardwareFlowControl_None, 128, 128);
}

/* end of file */
