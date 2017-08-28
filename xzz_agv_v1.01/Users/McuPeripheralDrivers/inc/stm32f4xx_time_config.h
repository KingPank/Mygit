/**************************************************
 *
 * Intrinsic
 *
 * Copyright
 *
 * $Revision:
 *
 **************************************************/
#ifndef __STM32F4XXTIMECONFIG_H__
#define __STM32F4XXTIMECONFIG_H__

    //Head Files
	#include "stm32f4xx.h"
    //Function Definition
	extern	void 	TIM7_Configuration(void);
	extern 	void TIM45_Configuration(void);
	extern	void TIM2_Configuration(void);
	extern  void TIM3_Configuration(void);
	
	extern	uint32_t micros(void);
	extern  void CalcPeriod(float *pperiod);
    //Constant Definition
    //Data Type Definition

    //Variable Definiti


#endif /* __MAIN_H */

