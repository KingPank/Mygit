/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_iic_config.h
    Description			:	
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2014.12.20>  V1.0
    Connector Fuction 	:
    Notes	£∫
*/
/*----------------------------------------------------------------------------*/
#ifndef __STM32F4XXIICCONFIG_H__
#define __STM32F4XXIICCONFIG_H__
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stm32f4xx.h"
	#include <stdio.h>
    /*---Macro Definition-----*/
    #define IIC1_ReadByte(byAD,byRA,pdata) 			IIC1_ReadData(byAD,byRA,pdata,1)
    #define IIC1_ReadBytes(byAD,byRA,pdata,count) 	IIC1_ReadData(byAD,byRA,pdata,count)  
    #define IIC1_WriteByte(byAD,byRA,data) 			IIC1_WriteData(byAD,byRA,data)
//    #define IIC1_WriteBytes(byAD,byRA,pdata,count) 	IIC1_WriteData(byAD,byRA,pdata,count)  
	/*---Variable Definition--*/
	/*---Function Definiton---*/
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	IIC1_Confugration
	Description       :		
	Input parameter   :   	Class			Name		Action	
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	void IIC1_Confugration(void);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	IIC1_ReadData
	Description       :		Read  bytes through the iic bus
	Input parameter   :   	Class			Name		Action	
							unsigned char 	byAD		The device address
							unsigned int 	byRA 		The Rom address
							unsigned char 	*pData 		point to the read buff
							unsigned char	count 		the length of the data
	Output parameter  :   	Class			Name		Action		
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	int IIC1_ReadData(u8 byAD,u8 byRA,u8 *pdata,u8 count);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	IIC1_WriteData
	Description       :		Write a byte through the IIC1 bus
	Input parameter   :   	Class			Name		Action	
							unsigned char 	byAD		The device address
							unsigned int 	byRA 		The Rom address
							unsigned char 	*pdata 		The point of data
							unsigned char 	count		The length of data
	Output parameter  :   	Class			Name		Action						
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	int IIC1_WriteData(u8 byAD,u8 byRA,u8 data);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	IIC1_WriteBits
	Description       :		
	Input parameter   :   	Class			Name		Action	
							unsigned char 	byAD		The device address
							unsigned int 	byRA 		The Rom address
							u8 				bitStart	The Bit start 
							u8 				length		length
							u8 				data 		data
	Output parameter  :   	Class			Name		Action					
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	u8 IIC1_WriteBits(u8 byAD,u8 byRA,u8 bitStart,u8 length,u8 data);
	/*----------------------------------------------------------------------------*/
	/*
	Fuction Name      :	 	IIC1_WriteBit
	Description       :		
	Input parameter   :   	Class			Name		Action	
							unsigned char 	byAD		The device address
							unsigned int 	byRA 		The Rom address
							u8 bitNum
							u8 data
	Output parameter  :   	Class			Name		Action					
	Author&Date       :		Jones.Lee & 2014.12.20
	Notes             :	
	*/
	/*----------------------------------------------------------------------------*/
	u8 IIC1_WriteBit(u8 byAD, u8 byRA, u8 bitNum, u8 data);
/*----------------------------------------------------------------------------*/

//#define READ_SDA   PCin(11)  // ‰»ÎSDA 
#endif

