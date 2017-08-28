#ifndef __AGV_DEAL_H
#define __AGV_DEAL_H 			   
#include "stm32f4xx.h"

extern void AGVRecv_send_Data(u8 *dma_RxBuffer);
extern void AGVRecv_USART1_Data(u8 *data ,u8 *Rx_Buffer);

#endif
