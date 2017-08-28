/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_usart_config.c
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
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stm32f4xx_usart_config.h"
	#include "stm32f4xx_it.h"
	#include <string.h>
	#include <stdio.h>
	#include <stdarg.h>  
//	#include "queue.h"
//#include "BCBGlobalType.h"
//#include "BCBGlobalFunc.h"
    /*---Macro Definition-----*/
	/*---Variable Definition--*/
	u8	pUsartRecvBuff[200];
	u8	pUsartSendBuff[200];
	short int  sbus_channel_temp[15] = {0};  //  temp sbus decode channel data
	unsigned char sbus_rx_buffer[18];
	/*---Function Definiton---*/
	void USART1_Configuration(void);
	void USART2_Configuration(void);
	void USART3_Configuration(void);
	void EXTI_Configuration(void);
	void USART_SendByte(USART_TypeDef* USARTx, u8 data);
	void UART_SendBuffer(USART_TypeDef* USARTx, char *buffer);
	void USART_Printf(USART_TypeDef* USARTx,char *fmt, ...) ;
	void USART_SendBytes(USART_TypeDef* USARTx, u8 *data,u32 cnt);
	void SendBytesInfoProc(u8* pSendInfo, u16 nSendCount)  ;
 void u1_SendBytesInfoProc(u8* pSendInfo, u16 nSendCount);
	
 u8 dma_RxBuffer[10];
 u8 dma_TxBuffer[10];

	u8 dma_u1_RxBuffer[13];
	u8 dma_u1_TxBuffer[15];
	
	 u8 Rx_Buffer[50];
//	void AGVRecv_USART1_Data(u8 data);//上位机发送指令解析
	
//  void AGVRecvData(u8 data);
/*----------------------------------------------------------------------------*/
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
void USART1_Configuration()                                                        
{
	USART_InitTypeDef usart1;
	GPIO_InitTypeDef  gpio;
//	NVIC_InitTypeDef  nvic;
	
	DMA_InitTypeDef  DMA_u1_InitStructure_RX;
  DMA_InitTypeDef  DMA_u1_InitStructure_TX;
	NVIC_InitTypeDef  nvic_u1_Rx;
	NVIC_InitTypeDef  nvic_u1_Tx;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9 ,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); 

	gpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	//  gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpio);

	usart1.USART_BaudRate = 115200;
	usart1.USART_WordLength = USART_WordLength_8b;
	usart1.USART_StopBits = USART_StopBits_1;
	usart1.USART_Parity = USART_Parity_No;
	usart1.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	usart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1,&usart1);

//	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
//	USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
//	USART_Cmd(USART1,DISABLE);
//	
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
		/*打开USART中断*/
	USART_ITConfig(USART1,USART_IT_TC,DISABLE);  
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(USART1,USART_IT_IDLE,DISABLE);
		
		
//	nvic.NVIC_IRQChannel = USART1_IRQn;
//	nvic.NVIC_IRQChannelPreemptionPriority = 0;
//	nvic.NVIC_IRQChannelSubPriority = 2;
//	nvic.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&nvic);


  USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  USART_Cmd(USART1, ENABLE);

	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2????   
	DMA_DeInit(DMA2_Stream5);  
    while (DMA_GetCmdStatus(DMA2_Stream5) != DISABLE);//??DMA???   
    /* ?? DMA Stream */  
   DMA_u1_InitStructure_RX.DMA_Channel = DMA_Channel_4;  //????  
    DMA_u1_InitStructure_RX.DMA_PeripheralBaseAddr = (u32)&USART1->DR;//DMA????  
    DMA_u1_InitStructure_RX.DMA_Memory0BaseAddr = (u32) dma_u1_RxBuffer;//DMA ???0??  
    DMA_u1_InitStructure_RX.DMA_DIR = DMA_DIR_PeripheralToMemory ;//????????  
    DMA_u1_InitStructure_RX.DMA_BufferSize = 13;//?????   
    DMA_u1_InitStructure_RX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//???????  
    DMA_u1_InitStructure_RX.DMA_MemoryInc = DMA_MemoryInc_Enable;//???????  
    DMA_u1_InitStructure_RX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//??????:8?  
    DMA_u1_InitStructure_RX.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//???????:8?  
    DMA_u1_InitStructure_RX.DMA_Mode = DMA_Mode_Circular;// ??????   
    DMA_u1_InitStructure_RX.DMA_Priority = DMA_Priority_Medium;//?????  
    DMA_u1_InitStructure_RX.DMA_FIFOMode = DMA_FIFOMode_Disable;           
    DMA_u1_InitStructure_RX.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;  
    DMA_u1_InitStructure_RX.DMA_MemoryBurst = DMA_MemoryBurst_Single;//?????????  
    DMA_u1_InitStructure_RX.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//????????  
    DMA_Init(DMA2_Stream5, &DMA_u1_InitStructure_RX);//???DMA Stream  
    //DMA NVIC    
    nvic_u1_Rx.NVIC_IRQChannel = DMA2_Stream5_IRQn;    
    nvic_u1_Rx.NVIC_IRQChannelPreemptionPriority = 1;    
    nvic_u1_Rx.NVIC_IRQChannelSubPriority = 1;    
    nvic_u1_Rx.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&nvic_u1_Rx);    
    DMA_Cmd(DMA2_Stream5, ENABLE);  //??DMA??   
      
		DMA_ITConfig(DMA2_Stream5,DMA_IT_TC,ENABLE);  
		DMA_Cmd(DMA2_Stream5,ENABLE); 
	

 DMA_DeInit(DMA2_Stream7);  
    while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);//??DMA???   
    /* ?? DMA Stream */  
   DMA_u1_InitStructure_TX.DMA_Channel = DMA_Channel_4;  //????  
    DMA_u1_InitStructure_TX.DMA_PeripheralBaseAddr = (u32)&USART1->DR;//DMA????  
    DMA_u1_InitStructure_TX.DMA_Memory0BaseAddr = (u32)dma_u1_TxBuffer;//DMA ???0??  
   DMA_u1_InitStructure_TX.DMA_DIR = DMA_DIR_MemoryToPeripheral;//????????  
   DMA_u1_InitStructure_TX.DMA_BufferSize = 15;//?????   
    DMA_u1_InitStructure_TX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//???????  
    DMA_u1_InitStructure_TX.DMA_MemoryInc = DMA_MemoryInc_Enable;//???????  
    DMA_u1_InitStructure_TX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//??????:8?  
    DMA_u1_InitStructure_TX.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//???????:8?  
    DMA_u1_InitStructure_TX.DMA_Mode = DMA_Mode_Normal;// ??????   
    DMA_u1_InitStructure_TX.DMA_Priority = DMA_Priority_Medium;//?????  
    DMA_u1_InitStructure_TX.DMA_FIFOMode = DMA_FIFOMode_Disable;           
    DMA_u1_InitStructure_TX.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;  
    DMA_u1_InitStructure_TX.DMA_MemoryBurst = DMA_MemoryBurst_Single;//?????????  
    DMA_u1_InitStructure_TX.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//????????  
    DMA_Init(DMA2_Stream7, &DMA_u1_InitStructure_TX);//???DMA Stream  
    //DMA NVIC    
     nvic_u1_Tx.NVIC_IRQChannel = DMA2_Stream7_IRQn;    
    nvic_u1_Tx.NVIC_IRQChannelPreemptionPriority = 1;    
    nvic_u1_Tx.NVIC_IRQChannelSubPriority = 2;    
    nvic_u1_Tx.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&nvic_u1_Tx);    
    DMA_ITConfig(DMA2_Stream7,DMA_IT_TC,ENABLE); 
}
void DMA2_Stream5_IRQHandler()
{
	      /* transfer completed */        
        if (DMA_GetITStatus(DMA2_Stream5, DMA_IT_TCIF5) != RESET)
        {
          DMA_Cmd(DMA2_Stream5, DISABLE);
					
			//		UART1_ReceiveSize =RECEIVE_BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Stream1); 
					 
					AGVRecv_USART1_Data(dma_u1_RxBuffer,Rx_Buffer);
					
					 DMA_ClearFlag(DMA2_Stream5,DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5);
          DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TCIF5);
         	 DMA_Cmd(DMA2_Stream5, ENABLE);                               
				}
}
void u1_DmaSendDataProc(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)  
{  
   
    DMA_Cmd(DMA_Streamx, DISABLE);                      //??DMA??   
      
    while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}  //??DMA?????    
          
    DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //?????    
   
    DMA_Cmd(DMA_Streamx, ENABLE);                      //??DMA??   
} 
void u1_SendBytesInfoProc(u8* pSendInfo, u16 nSendCount)  
{  
    u16 i = 0;  
    u8 *pBuf = NULL;  
  
    pBuf = dma_u1_TxBuffer;  
  
    for (i=0; i<nSendCount; i++)  
    {  
        *pBuf++ = pSendInfo[i];  
    }  

    u1_DmaSendDataProc(DMA2_Stream7,nSendCount); //????DMA??!      
}  
void DMA2_Stream7_IRQHandler()
{  
     if(DMA_GetFlagStatus(DMA2_Stream7,DMA_FLAG_TCIF7)!=RESET)//??DMA2_Steam7????  
    {   
        DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);//??DMA2_Steam7??????  
    }  

}  


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

void USART2_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	DMA_InitTypeDef   DMA_InitStructure;
		NVIC_InitTypeDef  nvic;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3 ,GPIO_AF_USART2);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    USART_DeInit(USART2);
	USART_InitStructure.USART_BaudRate = 100000;   //SBUS 100K baudrate
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Even;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2,&USART_InitStructure);
    
	USART_Cmd(USART2,ENABLE);
    USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
	
	/*USART2 DMA1 Stream5 Channel4*/
	DMA_DeInit(DMA1_Stream5);
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_Channel           =DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)&(USART2->DR);                 //外设地址
	DMA_InitStructure.DMA_Memory0BaseAddr    =(u32)sbus_rx_buffer;                     //内存地址
	DMA_InitStructure.DMA_DIR               =DMA_DIR_PeripheralToMemory;         //外设作为数据来?
	DMA_InitStructure.DMA_BufferSize        =18;                             //每次2个字节?
	DMA_InitStructure.DMA_PeripheralInc     =DMA_PeripheralInc_Disable;     //外设不变
	DMA_InitStructure.DMA_MemoryInc         =DMA_MemoryInc_Enable;          //内存地址增加
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;   //大小为字节
	DMA_InitStructure.DMA_MemoryDataSize    =DMA_MemoryDataSize_Byte;       //大小为字节
	DMA_InitStructure.DMA_Mode              =DMA_Mode_Circular;             //循环模式
	DMA_InitStructure.DMA_Priority          =DMA_Priority_High;         //高优先级
	DMA_InitStructure.DMA_FIFOMode          = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold     = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure.DMA_MemoryBurst       = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBurst   = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA1_Stream5,&DMA_InitStructure);
	DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,ENABLE);             //使能中断
	DMA_Cmd(DMA1_Stream5,ENABLE);
	
	    nvic.NVIC_IRQChannel = DMA1_Stream5_IRQn;    
    nvic.NVIC_IRQChannelPreemptionPriority = 0;    
    nvic.NVIC_IRQChannelSubPriority = 1;    
    nvic.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&nvic);    
    DMA_Cmd(DMA1_Stream5, ENABLE);  //??DMA??   
}

void USART3_Configuration()
{
  USART_InitTypeDef usart3;
	GPIO_InitTypeDef  gpio;
	NVIC_InitTypeDef  nvic;
	NVIC_InitTypeDef  nvic_tx;
	DMA_InitTypeDef  DMA_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure_TX;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10 ,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); 

	gpio.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	//  gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&gpio);

	usart3.USART_BaudRate = 115200;
	usart3.USART_WordLength = USART_WordLength_8b;
	usart3.USART_StopBits = USART_StopBits_1;
	usart3.USART_Parity = USART_Parity_No;
	usart3.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	usart3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART3,&usart3);

	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USART3,USART_IT_TXE,DISABLE);
		/*打开USART中断*/
	USART_ITConfig(USART3,USART_IT_TC,DISABLE);  
	USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(USART3,USART_IT_IDLE,DISABLE);

//	nvic.NVIC_IRQChannel = USART3_IRQn;
//	nvic.NVIC_IRQChannelPreemptionPriority = 1;
//	nvic.NVIC_IRQChannelSubPriority = 1;
//	nvic.NVIC_IRQChannelCmd = DISABLE;
//	NVIC_Init(&nvic);
  USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
  USART_Cmd(USART3, ENABLE);

	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA2????   
	DMA_DeInit(DMA1_Stream1);  
    while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);//??DMA???   
    /* ?? DMA Stream */  
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  //????  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART3->DR;//DMA????  
    DMA_InitStructure.DMA_Memory0BaseAddr = (u32)dma_RxBuffer;//DMA ???0??  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;//????????  
    DMA_InitStructure.DMA_BufferSize = 10;//?????   
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//???????  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//???????  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//??????:8?  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//???????:8?  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ??????   
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//?????  
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;           
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;  
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//?????????  
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//????????  
    DMA_Init(DMA1_Stream1, &DMA_InitStructure);//???DMA Stream  
    //DMA NVIC    
    nvic.NVIC_IRQChannel = DMA1_Stream1_IRQn;    
    nvic.NVIC_IRQChannelPreemptionPriority = 1;    
    nvic.NVIC_IRQChannelSubPriority = 1;    
    nvic.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&nvic);    
    DMA_Cmd(DMA1_Stream1, ENABLE);  //??DMA??   
      
		DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);  
		DMA_Cmd(DMA1_Stream1,ENABLE); 
	

 DMA_DeInit(DMA1_Stream3);  
    while (DMA_GetCmdStatus(DMA1_Stream3) != DISABLE);//??DMA???   
    /* ?? DMA Stream */  
    DMA_InitStructure_TX.DMA_Channel = DMA_Channel_4;  //????  
    DMA_InitStructure_TX.DMA_PeripheralBaseAddr = (u32)&USART3->DR;//DMA????  
    DMA_InitStructure_TX.DMA_Memory0BaseAddr = (u32) dma_TxBuffer;//DMA ???0??  
    DMA_InitStructure_TX.DMA_DIR = DMA_DIR_MemoryToPeripheral;//????????  
    DMA_InitStructure_TX.DMA_BufferSize = 10;//?????   
    DMA_InitStructure_TX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//???????  
    DMA_InitStructure_TX.DMA_MemoryInc = DMA_MemoryInc_Enable;//???????  
    DMA_InitStructure_TX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//??????:8?  
    DMA_InitStructure_TX.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//???????:8?  
    DMA_InitStructure_TX.DMA_Mode = DMA_Mode_Normal;// ??????   
    DMA_InitStructure_TX.DMA_Priority = DMA_Priority_Medium;//?????  
    DMA_InitStructure_TX.DMA_FIFOMode = DMA_FIFOMode_Disable;           
    DMA_InitStructure_TX.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;  
    DMA_InitStructure_TX.DMA_MemoryBurst = DMA_MemoryBurst_Single;//?????????  
    DMA_InitStructure_TX.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//????????  
    DMA_Init(DMA1_Stream3, &DMA_InitStructure_TX);//???DMA Stream  
    //DMA NVIC    
    nvic_tx.NVIC_IRQChannel = DMA1_Stream3_IRQn;    
    nvic_tx.NVIC_IRQChannelPreemptionPriority = 1;    
    nvic_tx.NVIC_IRQChannelSubPriority = 2;    
    nvic_tx.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&nvic_tx);    
    DMA_ITConfig(DMA1_Stream3,DMA_IT_TC,ENABLE); 
}

void DMA1_Stream1_IRQHandler()
{
	      /* transfer completed */        
        if (DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1) != RESET)
        {
          DMA_Cmd(DMA1_Stream1, DISABLE);
					
			//		UART1_ReceiveSize =RECEIVE_BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Stream1); 
//					 AGVRecv_send_Data(dma_RxBuffer);
					DMA_ClearFlag(DMA1_Stream1,DMA_FLAG_TCIF1 | DMA_FLAG_FEIF1 | DMA_FLAG_DMEIF1 | DMA_FLAG_TEIF1| DMA_FLAG_HTIF1);
					 //DMA_ClearFlag(DMA2_Stream5,DMA_FLAG_TCIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_DMEIF5 | DMA_FLAG_TEIF5 | DMA_FLAG_HTIF5);
          DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);
         	 DMA_Cmd(DMA1_Stream1, ENABLE);                               
				}
}
void DmaSendDataProc(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)  
{  
   
    DMA_Cmd(DMA_Streamx, DISABLE);                      //??DMA??   
      
    while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}  //??DMA?????    
          
    DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //?????    
   
    DMA_Cmd(DMA_Streamx, ENABLE);                      //??DMA??   
} 
void SendBytesInfoProc(u8* pSendInfo, u16 nSendCount)  
{  
    u16 i = 0;  
    u8 *pBuf = NULL;  
  
    pBuf = dma_TxBuffer;  
  
    for (i=0; i<nSendCount; i++)  
    {  
        *pBuf++ = pSendInfo[i];  
    }  

    DmaSendDataProc(DMA1_Stream3,nSendCount); //????DMA??!      
}  
void DMA1_Stream3_IRQHandler()
{  
     if(DMA_GetFlagStatus(DMA1_Stream3,DMA_FLAG_TCIF3)!=RESET)//??DMA2_Steam7????  
    {   
        DMA_ClearFlag(DMA1_Stream3,DMA_FLAG_TCIF3);//??DMA2_Steam7??????  
    }  

}  




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


void USART_Printf(USART_TypeDef* USARTx,char *fmt, ...) 
{    
	char   uart0_pString[100]; 
	va_list  uart0_ap; 
	va_start(uart0_ap, fmt);
	vsnprintf(uart0_pString, 60, fmt, uart0_ap);   
	UART_SendBuffer(USARTx,uart0_pString); 
	va_end(uart0_ap);       
} 
void UART_SendBuffer( USART_TypeDef* USARTx,char *buffer)
{
	while(*buffer)
	{
		USART_SendData( USARTx, *buffer++);
		while( USART_GetFlagStatus(USARTx , USART_FLAG_TXE) == RESET);	
	}
}
int fputc(int ch, FILE *f)//printf重定向到串口1
{
    while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
    USART_SendData(USART1, (uint8_t)ch);    
    return ch;
}



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
void USART_SendBytes(USART_TypeDef* USARTx,uint8_t* data,uint32_t length)
{
	u16 i;
	for (i=0; i<length; i++)
	{
//		#ifdef __QUEUE_H
//		QueueWrite((void *)pUsartSendBuff,  data[i]);
//		#else
		USART_SendData( USARTx, *data++);
		while( USART_GetFlagStatus(USARTx , USART_FLAG_TXE) ==  RESET);			
//		#endif
	}
//	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
}
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
void USART_SendByte(USART_TypeDef* USARTx, uint8_t data)
{
//		#ifdef __QUEUE_H
//		QueueWrite((void *)pUsartSendBuff,  data);
//		#else
		USART_SendData( USARTx, data);
		while( USART_GetFlagStatus(USARTx , USART_FLAG_TXE) == RESET);	
//		#endif	
	
}


//wellcasa点对点校验


//	#define		Recv_bz1          1
//	#define		Recv_bz2					1




