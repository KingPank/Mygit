/*----------------------------------------------------------------------------*/
/*
	File Name			:	

	Description			:

	Author				:  	
	Copyright			: 	
	Version&Date		: 	
	Notes		  	 	:
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
	
	#include "BCBGlobalFunc.h"
	#include "stm32f4xx_usart_config.h"
		#include<stdio.h>
	#include<string.h>
    /*---Macro Definition-----*/
	#define B_PROTOCL_HEAD  		0x80
	#define B_PROTOCL_OVER   	 	0x40
	#define	RX_BUFFER_SIZE			300
	
	//头帧内容
	#define		RequCmdFlag1					0xa5
	#define		RequCmdFlag2					0x5a

	#define  	RequCmdOrderNumMax    				0x05	
    /*---Variable Definition--*/
	unsigned char Rx_Buffer[300];
	unsigned int Rx_Index;
	unsigned char Rx_Flag;
    /*---Function Definiton---*/
	unsigned char MTSCheckCRC(unsigned char *str,unsigned char len);
	void MTSRecvData(unsigned char data);
	void (*MTSCmdCallback[RequCmdOrderNumMax])(const void *para);
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	MTSProtoclInit
Description       :	 	
Input parameter   :   	Class			Name		Action	
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		
*/
/*----------------------------------------------------------------------------*/
void  MTSProtoclInit()
{
	Rx_Flag = 0;
//	MTSCmdCallback[RequCmdOrderIsSetVxVrot]  = 	CmdIsSetVxVrotCallBack;
//	MTSCmdCallback[RequCmdOrderIsSetGxGyRot] = 	CmdIsSetGxGyRotCallBack;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	MTSRecvData
Description       :	 	
Input parameter   :   	Class			Name		Action	
						unsigned char 	data		Recv Data
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		Put the function in  the recv data interrupt or thread
*/
/*----------------------------------------------------------------------------*/
void MTSRecvData(unsigned char data)
{
	if( data == RequCmdFlag1)
	{ 
		Rx_Index=0;
		Rx_Flag |= B_PROTOCL_HEAD;
		Rx_Buffer[Rx_Index++]=data;
	}
	else if(data==RequCmdFlag2)
	{ 
		if(Rx_Flag & B_PROTOCL_HEAD)
		{ 
			Rx_Index=0;
			Rx_Flag&=~B_PROTOCL_OVER;
		}
		else
		{
			Rx_Buffer[Rx_Index++]=data;
		}
		Rx_Flag&=~B_PROTOCL_HEAD;
	}
	else
	{ 
	   Rx_Buffer[Rx_Index++]=data;
	   Rx_Flag&=~B_PROTOCL_HEAD;
	   if(Rx_Buffer[0] == Rx_Index)
	   {  
			Rx_Flag |= B_PROTOCL_OVER;
	//		if((MTSCheckCRC(&Rx_Buffer[1],Rx_Buffer[0]-3) == Rx_Buffer[Rx_Index])) 
			{
				//call back
				switch (Rx_Buffer[1])
				{
					case 0x02:
						break;
					case 0x03:
						break;	
					case 0x04:
						break;
				}
				Rx_Flag&=~B_PROTOCL_OVER;
				MemClr(Rx_Buffer,20);
			}
	   }
	}
	if(Rx_Index == RX_BUFFER_SIZE)
		Rx_Index--;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	MTSCheckCRC
Description       :	 	
Input parameter   :   	Class			Name		Action	
						unsigned char 	data		*str
						unsigned char 	len			length
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :		Put the function in  the recv data interrupt or thread
*/
/*----------------------------------------------------------------------------*/
unsigned char MTSCheckCRC(unsigned char *str,unsigned char len)
{
  	unsigned char sum = 0,i = 0;
	for (i = 0; i < len; i++)
	{
		sum +=str[i];
	}
	return sum;
}



