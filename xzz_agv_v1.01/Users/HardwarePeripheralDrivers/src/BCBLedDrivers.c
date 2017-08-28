/*----------------------------------------------------------------------------*/
/*
	File Name			:	Bldc_Led.c
	Description			:	
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.22>  V1.0
	Connector Fuction 	:
	Notes	£º
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "BCBLedDriver.h"
	#include "stm32f4xx.h"
	/*---Variable Definition--*/
	/*----LED_GREEN----PA6-----'0' is on,'1' is off */
	/*----LED_RED------PA7-----'0' is on,'1' is off */
	/*---Function Definiton---*/
	/*---Macro Definition-----*/

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	
Description       :	 	
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		
*/
/*----------------------------------------------------------------------------*/
void Led_Configuration(void)
{
//  GPIO_InitTypeDef gpio;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
//	
//	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
//	gpio.GPIO_Mode = GPIO_Mode_OUT;
//	gpio.GPIO_OType = GPIO_OType_PP;
//	gpio.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOA,&gpio);
//    
//    LED_GREEN_OFF();
//    LED_RED_OFF();
		GPIO_InitTypeDef          gpio;
    TIM_TimeBaseInitTypeDef   tim;
    TIM_OCInitTypeDef         oc;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

    gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA,&gpio);
    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2, GPIO_AF_TIM9);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3, GPIO_AF_TIM9);    
    
    tim.TIM_Prescaler = 72;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 255;   //2.5ms
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM9,&tim);
    
    oc.TIM_OCMode = TIM_OCMode_PWM2;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OutputNState = TIM_OutputState_Disable;
    oc.TIM_Pulse = 0;
    oc.TIM_OCPolarity = TIM_OCPolarity_Low;
    oc.TIM_OCNPolarity = TIM_OCPolarity_High;
    oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
    oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
    TIM_OC1Init(TIM9,&oc);
    TIM_OC2Init(TIM9,&oc);
    
    TIM_OC1PreloadConfig(TIM9,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM9,TIM_OCPreload_Enable);
           
    TIM_ARRPreloadConfig(TIM9,ENABLE);
    
    TIM_CtrlPWMOutputs(TIM9,ENABLE);
    
    TIM_Cmd(TIM9,ENABLE);
}
void  setLedLight(unsigned char R,unsigned char G, unsigned char B)
{
	
}
