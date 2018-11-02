
#include "Control.h"
#include "Disp_App.h"


uint8_t machine_status=0;
uint8_t key_fresh;

uint8_t sys_disp_tm;
uint8_t colon_flash;
uint8_t operate_wait_tm;

uint8_t colon_flag;
uint8_t tm_sw_cnt, tm_sw_flag;

uint16_t ctrl_ms;
uint16_t down_wait_sec;

Std_Environ_Param 	Real_Param;
Std_Environ_Param 	Set_Param;
Std_Time RunTime_Set;
uint16_t Sec_ParamSet;
uint16_t Sec_Add;
uint16_t Sec_Left;

uint8_t Tempereture_Ctrl_Allow=0;

extern uint8_t temperature[2];
extern uint8_t sys_500ms;
extern uint8_t last_temp;

void Machine_Init(void)
{
	Disp_Clean();
	Disp_Reflesh();
	LCD_BL_OFF;
}

void Control_S_tick(void)
{
	if(( 0 == ctrl_ms) &&
		(2 == machine_status || 4 == machine_status))
	{
		Sec_Add++;
		Sec_Left--;
	}
	ctrl_ms++;
	if(1000 < ctrl_ms)
	{
		ctrl_ms = 0;
	}
}

void Key_Deal(uint8_t k_value)				// 按键检测与处理
{
	if(0xFF == k_value)return;
	
	switch(machine_status)
	{
		case 0:{		// 待机状态
			if(1 == k_value)
			{
				machine_status = 1;			// 进入启动模式
				LCD_BL_ON;
//				disp_Num_Tm(0,0);
//				disp_Num_Tm(1,1);
//				disp_Num_Tm(2,2);
//				disp_Num_Tm(3,3);
//				Disp_Reflesh();
				
				Disp_Tempereture(Real_Param.tempereture, 0, 1);		// 刷新温度值
				Disp_Reflesh();
				
				sys_disp_tm = 10;			// 10秒无操作，LED灯、背光灯熄灭
			}
		}break;
		
		case 1:{		// 启动模式
			switch(k_value)
			{
				case 1:{
					machine_status = 1;			// 进入运行模式
					sys_disp_tm = 5;			// 5秒后，LED灯、背光灯熄灭
				}break;
				
				case 2:{
					last_temp = 0;
					disp_seg(FUNC_Line, 1);			// 功能条 亮
					disp_seg(Standard_Mode_Txt, 1);		// 显示“标准模式”, 进入运行模式
					disp_seg(Set_Mode_Txt, 	0);
					Disp_Tempereture(Real_Param.tempereture, 0, 1);
					
					Set_Param.tempereture = 34;
					Set_Param.wind_class = 3;
					RunTime_Set.min = 60;
					RunTime_Set.sec = 0;
					Sec_Add = 0;
					
					Disp_Temp_Bar((Set_Param.tempereture-18) >> 1);
					Sec_Left = RunTime_Set.min * 60 + RunTime_Set.sec;
					disp_seg(AddUp_Tm_Txt, 1);			// 先显示 累计时间
					disp_seg(Under_4|Under_5, 1);
					
					Disp_WindClass(Set_Param.wind_class, 1);				// 显示  风力等级
					Disp_Reflesh();
					
					Wind_Control(Set_Param.wind_class);		// 风机控制
					Tempereture_Ctrl_Allow = 1;
					tm_sw_cnt = 0;
					machine_status = 2;				// 进入运行模式
				}break;
				
				case 0x12:{
					Set_Param.tempereture = 34;
					Set_Param.wind_class = 3;
					RunTime_Set.min = 60;
					RunTime_Set.sec = 0;
					Sec_Add = 0;
					Sec_Left = RunTime_Set.min*60;
					
					disp_seg(Standard_Mode_Txt, 0);
					disp_seg(Set_Mode_Txt, 1);
					Disp_Temp_Bar((Set_Param.tempereture-18) >> 1);
					Disp_WindClass(Set_Param.wind_class, 1);
					Disp_Time(RunTime_Set.min, RunTime_Set.sec,1);
					Disp_Tempereture(Real_Param.tempereture, 0, 1);
					disp_seg(FUNC_Line, 1);			// 功能条 亮
					Disp_Reflesh();
					
					operate_wait_tm = 5;
					machine_status = 3;				// 进入设置模式
				}break;
				
				case 0x03:{
					Set_Param.tempereture = 34;
					Set_Param.wind_class = 2;
					RunTime_Set.min = 30;
					RunTime_Set.sec = 0;
					Sec_Add = 0;
					Sec_Left = RunTime_Set.min*60;
					tm_sw_cnt = 0;
					
					disp_seg(Remaining_Tm_Txt, 1);
					disp_seg(FUNC_Line, 1);			// 功能条 亮
					disp_seg(Under_1|Under_2|Under_4|Under_6, 1);
					Disp_Tempereture(Real_Param.tempereture, 0, 1);		// 刷新温度值
					Disp_Reflesh();
					
					Wind_Control(Set_Param.wind_class);		// 风机控制
					Anion_Generator_Control(1);			// 打开负离子发生器
					Infrared_Control(1);				// 打开红外理疗灯
					Tempereture_Ctrl_Allow = 1;
					
					machine_status = 4;				// 进入理疗模式
				}break;
			}
		}break;
		
		case 2:{		// 运行模式
			switch(k_value)
			{
				case 1:{		// 按下 KEY1，设备停止运行
					machine_status = 5;			// 进入暂停状态
					Tempereture_Ctrl_Allow = 0;
					
					operate_wait_tm = 5;
				}break;
			}
		}break;
		
		case 3:{		// 设置模式
			sys_500ms = 0;
			operate_wait_tm = 5;		// 操作时间刷新
			switch(k_value)
			{
				case 4:{				// 温度设定
					Set_Param.tempereture += 2;
					if(34 < Set_Param.tempereture)
					{
						Set_Param.tempereture = 20;
					}
					Disp_Temp_Bar((Set_Param.tempereture-18) >> 1);
				}break;
				
				case 5:{				// 风力设定
					Set_Param.wind_class++;
					if(4 == Set_Param.wind_class)
					{
						Set_Param.wind_class = 1;
					}
					Disp_WindClass(Set_Param.wind_class, 1);
				}break;
				
				case 6:{				// 时间设定
					RunTime_Set.min += 10;
					if(90 < RunTime_Set.min)
					{
						RunTime_Set.min = 20;
					}
					Disp_Time(RunTime_Set.min, RunTime_Set.sec,1);
				}break;
			}
			Disp_Reflesh();
			k_value = 0xFF;
		}break;
		
		case 4:{			// 理疗模式
			switch(k_value)
			{
				case 1:{		//暂停
					Anion_Generator_Control(0);			// 关闭负离子发生器
					Infrared_Control(0);				// 关闭红外理疗灯
					Tempereture_Ctrl_Allow = 0;
					
					machine_status = 5;			// 进入暂停状态
					operate_wait_tm = 5;
				}break;
				
				case 5:{		//风速调节
					Set_Param.wind_class++;
					if(4 == Set_Param.wind_class)
					{
						Set_Param.wind_class = 1;
					}
					Disp_WindClass(Set_Param.wind_class, 1);
					Disp_Reflesh();
					
					Wind_Control(Set_Param.wind_class);		// 风机控制
				}break;
				
				case 6:{		//时间调节
					Sec_Left += 600;
					if(5400 < Sec_Left)
					{
						Sec_Left = 1200;
					}
					Disp_Time(Sec_Left/60, Sec_Left%60, 1);
					Disp_Reflesh();
				}break;
			}
		}break;
		
		case 5:{			// 运行暂停
			switch(k_value)
			{
				case 1:{
					Wind_Control(0);		// 风机控制
					
					machine_status = 0;
					Disp_Clean();
					Disp_Reflesh();
					LCD_BL_OFF;
				}break;
				
				default:	break;
			}
		}break;
		
		case 6:{			// 运行结束
			switch(k_value)
			{
				case 1:{
					Wind_Control(0);		// 风机控制
					
					machine_status = 0;
					Disp_Clean();
					Disp_Reflesh();
					LCD_BL_OFF;
				}break;
				
				default:	break;
			}
		}break;
	}
	k_value = 0xFF;
}



void Disp_App(void)					// 显示处理
{
	uint8_t d_min, d_sec;
	switch(machine_status)
	{
		case 1:{			// 启动模式
			if(0 == sys_disp_tm)
			{
				Disp_Clean();
				Disp_Reflesh();
				LCD_BL_OFF;
				machine_status = 0;
			}
		}break;
		
		case 2:{			// 运行模式
			if(1 == colon_flash)
			{
				colon_flash = 0;
				if(0 == colon_flag)
				{
					disp_seg(AddUp_Tm_Txt, (tm_sw_flag?0:1));			// 累计时间
					disp_seg(Remaining_Tm_Txt, (tm_sw_flag?1:0));		// 显示剩余时间
					d_min = ((0 == tm_sw_flag)?(Sec_Add/60):(Sec_Left/60));
					d_sec = ((0 == tm_sw_flag)?(Sec_Add%60):(Sec_Left%60));
					colon_flag = 1;
					disp_seg(Colon,1);
					Disp_WindClass(3,1);
					Disp_Time(d_min, d_sec,1);
					Disp_Reflesh();
					
					if(0 == Sec_Left)			// 运行结束
					{
						disp_seg(Standard_Mode_Txt,0);
						disp_seg(AddUp_Tm_Txt, 0);			// 累计时间
						disp_seg(Remaining_Tm_Txt, 1);		// 显示剩余时间
						disp_seg(Under_1|Under_2|Under_4|Under_5|Under_6, 0);
						disp_seg(Under_3, 1);
						
						Disp_Temp_Bar(0);
						
						Disp_Tempereture(0xEE, 0xEE, 0);
						Disp_WindClass(0,0);	
						Disp_Reflesh();
						Tempereture_Ctrl_Allow = 0;
						
						machine_status = 6;			// 结束模式
						down_wait_sec = 0;
						break;
					}
					tm_sw_cnt++;
					if(10 <= tm_sw_cnt)
					{
						tm_sw_cnt = 0;
						tm_sw_flag = (tm_sw_flag?0:1);
					}
				}
				else if(1 == colon_flag)
				{
					colon_flag = 0;
					disp_seg(Colon,0);
					Disp_Reflesh();
				}
				
				Disp_Tempereture(Real_Param.tempereture, 0, 1);		// 刷新温度值
				Disp_Reflesh();
			}
		}break;
		
		case 3:{						// 设置模式
			if(1 == colon_flash)
			{
				colon_flash = 0;
				if(0 == colon_flag)
				{
					colon_flag = 1;
					disp_seg(Set_Mode_Txt, 	0);
					Disp_Reflesh();
//					Disp_Temp_Bar((Set_Param.tempereture-18) >> 1);
//					Disp_WindClass(Set_Param.wind_class, 1);
//					Disp_Time(RunTime_Set.min, RunTime_Set.sec,1);
//					disp_seg(Under_4|Under_5, 1);
				}
				else if(1 == colon_flag)
				{
					colon_flag = 0;
					disp_seg(Set_Mode_Txt, 1);
//					Disp_Tempereture(Real_Param.tempereture,0,1);
//					Disp_Temp_Bar(0);
//					Disp_WindClass(0, 1);
//					Disp_Time(0xEE,0xEE,0);
//					disp_seg(Under_4|Under_5, 0);
					
					operate_wait_tm--;
					if(0 == operate_wait_tm)				// 退出设置模式
					{
						disp_seg(Set_Mode_Txt, 	0);
						disp_seg(Standard_Mode_Txt, 1);		// 显示“标准模式”, 进入运行模式
						
						Disp_Temp_Bar((Set_Param.tempereture-18) >> 1);
						Sec_Left = RunTime_Set.min * 60 + RunTime_Set.sec;
						disp_seg(AddUp_Tm_Txt, 1);			// 先显示 累计时间
						disp_seg(Under_4|Under_5, 1);
						
						Disp_WindClass(Set_Param.wind_class, 1);				// 显示  风力等级
						
						Wind_Control(Set_Param.wind_class);		// 风机控制
						
						machine_status = 2;				// 5s 未操作，进入运行模式
					}
					Disp_Reflesh();
				}
				
			}
		}break;
		
		case 4:{				// 理疗模式
			if(1 == colon_flash)
			{
				colon_flash = 0;
				if(0 == colon_flag)
				{
					colon_flag = 1;
					disp_seg(AddUp_Tm_Txt, (tm_sw_flag?0:1));			// 累计时间
					disp_seg(Remaining_Tm_Txt, (tm_sw_flag?1:0));		// 显示剩余时间
					d_min = ((0 == tm_sw_flag)?(Sec_Add/60):(Sec_Left/60));
					d_sec = ((0 == tm_sw_flag)?(Sec_Add%60):(Sec_Left%60));
					disp_seg(Colon,1);
					Disp_WindClass(Set_Param.wind_class,1);
					Disp_Time(d_min, d_sec,1);
					Disp_Reflesh();
					
					if(0 == Sec_Left)			// 运行结束
					{
						disp_seg(AddUp_Tm_Txt, 0);			// 累计时间
						disp_seg(Remaining_Tm_Txt, 1);		// 显示剩余时间
						disp_seg(Under_1|Under_2|Under_4|Under_5|Under_6, 0);
						disp_seg(Under_3, 1);
						
						Disp_Temp_Bar(0);
						
						Disp_Tempereture(0xEE, 0xEE, 0);
						Disp_WindClass(0,0);	
						Disp_Reflesh();
						
						Wind_Control(0);		// 风机控制
						Anion_Generator_Control(0);			// 关闭负离子发生器
						Infrared_Control(0);				// 关闭红外理疗灯
						Tempereture_Ctrl_Allow = 0;
						
						machine_status = 6;			// 结束模式
						down_wait_sec = 0;
						break;
					}
					tm_sw_cnt++;
					if(10 <= tm_sw_cnt)
					{
						tm_sw_cnt = 0;
						tm_sw_flag = (tm_sw_flag?0:1);
					}
				}
				else if(1 == colon_flag)
				{
					colon_flag = 0;
					disp_seg(Colon,0);
					Disp_Reflesh();
				}
				Disp_Tempereture(Real_Param.tempereture, 0, 1);		// 刷新温度值
				Disp_Reflesh();
			}
		}break;
		
		case 5:{				// 运行暂停
			if(1 == colon_flash)
			{
				colon_flash = 0;
				if(0 == colon_flag)
				{
					colon_flag = 1;
					Disp_Time(Sec_Left/60, Sec_Left%60, 1);
					Disp_Reflesh();
				}
				else
				{
					colon_flag = 0;
					Disp_Time(0xEE, 0xEE,1);
					Disp_Reflesh();
					operate_wait_tm--;
					if(0 == operate_wait_tm)
					{
						machine_status = 0;
						Disp_Clean();
						Disp_Reflesh();
						LCD_BL_OFF;
					}
				}
			}
		}break;
		
		case 6:{		// 运行结束
			if(1 == colon_flash)
			{
				colon_flash = 0;
				if(0 == colon_flag)
				{
					colon_flag = 1;
					Disp_Time(0, 0,1);
					Disp_Reflesh();
				}
				else
				{
					colon_flag = 0;
					Disp_Time(0xEE, 0xEE,1);
					Disp_Reflesh();
					down_wait_sec++;
					if(300 <= down_wait_sec)
					{
						machine_status = 0;
						Disp_Clean();
						Disp_Reflesh();
						LCD_BL_OFF;
					}
				}
			}
		}break;
	}
}


void Tempereture_Control(void)			// 温度控制
{
	if(0 == Tempereture_Ctrl_Allow)		// 关闭NTC
	{
		return;
	}
	
	
}

void Wind_Control(uint8_t wd_cls)		// 风力控制
{
	switch(wd_cls)
	{
		case 1:{
			
		}break;
		
		case 2:{
			
		}break;
		
		case 3:{
			
		}break;
		
		default:{
			
		}break;
	}
}

void Anion_Generator_Control(uint8_t ctl)// 负离子发生器控制
{
	
}

void Infrared_Control(uint8_t ctl)		// 红外理疗灯控制
{
	
}


