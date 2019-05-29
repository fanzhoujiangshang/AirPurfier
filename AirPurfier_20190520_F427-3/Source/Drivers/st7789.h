#ifndef __st7789_h
#define __st7789_h

#include "stm32f4xx.h"
#include "spi.h"
#include "fonts.h"

#define WIDTH   240
#define HEIGHT  204

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#define LCD1_CS_0		(GPIOA->BSRRH = LCD_CS1_PIN)
#define LCD1_CS_1		(GPIOA->BSRRL = LCD_CS1_PIN)

#define LCD1_DC_0		(GPIOA->BSRRH = LCD_DC1_PIN)
#define LCD1_DC_1		(GPIOA->BSRRL = LCD_DC1_PIN)

#define LCD1_SCK_0		(GPIOA->BSRRH = LCD_CLK1_PIN)
#define LCD1_SCK_1		(GPIOA->BSRRL = LCD_CLK1_PIN)

#define LCD1_SDA_0		(GPIOA->BSRRH = LCD_SDA1_PIN)
#define LCD1_SDA_1		(GPIOA->BSRRL = LCD_SDA1_PIN)

#define LCD2_CS_0		(GPIOE->BSRRH = LCD_CS2_PIN)
#define LCD2_CS_1		(GPIOE->BSRRL = LCD_CS2_PIN)

#define LCD2_DC_0		(GPIOE->BSRRH = LCD_DC2_PIN)
#define LCD2_DC_1		(GPIOE->BSRRL = LCD_DC2_PIN)

#define LCD2_SCK_0		(GPIOE->BSRRH = LCD_CLK2_PIN)
#define LCD2_SCK_1		(GPIOE->BSRRL = LCD_CLK2_PIN)

#define LCD2_SDA_0		(GPIOE->BSRRH = LCD_SDA2_PIN)
#define LCD2_SDA_1		(GPIOE->BSRRL = LCD_SDA2_PIN)


#define LCD_RST_0       (GPIOD->BSRRH = GPIO_Pin_8)
#define LCD_RST_1       (GPIOD->BSRRL = GPIO_Pin_8)

//#ifndef USE_TB
//#define LCD_RST_0       (GPIOD->BSRRH = GPIO_Pin_8)
//#define LCD_RST_1       (GPIOD->BSRRL = GPIO_Pin_8)
//#else
//#define LCD_RST_0       (GPIOB->BRR = GPIO_Pin_8)
//#define LCD_RST_1       (GPIOB->BSRR = GPIO_Pin_8)
//#endif

#define LCD_BL_0		(GPIOB->BSRRH = GPIO_Pin_7)
#define LCD_BL_1		(GPIOB->BSRRL = GPIO_Pin_7)

#define LCD2_BL_0		(GPIOB->BSRRH = GPIO_Pin_6)
#define LCD2_BL_1		(GPIOB->BSRRL = GPIO_Pin_6)
typedef enum
{
    ALIGN_LEFT = 0,
    ALIGN_CENTER = 1
} AlignType_t;

typedef enum
{
    LCD1 = 0,
    LCD2 = 1
} LcdIndexType_t;

void LCD_Clear(LcdIndexType_t lcd, uint16_t color);
void LCD_Default(LcdIndexType_t lcd);

void st7789Init(void);
void st7789Reset(void);
void st7789LowLevelInit(LcdIndexType_t lcd);

void LCD_WR_REG(LcdIndexType_t lcd, uint32_t cmd);

void drawNum(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, uint32_t font, uint32_t num);
void drawIcon(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, uint32_t index, uint8_t transparent);
void LCD_DrawKanji(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, uint32_t font, uint32_t index);
void drawKanjiFromTable(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t color, const uint8_t *table, uint8_t index);
void lcdDrawRectange(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
void lcdDrawRectangeDefault(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void lcdDisplayChar(LcdIndexType_t lcd, uint32_t x, uint32_t y, const char c, sFONT* Font, uint16_t color);
void lcdPrintFloat(LcdIndexType_t lcd, uint32_t x, uint32_t y, uint16_t color, sFONT* Font, float a, int digit);
int lcdDrawInteger(LcdIndexType_t lcd, int x, int y, AlignType_t align, int num, uint16_t size, uint16_t color);
int lcdDrawIntegerFont(LcdIndexType_t lcd, int x, int y, int num, sFONT* Font, uint16_t color);
void lcdDrawIcon(LcdIndexType_t lcd, int x, int y, const uint8_t *table, int w, int h, uint16_t color);
int lcdDrawFloat40(LcdIndexType_t lcd, int x, int y, AlignType_t align, int digits, float flt, uint16_t color);

typedef struct
{
	u8 temp_data[8];
	u16 x_position;
	u16 y_position;
	u8 Reg_Addr;
	u8 status_up;
	u8 status_down;
	u8 status_press;
	u32 press_times;

}TF1touchStruct_t;

extern TF1touchStruct_t TF1touchdata,TF2touchdata;

extern const uint8_t POWER_ON_OFF[];
#endif /* __st7789_h */

/* end of file */	



