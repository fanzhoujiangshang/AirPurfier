#ifndef __ui_h
#define __ui_h

#include "afx.h"

typedef enum {
    UI_LEFT_POWER_OFF = 0,
    UI_LEFT_POWER_ON = 1,
    UI_LEFT_AUTO = 2,
    UI_LEFT_AIR_SPEED = 3,
    UI_LEFT_TIMING = 4,
    UI_LEFT_SLEEP = 5,
		UI_LEFT_AQI = 6,
    UI_LEFT_PM25 = 7,
    UI_LEFT_METHANAL = 8,
    UI_LEFT_VOC = 9,
    UI_LEFT_HUMIDITY = 10,
    UI_LEFT_FILTER = 11,
		UI_LEFT_STANDBY = 12,
    UI_LEFT_END
} uiLeftMode_t;

typedef enum {
    UI_RIGHT_POWER_OFF = 0,
    UI_RIGHT_AQI = 1,
    UI_RIGHT_PM25 = 2,
    UI_RIGHT_METHANAL = 3,
    UI_RIGHT_VOC = 4,
    UI_RIGHT_HUMIDITY = 5,
    UI_RIGHT_FILTER = 6,
    UI_RIGHT_END
} uiRightMode_t;

typedef struct
{
    uiLeftMode_t leftMode;
    uiRightMode_t rightMode;
    
    uint8_t warnModeRun;
    uint8_t leftDisplay;
    uint8_t rightDisplay;
    
    uint8_t leftUpdateReq;
    
} uiStruct_t;

void uiInit(void);

extern uiStruct_t uiData;

extern int test_percent;

extern void leftLcdChange(uiLeftMode_t mode);
extern void rightLcdChange(uiRightMode_t mode);
extern uint8_t rightLast;
extern uint8_t leftLast;



#endif /* __ui_h */

