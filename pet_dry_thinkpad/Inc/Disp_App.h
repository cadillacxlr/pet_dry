
#ifndef __Disp_App_H__
#define __Disp_App_H__

#include "stm32f0xx_hal.h"


#define Under_1		0x0020
#define Under_2		0x0040
#define Under_3		0x0080
#define Under_4		0x0001
#define Under_5		0x0002
#define Under_6		0x0004

#define FUNC_Line	0x0010

#define Wind_Txt	0x0180			// 风力等级
#define Wind_1		0x0008
#define Wind_2		0x0110
#define Wind_3		0x0120

#define RT_Tempereture	0x0310		// 实时温度——文字
#define Num_2A			0x0208			// 温度数字1
#define Num_2B			0x0204			// 温度数字1
#define Num_2C			0x0201			// 温度数字1
#define Num_2D			0x0210			// 温度数字1
#define Num_2E			0x0320			// 温度数字1
#define Num_2F			0x0340			// 温度数字1
#define Num_2G			0x0202			// 温度数字1

#define Num_3A			0x0280			// 温度数字2
#define Num_3B			0x0104			// 温度数字2
#define Num_3C			0x0302			// 温度数字2
#define Num_3D			0x0301			// 温度数字2
#define Num_3E			0x0220			// 温度数字2
#define Num_3F			0x0240			// 温度数字2
#define Num_3G			0x0102			// 温度数字2

#define Temp_Uint_C		0x0140
#define Temp_Uint_F		0x0108

#define Standard_Mode_Txt	0x0A10
#define Set_Mode_Txt		0x0A20
#define AddUp_Tm_Txt		0x0A40
#define Remaining_Tm_Txt	0x0A80

#define Num_4A			0x0801
#define Num_4B			0x0810
#define Num_4C			0x0840
#define Num_4D			0x0808
#define Num_4E			0x0804
#define Num_4F			0x0802
#define Num_4G			0x0820

#define Colon			0x0780			// 冒号

//#define Temp_Bar

void disp_seg(uint16_t seg, uint8_t status);
void disp_Num2(uint8_t num);
void disp_clr_Num2(uint8_t num);
void disp_Num3(uint8_t num);
void disp_clr_Num3(uint8_t num);

void disp_Num_Tm(uint8_t loc, uint8_t num);
void disp_clr_Num_Tm(uint8_t loc, uint8_t num);
void Disp_Time(uint8_t min, uint8_t sec, uint8_t colon);
void Disp_Temp_Bar(uint8_t cls);

void Disp_Tempereture(uint8_t temp, uint8_t unit, uint8_t txt);
void disp_Num_Temp(uint8_t loc, uint8_t num, uint8_t style);

void Disp_WindClass(uint8_t wind_cls, uint8_t txt);			// 显示温度等级

void disp_test(void);
void Disp_Clean(void);
void Disp_All(void);

void Disp_Reflesh(void);

#endif
