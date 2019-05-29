#ifndef __board_m1_r0_h
#define __board_m1_r0_h

#include "stm32f4xx.h"

/* 硬件版本号 */
#define HW_VER	"V1.0"

/* 电池节数 */
#define BATTERY_CELL_NUM			3

#define USART3_REMAP_PARTIAL

/* <- 指示灯定义 -------------------------------------------------------------------> */
/* 指示灯驱动方式定义 */
#define LED_DRIVE_HIGH_ON			1
#define LED_DRIVE_LOW_ON			0

/* 系统工作指示灯 #43 (PE12) */
#define LED_SYSTEM_PORT				GPIOE
#define LED_SYSTEM_PIN				GPIO_Pin_12
#define LED_SYSTEM_DRIVE			LED_DRIVE_HIGH_ON

/* 通信指示灯 #42 (PE11) */
#define LED_COMM_PORT				GPIOE
#define LED_COMM_PIN				GPIO_Pin_11
#define LED_COMM_DRIVE				LED_DRIVE_HIGH_ON

/* 电源指示灯 #41 (PE10) */
#define LED_POWER_PORT				GPIOE
#define LED_POWER_PIN				GPIO_Pin_10
#define LED_POWER_DRIVE				LED_DRIVE_HIGH_ON

/* <- 按键定义 ---------------------------------------------------------------------> */
#define BTN_NUM						21
#define BTN_PRESS_NUM               16
#define BTN_DEFUALT_LOW				0
#define BTN_DEFUALT_HIGH			1

/* BTN00  起飞/降落-按键(Launch/Land) #65 (PC8) */
#define BTN_LNCH_LND_PORT			GPIOC
#define BTN_LNCH_LND_PIN			GPIO_Pin_8
#define BTN_LNCH_LND_DEFAULT		BTN_DEFUALT_HIGH

/* BTN01 返航按键(Return to launch) #61 (PD14) */
#define BTN_RTL_PORT				GPIOD
#define BTN_RTL_PIN					GPIO_Pin_14
#define BTN_RTL_DEFAULT				BTN_DEFUALT_HIGH

/* <- 蜂鸣器控制 ---------------------------------------------------------------------> */
/* 充电状态定义 */
#define CHARGE_OKAY					1
#define CHARGE_NONE					0

/* 充电检测 (PA5) */
#define CHARGE_PORT					GPIOA
#define CHARGE_PIN					GPIO_Pin_5
#define CHARGE_DEFAULT				BTN_DEFUALT_HIGH

/* <- 蜂鸣器控制 ---------------------------------------------------------------------> */
/* 蜂鸣器状态定义 */
#define BUZZER_BEEP					1
#define BUZZER_MUTE					0

/* 蜂鸣器引脚定义 (PA0) */
#define BUZZER_PORT					GPIOA
#define BUZZER_PIN					GPIO_Pin_0
#define BUZZER_DEFAULT				BUZZER_MUTE

/* <- 电源控制 ---------------------------------------------------------------------> */
/* 电源电平驱动方式 */
#define PWR_DRIVE_HIGH_ON			1	/* 高电平使能 */
#define PWR_DRIVE_LOW_ON			0	/* 低电平使能 */

/* 遥控器电源控制 (PE9) */
#define PWR_RC_PORT					GPIOD
#define PWR_RC_PIN					GPIO_Pin_5
#define PWR_RC_DEFAULT				PWR_DRIVE_HIGH_ON

/* 数传电源控制脚 #34 (PC5) */
#define PWR_RADIO_PORT				GPIOC
#define PWR_RADIO_PIN				GPIO_Pin_5
#define PWR_RADIO_DEFAULT			PWR_DRIVE_HIGH_ON

/* 图传电源控制脚 #67(PA8) */
#define PWR_VIDEO_PORT				GPIOA
#define PWR_VIDEO_PIN				GPIO_Pin_8
#define PWR_VIDEO_DEFAULT			PWR_DRIVE_HIGH_ON

/* 安卓电源控制 (PE1) */
#define PWR_ANDROID_PORT			GPIOE
#define PWR_ANDROID_PIN				GPIO_Pin_1
#define PWR_ANDROID_DEFAULT			PWR_DRIVE_HIGH_ON

/* 安卓状态检测引脚 */
#define PWR_ANDROID_CHECK_PORT      GPIOD
#define PWR_ANDROID_CHECK_PIN       GPIO_Pin_0

/* 安卓关机触发信号脚 */
#define PWR_ANDROID_TRIGGER_PORT    GPIOD
#define PWR_ANDROID_TRIGGER_PIN     GPIO_Pin_1
#define PWR_ANDROID_TRIGGER_DEFAULT PWR_DRIVE_HIGH_ON

/* <- 串口定义 ---------------------------------------------------------------------> */
/* USART1 */
#define SERIAL_UART1_PORT			GPIOA
#define SERIAL_UART1_RX_PORT	    GPIOA
#define SERIAL_UART1_TX_PORT	    GPIOA
#define SERIAL_UART1_RX_PIN	        GPIO_Pin_10
#define SERIAL_UART1_TX_PIN	        GPIO_Pin_9
//#define SERIAL_UART1_CTS_PIN	    GPIO_Pin_11
//#define SERIAL_UART1_RTS_PIN	    GPIO_Pin_12
#define SERIAL_UART1_RX_SOURCE	    GPIO_PinSource10
#define SERIAL_UART1_TX_SOURCE	    GPIO_PinSource9
//#define SERIAL_UART1_CTS_SOURCE	GPIO_PinSource11
//#define SERIAL_UART1_RTS_SOURCE	GPIO_PinSource12
#define SERIAL_UART1_RX_DMA_ST	    DMA2_Stream2
#define SERIAL_UART1_TX_DMA_ST	    DMA2_Stream7
#define SERIAL_UART1_RX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART1_TX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART1_TX_DMA_IT	    DMA2_Stream7_IRQHandler
#define SERIAL_UART1_TX_IRQn	    DMA2_Stream7_IRQn
#define SERIAL_UART1_RX_IRQn	    DMA2_Stream2_IRQn
#define SERIAL_UART1_RX_TC_FLAG	    DMA_FLAG_TCIF2
#define SERIAL_UART1_RX_HT_FLAG	    DMA_FLAG_HTIF2
#define SERIAL_UART1_RX_TE_FLAG	    DMA_FLAG_TEIF2
#define SERIAL_UART1_RX_DM_FLAG	    DMA_FLAG_DMEIF2
#define SERIAL_UART1_RX_FE_FLAG	    DMA_FLAG_FEIF2
#define SERIAL_UART1_TX_TC_FLAG	    DMA_FLAG_TCIF7
#define SERIAL_UART1_TX_HT_FLAG	    DMA_FLAG_HTIF7
#define SERIAL_UART1_TX_TE_FLAG	    DMA_FLAG_TEIF7
#define SERIAL_UART1_TX_DM_FLAG	    DMA_FLAG_DMEIF7
#define SERIAL_UART1_TX_FE_FLAG	    DMA_FLAG_FEIF7

/* USART2 */
#define SERIAL_UART2_PORT
#define SERIAL_UART2_RX_PORT	    GPIOA
#define SERIAL_UART2_TX_PORT	    GPIOA
#define SERIAL_UART2_RX_PIN	        GPIO_Pin_3
#define SERIAL_UART2_TX_PIN	        GPIO_Pin_2
//#define SERIAL_UART2_CTS_PIN	    GPIO_Pin_3
//#define SERIAL_UART2_RTS_PIN	    GPIO_Pin_4
#define SERIAL_UART2_RX_SOURCE	    GPIO_PinSource3
#define SERIAL_UART2_TX_SOURCE	    GPIO_PinSource2
//#define SERIAL_UART2_CTS_SOURCE	GPIO_PinSource3
//#define SERIAL_UART2_RTS_SOURCE	GPIO_PinSource4
#define SERIAL_UART2_RX_DMA_ST	    DMA1_Stream5
#define SERIAL_UART2_TX_DMA_ST	    DMA1_Stream6
#define SERIAL_UART2_RX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART2_TX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART2_TX_DMA_IT	    DMA1_Stream6_IRQHandler
#define SERIAL_UART2_TX_IRQn	    DMA1_Stream6_IRQn
#define SERIAL_UART2_RX_TC_FLAG	    DMA_FLAG_TCIF5
#define SERIAL_UART2_RX_HT_FLAG	    DMA_FLAG_HTIF5
#define SERIAL_UART2_RX_TE_FLAG	    DMA_FLAG_TEIF5
#define SERIAL_UART2_RX_DM_FLAG	    DMA_FLAG_DMEIF5
#define SERIAL_UART2_RX_FE_FLAG	    DMA_FLAG_FEIF5
#define SERIAL_UART2_TX_TC_FLAG	    DMA_FLAG_TCIF6
#define SERIAL_UART2_TX_HT_FLAG	    DMA_FLAG_HTIF6
#define SERIAL_UART2_TX_TE_FLAG	    DMA_FLAG_TEIF6
#define SERIAL_UART2_TX_DM_FLAG	    DMA_FLAG_DMEIF6
#define SERIAL_UART2_TX_FE_FLAG	    DMA_FLAG_FEIF6

/* USART3 */
#define SERIAL_UART3_PORT
#define SERIAL_UART3_RX_PORT	    GPIOC
#define SERIAL_UART3_TX_PORT	    GPIOC
#define SERIAL_UART3_RX_PIN	        GPIO_Pin_11
#define SERIAL_UART3_TX_PIN	        GPIO_Pin_10
//#define SERIAL_UART3_CTS_PIN	    GPIO_Pin_11
//#define SERIAL_UART3_RTS_PIN	    GPIO_Pin_12
#define SERIAL_UART3_RX_SOURCE	    GPIO_PinSource11
#define SERIAL_UART3_TX_SOURCE	    GPIO_PinSource10
//#define SERIAL_UART3_CTS_SOURCE	GPIO_PinSource11
//#define SERIAL_UART3_RTS_SOURCE	GPIO_PinSource12
#define SERIAL_UART3_RX_DMA_ST	    DMA1_Stream1
#define SERIAL_UART3_TX_DMA_ST	    DMA1_Stream3
#define SERIAL_UART3_RX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART3_TX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART3_TX_DMA_IT	    DMA1_Stream3_IRQHandler
#define SERIAL_UART3_TX_IRQn	    	DMA1_Stream3_IRQn
#define SERIAL_UART3_RX_IRQn	    	DMA1_Stream1_IRQn
#define SERIAL_UART3_RX_TC_FLAG	    DMA_FLAG_TCIF1
#define SERIAL_UART3_RX_HT_FLAG	    DMA_FLAG_HTIF1
#define SERIAL_UART3_RX_TE_FLAG	    DMA_FLAG_TEIF1
#define SERIAL_UART3_RX_DM_FLAG	    DMA_FLAG_DMEIF1
#define SERIAL_UART3_RX_FE_FLAG	    DMA_FLAG_FEIF1
#define SERIAL_UART3_TX_TC_FLAG	    DMA_FLAG_TCIF3
#define SERIAL_UART3_TX_HT_FLAG	    DMA_FLAG_HTIF3
#define SERIAL_UART3_TX_TE_FLAG	    DMA_FLAG_TEIF3
#define SERIAL_UART3_TX_DM_FLAG	    DMA_FLAG_DMEIF3
#define SERIAL_UART3_TX_FE_FLAG	    DMA_FLAG_FEIF3

/* UART4 */
#define SERIAL_UART4_PORT
#define SERIAL_UART4_RX_PORT		GPIOA
#define SERIAL_UART4_TX_PORT        GPIOA
#define SERIAL_UART4_RX_PIN		    GPIO_Pin_1
#define SERIAL_UART4_TX_PIN		    GPIO_Pin_0
#define SERIAL_UART4_RX_SOURCE	    GPIO_PinSource1
#define SERIAL_UART4_TX_SOURCE	    GPIO_PinSource0
#define SERIAL_UART4_RX_DMA_ST	    DMA1_Stream2
#define SERIAL_UART4_TX_DMA_ST	    DMA1_Stream4
#define SERIAL_UART4_RX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART4_TX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART4_TX_DMA_IT	    DMA1_Stream4_IRQHandler
#define SERIAL_UART4_TX_IRQn	    DMA1_Stream4_IRQn
#define SERIAL_UART4_RX_TC_FLAG	    DMA_FLAG_TCIF2
#define SERIAL_UART4_RX_HT_FLAG	    DMA_FLAG_HTIF2
#define SERIAL_UART4_RX_TE_FLAG	    DMA_FLAG_TEIF2
#define SERIAL_UART4_RX_DM_FLAG	    DMA_FLAG_DMEIF2
#define SERIAL_UART4_RX_FE_FLAG	    DMA_FLAG_FEIF2
#define SERIAL_UART4_TX_TC_FLAG	    DMA_FLAG_TCIF4
#define SERIAL_UART4_TX_HT_FLAG     DMA_FLAG_HTIF4
#define SERIAL_UART4_TX_TE_FLAG	    DMA_FLAG_TEIF4
#define SERIAL_UART4_TX_DM_FLAG	    DMA_FLAG_DMEIF4
#define SERIAL_UART4_TX_FE_FLAG	    DMA_FLAG_FEIF4

/* UART5 */
#define SERIAL_UART5_PORT
#define SERIAL_UART5_RX_PORT	    GPIOD
#define SERIAL_UART5_TX_PORT	    GPIOC
#define SERIAL_UART5_RX_PIN	        GPIO_Pin_2
#define SERIAL_UART5_TX_PIN	        GPIO_Pin_12
#define SERIAL_UART5_RX_SOURCE	    GPIO_PinSource2
#define SERIAL_UART5_TX_SOURCE	    GPIO_PinSource12
#define SERIAL_UART5_RX_DMA_ST	    DMA1_Stream0
#define SERIAL_UART5_TX_DMA_ST	    DMA1_Stream7
#define SERIAL_UART5_RX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART5_TX_DMA_CH	    DMA_Channel_4
#define SERIAL_UART5_TX_DMA_IT	    DMA1_Stream7_IRQHandler
#define SERIAL_UART5_TX_IRQn	    	DMA1_Stream7_IRQn
#define SERIAL_UART5_RX_IRQn	    	DMA1_Stream0_IRQn
#define SERIAL_UART5_RX_TC_FLAG	    DMA_FLAG_TCIF0
#define SERIAL_UART5_RX_HT_FLAG	    DMA_FLAG_HTIF0
#define SERIAL_UART5_RX_TE_FLAG	    DMA_FLAG_TEIF0
#define SERIAL_UART5_RX_DM_FLAG	    DMA_FLAG_DMEIF0
#define SERIAL_UART5_RX_FE_FLAG	    DMA_FLAG_FEIF0
#define SERIAL_UART5_TX_TC_FLAG	    DMA_FLAG_TCIF7
#define SERIAL_UART5_TX_HT_FLAG	    DMA_FLAG_HTIF7
#define SERIAL_UART5_TX_TE_FLAG	    DMA_FLAG_TEIF7
#define SERIAL_UART5_TX_DM_FLAG	    DMA_FLAG_DMEIF7
#define SERIAL_UART5_TX_FE_FLAG	    DMA_FLAG_FEIF7

/* USART6 */
#define SERIAL_UART6_PORT
#define SERIAL_UART6_RX_PORT	    GPIOC
#define SERIAL_UART6_TX_PORT	    GPIOC
#define SERIAL_UART6_RX_PIN	        GPIO_Pin_7
#define SERIAL_UART6_TX_PIN	        GPIO_Pin_6
//#define SERIAL_UART6_CTS_PIN	    GPIO_Pin_11
//#define SERIAL_UART6_RTS_PIN	    GPIO_Pin_12
#define SERIAL_UART6_RX_SOURCE	    GPIO_PinSource7
#define SERIAL_UART6_TX_SOURCE	    GPIO_PinSource6
//#define SERIAL_UART6_CTS_SOURCE	GPIO_PinSource11
//#define SERIAL_UART6_RTS_SOURCE	GPIO_PinSource12
#define SERIAL_UART6_RX_DMA_ST	    DMA2_Stream1
#define SERIAL_UART6_TX_DMA_ST	    DMA2_Stream6
#define SERIAL_UART6_RX_DMA_CH	    DMA_Channel_5
#define SERIAL_UART6_TX_DMA_CH	    DMA_Channel_5
#define SERIAL_UART6_TX_DMA_IT	    DMA2_Stream6_IRQHandler
#define SERIAL_UART6_TX_IRQn	    DMA2_Stream6_IRQn
#define SERIAL_UART6_RX_TC_FLAG	    DMA_FLAG_TCIF1
#define SERIAL_UART6_RX_HT_FLAG	    DMA_FLAG_HTIF1
#define SERIAL_UART6_RX_TE_FLAG	    DMA_FLAG_TEIF1
#define SERIAL_UART6_RX_DM_FLAG	    DMA_FLAG_DMEIF1
#define SERIAL_UART6_RX_FE_FLAG	    DMA_FLAG_FEIF1
#define SERIAL_UART6_TX_TC_FLAG	    DMA_FLAG_TCIF6
#define SERIAL_UART6_TX_HT_FLAG	    DMA_FLAG_HTIF6
#define SERIAL_UART6_TX_TE_FLAG	    DMA_FLAG_TEIF6
#define SERIAL_UART6_TX_DM_FLAG	    DMA_FLAG_DMEIF6
#define SERIAL_UART6_TX_FE_FLAG	    DMA_FLAG_FEIF6


#define METHANAL_UART                   USART1
#define METHANAL_UART_BAUD              9600
#define EC20_UART                       USART3
#define EC20_UART_BAUD                  115200
#define GRANULE_UART                    UART5
#define GRANULE_UART_BAUD               9600

#endif /* __board_m1_r5 */
