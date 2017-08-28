#include "stm32f4xx_it.h"
#include<stdio.h>
#include<string.h>
#include "stm32f4xx_usart_config.h"
#include "AGB_GG.h"
void AGV_EN(int a);
void AGV_SD(int i,int16_t a);
void AGV_monitoring(void);
void AGV_sd(u8 zz);

//void inttohex(int aa);

u8 agv1_en[10]={0X01,0X23,0X40,0X60,0X00,0X0F,0X00,0X00,0X00,0X2D};
u8 agv1_nen[10]={0X01,0X23,0X40,0X60,0X00,0X06,0X00,0X00,0X00,0X36};

u8 agv2_en[10]={0X02,0X23,0X40,0X60,0X00,0X0F,0X00,0X00,0X00,0X2C};
u8 agv2_nen[10]={0X02,0X23,0X40,0X60,0X00,0X06,0X00,0X00,0X00,0X35};

u8 agv1_model[10]={0X01,0X23,0X60,0X60,0X00,0X03,0X00,0X00,0X00,0X19};
u8 agv2_model[10]={0X02,0X23,0X60,0X60,0X00,0X03,0X00,0X00,0X00,0X18};

u8 SD[4]={0X00,0X00,0X00,0X00};
//u16 SD2[4]={0X00,0X00,0X00,0X00};
u8 agv1_SD[10]={0X01,0X23,0XFF,0X60,0X00};
u8 agv2_SD[10]={0X02,0X23,0XFF,0X60,0X00};


u8 agv1_monitoring[10]={0X01,0X40,0XF9,0X60,0X18,0X00,0X00,0X00,0X00,0X4E};
u8 agv2_monitoring[10]={0X02,0X40,0XF9,0X60,0X18,0X00,0X00,0X00,0X00,0X4D};

//u8 agv1_monitoring_1[10]={0};
//u8 agv2_monitoring_2[10]={0};
//u8 agv_monitoring_bz=0;
Remote_t			RemoteNow;	
void AGV_EN(int a)                    //小车使能和停止
{
	static int j = 0;
	if(a==0)
	{
			if(j==0)
			{
				j=1;
		//	USART3_SendBytes( agv1_nen,10);	 
       SendBytesInfoProc(agv1_nen,10);			
			}
		else
			{
				j=0;
			//USART3_SendBytes( agv2_nen,10);
				SendBytesInfoProc(agv2_nen,10);
			}
	}
	else if( a==1 )
	{
		  	if(j==0)
			  {
					j=1;
				//	USART3_SendBytes( agv1_en,10);
					SendBytesInfoProc(agv1_en,10);
		    }
		  else
				{
					j=0;
		//	USART3_SendBytes( agv2_en,10);
					SendBytesInfoProc(agv2_en,10);
					
				}
	}

}
void AGV_SD(int i,int16_t a)//小车赋予速度
{
	int b=0,j=0,k=0,n=0;
	u16 sum=0;
	if(a>=0)
	{
		
	if(i==1)
	{
		b=a*512*4096/1875;
	  SD[0]=(b&0x000000ff);
		SD[1]=(b&0X0000FF00)>>8;
		SD[2]=(b&0X00ff0000)>>16;
		SD[3]=(b&0xff000000)>>24;
		for(j=5,k=0;j<10;j++,k++)
		{
			agv1_SD[j]=SD[k];
		}
		for(n=0,sum=0;n<9;n++)
		{
			sum=sum + *(agv1_SD+n);
		}
		agv1_SD[9]=(-sum)&0x000000ff;
		SendBytesInfoProc(agv1_SD,10);
		//	USART3_SendBytes(agv1_SD,10);
		
		b=0,j=0,k=0,n=0,sum=0;
	}
	else if(i==2)
	{
		b=a*512*4096/1875;
		SD[0]=(b&0x000000ff);
		SD[1]=(b&0X0000FF00)>>8;
		SD[2]=(b&0X00ff0000)>>16;
		SD[3]=(b&0xff000000)>>24; 
		
		for(j=5,k=0;j<10;j++,k++)
		{
			agv2_SD[j]=SD[k];
		}
		for(n=0;n<9;n++)
		{
			sum=sum + *(agv2_SD+n);
		}
		agv2_SD[9]=(-sum)&0x000000ff;
	
//		for(n=0;n<10;n++)
//		{
//			dma_TxBuffer[n]=agv2_SD[n];
//		}
		SendBytesInfoProc(agv2_SD,10);
		
	//	USART3_SendBytes(agv2_SD,10);
		
	}
	}
		else if(a<0)
	{
		a=-a;
	if(i==1)
	{
		b=a*512*4096/1875;
	  SD[0]=(b&0x000000ff);
		SD[1]=(b&0X0000FF00)>>8;
		SD[2]=(b&0X00ff0000)>>16;
		SD[3]=0xff;
		for(j=5,k=0;j<10;j++,k++)
		{
			agv1_SD[j]=SD[k];
		}
		for(n=0,sum=0;n<9;n++)
		{
			sum=sum + *(agv1_SD+n);
		}
		agv1_SD[9]=(-sum)&0x000000ff;
		SendBytesInfoProc(agv1_SD,10);
		//	USART3_SendBytes(agv1_SD,10);
		
		b=0,j=0,k=0,n=0,sum=0;
	}
	else if(i==2)
	{
		b=a*512*4096/1875;
		SD[0]=(b&0x000000ff);
		SD[1]=(b&0X0000FF00)>>8;
		SD[2]=(b&0X00ff0000)>>16;
		SD[3]=0xff; 
		
		for(j=5,k=0;j<10;j++,k++)
		{
			agv2_SD[j]=SD[k];
		}
		for(n=0;n<9;n++)
		{
			sum=sum + *(agv2_SD+n);
		}
		agv2_SD[9]=(-sum)&0x000000ff;
	
//		for(n=0;n<10;n++)
//		{
//			dma_TxBuffer[n]=agv2_SD[n];
//		}
		SendBytesInfoProc(agv2_SD,10);
		
	//	USART3_SendBytes(agv2_SD,10);
		
	}
}
//	USART_ClearFlag(USART2, USART_IT_TC );
//  USART_ClearITPendingBit(USART2, USART_IT_TC ); 

}

void AGV_monitoring(void)//监控
{

	static int i = 0;
	if(i == 0)
	{
    i = 1;
		//USART3_SendBytes(agv1_monitoring,10);
		SendBytesInfoProc(agv1_monitoring,10);
	
	}
	else
	{
		i = 0;
		//USART3_SendBytes(agv2_monitoring,10);
		SendBytesInfoProc(agv2_monitoring,10);
	  
	}
}



 


