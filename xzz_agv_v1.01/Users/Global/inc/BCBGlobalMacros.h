#ifndef __BCBGLOBALMACROS_H__
#define __BCBGLOBALMACROS_H__

#define  	MaxMinLimit(pre,max,min)	{	if(*(pre) > (max)) *(pre) = max;  if(*(pre) < (min)) *(pre) = (min);}
#define		MOTOSPPEDNEEDRAD	0
#define 	RADTODEG	 57.32			//180/3.14
#define 	DEGTORAD	 0.01744444		//3.14/180
	
	
//#define		DJIBOARD		1
	
	
	
#ifndef __FLASHBLOCKDEF_H__
#define __FLASHBLOCKDEF_H__
	/*
			SartAddr			EndAddr				Size
	BOOT 	0x0800 0000			0x800 F000			60k

	Data 	0x0800 F000			0x801 0000			4k

	App 	0x0801 0000			0x808 0000			512K-64K	

	*/

	#define 	FLASH_BOOT_ADDR		0x08000000  	

	#define 	FLASH_DATA_ADDR		0x0800F000  

	#define	 	FLASH_DATA_DEVICEINFO_ADDR0	0x0800F000

	#define	 	FLASH_DATA_IMUOFFSTDATA_ADDR0		0x0800F100
	
	#define	 	FLASH_DATA_CANIDDATA_ADDR0			0x0800F300
	
	#define	 	FLASH_DATA_MACOFFSTDDATA_ADDR0	0x0800F400

	#define	 	FLASH_DATA_MACPARADATA_ADDR0		0x0800F500
	
	#define FLASH_APP1_ADDR		0x08010000  	


#endif

#endif

