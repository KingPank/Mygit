/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               diskio.c
** Descriptions:            The FATFS Diskio
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-4
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "diskio.h"
#include "ffconf.h"
#include "BCBSDDriver.h"
#include <stdio.h>

/* Private variables ---------------------------------------------------------*/
extern SD_CardInfo SDCardInfo;


DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
 int Status;
	
 switch (drv) 
 {
	case 0 :	  
	    Status = SD_Init();
	    if(Status == SD_OK)
		  return 0;
	    else 
		  return STA_NOINIT;  
	case 1 :
		return STA_NOINIT;
  }
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
    switch (drv) 
	{
	  case 0 :	
	  /* translate the reslut code here	*/
	    return 0;
	  case 1 :
	  /* translate the reslut code here	*/
	    return 0;
	  case 2 :
	  /* translate the reslut code here	*/
	    return 0;
	  default:
        break;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
  int Status;
  if( !count )
  {    
    return RES_PARERR;  /* count���ܵ���0�����򷵻ز������� */
  }

  switch (drv)
  {
    case 0:	
	    if(count==1)            /* 1��sector�Ķ����� */      
	    {       
		    /* Read block of 512 bytes from address 0 */
		    Status = SD_ReadBlock(buff, sector << 9, _MAX_SS);
		    /* Check if the Transfer is finished */
		    //Status = SD_WaitReadOperation();
		    while(SD_GetStatus() != SD_TRANSFER_OK);
			//if(SD_OK == Status)return RES_OK;
	    }                                                
	    else                    /* ���sector�Ķ����� */     
	    {   
		    /* Read block of many bytes from address 0 */
		    Status = SD_ReadMultiBlocks(buff, sector << 9, _MAX_SS, count);
		    /* Check if the Transfer is finished */
		    //Status = SD_WaitReadOperation();
		    while(SD_GetStatus() != SD_TRANSFER_OK);
			//if(SD_OK == Status)return RES_OK;
	    }                                                
	    if(Status == SD_OK)
	    {
	      return RES_OK;
	    }
	    else
	    {
	      printf("read data error : %d\n\r",Status);
		  return RES_ERROR;
		}

    default:
      break;
  
  }
  return RES_ERROR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	        /* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
  int Status;
  if( !count )
  {    
    return RES_PARERR;  /* count���ܵ���0�����򷵻ز������� */
  }

  switch (drv)
  {
    case 0:
	    if(count==1)            /* 1��sector��д���� */      
	    {   
		    /* Write block of 512 bytes on address 0 */
		    Status = SD_WriteBlock((uint8_t *)buff, sector << 9, _MAX_SS);
		    /* Check if the Transfer is finished */
		    //Status = SD_WaitWriteOperation();
		    while(SD_GetStatus() != SD_TRANSFER_OK);
	    }                                                
	    else                    /* ���sector��д���� */    
	    {   
		    /* Write multiple block of many bytes on address 0 */
		    Status = SD_WriteMultiBlocks((uint8_t *)buff, sector << 9, _MAX_SS, count);
		    /* Check if the Transfer is finished */
		    //Status = SD_WaitWriteOperation();
		    while(SD_GetStatus() != SD_TRANSFER_OK);
			//if(SD_OK == Status)return RES_OK;  
	    }                                                
	    if(Status == SD_OK)
	    {
	       return RES_OK;
	    }
	    else
	    {
	       printf("write data error : %d\n\r",Status);
		   return RES_ERROR;
	    }
    default :
       break;
  }
 return RES_ERROR;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	if(drv==0){
		SD_GetCardInfo(&SDCardInfo);
		switch (ctrl) 
		{
		  case CTRL_SYNC : 
			return RES_OK;
		  case GET_SECTOR_COUNT : 
		    *(DWORD*)buff = SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize;
		    return RES_OK;
		  case GET_BLOCK_SIZE :
		    *(WORD*)buff = SDCardInfo.CardBlockSize;
		    return RES_OK;	
		  case CTRL_POWER :
			break;
		  case CTRL_LOCK :
			break;
		  case CTRL_EJECT :
			break;
	      /* MMC/SDC command */
		  case MMC_GET_TYPE :
			break;
		  case MMC_GET_CSD :
			break;
		  case MMC_GET_CID :
			break;
		  case MMC_GET_OCR :
			break;
		  case MMC_GET_SDSTAT :
			break;	
		} 
	}
	else{				  
		return RES_PARERR; /* ��֧�ֵ����̲��������򷵻ز������� */ 
	}
	return RES_PARERR; /* ��֧�ֵ����̲��������򷵻ز������� */ 
}

/* �õ��ļ�Calendar��ʽ�Ľ�������,��DWORD get_fattime (void) ��任 */							
/*-----------------------------------------------------------------------*/
/* User defined function to give a current time to fatfs module          */
/* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
/* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{
   
    return 0;
}



/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
