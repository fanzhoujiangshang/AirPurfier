#include "st7789.h"
#include "spi.h"
#include "timer.h"
#include "digital.h"
#include "fonts.h"

#define BK1 0
#define BK2 0

TF1touchStruct_t TF1touchdata,TF2touchdata;

void st7789Reset(void)
{
    LCD_RST_1;  
//    
    LCD1_CS_0;
    LCD2_CS_0;
//    
//// 	delay_ms(1);
////	LCD_RST_0;
////	delay_ms(100);
////	LCD_RST_1;
////	delay_ms(100);
//    
//    LCD_BL_1;
//		LCD2_BL_1;

}

void LCD_WR_REG(LcdIndexType_t lcd, uint32_t cmd)
{
    if (lcd == LCD1)
    {   
//        LCD2_DC_0;
//        LCD1_SCK_0; (cmd & 0x80) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (cmd & 0x40) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (cmd & 0x20) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (cmd & 0x10) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (cmd & 0x08) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (cmd & 0x04) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (cmd & 0x02) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (cmd & 0x01) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//      
//        LCD1_DC_1;
		
//				LCD1_CS_0;
        LCD1_DC_0;
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
					SPI_I2S_SendData(SPI1, cmd);
				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//				LCD1_CS_1;
				LCD1_DC_1;
		
    }
    else
    {
//        LCD2_DC_0;
//        
//        LCD2_SCK_0; (cmd & 0x80) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (cmd & 0x40) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (cmd & 0x20) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (cmd & 0x10) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (cmd & 0x08) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (cmd & 0x04) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (cmd & 0x02) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (cmd & 0x01) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        
//        LCD2_DC_1;
		
//		LCD2_CS_0;
			
			
        LCD2_DC_0;
		while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);
		//SPI_I2S_SendData(SPI2, cmd);
		SPI4->DR = cmd;
		while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);
//		LCD2_CS_1;
		LCD2_DC_1;
    }
}

void LCD_WR_DATA(LcdIndexType_t lcd, uint32_t data)
{
    if (lcd == LCD1)
    {
//        LCD1_SCK_0; (data & 0x80) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x40) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x20) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x10) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x08) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x04) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x02) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x01) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
        		
//		LCD1_CS_0;
        LCD1_DC_1;
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, data);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//		LCD1_CS_1;
    }
    else
    {
//					LCD2_DC_1;
//        LCD2_SCK_0; (data & 0x80) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x40) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x20) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x10) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x08) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x04) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x02) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x01) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;

		  LCD2_DC_1;
		  while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);
          //SPI_I2S_SendData(SPI2, data);
			SPI4->DR = data;
		  while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);

    }
}

void LCD_WR_DATA16(LcdIndexType_t lcd, uint32_t data)
{
    if (lcd == LCD1)
    {
//        LCD1_SCK_0; (data & 0x8000) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x4000) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x2000) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x1000) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0800) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0400) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0200) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0100) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0080) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0040) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0020) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0010) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0008) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0004) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0002) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
//        LCD1_SCK_0; (data & 0x0001) ? LCD1_SDA_1 : LCD1_SDA_0; LCD1_SCK_1;
		
//      LCD1_CS_0;
        LCD1_DC_1;
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, data >> 8);
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, data & 0xff);
				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//   	LCD1_CS_1;
    }
    else
    {
//			LCD2_DC_1;
//        LCD2_SCK_0; (data & 0x8000) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x4000) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x2000) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x1000) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0800) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0400) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0200) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0100) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0080) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0040) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0020) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0010) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0008) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0004) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0002) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
//        LCD2_SCK_0; (data & 0x0001) ? LCD2_SDA_1 : LCD2_SDA_0; LCD2_SCK_1;
        
		
//		  LCD2_CS_0;
          LCD2_DC_1;
          while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);
          //SPI_I2S_SendData(SPI2, data >> 8);
		  SPI4->DR = data >> 8;
          while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);
          //SPI_I2S_SendData(SPI2, data & 0xff);
		  SPI4->DR = data &0xff;
		  while (SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE) == RESET);
//		  LCD2_CS_1;
    }
}

void LCD_SetCursor(LcdIndexType_t lcd, u16 Xpos, u16 Ypos)
{
	LCD_WR_REG(lcd, 0x2a);
	LCD_WR_DATA(lcd, Xpos >> 8);
	LCD_WR_DATA(lcd, Xpos & 0xff);
  LCD_WR_DATA(lcd, 0);
	LCD_WR_DATA(lcd, 0xef);
	LCD_WR_REG(lcd, 0x2b);
	LCD_WR_DATA(lcd, Ypos >> 8);
	LCD_WR_DATA(lcd, Ypos & 0xff);
  LCD_WR_DATA(lcd, 0);
	LCD_WR_DATA(lcd, 0xef);
  LCD_WR_REG(lcd, 0x2c); 
}

////??LeftInit
void st7789LowLevelInit(LcdIndexType_t lcd)
{
//	LCD1_WR_REG(0x11); /* Sleep out */
//	delay_ms(120);         //Delay 120ms 

	//--------------------------------------Display Setting------------------------------------------// 
	LCD_WR_REG(lcd, 0x36); /* Memory data access control */
	LCD_WR_DATA(lcd, 0x00); 
	LCD_WR_REG(lcd, 0x3a); /* Interface pixal format */
	LCD_WR_DATA(lcd, 0x55); 
	//--------------------------------ST7789S Frame rate setting----------------------------------// 
	LCD_WR_REG(lcd, 0xb2); /* Porch setting */
	LCD_WR_DATA(lcd, 0x0c);
	LCD_WR_DATA(lcd, 0x0c);
	LCD_WR_DATA(lcd, 0x00);
	LCD_WR_DATA(lcd, 0x33);
	LCD_WR_DATA(lcd, 0x33);
	LCD_WR_REG(lcd, 0xb7); /* Gate control */
	LCD_WR_DATA(lcd, 0x35); // 0x35
	//---------------------------------ST7789S Power setting--------------------------------------// 
	LCD_WR_REG(lcd, 0xbb); 	/* VCOM setting */
	LCD_WR_DATA(lcd, 0x3d); /* 0x28 0x0e */
	LCD_WR_REG(lcd, 0xc0); 	/* LCM control */
	LCD_WR_DATA(lcd, 0x2c);
	LCD_WR_REG(lcd, 0xc2); 	/* VDV and VRH command enable */
	LCD_WR_DATA(lcd, 0x01);
	LCD_WR_REG(lcd, 0xc3); 	/* VRH set */
	LCD_WR_DATA(lcd, 0x19); /* 0x12 */
	LCD_WR_REG(lcd, 0xc4); 	/* VDV set */
	LCD_WR_DATA(lcd, 0x20); 
	LCD_WR_REG(lcd, 0xc6); 	/* Frame rate control in normal mode */
	LCD_WR_DATA(lcd, 0x0f); 
	LCD_WR_REG(lcd, 0xd0); 	/* Power control 1 */
	LCD_WR_DATA(lcd, 0xa4); 
	LCD_WR_DATA(lcd, 0xa1); 
	//--------------------------------ST7789S gamma setting---------------------------------------// 
	LCD_WR_REG(lcd, 0xe0); /* Positive voltage gamma control */
	LCD_WR_DATA(lcd, 0xd0); 
	LCD_WR_DATA(lcd, 0x06); 
	LCD_WR_DATA(lcd, 0x0b); 
	LCD_WR_DATA(lcd, 0x0a); /* 0x0d */
	LCD_WR_DATA(lcd, 0x09); /* 0x0f */
	LCD_WR_DATA(lcd, 0x06); /* 0x2b */
	LCD_WR_DATA(lcd, 0x2f); /* 0x3b */
	LCD_WR_DATA(lcd, 0x44); /* 0x44 */
	LCD_WR_DATA(lcd, 0x45); /* 0x4a */
	LCD_WR_DATA(lcd, 0x18); /* 0x18 */
	LCD_WR_DATA(lcd, 0x14); /* 0x0f */
	LCD_WR_DATA(lcd, 0x14); /* 0x06 */
	LCD_WR_DATA(lcd, 0x27); /* 0x1f */
	LCD_WR_DATA(lcd, 0x2d); /* 0x22 */
    
	LCD_WR_REG(lcd, 0xe1); /* Negative voltage gamma control */
	LCD_WR_DATA(lcd, 0xd0); 
	LCD_WR_DATA(lcd, 0x06); 
	LCD_WR_DATA(lcd, 0x0b); 
	LCD_WR_DATA(lcd, 0x0a);
    
    LCD_WR_DATA(lcd, 0x09); /* 0x10 */
	LCD_WR_DATA(lcd, 0x05); /* 0x2b */
	LCD_WR_DATA(lcd, 0x2e); /* 0x3d */
	LCD_WR_DATA(lcd, 0x43); /* 0x54 */
	LCD_WR_DATA(lcd, 0x45); /* 0x50 */
	LCD_WR_DATA(lcd, 0x18); /* 0x2f */
	LCD_WR_DATA(lcd, 0x14); /* 0x1f */
	LCD_WR_DATA(lcd, 0x14); /* 0x1f */
	LCD_WR_DATA(lcd, 0x27); /* 0x1f */
	LCD_WR_DATA(lcd, 0x2d); /* 0x19 */
	
    LCD_WR_REG(lcd, 0x21);
    LCD_WR_REG(lcd, 0x11);
    LCD_WR_REG(lcd, 0x29);
}

void LCD_Clear(LcdIndexType_t lcd, uint16_t color)
{
    uint32_t i;
    uint32_t j;
    
	LCD_SetCursor(lcd, 0, 0);//?????? 
 	  
	for (i = 0; i < WIDTH; i++)
	{
        for (j = 0; j < HEIGHT; j++)
        {
            LCD_WR_DATA16(lcd, color);
        }
	}
}

void LCD_Default(LcdIndexType_t lcd)
{
    uint32_t i;
    uint32_t j;
    
	LCD_SetCursor(lcd, 0, 0);
 	  
	for (i = 0; i < HEIGHT; i++)
	{
        for (j = 0; j < WIDTH; j++)
        {
            if (i > j)
            {
                LCD_WR_DATA16(lcd, BK1);
            }
            else
            {
                LCD_WR_DATA16(lcd, BK2);
            }
        }
	}
}

void LCD_SetArea(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    LCD_WR_REG(lcd, 0x2a);
	LCD_WR_DATA16(lcd, x);
	LCD_WR_DATA16(lcd, x + w - 1);
	LCD_WR_REG(lcd, 0x2b);
	LCD_WR_DATA16(lcd, y);
	LCD_WR_DATA16(lcd, y + h - 1);
    LCD_WR_REG(lcd, 0x2c);
}

void LCD_clear(LcdIndexType_t lcd, unsigned short color)
{
    uint32_t i;
    uint32_t j;
	//uint32_t k;
    
	LCD_SetCursor(lcd, 0, 0);//?????? 
 	  
	for (i = 0; i < WIDTH; i++)
	{
        for (j = 0; j < HEIGHT; j++)
        {
            LCD_WR_DATA16(lcd, color);
//			if((i == 102)&&(j == 0))
//			{
//				k = i + j;
//			}
        }
	}
}

void st7789Init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;
		SPI_InitTypeDef SPI_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
//	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource2,GPIO_AF_SPI4); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_SPI4); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_4);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
    
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
//    
//	GPIO_SetBits(GPIOE,GPIO_Pin_2);
//	
//	
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
//    
//	GPIO_SetBits(GPIOE,GPIO_Pin_6);
//	
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//??SPI???????????:SPI??????????
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;//??SPI????:????SPI
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;//??SPI?????:SPI????8????
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;//??????????:?????
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;//???????????
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//NSS?????(NSS??)????(??SSI?)??:??NSS???SSI???
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;//??????????:????????256
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//???????MSB???LSB???:?????MSB???
	SPI_InitStructure.SPI_CRCPolynomial=7;//CRC???????
	SPI_Init(SPI4,&SPI_InitStructure);//??SPI_InitStruct???????????SPIx???
    
	SPI_Cmd(SPI4,ENABLE);//??SPI??
	
    spiInit();
	
//  	spi2Init();

    st7789Reset();
    
    st7789LowLevelInit(LCD1);
    st7789LowLevelInit(LCD2);
    
    LCD_Default(LCD1);
    LCD_Default(LCD2);
	
//    drawIcon(LCD1, 96, 96, RED, 1, 1);
		lcdDrawIcon(LCD1, 90, 80, POWER_ON_OFF, 72, 70, RED);
		delay_ms(50);
    LCD_BL_1;
		LCD2_BL_1;

//    LCD1_Default();
//    
//    //lcdDrawRectange(50, 50, 50, 50, RED);
//    
//    drawIcon(96, 96, WHITE, 1);
//    
//    LCD_DrawKanji(100, 180, RED, 0, 0);
//    LCD_DrawKanji(116, 180, RED, 0, 1);
//    LCD_DrawKanji(132, 180, RED, 0, 2);
//    LCD_DrawKanji(148, 180, RED, 0, 3);
    
//    while (1);
    
//    while (1)
//    {
//        for (uint32_t i = 0; i < 100; i++)
//        {
//            drawNum(80, 90, BLUE, 0, i / 10);
//            drawNum(120, 90, BLUE, 0, i % 10);
//        }
//    }
//    while (1)
//    {
////        LCD1_Clear(RED);
////        //LCD2_Clear(RED);
////        LCD1_Clear(GREEN);
////        //LCD2_Clear(GREEN);
////        LCD1_Clear(BLUE);
////        //LCD2_Clear(BLUE);
//		for(i=0;i<20;i++)
//		{
//			LCD_DrawKanji(50, 100, YELLOW, 0, i);
//			delay_ms(1000);
//			//LCD1_Clear(GREEN);
//			
//		}
//    }
} 

void drawNum(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, uint32_t size, uint32_t num)
{
    uint32_t i, j;
    uint32_t tempx, tempy;
    
    if (size == 40)
    {
        LCD_SetArea(lcd, x, y, 40, 60);
        
        for (i = 0; i < 60; i++)
        {
            for (j = 0; j < 40; j++)
            {
                tempx = j / 8;
                tempy = j % 8;
                if (Font40Num_Table[num * 300 + 5 * i + tempx] & (0x80 >> tempy))
                {
                    LCD_WR_DATA16(lcd, color);
                }
                else
                {
                    LCD_WR_DATA16(lcd, BK1);
                }
            }
        }
    }
	else if (size == 35)
	{
        LCD_SetArea(lcd, x, y, 40, 60);
        
        for (i = 0; i < 60; i++)
        {
            for (j = 0; j < 40; j++)
            {
                tempx = j / 8;
                tempy = j % 8;
                if (Font35Num_Table[num * 300 + 5 * i + tempx] & (0x80 >> tempy))
                {
                    LCD_WR_DATA16(lcd, color);
                }
                else
                {
                    LCD_WR_DATA16(lcd, BK1);
                }
            }
        }
	
	}
    else if (size == 24)
    {
        LCD_SetArea(lcd, x, y, 24, 40);
        
        for (i = 0; i < 40; i++)
        {
            for (j = 0; j < 24; j++)
            {
                tempx = j / 8;
                tempy = j % 8;
                if (Font24Num_Table[num * 120 + 3 * i + tempx] & (0x80 >> tempy))
                {
                    LCD_WR_DATA16(lcd, color);
                }
                else
                {
                    LCD_WR_DATA16(lcd, BK1);
                }
            }
        }
    }
    else if (size == 20)
    {
        LCD_SetArea(lcd, x, y, 20, 30);
        
        for (i = 0; i < 30; i++)
        {
            for (j = 0; j < 20; j++)
            {
                tempx = j / 8;
                tempy = j % 8;
                if (Font20Num_Table[num * 90 + 3 * i + tempx] & (0x80 >> tempy))
                {
                    LCD_WR_DATA16(lcd, color);
                }
                else
                {
                    LCD_WR_DATA16(lcd, BK1);
                }
            }
        }
    }
}

void LCD_DrawKanji(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, uint32_t font, uint32_t index)
{
    uint32_t i, j;
    uint32_t tempx, tempy;
    
    LCD_SetArea(lcd, x, y, 16, 16);
    
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            tempx = j / 8;
            tempy = j % 8;
            if (GB_16[index * 32 + 2 * i + tempx] & (0x80 >> tempy))
            {
                LCD_WR_DATA16(lcd, color);
            }
            else
            {
                LCD_WR_DATA16(lcd, BK1);
            }
        }
    }
}

void drawKanjiFromTable(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, const uint8_t *table, uint8_t index)
{
	uint32_t i, j;
    uint32_t tempx, tempy;
    
    LCD_SetArea(lcd, x, y, 16, 16);

    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            tempx = j / 8;
            tempy = j % 8;
            if (table[index * 32 + 2 * i + tempx] & (0x80 >> tempy))
            {
                LCD_WR_DATA16(lcd, color);
            }
            else
            {
                LCD_WR_DATA16(lcd, BK1);
            }
        }
    }
}

void drawIcon(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, uint32_t index, uint8_t transparent)
{
    uint32_t i, j;
    uint32_t tempx, tempy;
    
    uint8_t *pTable = NULL;
    
    LCD_SetArea(lcd, x, y, 48, 48);
    
    if (index == 1)
    {
        pTable = (uint8_t *)PowerIcon_Table;
    }
    else
    {
        pTable = (uint8_t *)SleepIcon_Table;
    }
    
    for (i = 0; i < 48; i++)
    {
        for (j = 0; j < 48; j++)
        {
            tempx = j / 8;
            tempy = j % 8;
            if (pTable[6 * i + tempx] & (0x80 >> tempy))
            {
                LCD_WR_DATA16(lcd, color);
            }
            else
            {
                LCD_WR_DATA16(lcd, BK1);
            }
        }
    }
}

void drawIcon_R(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, uint32_t index, uint8_t transparent)
{
    uint32_t i, j;
    uint32_t tempx, tempy;
    
    uint8_t *pTable = NULL;
    
    LCD_SetArea(lcd, x, y, 48, 48);
    
    
    if (index == 1)
    {
        pTable = (uint8_t *)PowerIcon_Table;
    }
    else
    {
        pTable = (uint8_t *)SleepIcon_Table;
    }
    
    for (i = 0; i < 48; i++)
    {
        for (j = 0; j < 48; j++)
        {
            tempx = j / 8;
            tempy = j % 8;
            if (pTable[6 * i + tempx] & (0x80 >> tempy))
            {
                LCD_WR_DATA16(lcd, color);
            }
            else
            {
                if (transparent)
                {
                    LCD_WR_DATA16(lcd, BK1);
                }
                else
                {
                    LCD_WR_DATA16(lcd, BLACK);
                }
            }
        }
    }
}

void lcdDrawRectange(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color)
{
    uint32_t i, j;
    
    LCD_SetArea(lcd, x, y, w, h);
    
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < h; j++)
        {
            LCD_WR_DATA16(lcd, color);
        }
    }
}

void lcdDrawRectangeDefault(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    uint32_t i, j;
    
    LCD_SetArea(lcd, x, y, w, h);
    
    for (i = 0; i < w; i++)
    {
        for (j = 0; j < h; j++)
        {
            LCD_WR_DATA16(lcd, BK1);
        }
    }
}

/* 字符显示 */
void lcdDisplayChar(LcdIndexType_t lcd, uint32_t x, uint32_t y, const char c, sFONT* Font, uint16_t color)
{
	uint32_t i, j;
	
	uint32_t Char_Offset = (c - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
	
	const unsigned char* ptr = &Font->table[Char_Offset];
	
    LCD_SetArea(lcd, x, y, Font->Width, Font->Height);

	for (i = 0; i < Font->Height; i++ )
	{
		for ( j = 0; j < Font->Width; j ++ )
		{
			//To determine whether the font background color and screen background color is consistent

			if (*ptr & (0x80 >> (j % 8)))
			{
				LCD_WR_DATA16(lcd, color);
			}
			else
			{
                LCD_WR_DATA16(lcd, BK1);
			}

			//One pixel is 8 bits
            if (j % 8 == 7)
			{
                ptr++;
            }	
		}
		
		/* Write a line */
		if (Font->Width % 8 != 0)
		{
				ptr++;
		}
	}/* Write all */
}

void lcdPrintFloat(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint16_t color, sFONT* Font, float a, int digit)
{
	char str[32] = { 0 };
	int val_max = 1;

	if (digit > 5)
	{
		digit = 5;
	}

	switch (digit)
	{
	case 1:
		val_max = 10;
		break;
	case 2:
		val_max = 100;
		break;
	case 3:
		val_max = 1000;
		break;
	case 4:
		val_max = 10000;
		break;
	case 5:
		val_max = 100000;
		break;
	}
	
	if (a > val_max)
	{
		a = val_max - 1;
	}

	sprintf(str, "%f", a);

	if (str[digit] == '.')
	{
		x += (Font->Width / 4);
		for (int i = 0; i < digit; i++)
		{
			lcdDisplayChar(lcd, x, y, str[i], Font, color);
			x += Font->Width;
		}
	}
	else
	{
		for (int i = 0; i < digit + 1; i++)
		{
			if (str[i] != '.')
			{
				lcdDisplayChar(lcd, x, y, str[i], Font, color);
				x += Font->Width;
			}
			else
			{
				lcdDisplayChar(lcd, x, y, str[i], Font, color);
				x += (Font->Width / 2);
			}
		}
	}
}

int lcdDrawInteger(LcdIndexType_t lcd, int x, int y, AlignType_t align, int num, uint16_t size, uint16_t color)
{
    //uint8_t flag = 0;
    
    if (num > 999)
    {
        num = 999;
    }
    else if (num < -99)
    {
        num = -99;
    }
    
    if (align == ALIGN_CENTER)
    {
        if (num > 99)
        {
            drawNum(lcd, x - (size * 3 / 2), y, color, size, num / 100);
            drawNum(lcd, x - (size / 2), y, color, size, (num / 10) % 10);
            drawNum(lcd, x + (size / 2), y, color, size, num % 10);
            x += (size * 3 / 2);
        }
        else if (num > 9)
        {
            drawNum(lcd, x - size, y, color, size, num / 10);
            drawNum(lcd, x, y, color, size, num % 10);
            x += (size);
        }
        else if (num > -1)
        {
            drawNum(lcd, x - size / 2, y, color, size, num);
            x += (size / 2);
        }
        else if (num > - 10)
        {
            lcdDrawRectange(lcd, x - size, y + (size / 2), size - 2, size / 5, color);
            drawNum(lcd, x, y, color, size, num % 10);
            x += (size);
        }
        else if (num > -100)
        {
            lcdDrawRectange(lcd, x - (size * 3 / 2), y + (size / 2), size - 2, size / 5, color);
            drawNum(lcd, x - (size / 2), y, color, size, (num / 10) % 10);
            drawNum(lcd, x + (size / 2), y, color, size, num % 10);
            x += (size * 3 / 2);
        }
    }
    else /* 左对齐 */
    {
        if (num < 0)
        {
            /* 绘制负号 */
            //flag = 1;
            
            lcdDrawRectange(lcd, x, y + (size / 2), size - 2, size / 5, color);
            x += size;
            num = -num;
        }
        if (num > 99)
        {
            drawNum(lcd, x, y, color, size, num / 100);
            drawNum(lcd, x + size, y, color, size, (num / 10) % 10);
            drawNum(lcd, x + size * 2, y, color, size, num % 10);
            x += (size * 3);
        }
        else if (num > 9)
        {
            drawNum(lcd, x, y, color, size, num / 10);
            drawNum(lcd, x + size, y, color, size, num % 10);
            x += (size * 2);
        }
        else
        {
            drawNum(lcd, x, y, color, size, num);
            x += size;
        }
    }
    
    return x;
}

int lcdDrawIntegerFont(LcdIndexType_t lcd, int x, int y, int num, sFONT* Font, uint16_t color)
{
    /* 判断正负 */
    if (num < 0)
    {
        /* 绘制负号 */
        lcdDrawRectange(lcd, x, y + Font->Height / 2, Font->Width, 2, color);
        x += (Font->Width);
        
        num = -num;
    }
    
    if (num > 999)
    {
        num = 999;
    }
    
    if (num > 99)
    {
        lcdDisplayChar(lcd, x, y, num / 100 + '0', Font, color);
        lcdDisplayChar(lcd, x + Font->Width, y, (num / 10) % 10 + '0', Font, color);
        lcdDisplayChar(lcd, x + Font->Width * 2, y, num % 10 + '0', Font, color);
        
        x += (Font->Width * 3);
    }
    else if (num > 9)
    {
        lcdDisplayChar(lcd, x, y, num / 10 + '0', Font, color);
        lcdDisplayChar(lcd, x + Font->Width, y, num % 10 + '0', Font, color);
        
        x += (Font->Width * 2);
    }
    else
    {
        lcdDisplayChar(lcd, x, y, num + '0', Font, color);
        
        x += (Font->Width);
    }
    
    return x;
}  

void lcdDrawIcon(LcdIndexType_t lcd, int x, int y, const uint8_t *table, int w, int h, uint16_t color)
{
    uint32_t i, j;
    uint32_t tempx, tempy, width_words;
    
    LCD_SetArea(lcd, x, y, w, h);
    
    if (w % 8)
    {
        width_words = w / 8 + 1;
    }
    else
    {
        width_words = w / 8;
    }
    
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            tempx = j / 8;
            tempy = j % 8;
            if (table[width_words * i + tempx] & (0x80 >> tempy))
            {
                LCD_WR_DATA16(lcd, color);
            }
            else
            {
                LCD_WR_DATA16(lcd, BLACK);
            }
        }
    }
}

int lcdDrawFloat40(LcdIndexType_t lcd, int x, int y, AlignType_t align, int digits, float flt, uint16_t color)
{
    char str[32] = { 0 };
    int val_max = 1;
    
    if (flt < 0)
    {
        flt = 0.0f;
    }

    if (digits > 5)
    {
        digits = 5;
    }

    switch (digits)
    {
    case 1:
        val_max = 9;
        x = 100;
        break;
    case 2:
        val_max = 99;
        x = 80;
        break;
    case 3:
        val_max = 999;
        x = 60;
        break;
    case 4:
        val_max = 999;
        x = 40;
        break;
    case 5:
        val_max = 9999;
        x = 20;
        break;
    }

    if (flt > val_max)
    {
        flt = val_max;
    }

    sprintf(str, "%f", flt);

    if (str[digits] == '.') /* 无小数点情况 */
    {
        for (int i = 0; i < digits; i++)
        {
            drawNum(lcd, x, y, color, 40, str[i] - '0');
            x += 40;
        }
    }
    else /* 有小数点情况 */
    {
        x -= 10; /* 左移留出小数点的位置 */
        
        for (int i = 0; i < digits + 1; i++)
        {
            if (str[i] != '.')
            {
                drawNum(lcd, x, y, color, 40, str[i] - '0');
                x += 40;
            }
            else
            {
                /* 绘制小数点, 方块代替 */
                lcdDrawRectange(lcd, x + 4, y + 48, 10, 10, color);
                x += 20;
            }
        }
    }
    
    return x;
}
