#ifndef __BCBGLOBALFUNC_H__
#define	__BCBGLOBALFUNC_H__

#include "BCBGlobalType.h"
#include "BCBGlobalMacros.h"
#include "stm32f4xx.h"

extern  CanSendPackage1_t CanSendPackage1;
extern  CanSendPackage2_t CanSendPackage2;
extern  CanSendPackage3_t	CanSendPackage3;
extern  MoveInfo_t 	MoveInfo;
extern  EncoderInfo_t EncoderInfo;
extern  EncoderPara_t EncoderPara;

extern FullSquarePosData_st 			FullSquarePosData;
extern  EepromMacOffsetData_t 		EepromMacOffsetData;
extern  EepromIMUOffsetData_t 		EepromIMUOffsetData;
extern  EepromCanIdData_t 				EepromCanIdData;
extern	EepromMacParaData_t				EepromMacParaData;
extern  CanIdConfig_t		CanIdConfig;

extern	PIDPara_t 			PID;				//PID参数
extern	Angle_t					AngleNow;			//角度数据
extern	Gyro_t					GyroNow;			//角速度数据
extern	Angle_t					AngleFilter;		//角度数据
extern	Gyro_t					GyroFilter;			//角速度数据
extern	Remote_t				RemoteNow;			//遥控信息
extern	MotoPwm_t				MotoPwmNow;			//电机PWM信息
extern	MotoSpeed_t			MotoSpeed;			//电机速度信息
extern 	TimeOutInfo_t			TimeOut;	
extern	BCBToMotoCanId_t 	BTM1CId;
extern	BCBToMotoCanId_t 	BTM2CId;
extern	MotoToBCBCanId_t	M1TBCId;
extern	MotoToBCBCanId_t	M2TBCId;

extern	MachInfo_t CarMachInfo;
extern	MoveInfo_t CarMoveInfo;

extern B2UData_t B2UData;
extern U2BData_t U2BData;

extern DmaUsartConfig_t DmaUsart3Config;
extern UsartSendConfig_t	Usart3SendConfig;

extern	float	RealCalcPeriod;

extern unsigned char RemoteErrorFlag;

extern unsigned char Can1SendFlag ;
extern unsigned char Can2SendFlag ;

extern unsigned int TIM7OverFlag;
extern unsigned int TIM4OverFlag ;

extern DMA_InitTypeDef DMARecv_InitStructure;
extern DMA_InitTypeDef DMASend_InitStructure;

void delay_ms(unsigned int t);
void delay_us(unsigned int t);
unsigned char  CheckCRC(unsigned char *str,unsigned char len);
void MemClr(unsigned char *pdata,unsigned int len);
void GlobalVariableInit(void);
#endif
