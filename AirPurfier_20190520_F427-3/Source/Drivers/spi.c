#include "spi.h"

void spiInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1|RCC_APB2Periph_SPI4, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2); 
 
//	//这里只针对SPI口初始化
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,DISABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
    
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
    
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1); //PB3复用为 SPI1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1); //PB5复用为 SPI1
 
	//这里只针对SPI口初始化
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);//复位SPI1
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//停止复位SPI1
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
    
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//??SPI???????????:SPI??????????
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;//??SPI????:????SPI
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;//??SPI?????:SPI????8????
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;//??????????:?????
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;//???????????
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//NSS?????(NSS??)????(??SSI?)??:??NSS???SSI???
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;//??????????:????????256
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//???????MSB???LSB???:?????MSB???
	SPI_InitStructure.SPI_CRCPolynomial=7;//CRC???????
	SPI_Init(SPI2,&SPI_InitStructure);//??SPI_InitStruct???????????SPIx???
    
	SPI_Cmd(SPI2,ENABLE);//??SPI??
    
	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//??SPI???????????:SPI??????????
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;//??SPI????:????SPI
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;//??SPI?????:SPI????8????
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;//??????????:?????
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;//???????????
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//NSS?????(NSS??)????(??SSI?)??:??NSS???SSI???
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;//??????????:????????256
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//???????MSB???LSB???:?????MSB???
	SPI_InitStructure.SPI_CRCPolynomial=7;//CRC???????
	SPI_Init(SPI1,&SPI_InitStructure);//??SPI_InitStruct???????????SPIx???
    
	SPI_Cmd(SPI1,ENABLE);//??SPI??
	
	
//SPI4 初始化

//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
////	
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource2,GPIO_AF_SPI4); 
//	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_SPI4); 
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	GPIO_SetBits(GPIOE,GPIO_Pin_4);
//    
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
//    
//	GPIO_SetBits(GPIOE,GPIO_Pin_5);
//	
//	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//??SPI???????????:SPI??????????
//	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;//??SPI????:????SPI
//	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;//??SPI?????:SPI????8????
//	SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;//??????????:?????
//	SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;//???????????
//	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;//NSS?????(NSS??)????(??SSI?)??:??NSS???SSI???
//	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;//??????????:????????256
//	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;//???????MSB???LSB???:?????MSB???
//	SPI_InitStructure.SPI_CRCPolynomial=7;//CRC???????
//	SPI_Init(SPI4,&SPI_InitStructure);//??SPI_InitStruct???????????SPIx???
//    
//	SPI_Cmd(SPI4,ENABLE);//??SPI??

}

void spi2Init()
{
		GPIO_InitTypeDef GPIO_InitStructure;
	  SPI_InitTypeDef SPI_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);  //????
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);  //??
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //?????
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);  //?????????
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
			    
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //?????
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   //??????
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //????8
    SPI_InitStructure.SPI_CPOL  = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //????NSS??
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2,&SPI_InitStructure);
    SPI_Cmd(SPI2,ENABLE);
}


/* end of file */
