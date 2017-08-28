#include "stm32f4xx_it.h"
#include<stdio.h>
#include<string.h>
#include "stm32f4xx_usart_config.h"
#include "MTSProtocol.h"
#include "agv_handle.h"
#include "BCBCtrlIMU.h"
#include "stdint.h"
#include "delay.h"


int16_t Rx_Buffer_sd;

#define	 Recv_bz1   0x01;
#define	 Recv_bz2   0x11;

u8 Rx_Index=0;
u8 rx_data_bz=0;
u8 bz;

void AGVRecv_USART1_Data(u8 *data ,u8 *Rx_Buffer)//上位机发送指令解析
{
	int n;
	u8 sum;	
    if(*data == 0xa5 && bz == 0)
  	{
 		  bz=Recv_bz1;
  		Rx_Index++;
	     if(*(data+1)==0x5a && bz==0x01)
			 {
    		bz=Recv_bz2;
    		Rx_Index=0; 		
			 }
    	if(bz==0x11)
  	   {
						for(rx_data_bz=0;rx_data_bz<12;rx_data_bz++)
					 {
						Rx_Buffer[rx_data_bz]=*(data+2+rx_data_bz);
						Rx_Index++;
					 }
//				if(Rx_Buffer[0]==Rx_Index)
//				{		
					Rx_Buffer_sd=Rx_Buffer[5]|(Rx_Buffer[6]&0x00ff<<8);	
					 if(Rx_Buffer_sd > 10000)
					 {
						 Rx_Buffer_sd=Rx_Buffer_sd-65536;
					 }
					for(n=0,sum=0;n<Rx_Index;n++)
					{
						if(n!=2)
						{
						  sum=+Rx_Buffer[n];
						}
					}			
							switch (Rx_Buffer[3])
						{
							case 0x01:Agv_EN(0);
								break;
							case 0x02:Agv_EN(1);
								break;
							case 0x03:Agv_Speed(Rx_Buffer[2],Rx_Buffer_sd);
								break;
							case 0x04:
								break;
						}		
							
				}
			
			}
		  	bz=0;
				Rx_Index=0;
				for(n=0;n<50;n++)
				{
					Rx_Buffer[n]=0;
				}	
}




u8 Rx_Buffer_XCSD[15];
int sj=0;
u8 Rx_Buffer_sj[10];

void AGVRecv_send_Data(u8 *dma_RxBuffer)//读取小车数据打包
{
	u8 n;
	u16 sum;
    Angle_t olj;
	  Gyro_t gyro;
	 float_u Z_olj;
	
	if(*(dma_RxBuffer+1)!=0x80&&*(dma_RxBuffer+2)==0xf9&&*(dma_RxBuffer+3)==0x60&&*(dma_RxBuffer+4)==0x18)
	{	
	for(sj=0;sj<10;sj++)
	{
		Rx_Buffer_sj[sj]=*(dma_RxBuffer+sj);
	}

		 Rx_Buffer_XCSD[0]=0xa5;
		 Rx_Buffer_XCSD[1]=0x5a;
		 Rx_Buffer_XCSD[2]=0x0f;
		 Rx_Buffer_XCSD[3]=0;
		 Rx_Buffer_XCSD[5]=0x01;
	   Rx_Buffer_XCSD[6]= Rx_Buffer_sj[0];
     if(Rx_Buffer_sj[1]!=0x80&&Rx_Buffer_sj[2]==0xf9&&Rx_Buffer_sj[3]==0x60&&Rx_Buffer_sj[4]==0x18)
		 {			 
		    Rx_Buffer_XCSD[7]= Rx_Buffer_sj[5];
			  Rx_Buffer_XCSD[8]= Rx_Buffer_sj[6];
			  Rx_Buffer_XCSD[9]= Rx_Buffer_sj[7];
			  Rx_Buffer_XCSD[10]= Rx_Buffer_sj[8];
		 
   IMU_getYawPitchRoll(&olj,&gyro,0.007);
      Z_olj.fdata=olj.Yaw;
			  Rx_Buffer_XCSD[11]=Z_olj.udata[0];
			  Rx_Buffer_XCSD[12]=Z_olj.udata[1];
			  Rx_Buffer_XCSD[13]=Z_olj.udata[2];
			  Rx_Buffer_XCSD[14]=Z_olj.udata[3];
		for(n=0,sum=0;n<15;n++)
		 {
			 if(n!=4)
			 {
				 
			 sum = sum +Rx_Buffer_sj[n];
		 
			 }
		 }
		 Rx_Buffer_XCSD[4]=sum;
		
		 u1_SendBytesInfoProc(Rx_Buffer_XCSD,15);
		 
		 }

	 }

}
