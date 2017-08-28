#ifndef __BCBGLOBALTYPE_H__
#define	__BCBGLOBALTYPE_H__
#include "BCBGlobalMacros.h"
#include "stm32f4xx.h"
#pragma anon_unions
/* include some variable type that may be used in all the dll systems.*/
typedef		void										KBvoid;
typedef		char										KBchar;
//typedef		bool									KBbool;
/*unsigned variable type */
typedef		unsigned char						KBu8;
typedef		unsigned short int			KBu16;
typedef		unsigned int						KBu32;
typedef		unsigned long int				KBu64;
/*signed variable type */
typedef		char										KBs8;
typedef		short int								KBs16;
typedef		int											KBs32;
typedef		long int								KBs64;
/*float variable type */
typedef		float							KBfloat;
typedef		double						KBdouble;
/*some union data*/
typedef union
{
	KBfloat	fdata;
	KBu8 udata[4];
}float_u;
typedef union
{
	KBdouble ddata;
	KBu8 udata[8];
}double_u;
typedef union
{
	KBs16	sdata;
	KBu8 udata[2];
}s16_u;
typedef union
{
	unsigned short int	sdata;
	unsigned char udata[2];
}u16_u;
typedef union
{
	KBs32	sdata;
	KBu8 udata[4];
}s32_u;
typedef union
{
	KBu32	sdata;
	KBu8 udata[4];
}u32_u;
typedef union
{
	KBs64	sdata;
	KBu8 udata[8];
}s64_u;

typedef	struct							
{
	union
	{
		float T[4][4];				
		struct
		{
			float T11;
			float T12;
			float T13;
			float T14;			
			
			float T21;
			float T22;
			float T23;
			float T24;
			
			float T31;
			float T32;
			float T33;
			float T34;
			
			float T41;
			float T42;
			float T43;
			float T44;
		};
	};
} Matrix_t;

typedef	struct							
{
	union
	{
		float XYZW[4];				
		struct
		{
			float X;					//X
			float	Y;					//Y
			float	Z;					//Z
			float	W;					//Z
		};
	};

} DecareAbs_t;
typedef	struct						
{
	union
	{
		float NPS[3];			
		struct
		{
			float   Nut;			
			float		Pre;				
			float		Ser;			
		};
	};
} EulerAbs_t;
typedef	struct						
{
	union
	{
		float RPY[3];				
		struct
		{
			float   Rol;				
			float   Pit;		
			float		Yaw;			
		};
	};

} RotationAbs_t;
#define	Accel_t DecareAbs_t
#define	Angle_t RotationAbs_t
#define Gyro_t RotationAbs_t
typedef struct
{			 
	float RolTar;
	float PitTar;
	float YawTar;
	float ThrTar;
} Remote_t;
typedef struct
{			 
	float M1;
	float M2;
} MotoPwm_t;
typedef struct
{			 
	union
	{
		float M1Tar;
		unsigned char M1uTar[4];
	};
	union
	{
		float M2Tar;
		unsigned char M2uTar[4];
	};	
	union
	{
		float M1Now;
		unsigned char M1uNow[4];
	};	
	union
	{
		float M2Now;
		unsigned char M2uNow[4];
	};	
	union
	{
		float M1NowTemp;
		unsigned char M1uNowTemp[4];
	};	
	union
	{
		float M2NowTemp;
		unsigned char M2uNowTemp[4];
	};	
	union
	{
		float M1DeltaVNow;
		unsigned char M1DeltauNow[4];
	};	
	union
	{
		float M2DeltaVNow;
		unsigned char M2DeltauNow[4];
	};	
} MotoSpeed_t;
typedef struct
{			 
	float ThrTar;
	float SelfRotationV;
} U2BData_t;
typedef struct
{			 
	float GlobalX;
	float GlobalY;
	float SelfRotation;
} B2UData_t;
typedef struct
{			 
	float Lbase;
	float	Rwheel;
	float	Nenc;
} MachInfo_t;
typedef struct
{	
	DecareAbs_t  E2BVel;
	
	float			DeltaDeg;
	float    	DeltaX;
	float    	DeltaY;
	DecareAbs_t EInGPos;				/* Encoder In Global Position*/
	DecareAbs_t EInGVel;				/* Encoder In Global Velocity*/

	RotationAbs_t EInGDeg; 		/* Encoder In Global Angle*/
	RotationAbs_t EInGDps;			/* Encoder In Global Gyro*/

	DecareAbs_t CInGPos;				/* Car In Global Position*/
	DecareAbs_t CInGVel;	  		/* Car In Global Velocity*/

	RotationAbs_t CInGDeg;	 	/* Car In Global Angle*/
	RotationAbs_t CInGDps; 		/* Car In Global Gyro*/
	
} MoveInfo_t;
/*------------------------PID----------------------------------------*/
typedef	struct 
{
	/*base pid data*/
	KBfloat  	P;		
	KBfloat  	I;
	KBfloat  	D;
}PIDAbs_t;
typedef	struct 
{
	/*extra pid data,in the caling,we need remember some data*/
	KBfloat 	NowData;
	KBfloat		LastData;
	KBfloat		SumData;
	KBfloat		ErrData;
	KBfloat		OutData;
	/*limlit value*/
	KBu32		OutDataMax;
	KBu32		IOutDataMax;
}PIDExtra_t;
typedef	struct 
{
	PIDAbs_t 		Abs;
	PIDExtra_t	Extra;
}PIDBasePara_t;
typedef struct  
{
	PIDBasePara_t PitAngle;
	PIDBasePara_t PitGyro;
	PIDBasePara_t YawAngle;
	PIDBasePara_t YawGyro;
	PIDBasePara_t Moto1Pos;
	PIDBasePara_t Moto2Pos;
	unsigned int Period;	//ms
	/*funciton point, it point the singleloop feedback function*/
	KBvoid (*Singleloop)(PIDBasePara_t *,KBfloat,KBfloat);
} PIDPara_t;

//moto pwm
typedef struct
{			 
	KBs32 Pwm;
	KBs32 MPwmMax;
} MotoPWM_t;
//电流电压数据
typedef struct
{			 
	KBfloat Now;
	KBfloat	Average;
	KBfloat	Max;
	KBfloat	Static;
} AVData_t;
typedef struct
{
	unsigned int Cnt;
	unsigned int Max;
}TimeOutBase_t;
typedef struct
{
	TimeOutBase_t RecvVxVr;			//上位机传来指令周期超时
	TimeOutBase_t Calc;				//计算进入死机
	TimeOutBase_t SendGxGyRot;		//发送数据
	TimeOutBase_t SendChaos;			//发送数据
	TimeOutBase_t RecvMoto1Gyro;		//接收电机数据数据
	TimeOutBase_t RecvMoto2Gyro;		//接收电机速度数据
	TimeOutBase_t Remote;				//遥控器数据
}TimeOutInfo_t;

/*-------------------------------------Can--------------------------------------*/
typedef struct
{
	int Base;				//基准
	int	SetGyro;			//发送速度
	int	SetCurrent;			//发送速度
	int	SetPWM;				//发送速度
	int	SetMode;			//模式
	int	SetGPID;			//设置速度PID
	int	SetAPID;			//设置位置PID
	int	SetCPID;			//设置电流PID
	int	GetMode;			//设置模式
	int	GetGPID;			//得到速度PID
	int	GetAPID;			//得到位置PID
	int	GetCPID;			//得到电流PID
}BCBToMotoCanId_t;
typedef struct
{
	int Base;				//基准
	int	SendGyro;			//发送速度
	int	SendMode;			//模式
	int	SendGPID;			//设置速度PID
	int	SendAV;				//设置速度PID
	int	SendAPID;			//设置位置PID
	int	SendCPID;			//设置电流PID
}MotoToBCBCanId_t;

typedef struct
{
//	DMA_InitTypeDef DMARecv_IS;
//	DMA_InitTypeDef DMASend_IS;
	unsigned char TxBusy;
	unsigned char RxBusy;
	unsigned char *RxBuff[2];
	unsigned char *TxBuff[2];
	unsigned int RxLen;
	unsigned int TxLen;
}DmaUsartConfig_t;
typedef struct
{
	TimeOutBase_t GxGyRot;		//发送数据
	TimeOutBase_t Chaos;		//发送数据
}UsartSendConfig_t;


typedef struct
{
	unsigned short int PId1;
	unsigned short int PId2;
	unsigned short int PId3;
}CanIdConfig_t;

typedef struct
{
	unsigned short int yawangle;
	unsigned short int pitangle;
	unsigned short int rolangle;
	unsigned short int yawgyro;
}CanSendPackage1_t;
typedef struct
{
	 int x;
	 int y;
}CanSendPackage2_t;
typedef struct
{
	 unsigned short int xdot;
	 unsigned short int ydot;
		
}CanSendPackage3_t;


typedef struct
{
	DecareAbs_t  ADXR620Offset;
	DecareAbs_t  MPU6050GyroOffset;
	uint16_t Crc;
}EepromIMUOffsetData_t;	
typedef struct
{
	float  	DeltaX;
	float  	DeltaY;
	float  	DeltaYaw;
}EepromMacOffsetData_t;
typedef struct
{
	unsigned short int 	PId1;
	unsigned short int  PId2;
	unsigned short int  PId3;
	unsigned short int Crc;
}EepromCanIdData_t;
typedef struct
{
	unsigned short int WheelRadius;
	unsigned short int EncoderNumber;
}EepromMacParaData_t;



typedef struct
{
	double    dx;
	double    dy;
	int  			dxNum;
	int  			dyNum;
	float  		dxAngle;
	float  		dyAngle;
}EncoderInfo_t;
typedef struct
{
	int 	Number;
	float Accuracy;
	float WheelRadius;
}EncoderPara_t;


typedef struct
{
		Angle_t Angle;
		Gyro_t 	Gyro;
    DecareAbs_t   Pos;
		DecareAbs_t   Vel;
}  FullSquarePosData_st;
typedef struct
{
    unsigned short int rols;
    unsigned char data[640];
}  __attribute__((packed)) GrayImage_st;

typedef struct
{
    float                   Yaw;
    float                   Pit;
    float                   Rol;
    float                   Current;
    float                   AngleInc;
    float                   Freq;
    unsigned short int      Distance[480];
}  LidarData_t;

#endif
