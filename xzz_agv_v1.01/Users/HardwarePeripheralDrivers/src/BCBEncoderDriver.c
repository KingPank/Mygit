#include "BCBEncoderDriver.h"

#include "stm32f4xx.h"
void Encoder_Configuration(void);
void Encoder_Configuration(void)
{
    GPIO_InitTypeDef gpio;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3  | RCC_APB1Periph_TIM2 ,ENABLE);
    
    gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC,&gpio);
    
    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOA,&gpio);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0,  GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1,  GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6,  GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7,  GPIO_AF_TIM3);
	
		TIM_TimeBaseInitStructure.TIM_Period=65535;   
		TIM_TimeBaseInitStructure.TIM_Prescaler=0;  
		TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
		TIM_TimeBaseInitStructure.TIM_Period=65535;   
		TIM_TimeBaseInitStructure.TIM_Prescaler=0;  
		TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);


    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
		TIM_SetCounter(TIM3,0x7fff);
		TIM_SetCounter(TIM2,0x7fff);
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}
void GetEncoder( int *dx,int *dy)
{
	*dx = (TIM2->CNT - 0x7fff);
	*dy = (TIM3->CNT - 0x7fff);
	TIM2->CNT  = 0x7fff;
	TIM3->CNT  = 0x7fff;
}
