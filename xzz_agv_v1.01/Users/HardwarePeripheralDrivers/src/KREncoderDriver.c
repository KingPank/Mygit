/*----------------------------------------------------------------------------*/
/*
    File Name           :   KREncoderDriver.c
    Description         :   Encoder Driver
    Author              :   JonesLee 
    Copyright           :   Copyright (C) 2015,WellCasa.Inc All Right Reserved
    Version&Date        :   V0.3 2015-11-1
    Notes               :
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
	#include "stm32f4xx.h"
	#include "KREncoderDriver.h"
	#include "KRGlobalType.h"
    /*---Variable Definition--*/
    /*---Function Definiton---*/
    /*---Macro Definition-----*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	Encoder_Configuration
Description       :		
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		JonesLee   2015-11-1
Notes             :	
*/
/*----------------------------------------------------------------------------*/
Result_t Encoder_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef        GPIO_InitStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;


//	/*encoder Init*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);    
//    gpio.GPIO_Pin =  GPIO_Pin_4;
//    gpio.GPIO_Mode = GPIO_Mode_IN;
//    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    gpio.GPIO_Speed = GPIO_Speed_100MHz;
//    GPIO_Init(GPIOB,&gpio);
//	
//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource4);   
//    exti.EXTI_Line = EXTI_Line4;
//    exti.EXTI_Mode = EXTI_Mode_Interrupt;
//    exti.EXTI_Trigger = EXTI_Trigger_Rising;
//    exti.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&exti);
//	  return RES_OK;	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;       
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_Period=65535;   
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;  
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI1,TIM_ICPolarity_BothEdge,0);	
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 6;//ICx_FILTER;
//	TIM_ICInit(TIM3, &TIM_ICInitStructure);	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//	TIM_ClearFlag(TIM3,TIM_FLAG_Update); 
	TIM_SetCounter(TIM3,0x7fff);
	TIM_Cmd(TIM3,ENABLE);
	return RES_OK;
}
Result_t Zero_Configuration(void)
{
    GPIO_InitTypeDef  gpio;
    EXTI_InitTypeDef  exti;
	/*Zero Init*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);    
    gpio.GPIO_Pin =  GPIO_Pin_2;
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&gpio);
  
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource2);   
    exti.EXTI_Line = EXTI_Line2;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising;
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
	return RES_OK;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	OpenEncoder CloseEncoder
Description       :		
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		JonesLee   2015-11-1
Notes             :	
*/
/*----------------------------------------------------------------------------*/
Result_t OpenEncoder()
{
//	EXTI_InitTypeDef  exti;
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource4);   
//    exti.EXTI_Line = EXTI_Line4;
//    exti.EXTI_Mode = EXTI_Mode_Interrupt;
//    exti.EXTI_Trigger = EXTI_Trigger_Rising;
//    exti.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&exti);
	TIM_Cmd(TIM3,ENABLE);
	return RES_OK;
}
Result_t CloseEncoder()
{
//	EXTI_InitTypeDef  exti;
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource4);   
//    exti.EXTI_Line = EXTI_Line4;
//    exti.EXTI_Mode = EXTI_Mode_Interrupt;
//    exti.EXTI_Trigger = EXTI_Trigger_Rising;
//    exti.EXTI_LineCmd = DISABLE;
//    EXTI_Init(&exti);
	TIM_Cmd(TIM3,DISABLE);
	return RES_OK;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	OpenZero CloseZero
Description       :		
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		JonesLee   2015-11-1
Notes             :	
*/
/*----------------------------------------------------------------------------*/
Result_t OpenZero()
{
	EXTI_InitTypeDef  exti;
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource2);   
    exti.EXTI_Line = EXTI_Line2;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising;
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
	return RES_OK;
}
Result_t CloseZero()
{
	EXTI_InitTypeDef  exti;
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD,EXTI_PinSource2);   
    exti.EXTI_Line = EXTI_Line2;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising;
    exti.EXTI_LineCmd = DISABLE;
    EXTI_Init(&exti);
	return RES_OK;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	GetEncoderAngle
Description       :		Get Encoder Angle
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		JonesLee   2015-11-1
Notes             :	
*/
/*----------------------------------------------------------------------------*/
Result_t GetEncoderAngle(unsigned short int  *angle)
{
	*angle = (TIM3->CNT - 0x7fff);
	return RES_OK;
}
