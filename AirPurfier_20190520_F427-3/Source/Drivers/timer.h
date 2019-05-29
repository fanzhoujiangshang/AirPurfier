#ifndef __timer_h
#define __timer_h

#include "afx.h"

#define uwTick      (xTaskGetTickCount())
#define uwTickISR   (xTaskGetTickCountFromISR())
#define uwTickHD    (TIM4->CNT)

void timerInit(void);
void delay_ms(uint16_t nms);

#endif /* __timer_h */

/* end of file */
