#include "stm32f4xx_it.h"
//#include "BCBGlobalFunc.h"	
#include<stdio.h>
#include<string.h>
#include "stm32f4xx_usart_config.h"
#include "MTSProtocol.h"
#include "agv_handle.h"
#include "BCBCtrlIMU.h"
#include "stdint.h"
#include "BCBGLOBALTYPE.h"
#include "delay.h"
#include "agv_deal.h"
//#include "CheckError.h"
/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
	
	void TIM2_Start(void);
	void TIM3_Start(void);
	void TIM2_Configuration(void);
	void TIM3_Configuration(void);
	
	void EXTI0_IRQHandler(void);
	void EXTI1_IRQHandler(void);
	void EXTI2_IRQHandler(void);
	void EXTI3_IRQHandler(void);
	void EXTI4_IRQHandler(void);
	void EXTI5_10_IRQHandler(void);
	
	//void CAN1_TX_IRQHandler(void);
	  void AGVRecv_send_Data(u8 *dma_RxBuffer);
	
	
	#define  AGV_send_SDBZ  0x01
	#define  AGV_send_JKBZ  0x11
	int AGV_send_bz=AGV_send_JKBZ;
	
	
	 int16_t YKSD=0;
	
//	void AGVRecv_USART1_Data(u8 data ,u8 *Rx_Buffer);

void AGVRecv_USART1_Data(u8 *data ,u8 *Rx_Buffer);
	
	
	int i=1;
	u16 a=50;
	
	

	
	
	
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
  
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	CAN1_RX0_IRQHandler
Description       :		
Input parameter   :   	Class			Name		Action
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		与电机通信
*/
/*----------------------------------------------------------------------------*/




//void CAN1_TX_IRQHandler(void)
//{
//	if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
//	{
//	 CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
////		Can1SendFlag = 1;
//	}
//}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	TIM7_IRQHandler
Description       :		
Input parameter   :   	Class			Name		Action
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		检测定时器
*/
/*----------------------------------------------------------------------------*/







void TIM2_Configuration(void)//监控计时器中断
{
	TIM_TimeBaseInitTypeDef  tim;
	NVIC_InitTypeDef         nvic;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	tim.TIM_Prescaler = 72 - 1;
	//tim.TIM_Prescaler = 22500 - 1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_Period = 10000;
	TIM_TimeBaseInit(TIM2,&tim);// 1S
	
	nvic.NVIC_IRQChannel = TIM2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority =2;
	nvic.NVIC_IRQChannelSubPriority =2;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
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
		

		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);   	
  }
}




void TIM3_Configuration(void)//速度发送中断
{
	TIM_TimeBaseInitTypeDef  tim;
	NVIC_InitTypeDef         nvic;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		
	tim.TIM_Prescaler = 72-1;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_Period = 10000;
	TIM_TimeBaseInit(TIM3,&tim);// 1S
	
	nvic.NVIC_IRQChannel = TIM3_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority =3;
	nvic.NVIC_IRQChannelSubPriority =0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
		
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

	static int MARK=1;

  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET) 
  {
			  	
    if(MARK==1)
		{
			MARK=2;
			Agv_Speed(1,YKSD);
		}
		else if(MARK==2)
		{
			MARK=3;
			Agv_Speed(2,YKSD);
		}
		else if(MARK==3)
		{
			MARK=4;
			Agv_Monitoring();

		}
		else if(MARK==4)
		{
			MARK=1;
			AGVRecv_send_Data(G_Dma_U3_RxBuffer);
		}

		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);   	
  }
}



void EXTI0_IRQHandler(void)
{  

	delay_ms(10);
    if(EXTI_GetITStatus(EXTI_Line0))
    {
				//USART2_SendByte(j);
			   Agv_EN(1);
		     //	Agv_Speed(i,a);
        EXTI_ClearITPendingBit(EXTI_Line0);

    }
}

void EXTI3_IRQHandler(void)
{  
	//int i=1,a=100,j=0x33;
	delay_ms(20);
    if(EXTI_GetITStatus(EXTI_Line3))
    {
			   // USART2_SendByte(j);
					a--;
			   Agv_Speed(i,a);
		     //	Agv_EN(i);
          EXTI_ClearITPendingBit(EXTI_Line3);

    }
}

 
void EXTI2_IRQHandler(void)
{   
	delay_ms(20);
    if(EXTI_GetITStatus(EXTI_Line2))
    { 

        EXTI_ClearITPendingBit(EXTI_Line2);

    }
}


void EXTI4_IRQHandler(void)
{  

	delay_ms(10);
    if(EXTI_GetITStatus(EXTI_Line4))
    {

          EXTI_ClearITPendingBit(EXTI_Line4);

    }
}



#define TAKE_BIT_HI(src,nbit) ((src)>>(8-(nbit)))
#define TAKE_BIT_LO(src,nbit) ((src)&(~(0xFF<<(nbit))))


Remote_t			RemoteNow;	
void DMA1_Stream5_IRQHandler(void)
{
    //s16_u KZ_sd;
	 
	 
    if(DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5))
			{
					DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);
					DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);
					sbus_channel_temp[0] = (sbus_rx_buffer[0]| (sbus_rx_buffer[1] << 8)) & 0x07ff;
					sbus_channel_temp[1] = ((sbus_rx_buffer[1] >> 3) | (sbus_rx_buffer[2] << 5)) & 0x07ff;
					sbus_channel_temp[2] = ((sbus_rx_buffer[2] >> 6) | (sbus_rx_buffer[3] << 2) | (sbus_rx_buffer[4] << 10)) & 0x07ff;
					sbus_channel_temp[3] = ((sbus_rx_buffer[4] >> 1) | (sbus_rx_buffer[5] << 7)) & 0x07ff;
					sbus_channel_temp[4] = ((sbus_rx_buffer[5] >> 4)& 0x000C) >> 2;//radio_switch_left
					sbus_channel_temp[5] = ((sbus_rx_buffer[5] >> 4)& 0x0003);//radio_switch_right
					//源数据 364 - 1024 - 1684/ 之间为660 - 660 
					RemoteNow.ThrTar = (sbus_channel_temp[3] - 1024 );
					RemoteNow.RolTar  = (sbus_channel_temp[2] - 1024 );
					RemoteNow.PitTar = (sbus_channel_temp[1] - 1024 );
					RemoteNow.YawTar = (sbus_channel_temp[0] - 1024 );
					
					
						
					if( (RemoteNow.ThrTar > 660)||(RemoteNow.ThrTar < -660)||
						(RemoteNow.YawTar > 660)||(RemoteNow.YawTar < -660)||
						(RemoteNow.PitTar > 660)||(RemoteNow.PitTar < -660)||
						(RemoteNow.RolTar > 660)||(RemoteNow.RolTar < -660)
						)
					{
						RemoteNow.ThrTar = 0;
						RemoteNow.YawTar = 0;
						RemoteNow.PitTar = 0;
						RemoteNow.RolTar = 0;
					}
		}
		
		YKSD = RemoteNow.ThrTar;


}




