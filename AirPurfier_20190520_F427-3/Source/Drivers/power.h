#ifndef __power_h
#define __power_h

#include "afx.h"

void powerPinInit(void);
void powerSystemHold(void);
void powerSystemHalt(void);
void powerRadioHold(void);
void powerRadioHalt(void);
void powerVideoHold(void);
void powerVideoHalt(void);

void directBoot(void);

void androidWorkMonitor(void);
void androidShutdownTrigger(void);

extern uint32_t rc_power_tick;

#endif /* __POWER_H */

/* end of file */
