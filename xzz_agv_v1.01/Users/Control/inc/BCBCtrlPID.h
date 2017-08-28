#ifndef __BCBCTRLPID_H__
#define __BCBCTRLPID_H__
#include "stm32f4xx.h"
	#include "BCBGlobalType.h"
#include <math.h>
	void 	BCBCtrlFeedBack(PIDPara_t *pidpara,Angle_t angle,Gyro_t gyro,Remote_t remote,MotoSpeed_t *motospeed,float dt,MachInfo_t machinfo_t);
	void 	BCBCtrlSingleLoopPID(PIDBasePara_t *pid, float currentdata, float targetdata);
	void 	BCBCtrlMaxMinLimit(float *pre,float max, float min);
#endif
