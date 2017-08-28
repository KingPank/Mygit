/*----------------------------------------------------------------------------*/
/*
	File Name			:	stm32f4xx_Bsp_config.c
	Description			:	
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.33>  V1.0
	Connector Fuction 	:
	Notes	：
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "stm32f4xx_bsp_config.h"
	/*---Variable Definition--*/
	/*---Function Definiton---*/
	void NVIC_Configuration(void);	
	static volatile ErrorStatus HSEStartUpStatus = SUCCESS;
	/*---Macro Definition-----*/

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	Bsp_Configuration
Description       :	 	
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		
*/
/*----------------------------------------------------------------------------*/
void  Bsp_Configuration()
{
	NVIC_Configuration();	 
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	NVIC_Configuration
Description       :	 	
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		
*/
/*----------------------------------------------------------------------------*/
void NVIC_Configuration(void)
{ 
  	NVIC_InitTypeDef NVIC_InitStructure;
//	#ifdef  VECT_TAB_RAM  
//	  /* Set the Vector Table base location at 0x20000000 */ 
//	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
//	#else  /* VECT_TAB_FLASH  */
//	  /* Set the Vector Table base location at 0x08000000 */ 
//	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
//	#endif
//   	/* Configure the STICK Preemption Priority Bits */  
////	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;	 
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);	
//	/* Enable the USARTy Interrupt */
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  	

	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;    		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;       
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          
	NVIC_Init(&NVIC_InitStructure);   
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
    
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;    		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           
	NVIC_Init(&NVIC_InitStructure);   
  
}



//NVIC_InitTypeDef NVIC_InitStructure;
////	#ifdef  VECT_TAB_RAM  
////	  /* Set the Vector Table base location at 0x20000000 */ 
////	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
////	#else  /* VECT_TAB_FLASH  */
////	  /* Set the Vector Table base location at 0x08000000 */ 
////	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
////	#endif
////   	/* Configure the STICK Preemption Priority Bits */  
//////	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;	 
//////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitStructure);	
////	/* Enable the USARTy Interrupt */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;    		
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;       
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          
//	NVIC_Init(&NVIC_InitStructure);   
//	
////	NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_IRQn;
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitStructure);

////	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;		
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitStructure);
////   
////	/* Enable the TIM2 gloabal Interrupt [??TIM2????]*/


//	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;    			//更新事件 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //抢占优先级0 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //响应优先级1 
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断 
//	NVIC_Init(&NVIC_InitStructure);   
////	NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitStructure);

////	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;  
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
////	NVIC_Init(&NVIC_InitStructure);


//	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);    
//    
//	    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//	
//	
//		
//    
//	
//	
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}

