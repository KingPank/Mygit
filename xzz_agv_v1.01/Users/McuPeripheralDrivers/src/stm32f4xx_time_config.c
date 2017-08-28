/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f10x_time_config.c

    Description			:

    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
    Version&Date		: 	
    Connectot Fuction 	:
    Notes				��	
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
	volatile unsigned int lastUpdate, now; // �������ڼ��� ��λ us
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
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   //���ϼ���ģʽ
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM7, &TIM_BaseInitStructure); 
	
	//���жϣ�����һ�����жϺ����������ж� 
	TIM_ClearFlag(TIM7, TIM_FLAG_Update); 
	//ʹ��TIM2�ж�Դ 
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); 
	//TIM2�ܿ��أ����� 
	TIM_Cmd(TIM7, ENABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;    			//�����¼� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //��ռ���ȼ�0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //��Ӧ���ȼ�1 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж� 
	NVIC_Init(&NVIC_InitStructure);   

}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void Initial_Timer3(void)
*��������:	  ��ʼ��Tim2  TIM5 ��������ʱ���������Բ���һ��32λ�Ķ�ʱ�����ṩϵͳus ���ļ�ʱ	
�����������
���������û��	
*******************************************************************************/
void TIM45_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5, ENABLE); 
	/* TIM4 configuration*/ 
  /* Time Base configuration �������� ���ö�ʱ����ʱ����Ԫ*/
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 0xffff; //�Զ���װֵ         
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
	/* ��ʱ������:
	1.���ö�ʱ��������ֵ 50000
	2.����ʱ�ӷ�Ƶϵ����TIM_CKD_DIV1
	3. ����Ԥ��Ƶ��  1Mhz/50000= 1hz 
	4.��ʱ������ģʽ  ���ϼ���ģʽ
	*/		 
  	TIM_TimeBaseStructure.TIM_Period = 0xffff;     
  	TIM_TimeBaseStructure.TIM_Prescaler = 72;	 //1M ��ʱ��  
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	//Ӧ�����õ�TIM5 
  	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// ʹ��TIM5���ؼĴ���ARR
  	TIM_ARRPreloadConfig(TIM5, ENABLE);	

	TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_Reset);
	TIM_UpdateRequestConfig(TIM5, TIM_UpdateSource_Regular);
	/* ----------------------TIM5 Configuration as Master for the TIM4 -----------*/
  	/* Use the TIM5 Update event  as TIM5 Trigger Output(TRGO) */
  	TIM_SelectOutputTrigger(TIM5, TIM_TRGOSource_Update);
  	/* Enable the TIM5 Master Slave Mode */
  	TIM_SelectMasterSlaveMode(TIM5, TIM_MasterSlaveMode_Enable);

  	//������ʱ��
	TIM_Cmd(TIM5, ENABLE); 
  TIM_Cmd(TIM4, ENABLE);    
	lastUpdate = micros();//����ʱ��
 	now = micros();	
}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		uint32_t micros(void)
*��������:	  ��ȡϵͳ���е�ʱ�� �����ص�λΪus ��ʱ������	
�����������
�����������������ǰʱ�䣬���ϵ翪ʼ��ʱ  ��λ us
*******************************************************************************/
uint32_t micros(void)
{
 	uint32_t temp=0 ;
 	temp = TIM4->CNT; //����16λʱ��
 	temp = temp<<16;
 	temp += TIM5->CNT; //����16λʱ��
 	return temp;
}

void CalcPeriod(float *pperiod)
{
	  now = micros();  //��ȡʱ��
	  if(now<lastUpdate){ //��ʱ��������ˡ�
	  *pperiod =  ((float)(now + (0xffff- lastUpdate)) / 1000000.0f);
	  }
	  else	{
	  *pperiod =  ((float)(now - lastUpdate) / 1000000.0f);
	  }
	  lastUpdate = now;	//����ʱ��
}


//�Լ�д�Ķ�ʱ�����������ж�

//void TIM3_Configuration(void)    
//{ 
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
//  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
//    
//  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  
//    
//  TIM_TimeBaseStructure.TIM_Period = 2000;//Ƶ��:72MHz  72000000/36000=2000  
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
/*void TIM2_Configuration(void)//��ؼ�ʱ���ж�
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




void TIM3_Configuration(void)//�ٶȷ����ж�
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

