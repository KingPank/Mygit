/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f10x_spi_config.c
    Description			:	
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2014.12.20>  V2.0
    Connector Fuction 	:
    Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef __STM32F10XSPICONFIG_H__
#define __STM32F10XSPICONFIG_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include <stdio.h>
	#include "stm32f4xx.h"
    /*---Macro Definition-----*/
	#define SPI_SPEED_LOW   0
	#define SPI_SPEED_HIGH  1
	/*---Variable Definition--*/
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	SPI_RW
	Description       :		Read and Write
	Input parameter   :   	Class			Name		Action	
							SPI_TypeDef *	SPI	  		The using SPI Bus(SPI1 SPI2)
							uint8_t 		data		wirting data
	Output parameter  :   	Class			Name		Action	
							uint8_t 					reading data					
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern u8 SPI_RW(SPI_TypeDef *SPI,u8 data);
	#define		SPI1_RW(data)  	SPI_RW(SPI1,data)
	#define		SPI2_RW(data)  	SPI_RW(SPI2,data)
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	SPI_SetSpeed
	Description       :		Configurate the all gpio.
	Input parameter   :   	Class			Name		Action
							SPI_TypeDef *	SPI	  		The using SPI Bus(SPI1 SPI2)
							uint8_t			SpeedSet	The speed of the spi
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
		extern 	void SPI_SetSpeed(SPI_TypeDef *SPI,uint8_t SpeedSet);
	#define		SPI1_SetSpeed(speed)  	SPI_SetSpeed(SPI1,speed)
	#define		SPI2_SetSpeed(speed)  	SPI_SetSpeed(SPI2,speed)
	 /*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	SPI_Configuration
	Description       :		Configurate the using SPI.
	Input parameter   :   	Class			Name		Action
							SPI_TypeDef *	SPI	  		The using SPI Bus(SPI1 SPI2)	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern void SPI_Configuration(SPI_TypeDef *SPI);
	#define		SPI1_Configuration()  	SPI_Configuration(SPI1)
	#define		SPI2_Configuration()  	SPI_Configuration(SPI2)
/*----------------------------------------------------------------------------*/

#endif /* __STM32F10XSPICONFIG_H__ */
