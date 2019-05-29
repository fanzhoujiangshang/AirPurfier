#include "analog.h"

_adc_t adc;

void analogGPIOConfig(GPIO_TypeDef *GPIOx, uint16_t Pinx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_AFIO, ENABLE);
	
	/* Open GPIO clock */
	if (GPIOx == GPIOA)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	}
	else if (GPIOx == GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	}
	else if (GPIOx == GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	}
	else if (GPIOx == GPIOD)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	}
	else if (GPIOx == GPIOE)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	}
	else if (GPIOx == GPIOF)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	}
	
	GPIO_InitStructure.GPIO_Pin = Pinx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void analogADCConfig(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	if (ADC_BAT == ADC1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	}
	
	if (ADC_DMA == DMA1)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	}
	
	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC_BAT->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(adc.value);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = ADC_NUM;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);

	/* Enable DMAx channelx */
	DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);

	/* ADCx configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = ADC_NUM;
	ADC_Init(ADC_BAT, &ADC_InitStructure);

	/* ADC1 regular channel14 configuration */ 
	ADC_RegularChannelConfig(ADC_ROLL, ADC_ROLL_CH, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC_PITCH, ADC_PITCH_CH, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC_THROTTLE, ADC_THROTTLE_CH, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC_YAW, ADC_YAW_CH, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC_BAT, ADC_BAT_CH, 5, ADC_SampleTime_239Cycles5);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while (ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while (ADC_GetCalibrationStatus(ADC1));
	 
	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void analogInit(void)
{
	analogGPIOConfig(ADC_BAT_PORT, ADC_BAT_PIN);
	analogGPIOConfig(ADC_ROLL_PORT, ADC_ROLL_PIN);
	analogGPIOConfig(ADC_PITCH_PORT, ADC_PITCH_PIN);
	analogGPIOConfig(ADC_THROTTLE_PORT, ADC_THROTTLE_PIN);
	analogGPIOConfig(ADC_YAW_PORT, ADC_YAW_PIN);
	
	analogADCConfig();
}

uint16_t batteryGetADC(void)
{
	uint16_t battery_adc;
	
	battery_adc = adc.value[4];
	
	return battery_adc;
}

/* end of file */
