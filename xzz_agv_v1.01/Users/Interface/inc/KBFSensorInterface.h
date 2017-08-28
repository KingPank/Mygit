/*----------------------------------------------------------------------------*/
/*
	File Name			:	KBFMcuInterface.c
    Description			:	The file is used to connect the hard board and the
							app.It makes the users easily to transfer the C Pro.
							You can transfer the App files to any one mcu if the
							mcu have the basic function sush as USART IIC SPI 
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2014.12.20>  V2.0
    Connector Fuction 	:
    Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef 	__KBFSENSORINTERFACE_H__
#define 	__KBFSENSORINTERFACE_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stdint.h"
	#include "KBFGlobalType.h"
    /*---Macro Definition-----*/
	typedef enum 
	{
		Sen_OK  = 0,
		Sen_ERR = 1
	} KBFSenRes;
	typedef enum 
	{
		MPU6050 = 0,
		HMC5883 = 1,
		BMP085 = 2 ,
		NRF24L01 = 3,
		OLED = 4
	} KBFSenVari;

	/*---Variable Definition--*/
	extern   void *pSenNrfRecvBuff;
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	About			 :		Init			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern KBFSenRes  KBFSensorInit(KBFSenVari sen);
	  	/*----------------------------------------------------------------------------*/
	/*
	About			 :		ENABEL			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern KBFSenRes  KBFSENEnable(uint8_t flag);	
	extern KBFSenRes  KBFSDCEnable(uint8_t flag);	
	extern KBFSenRes  KBFNRFEnable(uint8_t flag);
	extern KBFSenRes  KBFMPUEnable(uint8_t flag);
	extern KBFSenRes  KBFBLUEnable(uint8_t flag);
	  	/*----------------------------------------------------------------------------*/
	/*
	About			 :		MPU6050			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern KBFSenRes  KBFGetAccel(AccelInfo *Accel);
	extern KBFSenRes  KBFGetAngle(AngleInfo *Angle);
	extern KBFSenRes  KBFGetGyro(GyroInfo *Gyro);	
	  	/*----------------------------------------------------------------------------*/
	/*
	About			 :		ATC512			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern KBFSenRes  KBFGetSmallStorageValue(uint32_t byRA,uint8_t * pData, uint8_t byCount);
	extern KBFSenRes  KBFSetSmallStorageValue(uint32_t byRA,uint8_t *pData,uint8_t byCount);
	extern KBFSenRes  KBFCheckSmallStorage(void);
	/*----------------------------------------------------------------------------*/
	/*
	About			 :		NRF			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern void  KBFSetCommandBuff(uint8_t *buff,uint32_t length);
	  	/*----------------------------------------------------------------------------*/
	/*
	About			 :		OLED			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern KBFSenRes  KBFOLEDFlush(void);
	extern KBFSenRes  KBFOLEDClear(void);
	
	extern KBFSenRes  KBFOLEDDrawByte(uint8_t px,uint8_t py,uint8_t *byte);
	extern KBFSenRes  KBFOLEDDrawString(uint8_t px,uint8_t py,uint8_t *str);
	extern KBFSenRes  KBFOLEDDrawNum(uint8_t px,uint8_t py,uint8_t num);
	
	extern KBFSenRes  KBFOLEDprintf(uint8_t row,uint8_t col,char *fmt,...);
	extern KBFSenRes  KBFOLEDDrawPoint(uint8_t px,uint8_t py,uint8_t t);
	extern KBFSenRes  KBFOLEDDrawLine(uint8_t orignpx,uint8_t orignpy,uint8_t targetpx,uint8_t targetpy);
	extern KBFSenRes  KBFOLEDDrawFill(uint8_t lefttoppx,uint8_t lefttoppy,uint8_t rightdownpx,uint8_t rightdownpy,uint8_t t);
	/*----------------------------------------------------------------------------*/
#endif	


