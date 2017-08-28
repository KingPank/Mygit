/*----------------------------------------------------------------------------*/
/*
	File Name			:	BCBKinematics
	Description			:		
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.X.XX>  V1.0
	Connector Fuction 	:
	Notes				:	
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
		
	#include "math.h"
	#include "BCBGlobalFunc.h"	
	#include "BCBKinematics.h"

	#include "stm32f4xx_bsp_config.h"

	#include "BCBLedDriver.h"
	#include "BCBKeyDriver.h"
	#include "BCBEncoderDriver.h"

	#include "BCBCtrlIMU.h"

	
  /*---Macro Definition-----*/
	/*---Variable Definition--*/			
	
unsigned char EncoderXYOffsetCalcFlag;
unsigned char EncoderYawOffsetCalcFlag;

void CalcEncoderInfo( EncoderPara_t *encoderpara,EncoderInfo_t *encoderinfo,float dt);
void CalcKinematics(MoveInfo_t *moveinfo,EncoderInfo_t *encoderinfo,Angle_t *angle,Gyro_t *gyro,float dt);
void 		BeginCalcDeltaXY(MoveInfo_t *moveinfo);
uint8_t CheckCalcDeltaXYEnd(MoveInfo_t *moveinfo);
void 		CalcAndSaveDeltaXY(MoveInfo_t *moveinfo);

void 		BeginCalcDeltaYaw(MoveInfo_t *moveinfo);
uint8_t CheckCalcDeltaYawEnd(MoveInfo_t *moveinfo);
void 		CalcAndSaveDeltaYaw(MoveInfo_t *moveinfo);
/*----------------------------------------------------------------------------*/
void Calc()
{
	float dt;
	//����������ʱ��
	CalcPeriod(&dt);
	//���������
	CalcEncoderInfo(&EncoderPara,&EncoderInfo,dt);
	//�жϱ���������û ������IMU yawһ���źţ��ж��͸�yaw, �������Ͳ���
	
	//����IMU�ǶȽ��ٶ�
	CalcIMUInfo(&AngleNow,&GyroNow,dt);
	//�����±������ĵ�λʱ������ �ȼ������ݺ����XY����
	CalcKinematics(&MoveInfo,&EncoderInfo,&AngleNow,&GyroNow,dt);


	if(EncoderXYOffsetCalcFlag == 1)
	{
			if(CheckCalcDeltaXYEnd(&MoveInfo) == 1)
			{
					CalcAndSaveDeltaXY(&MoveInfo);
					EncoderXYOffsetCalcFlag = 0;
			}
			return;
	}
	if(EncoderYawOffsetCalcFlag == 1)
	{
			if(CheckCalcDeltaYawEnd(&MoveInfo) == 1)
			{
					CalcAndSaveDeltaYaw(&MoveInfo);
					EncoderYawOffsetCalcFlag = 0;
			}
			return;
	}
	//��������
	CanSendPackage1.pitangle = 	AngleNow.Pit;
	CanSendPackage1.yawangle = 	AngleNow.Rol;
	CanSendPackage1.rolangle = 	AngleNow.Yaw;
	CanSendPackage1.yawgyro = 	GyroNow.Yaw;
	CanSendPackage2.x = MoveInfo.CInGPos.X;
	CanSendPackage2.y = MoveInfo.CInGPos.Y;
	CAN1SendMsg(CanIdConfig.PId1,(unsigned char *)&CanSendPackage1,8);
	CAN1SendMsg(CanIdConfig.PId2,(unsigned char *)&CanSendPackage2,8);
	CAN1SendMsg(CanIdConfig.PId3,(unsigned char *)&CanSendPackage3,8);
}
void CalcEncoderInfo( EncoderPara_t *encoderpara,EncoderInfo_t *encoderinfo,float dt)
{
	int deltaxnow,deltaynow;
	double dx,dy;
//	encoderpara->Number = 4000;
//	encoderpara->Accuracy = 2*3.14/4000;
//	encoderpara->WheelRadius = 30;
	GetEncoder(&deltaxnow,&deltaynow);
	/*�õ���λʱ��ı�������Ŀ*/
	dx = (double)deltaxnow ;
	dy = (double)deltaynow ;
	/*�õ���λʱ��ĽǶ�*/	
	dx = dx * (double)encoderpara->Accuracy;
	dy = dy * (double)encoderpara->Accuracy;
	/*�õ���λʱ�����·�� s = angle * r ����·�� = ���ȽǶ� ���԰뾶*/	
	dx = dx * (double)encoderpara->WheelRadius;
	dy = dy * (double)encoderpara->WheelRadius;
	/*�õ���λʱ������ٶ�*/	
	dx = dx / (double)dt;
	dy = dy / (double)dt;
	/*��ֵ*/	
	encoderinfo->dx = dx;
	encoderinfo->dy = dy;
}
void CalcKinematics(MoveInfo_t *moveinfo,EncoderInfo_t *encoderinfo,Angle_t *angle,Gyro_t *gyro,float dt)
{
	/*
		��������װ��ĽǶ���б����
		�ǶȾ��� DeltaDeg
	*/
	float  dx = encoderinfo->dx;
	float  dy = encoderinfo->dy;	
	float	 dyaw = (float)((gyro->Yaw) /((float)180 * 3.14));
	float  deltadeg = 0;
	float  deltax = moveinfo->DeltaX;
	float  deltay = moveinfo->DeltaY;
	moveinfo->E2BVel.X = ( dx ) * (cos(deltadeg)) + ( dy ) * (sin(deltadeg));
	moveinfo->E2BVel.Y = ( dx ) * (sin(deltadeg)) + ( dy ) * (cos(deltadeg));
	/*
		�õ�ȫ������ϵ������XY���ϵ��ٶ�
	  ���������Ĳ��ܲ���һ����Ϊ���Ǵӱ�������ԭ���������Բ��ܷ�һ��
		����ת���и��ط����׻죬����ĳ�����������˶��� X Y ���Ƕ����˶��ģ�
		�����ٶȵú�������������ֻ��һ�������ٶȣ��ٸ����ӣ�����ǰ�ߣ�Y��û���ٶ�
	*/
	moveinfo->EInGVel.X = ( moveinfo->E2BVel.X ) * (cos(moveinfo->EInGDeg.Yaw)) + ( moveinfo->E2BVel.Y ) * (sin(moveinfo->EInGDeg.Yaw));
	moveinfo->EInGVel.Y = ( moveinfo->E2BVel.X ) * (sin(moveinfo->EInGDeg.Yaw)) + ( moveinfo->E2BVel.Y ) * (cos(moveinfo->EInGDeg.Yaw));
//	moveinfo->EInGVel.X = ( moveinfo->E2BVel.X ) * (1) + ( moveinfo->E2BVel.Y ) * (0);
//	moveinfo->EInGVel.Y = ( moveinfo->E2BVel.X ) * (0) + ( moveinfo->E2BVel.Y ) * (1);
	moveinfo->EInGDps.Yaw= dyaw; 
	/*
		�õ�ȫ������ϵ������XY���ϵ�λ��
		�����ּ���
	*/
	moveinfo->EInGPos.X = moveinfo->EInGPos.X + moveinfo->EInGVel.X *dt ;
	moveinfo->EInGPos.Y = moveinfo->EInGPos.Y + moveinfo->EInGVel.Y *dt;
	moveinfo->EInGDeg.Yaw = moveinfo->EInGDeg.Yaw + moveinfo->EInGDps.Yaw *dt ;
	//��λ
	if(moveinfo->EInGDeg.Yaw >= (float)3.14)
		moveinfo->EInGDeg.Yaw -= (float)2*3.14;
	if(moveinfo->EInGDeg.Yaw < -(float)3.14)
		moveinfo->EInGDeg.Yaw +=(float)2*3.14;	
	/*
		��������װ�복������λ��ƫ�� ���Գ�������λ����Ҫһ��ƫ��
	*/
	moveinfo->CInGPos.X = moveinfo->EInGPos.X + deltax;
	moveinfo->CInGPos.Y = moveinfo->EInGPos.Y + deltay;
	moveinfo->CInGDeg.Yaw = moveinfo->EInGDeg.Yaw;
}



void BeginCalcDeltaXY(MoveInfo_t *moveinfo)
{
	/*
		������־λ
		������������
	*/
}
uint8_t CheckCalcDeltaXYEnd(MoveInfo_t *moveinfo)
{
	if(moveinfo->EInGDeg.Yaw >= 90)
	{
			return 1;
	}
	else
	{
			return 0;
	}
}
void CalcAndSaveDeltaXY(MoveInfo_t *moveinfo)
{
	float deltax;
	float deltay;
	float x = moveinfo->EInGPos.X;
	float y = moveinfo->EInGPos.Y;

	deltax = (x + y)/2;
	deltay = (x - y)/2;

	moveinfo->DeltaX = deltax;
	moveinfo->DeltaY = deltay;
}

void BeginCalcDeltaYaw(MoveInfo_t *moveinfo)
{
	/*
		������־λ
		������������
	*/
	
}
uint8_t CheckCalcDeltaYawEnd(MoveInfo_t *moveinfo)
{
	return 1;
}
void CalcAndSaveDeltaYaw(MoveInfo_t *moveinfo)
{
	float deltayaw;
	float deltay;
	float x = moveinfo->EInGPos.X;
	float y = moveinfo->EInGPos.Y;
	
	x=x;
	y =y;
	
	deltayaw = deltayaw;
	deltay = deltay;
	deltayaw = cos(x);
	moveinfo->DeltaDeg = deltayaw;
}
