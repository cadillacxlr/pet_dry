
#ifndef __HT1602B_H__
#define __HT1602B_H__

#include "stm32f0xx_hal.h"

#define HT1621_CS       GPIO_PIN_7
#define HT1621_WR       GPIO_PIN_5
#define HT1621_DAT      GPIO_PIN_3

#define HT1621_CSL		HAL_GPIO_WritePin(GPIOB, HT1621_CS,GPIO_PIN_RESET)
#define HT1621_CSH		HAL_GPIO_WritePin(GPIOB, HT1621_CS,GPIO_PIN_SET)
#define HT1621_WRL		HAL_GPIO_WritePin(GPIOB, HT1621_WR,GPIO_PIN_RESET)
#define HT1621_WRH		HAL_GPIO_WritePin(GPIOB, HT1621_WR,GPIO_PIN_SET)
#define HT1621_DATL     HAL_GPIO_WritePin(GPIOB, HT1621_DAT,GPIO_PIN_RESET)
#define HT1621_DATH     HAL_GPIO_WritePin(GPIOB, HT1621_DAT,GPIO_PIN_SET)

/* defines -------------------------------------------------------------------*/
#define BIAS   0x52     //0b1000 0101 0010  1/2duty 4com 

#define SYSDIS 0X00	//0b1000 0000 0000   ???????LCD????? 
#define SYSEN  0X02     //0b1000 0000 0010  ??????? 

#define LCDOFF 0X04     //0b1000 0000 0100  ?LCD?? 
#define LCDON  0X06     //0b1000 0000 0110  ??LCD?? 

#define XTAL   0x28     //0b1000 0010 1000  ????? 
#define RC256  0X30     //0b1000 0011 0000  ???? 

#define TONEON  0X12    //0b1000 0001 0010  ?????? 
#define TONEOFF 0X10    //0b1000 0001 0000  ?????? 

#define WDTDIS  0X0A    //0b1000 0000 1010  ????? 
#define TIMEREN 0X0C    //0b1000 0000 1100  ?????? 
#define TEST    0XC0    //0b1000 0000 1100  ??????
/* Private variables ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
//extern void Delay_ms(uint16_t nTime);
extern void Ht1621_Init(void);  
extern void Ht1621WrAllData(uint8_t Addr,uint8_t *p,uint8_t cnt); 

#endif
