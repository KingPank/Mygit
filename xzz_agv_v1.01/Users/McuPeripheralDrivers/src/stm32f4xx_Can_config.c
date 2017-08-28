/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_Can_config.c
	Description			:	Communication with the balance board
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.33>  V1.0
	Connector Fuction 	:
	Notes	：
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "stm32f4xx_Can_config.h"
	#include "BCBGlobalFunc.h"
	/*---Variable Definition--*/
	/*---Function Definiton---*/
    void   CAN1_Configuration(void);
    void   CAN2_Configuration(void);
	unsigned char  CAN1SendMsg(unsigned int ID,unsigned char *str,unsigned char len);
	unsigned char  CAN2SendMsg(unsigned int ID,unsigned char *str,unsigned char len);
	/*---Macro Definition-----*/
	#define		CanDelayUs(t) 	delay_us(t)
/*----------------------------------------------------------------------------*/

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
void CAN1_Configuration(void)
{
    CAN_InitTypeDef        can;
    CAN_FilterInitTypeDef  can_filter;
    GPIO_InitTypeDef       gpio;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	#ifndef	DJIBOARD
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);
		gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		gpio.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOB, &gpio);
    #else
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
		gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11;
		gpio.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOA, &gpio);
	#endif
    CAN_DeInit(CAN1);
    CAN_StructInit(&can);
    can.CAN_TTCM = DISABLE;
    can.CAN_ABOM = DISABLE;
    can.CAN_AWUM = DISABLE;
    can.CAN_NART = DISABLE;
    can.CAN_RFLM = DISABLE;
    can.CAN_TXFP = ENABLE;
    can.CAN_Mode = CAN_Mode_Normal;
    can.CAN_SJW  = CAN_SJW_1tq;
    can.CAN_BS1 = CAN_BS1_9tq;
    can.CAN_BS2 = CAN_BS2_4tq;
    can.CAN_Prescaler = 3;   		//CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN1, &can);

	can_filter.CAN_FilterNumber=0;
	can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh=0x0000;
	can_filter.CAN_FilterIdLow=0x0000;
	can_filter.CAN_FilterMaskIdHigh=0x0000;
	can_filter.CAN_FilterMaskIdLow=0x0000;
	can_filter.CAN_FilterFIFOAssignment=0;
	can_filter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&can_filter);
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE); 
}
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
void CAN2_Configuration(void)
{
    CAN_InitTypeDef        can;
    CAN_FilterInitTypeDef  can_filter;
    GPIO_InitTypeDef       gpio;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2); 

    gpio.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12 ;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &gpio);


    CAN_DeInit(CAN2);
    CAN_StructInit(&can);

    can.CAN_TTCM = DISABLE;
    can.CAN_ABOM = DISABLE;    
    can.CAN_AWUM = DISABLE;    
    can.CAN_NART = DISABLE;    
    can.CAN_RFLM = DISABLE;    
    can.CAN_TXFP = ENABLE;     
    can.CAN_Mode = CAN_Mode_Normal; 
    can.CAN_SJW  = CAN_SJW_1tq;
    can.CAN_BS1 = CAN_BS1_9tq;
    can.CAN_BS2 = CAN_BS2_4tq;
    can.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN2, &can);
    
    can_filter.CAN_FilterNumber=14;
    can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
    can_filter.CAN_FilterScale=CAN_FilterScale_32bit;
    can_filter.CAN_FilterIdHigh=0x0000;
    can_filter.CAN_FilterIdLow=0x0000;
    can_filter.CAN_FilterMaskIdHigh=0x0000;
    can_filter.CAN_FilterMaskIdLow=0x0000;
    can_filter.CAN_FilterFIFOAssignment=0;//the message which pass the filter save in fifo0
    can_filter.CAN_FilterActivation=ENABLE;
    CAN_FilterInit(&can_filter);
    
    CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
}

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

Notes             ：	2015.11.9
						加了超时提醒
						但是等待中断的感觉不好，这样 能不能这一次的发送中断到下
						一次发送中断等待呢。这样不用麻烦主控了。

*/
/*----------------------------------------------------------------------------*/
unsigned char  CAN1SendMsg(unsigned int ID,unsigned char *str,unsigned char len)
{
		CanTxMsg tx_message;
		unsigned char i = 0;
		unsigned int sendtimeout = 100;
		tx_message.RTR = CAN_RTR_Data;  		//数据帧
		tx_message.IDE = CAN_Id_Standard;    	//标准帧
		tx_message.DLC = len;          			//帧长度为4  
		tx_message.StdId = ID;
		for(i = 0; i < len; i++)
		{
			tx_message.Data[i] = str[i];			
		}
		CAN_Transmit(CAN1,&tx_message);
		while(Can1SendFlag == 0)
		{
			if( sendtimeout == 0)
			{
				return 0;
			}
			else
			{
				CanDelayUs(1);
				sendtimeout--;
			}
		}
		Can1SendFlag = 0;
		return 1;
}
unsigned char  CAN2SendMsg(unsigned int ID,unsigned char *str,unsigned char len)
{
		CanTxMsg tx_message;
		unsigned char i = 0;
		unsigned int sendtimeout = 100;
		tx_message.RTR = CAN_RTR_Data;  		//数据帧
		tx_message.IDE = CAN_Id_Standard;    	//标准帧
		tx_message.DLC = len;          			//帧长度为4  
		tx_message.StdId = ID;
		for(i = 0; i < len; i++)
		{
			tx_message.Data[i] = str[i];			
		}
		Can1SendFlag = 0;
		CAN_Transmit(CAN2,&tx_message);
		while(Can1SendFlag == 0)
		{
			if( sendtimeout == 0)
			{
				return 0;
			}
			else
			{
				CanDelayUs(1);
				sendtimeout--;
			}
		}
		
		return 1;
}
