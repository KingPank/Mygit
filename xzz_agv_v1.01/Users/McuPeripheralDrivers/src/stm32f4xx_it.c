#include "stm32f4xx_it.h"
//#include "BCBGlobalFunc.h"	
#include<stdio.h>
#include<string.h>
#include "stm32f4xx_usart_config.h"
#include "MTSProtocol.h"
#include "AGB_GG.h"
#include "AGB_GG.h"
#include "BCBCtrlIMU.h"
#include "stdint.h"
#include "BCBGLOBALTYPE.h"

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
	
	
	
	void delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=42000;
		while(a--);
	}
}
void delay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=40;
		while(a--);
	}
}
	
	
	
	
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

#define agv1
u8 AGV_SJ[10]={0};
   int bz1=0;
u8 AGV_JK[10]={0};
   int bz3=0;
int16_t Rx_Buffer_sd;

#define	 Recv_bz1   0x01;
#define	 Recv_bz2   0x11;

 
u8 Rx_Index=0;
u8 rx_data_bz=0;
//unsigned int Rx_Index=0;
unsigned int Rx_len=2;
u8 bz;
//void AGVRecv_USART1_Data(u8 data ,u8 *Rx_Buffer)//上位机发送指令解析
//{
//	int n;
//	u8 sum;
//		
//    if(data == 0xa5 && bz == 0)
//  	{
// 		  bz=Recv_bz1;
//  		Rx_Index++;
//  	}	
//	 else if(data==0x5a && bz==0x01)
//  	{	
//    		bz=Recv_bz2;
//    		Rx_Index=0; 		
//  	} 
//    else	if(bz==0x11)
//  	{
//				Rx_Buffer[Rx_Index]=data;
//				Rx_Index++;
//		
//				if(Rx_Buffer[0]==Rx_Index)
//				{		
//					 AGV_send_bz=AGV_send_SDBZ;
//					
//					Rx_Buffer_sd=Rx_Buffer[5]|(Rx_Buffer[6]&0x00ff<<8);	
//					for(n=0,sum=0;n<Rx_Index;n++)
//					{
//						if(n!=2)
//						{
//						  sum=+Rx_Buffer[n];
//						}
//					}		
//			
//			
////					if(Rx_Buffer[2]==sum)
////					{
//							switch (Rx_Buffer[3])
//						{
//							case 0x01:AGV_EN(0);
//								break;
//							case 0x02:AGV_EN(1);
//								break;
//							case 0x03:AGV_SD(Rx_Buffer[2],Rx_Buffer_sd);
//								break;
//							case 0x04:
//								break;
//						}	
//		//	    }
//				
//					bz=0;
//					Rx_Index=0;
//				}
//				
//     }
//		else if(bz==0x11 && Rx_Index > Rx_Buffer[0])
//		{
//			bz=0;
//		  Rx_Index=0;
//			for(n=0;n>50;n++)
//			{
//			Rx_Buffer[n]=0;

//			}
//		}		
//}
void AGVRecv_USART1_Data(u8 *data ,u8 *Rx_Buffer)//上位机发送指令解析
{
	int n,wcbz=0;
	u8 sum;	
    if(*data == 0xa5 && bz == 0)
  	{
 		  bz=Recv_bz1;
  		Rx_Index++;
	     if(*(data+1)==0x5a && bz==0x01)
			 {
    		bz=Recv_bz2;
    		Rx_Index=0; 		
			 }
    	if(bz==0x11)
  	   {
						for(rx_data_bz=0;rx_data_bz<12;rx_data_bz++)
					 {
						Rx_Buffer[rx_data_bz]=*(data+2+rx_data_bz);
						Rx_Index++;
					 }
//				if(Rx_Buffer[0]==Rx_Index)
//				{		
					Rx_Buffer_sd=Rx_Buffer[5]|(Rx_Buffer[6]&0x00ff<<8);	
					 if(Rx_Buffer_sd > 10000)
					 {
						 Rx_Buffer_sd=Rx_Buffer_sd-65536;
					 }
					for(n=0,sum=0;n<Rx_Index;n++)
					{
						if(n!=2)
						{
						  sum=+Rx_Buffer[n];
						}
					}			
							switch (Rx_Buffer[3])
						{
							case 0x01:AGV_EN(0);
								break;
							case 0x02:AGV_EN(1);
								break;
							case 0x03:AGV_SD(Rx_Buffer[2],Rx_Buffer_sd);
								break;
							case 0x04:
								break;
						}		
//                 if(Rx_Buffer[3]==0x01)
//								 {
//										AGV_EN(0);
//									 wcbz=1;
//								 }
//                  else if(Rx_Buffer[3]==0x02)
//									{
//									  AGV_EN(1);	
//									}
//                  else if(Rx_Buffer[3]==0x03)
//									{
//									  AGV_SD(Rx_Buffer[2],Rx_Buffer_sd);										
//									}
//                   else ;									
				}
			
			}
		  	bz=0;
				Rx_Index=0;
				for(n=0;n<50;n++)
				{
					Rx_Buffer[n]=0;
				}
		
     //}
//		else if(bz==0x11 && Rx_Index > (Rx_Buffer[0]+10))
//		{
//			bz=0;
//			Rx_Index=0;
//			rx_data_bz=0;
//			for(n=0;n>50;n++)
//			{
//			Rx_Buffer[n]=0;

//			}
//		}		
}



//void USART1_IRQHandler(void)
//{
//	u8 data;
////	u8 bz=0;
//   
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//	{
//		
//		data=USART_ReceiveData(USART1);

//		AGVRecv_USART1_Data(data ,Rx_Buffer);
//		
////	//	AGVRecv_USART1_Data(data);
////	  AGV_SJ[bz1]=data;
////		bz1++;
////		if(bz1==10)
////		{
////			USART3_SendBytes(AGV_SJ,10);
////			bz1=0;
////		}
//		USART_ClearFlag(USART1, USART_IT_RXNE);
//    USART_ClearITPendingBit(USART1, USART_IT_RXNE); 
//	}
//}



u8 Rx_Buffer_XCSD[15];
int sj=0;
u8 Rx_Buffer_sj[10];

void AGVRecv_send_Data(u8 *dma_RxBuffer)//读取小车数据打包
{
	u8 n;
	u16 sum;
    Angle_t olj;
	  Gyro_t gyro;
	 float_u Z_olj;
	
	if(*(dma_RxBuffer+1)!=0x80&&*(dma_RxBuffer+2)==0xf9&&*(dma_RxBuffer+3)==0x60&&*(dma_RxBuffer+4)==0x18)
	{	
	for(sj=0;sj<10;sj++)
	{
		Rx_Buffer_sj[sj]=*(dma_RxBuffer+sj);
	}

		 Rx_Buffer_XCSD[0]=0xa5;
		 Rx_Buffer_XCSD[1]=0x5a;
		 Rx_Buffer_XCSD[2]=0x0f;
		 Rx_Buffer_XCSD[3]=0;
		 Rx_Buffer_XCSD[5]=0x01;
	   Rx_Buffer_XCSD[6]= Rx_Buffer_sj[0];
     if(Rx_Buffer_sj[1]!=0x80&&Rx_Buffer_sj[2]==0xf9&&Rx_Buffer_sj[3]==0x60&&Rx_Buffer_sj[4]==0x18)
		 {			 
		    Rx_Buffer_XCSD[7]= Rx_Buffer_sj[5];
			  Rx_Buffer_XCSD[8]= Rx_Buffer_sj[6];
			  Rx_Buffer_XCSD[9]= Rx_Buffer_sj[7];
			  Rx_Buffer_XCSD[10]= Rx_Buffer_sj[8];
		 
   IMU_getYawPitchRoll(&olj,&gyro,0.007);
      Z_olj.fdata=olj.Yaw;
			  Rx_Buffer_XCSD[11]=Z_olj.udata[0];
			  Rx_Buffer_XCSD[12]=Z_olj.udata[1];
			  Rx_Buffer_XCSD[13]=Z_olj.udata[2];
			  Rx_Buffer_XCSD[14]=Z_olj.udata[3];
		for(n=0,sum=0;n<15;n++)
		 {
			 if(n!=4)
			 {
				 
			 sum = sum +Rx_Buffer_sj[n];
		 
			 }
		 }
		 Rx_Buffer_XCSD[4]=sum;
		
		 u1_SendBytesInfoProc(Rx_Buffer_XCSD,15);
		 
		 }

	 }
//		 for(sj=0;sj<15;sj++)
//		 {
//		 Rx_Buffer_XCSD[sj]=0;
//		 }
}







//void USART3_IRQHandler(void)
//{
//		u8 data3;
//	
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
//	{
//		
//	
//		data3=USART_ReceiveData(USART3);
//	//	AGVRecv_send_Data(data3);
//		//USART1_SendBytes(Rx_Buffer_XCSD,9);
//	//	USART1_SendByte(data3);
//	  AGV_JK[bz3]=data3;
//		bz3++;
//		if(bz3==10)
//		{
//		if(AGV_send_bz==AGV_send_JKBZ)
//		{
//			AGVRecv_send_Data(AGV_JK);
//		}
//			//USART1_SendBytes(AGV_JK,10);
//				AGV_send_bz=AGV_send_JKBZ;
//			bz3=0;
//		}
//		USART_ClearFlag(USART3, USART_IT_RXNE);
//    USART_ClearITPendingBit(USART3, USART_IT_RXNE); 
//	  
//	}
//}





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
//void TIM2_Stop(void)
//{
//  TIM_Cmd(TIM2, DISABLE);
//}

void TIM2_Start(void)
{
	TIM2->CNT=0;
	TIM_Cmd(TIM2, ENABLE);	 
}
void TIM2_IRQHandler(void)  
{
	  static int j=0;
	
 if(TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
  {
		

//	if(AGV_send_bz==AGV_send_JKBZ)
//	{
//		 	if(j==0)
//			  {
				
//					j=1;
//	USART1_SendBytes(Rx_Buffer_XCSD,9);
		
//				}
//				if(j==1)
//				{  
//					  j=0;
					//	AGV_monitoring();
					
//			}
//	  
//		}	
		  //USART3_SendBytes(AGV_JK,10);
			
  	


	//  printf(" Rol=%f  Pit=%f  Yaw=%f \n",olj.Rol,olj.Pit, olj.Yaw);
		//printf("gyroRol=%f  gyroPit=%f gyroYaw=%f \n",gyro.Rol,gyro.Pit, gyro.Yaw);	
	//	AGV_SD(Rx_Buffer[1],Rx_Buffer_sd);
	//	printf("1  ");
		
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
	static int j=0;
	static int YK_bz=1;
	int it;
  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!= RESET) 
  {
			  	
    if(YK_bz==1)
		{
			YK_bz=2;
			AGV_SD(1,YKSD);
		}
		else if(YK_bz==2)
		{
			YK_bz=3;
			AGV_SD(2,YKSD);
		}
		else if(YK_bz==3)
		{
			YK_bz=4;
			AGV_monitoring();

		}
			else if(YK_bz==4)
			{
				YK_bz=1;
				 AGVRecv_send_Data(dma_RxBuffer);
			}
			
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);   	
  }
}



void EXTI0_IRQHandler(void)
{  
//	int i=1,a=100,j=0x00;
	delay_ms(10);
    if(EXTI_GetITStatus(EXTI_Line0))
    {
				//USART2_SendByte(j);
			   AGV_EN(1);
		     //	AGV_SD(i,a);
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
			   AGV_SD(i,a);
		     //	AGV_EN(i);
          EXTI_ClearITPendingBit(EXTI_Line3);

    }
}

 
void EXTI2_IRQHandler(void)
{   
	delay_ms(20);
    if(EXTI_GetITStatus(EXTI_Line2))
    { 
			//USART2_SendByte(j);	

        a++;			
		   AGV_SD(i,a);
        EXTI_ClearITPendingBit(EXTI_Line2);

    }
}


void EXTI4_IRQHandler(void)
{  
	int i=1,a=100;
	int j=0x44;
	delay_ms(10);
    if(EXTI_GetITStatus(EXTI_Line4))
    {
			    USART2_SendByte(j);
					
		     //	AGV_EN(i);
          EXTI_ClearITPendingBit(EXTI_Line4);

    }
}

//void EXTI3_IRQHandler(void)
//{
//	GPIO_SetBits(GPIOD,GPIO_Pin_3);     
//	EXTI_ClearITPendingBit(EXTI_Line3);
//		  int i=1;
//		int a=0;
//		AGV_SD(i,a);
//	
//	EXTI_ClearITPendingBit(EXTI_Line5);
//}
//void EXTI10_5_IRQHandler(void)
//{
//			  int i=2;
//		int a=0;
//		AGV_SD(i,a);
//	EXTI_ClearITPendingBit(EXTI_Line5);
//}






//volatile u8 Rx_Buffer_XCSD[13];
//int sj=0;
//u8 Rx_Buffer_sj[10];
//void AGVRecv_send_Data(u8 data)//读取小车数据打包
//{
//	u8 data_jk,n;
//	u16 sum;
//  data_jk=USART_ReceiveData(USART3);
//  Rx_Buffer_sj[sj]=data_jk;
//	sj++;
//	if(sj==10)
//	{
//		 Rx_Buffer_XCSD[0]=0xa5;
//		 Rx_Buffer_XCSD[1]=0x5a;
//		 Rx_Buffer_XCSD[2]=9;
//		 Rx_Buffer_XCSD[3]=0;
//		 Rx_Buffer_XCSD[5]=0x01;
//		 Rx_Buffer_XCSD[6]= Rx_Buffer_sj[0];
//     if(Rx_Buffer_sj[1]!=0x80&&Rx_Buffer_sj[2]==0xf9&&Rx_Buffer_sj[3]==0x60&&Rx_Buffer_sj[4]==0x18)
//		 {			 
//		    Rx_Buffer_XCSD[7]= Rx_Buffer_sj[5];
//			  Rx_Buffer_XCSD[8]= Rx_Buffer_sj[6];
//		 }
//		 else if(Rx_Buffer_sj[1]==0x80)
//		 {
//			  Rx_Buffer_XCSD[7]=0x00;
//			  Rx_Buffer_XCSD[8]=0x00;
//		 }
//		 else
//		 {
//			 Rx_Buffer_XCSD[7]=0x00;
//			 Rx_Buffer_XCSD[8]=0x01;
//		 }
//		 for(n=0,sum=0;n<9;n++)
//		 {
//			 if(n!=4)
//			 {
//				 
//			 sum = sum + Rx_Buffer_XCSD[n];
//		 
//			 }
//		 }
//		 Rx_Buffer_XCSD[4]=sum;
//		 
//		 sj=0;
//	}
//}
#define TAKE_BIT_HI(src,nbit) ((src)>>(8-(nbit)))
#define TAKE_BIT_LO(src,nbit) ((src)&(~(0xFF<<(nbit))))



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

//     KZ_sd.sdata=RemoteNow.ThrTar;
//	dma_u1_RxBuffer[7]  =  KZ_sd.udata[0];
//  dma_u1_RxBuffer[8]  =  KZ_sd.udata[1];

}




//void DCMI_IRQHandler(void)
//{
//  if(DCMI_GetITStatus(DCMI_IT_FRAME)== SET) 
//  { 
//	TimeOutInfo.Dis2k.Cnt = 0;										/*Clear the TimeOut DMA Cnt*/
//    //ping pang control 
//	DMA_Cmd(DMA2_Stream1, DISABLE);  
//	StartFlag = 1;
//    // put recving data in  DmaDcmiConfig->pNode0Data
//    if ( DmaDcmiConfig.NodeRecvingNum == 0)     					/*Reced 1 Completed*/
//    {   
//        
//        DmaDcmiConfig.NodeRecvdFlag = NODEFLAG0; 					/*Node Flag*/           
//        DmaDcmiConfig.NodeRecvingNum = 1;  							/*Switch Memory Flag*/
//	
//		DMA2_Stream1->M0AR = (uint32_t)(DmaDcmiConfig.pNodeData[1]);/*Switch Memory*/
//		DMA2_Stream1->NDTR = 1024;
//    }
//    // put recving data in  DmaDcmiConfig->pNode1Data
//    else if( DmaDcmiConfig.NodeRecvingNum == 1)  					/*Reced 0 Completed*/
//    {
//        DmaDcmiConfig.NodeRecvdFlag = NODEFLAG1;       				/*Node Flag*/
//        DmaDcmiConfig.NodeRecvingNum = 0;							/*Switch Memory Flag*/

//		DMA2_Stream1->M0AR = (uint32_t)(DmaDcmiConfig.pNodeData[0]);/*Switch Memory*/
//		DMA2_Stream1->NDTR = 1024;
//    }
//		DMA_Cmd(DMA2_Stream1, ENABLE);  	
//    DCMI_ClearITPendingBit(DCMI_IT_FRAME);
//    DCMI_ClearFlag(DCMI_IT_FRAME); 
//	
//	DMADCMIInterruptFlag = 1;
// 	StartFlag = 0;
//  }
//}



