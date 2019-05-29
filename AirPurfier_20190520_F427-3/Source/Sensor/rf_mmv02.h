#ifndef __rf_mmv02_h
#define __rf_mmv02_h

#include "afx.h"

typedef struct
{
    uint16_t raisingTick;
    uint16_t fallingTick;
    uint16_t deltaTick;
} rf_mmv02Struct_t;
    
void rf_mmv02Init(void);

extern rf_mmv02Struct_t rf_mmv02Data;

#endif /* __rf_mmv02_h */

/* end of file */
