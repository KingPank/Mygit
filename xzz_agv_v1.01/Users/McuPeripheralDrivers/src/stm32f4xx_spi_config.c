/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f10x_spi_config.c
    Description			:
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
	#include "stm32f4xx_spi_config.h"

    /*---Macro Definition-----*/
	/*---Variable Definition--*/
	/*---Function Definiton---*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	SPI_Configuration
Description       :		Configurate the using SPI.
Input parameter   :   	Class			Name		Action
						SPI_TypeDef *	SPI	  		The using SPI Bus(SPI1 SPI2)	
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void SPI_Configuration(SPI_TypeDef *SPI)
{
	if(SPI == SPI1)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;
		SPI_InitTypeDef  SPI_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

		//GPIOFB3,4,5初始化设置
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1); 
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1); 


	//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);
	//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);

		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;						//设置SPI的数据大小:SPI发送接收8位帧结构
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;									//串行同步时钟的空闲状态为高电平
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;								//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;										//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//定义波特率预分频的值:波特率预分频值为256
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
		SPI_InitStructure.SPI_CRCPolynomial = 7;										//CRC值计算的多项式
		SPI_Init(SPI1, &SPI_InitStructure);  									//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

		SPI_Cmd(SPI1, ENABLE); //使能SPI外设

		//	SPI_RW(SPI1,0xff);//启动传输		 
	}
	else
	{
		
	}

}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	SPI_SetSpeed
Description       :		Configurate the all gpio.
Input parameter   :   	Class			Name		Action
						SPI_TypeDef *	SPI	  		The using SPI Bus(SPI1 SPI2)
						uint8_t			SpeedSet	The speed of the spi
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void SPI_SetSpeed(SPI_TypeDef *SPI,uint8_t SpeedSet)
{
		SPI_InitTypeDef SPI_InitStructure;
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    if(SpeedSet==SPI_SPEED_LOW)
    {
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    }
    else
    {
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    }
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(SPI, &SPI_InitStructure);
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	SPI_RW
Description       :		Read and Write
Input parameter   :   	Class			Name		Action	
						SPI_TypeDef *	SPI	  		The using SPI Bus(SPI1 SPI2)
						uint8_t 		data		wirting data
Output parameter  :   	Class			Name		Action	
						uint8_t 					reading data					
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
//uint8_t SPI_RW(SPI_TypeDef *SPI,uint8_t data)
//{ 
//	while((SPI->SR & SPI_I2S_FLAG_TXE)==RESET);
//	SPI->DR = data;
//	while((SPI->SR & SPI_I2S_FLAG_RXNE)==RESET);
//	return(SPI->DR);
//}

//void LCD_WR_REG(uint8_t Index,uint8_t CongfigTemp)
//{
//	*(__IO u16 *) (Bank1_LCD_C) = Index;	
//	*(__IO u16 *) (Bank1_LCD_D) = CongfigTemp;
//}
u8 SPI1_ReadWriteByte(u8 TxData)
  {                                
		 while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}
		SPI_I2S_SendData(SPI1, TxData);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} 
		return SPI_I2S_ReceiveData(SPI1);                  
  }
