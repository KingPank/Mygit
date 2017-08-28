#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

		void NMI_Handler(void);
		void HardFault_Handler(void);
		void MemManage_Handler(void);
		void BusFault_Handler(void);
		void UsageFault_Handler(void);
		void SVC_Handler(void);
		void DebugMon_Handler(void);
		void PendSV_Handler(void);
		void SysTick_Handler(void);
		extern	 void TIM2_Configuration(void);
		extern	 void TIM3_Configuration(void); 
		extern void TIM2_Start(void);	 
		extern	void TIM3_Start(void);



		extern	void EXTI0_IRQHandler(void);
		extern	void EXTI1_IRQHandler(void);
		extern	void EXTI2_IRQHandler(void);
		extern	void EXTI3_IRQHandler(void);
		extern	void EXTI4_IRQHandler(void);
		extern	void EXTI5_10_IRQHandler(void);
//    extern  void CAN1_TX_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
