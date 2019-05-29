#include "lcd.h"
#include "st7789.h"
#include "time.h"
#include "i2c.h"

//LCD_DIS sLCD_DIS;

void lcdInit(void)
{
		delay_ms(100);
		st7789Init();
}

///********************************************************************************
//function:	Set the display scan and color transfer modes
//parameter: 
//		Scan_dir   :   Scan direction
//		Colorchose :   RGB or GBR color format
//********************************************************************************/
//void LCD_SetGramScanWay(LCD_SCAN_DIR Scan_dir)
//{		
//	//Get the screen scan direction
//	sLCD_DIS.LCD_Scan_Dir = Scan_dir;
//	
//	//Get GRAM and LCD width and height
//	if(Scan_dir == L2R_U2D || Scan_dir == L2R_D2U || Scan_dir == R2L_U2D || Scan_dir == R2L_D2U){
//		sLCD_DIS.LCD_Dis_Column	= LCD_HEIGHT ;
//		sLCD_DIS.LCD_Dis_Page = LCD_WIDTH ;		
//	}else{
//		sLCD_DIS.LCD_Dis_Column	= LCD_WIDTH ;
//		sLCD_DIS.LCD_Dis_Page = LCD_HEIGHT ;	
//	}
//	
//	// Gets the scan direction of GRAM
//	uint16_t MemoryAccessReg_Data=0;  //0x36	
//	switch (Scan_dir){				
//		case L2R_U2D:
//			MemoryAccessReg_Data = 0X00 | 0x00;//x Scan direction | y Scan direction
//			break;
//		case L2R_D2U:
//			MemoryAccessReg_Data = 0x00 | 0x80;//0xC8 | 0X10
//			break;
//		case R2L_U2D://	0X4
//			MemoryAccessReg_Data = 0x40 | 0x00;
//			break;
//		case R2L_D2U://	0XC
//			MemoryAccessReg_Data = 0x40 | 0x80;
//			break;
//		case U2D_L2R://0X2
//			MemoryAccessReg_Data = 0X00 | 0X00 | 0x20;
//			break;
//		case U2D_R2L://0X6
//			MemoryAccessReg_Data = 0x00 | 0X40 | 0x20;
//			break;
//		case D2U_L2R://0XA
//			MemoryAccessReg_Data = 0x80 | 0x00 | 0x20;
//			break;
//		case D2U_R2L://0XE
//			MemoryAccessReg_Data = 0x40 | 0x80 | 0x20;
//			break;
//	}
//	
//	//please set (MemoryAccessReg_Data & 0x10) != 1
//	if((MemoryAccessReg_Data & 0x10) != 1){
//		sLCD_DIS.LCD_X_Adjust = LCD_X;
//		sLCD_DIS.LCD_Y_Adjust = LCD_Y;
//	}else{
//		sLCD_DIS.LCD_X_Adjust = LCD_X;
//		sLCD_DIS.LCD_Y_Adjust = LCD_Y + 2;
//	}
//	
//	// Set the read / write scan direction of the frame memory
//	LCD_WriteReg(0x36); //MX, MY, RGB mode 	
//#if defined(LCD_1IN44)
//	LCD_WriteData_8Bit( MemoryAccessReg_Data | 0x08);	//0x08 set RGB
//#elif defined(LCD_1IN8)
//	LCD_WriteData_8Bit( MemoryAccessReg_Data & 0xf7);	//RGB color filter panel
//#endif
//	
//}

//static void LCD_WriteData_NLen16Bit(uint16_t Data,uint32_t DataLen)
//{
//    uint32_t i ;
//    
//	for(i = 0; i < DataLen; i++){
//		SPI_Write_Byte( (uint8_t)(Data >> 8) );
//		SPI_Write_Byte( (uint8_t)(Data & 0XFF) );
//	}	
//}

///********************************************************************************
//function:	Sets the start position and size of the display area
//parameter: 
//		Xstart 	:   X direction Start coordinates
//		Ystart  :   Y direction Start coordinates
//		Xend    :   X direction end coordinates
//		Yend    :   Y direction end coordinates
//********************************************************************************/
//void LCD_SetWindows( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend )
//{

//	//set the X coordinates
//	LCD_WriteReg ( 0x2A ); 				
//	LCD_WriteData_8Bit ( 0x00 );						//Set the horizontal starting point to the high octet
//	LCD_WriteData_8Bit ( (Xstart & 0xff) + sLCD_DIS.LCD_X_Adjust);			//Set the horizontal starting point to the low octet
//	LCD_WriteData_8Bit ( 0x00 );				//Set the horizontal end to the high octet
//	LCD_WriteData_8Bit ( (( Xend - 1 ) & 0xff) + sLCD_DIS.LCD_X_Adjust);	//Set the horizontal end to the low octet

//	//set the Y coordinates
//	LCD_WriteReg ( 0x2B );
//	LCD_WriteData_8Bit ( 0x00 );
//	LCD_WriteData_8Bit ( (Ystart & 0xff) + sLCD_DIS.LCD_Y_Adjust);
//	LCD_WriteData_8Bit ( 0x00 );
//	LCD_WriteData_8Bit ( ( (Yend - 1) & 0xff )+ sLCD_DIS.LCD_Y_Adjust);
//		
//	LCD_WriteReg(0x2C);	
//	
//}

///********************************************************************************
//function:	Set the display point (Xpoint, Ypoint)
//parameter: 
//		xStart :   X direction Start coordinates
//		xEnd   :   X direction end coordinates
//********************************************************************************/
//void LCD_SetCursor ( POINT Xpoint, POINT Ypoint )
//{
//	LCD_SetWindows ( Xpoint, Ypoint, Xpoint , Ypoint );
//}

///********************************************************************************
//function:	Set show color
//parameter: 
//		Color  :   Set show color
//********************************************************************************/
////static void LCD_SetColor( LENGTH Dis_Width, LENGTH Dis_Height, COLOR Color ){
//void LCD_SetColor( COLOR Color ,POINT Xpoint, POINT Ypoint)
//{		
//	LCD_WriteData_NLen16Bit(Color ,(uint32_t)Xpoint * (uint32_t)Ypoint); 
//}

///********************************************************************************
//function:	Point (Xpoint, Ypoint) Fill the color
//parameter: 
//		Xpoint :   The x coordinate of the point
//		Ypoint :   The y coordinate of the point
//		Color  :   Set the color
//********************************************************************************/
//void LCD_SetPointlColor ( POINT Xpoint, POINT Ypoint, COLOR Color )
//{	
//	if ( ( Xpoint <= sLCD_DIS.LCD_Dis_Column ) && ( Ypoint <= sLCD_DIS.LCD_Dis_Page ) ){		
//		LCD_SetCursor (Xpoint, Ypoint);		
//		LCD_SetColor ( Color , 1 , 1);
//	}
//}

///********************************************************************************
//function:	Fill the area with the color
//parameter: 
//		Xstart :   Start point x coordinate
//		Ystart :   Start point y coordinate
//		Xend   :   End point coordinates
//		Yend   :   End point coordinates
//		Color  :   Set the color
//********************************************************************************/
//void LCD_SetArealColor (POINT Xstart, POINT Ystart, POINT Xend, POINT Yend,	COLOR  Color)
//{	
//	if((Xend > Xstart) && (Yend > Ystart)){			
//		LCD_SetWindows( Xstart , Ystart , Xend , Yend  );
//		LCD_SetColor ( Color ,Xend - Xstart , Yend - Ystart );
//	}
//}

///********************************************************************************
//function:	
//			Clear screen 
//********************************************************************************/
//void LCD_Clear(COLOR  Color)
//{
//	LCD_SetArealColor(0,0, sLCD_DIS.LCD_Dis_Column , sLCD_DIS.LCD_Dis_Page  , Color);	

//}

///********************************************************************************
//function:	Draw Point (Xpoint, Ypoint) Fill the color
//parameter: 
//			Xpoint		:   The x coordinate of the point
//			Ypoint		:   The y coordinate of the point
//			Color		:   Set color
//			Dot_Pixel	:	point size
//********************************************************************************/
//void LCD_DrawPoint(	POINT Xpoint, POINT Ypoint, COLOR Color, 
//					DOT_PIXEL Dot_Pixel, DOT_STYLE DOT_STYLE)
//{							
//	if ( Xpoint > sLCD_DIS.LCD_Dis_Column || Ypoint > sLCD_DIS.LCD_Dis_Page ) {
//		return;
//	}
//	
//	uint16_t XDir_Num ,YDir_Num;
//	if(DOT_STYLE == DOT_FILL_AROUND){
//		for(XDir_Num = 0; XDir_Num < 2 * Dot_Pixel - 1 ; XDir_Num++){
//			for(YDir_Num = 0; YDir_Num < 2 * Dot_Pixel - 1 ; YDir_Num++){
//				LCD_SetPointlColor( Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel, Color);
//			}
//		}
//	}else{
//		for(XDir_Num = 0; XDir_Num <  Dot_Pixel ; XDir_Num++){
//			for(YDir_Num = 0; YDir_Num <  Dot_Pixel ; YDir_Num++){
//				LCD_SetPointlColor( Xpoint + XDir_Num - 1 , Ypoint + YDir_Num -1 , Color);
//			}
//		}
//	}	
//}

///********************************************************************************
//function:	Draw a line of arbitrary slope
//parameter: 
//			Xstart £ºStarting x point coordinates
//			Ystart £ºStarting x point coordinates
//			Xend   £ºEnd point x coordinate
//			Yend   £ºEnd point y coordinate
//			Color  £ºThe color of the line segment
//********************************************************************************/
//void LCD_DrawLine ( POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, 
//					COLOR Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel)
//{
//						
//	if (Xstart > sLCD_DIS.LCD_Dis_Column || Ystart > sLCD_DIS.LCD_Dis_Page || Xend > sLCD_DIS.LCD_Dis_Column || Yend > sLCD_DIS.LCD_Dis_Page) {
//		return;
//	}	
//	
//	POINT Xpoint = Xstart; 
//	POINT Ypoint = Ystart; 
//	int32_t dx = (int32_t)Xend - (int32_t)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
//	int32_t dy = (int32_t)Yend - (int32_t)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;
//	
//	// Increment direction, 1 is positive, -1 is counter;
//	int32_t XAddway = Xstart < Xend ? 1 : -1;
//	int32_t YAddway = Ystart < Yend ? 1 : -1;
//	
//	//Cumulative error
//	int32_t Esp = dx + dy;
//	int8_t Line_Style_Temp = 0;

//	for (;;){
//		Line_Style_Temp++;
//		//Painted dotted line, 2 point is really virtual
//		if(Line_Style == LINE_DOTTED && Line_Style_Temp %3 == 0){
//			LCD_DrawPoint( Xpoint, Ypoint, LCD_BACKGROUND, Dot_Pixel, DOT_STYLE_DFT);
//			Line_Style_Temp = 0;
//		}else{
//			LCD_DrawPoint( Xpoint, Ypoint, Color, Dot_Pixel, DOT_STYLE_DFT);
//		}	
//        if (2 * Esp >= dy) {
//			if (Xpoint == Xend) break;			
//            Esp += dy; 
//			Xpoint += XAddway;
//        }
//        if (2 * Esp <= dx) {
//			if (Ypoint == Yend) break;	
//            Esp += dx; 
//			Ypoint += YAddway;
//        }
//	}
//}   

///********************************************************************************
//function:	Draw a rectangle
//parameter: 
//			Xstart £ºRectangular  Starting x point coordinates
//			Ystart £ºRectangular  Starting x point coordinates
//			Xend   £ºRectangular  End point x coordinate
//			Yend   £ºRectangular  End point y coordinate
//			Color  £ºThe color of the Rectangular segment
//			Filled : Whether it is filled--- 1 solid 0£ºempty
//********************************************************************************/
//void LCD_DrawRectangle ( 	POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, 
//							COLOR Color, DRAW_FILL Filled, DOT_PIXEL Dot_Pixel )
//{
//					
//	if (Xstart > sLCD_DIS.LCD_Dis_Column || Ystart > sLCD_DIS.LCD_Dis_Page || Xend > sLCD_DIS.LCD_Dis_Column || Yend > sLCD_DIS.LCD_Dis_Page) {
//		return;
//	}	
//	
//	if ( Filled ){
//		LCD_SetArealColor( Xstart, Ystart, Xend, Yend, Color);
//	}else{
//		LCD_DrawLine ( Xstart, Ystart, Xend, Ystart, Color , LINE_SOLID, Dot_Pixel);
//		LCD_DrawLine ( Xstart, Ystart, Xstart, Yend, Color , LINE_SOLID, Dot_Pixel);
//		LCD_DrawLine ( Xend, Yend, Xend, Ystart, Color , LINE_SOLID, Dot_Pixel);
//		LCD_DrawLine ( Xend, Yend, Xstart, Yend, Color , LINE_SOLID, Dot_Pixel);		
//	}
//}

///********************************************************************************
//function:	Use the 8-point method to draw a circle of the 
//				specified size at the specified position.
//parameter: 
//			X_Center £ºCenter X coordinate
//			Y_Center £ºCenter Y coordinate
//			Radius   £ºcircle Radius
//			Color  £ºThe color of the £ºcircle segment
//			Filled : Whether it is filled: 1 filling 0£ºDo not
//********************************************************************************/
//void LCD_DrawCircle ( 	POINT X_Center, POINT Y_Center, LENGTH Radius, 
//						COLOR Color, DRAW_FILL  Draw_Fill, DOT_PIXEL Dot_Pixel )
//{
//							
//	if (X_Center > sLCD_DIS.LCD_Dis_Column || Y_Center >= sLCD_DIS.LCD_Dis_Page) {
//		return;
//	}						
//	
//	//Draw a circle from (0, R) as a starting point
//	int16_t XCurrent, YCurrent;
//	XCurrent = 0; 
//	YCurrent = Radius;	
//	
//	//Cumulative error,judge the next point of the logo
//	int16_t Esp = 3 - ( Radius << 1 );
//	
//	int16_t sCountY;
//	if ( Draw_Fill ){
//		while ( XCurrent <= YCurrent ){ //Realistic circles			
//			for ( sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {                      
//				LCD_SetPointlColor ( X_Center + XCurrent, Y_Center + sCountY,   Color );           //1
//				LCD_SetPointlColor ( X_Center - XCurrent, Y_Center + sCountY,   Color );           //2       
//				LCD_SetPointlColor ( X_Center - sCountY,   Y_Center + XCurrent, Color );           //3
//				LCD_SetPointlColor ( X_Center - sCountY,   Y_Center - XCurrent, Color );           //4
//				LCD_SetPointlColor ( X_Center - XCurrent, Y_Center - sCountY,   Color );           //5    
//				LCD_SetPointlColor ( X_Center + XCurrent, Y_Center - sCountY,   Color );           //6
//				LCD_SetPointlColor ( X_Center + sCountY,   Y_Center - XCurrent, Color );           //7 	
//				LCD_SetPointlColor ( X_Center + sCountY,   Y_Center + XCurrent, Color );           //0				
//			}
//			if ( Esp < 0 ) 
//				Esp += 4 * XCurrent + 6;	  
//			else{
//				Esp += 10 + 4 * ( XCurrent - YCurrent );   
//				YCurrent --;
//			}
//			XCurrent ++;
//		}
//	}else{ //Draw a hollow circle  
//		while ( XCurrent <= YCurrent ){ 	
//			LCD_DrawPoint ( X_Center + XCurrent, Y_Center + YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //1
//			LCD_DrawPoint ( X_Center - XCurrent, Y_Center + YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //2      
//			LCD_DrawPoint ( X_Center - YCurrent, Y_Center + XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //3
//			LCD_DrawPoint ( X_Center - YCurrent, Y_Center - XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //4
//			LCD_DrawPoint ( X_Center - XCurrent, Y_Center - YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //5       
//			LCD_DrawPoint ( X_Center + XCurrent, Y_Center - YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //6
//			LCD_DrawPoint ( X_Center + YCurrent, Y_Center - XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //7 
//			LCD_DrawPoint ( X_Center + YCurrent, Y_Center + XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //0
//			
//			if ( Esp < 0 ) 
//				Esp += 4 * XCurrent + 6;	  
//			else{
//				Esp += 10 + 4 * ( XCurrent - YCurrent );   
//				YCurrent --;
//			}
//			XCurrent ++;
//		}
//	}
//}

///********************************************************************************
//function:	Show English characters
//parameter: 
//			Xpoint £ºX coordinate
//			Ypoint £ºY coordinate
//			Acsii_Char   £ºTo display the English characters
//			Font  £ºA structure pointer that displays a character size
//			Color_Background : Select the background color of the English character
//			Color_Foreground : Select the foreground color of the English character
//********************************************************************************/
//void LCD_DisplayChar( 	POINT Xpoint, POINT Ypoint, const char Acsii_Char,
//						sFONT* Font, COLOR Color_Background,	COLOR Color_Foreground )
//{
//	POINT Page, Column;
//	
//	if (Xpoint >= sLCD_DIS.LCD_Dis_Column || Ypoint >= sLCD_DIS.LCD_Dis_Page) {
//		return;
//	}
//	
//	uint32_t Char_Offset = (Acsii_Char - ' ') * Font->Height * (Font->Width / 8 + (Font->Width % 8 ? 1 : 0));
//	const unsigned char* ptr = &Font->table[Char_Offset];

//	for ( Page = 0; Page < Font->Height; Page ++ ){
//		for ( Column = 0; Column < Font->Width; Column ++ ){
//			
//			//To determine whether the font background color and screen background color is consistent
//			if (FONT_BACKGROUND == Color_Background){//this process is to speed up the scan
//				if (*ptr & (0x80 >> (Column % 8)))
//					LCD_SetPointlColor (Xpoint + Column,Ypoint + Page, Color_Foreground );
//			}else{
//				if (*ptr & (0x80 >> (Column % 8))){
//					LCD_SetPointlColor (Xpoint + Column,Ypoint + Page, Color_Foreground );
//				}else{
//					LCD_SetPointlColor (Xpoint + Column,Ypoint + Page, Color_Background );
//				}
//			}
//			//One pixel is 8 bits
//            if (Column % 8 == 7) {
//                ptr++;
//            }	
//		}/* Write a line */
//		if (Font->Width % 8 != 0) {
//				ptr++;
//		}
//	}/* Write all */
//}

///********************************************************************************
//function:	Display the string
//parameter: 
//			Xstart £ºX coordinate
//			Ystart £ºY coordinate
//			pString   £ºThe first address of the English string to be displayed
//			Font  £ºA structure pointer that displays a character size
//			Color_Background : Select the background color of the English character
//			Color_Foreground : Select the foreground color of the English character
//********************************************************************************/
//void LCD_DisplayString (	POINT Xstart, POINT Ystart, const char * pString, 
//							sFONT* Font,COLOR Color_Background, COLOR Color_Foreground )
//{
//	POINT Xpoint = Xstart;
//	POINT Ypoint = Ystart;

//	if (Xstart >= sLCD_DIS.LCD_Dis_Column || Ystart >= sLCD_DIS.LCD_Dis_Page) {
//		return;
//	}
//		
//	while ( * pString != '\0')
//	{
//		//if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the height of the character
//		if ( ( Xpoint + Font->Width ) > sLCD_DIS.LCD_Dis_Column ){
//			Xpoint = Xstart;
//			Ypoint += Font->Height;
//		}
//		
//		// If the Y direction is full, reposition to (Xstart, Ystart)
//		if ( ( Ypoint  + Font->Height ) > sLCD_DIS.LCD_Dis_Page ){
//			Xpoint = Xstart;
//			Ypoint = Ystart;
//		}		
//		LCD_DisplayChar ( Xpoint, Ypoint, * pString, Font, Color_Background, Color_Foreground );
//		
//		//The next character of the address
//		pString ++;
//		
//		//The next word of the abscissa increases the font of the broadband
//		Xpoint += Font->Width;	
//	}
//}
//							
///********************************************************************************
//function:	Display the string
//parameter: 
//			Xstart £ºX coordinate
//			Ystart : Y coordinate
//			Nummber: The number displayed
//			Font  £ºA structure pointer that displays a character size
//			Color_Background : Select the background color of the English character
//			Color_Foreground : Select the foreground color of the English character
//********************************************************************************/
//#define  ARRAY_LEN 255
//void LCD_DisplayNum(	POINT Xpoint, POINT Ypoint, int32_t Nummber, 
//						sFONT* Font,COLOR Color_Background, COLOR Color_Foreground )
//{
//		
//	int16_t Num_Bit = 0, Str_Bit = 0;
//	uint8_t Str_Array[ARRAY_LEN] = {0},Num_Array[ARRAY_LEN] = {0};
//	uint8_t *pStr = Str_Array;
//	
//	if (Xpoint >= sLCD_DIS.LCD_Dis_Column || Ypoint >= sLCD_DIS.LCD_Dis_Page) {
//		return;
//	}
//	
//	//Converts a number to a string
//	while(Nummber){
//		Num_Array[Num_Bit] = Nummber % 10 + '0';
//		Num_Bit++;
//		Nummber /= 10;
//    }
//	
//	//The string is inverted
//	while( Num_Bit > 0){
//		Str_Array[Str_Bit] = Num_Array[Num_Bit -1];
//		Str_Bit ++;
//		Num_Bit --;
//	}
//	
//	//show
//	LCD_DisplayString( Xpoint, Ypoint,  (const char*)pStr, Font, Color_Background, Color_Foreground );
//}


//void LCD_Show(void)
//{
//	if(sLCD_DIS.LCD_Dis_Column <= sLCD_DIS.LCD_Dis_Page){//Horizontal screen display

//		// printf("LCD Draw Line \r\n");
//		LCD_DrawLine(0, 10, sLCD_DIS.LCD_Dis_Column, 10, RED,LINE_SOLID, DOT_PIXEL_2X2);
//		LCD_DrawLine(0, sLCD_DIS.LCD_Dis_Page - 10, sLCD_DIS.LCD_Dis_Column, sLCD_DIS.LCD_Dis_Page - 10, RED,LINE_SOLID, DOT_PIXEL_2X2);	
//		LCD_DrawLine(0, 20, sLCD_DIS.LCD_Dis_Column, 20, RED,LINE_DOTTED, DOT_PIXEL_DFT);
//		LCD_DrawLine(0, sLCD_DIS.LCD_Dis_Page - 20, sLCD_DIS.LCD_Dis_Column, sLCD_DIS.LCD_Dis_Page - 20, RED,LINE_DOTTED, DOT_PIXEL_DFT);

//		// printf("LCD Draw Rectangle \r\n");
//		LCD_DrawRectangle(0,0,sLCD_DIS.LCD_Dis_Column,8,BLUE, DRAW_FULL, DOT_PIXEL_1X1);
//		LCD_DrawRectangle(0,sLCD_DIS.LCD_Dis_Page - 10,sLCD_DIS.LCD_Dis_Column,sLCD_DIS.LCD_Dis_Page,BLUE, DRAW_FULL, DOT_PIXEL_1X1);
//		LCD_DrawRectangle(1,1,sLCD_DIS.LCD_Dis_Column,sLCD_DIS.LCD_Dis_Page,RED,DRAW_EMPTY,DOT_PIXEL_2X2);
//		
//		// printf("LCD Draw Olympic Rings\r\n");
//		uint16_t Cx1 = 40, Cy1 = 85, Cr = 12;
//		uint16_t Cx2 = Cx1 + (2.5 * Cr), Cy2 = Cy1;
//		uint16_t Cx3 = Cx1 + (5 * Cr), Cy3 = Cy1;
//		uint16_t Cx4 = ( Cx1 + Cx2 )/2, Cy4 = Cy1 + Cr;
//		uint16_t Cx5 = ( Cx2 + Cx3 )/2, Cy5 = Cy1 + Cr;

//		LCD_DrawCircle( Cx1, Cy1, Cr, BLUE, DRAW_EMPTY, DOT_PIXEL_DFT);
//		LCD_DrawCircle( Cx2, Cy2, Cr, BLACK, DRAW_EMPTY, DOT_PIXEL_DFT);
//		LCD_DrawCircle( Cx3, Cy3, Cr, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
//		LCD_DrawCircle( Cx4, Cy4, Cr, YELLOW, DRAW_EMPTY, DOT_PIXEL_DFT);
//		LCD_DrawCircle( Cx5, Cy5, Cr, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);

//		// printf("LCD Draw Realistic circles\r\n");
//		LCD_DrawCircle(15, 110, 10, BRRED, DRAW_FULL, DOT_PIXEL_DFT);
//		LCD_DrawCircle(sLCD_DIS.LCD_Dis_Column - 15, 110, 10, BRRED, DRAW_FULL, DOT_PIXEL_DFT);

//		// printf("LCD Display String \r\n");
//		LCD_DisplayString(35,20,"AQI:100",&Font12,LCD_BACKGROUND,BLUE);
//		LCD_DisplayString(32,33,"PM2.5:99",&Font12,LCD_BACKGROUND,BLUE);
//		LCD_DisplayString(28,45,"VOC:888",&Font8,RED,GRED);

//		// printf("LCD Display Nummber \r\n");
//		LCD_DisplayNum(28,55,1234567890,&Font12,LCD_BACKGROUND,BLUE);
//	
//	}else{//Vertical screen display	

//		// printf("LCD Draw Line \r\n");
//		LCD_DrawLine(0, 10, sLCD_DIS.LCD_Dis_Column, 10, RED,LINE_SOLID, DOT_PIXEL_2X2);
//		LCD_DrawLine(0, sLCD_DIS.LCD_Dis_Page - 10, sLCD_DIS.LCD_Dis_Column, sLCD_DIS.LCD_Dis_Page - 10, RED,LINE_SOLID, DOT_PIXEL_2X2);	
//		LCD_DrawLine(0, 20, sLCD_DIS.LCD_Dis_Column, 20, RED,LINE_DOTTED, DOT_PIXEL_DFT);
//		LCD_DrawLine(0, sLCD_DIS.LCD_Dis_Page - 20, sLCD_DIS.LCD_Dis_Column, sLCD_DIS.LCD_Dis_Page - 20, RED,LINE_DOTTED, DOT_PIXEL_DFT);

//		// printf("LCD Draw Rectangle \r\n");
//		LCD_DrawRectangle(0,0,sLCD_DIS.LCD_Dis_Column,8,BLUE, DRAW_FULL, DOT_PIXEL_1X1);
//		LCD_DrawRectangle(0,sLCD_DIS.LCD_Dis_Page - 10,sLCD_DIS.LCD_Dis_Column,sLCD_DIS.LCD_Dis_Page,BLUE, DRAW_FULL, DOT_PIXEL_1X1);
//		LCD_DrawRectangle(1,1,sLCD_DIS.LCD_Dis_Column,sLCD_DIS.LCD_Dis_Page,RED,DRAW_EMPTY,DOT_PIXEL_2X2);
//		
//		// printf("LCD Draw Olympic Rings\r\n");
//		uint16_t Cx1 = 45, Cy1 = 80, Cr = 12;
//		uint16_t Cx2 = Cx1 + (2.5 * Cr), Cy2 = Cy1;
//		uint16_t Cx3 = Cx1 + (5 * Cr), Cy3 = Cy1;
//		uint16_t Cx4 = ( Cx1 + Cx2 )/2, Cy4 = Cy1 + Cr;
//		uint16_t Cx5 = ( Cx2 + Cx3 )/2, Cy5 = Cy1 + Cr;

//		LCD_DrawCircle( Cx1, Cy1, Cr, BLUE, DRAW_EMPTY, DOT_PIXEL_DFT);
//		LCD_DrawCircle( Cx2, Cy2, Cr, BLACK, DRAW_EMPTY, DOT_PIXEL_DFT);
//		LCD_DrawCircle( Cx3, Cy3, Cr, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
//		LCD_DrawCircle( Cx4, Cy4, Cr, YELLOW, DRAW_EMPTY, DOT_PIXEL_DFT);
//		LCD_DrawCircle( Cx5, Cy5, Cr, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);

//		// printf("LCD Draw Realistic circles\r\n");
//		LCD_DrawCircle(15, 90, 10, BRRED, DRAW_FULL, DOT_PIXEL_DFT);
//		LCD_DrawCircle(sLCD_DIS.LCD_Dis_Column - 15, 90, 10, BRRED, DRAW_FULL, DOT_PIXEL_DFT);

//		// printf("LCD Display String \r\n");
//		LCD_DisplayString(10,20,"WaveShare Electronic",&Font12,LCD_BACKGROUND,BLUE);
//		LCD_DisplayString(35,35,"1.8inch TFTLCD",&Font12,RED,GRED);

//		// printf("LCD Display Nummber \r\n");
//		LCD_DisplayNum(35,50,1234567890,&Font12,LCD_BACKGROUND,BLUE);

//	}
//}
