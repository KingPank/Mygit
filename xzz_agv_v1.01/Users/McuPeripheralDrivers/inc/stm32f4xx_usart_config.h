/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_usart_config.h
	Description			:		
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.4.28>  V1.0
	Connector Fuction 	:
	Notes				:	There are two usart the usart one is used to debugging
							The other is used to recv the signal from the dji re-
							-mote
*/
/*----------------------------------------------------------------------------*/
#ifndef __STM32F4XXUSARTCONFIG_H__
#define __STM32F4XXUSARTCONFIG_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stm32f4xx.h"
    /*---Macro Definition-----*/
    #define	USART1_SendByte(data)  			USART_SendByte(USART1,data)
	#define	USART1_SendBytes(pdata,cnt)  	USART_SendBytes(USART1,pdata,cnt)
	#define USART1_Printf(fmt)  			USART_Printf(USART1,char *fmt, ...)
		 #define	USART2_SendByte(data)  			USART_SendByte(USART2,data)
	#define	USART2_SendBytes(pdata,cnt)  	USART_SendBytes(USART2,pdata,cnt)
	#define USART2_Printf(fmt)  			USART_Printf(USART2,char *fmt, ...)
  
  
	#define	USART3_SendByte(data)  			USART_SendByte(USART3,data)
	#define	USART3_SendBytes(pdata,cnt)  	USART_SendBytes(USART3,pdata,cnt)
	#define USART3_Printf(fmt)  			USART_Printf(USART3,char *fmt, ...)
	/*---Variable Definition--*/
	extern	u8	pUsartRecvBuff[200];
	extern	u8	pUsartSendBuff[200];
	
	
extern	 u8 dma_RxBuffer[10];
extern   u8 dma_TxBuffer[10];
	
extern   u8	dma_u1_RxBuffer[13];
extern	u8 dma_u1_TxBuffer[15];
	
extern	void SendBytesInfoProc(u8* pSendInfo, u16 nSendCount)  ;
	extern	short int  sbus_channel_temp[15];  //  temp sbus decode channel data
	extern unsigned char sbus_rx_buffer[18];
	
extern	 void u1_SendBytesInfoProc(u8* pSendInfo, u16 nSendCount);
	
	
	
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	USART1_Configuration
	Description       :		
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern	void USART1_Configuration(void);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	USART2_Configuration
	Description       :		
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern	void USART2_Configuration(void);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	USART2_Configuration
	Description       :		
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern	void USART3_Configuration(void);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	USART_SendByte
	Description       :		
	Input parameter   :   	Class			Name		Action
							USART_TypeDef* 	USARTx 		The using USART Bus()
							u8 				data		the data to Send
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern	void USART_SendByte(USART_TypeDef* USARTx, u8 data);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	USART_SendBytes
	Description       :		
	Input parameter   :   	Class			Name		Action
							USART_TypeDef* 	USARTx 		The using USART Bus()
							uint8_t 		data		the data to Send
							uint8_t			length		the length of the data
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern  void USART_SendBytes(USART_TypeDef* USARTx, u8 *data,u32 cnt);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	USART_Printf
	Description       :		like printf
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern  void USART_Printf(USART_TypeDef* USARTx,char *fmt, ...) ;
	/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

#endif /* __STM32F4XXUSARTCONFIG_H__ */

//  extern void AGVRecv_USART1_Data(u8 data);
	extern void EXTI_Configuration(void);
	extern  void AGVRecvData(u8 data);
