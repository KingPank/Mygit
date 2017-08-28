#include<stdio.h>
#include<string.h>
#include "stm32f4xx.h"
#include "stm32f4xx_usart_config.h"
#include "delay.h"
#include "stm32f4xx_bsp_config.h"
#include "stm32f4xx_it.h"
#include "BCBMpu6050Driver.h"
#include "BCBCtrlIMU.h"


int main()
{
	
//			USART1_Configuration();

			USART2_Configuration();

			USART3_Configuration();

		  IIC1_Confugration();

			MPU6050_Configuation();

		 IMU_init();
			TIM3_Configuration();
		 TIM2_Configuration();

		while(1)
		{

			delay_ms(500);
		}
}