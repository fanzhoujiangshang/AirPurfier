#include "button.h"
#include "timer.h"

uint32_t last_press_tick = 0;
uint8_t shutdown_request = 0;

/* 按键描述 */
buttonStruct_t button[BTN_NUM] = {
	{ 1, BTN_LNCH_LND_PORT, BTN_LNCH_LND_PIN, BTN_LNCH_LND_DEFAULT }, 		    /* 0  起飞/降落-按键(Launch/Land) (PC6) */
	{ 1, BTN_MISSION_PORT, BTN_MISSION_PIN, BTN_MISSION_DEFAULT }, 		        /* 1  任务执行按键 (PD15) */
	{ 1, BTN_RTL_PORT, BTN_RTL_PIN, BTN_RTL_DEFAULT },                          /* 2  返航按键(Return to launch) (PD14) */
	{ 1, BTN_SPD_RSM_PORT, BTN_SPD_RSM_PIN, BTN_SPD_RSM_DEFAULT },              /* 3  任务暂停/恢复(Suspend/Resume) 按键 (PD13) */
//	{ 1, BTN_PHOTO_PORT, BTN_PHOTO_PIN, BTN_PHOTO_DEFAULT },                    /* 4  拍照按键 (PE7) */
//	{ 1, BTN_RECORD_PORT, BTN_RECORD_PIN, BTN_RECORD_DEFAULT },                 /* 5  摄像起/停按键 (PE8) */
//	{ 1, BTN_MNT_SWITCH_PORT, BTN_MNT_SWITCH_PIN, BTN_MNT_SWITCH_DEFAULT },     /* 6  用户自定义#1按键 (PE9) */
//	{ 1, BTN_MNT_TRIGGER_PORT, BTN_MNT_TRIGGER_PIN, BTN_MNT_TRIGGER_DEFAULT },  /* 7  用户自定义#2按键 (PE10) */
//	{ 1, BTN_ZOOM_IN_PORT, BTN_ZOOM_IN_PIN, BTN_ZOOM_IN_DEFAULT },              /* 8  相机变焦放大 (Zoom in) 按键 (PB3) */
//	{ 1, BTN_ZOOM_OUT_PORT, BTN_ZOOM_OUT_PIN, BTN_ZOOM_OUT_DEFAULT }, 	        /* 9  相机变焦缩小 (Zoom out) 按键 (PB4) */
//	{ 0, BTN_PITCH_INC_PORT, BTN_PITCH_INC_PIN, BTN_PITCH_INC_DEFAULT }, 	    /* 10 云台俯仰+ (gimbal pitch increase) 按键 (PE0) */
//	{ 0, BTN_PITCH_DEC_PORT, BTN_PITCH_DEC_PIN, BTN_PITCH_DEC_DEFAULT }, 	    /* 11 云台俯仰- (gimbal pitch decrease) 按键 (PE1) */
//    { 1, BTN_SPARE1_PORT, BTN_SPARE1_PIN, BTN_SPARE1_DEFAULT }, 		        /* 12 备用按键#1 */
//	{ 1, BTN_SPARE2_PORT, BTN_SPARE2_PIN, BTN_SPARE2_DEFAULT }, 	            /* 13 备用按键#2 */
//	{ 1, BTN_SPARE3_PORT, BTN_SPARE3_PIN, BTN_SPARE3_DEFAULT }, 	            /* 14 备用按键#3 */
//	{ 1, BTN_SPARE4_PORT, BTN_SPARE4_PIN, BTN_SPARE4_DEFAULT }, 	            /* 15 备用按键#4 */
//    { 0, BTN_CMR_SWITCH1_PORT, BTN_CMR_SWITCH1_PIN, BTN_CMR_SWITCH1_DEFAULT },  /* 16 相机切换 (PB9) */
//    { 0, BTN_CMR_SWITCH2_PORT, BTN_CMR_SWITCH2_PIN, BTN_CMR_SWITCH2_DEFAULT },  /* 17 相机切换 (PB9) */
//    { 0, BTN_FLT_MD1_PORT, BTN_FLT_MD1_PIN, BTN_FLT_MD1_DEFAULT },			    /* 18 飞行模式 (flight mode) (手动/自动切换) (PB8)*/
//    { 0, BTN_FLT_MD2_PORT, BTN_FLT_MD2_PIN, BTN_FLT_MD2_DEFAULT },			    /* 19 飞行模式 (flight mode) (手动/自动切换) (PB9)*/
//    { 1, BTN_PWR_PORT, BTN_PWR_PIN, BTN_PWR_DEFAULT }                           /* 20 电源按键 */
};

/* 按键定义 */
void buttonConfig(buttonStruct_t *_button)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Open GPIO clock */
	if (_button->GPIOx == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if (_button->GPIOx == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if (_button->GPIOx == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if (_button->GPIOx == GPIOD)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	}
	else if (_button->GPIOx == GPIOE)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	}
	else if (_button->GPIOx == GPIOF)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	}
	
	if (_button->pupd == BTN_DEFUALT_HIGH)
	{
		/* Configure Button IO as pull up */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	}
	else
	{
		/* Configure Button IO as pull down */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	}
	
	GPIO_InitStructure.GPIO_Pin = _button->Pinx;
	GPIO_Init(_button->GPIOx, &GPIO_InitStructure);
}

void buttonInit(void)
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	for (int i = 0; i < BTN_NUM; i++)
	{
		buttonConfig(&button[i]);
	}
}

void buttonUpdate(void)
{
}

/* end of file */
