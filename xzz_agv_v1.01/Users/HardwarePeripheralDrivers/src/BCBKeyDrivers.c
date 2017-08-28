/*----------------------------------------------------------------------------*/
/*
	File Name			:	Bldc_Key.c
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
	#include "BCBKeyDriver.h"
	#include "stm32f4xx.h"
	/*---Variable Definition--*/
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
void Key_Configuration()
{
	
	  GPIO_InitTypeDef  gpio;
    EXTI_InitTypeDef  exti;
    NVIC_InitTypeDef  nvic;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
   
    gpio.GPIO_Pin = GPIO_Pin_3;   
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &gpio);
    
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource3);
    
    exti.EXTI_Line = EXTI_Line3;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Falling;
    exti.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti);
    
    nvic.NVIC_IRQChannel = EXTI3_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);



    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);
   
    gpio.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;   
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &gpio);

	
}
void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3))
    {
        EXTI_ClearITPendingBit(EXTI_Line3);

    }
}
int Read_Key()
{
	int a;
	a = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
	//a &=0x01;
	return a;
}
int Read_Dial()
{
	int a;
	a = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1);
	a <<=1;
	a += GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0);
	a &=0x03;
	return a;
	
}
