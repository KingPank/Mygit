

#ifndef __AGV_GG_H__
#define __AGV_GG_H__



#include "stm32f4xx_it.h"
	
#include<stdio.h>
#include<string.h>
#include "stm32f4xx_usart_config.h"

#include  "BCBGlobalType.h"


extern Remote_t			RemoteNow;			//Ò£¿ØÐÅÏ¢

extern void AGV_EN(int a);
extern void AGV_SD(int i,int16_t a);
extern void AGV_monitoring(void);
//extern  void AGV_sd(u8 zz);
#endif
