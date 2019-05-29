#ifndef __BUTTON_H
#define __BUTTON_H

#include "afx.h"

typedef enum {
    BTN_LNCH_LND = 0,
    BTN_MISSION,
    BTN_RTL,
    BTN_SPD_RSM,
    BTN_PHOTO,
    BTN_RECORD,
    BTN_MNT_SWITCH,
    BTN_MNT_TRIGGER,
    BTN_ZOOM_IN,
    BTN_ZOOM_OUT,
    BTN_PITCH_INC,
    BTN_PITCH_DEC,
    BTN_SPARE1,
    BTN_SPARE2,
    BTN_SPARE3,
    BTN_SPARE4,
    BTN_CMR_SWITCH1,
    BTN_CMR_SWITCH2,
    BTN_FLT_MD1,
    BTN_FLT_MD2,
    BTN_POWER,
} btnType_t;

#define button_lnch_lnd button[BTN_LNCH_LND]
#define button_mission button[BTN_MISSION]
#define button_rtl button[BTN_RTL]
#define button_spd_rsm button[BTN_SPD_RSM]
#define button_photo button[BTN_PHOTO]
#define button_record button[BTN_RECORD]
#define button_mount_switch button[BTN_MNT_SWITCH]
#define button_mount_trigger button[BTN_MNT_TRIGGER]
#define button_zoom_in button[BTN_ZOOM_IN]
#define button_zoom_out button[BTN_ZOOM_OUT]
#define button_pitch_inc button[BTN_PITCH_INC]
#define button_pitch_dec button[BTN_PITCH_DEC]
#define button_spare1 button[BTN_SPARE1]
#define button_spare2 button[BTN_SPARE2]
#define button_spare3 button[BTN_SPARE3]
#define button_spare4 button[BTN_SPARE4]

#define button_cmr_switch1 button[BTN_CMR_SWITCH1]
#define button_cmr_switch2 button[BTN_CMR_SWITCH2]
#define button_flt_md1 button[BTN_FLT_MD1]
#define button_flt_md2 button[BTN_FLT_MD2]

#define button_power button[BTN_POWER]

typedef struct
{
    uint8_t ring;
	GPIO_TypeDef *GPIOx;
	uint16_t Pinx;
	uint8_t pupd;
	uint8_t pressed;
	uint8_t released;
	uint32_t press_tick;
	uint8_t value;
    uint8_t step;
} buttonStruct_t;

void buttonInit(void);
void buttonUpdate(void);

extern buttonStruct_t button[BTN_NUM];
extern uint8_t shutdown_request;

#endif /* __BUTTON_ */

/* end of file */
