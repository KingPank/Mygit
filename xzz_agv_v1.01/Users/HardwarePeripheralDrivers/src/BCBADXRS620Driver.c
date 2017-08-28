/*----------------------------------------------------------------------------*/
/*
	File Name			:	BCBADXRS620Driver.c
	Description			:	
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.3.22>  V1.0
	Connector Fuction 	:
	Notes	：
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "BCBAD7689Driver.h" 
	#include "BCBADXRS620Driver.h"
	#include "BCBGlobalFunc.h"
	/*---Variable Definition--*/

	/*---Function Definiton---*/
	void ADXRS620_Init_Offset(void);
	static int8_t ADXRS620_GetValuesuint16_t(uint8_t chnum,uint16_t *data);
/*---Macro Definition-----*/
	
	#define Sensitive_Gyro   78.642f         						//陀螺仪灵敏度[6mV/°/sec] 
	#define Gyro_To_32_8     (32.8f / Sensitive_Gyro) 	//将	陀螺仪 分 辨 率转成32.8,以便和上位机对应。
	
	
	
	#define ADXR620_DelayUs(us)		delay_us(us)




uint16_t ADXR620_Yaw_OffSet;
#define	 ADXRS620_pInFIFOMAX   20
uint32_t ADXRS620_SumFIFO[9] = {0};
uint16_t ADXRS620_FIFO[9][ADXRS620_pInFIFOMAX+1]= {0};
uint16_t ADXRS620_pInFIFO = 0;
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 		AD7689_Configuration
Description       :	 	
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :			Jones.Lee & 2014.12.20
Notes             :		
*/
/*----------------------------------------------------------------------------*/
void ADXRS620_Configuration()
{
		uint16_t temp = 0;
		ADXRS620_GetValuesuint16_t(ADXR620_YAW,&temp);  //第一个数据处理掉！
//		ADXRS620_Init_Offset();
}
void  ADXRS620_Filter(uint16_t *a1,uint16_t *a2)
{
	
	ADXRS620_SumFIFO[0] -= ADXRS620_FIFO[0][ADXRS620_pInFIFO];
	ADXRS620_SumFIFO[1] -= ADXRS620_FIFO[1][ADXRS620_pInFIFO];
	
	ADXRS620_FIFO[0][ADXRS620_pInFIFO] = *a1;
	ADXRS620_FIFO[1][ADXRS620_pInFIFO] = *a2;
	
	ADXRS620_SumFIFO[0] += ADXRS620_FIFO[0][ADXRS620_pInFIFO];
	ADXRS620_SumFIFO[1] += ADXRS620_FIFO[1][ADXRS620_pInFIFO];

	ADXRS620_pInFIFO++;
	if(ADXRS620_pInFIFO >= ADXRS620_pInFIFOMAX)
	{
		ADXRS620_pInFIFO = 0;
	}
	ADXRS620_FIFO[0][ADXRS620_pInFIFOMAX] = ADXRS620_SumFIFO[0] / ADXRS620_pInFIFOMAX;
	ADXRS620_FIFO[1][ADXRS620_pInFIFOMAX] = ADXRS620_SumFIFO[1] / ADXRS620_pInFIFOMAX;
	*a1 = ADXRS620_FIFO[0][ADXRS620_pInFIFOMAX];
	*a2 = ADXRS620_FIFO[1][ADXRS620_pInFIFOMAX];	
}
static int8_t ADXRS620_GetValuesuint16_t(uint8_t chnum,uint16_t *data)
{
	uint16_t ADCValue;
	if(chnum == ADXR620_YAW)
	{
	  AD7689_GetOneResult(0,&ADCValue);
	}
	if(chnum == ADXR620_YAWTEM)
	{
	  AD7689_GetOneResult(1,&ADCValue);
	}
	*data = ADCValue;
	return 1;
}

void ADXRS620_Init_Offset()
{
	uint16_t temp = 0;
	float   temp1 = 0;
	unsigned int  sum = 0;
	for(int i = 0; i < 100; i ++)
	{
			ADXRS620_GetValuesuint16_t(ADXR620_YAW,&temp);
			ADXR620_DelayUs(10);
			temp1 = temp;
			temp1 = temp1 ;
			sum += temp;
	}
	sum /=100;
//	sum +=32768;
	ADXR620_Yaw_OffSet = sum;
	
	EepromIMUOffsetData.ADXR620Offset.Z = ADXR620_Yaw_OffSet;
}
void ADXRS620_SetOffset(float gx,float gy,float gz)
{
	ADXR620_Yaw_OffSet = gz;
}
int8_t ADXRS620_GetValues(uint8_t chnum,float *data)
{
	uint16_t ADCValue;
	float    gyro;
	float    mid;
	mid = 	(float)32767.0;
	if(chnum == ADXR620_YAW)
	{
	  AD7689_GetOneResult(0,&ADCValue);
		gyro = ADCValue;
		gyro = gyro - ADXR620_Yaw_OffSet;
		gyro = gyro/Sensitive_Gyro;
		*data = gyro;
	}
		if(chnum == ADXR620_YAWTEM)
	{
	  AD7689_GetOneResult(1,&ADCValue);
		gyro = ADCValue;
		gyro = gyro - mid;
	//	gyro = gyro/Sensitive_Gyro;
		*data = gyro;
	}
	return 1;
}	
uint16_t uyaw = 0;
	uint16_t utem = 0;
	double    fyaw = 0;
	double    ftem = 0;
int8_t ADXRS620_GetYaw(float *yaw)
{

	ftem = ftem;
	ADXRS620_GetValuesuint16_t(ADXR620_YAW,&uyaw);
	ADXRS620_GetValuesuint16_t(ADXR620_YAWTEM,&utem);
	
	ADXRS620_Filter(&uyaw,&utem);
	
	fyaw = uyaw;
	fyaw = fyaw ;//- ADXR620_Yaw_OffSet;
	fyaw = (fyaw* 5/65535);     // 5/65535 * 1000/6;
 	*yaw = fyaw;
	
	return 1;
}
