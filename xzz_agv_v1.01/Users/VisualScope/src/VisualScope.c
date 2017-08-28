/*----------------------------------------------------------------------------*/
/*
	File Name			:	scope.c
    Description			:
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
    Version&Date		: 	<2013.5.1>&<V1.0>
    Connector Fuction 	:
    Notes	£º
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
	#include "VisualScope.h"
	#include "math.h"
	#include "stm32f4xx_usart_config.h"
    /*---Variable Definition--*/

    /*---Function Definiton---*/
	static 	unsigned char Checksun(unsigned char *Buf, unsigned char CRC_CNT);
 void  	PCCurverDisplay(float  X,float Y,float Z,float K,int mul,unsigned int mms);
    /*---Macro Definition-----*/

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      £º	Checksun

Description       £º

Input parameter   £º   	Class			Name		Action	
					 	
Output parameter  £º   	Class			Name		Action	
					
Author&Date       £º	Jones.Lee & 2013.5.1

Notes             £º	the check the trasmitting value using the uart is right 
						or wrong
*/
/*----------------------------------------------------------------------------*/
unsigned char Checksun(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned char i;

	char byChecksum;

    byChecksum = 0;

    for (i = 0; i < CRC_CNT; i++)
    {
        byChecksum += Buf[i];
    }

    return byChecksum;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      £º	VisualScope_Display

Description       £º

Input parameter   £º   	Class			Name		Action	
					 	float  			X, 			mux1
						float 			Y,			mux2
						float 			Z,			mux3
						float 			K,			mux4
						int 			base,		basement
						int 			mul,		if the information is small,you can large the mul.
						unsigned int	mms			delay
Output parameter  £º   	Class			Name		Action	
						void
Author&Date       £º	Jones.Lee & 2013.5.1

Notes             £º	

*/
/*----------------------------------------------------------------------------*/
void delayms()
{
	unsigned int i ,j;
	for(i = 0; i < 10000;i ++)
	{
		for(j = 0; j < 1000; j++)
		{
		
		}
	}
}
void  VisualScope_Display(float  X,float Y,float Z,float K,int base,int mul,unsigned int mms)
{
	unsigned char i;
	unsigned char cData[10];
	unsigned char byLen;
	unsigned int wGyroX = 0;
	unsigned int wGyroY = 0;
	unsigned int wGyroZ = 0;
	unsigned int wGyroK = 0;
	i = i;
	wGyroX =  X * mul+ base;
	wGyroY =  Y * mul+ base;
	wGyroZ =  Z * mul+ base;
	wGyroK =  K * mul+ base;

    cData[0]  = wGyroX;
    cData[1]  = wGyroX >> 8;
    
    cData[2]  = wGyroY;
    cData[3]  = wGyroY >> 8;

    cData[4]  = wGyroZ;
    cData[5]  = wGyroZ >> 8;
    
    cData[6]  = wGyroK;
    cData[7]  = wGyroK >> 8;

	//CRC16(&cData[0],&cData[8],8);
    cData[8]  = Checksun(&cData[0], 8);

    byLen = 9;

//    for (i = 0; i < byLen; i++)
//    {
//        McuUsartSendByte(cData[i]);
//    }
		USART1_SendBytes(cData,byLen);
	if(mms == 0)
	{
		return;
	}
	else
	{
  	  return;

	}

}
void  	PCCurverDisplay(float  X,float Y,float Z,float K,int mul,unsigned int mms)
{
////	uint16_t i;
//	unsigned char cData[20];
////	unsigned char byLen;
//	int wGyroX = 0;
//	int wGyroY = 0;
//	int wGyroZ = 0;
//	int wGyroK = 0;

//	wGyroX =X * mul;
//	wGyroY = Y * mul;
//	wGyroZ = Z * mul;
//	wGyroK = K * mul;

//    cData[0]  = wGyroX >> 0;
//    cData[1]  = wGyroX >> 8;
//    cData[2]  = wGyroX >> 16;
//    cData[3]  = wGyroX >> 24;

//    cData[4]  = wGyroY >> 0;
//    cData[5]  = wGyroY >> 8;
//    cData[6]  = wGyroY >> 16;
//    cData[7]  = wGyroY >> 24;

//	cData[8]  = wGyroZ >> 0;
//    cData[9]  = wGyroZ >> 8;
//    cData[10]  = wGyroZ >> 16;
//    cData[11]  = wGyroZ >> 24;	 

//	cData[12]  = wGyroK >> 0;
//    cData[13]  = wGyroK >> 8;
//    cData[14]  = wGyroK >> 16;
//    cData[15]  = wGyroK >> 24;

//    cData[16]  = Checksun(&cData[0], 16);

//    byLen = 17;
//	
  //  USART_SendByte(USART1,0X01);	
//    KBFMcuUsartSendByte('#');
//    KBFMcuUsartSendByte('C');
//    for (i = 0; i < byLen; i++)
//    {
//        KBFMcuUsartSendByte(cData[i]);
//    }
//	KBFMcuUsartSendByte('$');
//	KBFMcuUsartSendByte('!');
//
//	if(mms == 0)
//	{
//		return;
//	}
//	else
//	{
//  	 	delayms();
//
//	  return;
//	}
}
