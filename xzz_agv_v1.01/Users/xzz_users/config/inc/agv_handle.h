
#ifndef __AGV_HANDLE_H__
#define __AGV_HANDLE_H__




	
#include<stdio.h>
#include<string.h>
#include "stm32f4xx_usart_config.h"
#include  "BCBGlobalType.h"
#include "stm32f4xx_it.h"

extern Remote_t			RemoteNow;			//Ò£¿ØÐÅÏ¢

extern void Agv_EN(int a);
extern void Agv_Speed(int i,int16_t a);
extern void Agv_Monitoring(void);
//extern  void Agv_Speed(u8 zz);
#endif
