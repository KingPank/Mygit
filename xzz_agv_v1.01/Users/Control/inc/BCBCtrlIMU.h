/*----------------------------------------------------------------------------*/
/*
	File Name			:	
	Description			:		
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.4.28>  V1.0
	Connector Fuction 	:
	Notes				:	
*/
/*----------------------------------------------------------------------------*/
#ifndef __BCBCTRLIMU_H__
#define __BCBCTRLIMU_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stm32f4xx.h"
	#include <math.h>
	#include "BCBGlobalType.h"
    /*---Macro Definition-----*/
	#define M_PI  (float)3.1415926535
	/*---Variable Definition--*/
	extern float mygetqval[9];	
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	
	Description       :		
	Input parameter   :   	Class			Name		Action
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	void IMU_init(void); //≥ı ºªØ
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	
	Description       :		
	Input parameter   :   	Class			Name		Action
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	void IMU_getYawPitchRoll(Angle_t *angle,Gyro_t *gyro,float period);
	void CalcIMUInfo(Angle_t *angle,Gyro_t *gyro,float dt);
/*----------------------------------------------------------------------------*/
#endif

