/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f10x_time_config.c

    Description			:

    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
    Version&Date		: 	
    Connectot Fuction 	:
    Notes				：	
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
	#include "stm32f4xx_time_config.h"
    /*---Variable Definition--*/
    /*---Function Definiton---*/
  #include "AGV.h"
	void TIM45_Configuration(void);
	void TIM7_Configuration(void);
	
	void TIM2_Configuration(void);
	void TIM2_Start(void);
	
	void TIM3_Configuration(void);
	void TIM3_Start(void);
	uint32_t micros(void);
	void CalcPeriod(float *pperiod);
    /*---Macro Definition-----*/
	volatile unsigned int lastUpdate, now; // 采样周期计数 单位 us
/*----------------------------------------------------------------------------*/


void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_DeInit( TIM7);                              
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);  
	TIM_BaseInitStructure.TIM_Period =1000; 		
	TIM_BaseInitStructure.TIM_Prescaler = 71;  	
	TIM_BaseInitStructure.TIM_ClockDivision = 0; 
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数模式
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM7, &TIM_BaseInitStructure); 
	
	//清中断，以免一启用中断后立即产生中断 
	TIM_ClearFlag(TIM7, TIM_FLAG_Update); 
	//使能TIM2中断源 
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); 
	//TIM2总开关：开启 
	TIM_Cmd(TIM7, ENABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;    			//更新事件 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //抢占优先级0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //响应优先级1 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断 
	NVIC_Init(&NVIC_InitStructure);   

}
/**************************实现函数********************************************
*函数原型:		void Initial_Timer3(void)
*功　　能:	  初始化Tim2  TIM5 将两个定时器级联，以产生一个32位的定时器来提供系统us 级的计时	
输入参数：无
输出参数：没有	
*******************************************************************************/
void TIM45_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5, ENABLE); 
	/* TIM4 configuration*/ 
  /* Time Base configuration 基本配置 配置定时器的时基单元*/
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 0xffff; //自动重装值         
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
  
  TIM_PrescalerConfig(TIM4, 0, TIM_PSCReloadMode_Update);
  /* Disable the TIM4 Update event */
  TIM_UpdateDisableConfig(TIM4, ENABLE);
  /* ----------------------TIM4 Configuration as slave for the TIM5 ----------*/
  /* Select the TIM4 Input Trigger: TIM5 TRGO used as Input Trigger for TIM4*/
  TIM_SelectInputTrigger(TIM4, TIM_TS_ITR2);
  /* Use the External Clock as TIM4 Slave Mode */
  TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_External1);
  /* Enable the TIM4 Master Slave Mode */
  TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);
  TIM_ARRPreloadConfig(TIM4, ENABLE);	
	/* 定时器配置:
	1.设置定时器最大计数值 50000
	2.设置时钟分频系数：TIM_CKD_DIV1
	3. 设置预分频：  1Mhz/50000= 1hz 
	4.定时器计数模式  向上计数模式
	*/		 
  	TIM_TimeBaseStructure.TIM_Period = 0xffff;     
  	TIM_TimeBaseStructure.TIM_Prescaler = 72;	 //1M 的时钟  
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//应用配置到TIM5 
  	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// 使能TIM5重载寄存器ARR
  	TIM_ARRPreloadConfig(TIM5, ENABLE);	

	TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_Reset);
	TIM_UpdateRequestConfig(TIM5, TIM_UpdateSource_Regular);
	/* ----------------------TIM5 Configuration as Master for the TIM4 -----------*/
  	/* Use the TIM5 Update event  as TIM5 Trigger Output(TRGO) */
  	TIM_SelectOutputTrigger(TIM5, TIM_TRGOSource_Update);
  	/* Enable the TIM5 Master Slave Mode */
  	TIM_SelectMasterSlaveMode(TIM5, TIM_MasterSlaveMode_Enable);

  	//启动定时器
	TIM_Cmd(TIM5, ENABLE); 
  TIM_Cmd(TIM4, ENABLE);    
	lastUpdate = micros();//更新时间
 	now = micros();	
}
/**************************实现函数********************************************
*函数原型:		uint32_t micros(void)
*功　　能:	  读取系统运行的时间 ，返回单位为us 的时间数。	
输入参数：无
输出参数：处理器当前时间，从上电开始计时  单位 us
*******************************************************************************/
uint32_t micros(void)
{
 	uint32_t temp=0 ;
 	temp = TIM4->CNT; //读高16位时间
 	temp = temp<<16;
 	temp += TIM5->CNT; //读低16位时间
 	return temp;
}

void CalcPeriod(float *pperiod)
{
	  now = micros();  //读取时间
	  if(now<lastUpdate){ //定时器溢出过了。
	  *pperiod =  ((float)(now + (0xffff- lastUpdate)) / 1000000.0f);
	  }
	  else	{
	  *pperiod =  ((float)(now - lastUpdate) / 1000000.0f);
	  }
	  lastUpdate = now;	//更新时间
}


//自己写的定时器启动还有中断

//void TIM3_Configuration(void)    
//{ 
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
//  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
//    
//  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  
//    
//  TIM_TimeBaseStructure.TIM_Period = 2000;//频率:72MHz  72000000/36000=2000  
//  TIM_TimeBaseStructure.TIM_Prescaler = 35999;//36000-1=35999  
//  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;  
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
//  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
//    
//  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );  
//  TIM_Cmd(TIM3,ENABLE);  
//}  

//void NVIC_Configuration(void)   
//{    
//  NVIC_InitTypeDef NVIC_InitStructure;    
//      
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
//      
//  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
//  NVIC_Init(&NVIC_InitStructure);    
//}

//void TIM3_IRQHandler(void) 

//{
//	
//}
/*void TIM2_Configuration(void)//监控计时器中断
{
	TIM_TimeBaseInitTypeDef  tim;
	NVIC_InitTypeDef         nvic;
	
	nvic.NVIC_IRQChannel = TIM2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority =0;
	nvic.NVIC_IRQChannelSubPriority =1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	tim.TIM_Prescaler = 8400-1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_Period = 10000;
	TIM_TimeBaseInit(TIM2,&tim);// 1S
	
	
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
	TIM2_Start();
}

void TIM2_Start(void)
{
	TIM2->CNT=0;
	TIM_Cmd(TIM2, ENABLE);	 
}
void TIM2_IRQHandler(void)  
{
  if(TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
  {
		AGV_monitoring();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);   	
  }
}




void TIM3_Configuration(void)//速度发送中断
{
	TIM_TimeBaseInitTypeDef  tim;
	NVIC_InitTypeDef         nvic;
	
	nvic.NVIC_IRQChannel = TIM3_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority =0;
	nvic.NVIC_IRQChannelSubPriority =1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	tim.TIM_Prescaler = 8400-1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_Period = 10000;
	TIM_TimeBaseInit(TIM3,&tim);// 1S
	
	
	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
	TIM3_Start();
}

void TIM3_Start(void)
{
	TIM3->CNT=0;
	TIM_Cmd(TIM3, ENABLE);	 
}
void TIM3_IRQHandler(void)  
{
  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET) 
  {
		int i=1;
		u16 a=50;
		AGV_SD(i,a);
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);   	
  }
}
*/

