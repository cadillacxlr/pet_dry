
#ifndef __Key_H__
#define __Key_H__

#include "stm32f0xx_hal.h"

#define BEEP_ON		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
#define BEEP_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);


//typedef struct{
//	
//}TypeKey;






uint8_t Key_Check(void);



#endif
