/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f10x_systick_config.h
	Description			:	
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.22>  V1.0
	Connector Fuction 	:
	Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef __STM32F10XSYSTICKCONFIG_H__
#define __STM32F10XSYSTICKCONFIG_H__
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include <stm32f10x.h>
	/*---Variable Definition--*/

	/*---Function Definiton---*/
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
	extern	void systick_init10us(void);
	extern	void systick_initus(void);
	extern	void systick_initms(void);
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
	extern	void delay_ms(u32 systime);
	extern	void delay_us(u32 systime);
	extern	void delay_10us(u32 systime);
	extern	void TimingDelay_Dcrement(void);
	/*---Macro Definition-----*/

/*----------------------------------------------------------------------------*/





#endif




