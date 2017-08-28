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

extern	PIDPara_t 			PID;				//PID����
extern	Angle_t					AngleNow;			//�Ƕ�����
extern	Gyro_t					GyroNow;			//���ٶ�����
extern	Angle_t					AngleFilter;		//�Ƕ�����
extern	Gyro_t					GyroFilter;			//���ٶ�����
extern	Remote_t				RemoteNow;			//ң����Ϣ
extern	MotoPwm_t				MotoPwmNow;			//���PWM��Ϣ
extern	MotoSpeed_t			MotoSpeed;			//����ٶ���Ϣ
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
