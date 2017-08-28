/*----------------------------------------------------------------------------*/
/*
		File Name			:	App_CommTask.h
    Description			:	
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

	#include "stm32f4xx_bsp_config.h"
	#include "BCBGlobalType.h"
	#include "BCBMpu6050Driver.h"
	#include "BCBCtrlIMU.h"
	#include "BCBOledDriver.h"
	#include "BCBGlobalFunc.h"
	#include "BCBGlobalMacros.h"
	#include "Queue.h"
	
    /*---Variable Definition--*/
//	FlyRecvInfo CmdRecvInfo;
	unsigned char  *pCmdRecvBuff = pUsartRecvBuff; 
//	unsigned char  CmdSendBuff[50]; 
	Msg  CmdMsg;	
    /*---Function Definiton---*/
	uint8_t  CheckCRC(uint8_t *str,uint8_t len);
	void TranslateMessage(uint8_t *str);
	void TaskListenMsg(uint8_t msgchannel,void** info,uint8_t *res);
	void GetRemoteInfo(uint8_t *str,void *info,uint8_t *err);
	void GetOSSwitchInfo(uint8_t *str,void *info,uint8_t *err);
	void GetPIDRecvInfo(uint8_t *str,void *info,uint8_t *err);
	void GetSenorOffSetRecvInfo(uint8_t *str,void *info,uint8_t *err);
    /*---Macro Definition-----*/
/*----------------------------------------------------------------------------*/

void AppTaskCommRecv(void *Id)
{
 	unsigned char  temp;									/*temp data*/
	unsigned char  Mod;
	static struct
	{
		unsigned char    Flag;	
		unsigned char 	Cnt;	
		unsigned char 	*pPackageMsg;
	} CmdJs;
	unsigned char 	PackageMsg[23];	
	CmdJs.Flag = NULL;							/*init the flags*/
	CmdJs.Cnt = NULL;
	CmdJs.pPackageMsg = PackageMsg;	
													/*init the memory and vari and func point*/
//	CmdMsg.Info[RE1CONCHANNUM]			= &CmdRecvInfo.Remote;	
//	CmdMsg.pGetInfoFuc[RE1CONCHANNUM] 	= &GetRemoteInfo;
//	CmdMsg.Info[RE1OPECHANNUM]			= &CmdRecvInfo.OSSoftSwitch;
//	CmdMsg.pGetInfoFuc[RE1OPECHANNUM] 	= &GetOSSwitchInfo;
//	CmdMsg.Info[RE1PIDCHANNUM]			= &CmdRecvInfo.PID;
//	CmdMsg.pGetInfoFuc[RE1PIDCHANNUM] 	= &GetPIDRecvInfo;
//	CmdMsg.Info[RE1SECCHANNUM]			= &CmdRecvInfo.SensorOffSet;
//	CmdMsg.pGetInfoFuc[RE1SECCHANNUM] 	= &GetSenorOffSetRecvInfo;	
	Id  = Id;
				
	while(1)
	{
	if (QueueNData(pCmdRecvBuff) > NULL)
		{
			QueueRead(&temp, pCmdRecvBuff);
			if ((temp !=RECOMFG1BYT)&&(CmdJs.Flag == FALSE))
			{
				goto linecomm1 ;
			}
			CmdJs.pPackageMsg[CmdJs.Cnt] = temp;
			CmdJs.Flag = TRUE;		
			if(CmdJs.pPackageMsg[CmdJs.Cnt] == RECOMFG3BYT)	/** the last byte is ! or not*/
			{
				TranslateMessage(CmdJs.pPackageMsg);	
				CmdJs.Cnt = NULL;
				CmdJs.Flag = FALSE;
			}
			else
			{
				CmdJs.Cnt++;
				if (CmdJs.Cnt > 50)
				{
					CmdJs.Cnt = NULL;
					CmdJs.Flag = FALSE;
				}
			}
		}
linecomm1:Id  = Id;
		//OSTimeDlyHMSM(0,0,0,20);	
	}
}
///*----------------------------------------------------------------------------*/
///*
//Fuction Name      :	AppTaskCommSend
//Description       :	  
//Input parameter   :   	Class			Name		Action	
//Output parameter  :   	Class			Name		Action				
//Author&Date       :	Jones.Lee & 2014.10.20
//Notes             :	Jones.Lee & 2013.10.20 
//*/
///*----------------------------------------------------------------------------*/
//void AppTaskCommSend(void *Id)
//{
//	unsigned char  	*pTaskSendMsg,i = NULL;
//	unsigned char 	*pCmdSendBuff;
//	unsigned char 	Mod = NULL;
//	unsigned char  	err = NULL;
//	INT16U 	timeout = 100;
//	unsigned char 		freetime = 10; 	
//	unsigned char  	*MsgQueue[RESENDCOMSIZE];				
//	unsigned char 	PackageMsg[RESENDCOMSIZE];
//	void (*pTaskSendPackageFunc)(uint8_t *,unsigned int );
//	Id  = Id;										
//	Q_MsgCmdSend = OSQCreate((void *)MsgQueue,RESENDCOMSIZE);	/*Create an Q event in order to send msg to PC */
//	
//	PackageMsg[RECOMFG1BIT] = RECOMFG1BYT;
//	PackageMsg[RECOMFG2BIT] = RECOMFG2BYT;
//	PackageMsg[RECOMFG3BIT] = RECOMFG3BYT;
//	
//	//GetSmallStorageValue(ROMMODFLYADDR,&Mod,1);
//	pCmdSendBuff = CmdSendBuff;
//	if(Mod == 1)
//	{
//		#ifdef	__KBFMCUINTERFACEINTERFACE_H__
//		KBFMcuUsartSendQueuePoint((void *)(&pCmdSendBuff));		/*usart*/		
//		pTaskSendPackageFunc = KBFMcuUsartSendBytes;
//		if (QueueCreate((void *)pCmdSendBuff,	
//			 sizeof(pCmdSendBuff),
//			 NULL,
//			 NULL
//			 ))
//			 {}		
//		#endif
//	}
//	else
//	{
//		#ifdef 	__KBFSENSORINTERFACE_H__				/*NRF*/
//		//pSenNrfRecvBuff = (void *)pCmdSendBuff;			
//		pTaskSendPackageFunc = KBFSetCommandBuff;	
//		#endif
//	}
//	while(1)
//	{
//		pTaskSendMsg= OSQPend(Q_MsgCmdSend,timeout,&err);
//		if(err == OS_NO_ERR)  									
//		{
//			PackageMsg[RECOMCHANNL] = pTaskSendMsg[0];
//			PackageMsg[RECOMLENBIT] = pTaskSendMsg[1];
//			PackageMsg[RECOMCRCBIT] = CheckCRC(&pTaskSendMsg[2],pTaskSendMsg[1]);
//			for(i = 0; i < PackageMsg[RECOMLENBIT]; i++)		
//			{
//				PackageMsg[RECOMDATBIT + i] = pTaskSendMsg[2 + i];
//			}
//			(*pTaskSendPackageFunc)(PackageMsg,NULL);
//		}
//		else																									/*None*///空闲的时候发送数据
//		{	
//			if((freetime--) == 1)
//			{
//				freetime = 10;
//				PackageMsg[RECOMCHANNL] = RE1ONLCHANNUL;
//				PackageMsg[RECOMLENBIT] = 17;
//				PackageMsg[RECOMCRCBIT] = CheckCRC(&pTaskSendMsg[2],pTaskSendMsg[1]);	
//				for(i = 0; i < PackageMsg[RECOMLENBIT]; i++)		
//				{
//					PackageMsg[RECOMDATBIT + i] = pTaskSendMsg[2 + i];
//				}
//				(*pTaskSendPackageFunc)(PackageMsg,NULL);				
//			}
//		}
//		OSTimeDlyHMSM(0,0,0,40);
//	}
//}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :		CheckCRC
Description       :	  
Input parameter   :   	Class			Name		Action	
						uint8_t *str
						uint8_t len
Output parameter  :   	Class			Name		Action				
Author&Date       :		Jones.Lee & 2014.10.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
uint8_t  CheckCRC(uint8_t *str,uint8_t len)
{
  	uint8_t sum = 0,i = 0;
	for (i = 0; i < len; i++)
	{
		sum +=str[i];
	}
	return sum;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	TranslateMessage
Description       :	 	TranslateMessage
Input parameter   :   	Class			Name	Action	
						uint8_t *str
Output parameter  :   	Class			Name		Action				
Author&Date       :		Jones.Lee & 2014.10.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void TranslateMessage(uint8_t *str)
{
	uint8_t err;
	if(!((str[RECOMFG1BIT] == RECOMFG1BYT)&&(
		 (str[RECOMFG2BIT] == RECOMFG2BYT))))																	/*check bit*/
		return;	 
	if(str[RECOMCRCBIT] !=(CheckCRC(&str[RECOMDATBIT],str[RECOMLENBIT]))) 	/*sum check*/
		return;	
	CmdMsg.pGetInfoFuc[str[RECOMCHANNL]]( &str[RECOMDATBIT],CmdMsg.Info[str[RECOMCHANNL]],&err);
	CmdMsg.Flag[str[RECOMCHANNL]] = TRUE;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :		TaskListenMsg
Description       :		Evey task can take this function to listen the data from
						pc.
Input parameter   :   	Class			Name		Action
						uint8_t msgchannel
						void* info
						uint8_t *res
Output parameter  :   	Class			Name		Action				
Author&Date       :		Jones.Lee & 2014.10.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void TaskListenMsg(uint8_t msgchannel,void** info,uint8_t *res)
{	
////	OS_CPU_SR  cpu_sr;
////	OS_ENTER_CRITICAL();							
//	if(CmdMsg.Flag[msgchannel] == TRUE)
//	{	/*----------------------------*/
//		CmdMsg.Flag[msgchannel] = FALSE;
//		*info = CmdMsg.Info[msgchannel];		
//		info = info; 								
//		/*----------------------------*/
//		*res = TRUE;
//	}
//	else
//	{
//		*res = FALSE;
//	}
////	OS_EXIT_CRITICAL();
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	GetRemoteInfo/GetOSSwitchInfo/GetSenorOffSetRecvInfo
Description       :	Get data from pc or remote.
Input parameter   :   	Class				Name	Action	
												uint8_t *str
												void *info
												uint8_t *err
Output parameter  :   	Class			Name		Action				
Author&Date       :	Jones.Lee & 2014.10.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void GetRemoteInfo(uint8_t *str,void *info,uint8_t *err)
{
//	((RemoteInfo *)info)->ThrTar = *((float *)(&str[RECONCHANTHRLLBIT]));
//	((RemoteInfo *)info)->RolTar = *((float *)(&str[RECONCHANROLLLBIT]));
//	((RemoteInfo *)info)->PitTar = *((float *)(&str[RECONCHANPITLLBIT]));
//	((RemoteInfo *)info)->YawTar = *((float *)(&str[RECONCHANYAWLLBIT]));
//	//限位
//	KBFMaxMinLimit(1000,0,&(((RemoteInfo *)info)->ThrTar));
//	KBFMaxMinLimit(500,-500,&(((RemoteInfo *)info)->RolTar));
//	KBFMaxMinLimit(500,-500,&(((RemoteInfo *)info)->PitTar));
//	KBFMaxMinLimit(500,-500,&(((RemoteInfo *)info)->YawTar));
//	err = err;
}
void GetOSSwitchInfo(uint8_t *str,void *info,uint8_t *err)
{
//	((OSSoftSwitchRecvInfo *)info)->SubChannelNum	= *((uint8_t *)(&str[0]));
//	((OSSoftSwitchRecvInfo *)info)->uCOSSW			= *((uint8_t *)(&str[1]));
//	((OSSoftSwitchRecvInfo *)info)->PeripheralSW	= *((uint8_t *)(&str[2]));
//	((OSSoftSwitchRecvInfo *)info)->FlyModeSW		= *((uint8_t *)(&str[3]));
//	err = err;
}

void GetPIDRecvInfo(uint8_t *str,void *info,uint8_t *err)
{
//	static uint8_t CntTemp, buff[6][17];
//	((PIDRecvInfo *)info)->SubChannelNum	= *((uint8_t *)(&str[REPIDCHANSUBBIT]));
//	if(((PIDRecvInfo *)info)->SubChannelNum == REPIDCHANSUBUPIDDNUM)
//	{
//			for( CntTemp = 0; CntTemp < REPIDCHANSUBMAXNUM; CntTemp++)					//发送PID  循环发送六组数据
//			{
//				KBFGetSmallStorageValue(ROMPIDBASEADDR + CntTemp * ROMPIDDATASIZE ,&buff[CntTemp][3],ROMPIDDATASIZE);	
//				buff[CntTemp][0] = RE1PIDCHANNUM;		//PID通道
//				buff[CntTemp][1] = 17;							//数据量
//				buff[CntTemp][2] = CntTemp;							//子通道
//				OSQPost(Q_MsgCmdSend,&buff[CntTemp][0]);
//		}	
//	}
//	else
//	{
//		((PIDRecvInfo *)info)->PidAbs[str[0]].P	= *((float *)(&str[REPIDCHANPLLBIT]));
//		((PIDRecvInfo *)info)->PidAbs[str[0]].I	= *((float *)(&str[REPIDCHANILLBIT]));
//		((PIDRecvInfo *)info)->PidAbs[str[0]].D	= *((float *)(&str[REPIDCHANDLLBIT]));
//		//存储起来
//		KBFCtrlSavePID(	((PIDRecvInfo *)info)->PidAbs[((PIDRecvInfo *)info)->SubChannelNum],
//												ROMPIDBASEADDR + ROMPIDDATASIZE * (((PIDRecvInfo *)info)->SubChannelNum));	
//	}
//	err = err;
}
void GetSenorOffSetRecvInfo(uint8_t *str,void *info,uint8_t *err)
{
//	((SensorRecvInfo *)info)->SubChannelNum	= *((uint8_t *)(&str[0]));
//	((SensorRecvInfo *)info)->X[str[0]]	= *((float *)(&str[1]));
//	((SensorRecvInfo *)info)->Y[str[0]]	= *((float *)(&str[5]));
//	((SensorRecvInfo *)info)->Z[str[0]]	= *((float *)(&str[6]));
//	err = err;
}
