/*----------------------------------------------------------------------------*/
/*
	File Name			:	

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
	#include "stm32f10x_exti_config.h"

    /*---Variable Definition--*/

    /*---Function Definiton---*/

    /*---Macro Definition-----*/

/*----------------------------------------------------------------------------*/
/*****************************************************************************

*****************************************************************************/
void EXTI_Configuration(void)
{
	
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* =======================开启时钟================*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;    	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		//下拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);	 //EXTI0


	EXTI_DeInit();     //将EXIT寄存器重设置为缺省值
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 ;		 //中断线
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt ;  //中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;		//上升沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;		   //使能
	EXTI_Init(&EXTI_InitStructure);	
	EXTI_ClearITPendingBit(EXTI_Line0);	
	EXTI_ClearITPendingBit(EXTI_Line2);
}


