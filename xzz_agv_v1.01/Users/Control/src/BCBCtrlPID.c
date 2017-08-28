/*----------------------------------------------------------------------------*/
/*
	File Name			:  	BCBCtrlPID.c

    Description			: 

    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
    Version&Date		: 	<2014.10.20>
    Connector Fuction 	:
    Notes	£º
*/										 
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "BCBCtrlPID.h"
	#include "BCBGlobalType.h"
	/*---Variable Definition--*/
	/*---Function Definiton---*/
	void 	BCBCtrlFeedBack(PIDPara_t *pidpara,Angle_t angle,Gyro_t gyro,Remote_t remote,MotoSpeed_t *motospeed,float dt,MachInfo_t machinfo_t);
	void 	BCBCtrlSingleLoopPID(PIDBasePara_t *pid, float currentdata, float targetdata);
	void BCBCtrlMaxMinLimit(float *pre,float max, float min);
//	void 	BCBCtrlSavePID(PIDAbs pid,uint16_t addr);
//	void 	BCBCtrlUpDataPID(PIDAbs *pid,uint16_t addr);
//	void 	BCBCtrlUpDataAllPID(PIDPara *pPidPara);

	/*---Macro Definition-----*/
	//Interface
//#define	BCBCtrlDelayMs(n) BCBMcuDelay(n)		
//#define	BCBCtrlSaveData(addr,pdata,num) BCBSetSmallStorageValue(addr,pdata,num)
//#define	BCBCtrlUpData(addr,pdata,num) BCBGetSmallStorageValue(addr,pdata,num)
//#define BCBCtrlLimitValue(num,max,min)
/*----------------------------------------------------------------------------*/

float Moto1PostionCurrent ,Moto2PostionCurrent,BVelocityX,BVelocityXFilter,BPosition,Pout;
void BCBCtrlFeedBack(PIDPara_t *pidpara,Angle_t angle,Gyro_t gyro,Remote_t remote,MotoSpeed_t *motospeed,float dt,MachInfo_t machinfo)
{
	static int i = 0;
	i = i;
	
	if((angle.Pit >20)||(angle.Pit < -20))
	{
		motospeed->M1Tar =0;
		motospeed->M2Tar =0;
		return;
	}
	//Pit
	BCBCtrlSingleLoopPID(&(pidpara->PitAngle), angle.Pit, 0);
	BCBCtrlSingleLoopPID(&(pidpara->PitGyro) , gyro.Pit , pidpara->PitAngle.Extra.OutData);
	//Yaw
//	BCBCtrlSingleLoopPID(&(pidpara->YawAngle), angle.Yaw, remote.YawTar);
//	BCBCtrlSingleLoopPID(&(pidpara->YawGyro) , gyro.Yaw , pidpara->YawAngle.Extra.OutData);	


//	motospeed->M1Tar =pidpara->PitGyro.Extra.OutData;// + pidpara->YawGyro.Extra.OutData ;//+ pidpara->PosOrign.Extra.OutData;
//	motospeed->M2Tar =pidpara->PitGyro.Extra.OutData ;//- pidpara->YawGyro.Extra.OutData ;//+ pidpara->PosOrign.Extra.OutData;
	i++;
	if( i > 4)
	{ 
		i = 0;
		//位置环
//		BVelocityX  = -(float)(motospeed->M1Now + motospeed->M1Now)* DEGTORAD / 2;	
//		BVelocityXFilter *=0.80;
//		BVelocityXFilter +=BVelocityX*0.2;
//		BPosition +=BVelocityXFilter;
//		BPosition +=remote.ThrTar/10;
//		Pout = 3.2*BPosition+10*BVelocityXFilter;
//		Moto1PostionCurrent += ( ( (motospeed->M1Now + motospeed->M1Now)/2 - remote.ThrTar) * machinfo.Rwheel * DEGTORAD ) * dt;	
//		BCBCtrlSingleLoopPID(&(pidpara->Moto1Pos), Moto1PostionCurrent, 0);		
//		BCBCtrlSingleLoopPID(&(pidpara->Moto2Pos), Moto2PostionCurrent, 0);	
	
	}	
		motospeed->M1Tar =  +remote.PitTar + pidpara->PitGyro.Extra.OutData -Pout;//- pidpara->Moto1Pos.Extra.OutData;// + pidpara->YawGyro.Extra.OutData ;//
		motospeed->M2Tar =  -remote.PitTar +pidpara->PitGyro.Extra.OutData -Pout;// pidpara->Moto1Pos.Extra.OutData;//- pidpara->YawGyro.Extra.OutData ;//
}
void BCBCtrlSingleLoopPID(PIDBasePara_t *pid, float currentdata, float targetdata)
{
		pid->Extra.LastData = pid->Extra.NowData;
		pid->Extra.NowData = (targetdata - currentdata);
	
		pid->Extra.ErrData = (pid->Extra.NowData - pid->Extra.LastData);
		pid->Extra.SumData = (pid->Extra.SumData + pid->Extra.NowData);
		BCBCtrlMaxMinLimit(&(pid->Extra.SumData), 1000,-1000);

		pid->Extra.OutData = 	pid->Extra.NowData * pid->Abs.P +
													pid->Extra.SumData * pid->Abs.I +
													pid->Extra.ErrData * pid->Abs.D;	
}
void BCBCtrlMaxMinLimit(float *pre,float max, float min)	
{
	if( *pre > max) 
	{
		*pre = max; 
		return;
	}
	if( *pre < min)
	{
		*pre = min;
		return;
	}		
}
