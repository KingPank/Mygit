#include "delay.h"

#include "stm32f4xx.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用OS,则包括下面的头文件（以ucos为例）即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//支持OS时，使用	  
#endif


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

void delay_10ns(unsigned int t)
{
	int a=2*t;
	while(a--);
}

































