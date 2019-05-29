#ifndef __led_h
#define __led_h

#include "afx.h"

typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint16_t Pinx;
	uint8_t drive_mode;
}_led_hw_t;

void LedTurnOn(_led_hw_t *_led);
void LedTurnOff(_led_hw_t *_led);
void LedToggle(_led_hw_t *_led);
void LedConfig(_led_hw_t *_led);
void LedFault(void);

#endif /* __LED_H */

/* end of file */
