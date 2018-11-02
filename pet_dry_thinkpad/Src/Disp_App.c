
#include "Disp_App.h"
#include "HT1602B.h"


uint8_t SEG_Temp[16];

uint16_t Num2[11][7] = {
{Num_2A,Num_2B,Num_2C,Num_2D,Num_2E,Num_2F,0},	// 0
{Num_2B,Num_2C,0},
{Num_2A,Num_2B,Num_2G,Num_2D,Num_2E,0},			// 2
{Num_2A,Num_2B,Num_2C,Num_2D,Num_2G,0},
{Num_2B,Num_2C,Num_2F,Num_2G,0},				// 4
{Num_2A,Num_2F,Num_2G,Num_2C,Num_2D,0},
{Num_2A,Num_2F,Num_2G,Num_2C,Num_2D,Num_2E,0},	// 6
{Num_2A,Num_2B,Num_2C,0},
{Num_2A,Num_2B,Num_2C,Num_2D,Num_2E,Num_2F,Num_2G},			// 8
{Num_2A,Num_2B,Num_2C,Num_2D,Num_2F,Num_2G,0},
{Num_2G,0},
};

uint16_t Num3[11][7] = {
{Num_3A,Num_3B,Num_3C,Num_3D,Num_3E,Num_3F,0},	// 0
{Num_3B,Num_3C,0},
{Num_3A,Num_3B,Num_3G,Num_3D,Num_3E,0},			// 2
{Num_3A,Num_3B,Num_3C,Num_3D,Num_3G,0},
{Num_3B,Num_3C,Num_3F,Num_3G,0},				// 4
{Num_3A,Num_3F,Num_3G,Num_3C,Num_3D,0},
{Num_3A,Num_3F,Num_3G,Num_3C,Num_3D,Num_3E,0},	// 6
{Num_3A,Num_3B,Num_3C,0},
{Num_3A,Num_3B,Num_3C,Num_3D,Num_3E,Num_3F,Num_3G},			// 8
{Num_3A,Num_3B,Num_3C,Num_3D,Num_3F,Num_3G,0},
{Num_3G,0},
};

uint16_t Num4[10][7] = {
{Num_4A,Num_4B,Num_4C,Num_4D,Num_4E,Num_4F,0},	// 0
{Num_4B,Num_4C,0},
{Num_4A,Num_4B,Num_4G,Num_4D,Num_4E,0},			// 2
{Num_4A,Num_4B,Num_4C,Num_4D,Num_4G,0},
{Num_4B,Num_4C,Num_4F,Num_4G,0},				// 4
{Num_4A,Num_4F,Num_4G,Num_4C,Num_4D,0},
{Num_4A,Num_4F,Num_4G,Num_4C,Num_4D,Num_4E,0},	// 6
{Num_4A,Num_4B,Num_4C,0},
{Num_4A,Num_4B,Num_4C,Num_4D,Num_4E,Num_4F,Num_4G},			// 8
{Num_4A,Num_4B,Num_4C,Num_4D,Num_4F,Num_4G,0},
};


void disp_test(void)
{
	uint8_t i , j;

	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 8; j++)
		{
			SEG_Temp[i] = (1 << j);
			Ht1621WrAllData(0x00,SEG_Temp,16); 
			// 温度数字			HAL_Delay(50);
		}
		SEG_Temp[i] = 0;
	}

	while(1)
	{

	}
}

void Disp_Reflesh(void)
{
	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void disp_seg(uint16_t seg, uint8_t status)
{
	if(1 == status)
	{
		SEG_Temp[(seg&0xFF00)>>8] |= seg&0x00FF;
	}
	else
	{
		SEG_Temp[(seg&0xFF00)>>8] &= ((~seg)&0x00FF);
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void disp_col(void)			// 冒号
{
	disp_seg(Colon,1);
}

void disp_Num2(uint8_t num)		// 温度十位
{
	uint8_t i;
	
	for(i = 0; i < 7; i++)
	{
		if(0 != Num2[num][i])
		{
			SEG_Temp[(Num2[num][i]&0xFF00)>>8] |= Num2[num][i]&0x00FF;
		}
		else
		{
			i = 7;
		}
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void disp_clr_Num2(uint8_t num)
{
	uint8_t i;
	
	for(i = 0; i < 7; i++)
	{
		if(0 != Num2[num][i])
		{
			SEG_Temp[(Num2[num][i]&0xFF00)>>8] &= ~(Num2[num][i]&0x00FF);
		}
		else
		{
			i = 7;
		}
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void disp_Num3(uint8_t num)				// 温度 个位
{
	uint8_t i;
	
	for(i = 0; i < 7; i++)
	{
		if(0 != Num3[num][i])
		{
			SEG_Temp[(Num3[num][i]&0xFF00)>>8] |= Num3[num][i]&0x00FF;
		}
		else
		{
			i = 7;
		}
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void disp_clr_Num3(uint8_t num)
{
	uint8_t i;
	
	for(i = 0; i < 7; i++)
	{
		if(0 != Num3[num][i])
		{
			SEG_Temp[(Num3[num][i]&0xFF00)>>8] &= ~(Num3[num][i]&0x00FF);
		}
		else
		{
			i = 7;
		}
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void Disp_WindClass(uint8_t wind_cls, uint8_t txt)
{
	disp_seg(Wind_Txt, ((0 == txt)?0:1));				// 文字 风力等级
	
	switch(wind_cls)
	{
		case 0:{
			disp_seg(Wind_1, 0);
			disp_seg(Wind_2, 0);
			disp_seg(Wind_3, 0);
		}break;
		
		case 1:{
			disp_seg(Wind_1, 1);
			disp_seg(Wind_2, 0);
			disp_seg(Wind_3, 0);
		}break;
		
		case 2:{
			disp_seg(Wind_1, 1);
			disp_seg(Wind_2, 1);
			disp_seg(Wind_3, 0);
		}break;
		
		case 3:{
			disp_seg(Wind_1, 1);
			disp_seg(Wind_2, 1);
			disp_seg(Wind_3, 1);
		}break;
	}
}

uint8_t last_temp;
void Disp_Tempereture(uint8_t temp, uint8_t unit, uint8_t txt)				// 显示温度
{
	if(0xFF == temp)return;
//	if(last_temp == temp)return;
	
	last_temp = temp;
	
	uint8_t loc_dec = temp / 10;
	
	disp_clr_Num2(8);
	disp_clr_Num3(8);
	
	disp_seg(RT_Tempereture, ((0 == txt)?0:1));
	
	if(0xEE == unit)
	{
		disp_seg(Temp_Uint_C,0);
		disp_seg(Temp_Uint_F,0);
		return;
	}
	
	disp_seg(Temp_Uint_C, ((0 == unit)?1:0));
	disp_seg(Temp_Uint_F, ((0 == unit)?0:1));
	
	if(0xEE == temp)return;
	
	if(0xAA == temp)
	{
		disp_Num2(10);
		disp_Num3(10);
		return;
	}
	
	if(0 != loc_dec)
	{
		disp_Num2(loc_dec);
	}
	disp_Num3(temp % 10);
}

// loc : 位置，  num：数字
void disp_Num_Tm(uint8_t loc, uint8_t num)			// 显示时间的数字
{
	uint8_t i;
	
	for(i = 0; i < 7; i++)
	{
		if(0 != Num4[8][i])
		{
			SEG_Temp[((Num4[8][i]&0xFF00)>>8)-loc] &= ~(Num4[8][i]&0x00FF);
		}
		else
		{
			i = 7;
		}
	}
	if(0xEE == num)
	{
//		Ht1621WrAllData(0x00,SEG_Temp,16); 
		return;
	}
	for(i = 0; i < 7; i++)
	{
		if(0 != Num4[num][i])
		{
			SEG_Temp[((Num4[num][i]&0xFF00)>>8)-loc] |= Num4[num][i]&0x00FF;
		}
		else
		{
			i = 7;
		}
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void Disp_Time(uint8_t min, uint8_t sec, uint8_t colon)
{
	uint8_t i,min_d = min/10;
	
	disp_seg(Colon,colon);
	
	if(0xEE == min && 0xEE == sec)
	{
		for(i = 0; i < 4; i++)
		{
			disp_Num_Tm(i, 0xEE);
		}
		return;
	}
	
	disp_Num_Tm(0,(0 != min_d)?min_d:0xEE);
	disp_Num_Tm(1,(min%10));
	disp_Num_Tm(2,(sec/10));
	disp_Num_Tm(3,(sec%10));
}

void disp_clr_Num_Tm(uint8_t loc, uint8_t num)
{
	uint8_t i;
	
	for(i = 0; i < 7; i++)
	{
		if(0 != Num4[num][i])
		{
			SEG_Temp[((Num4[num][i]&0xFF00)>>8)-loc] &= ~(Num4[num][i]&0x00FF);
		}
		else
		{
			i = 7;
		}
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void disp_Num_Temp(uint8_t loc, uint8_t num, uint8_t style)			// 显示时间的数字
{
	uint8_t i;
	
	for(i = 0; i < 7; i++)
	{
		if(0 != Num3[num][i])
		{
			SEG_Temp[((Num3[num][i]&0xFF00)>>8)-loc] |= Num3[num][i]&0x00FF;
		}
		else
		{
			i = 7;
		}
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void Disp_Temp_Bar(uint8_t cls)					// 温度条
{
	switch(cls)
	{
		case 0:SEG_Temp[9] = 0x00;break;
		case 1:SEG_Temp[9] = 0x01;break;
		case 2:SEG_Temp[9] = 0x03;break;
		case 3:SEG_Temp[9] = 0x07;break;
		case 4:SEG_Temp[9] = 0x0F;break;
		case 5:SEG_Temp[9] = 0x1F;break;
		case 6:SEG_Temp[9] = 0x3F;break;
		case 7:SEG_Temp[9] = 0x7F;break;
		case 8:SEG_Temp[9] = 0xFF;break;
	}
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void Disp_All(void)
{
	uint8_t i;
	for(i = 0; i < 16; i++)
	{
		SEG_Temp[i] = 0xFF;
	}
	
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}

void Disp_Clean(void)
{
	uint8_t i;
	for(i = 0; i < 16; i++)
	{
		SEG_Temp[i] = 0;
	}
	
//	Ht1621WrAllData(0x00,SEG_Temp,16); 
}




