

#include "NTC.h"
#include "stm32f0xx_hal.h"


#define TEMP_TAB_MAX	74

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

uint16_t const Temp_Tab[TEMP_TAB_MAX]={
0x7fff,3605,3582,3557,3533,3507,3481,3454,3426,3397, //-20--11
3368,3338,3307,3276,3243,3211,3177,3143,3108,3073,  //-10--1
3037,3001,2964,2927,2889,2850,2812,2773,2733,2694,  //0-9
2654,2614,2573,2533,2492,2452,2411,2370,2329,2289,  //10-19
2248,2208,2167,2127,2087,2048,2008,1969,1930,1892,  //20-29
1854,1816,1778,1742,1705,1669,1634,1598,1564,1530,  //30-39
1496,1463,1431,1399,1368,1337,1306,1277,1247,1219,  //40-49
1191,1163,1136,0,    //50-53
};

static uint16_t   aADCxConvertedData_0[4];
uint8_t temperature[2];
uint8_t adc_en;
uint16_t adc_ms;


uint8_t ADC_to_Temp(uint16_t adc_temp)
{
	uint8_t r_temp = 0xFF;
	uint16_t i;
	
	for(i = 0; i < (TEMP_TAB_MAX -1); i++)
	{
		if((adc_temp <= Temp_Tab[i]) && (adc_temp > Temp_Tab[i+1]))
		{
			if(i >= 20)
			{
				r_temp = i - 20;
			}
			else
			{
				r_temp = 20 - i;
				r_temp &= 0x80;
			}
			return r_temp;
		}
	}
	return r_temp;
}


uint16_t ADC_to_Voltage(uint16_t adc_temp)
{
	uint32_t tmp_1, tmp_2, tmp_3;
	
	tmp_1 = (uint32_t)adc_temp * 1005 * 34;
	tmp_2 = tmp_1 / 4096;
	tmp_3 = ((tmp_2 % 10) / 5 ) * 10 + tmp_2;
	tmp_3 /= 10;
	
	return (uint16_t)(tmp_3);
}

void ADC_Systick(void)
{
	if(0 == adc_ms)
	{
		adc_en = 1;
	}
	adc_ms++;
	if(1000 <= adc_ms)
	{
		adc_ms = 0;
	}
}
uint8_t rt_temp;
uint8_t Tempereture_ADC(void)
{
	if(1 == adc_en)
	{
		uint8_t tmp[2];
		adc_en = 0;
		if (HAL_ADC_Start_DMA(&hadc,
		(uint32_t *)aADCxConvertedData_0,
		4
		) != HAL_OK)
		{
			Error_Handler();
		}
		
		tmp[0] = ADC_to_Temp(aADCxConvertedData_0[0])-4;
		tmp[1] = ADC_to_Temp(aADCxConvertedData_0[1])-4;
		
		rt_temp = (tmp[0] < tmp[1])?(tmp[1] - tmp[0]):(tmp[0] - tmp[1]);
		if(5 < rt_temp)
		{
			rt_temp = 0xEE;
		}
		else
		{
			rt_temp = ((tmp[0] + tmp[1]) >> 1);
		}
	}
	return rt_temp;
}


/* ADC init function */
void MX_ADC_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel to be converted. 
    */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel to be converted. 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}



