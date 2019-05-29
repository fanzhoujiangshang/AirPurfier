#ifndef __font_h
#define __font_h

#include "stdint.h"

/* Max size of bitmap will based on a font24 (17x24) */
#define MAX_HEIGHT_FONT         24
#define MAX_WIDTH_FONT          17
#define OFFSET_BITMAP           54

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct _tFont
{    
    const uint8_t *table;
    uint16_t Width;
    uint16_t Height;
} sFONT;

// ------------------  汉字字模的数据结构定义 ------------------------ //
extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;

extern const uint8_t Font40Num_Table[];
extern const uint8_t Font35Num_Table[];
extern const uint8_t Font24Num_Table[];
extern const uint8_t Font20Num_Table[];
extern const uint8_t PowerIcon_Table[];
extern const uint8_t SleepIcon_Table[];
extern const uint8_t GB_16[];
extern const uint8_t ugm3[];

#ifdef __cplusplus
}
#endif

#endif /* __font_h */
