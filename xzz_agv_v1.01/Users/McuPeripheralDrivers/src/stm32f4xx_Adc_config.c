/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_Adc_config.h
    Description			:	Provide the interface io to the app
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2015.4.28>  V1.0
    Connector Fuction 	:
    Notes	£º
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
	#include "stm32f4xx_Adc_config.h"
    /*---Variable Definition--*/
	vu16 AD_Value[ADCCHNNELCNT][ADCCHANNELNUM]; 																		    
    /*---Function Definiton---*/
	void ADC_Configuration(void);
	void ADCReadData(float *data,unsigned char channel);
	/*---Macro Definition-----*/	
	
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	ADC_Configuration
Description       :	 	Configurate the adc.
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		The code is copyed in the net. Then, there is using the
						DMA(Direct Memory Address)
*/
/*----------------------------------------------------------------------------*/
void ADC_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;	     
  	ADC_InitTypeDef ADC_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	
	ADC_DeInit(ADC1); 											//将外设 ADC1 的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 			//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode =ENABLE; 				//模数转换工作在扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 			//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //外部触发转换关闭
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 		//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = ADCCHANNELNUM; 		//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure); 						//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
																//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
																//ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_239Cycles5 );
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 4, ADC_SampleTime_239Cycles5 );
	
	ADC_DMACmd(ADC1, ENABLE);									// 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）		
	ADC_Cmd(ADC1, ENABLE); 										//使能指定的ADC1	
	ADC_ResetCalibration(ADC1); 								//复位指定的ADC1的校准寄存器	
	while(ADC_GetResetCalibrationStatus(ADC1)); 				//获取ADC1复位校准寄存器的状态,设置状态则等待		
	ADC_StartCalibration(ADC1); 								//开始指定ADC1的校准状态
	while(ADC_GetCalibrationStatus(ADC1)); 						//获取指定ADC1的校准程序,设置状态则等待
										   	

	DMA_DeInit(DMA1_Channel1); 									//将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; 	//DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value; 		//DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 			//内存作为数据传输的目的地
	DMA_InitStructure.DMA_BufferSize = ADCCHANNELNUM*ADCCHNNELCNT; //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 	//内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 			//工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 		//DMA通道 x拥有高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 				//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); 				//根据DMA_InitStruct中指定的参数初始化DMA的通道 
  	/* Enable DMA1 channel1 */
  	DMA_Cmd(DMA1_Channel1, ENABLE);	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);	 	
}

void ADCReadData(float *data,unsigned char channel)
{
	unsigned char i;
	for( i = 0; i < ADCCHNNELCNT; i++)
	{
		*data = AD_Value[i][channel];
	}
}

