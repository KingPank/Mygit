/*----------------------------------------------------------------------------*/
/*
    File Name           :   BCBHmc5883lDriver.c
    Description         : 
    Author              :   Jones.Lee 
    Copyright           :   Jones_Workspace
                            Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date        :   <2015.4.28>  V1.0
    Connector Fuction   : 
    Notes £º                Analog signal
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

    /*---Head Files---*/
    #include 	"stm32f4xx_iic_config.h"
	#include 		"BCBHmc5883LDriver.h"
    #include 	"BCBGlobalFunc.h"
    /*---Variable Definition--*/
    float       HMC5883_lastx,HMC5883_lasty,HMC5883_lastz;
    int16_t     HMC5883L_FIFO[3][11]; 
    int16_t     HMC5883L_pInFIFO = 0;
    int         HMC5883L_SumFIFO[6] ={0};
    /*---Function Definiton---*/
	void HMC5883L_Configuration(void);
	void HMC5883L_SetUp(void);	//初始化
	void HMC58X3_getID(char id[3]);	//读芯片ID
	void HMC58X3_getValues(int16_t *x,int16_t *y,int16_t *z); //读ADC
	void HMC58X3_GetValues(float *arry); //IMU 专用的读取磁力计值
	void HMC58X3_getlastValues(int16_t *x,int16_t *y,int16_t *z);
    void HMC58X3_getRaw(int16_t *x,int16_t *y,int16_t *z);
    /*---Macro Definition-----*/
    #define HMC58X3_ADDR 0x3C // 7 bit address of the HMC58X3 used with the Wire library
    #define HMC_POS_BIAS 1
    #define HMC_NEG_BIAS 2
                                // HMC58X3 register map. For details see HMC58X3 datasheet
    #define HMC58X3_R_CONFA     0
    #define HMC58X3_R_CONFB     1
    #define HMC58X3_R_MODE      2
    #define HMC58X3_R_XM        3
    #define HMC58X3_R_XL        4

    #define HMC58X3_R_YM (7)  //!< Register address for YM.
    #define HMC58X3_R_YL (8)  //!< Register address for YL.
    #define HMC58X3_R_ZM (5)  //!< Register address for ZM.
    #define HMC58X3_R_ZL (6)  //!< Register address for ZL.

    #define HMC58X3_R_STATUS 9
    #define HMC58X3_R_IDA 10
    #define HMC58X3_R_IDB 11
    #define HMC58X3_R_IDC 12


    #define HMC5883L_ReadByte(byAD,byRA,pdata)                  	IIC1_ReadData(byAD,byRA,pdata,1)
    #define HMC5883L_ReadBytes(byAD,byRA,count,pdata)           	IIC1_ReadData(byAD,byRA,pdata,count)
    #define HMC5883L_WriteByte(byAD,byRA,data)           			IIC1_WriteData(byAD,byRA,data)
    #define HMC5883L_WriteBits(dev,reg,bitStart,length,data)    	IIC1_WriteBits(dev,reg,bitStart,length,data)
    #define HMC5883L_WriteBit(dev,reg,bitNum,data)              	IIC1_WriteBit(dev,reg,bitNum,data)
    #define HMC5883L_DelayUs(tim)                                   delay_us(tim)    
/*----------------------------------------------------------------------------*/
unsigned char HMC5883_IS_newdata(void)
{
 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==Bit_SET){
	  return 1;
	 }
	 else return 0;
}
void HMC58X3_FIFO_init(void)
{
  int16_t temp[3];
  unsigned char i;
  for(i=0;i<50;i++){
  HMC58X3_getRaw(&temp[0],&temp[1],&temp[2]);
  HMC5883L_DelayUs(200); 
  }
}

void  HMC58X3_newValues(int16_t x,int16_t y,int16_t z)
{
    HMC5883L_SumFIFO[0] -= HMC5883L_FIFO[0][HMC5883L_pInFIFO];
    HMC5883L_SumFIFO[1] -= HMC5883L_FIFO[1][HMC5883L_pInFIFO];
    HMC5883L_SumFIFO[2] -= HMC5883L_FIFO[2][HMC5883L_pInFIFO];
    
    HMC5883L_FIFO[0][HMC5883L_pInFIFO] = x;
    HMC5883L_FIFO[1][HMC5883L_pInFIFO] = y;
    HMC5883L_FIFO[2][HMC5883L_pInFIFO] = z;

    HMC5883L_SumFIFO[0] += HMC5883L_FIFO[0][HMC5883L_pInFIFO];
    HMC5883L_SumFIFO[1] += HMC5883L_FIFO[1][HMC5883L_pInFIFO];
    HMC5883L_SumFIFO[2] += HMC5883L_FIFO[2][HMC5883L_pInFIFO];

    HMC5883L_pInFIFO++;
		if(HMC5883L_pInFIFO >= 10)
    {

        HMC5883L_pInFIFO = 0;
    }
    HMC5883L_FIFO[0][10] = HMC5883L_SumFIFO[0] / 10;
    HMC5883L_FIFO[1][10] = HMC5883L_SumFIFO[1] / 10;
    HMC5883L_FIFO[2][10] = HMC5883L_SumFIFO[2] / 10;
} 

void HMC58X3_writeReg(unsigned char reg, unsigned char val) {
  HMC5883L_WriteByte(HMC58X3_ADDR,reg,val);
}

void HMC58X3_getRaw(int16_t *x,int16_t *y,int16_t *z) {
   unsigned char vbuff[6];
   vbuff[0]=vbuff[1]=vbuff[2]=vbuff[3]=vbuff[4]=vbuff[5]=0;
   HMC5883L_ReadBytes(HMC58X3_ADDR,HMC58X3_R_XM,6,vbuff);
   HMC58X3_newValues(((int16_t)vbuff[0] << 8) | vbuff[1],((int16_t)vbuff[4] << 8) | vbuff[5],((int16_t)vbuff[2] << 8) | vbuff[3]);
   *x = HMC5883L_FIFO[0][10];
   *y = HMC5883L_FIFO[1][10];
   *z = HMC5883L_FIFO[2][10];
}

void HMC58X3_getlastValues(int16_t *x,int16_t *y,int16_t *z) {
  *x = HMC5883L_FIFO[0][10];
  *y = HMC5883L_FIFO[1][10]; 
  *z = HMC5883L_FIFO[2][10]; 
}

void HMC58X3_GetValues(float *arry) {
  int16_t xr,yr,zr;
  HMC58X3_getRaw(&xr, &yr, &zr);
  arry[0]= HMC5883_lastx=(float)(xr);
  arry[1]= HMC5883_lasty=(float)(yr);
  arry[2]= HMC5883_lastz=(float)(zr);
}

void HMC58X3_setGain(unsigned char gain) { 

  if (gain > 7) return;
  HMC58X3_writeReg(HMC58X3_R_CONFB, gain << 5);
}

void HMC58X3_setMode(unsigned char mode) {
  if (mode > 2) {
    return;
  }
  HMC58X3_writeReg(HMC58X3_R_MODE, mode);
  HMC5883L_DelayUs(100);
}

void HMC58X3_init(u8 setmode) {

  if (setmode) {
    HMC58X3_setMode(0);
  }

  HMC58X3_writeReg(HMC58X3_R_CONFA, 0x70); 
  HMC58X3_writeReg(HMC58X3_R_MODE, 0x00);

}


void HMC58X3_setDOR(unsigned char DOR) {
  if (DOR>6) return;
  HMC58X3_writeReg(HMC58X3_R_CONFA,DOR<<2);
}


void HMC58X3_getID(char id[3]) 
{
      HMC5883L_ReadByte(HMC58X3_ADDR,HMC58X3_R_IDA,(unsigned char *)&id[0]);  
      HMC5883L_ReadByte(HMC58X3_ADDR,HMC58X3_R_IDB,(unsigned char *)&id[1]);
		HMC5883L_ReadByte(HMC58X3_ADDR,HMC58X3_R_IDC,(unsigned char *)&id[2]);
}  

void HMC5883L_SetUp(void)
{ 
  HMC58X3_init(0); 
  HMC58X3_setMode(0);
  HMC58X3_setDOR(6);  
  HMC58X3_FIFO_init();
}

void HMC5883L_Configuration(void)
{ 
  HMC58X3_init(0); 
  HMC58X3_setMode(0);
  HMC58X3_setDOR(6);  
  HMC58X3_FIFO_init();
}
