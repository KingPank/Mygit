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
#ifndef __BCBAD7689DRIVER_H__
#define __BCBAD7689DRIVER_H__
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
							uint8_t 								
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern void AD7689_Configuration(void);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	
	Description       :		
	Input parameter   :   Class			Name		Action			
	Output parameter  :   Class			Name		Action	
							uint8_t 								
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/	
	extern int8_t AD7689_GetOneResult(uint8_t chnum,uint16_t *res);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	
	Description       :		
	Input parameter   :   Class			Name		Action			
	Output parameter  :   Class			Name		Action	
							uint8_t 								
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/		
	extern int8_t AD7689_GetAllResults(uint16_t res[]);
//	#define		AD7689FIRSTINTNUM			1
//	#define		AD7689SECONDINTNUM			1
//	#define		AD7689THIRDINTNUM			1
//	#define		AD7689FOURTHINTNUM			1
//	#define		AD7689FIFTHINTNUM			1
//	#define		AD7689SIXTHINTNUM			1	
//	#define AD7689_GetFirstResult(res)	 	AD7689_GetOneResult(1,res);
//	#define AD7689_GetSecondResult(res)	 	AD7689_GetOneResult(2,res);
//	#define AD7689_GetThirdResult(res)	 	AD7689_GetOneResult(3,res);
//	#define AD7689_GetFourthResult(res)		AD7689_GetOneResult(,res);
//	#define AD7689_GetFifthResult(res)	 	AD7689_GetOneResult(,res);
//	#define AD7689_GetSixthResult(res)	 	AD7689_GetOneResult(,res);
//	#define AD7689_GetSixthResult(res)	 	AD7689_GetOneResult(,res);
/*----------------------------------------------------------------------------*/
#endif /* __STM32F10XSPICONFIG_H__ */
