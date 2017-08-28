/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f10x_gpio_config.h
    Description			:	configruation the gpio
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2014.12.20>  V2.0
    Connector Fuction 	:
    Notes	£º
*/
/*----------------------------------------------------------------------------*/
#ifndef __STM32F4XXGPIOCONFIG_H__
#define __STM32F4XXGPIOCONFIG_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stm32f4xx.h"
	#include <stdio.h>
    /*---Macro Definition-----*/

	#define		LED1_GPIONUM		 		GPIO_Pin_0	 
	#define		LED1_GPIOMODE		 		GPIO_Mode_OUT
	#define		LED1_GPIOSPEED				GPIO_Speed_100MHz
	#define		LED1_GPIOTYPE				GPIO_OType_PP	
	#define		LED1_GPIOGRP		 		GPIOA

	#define		LED2_GPIONUM		 		GPIO_Pin_1	 
	#define		LED2_GPIOMODE		 		GPIO_Mode_OUT
	#define		LED2_GPIOSPEED				GPIO_Speed_100MHz
	#define		LED2_GPIOTYPE				GPIO_OType_PP	
	#define		LED2_GPIOGRP		 		GPIOA
	
	#define		KEY_GPIONUM		 			GPIO_Pin_3
	#define		KEY_GPIOMODE		 		GPIO_Mode_IN
	#define		KEY_GPIOSPEED		 		GPIO_Speed_50MHz
	#define		KEY_GPIOTYPE				GPIO_OType_PP		
	#define		KEY_GPIOGRP		 			GPIOB	


	#define		CAN1TX_GPIONUM		 		GPIO_Pin_9
	#define		CAN1TX_GPIOMODE		 		GPIO_Mode_AF
//	#define		CAN1TX_GPIOSPEED		 	GPIO_Speed_50MHz
//	#define		CAN1TX_GPIOTYPE				GPIO_OType_PP		
	#define		CAN1TX_GPIOGRP		 		GPIOB	

	#define		CAN1RX_GPIONUM		 		GPIO_Pin_8
	#define		CAN1RX_GPIOMODE		 		GPIO_Mode_AF
//	#define		CAN1RX_GPIOSPEED		 	GPIO_Speed_50MHz
//	#define		CAN1RX_GPIOTYPE				GPIO_OType_PP	
	#define		CAN1RX_GPIOGRP		 		GPIOB	

	#define		CAN2TX_GPIONUM		 		GPIO_Pin_13
	#define		CAN2TX_GPIOMODE		 		GPIO_Mode_AF
//	#define		CAN2TX_GPIOSPEED		 	GPIO_Speed_50MHz
//	#define		CAN2TX_GPIOTYPE				GPIO_OType_PP		
	#define		CAN2TX_GPIOGRP		 		GPIOB	

	#define		CAN2RX_GPIONUM		 		GPIO_Pin_12
	#define		CAN2RX_GPIOMODE		 		GPIO_Mode_AF
//	#define		CAN2RX_GPIOSPEED		 	GPIO_Speed_50MHz
//	#define		CAN2RX_GPIOTYPE				GPIO_OType_PP	
	#define		CAN2RX_GPIOGRP		 		GPIOB	
		
	#define		USART1RXD_GPIONUM			GPIO_Pin_10
	#define		USART1RXD_GPIOMODE		 	GPIO_Mode_AF
	#define		USART1RXD_GPIOSPEED			GPIO_Speed_100MHz
	#define		USART1RXD_GPIOTYPE			GPIO_OType_PP	
	#define		USART1RXD_GPIOGRP		 	GPIOA
		
	#define		USART1TXD_GPIONUM			GPIO_Pin_9
	#define		USART1TXD_GPIOMODE		 	GPIO_Mode_AF
	#define		USART1TXD_GPIOSPEED			GPIO_Speed_100MHz
	#define		USART1TXD_GPIOTYPE			GPIO_OType_PP	
 	#define		USART1TXD_GPIOGRP		 	GPIOA 
	
	#define		USART2RXD_GPIONUM			GPIO_Pin_3
	#define		USART2RXD_GPIOMODE		 	GPIO_Mode_AF
	#define		USART2RXD_GPIOSPEED			GPIO_Speed_50MHz
	#define		USART2RXD_GPIOTYPE			GPIO_OType_PP	
	#define		USART2RXD_GPIOGRP		 	GPIOA
		
//	#define		USART2TXD_GPIONUM			GPIO_Pin_9
//	#define		USART2TXD_GPIOMODE		 	GPIO_Mode_AF_PP
//	#define		USART2TXD_GPIOSPEED			GPIO_Speed_50MHz
//	#define		USART2TXD_GPIOTYPE			GPIO_OType_PP	
// 	#define		USART2TXD_GPIOGRP		 	GPIOA 

	#define		IIC1SDA_GPIONUM				GPIO_Pin_7
	#define		IIC1SDA_GPIOMODE		 	GPIO_Mode_OUT
	#define		IIC1SDA_GPIOSPEED			GPIO_Speed_100MHz
	#define		IIC1SDA_GPIOTYPE			GPIO_OType_OD	
	#define		IIC1SDA_GPIOGRP		 		GPIOB
		
	#define		IIC1SCL_GPIONUM				GPIO_Pin_6
	#define		IIC1SCL_GPIOMODE		 	GPIO_Mode_OUT
	#define		IIC1SCL_GPIOSPEED			GPIO_Speed_100MHz
	#define		IIC1SCL_GPIOTYPE			GPIO_OType_OD	
 	#define		IIC1SCL_GPIOGRP		 		GPIOB 
	
	#define		IIC2SDA_GPIONUM				GPIO_Pin_11
	#define		IIC2SDA_GPIOMODE		 	GPIO_Mode_OUT
	#define		IIC2SDA_GPIOSPEED			GPIO_Speed_100MHz
	#define		IIC2SDA_GPIOTYPE			GPIO_OType_OD	
	#define		IIC2SDA_GPIOGRP		 		GPIOA
		
	#define		IIC2SCL_GPIONUM				GPIO_Pin_10
	#define		IIC2SCL_GPIOMODE		 	GPIO_Mode_OUT
	#define		IIC2SCL_GPIOSPEED			GPIO_Speed_100MHz
	#define		IIC2SCL_GPIOTYPE			GPIO_OType_OD	
 	#define		IIC2SCL_GPIOGRP		 		GPIOA 
	
	#define		OLEDSCL_GPIONUM				GPIO_Pin_3
	#define		OLEDSCL_GPIOMODE		 	GPIO_Mode_OUT
	#define		OLEDSCL_GPIOSPEED			GPIO_Speed_100MHz
	#define		OLEDSCL_GPIOTYPE			GPIO_OType_PP	
 	#define		OLEDSCL_GPIOGRP		 		GPIOC 

	#define		OLEDSDA_GPIONUM				GPIO_Pin_2
	#define		OLEDSDA_GPIOMODE		 	GPIO_Mode_OUT
	#define		OLEDSDA_GPIOSPEED			GPIO_Speed_100MHz
	#define		OLEDSDA_GPIOTYPE			GPIO_OType_PP	
 	#define		OLEDSDA_GPIOGRP		 		GPIOC 

	#define		OLEDRST_GPIONUM				GPIO_Pin_0
	#define		OLEDRST_GPIOMODE		 	GPIO_Mode_OUT
	#define		OLEDRST_GPIOSPEED			GPIO_Speed_100MHz
	#define		OLEDRST_GPIOTYPE			GPIO_OType_PP	
 	#define		OLEDRST_GPIOGRP		 		GPIOC 

	#define		OLEDDC_GPIONUM				GPIO_Pin_1
	#define		OLEDDC_GPIOMODE		 		GPIO_Mode_OUT
	#define		OLEDDC_GPIOSPEED			GPIO_Speed_100MHz
	#define		OLEDDC_GPIOTYPE				GPIO_OType_PP	
 	#define		OLEDDC_GPIOGRP		 		GPIOC 
	
	#define		SDCLK_GPIONUM				GPIO_Pin_12
	#define		SDCLK_GPIOMODE		 		GPIO_Mode_AF
	#define		SDCLK_GPIOSPEED				GPIO_Speed_25MHz
	#define		SDCLK_GPIOPUPD				GPIO_PuPd_UP	
	#define		SDCLK_GPIOTYPE				GPIO_OType_PP	
 	#define		SDCLK_GPIOGRP		 		GPIOC 
	
	#define		SDDAT0_GPIONUM				GPIO_Pin_8
	#define		SDDAT0_GPIOMODE		 		GPIO_Mode_AF
	#define		SDDAT0_GPIOSPEED			GPIO_Speed_25MHz
	#define		SDDAT0_GPIOPUPD				GPIO_PuPd_UP		
	#define		SDDAT0_GPIOTYPE				GPIO_OType_PP	
 	#define		SDDAT0_GPIOGRP		 		GPIOC 
	
	#define		SDDAT1_GPIONUM				GPIO_Pin_9
	#define		SDDAT1_GPIOMODE		 		GPIO_Mode_AF
	#define		SDDAT1_GPIOSPEED			GPIO_Speed_25MHz
	#define		SDDAT1_GPIOPUPD				GPIO_PuPd_UP	
	#define		SDDAT1_GPIOTYPE				GPIO_OType_PP	
 	#define		SDDAT1_GPIOGRP		 		GPIOC 
	
	#define		SDDAT2_GPIONUM				GPIO_Pin_10
	#define		SDDAT2_GPIOMODE		 		GPIO_Mode_AF
	#define		SDDAT2_GPIOSPEED			GPIO_Speed_25MHz
	#define		SDDAT2_GPIOPUPD				GPIO_PuPd_UP	
	#define		SDDAT2_GPIOTYPE				GPIO_OType_PP	
 	#define		SDDAT2_GPIOGRP		 		GPIOC 
	
	#define		SDDAT3_GPIONUM				GPIO_Pin_11
	#define		SDDAT3_GPIOMODE		 		GPIO_Mode_AF
	#define		SDDAT3_GPIOSPEED			GPIO_Speed_25MHz
	#define		SDDAT3_GPIOPUPD				GPIO_PuPd_UP	
	#define		SDDAT3_GPIOTYPE				GPIO_OType_PP	
 	#define		SDDAT3_GPIOGRP		 		GPIOC 
	
	#define		SDCMD_GPIONUM				GPIO_Pin_2
	#define		SDCMD_GPIOMODE		 		GPIO_Mode_AF
	#define		SDCMD_GPIOSPEED				GPIO_Speed_25MH
	#define		SDCMD_GPIOPUPD				GPIO_PuPd_NOPULL	
	#define		SDCMD_GPIOTYPE				GPIO_OType_PP	
 	#define		SDCMD_GPIOGRP		 		GPIOD 
	
	
//	#define		USBDP_GPIONUM				GPIO_Pin_9
//	#define		USBDP_GPIOMODE		 		GPIO_Mode_AF_PP
//	#define		USBDP_GPIOSPEED				GPIO_Speed_50MHz
//	#define		USBDP_GPIOTYPE				GPIO_OType_PP	
// 	#define		USBDP_GPIOGRP		 		GPIOA 
//	
//	#define		USBDM_GPIONUM				GPIO_Pin_9
//	#define		USBDM_GPIOMODE		 		GPIO_Mode_AF_PP
//	#define		USBDM_GPIOSPEED				GPIO_Speed_50MHz
//	#define		USBDM_GPIOTYPE				GPIO_OType_PP	
// 	#define		USBDM_GPIOGRP		 		GPIOA 
//	
//	#define		USBEN_GPIONUM				GPIO_Pin_9
//	#define		USBEN_GPIOMODE		 		GPIO_Mode_AF_PP
//	#define		USBEN_GPIOSPEED				GPIO_Speed_50MHz
//	#define		USBEN_GPIOTYPE				GPIO_OType_PP	
// 	#define		USBEN_GPIOGRP		 		GPIOA 
//	
	
 	#define		PWM1_GPIONUM				GPIO_Pin_6
	#define		PWM1_GPIOMODE		 		GPIO_Mode_AF
	#define		PWM1_GPIOSPEED				GPIO_Speed_50MHz
	#define		PWM1_GPIOTYPE				GPIO_OType_PP	
	#define		PWM1_GPIOGRP		 		GPIOC
 
	#define		PWM2_GPIONUM				GPIO_Pin_7
	#define		PWM2_GPIOMODE		 		GPIO_Mode_AF
	#define		PWM2_GPIOSPEED				GPIO_Speed_50MHz
	#define		PWM2_GPIOTYPE				GPIO_OType_PP	
	#define		PWM2_GPIOGRP		 		GPIOC
	
	
 	#define LED1 PAout(0)	  
	#define LED2 PBout(1)	  

	/*---Variable Definition--*/
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	GPIO_Configuration
	Description       :		Configurate the all gpio.
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	extern 	void GPIO_Configuration(void);
/*----------------------------------------------------------------------------*/										
#endif /* __STM32F10XGPIOCONFIG_H__ */
