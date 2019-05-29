#ifndef __touch_h
#define __touch_h

#include "afx.h"

#define CTP_SLAVE_ADDR	    0x70

//Controller parameter getting/setting flag
#define CTP_RESOLUTION 0x1
#define CTP_THRESHOLD 0x2
#define CTP_IDLE_INTERVAL 0x4
#define CTP_SLEEP_INTERVAL 0x8
//#define CTP_DATA_MODE 0x10
//#define CTP_GESTURE_DISTANCE 0x20
//#define CTP_CHANGE_STATE_DELAY 0x40
//#define CTP_CALIBRATION 0x80

//Controller Mode
#define CTP_NORMAL_OPERATION 0x0B
#define CTP_SYSTEM_INFORMATION 0x1B
#define CTP_ACTIVE_MODE 0x4B


#define CTP_IDLE_MODE 0x8
#define CTP_SLEEP_MODE 0x10
#define CTP_DEBUG_MODE 0x1B

#define CTP_GESTURE_DETECTION_MODE 0x40
#define CTP_MULTIPLE_POINT_MODE 0x80



//#define CTP_SLAVE_ADDR		0xCE

//ADDRESS
#define HST_MODE_ADDR 0x0  
//DATA 
#define HST_MODE_NORMAL 0x1B   
#define HST_MODE_SYSTEM_INFORMATION 0x1B
#define HST_MODE_TEST  0X4B

#define GEST_ID_ADDR 0x1  
#define GEST_ID_NUMBER 0xFF  

#define TD_STAT_ADDR 0x2
#define TD_STAT_NUMBER_TOUCH 0x07
#define TT_MODE_BUFFER_INVALID 0x08//1-5 VALIDE

/*
#define TT_MODE_ADDR 0x1
#define TT_MODE_BUFFER_INVALID 0x20

#define TT_STAT_ADDR 0x2
#define TT_STAT_NUMBER_TOUCH 0xF
*/
#define TOUCH1_XH_ADDR 0x03
#define TOUCH1_EVEN_FLAG 0xC0
#define TOUCH1_XL_ADDR 0x4
#define TOUCH1_YH_ADDR 0x5
#define TOUCH1_ID 0xF0
#define TOUCH1_YL_ADDR 0x6


//#define TOUCH1_Z_ADDR  0x7

#define TOUCH2_XH_ADDR 0x09
#define TOUCH2_EVEN_FLAG 0xC0
#define TOUCH2_XL_ADDR 0xA
#define TOUCH2_YH_ADDR 0xB
#define TOUCH2_ID 0xF0
#define TOUCH2_YL_ADDR 0xC
//#define TOUCH2_Z_ADDR  0xD

#define TOUCH3_XH_ADDR 0x0F
#define TOUCH3_EVEN_FLAG 0xC0
#define TOUCH3_XL_ADDR 0x10
#define TOUCH3_YH_ADDR 0x11
#define TOUCH3_ID 0xF0
#define TOUCH3_YL_ADDR 0x12
//#define TOUCH3_Z_ADDR  0x14

#define TOUCH4_XH_ADDR 0x15
#define TOUCH4_EVEN_FLAG 0xC0
#define TOUCH4_XL_ADDR 0x16
#define TOUCH4_YH_ADDR 0x17
#define TOUCH4_ID 0xF0
#define TOUCH4_YL_ADDR 0x18
//#define TOUCH4_Z_ADDR  0x1A

#define TOUCH5_XH_ADDR 0x1B
#define TOUCH5_EVEN_FLAG 0xC0
#define TOUCH5_XL_ADDR 0x1C
#define TOUCH5_YH_ADDR 0x1D
#define TOUCH5_ID 0xF0
#define TOUCH5_YL_ADDR 0x1E

#define CTP_BL_FILE          0
#define CTP_BL_CMD           0xFF
#define CTP_BL_EXIT          0xA5
#define CTP_BL_SECUTITY_KEY1 0x0
#define CTP_BL_SECUTITY_KEY2 0x1
#define CTP_BL_SECUTITY_KEY3 0x2
#define CTP_BL_SECUTITY_KEY4 0x3
#define CTP_BL_SECUTITY_KEY5 0x4
#define CTP_BL_SECUTITY_KEY6 0x5
#define CTP_BL_SECUTITY_KEY7 0x6
#define CTP_BL_SECUTITY_KEY8 0x7
#define ACT_INTRVL_ADDR  0x1D

typedef enum
{
    touchEvent_None = 0,
    touchEvent_Middle = 1,
    touchEvent_Left = 2,
    touchEvent_Right = 3,
    touchEvent_MiddleLong = 4,
    touchEvent_End
} touchEvent_t;

typedef struct
{
    touchEvent_t leftEvent;
    touchEvent_t rightEvent;
    uint8_t pointCount;
    uint8_t err;
    uint16_t x;
    uint16_t y;
} touchStruct_t;

void touchInit(void);
void touchRead(void);
void touchHandle(void);

extern touchStruct_t touchData;

extern u8 temp_data[8];
extern u16 x_position,y_position;
extern u8 Reg_Addr;

#endif /* __touch_h */

/* end of file */
