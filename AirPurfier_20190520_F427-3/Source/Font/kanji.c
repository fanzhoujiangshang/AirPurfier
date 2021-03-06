#include "fonts.h"

const uint8_t GB_16[] =          // 数据表
{
//"合",0 
    0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,
      0x08,0x20,0x10,0x10,0x2F,0xEE,0xC0,0x04,
      0x00,0x10,0x1F,0xF8,0x10,0x10,0x10,0x10,
      0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,

//"格",1
    0x11,0x00,0x11,0x00,0x11,0xF8,0x12,0x08,
      0xFF,0x10,0x14,0xA0,0x38,0x40,0x34,0xA0,
      0x51,0x10,0x52,0x0E,0x97,0xFC,0x1A,0x08,
      0x12,0x08,0x12,0x08,0x13,0xF8,0x12,0x08,

//"良",2 
    0x02,0x00,0x01,0x10,0x3F,0xF8,0x20,0x10,
      0x20,0x10,0x3F,0xF0,0x20,0x10,0x20,0x10,
      0x3F,0xF8,0x24,0x10,0x24,0x20,0x22,0x40,
      0x21,0x80,0x28,0x60,0x30,0x1C,0x20,0x08,

//"好",3 
    0x10,0x00,0x11,0xFC,0x10,0x04,0x10,0x08,
      0xFC,0x10,0x24,0x20,0x24,0x24,0x27,0xFE,
      0x24,0x20,0x44,0x20,0x28,0x20,0x10,0x20,
      0x28,0x20,0x44,0x20,0x84,0xA0,0x00,0x40,

//"超",4 
0x10,0x08,0x13,0xFC,0x10,0x88,0x7C,0x88,
      0x10,0x88,0x10,0xA8,0xFD,0x10,0x12,0x00,
      0x51,0xF8,0x5D,0x08,0x51,0x08,0x51,0x08,
      0x71,0xF8,0x48,0x06,0x87,0xFC,0x00,0x00,

//"标",5 
0x10,0x00,0x10,0x10,0x13,0xF8,0x10,0x00,
      0xFC,0x00,0x10,0x04,0x37,0xFE,0x38,0x40,
      0x54,0x40,0x51,0x50,0x91,0x48,0x12,0x4C,
      0x14,0x44,0x10,0x40,0x11,0x40,0x10,0x80,

//"严",6 
0x00,0x08,0x7F,0xFC,0x02,0x40,0x12,0x48,
      0x0A,0x50,0x02,0x44,0x3F,0xFE,0x20,0x00,
      0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,
      0x20,0x00,0x20,0x00,0x40,0x00,0x80,0x00,

//"重",7 
0x00,0x38,0x3F,0xC0,0x01,0x04,0xFF,0xFE,
      0x01,0x10,0x1F,0xF8,0x11,0x10,0x1F,0xF0,
      0x11,0x10,0x1F,0xF0,0x01,0x00,0x3F,0xF8,
      0x01,0x00,0x01,0x04,0xFF,0xFE,0x00,0x00,

//优   8
0x10,0x80,0x10,0xA0,0x10,0x90,0x20,0x90,
      0x20,0x84,0x7F,0xFE,0xA1,0x40,0x21,0x40,
      0x21,0x40,0x22,0x40,0x22,0x40,0x22,0x40,
      0x24,0x42,0x24,0x42,0x28,0x3E,0x30,0x00,

//"中",9
0x01,0x00,0x01,0x00,0x01,0x04,0x7F,0xFE,
      0x41,0x04,0x41,0x04,0x41,0x04,0x41,0x04,
      0x7F,0xFC,0x41,0x04,0x01,0x00,0x01,0x00,
      0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
	
//差   10
 0x08,0x20,0x04,0x48,0x7F,0xFC,0x01,0x00,
      0x01,0x10,0x3F,0xF8,0x01,0x00,0x02,0x04,
      0xFF,0xFE,0x04,0x00,0x08,0x20,0x17,0xF0,
      0x20,0x80,0x40,0x80,0x80,0x88,0x1F,0xFC,
	  
//甲   11
 0x00,0x08,0x3F,0xFC,0x21,0x08,0x21,0x08,
      0x21,0x08,0x3F,0xF8,0x21,0x08,0x21,0x08,
      0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x00,
      0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,

//醛  12
0x04,0x88,0xFE,0x88,0x2B,0xFE,0x28,0x88,
      0xFE,0x20,0xAA,0x50,0xAA,0x8E,0xAB,0x04,
      0xC6,0xF8,0x82,0x20,0xFE,0x20,0x82,0xF8,
      0x82,0x20,0xFE,0x24,0x83,0xFE,0x00,0x00,
//湿  13
0x00,0x08,0x47,0xFC,0x34,0x08,0x14,0x08,
      0x87,0xF8,0x64,0x08,0x24,0x08,0x0F,0xF8,
      0x11,0x20,0x21,0x20,0xE9,0x24,0x25,0x28,
      0x23,0x30,0x21,0x24,0x3F,0xFE,0x20,0x00,
//温  14
0x00,0x08,0x43,0xFC,0x32,0x08,0x12,0x08,
      0x83,0xF8,0x62,0x08,0x22,0x08,0x0B,0xF8,
      0x10,0x00,0x27,0xFC,0xE4,0xA4,0x24,0xA4,
      0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x20,0x00,

//度  15
0x01,0x00,0x00,0x84,0x3F,0xFE,0x22,0x20,
      0x22,0x28,0x3F,0xFC,0x22,0x20,0x23,0xE0,
      0x20,0x00,0x2F,0xF0,0x22,0x20,0x21,0x40,
      0x20,0x80,0x43,0x60,0x8C,0x1E,0x30,0x04,
//颗  16
 0x00,0x04,0x7F,0xFE,0x54,0x40,0x54,0x84,
      0x7D,0xFE,0x55,0x04,0x55,0x24,0x7D,0x24,
      0x11,0x24,0xFF,0x24,0x31,0x24,0x39,0x24,
      0x55,0x24,0x54,0x50,0x90,0x8C,0x13,0x04,

//粒  17
0x10,0x80,0x10,0x40,0x10,0x40,0x54,0x08,
      0x3B,0xFC,0x10,0x00,0xFD,0x08,0x11,0x08,
      0x38,0x90,0x34,0x90,0x54,0x90,0x90,0xA0,
      0x10,0xA0,0x10,0x24,0x17,0xFE,0x10,0x00,
	  
//滤  18
0x00,0x90,0x40,0xF8,0x20,0x80,0x2F,0xFE,
      0x08,0x82,0x88,0xF4,0x5F,0x80,0x48,0x88,
      0x18,0x78,0x28,0x00,0xC9,0x40,0x4B,0x24,
      0x4D,0x2A,0x51,0x0A,0x50,0xF8,0x60,0x00,

//网  19
0x00,0x04,0x7F,0xFE,0x40,0x04,0x42,0x0C,
      0x62,0x8C,0x54,0x54,0x54,0x54,0x48,0x24,
      0x48,0x24,0x54,0x54,0x52,0x4C,0x62,0x8C,
      0x61,0x04,0x42,0x04,0x40,0x14,0x40,0x08

};

