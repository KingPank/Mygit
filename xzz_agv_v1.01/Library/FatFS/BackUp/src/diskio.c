/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: USB drive control */
//#include "atadrive.h"	/* Example: ATA drive control */
//#include "sdcard.h"		/* Example: MMC/SDC contorl */
//#include "MMC_SD.h"		/* Example: MMC/SDC contorl */
/* Definitions of physical drive number for each media */
#define ATA		0
#define MMC		1
#define USB		2
 /////////////////////////////////////////////////////
#define MMC_DIRVER
#ifdef  MMC_DIRVER
DRESULT	MMC_disk_initialize()
{
	SD_Configuration();		//iniliase
	return RES_OK;
}
DRESULT MMC_disk_status()
{
	return RES_OK;
} 
DRESULT MMC_disk_read(BYTE *buff,UINT sector , BYTE count)
 {
 	int Status;
	if(count==1)            /* 1个sector的读操作 */      
    {   
       Status =  SD_ReadSingleBlock( sector ,buff );
       if(Status == 0)
	   {
			return RES_OK;
       }
		else
		{
 			return RES_ERROR;
        }    
    }                                                
    else                    /* 多个sector的读操作 */     
    {  
        Status = SD_ReadMultiBlock( sector , buff ,count);
        if(Status == 0)
		{
			return RES_OK;
        }
		else
		{
			return RES_ERROR;
        } 
    }    

 }
DRESULT MMC_disk_write(const BYTE *buff,UINT sector,BYTE count)
{
	int Status;
	if(count==1)            /* 1个sector的读操作 */      
    {   
       Status =  SD_WriteSingleBlock( sector ,buff );
       if(Status == 0)
	   {
			return RES_OK;
       }
		else
		{
 			return RES_ERROR;
        }    
    }                                                
    else                    /* 多个sector的读操作 */     
    {  
        Status = SD_WriteMultiBlock( sector , buff ,count);
        if(Status == 0)
		{
			return RES_OK;
        }
		else
		{
			return RES_ERROR;
        } 
    } 
}
DRESULT MMC_disk_ioctl(	BYTE cmd,void *buff)
{
  switch (cmd)
  {
    case CTRL_SYNC:
      return RES_OK;
    case GET_SECTOR_COUNT:
      *((DWORD*)buff) = 0x1000; // 2Mbyte
      return RES_OK;

    case GET_BLOCK_SIZE:
      *((DWORD*)buff) = 512;
      return RES_OK;
    case CTRL_POWER:
      break;
    case CTRL_LOCK:
      break;
    case CTRL_EJECT:
      break;
      /* MMC/SDC command */
    case MMC_GET_TYPE:
      break;
    case MMC_GET_CSD:
      break;
    case MMC_GET_CID:
      break;
    case MMC_GET_OCR:
      break;
    case MMC_GET_SDSTAT:
      break;
  }
  return RES_PARERR;
}
#endif
////////////////////////////////////////////////
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	switch (pdrv) {
	case ATA :
#ifdef  ATA_DIRVER
			return  ATA_disk_initialize();
#endif
		// translate the reslut code here

	

	case MMC :
#ifdef  MMC_DIRVER
			return MMC_disk_initialize();
#endif
		// translate the reslut code here
	case USB :
#ifdef  USB_DIRVER
		result = USB_disk_initialize();
#endif
		// translate the reslut code here

		default:return STA_NOINIT;
	}
//	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	switch (pdrv) {
	case ATA :
#ifdef  ATA_DIRVER
		return ATA_disk_status();
#endif
		// translate the reslut code here
	case MMC :
#ifdef  MMC_DIRVER
		return MMC_disk_status();
#endif
		// translate the reslut code here
	case USB :
#ifdef  USB_DIRVER
		return  USB_disk_status();
#endif
		// translate the reslut code here
		default:return STA_NOINIT;	
	}
//	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..128) */
)
{
	switch (pdrv) {
	case ATA :
		// translate the arguments here
#ifdef  ATA_DIRVER
		return  ATA_disk_read(buff, sector, count);
#endif
		// translate the reslut code here


	case MMC :
		// translate the arguments here
 #ifdef  MMC_DIRVER
		return MMC_disk_read(buff, sector, count);
 #endif
		// translate the reslut code here

		

	case USB :
		// translate the arguments here
 #ifdef  USB_DIRVER
		return USB_disk_read(buff, sector, count);
 #endif
		// translate the reslut code here
	 default:return RES_ERROR;
	}
//	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
)
{
	switch (pdrv) {
	case ATA :
		// translate the arguments here
 #ifdef  ATA_DIRVER
 
		return ATA_disk_write(buff, sector, count);
 #endif
		// translate the reslut code here
	case MMC :
		// translate the arguments here
 #ifdef  MMC_DIRVER
		return MMC_disk_write(buff, sector, count);
 #endif
		// translate the reslut code here
	case USB :
		// translate the arguments here
#ifdef  USB_DIRVER
			return USB_disk_write(buff, sector, count);
#endif
		// translate the reslut code here
	 	 default:return RES_ERROR;
	}
//	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	switch (pdrv) {
	case ATA :
		// pre-process here
#ifdef  ATA_DIRVER
		return  ATA_disk_ioctl(cmd, buff);
#endif
		// post-process here
	case MMC :
		// pre-process here
#ifdef  MMC_DIRVER
	return MMC_disk_ioctl(cmd, buff);
#endif
		// post-process here
	case USB :
		// pre-process here
#ifdef  USB_DIRVER
	return  USB_disk_ioctl(cmd, buff);
#endif
		// post-process here
	default:return RES_ERROR;		
	}
//	return RES_PARERR;
}
#endif
DWORD get_fattime (void)
{
	return ((2010UL-1980) << 25) /* Year = 2010 */
	| (11UL << 21) /* Month = 11 */
	| (2UL << 16) /* Day = 2 */
	| (15U << 11) /* Hour = 15 */
	| (0U << 5) /* Min = 0 */
	| (0U >> 1) /* Sec = 0 */
	;
}
