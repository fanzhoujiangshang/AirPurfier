#ifndef __AFC_MATH_H
#define __AFC_MATH_H

#include "stm32f4xx.h"

#define constrain(v, lo, hi)			(((v) < (lo)) ? (lo) : (((v) > (hi)) ? (hi) : (v)))
#define constrainInt(v, lo, hi)	    (((int)(v) < (int)(lo)) ? (int)(lo) : (((int)(v) > (int)(hi)) ? (int)(hi) : (int)(v)))
#define constrainFloat(v, lo, hi)   (((float)(v) < (float)(lo)) ? (float)(lo) : (((float)(v) > (float)(hi)) ? (float)(hi) : (float)(v)))

#endif /* __AFC_MATH_H */

/* end of file */
