/*----------------------------------------------------------------------------*/
/*
	File Name			:	

	Description			:

	Author				:  	
	Copyright			: 	
	Version&Date		: 	
	Notes		  	 	:
*/
/*----------------------------------------------------------------------------*/
#ifndef __MTSPROTOCOL_H__
#define __MTSPROTOCOL_H__
/*----------------------------------------------------------------------------*/
	#pragma anon_unions
    /*---Head Files---*/
	#include "stm32f4xx.h"
	#include <stdio.h>
	#include <math.h>
	#include <string.h>
	#include <stdarg.h>
	#include "MTSProtocol.h"
    /*---Macro Definition-----*/
	#ifndef __BCBGLOBALTYPE_H__
	typedef union
	{
		float				fdata;
		unsigned char 	udata[4];
	}KBunfloat;
	#endif
    /*---Variable Definition--*/
    /*---Function Definiton---*/
	extern	void MTSProtoclInit(void);
	extern void MTSRecvData(unsigned char data);
	extern void UsartSendCmd(unsigned int millsecond);
/*-------------------------------------------------------------------*/
#endif
