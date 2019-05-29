#ifndef __spi_h
#define __spi_h

#include "stm32f4xx.h"

//#define LCD_DC1_PIN     GPIO_Pin_7
//#define LCD_CLK1_PIN    GPIO_Pin_5
//#define LCD_SDA1_PIN    GPIO_Pin_6
//#define LCD_CS1_PIN    GPIO_Pin_4

#define LCD_DC1_PIN     GPIO_Pin_6
#define LCD_CLK1_PIN    GPIO_Pin_5
#define LCD_SDA1_PIN    GPIO_Pin_7
#define LCD_CS1_PIN    GPIO_Pin_4

//#define LCD_DC2_PIN     GPIO_Pin_15
//#define LCD_CLK2_PIN    GPIO_Pin_13
//#define LCD_SDA2_PIN    GPIO_Pin_14
//#define LCD_CS2_PIN    GPIO_Pin_12

#define LCD_DC2_PIN     GPIO_Pin_5
#define LCD_CLK2_PIN    GPIO_Pin_2
#define LCD_SDA2_PIN   	GPIO_Pin_6
#define LCD_CS2_PIN   	GPIO_Pin_4



//#define LCD_DC1_PIN     GPIO_Pin_7
//#define LCD_CLK1_PIN    GPIO_Pin_5
//#define LCD_SDA1_PIN    GPIO_Pin_6
//#define LCD_CS1_PIN    	GPIO_Pin_4

//#define LCD_DC2_PIN     GPIO_Pin_15
//#define LCD_CLK2_PIN    GPIO_Pin_13
//#define LCD_SDA2_PIN   	GPIO_Pin_14
//#define LCD_CS2_PIN   	GPIO_Pin_12

void spiInit(void);
void spi2Init(void);
void SPI_Write_Byte(uint8_t data);

#endif /* __spi_h */

/* end of file */
