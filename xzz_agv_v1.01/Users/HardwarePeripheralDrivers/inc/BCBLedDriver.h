#ifndef __BCBKEYDRIVER_H__
#define __BCBKEYDRIVER_H__
   #include "BCBGlobalType.h"
void Led_Configuration(void);


	#define  LED_GREEN_ON()      GPIO_ResetBits(GPIOA, GPIO_Pin_2)
	#define  LED_GREEN_OFF()     GPIO_SetBits(GPIOA, GPIO_Pin_2)
	#define  LED_GREEN_TOGGLE()  GPIO_ToggleBits(GPIOA, GPIO_Pin_2)

	#define  LED_RED_ON()        GPIO_ResetBits(GPIOA, GPIO_Pin_3)
	#define  LED_RED_OFF()       GPIO_SetBits(GPIOA, GPIO_Pin_3)
	#define  LED_RED_TOGGLE()    GPIO_ToggleBits(GPIOA, GPIO_Pin_3)


#endif
