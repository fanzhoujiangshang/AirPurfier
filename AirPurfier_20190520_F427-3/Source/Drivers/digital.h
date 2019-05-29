#ifndef __digital_h
#define __digital_h

#include "afx.h"

typedef uint32_t digitalPin;

#define digitalHi(p)        *p = 1
#define digitalLo(p)        *p = 0
#define digitalSet(p, n)    *p = n
#define digitalGet(p)       (*p)
#define digitalTogg(p)      *p = !(*p)

extern uint32_t *digitalInit(GPIO_TypeDef* port, const uint16_t pin, uint8_t initial);

#endif /* __digital_h */

/* end of file */
