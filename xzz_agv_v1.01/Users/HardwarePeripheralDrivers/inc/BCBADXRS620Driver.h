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
#ifndef __BCBADXR620DRIVER_H__
#define __BCBADXR620DRIVER_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include <stdio.h>
	#include "stm32f4xx.h"
	/*---Macro Definition-----*/
	/*---Variable Definition--*/
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	
	Description       :		
	Input parameter   :   Class			Name		Action			
	Output parameter  :   Class			Name		Action								
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern void ADXRS620_Configuration(void);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	
	Description       :		
	Input parameter   :   Class			Name		Action			
	Output parameter  :   Class			Name		Action								
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/	

	extern int8_t ADXRS620_GetValues(uint8_t chnum,float *data);
	#define		ADXR620_YAW			0
	#define		ADXR620_YAWTEM			1
	
	int8_t ADXRS620_GetYaw(float *yaw);
	void ADXRS620_Init_Offset(void);
void ADXRS620_SetOffset(float gx,float gy,float gz);
/*----------------------------------------------------------------------------*/

#endif /* __STM32F10XSPICONFIG_H__ */
