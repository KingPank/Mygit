/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_Adc_config.h
    Description			:	Provide the interface io to the app
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2014.3.6>  V2.0
    Connector Fuction 	:
    Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef __STM32F4xXADCCONFIG_H__
#define __STM32F4xXADCCONFIG_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stm32f4xx.h"
	#include <stdio.h>
	/*---Macro Definition-----*/	
	#define ADCCHNNELCNT 	4 
	#define ADCCHANNELNUM 	4
    /*---Variable Definition--*/
	extern vu16 AD_Value[ADCCHNNELCNT][ADCCHANNELNUM]; 																    
    /*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	ADC_Configuration
	Description       :	 	Configurate the adc.
	
	Input parameter   :   	Class			Name		Action	
	
	Output parameter  :   	Class			Name		Action	
						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :		The code is copyed in the net. Then, there is using the
							DMA(Direct Memory Address)
	*/
	/*----------------------------------------------------------------------------*/
	extern void ADC_Configuration(void);
	extern void ADCReadData(float *data,unsigned char channel);
/*----------------------------------------------------------------------------*/
#endif

