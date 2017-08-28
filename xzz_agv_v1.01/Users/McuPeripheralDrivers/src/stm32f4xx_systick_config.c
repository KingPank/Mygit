/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f10x_systick_config.c
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
	#include "stm32f10x_systick_config.h"
	/*---Variable Definition--*/
	u32 systick_timer;
	
	static u8 fac_us=0; //us?????
	static u16 fac_ms=0; //ms?????
	/*---Function Definiton---*/
	void systick_init10us(void);
	void systick_initus(void);
	void systick_initms(void);
	void delay_ms(u32 systime);
	void delay_us(u32 systime);
	void delay_10us(u32 systime);
	void TimingDelay_Dcrement(void);
	/*---Macro Definition-----*/

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	systick_initus systick_init10us systick_initms
Description       :	 	
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		
*/
/*----------------------------------------------------------------------------*/
void systick_initus(void)
{
	if(SysTick_Config(SystemCoreClock/1000000))
		while(1);
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
}
void systick_init10us(void)
{
	if(SysTick_Config(SystemCoreClock/100000))
		while(1);
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
}
void systick_initms(void)
{
SysTick->CTRL&=0xfffffffb;//bit2??,?????? HCLK/8
fac_us=SystemCoreClock/8;
fac_ms=(u16)fac_us*1000;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	delay_us delay_10us delay_ms
Description       :	 	
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		
*/
/*----------------------------------------------------------------------------*/
void delay_us(u32 systime)
{
	systick_initus();
	systick_timer=systime;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
    while(systick_timer!=0);
}
void delay_10us(u32 systime)
{
	systick_init10us();
	systick_timer=systime;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
    while(systick_timer!=0);
}
void delay_ms(u32 systime)
{
u32 temp;
SysTick->LOAD=(u32)systime*fac_ms;//????(SysTick->LOAD?24bit)
SysTick->VAL =0x00; //?????
SysTick->CTRL=0x01 ; //????
do
{
 
temp=SysTick->CTRL;
}
while(temp&0x01&&!(temp&(1<<16)));//??????
SysTick->CTRL=0x00; //?????
SysTick->VAL =0X00; //?????
}
void TimingDelay_Dcrement(void)
{
	if(systick_timer!=0x0)
		systick_timer--;
}


