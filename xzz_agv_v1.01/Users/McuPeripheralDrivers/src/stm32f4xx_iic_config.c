/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_iic_config.c
    Description			:	
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2015.4.28>  V1.0
    Connector Fuction 	:	
    Notes	：				Analog signal
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "stm32f4xx_iic_config.h"
	#include "stm32f4xx.h"
	#include <stdio.h>
    /*---Macro Definition-----*/
	#define IIC1_SCL_H()      GPIO_SetBits(GPIOB,GPIO_Pin_6)
	#define IIC1_SCL_L()      GPIO_ResetBits(GPIOB,GPIO_Pin_6)
	#define IIC1_SDA_H()      GPIO_SetBits(GPIOB,GPIO_Pin_7)
	#define IIC1_SDA_L()      GPIO_ResetBits(GPIOB,GPIO_Pin_7)
	#define IIC1_SDA_Read()   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
	/*---Variable Definition--*/
	/*---Function Definiton---*/
	void 	IIC1_Confugration(void);
	void 	IIC1_Delay(unsigned int t);
	void	IIC1_SDA_Out(void);
	void 	IIC1_SDA_In(void);
	void 	IIC1_Start(void);
	void 	IIC1_Stop(void);
	void 	IIC1_Ack(u8 re);	
	int 	IIC1_WaitAck(void);	
	void 	IIC1_WriteReg(u8 Temp);
	u8 		IIC1_ReadReg(void);
	int 	IIC1_WriteData(u8 byAD,u8 byRA,u8 data);
	int 	IIC1_ReadData(u8 byAD,u8 byRA,u8 *pdata,u8 count);
	u8 		IIC1writeBits(u8 byAD,u8 byRA,u8 bitStart,u8 length,u8 data);
	u8 		IIC1writeBit(u8 byAD, u8 byRA, u8 bitNum, u8 data);
/*----------------------------------------------------------------------------*/
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
void IIC1_Confugration(void)
{
    GPIO_InitTypeDef   gpio;
    
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_OD;
	gpio.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_Init(GPIOB, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOB, &gpio);	
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	IIC1_Delay
						IIC1_SDA_Out
						IIC1_SDA_In
						IIC1_Start
						IIC1_Stop
						IIC1_Ack
						IIC1_WaitAck	
						IIC1_WriteReg
						IIC1_ReadReg	
Description       :		Some IIC Base Function
Input parameter   :   	Class			Name		Action						
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void IIC1_Delay(u32 t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a = 6;
		while(a--);
	}
}
void IIC1_SDA_Out(void)//输出IO口设置
{
    GPIO_InitTypeDef   gpio;
    
	gpio.GPIO_Pin = GPIO_Pin_7;
  gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_OD;
	gpio.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_Init(GPIOB, &gpio);
}
void IIC1_SDA_In(void)//输入IO口设置
{
    GPIO_InitTypeDef   gpio;
    
	gpio.GPIO_Pin = GPIO_Pin_7;   
  gpio.GPIO_Mode = GPIO_Mode_IN;
  gpio.GPIO_OType = GPIO_OType_PP;
  gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
}
void IIC1_Start(void)	//IIC开始							  
{
	IIC1_SDA_Out();
	IIC1_SDA_H();
	IIC1_SCL_H();
	IIC1_Delay(1);
	IIC1_SDA_L();
	IIC1_Delay(1);
	IIC1_SCL_L();
}
void IIC1_Stop(void)//IIC停止
{
	IIC1_SDA_Out();
	IIC1_SCL_L();
	IIC1_SDA_L();
	IIC1_Delay(1);
	IIC1_SCL_H();
	IIC1_SDA_H();
	IIC1_Delay(1);
}
void IIC1_Ack(u8 re)//发送应答				     
{
	IIC1_SDA_Out();
	if(re)
	   IIC1_SDA_H();
	else
	   IIC1_SDA_L();
	IIC1_SCL_H();
	IIC1_Delay(1);
	IIC1_SCL_L();
	IIC1_Delay(1);
}
int IIC1_WaitAck(void)//等待应答
{
	u16 Out_Time=1000;
    
    IIC1_SDA_H();
	IIC1_SDA_In();
	IIC1_Delay(1);
	IIC1_SCL_H();
	IIC1_Delay(1);
	while(IIC1_SDA_Read())
	{
		if(--Out_Time)
		{
			IIC1_Stop();
            printf("error 2A\r\n");
            return 0xff;
		}
	}
	IIC1_SCL_L();
    return 0;
}
void IIC1_WriteReg(u8 Temp)//写入计算机
{
	u8 i;
	IIC1_SDA_Out();
	IIC1_SCL_L();
	for(i=0;i<8;i++)
	{
		if(Temp&0x80)
		{
			IIC1_SDA_H();
		}
		else
		{
			IIC1_SDA_L();
		}
		Temp<<=1;
		IIC1_Delay(1);
		IIC1_SCL_H();
		IIC1_Delay(1);
		IIC1_SCL_L();
	}
}
u8 IIC1_ReadReg(void)//读取计算机
{
	u8 i,Temp=0;
	IIC1_SDA_In();
	for(i=0;i<8;i++)
	{
		IIC1_SCL_L();
		IIC1_Delay(1);
		IIC1_SCL_H();
		Temp<<=1;
		if(IIC1_SDA_Read())
		   Temp++;
		IIC1_Delay(1);
	}
	IIC1_SCL_L();
	return Temp;
}
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
u8 IIC1_WriteBits(u8 byAD,u8 byRA,u8 bitStart,u8 length,u8 data)//写入多位
{

    u8 b;

    if (IIC1_ReadData(byAD, byRA, &b,1) == 0) {
        u8 mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
        data <<= (8 - length);
        data >>= (7 - bitStart);
        b &= mask;
        b |= data;
        return IIC1_WriteData(byAD, byRA, b);
    } else {
        return 0;
    }
}
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
u8 IIC1_WriteBit(u8 byAD, u8 byRA, u8 bitNum, u8 data)//单次写入位
{
    u8 b;
    IIC1_ReadData(byAD, byRA, &b,1);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return IIC1_WriteData(byAD, byRA, b);
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	IIC1_WriteData
Description       :		Write  bytes through the IIC1 bus
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
int IIC1_WriteData(u8 byAD,u8 byRA,u8 data)//写入数据
{
	u8 i;
	i = i;
	IIC1_Start();
    
	IIC1_WriteReg(byAD);
	if(IIC1_WaitAck() == 0xff)
    {
        printf("error 2B\r\n");
        return 0xff;
    }
    
	IIC1_WriteReg(byRA);
	if(IIC1_WaitAck() == 0xff)
    {
        printf("error 2C\r\n");
        return 0xff;
    }

	IIC1_WriteReg(data);
   
    if(IIC1_WaitAck() == 0xff)
    {
        printf("error 2D\r\n");
        return 0xff;
    }

	IIC1_Stop();
    return 0;
}
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
int IIC1_ReadData(u8 byAD,u8 byRA,u8 *pdata,u8 count)//阅读数据
{
	u8 i;

    IIC1_Start();
	
    IIC1_WriteReg(byAD);
	if(IIC1_WaitAck() == 0xff)
    {
        printf("error 2F\r\n");
        return 0xff;
    }
    
    IIC1_WriteReg(byRA);
	if(IIC1_WaitAck() == 0xff)
    {
        printf("error 2G\r\n");
        return 0xff;
    }
	
    IIC1_Start();
    
    IIC1_WriteReg(byAD+1);
	if(IIC1_WaitAck() == 0xff)
    {
        printf("error 2H\r\n");
        return 0xff;
    }
    
    for(i=0;i<(count-1);i++)
    {
        *pdata=IIC1_ReadReg();
        IIC1_Ack(0);
        pdata++;
    }

    *pdata=IIC1_ReadReg();
    IIC1_Ack(1); 
    IIC1_Stop(); 
    return 0;    
}
u8 I2C_ReadOneByte(unsigned char byAD,unsigned char byRA)//阅读一位
{
	u8 data;
	IIC1_ReadData(byAD,byRA,&data,1);
	return data;
}




