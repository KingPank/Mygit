
#include "BCBGlobalType.h"
#include "stm32f4xx.h"
PIDPara_t 			PID;				//PID参数
Angle_t				AngleNow;			//角度数据
Gyro_t				GyroNow;			//角速度数据
Angle_t				AngleFilter;		//角度数据
Gyro_t				GyroFilter;			//角速度数据
Remote_t			RemoteNow;			//遥控信息
MotoPwm_t			MotoPwmNow;			//电机PWM信息
MotoSpeed_t			MotoSpeed;			//电机速度信息
TimeOutInfo_t			TimeOut;	
BCBToMotoCanId_t 	BTM1CId;
BCBToMotoCanId_t 	BTM2CId;
MotoToBCBCanId_t	M1TBCId;
MotoToBCBCanId_t	M2TBCId;

MachInfo_t CarMachInfo;
MoveInfo_t CarMoveInfo;

B2UData_t B2UData;
U2BData_t U2BData;

DmaUsartConfig_t DmaUsart3Config;
UsartSendConfig_t	Usart3SendConfig;

float	RealCalcPeriod = 0;

unsigned char RemoteErrorFlag = 0;

unsigned char Can1SendFlag = 0;
unsigned char Can2SendFlag = 0;


DMA_InitTypeDef DMARecv_InitStructure;
DMA_InitTypeDef DMASend_InitStructure;

unsigned int TIM7OverFlag = 0;
unsigned int TIM4OverFlag = 0;

unsigned char DmaUsart3RxBuff0[256];
unsigned char DmaUsart3RxBuff1[256];
unsigned char DmaUsart3TxBuff0[256];
unsigned char DmaUsart3TxBuff1[256];





EepromIMUOffsetData_t  EepromIMUOffsetData;
EepromCanIdData_t	EepromCanIdData;
EepromMacOffsetData_t EepromMacOffsetData;
EepromMacParaData_t EepromMacParaData;

CanIdConfig_t		CanIdConfig;
CanSendPackage1_t CanSendPackage1;
CanSendPackage2_t CanSendPackage2;
CanSendPackage3_t	CanSendPackage3;


MoveInfo_t 	MoveInfo;
EncoderInfo_t EncoderInfo;
EncoderPara_t EncoderPara;
FullSquarePosData_st FullSquarePosData;


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
 unsigned char  CheckCRC(unsigned char *str,unsigned char len)
{
  	unsigned char sum = 0,i = 0;
	for (i = 0; i < len; i++)
	{
		sum +=str[i];
	}
	return sum;
}
void MemClr(unsigned char *pdata,unsigned int len)
{
	unsigned int i;
	for(i = 0; i < len; i++)
	{
		*(pdata++) = 0;
	}
	return;
}
void GlobalVariableInit()
{
	MemClr((unsigned char *)(&PID),sizeof(PID));
	MemClr((unsigned char *)(&AngleNow),sizeof(AngleNow));
	MemClr((unsigned char *)(&GyroNow),sizeof(GyroNow));
	MemClr((unsigned char *)(&RemoteNow),sizeof(RemoteNow));
	MemClr((unsigned char *)(&BTM1CId),sizeof(BTM1CId));
	MemClr((unsigned char *)(&BTM2CId),sizeof(BTM2CId));
	MemClr((unsigned char *)(&M1TBCId),sizeof(M1TBCId));
	MemClr((unsigned char *)(&M2TBCId),sizeof(M2TBCId));
	MemClr((unsigned char *)(&TimeOut),sizeof(TimeOut));
	MemClr((unsigned char *)(&DmaUsart3Config),sizeof(DmaUsart3Config));
	MemClr((unsigned char *)(&DmaUsart3RxBuff0),sizeof(DmaUsart3RxBuff0));
	MemClr((unsigned char *)(&DmaUsart3RxBuff1),sizeof(DmaUsart3RxBuff1));
	MemClr((unsigned char *)(&DmaUsart3TxBuff0),sizeof(DmaUsart3TxBuff0));
	MemClr((unsigned char *)(&DmaUsart3TxBuff1),sizeof(DmaUsart3TxBuff1));
	
	//从flash读取PID 和其他数据，这里先模拟下
	PID.Period = 2;
	PID.PitAngle.Abs.P = 98;
	PID.PitAngle.Abs.I = 0.101;
	PID.PitAngle.Abs.D = 50;

	PID.PitGyro.Abs.P = 1.01;
	PID.PitGyro.Abs.I = 0;
	PID.PitGyro.Abs.D = 3.5;
	
	PID.YawAngle.Abs.P = 0;
	PID.YawAngle.Abs.I = 0;
	PID.YawAngle.Abs.D = 0;

	PID.YawGyro.Abs.P = 0;
	PID.YawGyro.Abs.I = 0;
	PID.YawGyro.Abs.D = 0;
	
	PID.Moto1Pos.Abs.P = 400;
	PID.Moto1Pos.Abs.I = 0.7;
	PID.Moto1Pos.Abs.D = 2.1;

	PID.Moto2Pos.Abs.P = 200;
	PID.Moto2Pos.Abs.I = 0.4;
	PID.Moto2Pos.Abs.D = 2.1;
	
	TimeOut.Calc.Max = 100;
	TimeOut.RecvMoto1Gyro.Max = 100;
	TimeOut.RecvMoto2Gyro.Max = 100;
	TimeOut.RecvVxVr.Max = 8000;
	TimeOut.Remote.Max = 100;
	TimeOut.SendGxGyRot.Max = 10;
	TimeOut.SendChaos.Max = 10;
	
	DmaUsart3Config.RxLen = 256;
	DmaUsart3Config.TxLen = 256;
	DmaUsart3Config.TxBusy = 0;
	DmaUsart3Config.RxBusy = 0;

	DmaUsart3Config.RxBuff[0] =DmaUsart3RxBuff0;
	DmaUsart3Config.RxBuff[1] =DmaUsart3RxBuff1;
	DmaUsart3Config.TxBuff[0] =DmaUsart3TxBuff0;
	DmaUsart3Config.TxBuff[1] =DmaUsart3TxBuff1;
	//Canid数据 应该可以从flash中读取应该。	这里先模拟一下.
	BTM1CId.Base = 0;						
	M1TBCId.Base = 100;
	BTM2CId.Base = 200;						
	M2TBCId.Base = 300;
	
	BTM1CId.SetGyro 	= BTM1CId.Base + 01;	
	BTM1CId.SetMode 	= BTM1CId.Base + 02;
	BTM1CId.SetGPID 	= BTM1CId.Base + 03;
	BTM1CId.SetCPID 	= BTM1CId.Base + 04;
	BTM1CId.SetCurrent 	= BTM1CId.Base + 05;
	BTM1CId.SetPWM 		= BTM1CId.Base + 06;
	BTM1CId.GetMode = BTM1CId.Base + 51;
	BTM1CId.GetGPID = BTM1CId.Base + 52;

	M1TBCId.SendGyro = M1TBCId.Base + 01;
	M1TBCId.SendMode = M1TBCId.Base + 02;
	M1TBCId.SendGPID = M1TBCId.Base + 03;
	M1TBCId.SendGPID = M1TBCId.Base + 04;
	M1TBCId.SendAV	 = M1TBCId.Base + 05;

	BTM2CId.SetGyro = BTM2CId.Base + 01;	
	BTM2CId.SetMode = BTM2CId.Base + 02;
	BTM2CId.SetGPID = BTM2CId.Base + 03;
	BTM2CId.SetCPID = BTM2CId.Base + 04;
	BTM2CId.SetCurrent = BTM2CId.Base + 05;
	BTM2CId.SetPWM = BTM2CId.Base + 06;
	BTM2CId.GetMode = BTM2CId.Base + 51;
	BTM2CId.GetGPID = BTM2CId.Base + 52;

	M2TBCId.SendGyro = M2TBCId.Base + 01;
	M2TBCId.SendMode = M2TBCId.Base + 02;
	M2TBCId.SendGPID = M2TBCId.Base + 03;
	M2TBCId.SendGPID = M2TBCId.Base + 04;
	M2TBCId.SendAV	 = M2TBCId.Base + 05;

	CarMachInfo.Lbase = 0.30;
	CarMachInfo.Rwheel = 0.071;
}
