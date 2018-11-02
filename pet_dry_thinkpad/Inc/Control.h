#ifndef __Control_H__
#define __Control_H__

#include "stm32f0xx_hal.h"


#define LCD_BL_ON 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)
#define LCD_BL_OFF 	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)


#define RELAY_1_ON	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)
#define RELAY_1_OFF	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)

#define RELAY_2_ON	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET)
#define RELAY_2_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET)

#define RELAY_3_ON	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)
#define RELAY_3_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET)

#define RELAY_4_ON	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)
#define RELAY_4_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)

#define RELAY_5_ON	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)
#define RELAY_5_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)

#define RELAY_6_ON	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET)
#define RELAY_6_OFF	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET)


typedef struct{
	uint8_t tempereture;
	uint8_t wind_class;
}Std_Environ_Param;

typedef struct{
	uint8_t min;
	uint8_t sec;
}Std_Time;

extern Std_Environ_Param 	Real_Param;
extern Std_Environ_Param 	Set_Param;
extern Std_Time RunTime_Set;



extern uint8_t sys_disp_tm;
extern uint8_t colon_flash;

void Machine_Init(void);
void Control_S_tick(void);
void Key_Deal(uint8_t k_value);
void Disp_App(void);

void Tempereture_Control(void);
void Wind_Control(uint8_t wd_cls);
void Anion_Generator_Control(uint8_t ctl);
void Infrared_Control(uint8_t ctl);


#endif
