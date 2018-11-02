

#ifndef __NTC_H__
#define __NTC_H__

#include "stm32f0xx_hal.h"

#define BEEP_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
#define BEEP_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);




uint8_t ADC_to_Temp(uint16_t adc_temp);
uint16_t ADC_to_Voltage(uint16_t adc_temp);
void MX_ADC_Init(void);
uint8_t Tempereture_ADC(void);
void ADC_Systick(void);

#endif
