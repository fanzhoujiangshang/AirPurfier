#ifndef __lcd_h
#define __lcd_h

#include "afx.h"
#include "fonts.h"

//#define	COLOR				uint16_t		//The variable type of the color (unsigned short) 
//#define	POINT				uint16_t		//The type of coordinate (unsigned short) 
//#define	LENGTH				uint16_t		//The type of coordinate (unsigned short) 

//#define LCD_1IN8
//#if defined(LCD_1IN44)
//	#define LCD_WIDTH  128  //LCD width
//	#define LCD_HEIGHT  128 //LCD height
//	#define LCD_X	2
//	#define LCD_Y	1
//#elif defined(LCD_1IN8)
//	#define LCD_WIDTH  160  //LCD width
//	#define LCD_HEIGHT  128 //LCD height
//	#define LCD_X	 1
//	#define LCD_Y	 1
//#endif

//#define LCD_X_MAXPIXEL  132  //LCD width maximum memory 
//#define LCD_Y_MAXPIXEL  162 //LCD height maximum memory

///********************************************************************************
//function:	
//			scanning method
//********************************************************************************/
//typedef enum{
//	L2R_U2D  = 0,	//The display interface is displayed , left to right, up to down 
//	L2R_D2U  ,
//	R2L_U2D  ,
//	R2L_D2U  ,
//	
//	U2D_L2R  ,
//	U2D_R2L  ,
//	D2U_L2R  ,
//	D2U_R2L  , 
//}LCD_SCAN_DIR;

//#define SCAN_DIR_DFT  L2R_U2D  //Default scan direction = L2R_U2D


///********************************************************************************
//function:	
//	Defines the total number of rows in the display area
//********************************************************************************/

//typedef struct{
//	LENGTH LCD_Dis_Column;	//COLUMN
//	LENGTH LCD_Dis_Page;	//PAGE
//	LCD_SCAN_DIR LCD_Scan_Dir;
//	POINT LCD_X_Adjust;		//LCD x actual display position calibration
//	POINT LCD_Y_Adjust;		//LCD y actual display position calibration
//}LCD_DIS;
//extern LCD_DIS sLCD_DIS;

///********************************************************************************
//function:	
//			dot pixel
//********************************************************************************/
//typedef enum{
//	DOT_PIXEL_1X1  = 1,		// dot pixel 1 x 1
//	DOT_PIXEL_2X2  , 		// dot pixel 2 X 2 
//	DOT_PIXEL_3X3  ,		// dot pixel 3 X 3
//	DOT_PIXEL_4X4  ,		// dot pixel 4 X 4
//	DOT_PIXEL_5X5  , 		// dot pixel 5 X 5
//	DOT_PIXEL_6X6  , 		// dot pixel 6 X 6
//	DOT_PIXEL_7X7  , 		// dot pixel 7 X 7
//	DOT_PIXEL_8X8  , 		// dot pixel 8 X 8
//}DOT_PIXEL;
//#define DOT_PIXEL_DFT  DOT_PIXEL_1X1  //Default dot pilex

///********************************************************************************
//function:	
//			dot Fill style
//********************************************************************************/
//typedef enum{
//	DOT_FILL_AROUND  = 1,		// dot pixel 1 x 1
//	DOT_FILL_RIGHTUP  , 		// dot pixel 2 X 2 
//}DOT_STYLE;
//#define DOT_STYLE_DFT  DOT_FILL_AROUND  //Default dot pilex
///********************************************************************************
//function:	
//			solid line and dotted line
//********************************************************************************/
//typedef enum{
//	LINE_SOLID = 0,
//	LINE_DOTTED,
//}LINE_STYLE;

///********************************************************************************
//function:	
//			DRAW Internal fill
//********************************************************************************/
//typedef enum{
//	DRAW_EMPTY = 0,
//	DRAW_FULL,
//}DRAW_FILL;

///********************************************************************************
//function:	
//			Defines commonly used colors for the display
//********************************************************************************/
//#define LCD_BACKGROUND		WHITE   //Default background color
//#define FONT_BACKGROUND		WHITE   //Default font background color
//#define FONT_FOREGROUND	    GRED    //Default font foreground color

////画笔颜色
//#define WHITE         	 0xFFFF
//#define BLACK         	 0x0000	  
//#define BLUE         	 0x001F  
//#define BRED             0XF81F
//#define GRED 			 0XFFE0
//#define GBLUE			 0X07FF
//#define RED           	 0xF800
//#define MAGENTA       	 0xF81F
//#define GREEN         	 0x07E0
//#define CYAN          	 0x7FFF
//#define YELLOW        	 0xFFE0
//#define BROWN 			 0XBC40 //棕色
//#define BRRED 			 0XFC07 //棕红色
//#define GRAY  			 0X8430 //灰色
////GUI颜色

//#define DARKBLUE      	 0X01CF	//深蓝色
//#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
//#define GRAYBLUE       	 0X5458 //灰蓝色
////以上三色为PANEL的颜色 
// 
//#define LIGHTGREEN     	 0X841F //浅绿色
////#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
//#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

//#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
//#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

void lcdInit(void);
extern void delay_ms(uint16_t ms);

///********************************************************************************
//function:	
//			Macro definition variable name
//********************************************************************************/
//void LCD_Init( LCD_SCAN_DIR Lcd_ScanDir );
//void LCD_SetGramScanWay(LCD_SCAN_DIR Scan_dir);

////LCD set cursor + windows + color
//void LCD_SetWindows( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend );
//void LCD_SetCursor ( POINT Xpoint, POINT Ypoint );
//void LCD_SetColor( COLOR Color ,POINT Xpoint, POINT Ypoint);
//void LCD_SetPointlColor ( POINT Xpoint, POINT Ypoint, COLOR Color );
//void LCD_SetArealColor ( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend,COLOR  Color);
//void LCD_Clear(COLOR  Color);

////Drawing
//void LCD_DrawPoint(POINT Xpoint, POINT Ypoint, COLOR Color, DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_FillWay);
//void LCD_DrawLine ( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel);
//void LCD_DrawRectangle ( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color, DRAW_FILL Filled , DOT_PIXEL Dot_Pixel );
//void LCD_DrawCircle ( POINT X_Center, POINT Y_Center, LENGTH Radius, COLOR Color, DRAW_FILL Draw_Fill , DOT_PIXEL Dot_Pixel );

////Display string
//void LCD_DisplayChar( POINT Xstart, POINT Ystart, const char Acsii_Char, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground );
//void LCD_DisplayString (POINT Xstart, POINT Ystart, const char * pString, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground );
//void LCD_DisplayNum(POINT Xpoint, POINT Ypoint, int32_t Nummber, sFONT* Font, COLOR Color_Background, COLOR Color_Foreground );
//void LCD_Show(void);

#endif /* __lcd_h */

/* end of file */
