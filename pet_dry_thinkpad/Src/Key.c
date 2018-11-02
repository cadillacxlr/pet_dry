
#include "Key.h"


#define Key_Beep	BEEP_ON;HAL_Delay(160);	BEEP_OFF

uint8_t K1,K2,K3,K4,K5,K6;



uint8_t Key_Check(void)
{
	uint8_t key_val= 0xFF;
	uint8_t key_prs_tm, key_status;
	if(1 == K1)
	{
		HAL_Delay(15);
		if(0 == HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_7))
		{
			K1 = 2;
			Key_Beep;
			key_val = 4;
		}
		else
		{
			K1 = 0;
		}
	}
	
	if(1 == K2)
	{
		HAL_Delay(15);
		if(0 == HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_6))
		{
			K2 = 2;
			Key_Beep;
			key_val = 5;
		}
		else
		{
			K2 = 0;
		}
	}
	
	if(1 == K3)
	{
		HAL_Delay(15);
		if(0 == HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8))
		{
			K3 = 2;
			Key_Beep;
			key_val = 6;
		}
		else
		{
			K3 = 0;
		}
	}
	
	if(1 == K4)
	{
		HAL_Delay(15);
		if(0 == HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9))
		{
			key_prs_tm = 0;
			do{
				HAL_Delay(100);
				key_prs_tm++;
				key_status = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9);
			}while(0 == key_status && 30 > key_prs_tm);
			
			K4 = 2;
			Key_Beep;
			if(30 > key_prs_tm)
			{
				key_val = 0x02;
			}
			else
			{
				key_val = 0x12;
			}
		}
		else
		{
			K4 = 0;
		}
	}
	
	if(1 == K5)
	{
		HAL_Delay(15);
		if(0 == HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13))
		{
			K5 = 2;
			Key_Beep;
			key_val = 3;
		}
		else
		{
			K5 = 0;
		}
	}
	
	if(1 == K6)
	{
		HAL_Delay(15);
		if(0 == HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2))
		{
			K6 = 2;
			Key_Beep;
			key_val = 1;
		}
		else
		{
			K6 = 0;
		}
	}
	return key_val;
}




