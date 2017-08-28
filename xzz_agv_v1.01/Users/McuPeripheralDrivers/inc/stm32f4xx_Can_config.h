/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_Can_config.H
	Description			:	Communication with the balance board
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.22>  V1.0
	Connector Fuction 	:
	Notes	：
*/
/*----------------------------------------------------------------------------*/
#ifndef __STM32F4XXCANCONFIG_H__
#define __STM32F4XXCANCONFIG_H__
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "stm32f4xx.h"
	/*---Variable Definition--*/
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	CAN1_Configuration
	Description       :	 	
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :		
	*/
	/*----------------------------------------------------------------------------*/
	extern	void CAN1_Configuration(void);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	CAN2_Configuration
	Description       :	 	
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :		
	*/
	/*----------------------------------------------------------------------------*/
	extern	void CAN2_Configuration(void);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      ：	CANSendMsg
	Description       ：
	Input parameter   ：   	Class			Name		Action	
							unsigned int 	ID			CAN ID
							unsigned char 	*str		Tramsit data
							unsigned char 	len			the length of the data
	Output parameter  ：   	Class			Action	
							unsigned char 	1	true
											0	Error
	Author&Date       ：	Jones.Lee & 2015.11.9

	Notes             ：	加了超时提醒
							但是等待中断的感觉不好，这样 能不能这一次的发送中断到下
							一次发送中断等待呢。这样不用麻烦主控了。
	*/
	/*----------------------------------------------------------------------------*/
	extern	unsigned char  CAN1SendMsg(unsigned int ID,unsigned char *str,unsigned char len);
	extern	unsigned char  CAN2SendMsg(unsigned int ID,unsigned char *str,unsigned char len);
	/*---Macro Definition-----*/
/*----------------------------------------------------------------------------*/
#endif 
