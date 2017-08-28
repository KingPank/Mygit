/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_Bsp_config.c
    Description			:	
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2014.12.20>  V2.0
    Connector Fuction 	:
    Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef __STM32F4XXBSPCONFIG_H__
#define __STM32F4XXBSPCONFIG_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stm32f4XX.h"
	
//	#include "stm32f4xx_systick_config.h"
	#include "stm32f4xx_gpio_config.h"
	#include "stm32f4xx_usart_config.h"
//	#include "stm32f4xx_time_config.h"
	#include "stm32f4xx_Can_config.h"
	#include "stm32f4xx_iic_config.h"
	#include "stm32f4xx_spi_config.h"
//	#include "stm32f4xx_Adc_config.h"
	#include "stm32f4xx_time_config.h"
//	#include "stm32f4xx_exti_config.h"
#include "stm32f4xx_flash_config.h"

    /*---Variable Definition--*/
    /*---Macro Definition-----*/
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	Bsp_Configuration
	Description       :	 	
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :		
	*/
	/*----------------------------------------------------------------------------*/
	extern void  Bsp_Configuration(void);
/*----------------------------------------------------------------------------*/


#endif /*__STM32F4XXBSPCONFIG_H__ */
