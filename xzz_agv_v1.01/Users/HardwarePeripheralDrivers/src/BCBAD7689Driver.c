/*----------------------------------------------------------------------------*/
/*
	File Name			:	BCBAD7689Driver.c
	Description			:	
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.22>  V1.0
	Connector Fuction 	:
	Notes	：
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "BCBAD7689Driver.h"
	#include "stm32f4xx_spi_config.h"
	#include "stm32f4xx.h"
	#include "BCBGlobalFunc.h"
	/*---Variable Definition--*/
	static uint16_t  AD7689ConfigBuf[8]={

																		(0x3c39|(0x0000<<7)), //通道0的CFG配置值
																		(0x3c39|(0x0001<<7)), //通道1的CFG配置值
																		(0x3c39|(0x0002<<7)), //通道2的CFG配置值
																		(0x3c39|(0x0003<<7)), //通道3的CFG配置值
																		(0x3c39|(0x0004<<7)), //通道4的CFG配置值	
																		(0x3c39|(0x0005<<7)), //通道5的CFG配置值
																		(0x3c39|(0x0006<<7)), //通道6的CFG配置值
																		(0x3c39|(0x0007<<7))  //通道7的CFG配置值
																		};
	/*---Function Definiton---*/
	/*---Macro Definition-----*/
	#define	CSH			GPIOA->ODR |= GPIO_Pin_4
	#define	CSL			GPIOA->ODR &= ~GPIO_Pin_4
	#define	AD7689_RW(data)				SPI1_RW(data)
	#define AD7689_DelayUs(us)		delay_us(us)
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 		AD7689_Configuration
Description       :	 	
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :			Jones.Lee & 2014.12.20
Notes             :		
*/
/*----------------------------------------------------------------------------*/
void AD7689_Configuration()
{
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_4;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);
}
int8_t AD7689_GetOneResult(uint8_t chnum,uint16_t *res)
{

	uint16_t Config = 0;
	uint16_t  ADC_Value = 0x00;
	if(chnum > 8)
	{
		return -1;
	}
	Config = AD7689ConfigBuf[chnum];
	Config = Config << 2;
	Config |= 0x8000;
	CSL;
	ADC_Value = AD7689_RW(Config >> 8);
	ADC_Value = ADC_Value << 8;						//ADC结果高字节
	ADC_Value |= AD7689_RW(Config & 0x00ff);
	CSH;
	AD7689_DelayUs(5);
	
	*res = ADC_Value;
	return 1;
	
}
int8_t AD7689_GetAllResults(uint16_t res[])
{
		uint16_t Config = 0;
	uint16_t  ADC_Value = 0x00;

	for(int i = 0 ; i < 8; i++)
	{
		Config = AD7689ConfigBuf[i];
		Config = Config << 2;
		Config |= 0x8000;
		CSL;
		ADC_Value = AD7689_RW(Config >> 8);
		ADC_Value = ADC_Value << 8;						//ADC结果高字节
		ADC_Value |= AD7689_RW(Config & 0x00ff);
		CSH;
		AD7689_DelayUs(1);
		res[i] = ADC_Value;
		return 1;
		
	}
	return 1;
}
