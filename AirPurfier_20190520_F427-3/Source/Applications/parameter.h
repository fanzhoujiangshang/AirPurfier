#ifndef __parameter_h
#define __parameter_h

#include "afx.h"

#define PARAM_FITER_TIME_L 0x5555
#define PARAM_FITER_TIME_H 0x5556
#define PARAM_MOTOR_LEVEL  0x5558
#define PARAM_MOTOR_MODE   0x5557

void parameterInit(void);

extern uint32_t mcuID[3];

#endif /* __parameter_h */

/* end of file */
