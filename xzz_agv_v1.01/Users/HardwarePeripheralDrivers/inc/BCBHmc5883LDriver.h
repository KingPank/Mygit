/*----------------------------------------------------------------------------*/
/*
	File Name			:	BCBHmc5883lDriver.h
	Description			:	
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.33>  V1.0
	Connector Fuction 	:
	Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef __BCBHMC5883LDRIVER_H__
#define __BCBHMC5883LDRIVER_H__
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "stm32f4xx.h"
	/*---Variable Definition--*/

	/*---Function Definiton---*/
	extern	void HMC5883L_Configuration(void);	//初始化
	
	extern	void HMC5883L_SetUp(void);	//初始化
	
	extern	void HMC58X3_getID(char id[3]);	//读芯片ID
	
	extern	void HMC58X3_getValues(int16_t *x,int16_t *y,int16_t *z); //读ADC
	
	extern	void HMC58X3_GetValues(float *arry); //IMU 专用的读取磁力计值
	
	extern	void HMC58X3_getlastValues(int16_t *x,int16_t *y,int16_t *z);

	/*---Macro Definition-----*/

/*----------------------------------------------------------------------------*/
#endif
