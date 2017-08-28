/*----------------------------------------------------------------------------*/
/*
	File Name			:	KBFMcuInterface.c
    Description			:	The file is the middle file . It is provide the int-
							-erface to the operate system. It Can easily decrease
							the error of the tranplant.
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2014.12.20>  V2.0
    Connector Fuction 	:
    Notes	：
*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
	#include "KBFSensorInterface.h"
	#include "Mpu6050.h"
	#include "AT24C16.h"
	#include "includes.h"
	#include "nrf24l01.h"

    /*---Variable Definition--*/
    /*---Function Definiton---*/
    /*---Macro Definition-----*/
   #define		MPU6050_ADDR	0XD0
   #define		AT24C16_ADDR	0XA0
   #define		HMC5883_ADDR	0X3C
   #define		BMP085_ADDR		0xEE
   void *pSenNrfRecvBuff;
/*----------------------------------------------------------------------------*/
KBFSenRes  KBFSensorInit(KBFSenVari sen)
{
	//这里需要加宏定义来限制裁剪带来的错误
	switch (sen)
	{
		#ifdef __MPU6050_H__
		case MPU6050:
			Mpu6050Init(MPU6050_ADDR);
			break;
		#endif
		#ifdef __HMC5883_H__
		case HMC5883:
			HMC5883Init(HMC5883_ADDR);
			break;
		#endif
		#ifdef __BMP085_H__
		case BMP085:
			BMP085Init(BMP085_ADDR);
			break;	
		#endif
		#ifdef __NRF24L01_H__
		case NRF24L01:
			NRF24L01Init(&pSenNrfRecvBuff);
			NRF24L01Detect();
			NRF24L01SetRxMode();
			//pSenNrfRecvBuff = pNrfRecvBuff;
			break;
		#endif
		#ifdef __OLED_H__
 		case OLED:
				OLED_Init();
			break;
		#endif
	}
	return Sen_OK;	
}
KBFSenRes  KBFSENEnable(uint8_t flag)
{
	return Sen_OK;	
}
KBFSenRes  KBFSDCEnable(uint8_t flag)
{
	return Sen_OK;	
}
KBFSenRes  KBFNRFEnable(uint8_t flag)
{
	return Sen_OK;	
}
KBFSenRes  KBFMPUEnable(uint8_t flag)
{
	return Sen_OK;	
}		
KBFSenRes  KBFBLUEnable(uint8_t flag)
{	
	return Sen_OK;	

}	

KBFSenRes  KBFGetRemote(uint8_t channel,unsigned short int data)
{
  	return Sen_OK;
}
KBFSenRes  KBFGetAccel(AccelInfo *Accel)
{ 	
	#ifdef __MPU6050_H__
	float accelX,accelY,accelZ;
	Mpu6050_ReadAccelrate(MPU6050_ADDR,&(accelX),&(accelY),&(accelZ));
	Accel->X = -accelX; 
	Accel->Y = -accelY; 
	Accel->Z = accelZ; 
	return Sen_OK;	
	#else
	return Sen_ERR;
	#endif	
}
KBFSenRes  KBFGetGyro(GyroInfo *Gyro)
{
	#ifdef __MPU6050_H__	
	float gyroX,gyroY,gyroZ;
	Mpu6050_ReadGyro(MPU6050_ADDR,&(gyroX),&(gyroY),&(gyroZ));	
	Gyro->X = -gyroX; 
	Gyro->Y = -gyroY; 	 
	Gyro->Z = gyroZ; 
	return Sen_OK;
	#else
	return Sen_ERR;
	#endif
}
KBFSenRes  KBFGetAngle(AngleInfo *Angle)
{
	#ifdef __MPU6050_H__
	float angleX,angleY,angleZ;
	Mpu6050_ReadAngle(MPU6050_ADDR,&(angleX),&(angleY),&(angleZ));
	Angle->X = -angleY;
	Angle->Y = -angleX;
	Angle->Z = -angleZ;
	return Sen_OK;
	#else
	return Sen_ERR;
	#endif
}	

KBFSenRes  KBFGetSmallStorageValue( uint32_t byRA,uint8_t * pData, uint8_t byCount)
{
		AT24C16ReadBytes(AT24C16_ADDR,byRA,pData,byCount);
	return Sen_OK;
}
KBFSenRes  KBFSetSmallStorageValue(uint32_t byRA,uint8_t *pData,uint8_t byCount)
{
  	AT24C16WriteBytes(AT24C16_ADDR, byRA,pData,byCount);
  	return Sen_OK;
}
KBFSenRes  KBFCheckSmallStorage(void)
{
//	uint8_t temp;
//  	temp = AT24C16Check(AT24C16_ADDR);
//	if( temp == 0)
//  		return Sen_OK;
//	else
		return Sen_ERR;
}


void  KBFSetCommandBuff(uint8_t *buff,uint32_t length)
{
	#ifdef OS_CPU_H          
	OS_CPU_SR  cpu_sr;
	#endif  
	               
	#ifdef  OS_CPU_H
    	OS_ENTER_CRITICAL(); 
	#endif	
	#ifdef __NRF24L01_H__
		NRF24L01TxPacket(buff,length);	
	#endif
	
	#ifdef  OS_CPU_H
	OS_EXIT_CRITICAL();
	#endif
  	//return Sen_OK;
}

KBFSenRes  KBFOLEDFlush(void)
{
	#ifdef __OLED_H__
	OLED_RefreshGram();
	#endif
  	return Sen_OK;
}
KBFSenRes  KBFOLEDClear(void)
{
	#ifdef __OLED_H__
	
	OLED_Clear();
	#endif
  	return Sen_OK;
}
KBFSenRes  KBFOLEDDrawByte(uint8_t px,uint8_t py,uint8_t *byte)
{
	#ifdef __OLED_H__
	#endif
  	return Sen_OK;
}
KBFSenRes  KBFOLEDDrawNum(uint8_t px,uint8_t py,uint8_t num)
{
	#ifdef __OLED_H__
	#endif
  	return Sen_OK;
	
}
KBFSenRes  KBFOLEDDrawString(uint8_t px,uint8_t py,uint8_t *str)
{
	#ifdef __OLED_H__
	OLED_ShowString(px,py,str);
	#endif
  	return Sen_OK;
}
KBFSenRes  KBFOLEDprintf(uint8_t row,uint8_t col,char *fmt,...)
{
	#ifdef __OLED_H__
	OLED_Printf(row,col,fmt);
	#endif
  	return Sen_OK;
}
KBFSenRes  KBFOLEDDrawPoint(uint8_t px,uint8_t py,uint8_t t)
{
	#ifdef __OLED_H__
	OLED_DrawPoint(px,py,t);
	#endif
  	return Sen_OK;
}
KBFSenRes  KBFOLEDDrawLine(uint8_t orignpx,uint8_t orignpy,uint8_t targetpx,uint8_t targetpy)
{
	#ifdef __OLED_H__
	#endif
  	return Sen_OK;
}
KBFSenRes  KBFOLEDDrawFill(uint8_t lefttoppx,uint8_t lefttoppy,uint8_t rightdownpx,uint8_t rightdownpy,uint8_t t)
{
	#ifdef __OLED_H__
	OLED_Fill(lefttoppx,lefttoppy,rightdownpx,rightdownpy,t);
	#endif
  	return Sen_OK;
}

