/*----------------------------------------------------------------------------*/
/*
	File Name			:	BCBMUP6050DRIVER.c
	Description			:	
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.33>  V1.0
	Connector Fuction 	:
	Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef __BCBMPU6050DRIVER_H__
#define __BCBMPU6050DRIVER_H__
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "stm32f4xx.h"
	/*---Variable Definition--*/
	extern float Acc1G_Values;
	/*---Function Definiton---*/
	extern	void 			MPU6050_Configuation(void); 
	extern	uint8_t 	MPU6050_TestConnection(void);
	extern	void 			MPU6050_getMotion6(int16_t* accgyroval) ;
	extern	uint8_t 	MPU6050_GetDeviceID(void); 
	extern	void 			MPU6050_InitGyro_Offset(void);
	extern	void 			MPU6050_GetValues(float* accgyroval); 
	
	extern	short MPU6050_GetDeviceWD(void);
  extern void MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
  extern void MPU_Get_Accelerometer(float *axc);
	
	
	
	extern  void      MPU6050_SetGyroOffset(float gx,float gy,float gz);
	/*---Macro Definition-----*/

/*----------------------------------------------------------------------------*/

#endif
