/*----------------------------------------------------------------------------*/
/*
	File Name			:	KBFMcuInterface.c
    Description			:	The file is the middle file . It is provide the int-
							-erface to the operate system. It Can easily decrease
							the error of the tranplant.
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2014.12.20>  V2.0
    Connector Fuction 	:
    Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef	__KBFMCUINTERFACEINTERFACE_H__
#define	__KBFMCUINTERFACEINTERFACE_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stdint.h"	
    /*---Macro Definition-----*/
	#ifndef	FALSE
		#define FALSE 		0	
	#endif
	#ifndef TRUE
		#define	TRUE		 1
	#endif
	typedef enum 
	{
		BoardLed1 = 1,
		BoardLed2 = 2,
		BoardLed3 = 4,
		BoardLed4 = 8
	} BoardLed;
	#define		BOARDLED1BIT			0
	#define		BOARDLED2BIT			1
	#define		BOARDLED3BIT			2
	#define		BOARDLED4BIT			3
	typedef enum 
	{
		GpioGrpA = 0,
		GpioGrpB,
		GpioGrpC,
		GpioGrpD,
		GpioGrpE
	} GpioGrp;
	/*---Variable Definition--*/
	extern	uint8_t 	*pKBFMcuCommRecvBuff;
	extern	uint8_t 	*pKBFMcuCommSendBuff;
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	About			 :		Init				
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern	void 		KBFMcuHardConfig(void);
	/*----------------------------------------------------------------------------*/
	/*		
	About			 :		IIC				
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/	
	extern	void		KBFMcuIIcReadByte(uint8_t byAD,uint32_t byRA ,uint8_t* DatatoRead);
	extern	void 		KBFMcuIIcWriteByte(uint8_t byAD,uint32_t byRA, uint8_t DataToWrite);
	extern	void 		KBFMcuIIcWriteBytes(uint8_t byAD, uint32_t byRA,uint8_t * pData, uint8_t byCount);	
	extern	void 		KBFMcuIIcReadBytes(uint8_t byAD, uint32_t byRA,uint8_t * pData, uint8_t byCount);	 
	/*----------------------------------------------------------------------------*/
	/*	
	About			 :		SPI				
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern 	void 		KBFMcuSPIReadByte(uint8_t *pData);
	extern 	void 		KBFMcuSPIWirteByte(uint8_t data);
	extern	uint8_t 	KBFMcuSPIRWByte(uint8_t data);
	extern	void 		KBFMcuSPISetSpeed(uint8_t SpeedSet);
	/*----------------------------------------------------------------------------*/
	/*	
	About			 :		GPIO			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/	
	extern	void  		KBFMcuLedFlash(BoardLed port,uint16_t time,uint16_t cnt);
	extern  void 			KBFMcuLedSFlashs(uint8_t port,uint16_t time,uint16_t cnt);
	extern  void 			KBFMcuLedDFlashs(uint8_t port,uint16_t time,uint16_t cnt);
	extern	void 		KBFMcuGPIOOutPut(GpioGrp gpiogrp, uint8_t num,uint8_t out);
	extern	void 		KBFMcuDelay(uint32_t ms);
  	/*----------------------------------------------------------------------------*/
	/*	
	About			 :		USART			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/
	extern	void 		KBFMcuUsartRecvQueuePoint(void **ppData);
	extern	void 		KBFMcuUsartSendQueuePoint(void **ppData);
	extern	void 		KBFMcuUsartSendBytes(uint8_t *buff,uint32_t cnt);
	extern	void 		KBFMcuUsartSendByte(uint8_t buff);
	extern	void 		KBFMcuprintf(char *fmt, ...);
  	/*----------------------------------------------------------------------------*/
	/*
	About			 :		ADC			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/	
	extern	void 		KBFMcuADCReadData(float *pdata);
  	/*----------------------------------------------------------------------------*/
	/*
	About			 :		ADC			
	Author&Date      :		Jones.Lee & 2014.12.20
	Notes            :	
	*/
	/*----------------------------------------------------------------------------*/		
	extern void KBFMcuPWMPutPut(uint16_t pwm1_val,uint16_t pwm2_val,uint16_t pwm3_val,uint16_t pwm4_val);
/*----------------------------------------------------------------------------*/

#endif /*__KBFMCUINTERFACEINTERFACE_H__*/
