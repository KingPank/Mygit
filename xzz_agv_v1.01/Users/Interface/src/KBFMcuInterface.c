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
    Notes	：
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
	#include "stm32f10x_bsp_config.h"
	#include "KBFMcuInterface.h"
	#include "app_cfg.h"
	#include <string.h>
	#include <stdio.h>
	#include <stdarg.h>  
    /*---Variable Definition--*/
	uint8_t *pKBFMcuCommRecvBuff;
	uint8_t *pKBFMcuCommSendBuff;
    /*---Function Definiton---*/
    /*---Macro Definition-----*/
	#define		SPIUSER 			SPI1
	#define		IICUSER 			I2C1
	#define		USARTPC				USART1
	#define		IICUSER				I2C1
	#define		TIMPWMUSER			TIM2
	#define		TIMCAPUSER			TIM1
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void KBFMcuHardConfig(void)
{
  	Bsp_Configuration();/* Initialize "BSP the hardboard"              */
	//指针，为了统一接口
}
void KBFMcuUsartRecvQueuePoint(void **ppData)
{
	pUsartRecvBuff = (uint8_t *)(*ppData);
}
void KBFMcuUsartSendQueuePoint(void **ppData)
{
	pUsartSendBuff = (uint8_t *)(*ppData);
}
void KBFMcuIIcReadByte(uint8_t byAD,uint32_t byRA,uint8_t* DataToRead)
{    
	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif

	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_IIC1, 0, &err);	 // 等待信号量
	#endif

	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	 
	 
	#ifdef __STM32F10XIICCONFIG_H__
		IIC_Read_Byte(IICUSER,byAD,byRA,DataToRead);
	#endif

	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_IIC1);			 // 释放信号量 
	#endif

	#ifdef  OS_CPU_H
    	OS_EXIT_CRITICAL();
	#endif
}
void KBFMcuIIcWriteByte(uint8_t byAD,uint32_t byRA, uint8_t DataToWrite)
{
	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif  
	               
	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_IIC1, 0, &err);	 // 等待信号量
 	#endif	

	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	

	#ifdef __STM32F10XIICCONFIG_H__
		IIC_Write_Byte(IICUSER,byAD,byRA, DataToWrite);
	#endif

	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_IIC1);			 // 释放信号量 
	#endif

	#ifdef  OS_CPU_H
		OS_EXIT_CRITICAL();
	#endif
}
void KBFMcuIIcWriteBytes(uint8_t byAD, uint32_t byRA,uint8_t *pData, uint8_t byCount)
{
	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif

	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_IIC1, 0, &err);	 // 等待信号量
 	#endif 

	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	

	#ifdef __STM32F10XIICCONFIG_H__
 		IIC_Write_Bytes(IICUSER,byAD,byRA,pData,byCount);
	#endif

	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_IIC1);			 // 释放信号量 
	#endif	

	#ifdef  OS_CPU_H
		OS_EXIT_CRITICAL();
	#endif
}	
void KBFMcuIIcReadBytes(uint8_t byAD, uint32_t byRA,uint8_t *pData, uint8_t byCount)
{
	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif  

	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_IIC1, 0, &err);	 // 等待信号量
  	#endif

	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	

	#ifdef __STM32F10XIICCONFIG_H__
		IIC_Read_Bytes(IICUSER,byAD,byRA,pData,byCount);
	#endif
		
	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_IIC1);			 // 释放信号量 
	#endif

	#ifdef  OS_CPU_H
		OS_EXIT_CRITICAL();
	#endif
}
void KBFMcuSPIWirteByte(uint8_t data)
{
	uint8_t temp;

	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif

	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_SPI1, 0, &err);	 // 等待信号量
  	#endif
  
	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	

	#ifdef __STM32F10XSPICONFIG_H__
		temp =  SPI_RW(SPIUSER,data);		 /////////////////////////////// 
		 	 temp = temp;
	#endif

	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_SPI1);			 // 释放信号量 
	#endif
	#ifdef  OS_CPU_H
    	OS_EXIT_CRITICAL();
	#endif
}
uint8_t KBFMcuSPIRWByte(uint8_t data)
{
	uint8_t temp;

	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif

	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_SPI1, 0, &err);	 // 等待信号量
  	#endif

	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	

	#ifdef __STM32F10XSPICONFIG_H__
		temp =  SPI_RW(SPIUSER,data);		 ///////////////////////////////
	#endif

	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_SPI1);			 // 释放信号量 
	#endif
	#ifdef  OS_CPU_H
    	OS_EXIT_CRITICAL();
	#endif
	return temp;
}

void KBFMcuSPIReadByte(uint8_t *pData)
{
	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif

	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_SPI1, 0, &err);	 // 等待信号量
  	#endif

	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	

	#ifdef __STM32F10XSPICONFIG_H__
		*pData =  SPI_RW(SPIUSER,0xff);		 ///////////////////////////////
	#endif

	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_SPI1);			 // 释放信号量 
	#endif
	#ifdef  OS_CPU_H
    	OS_EXIT_CRITICAL();
	#endif
}
void KBFMcuSPISetSpeed(uint8_t SpeedSet)
{
	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif

	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_SPI1, 0, &err);	 // 等待信号量
  	#endif

	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	
	#ifdef __STM32F10XSPICONFIG_H__
		SPI_SetSpeed(SPIUSER,SpeedSet);
	#endif

		#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_SPI1);			 // 释放信号量 
	#endif

	#ifdef  OS_CPU_H
    	OS_EXIT_CRITICAL();
	#endif
}

void KBFMcuLedFlash(BoardLed port,uint16_t time,uint16_t cnt)
{
	#ifdef __STM32F10XGPIOCONFIG_H__
		switch (port)
		{
			case BoardLed1:
				LED1FLASHS(time,cnt);
				break;
			case BoardLed2:
				LED2FLASHS(time,cnt);
				break;
			case BoardLed3:
				LED3FLASHS(time,cnt);
				break;
			case BoardLed4:
				LED4FLASHS(time,cnt);
				break;
		}
	#endif		
}
void KBFMcuLedSFlashs(uint8_t port,uint16_t time,uint16_t cnt)
{
	#ifdef __STM32F10XGPIOCONFIG_H__
	uint8_t ledstate[4] = {0};
	if(port&(1<<BOARDLED1BIT)) ledstate[BOARDLED1BIT] = 1;
	else	ledstate[BOARDLED1BIT] = 0;	
	if(port&(1<<BOARDLED2BIT)) ledstate[BOARDLED2BIT] = 1;
	else	ledstate[BOARDLED2BIT] = 0;	
	if(port&(1<<BOARDLED3BIT)) ledstate[BOARDLED3BIT] = 1;
	else	ledstate[BOARDLED3BIT] = 0;	
	if(port&(1<<BOARDLED4BIT)) ledstate[BOARDLED4BIT] = 1;
	else	ledstate[BOARDLED4BIT] = 0;	
	while(cnt--)
	{
		LED1 =  ledstate[BOARDLED1BIT]; 
		LED2 =  ledstate[BOARDLED2BIT];
		LED3 =  ledstate[BOARDLED3BIT];
		LED4 =  ledstate[BOARDLED4BIT];
		OSTimeDlyHMSM(0,0,0,time);
		LED1OFF;LED2OFF;LED3OFF;LED4OFF;
		OSTimeDlyHMSM(0,0,0,time);	
	}
	LED1OFF;LED2OFF;LED3OFF;LED4OFF;
	#endif		
}
void KBFMcuLedDFlashs(uint8_t port,uint16_t time,uint16_t cnt)
{
	#ifdef __STM32F10XGPIOCONFIG_H__
	uint8_t ledstate[4] = {0};
	if(port&(1<<BOARDLED1BIT)) ledstate[BOARDLED1BIT] = 1;
	else	ledstate[BOARDLED1BIT] = 0;	
	if(port&(1<<BOARDLED2BIT)) ledstate[BOARDLED2BIT] = 1;
	else	ledstate[BOARDLED2BIT] = 0;	
	if(port&(1<<BOARDLED3BIT)) ledstate[BOARDLED3BIT] = 1;
	else	ledstate[BOARDLED3BIT] = 0;	
	if(port&(1<<BOARDLED4BIT)) ledstate[BOARDLED4BIT] = 1;
	else	ledstate[BOARDLED4BIT] = 0;	
	while(cnt--)
	{
		LED1 =  ledstate[BOARDLED1BIT]; 
		LED2 =  ledstate[BOARDLED2BIT];
		LED3 =  ledstate[BOARDLED3BIT];
		LED4 =  ledstate[BOARDLED4BIT];
		OSTimeDlyHMSM(0,0,0,time);
		LED1 =  (~ledstate[BOARDLED1BIT])&(0x01); 
		LED2 =  (~ledstate[BOARDLED2BIT])&(0x01);
		LED3 =  (~ledstate[BOARDLED3BIT])&(0x01);
		LED4 =  (~ledstate[BOARDLED4BIT])&(0x01);
		OSTimeDlyHMSM(0,0,0,time);	
	}
	LED1OFF;LED2OFF;LED3OFF;LED4OFF;
	#endif		
}
void KBFMcuGPIOOutPut(GpioGrp gpiogrp, uint8_t num,uint8_t out)
{
	#ifdef __STM32F10XGPIOCONFIG_H__
		switch (gpiogrp)
		{
			case GpioGrpA:
				PAout(num) = out;
				break;
			case GpioGrpB:
				PBout(num) = out;
				break;
			case GpioGrpC:
				PCout(num) = out;
				break;
			case GpioGrpD:
				PDout(num) = out;
				break;
			case GpioGrpE:
				PEout(num) = out;
				break;
		}
	#endif		
}
void KBFMcuDelay(uint32_t ms)
{
		#ifdef OS_uCOS_II_H
   			OSTimeDlyHMSM(0,0,0,ms);
		#else
			  #ifdef __STM32F10XSYSTICKCONFIG_H__

			  #endif
		#endif
}
void KBFMcuUsartSendBytes(uint8_t *buff,uint32_t cnt)
{	
	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_USART1, 0, &err);	 // 等待信号量
	#endif

	#ifdef __STM32F10XUSARTCONFIG_H__
 //		USART_SendBytes(USARTPC,buff,cnt);
	#endif

 	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_USART1);			 // 释放信号量 
	#endif
}
void KBFMcuUsartSendByte(uint8_t buff)
{ 
	#ifdef OS_EVENT_MULTI_EN
		uint8_t err = 0;
 		OSMutexPend(Mutex_USART1, 0, &err);	 // 等待信号量
	#endif

 	#ifdef __STM32F10XUSARTCONFIG_H__
		USART_SendByte(USARTPC,buff);
	#endif

 	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_USART1);			 // 释放信号量 
	#endif
}

void KBFMcuprintf(char *fmt, ...)
{ 

	#ifdef OS_CPU_H          
		OS_CPU_SR  cpu_sr;
	#endif
	
	char      uart0_pString[101]; 
	va_list   uart0_ap;  							//定义一个va_list型的变量，这个变量是指向参数的指针 

	#ifdef OS_EVENT_MULTI_EN		 				//这个地方有问题
		uint8_t err = 0;
 		OSMutexPend(Mutex_USART1, 0, &err);	 		// 等待信号量
	#endif
 
	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif

	#ifdef __STM32F10XUSARTCONFIG_H__
	va_start(uart0_ap, fmt);    					//用该宏初始化变量   
	vsnprintf(uart0_pString, 100, fmt, uart0_ap);   
	UART_SendBuffer(USARTPC,uart0_pString); 
	va_end(uart0_ap);         						//宏结束可变参数的获取 
	#endif
	#ifdef  OS_CPU_H
    	OS_EXIT_CRITICAL();
	#endif
	#ifdef OS_EVENT_MULTI_EN
		OSMutexPost(Mutex_USART1);			 // 释放信号量 
	#endif

}

void KBFMcuADCReadData(float *pdata)
{ 
	#ifdef __STM32F10XADCCONFIG_H__
		static int predata;
		int sum = 0,i;
		u8 count;
		for(i = 0;i < ADCCHANNELNUM; i++)	
		{	
			for ( count=0;count<ADCCHNNELCNT;count++)	
			{	
				sum += AD_Value[count][i];	
			}	
			*(pdata + i)	= sum/ADCCHNNELCNT;	
			sum=0;
		}
		*(pdata + i) = (*(pdata + i)) * 0.7+ 0.3 *predata;
		predata =  *(pdata + i);	
	#endif
}
void KBFMcuPWMPutPut(uint16_t pwm1_val,uint16_t pwm2_val,uint16_t pwm3_val,uint16_t pwm4_val)
{
	#ifdef __STM32F10XTIMECONFIG_H__
		//换了，与程序兼容 与建立模型相同 
		//	
		//	 \	/				 \	/
		//	  \/				  \/
		//	  /\ 				  /\
		//	 /	\				 /	\
		//	   1			       4
		//
		//	 \	/				 \	/
		//	  \/				  \/
		//	  /\ 				  /\
		//	 /	\				 /	\
		//	   2				   3
		PWM_Set(TIMPWMUSER,pwm2_val,pwm3_val,pwm4_val,pwm1_val);
	#endif		
}
