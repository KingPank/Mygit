/*----------------------------------------------------------------------------*/
/*
	File Name			:	

	Description			:

	Author				:  	
	Copyright			: 	
	Version&Date		: 	
	Notes		  	 	£º	
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
//	// operation system
//	#include "FreeRTOS.h"
//	#include "queue.h"
//	#include "croutine.h"
//	#include "task.h" 
//	//file system
//	#include "ff.h"
//	#include "diskio.h"
	// mcu
	#include "stm32f4xx_bsp_config.h"
	#include "BCBGlobalType.h"
	#include "BCBGlobalFunc.h"	
	#include "VisualScope.h"
	#include "BCBMpu6050Driver.h"
	#include "BCBLedDriver.h"
	#include "BCBEncoderDriver.h"
	
	#include "BCBCtrlIMU.h"
	#include "BCBKeyDriver.h"
	#include "BCBAD7689Driver.h" 
	#include "BCBADXRS620Driver.h"
	#include "BCBEncoderDriver.h"
	
	#include "BCBKinematics.h"
	
	#include "MTSProtocol.h"
	
	#include "stdlib.h"
	
	#include "BCBOledDriver.h"
	
	#include "AGV.h"
	
	//other
	#include<stdio.h>
	#include<string.h>
    /*---Variable Definition--*/
    /*---Function Definiton---*/
volatile unsigned long ulHighFrequencyTimerTicks;
    /*---Macro Definition-----*/

int main()
{
	int a=1;
	USART1_Configuration();
	TIM2_Configuration();
	TIM3_Configuration();
	AGV_EN(a);
	while(1)
	{
		AGV_EN(a);
		delay_ms(5000);
	}
}



































//	#define AccSen							0.0078125	//g/lsb @ +/- 16g
//	#define GyroSen							0.01524		//¡ã/s/lsb @ 500
//	#define TempSen							0.5			//K/LSB center temperature is 23¡æ
//	#define MagxySen						0.3			//uT/lsb
//	#define MagzSen							0.15		//uT/lsb

//	//SDO1 SDO2 CSB3 pulled to GND
//	#define Acc_addr						0x18
//	#define Gyro_addr						0x68
//	#define Mag_addr						0x10


//	/* BMX055 Register Map */
//	//ACC define
//	#define	ACC_ID							0x00	//OXFA
//	#define	ACC_XL							0x02
//	#define	ACC_XM							0x03
//	#define	ACC_YL							0x04
//	#define	ACC_YM							0x05
//	#define	ACC_ZL							0x06
//	#define	ACC_ZM							0x07
//	#define	Temp							0x08
//	#define ACC_range						0x0f	//1100b --> +/- 16g
//	#define Shasow_dis						0x13
//	#define ACC_ret							0x14	//write 0xb6
//	//Gyro define
//	#define	GYRO_ID							0x00	//OXOF
//	#define	GYRO_XL							0x02
//	#define	GYRO_XM							0x03
//	#define	GYRO_YL							0x04
//	#define	GYRO_YM							0x05
//	#define	GYRO_ZL							0x06
//	#define	GYRO_ZM							0x07
//	#define GYRO_range						0x0f	//010b --> +/- 500¡ã/s
//	#define GYRO_ret						0x14	//write 0xb6
//	//MAG define
//	#define	MAG_ID							0x40	//OX32
//	#define	MAG_XL							0x42
//	#define	MAG_XM							0x43
//	#define	MAG_YL							0x44
//	#define	MAG_YM							0x45
//	#define	MAG_ZL							0x46
//	#define	MAG_ZM							0x47
//	#define	MAG_RHAL						0x48
//	#define	MAG_RHAM						0x49
//	#define MAG_ret							0x4b	//1000 0001b
///*----------------------------------------------------------------------------*/

//	int i = 0;

//	u8 temp = 0;  

//	u8	BMX055_ABUF[7];//»º´æ
//	u8	BMX055_GBUF[6];
//	u8	BMX055_MBUF[8];	
//	float Acc_dat[3];
//	float Gyro_dat[3];
//	float Mag_dat[3];
//	float Tem_dat;
//	
	

	






























//{
////	SCB->VTOR = FLASH_BASE | 0x10000;	

//	USART1_Configuration();
//	OLED_Configuration();
//	IIC1_Confugration();
////	TIM45_Configuration();
////	SPI1_Configuration();
////	AD7689_Configuration();
////	ADXRS620_Configuration();
////	MPU6050_Configuation();
////	Encoder_Configuration();
////	IMU_init();
////	CAN1_Configuration();

////	ADXRS620_Init_Offset();
////	MPU6050_InitGyro_Offset();
//	
//	printf("Inited , Start~\n\r");	// \n\r »»ÐÐ£¬»Ø³µ


//	//¶ÁID

////	IIC1_IIC1_ReadData(Acc_addr,ACC_ID,&temp,8);
//	if(temp == 0xfa)
//	printf("The ACC is ok.\n\r");
//	else
//	printf("Error,the ACC_ID is : 0x%x\n\r",temp);

//	IIC1_ReadData(Gyro_addr,GYRO_ID,&temp,8);
//	if(temp == 0x0f)
//	printf("The GYRO is ok.\n\r");
//	else
//	printf("Error,the GYRO_ID is : 0x%x\n\r",temp);

//	IIC1_ReadData(Mag_addr,MAG_ID,&temp,8);
//	if(temp == 0x32)
//	printf("The MAG is ok.\n\r");
//	else
//	printf("Error,the MAG_ID is : 0x%x\n\r",temp);
//	
//	
//	//acc
//	IIC1_ReadData(Acc_addr,ACC_XL,BMX055_ABUF,56);
//	for(i = 0; i < 3;i ++)//0 1 2  0 1 2 3 4 5
//	{
//		Acc_dat[i] = (float)((int)(BMX055_ABUF[2*i]>>4 | BMX055_ABUF[2*i+1]<<4))*AccSen;
//	
//	}
//	Tem_dat = (float)((s8)(BMX055_ABUF[6]))*TempSen + 23;
//	//gyro
//	IIC1_ReadData(Gyro_addr,GYRO_XL,BMX055_GBUF,48);
//	for(i = 0; i < 3;i ++)//0 1 2  0 1 2 3 4 5
//	{
//		Gyro_dat[i] = (float)((int)(BMX055_GBUF[2*i] | BMX055_GBUF[2*i+1])<<8)*GyroSen;
//	
//	}
//	//mag
//	IIC1_ReadData(Mag_addr,MAG_XL,BMX055_MBUF,64);
//	for(i = 0; i < 2;i ++)//0 1   0 1 2 3
//	{
//		Mag_dat[i] = (float)((int)(BMX055_MBUF[2*i]>>3 | BMX055_MBUF[2*i+1])<<5)*MagxySen;
//	
//	}
//	Mag_dat[2] = (float)((int)(BMX055_MBUF[4]>>1 | BMX055_MBUF[5])<<7)*MagzSen;


//	while(1)
//	{
//		printf("accx %f,accy %f,accz %f.\n\r",Acc_dat[0],Acc_dat[1],Acc_dat[2]);
//		printf("gyrox %f,gyroy %f,gyroz %f.\n\r",Gyro_dat[0],Gyro_dat[1],Gyro_dat[2]);
//		printf("magx %f,magy %f,magz %f.\n\r",Mag_dat[0],Mag_dat[1],Mag_dat[2]);
//		printf("The temperature is %f.\n\r",Tem_dat);
//		delay_ms(500);
//		
//		OLED_Printf(1,1,"%d",i++);
//	}
//}

