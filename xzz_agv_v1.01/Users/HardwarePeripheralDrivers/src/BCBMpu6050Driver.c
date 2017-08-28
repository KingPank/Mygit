/*----------------------------------------------------------------------------*/
/*
	File Name			:	Mpu6050.c
    Description			:	
    Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
    Version&Date		: 	<2015.4.28>  V1.0
    Connector Fuction 	:	
    Notes	£º				Analog signal
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

	/*---Head Files---*/
	#include "BCBMpu6050Driver.h"
	#include "stm32f4xx_iic_config.h"
    #include "BCBGlobalFunc.h"
	/*---Variable Definition--*/
	uint8_t buffer[14];
	int16_t MPU6050_FIFO[6][11] = {0};
	int MPU6050_SumFIFO[6] ={0};
	int16_t MPU6050_pInFIFO = 0;
	int16_t Gx_offset=33;
	int16_t Gy_offset=33;
	int16_t Gz_offset=33;
	/*---Function Definiton---*/
	void 	MPU6050_NewValues(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz);
	void 	MPU6050_SetClockSource(uint8_t source);
	void 	MPU6050_SetFullScaleGyroRange(uint8_t range) ;
	void 	MPU6050_SetFullScaleAccelRange(uint8_t range) ;
	void 	MPU6050_SetSleepEnabled(uint8_t enabled);
	uint8_t MPU6050_GetDeviceID(void);
	uint8_t MPU6050_TestConnection(void) ;
	void 	MPU6050_SetI2CMasterModeEnabled(uint8_t enabled) ;
	void 	MPU6050_SetI2CBypassEnabled(uint8_t enabled);
	uint8_t MPU6050_is_DRY(void);
	void 	MPU6050_Configuation(void);
	void 	MPU6050_getMotion6(int16_t* accgyroval);
	void 	MPU6050_getlastMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
	void 	MPU6050_InitGyro_Offset(void);
	
	short MPU6050_GetDeviceWD(void);
  void MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
  void MPU_Get_Accelerometer(float *axc);
	
	
	void Mpu6050_ReadGyro(float * pwGyroX,float * pwGyroY, float * pwGyroZ);
	/*---Macro Definition-----*/
	#define devAddr  0xD0
	#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
	#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
	#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW
	#define MPU6050_RA_XG_OFFS_TC       0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
	#define MPU6050_RA_YG_OFFS_TC       0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
	#define MPU6050_RA_ZG_OFFS_TC       0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
	#define MPU6050_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
	#define MPU6050_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
	#define MPU6050_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
	#define MPU6050_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
	#define MPU6050_RA_XA_OFFS_L_TC     0x07
	#define MPU6050_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
	#define MPU6050_RA_YA_OFFS_L_TC     0x09
	#define MPU6050_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
	#define MPU6050_RA_ZA_OFFS_L_TC     0x0B
	#define MPU6050_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
	#define MPU6050_RA_XG_OFFS_USRL     0x14
	#define MPU6050_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
	#define MPU6050_RA_YG_OFFS_USRL     0x16
	#define MPU6050_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
	#define MPU6050_RA_ZG_OFFS_USRL     0x18
	#define MPU6050_RA_SMPLRT_DIV       0x19
	#define MPU6050_RA_CONFIG           0x1A
	#define MPU6050_RA_GYRO_CONFIG      0x1B
	#define MPU6050_RA_ACCEL_CONFIG     0x1C
	#define MPU6050_RA_FF_THR           0x1D
	#define MPU6050_RA_FF_DUR           0x1E
	#define MPU6050_RA_MOT_THR          0x1F
	#define MPU6050_RA_MOT_DUR          0x20
	#define MPU6050_RA_ZRMOT_THR        0x21
	#define MPU6050_RA_ZRMOT_DUR        0x22
	#define MPU6050_RA_FIFO_EN          0x23
	#define MPU6050_RA_I2C_MST_CTRL     0x24
	#define MPU6050_RA_I2C_SLV0_ADDR    0x25
	#define MPU6050_RA_I2C_SLV0_REG     0x26
	#define MPU6050_RA_I2C_SLV0_CTRL    0x27
	#define MPU6050_RA_I2C_SLV1_ADDR    0x28
	#define MPU6050_RA_I2C_SLV1_REG     0x29
	#define MPU6050_RA_I2C_SLV1_CTRL    0x2A
	#define MPU6050_RA_I2C_SLV2_ADDR    0x2B
	#define MPU6050_RA_I2C_SLV2_REG     0x2C
	#define MPU6050_RA_I2C_SLV2_CTRL    0x2D
	#define MPU6050_RA_I2C_SLV3_ADDR    0x2E
	#define MPU6050_RA_I2C_SLV3_REG     0x2F
	#define MPU6050_RA_I2C_SLV3_CTRL    0x30
	#define MPU6050_RA_I2C_SLV4_ADDR    0x31
	#define MPU6050_RA_I2C_SLV4_REG     0x32
	#define MPU6050_RA_I2C_SLV4_DO      0x33
	#define MPU6050_RA_I2C_SLV4_CTRL    0x34
	#define MPU6050_RA_I2C_SLV4_DI      0x35
	#define MPU6050_RA_I2C_MST_STATUS   0x36
	#define MPU6050_RA_INT_PIN_CFG      0x37
	#define MPU6050_RA_INT_ENABLE       0x38
	#define MPU6050_RA_DMP_INT_STATUS   0x39
	#define MPU6050_RA_INT_STATUS       0x3A
	#define MPU6050_RA_ACCEL_XOUT_H     0x3B
	#define MPU6050_RA_ACCEL_XOUT_L     0x3C
	#define MPU6050_RA_ACCEL_YOUT_H     0x3D
	#define MPU6050_RA_ACCEL_YOUT_L     0x3E
	#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
	#define MPU6050_RA_ACCEL_ZOUT_L     0x40
	#define MPU6050_RA_TEMP_OUT_H       0x41
	#define MPU6050_RA_TEMP_OUT_L       0x42
	#define MPU6050_RA_GYRO_XOUT_H      0x43
	#define MPU6050_RA_GYRO_XOUT_L      0x44
	#define MPU6050_RA_GYRO_YOUT_H      0x45
	#define MPU6050_RA_GYRO_YOUT_L      0x46
	#define MPU6050_RA_GYRO_ZOUT_H      0x47
	#define MPU6050_RA_GYRO_ZOUT_L      0x48
	#define MPU6050_RA_EXT_SENS_DATA_00 0x49
	#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
	#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
	#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
	#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
	#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
	#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
	#define MPU6050_RA_EXT_SENS_DATA_07 0x50
	#define MPU6050_RA_EXT_SENS_DATA_08 0x51
	#define MPU6050_RA_EXT_SENS_DATA_09 0x52
	#define MPU6050_RA_EXT_SENS_DATA_10 0x53
	#define MPU6050_RA_EXT_SENS_DATA_11 0x54
	#define MPU6050_RA_EXT_SENS_DATA_12 0x55
	#define MPU6050_RA_EXT_SENS_DATA_13 0x56
	#define MPU6050_RA_EXT_SENS_DATA_14 0x57
	#define MPU6050_RA_EXT_SENS_DATA_15 0x58
	#define MPU6050_RA_EXT_SENS_DATA_16 0x59
	#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
	#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
	#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
	#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
	#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
	#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
	#define MPU6050_RA_EXT_SENS_DATA_23 0x60
	#define MPU6050_RA_MOT_DETECT_STATUS    0x61
	#define MPU6050_RA_I2C_SLV0_DO      0x63
	#define MPU6050_RA_I2C_SLV1_DO      0x64
	#define MPU6050_RA_I2C_SLV2_DO      0x65
	#define MPU6050_RA_I2C_SLV3_DO      0x66
	#define MPU6050_RA_I2C_MST_DELAY_CTRL   0x67
	#define MPU6050_RA_SIGNAL_PATH_RESET    0x68
	#define MPU6050_RA_MOT_DETECT_CTRL      0x69
	#define MPU6050_RA_USER_CTRL        0x6A
	#define MPU6050_RA_PWR_MGMT_1       0x6B
	#define MPU6050_RA_PWR_MGMT_2       0x6C
	#define MPU6050_RA_BANK_SEL         0x6D
	#define MPU6050_RA_MEM_START_ADDR   0x6E
	#define MPU6050_RA_MEM_R_W          0x6F
	#define MPU6050_RA_DMP_CFG_1        0x70
	#define MPU6050_RA_DMP_CFG_2        0x71
	#define MPU6050_RA_FIFO_COUNTH      0x72
	#define MPU6050_RA_FIFO_COUNTL      0x73
	#define MPU6050_RA_FIFO_R_W         0x74
	#define MPU6050_RA_WHO_AM_I         0x75
	#define MPU6050_TC_PWR_MODE_BIT     7
	#define MPU6050_TC_OFFSET_BIT       6
	#define MPU6050_TC_OFFSET_LENGTH    6
	#define MPU6050_TC_OTP_BNK_VLD_BIT  0
	#define MPU6050_VDDIO_LEVEL_VLOGIC  0
	#define MPU6050_VDDIO_LEVEL_VDD     1
	#define MPU6050_CFG_EXT_SYNC_SET_BIT    5
	#define MPU6050_CFG_EXT_SYNC_SET_LENGTH 3
	#define MPU6050_CFG_DLPF_CFG_BIT    2
	#define MPU6050_CFG_DLPF_CFG_LENGTH 3
	#define MPU6050_EXT_SYNC_DISABLED       0x0
	#define MPU6050_EXT_SYNC_TEMP_OUT_L     0x1
	#define MPU6050_EXT_SYNC_GYRO_XOUT_L    0x2
	#define MPU6050_EXT_SYNC_GYRO_YOUT_L    0x3
	#define MPU6050_EXT_SYNC_GYRO_ZOUT_L    0x4
	#define MPU6050_EXT_SYNC_ACCEL_XOUT_L   0x5
	#define MPU6050_EXT_SYNC_ACCEL_YOUT_L   0x6
	#define MPU6050_EXT_SYNC_ACCEL_ZOUT_L   0x7
	#define MPU6050_DLPF_BW_256         0x00
	#define MPU6050_DLPF_BW_188         0x01
	#define MPU6050_DLPF_BW_98          0x02
	#define MPU6050_DLPF_BW_42          0x03
	#define MPU6050_DLPF_BW_20          0x04
	#define MPU6050_DLPF_BW_10          0x05
	#define MPU6050_DLPF_BW_5           0x06

	#define MPU6050_GCONFIG_FS_SEL_BIT      4
	#define MPU6050_GCONFIG_FS_SEL_LENGTH   2

	#define MPU6050_GYRO_FS_250         0x00
	#define MPU6050_GYRO_FS_500         0x01
	#define MPU6050_GYRO_FS_1000        0x02
	#define MPU6050_GYRO_FS_2000        0x03

	#define MPU6050_ACONFIG_XA_ST_BIT           7
	#define MPU6050_ACONFIG_YA_ST_BIT           6
	#define MPU6050_ACONFIG_ZA_ST_BIT           5
	#define MPU6050_ACONFIG_AFS_SEL_BIT         4
	#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2
	#define MPU6050_ACONFIG_ACCEL_HPF_BIT       2
	#define MPU6050_ACONFIG_ACCEL_HPF_LENGTH    3

	#define MPU6050_ACCEL_FS_2          0x00
	#define MPU6050_ACCEL_FS_4          0x01
	#define MPU6050_ACCEL_FS_8          0x02
	#define MPU6050_ACCEL_FS_16         0x03
	#define MPU6050_DHPF_RESET          0x00
	#define MPU6050_DHPF_5              0x01
	#define MPU6050_DHPF_2P5            0x02
	#define MPU6050_DHPF_1P25           0x03
	#define MPU6050_DHPF_0P63           0x04
	#define MPU6050_DHPF_HOLD           0x07
	#define MPU6050_TEMP_FIFO_EN_BIT    7
	#define MPU6050_XG_FIFO_EN_BIT      6
	#define MPU6050_YG_FIFO_EN_BIT      5
	#define MPU6050_ZG_FIFO_EN_BIT      4
	#define MPU6050_ACCEL_FIFO_EN_BIT   3
	#define MPU6050_SLV2_FIFO_EN_BIT    2
	#define MPU6050_SLV1_FIFO_EN_BIT    1
	#define MPU6050_SLV0_FIFO_EN_BIT    0
	#define MPU6050_MULT_MST_EN_BIT     7
	#define MPU6050_WAIT_FOR_ES_BIT     6
	#define MPU6050_SLV_3_FIFO_EN_BIT   5
	#define MPU6050_I2C_MST_P_NSR_BIT   4
	#define MPU6050_I2C_MST_CLK_BIT     3
	#define MPU6050_I2C_MST_CLK_LENGTH  4
	#define MPU6050_CLOCK_DIV_348       0x0
	#define MPU6050_CLOCK_DIV_333       0x1
	#define MPU6050_CLOCK_DIV_320       0x2
	#define MPU6050_CLOCK_DIV_308       0x3
	#define MPU6050_CLOCK_DIV_296       0x4
	#define MPU6050_CLOCK_DIV_286       0x5
	#define MPU6050_CLOCK_DIV_276       0x6
	#define MPU6050_CLOCK_DIV_267       0x7
	#define MPU6050_CLOCK_DIV_258       0x8
	#define MPU6050_CLOCK_DIV_500       0x9
	#define MPU6050_CLOCK_DIV_471       0xA
	#define MPU6050_CLOCK_DIV_444       0xB
	#define MPU6050_CLOCK_DIV_421       0xC
	#define MPU6050_CLOCK_DIV_400       0xD
	#define MPU6050_CLOCK_DIV_381       0xE
	#define MPU6050_CLOCK_DIV_364       0xF
	#define MPU6050_I2C_SLV_RW_BIT      7
	#define MPU6050_I2C_SLV_ADDR_BIT    6
	#define MPU6050_I2C_SLV_ADDR_LENGTH 7
	#define MPU6050_I2C_SLV_EN_BIT      7
	#define MPU6050_I2C_SLV_BYTE_SW_BIT 6
	#define MPU6050_I2C_SLV_REG_DIS_BIT 5
	#define MPU6050_I2C_SLV_GRP_BIT     4
	#define MPU6050_I2C_SLV_LEN_BIT     3
	#define MPU6050_I2C_SLV_LEN_LENGTH  4
	#define MPU6050_I2C_SLV4_RW_BIT         7
	#define MPU6050_I2C_SLV4_ADDR_BIT       6
	#define MPU6050_I2C_SLV4_ADDR_LENGTH    7
	#define MPU6050_I2C_SLV4_EN_BIT         7
	#define MPU6050_I2C_SLV4_INT_EN_BIT     6
	#define MPU6050_I2C_SLV4_REG_DIS_BIT    5
	#define MPU6050_I2C_SLV4_MST_DLY_BIT    4
	#define MPU6050_I2C_SLV4_MST_DLY_LENGTH 5
	#define MPU6050_MST_PASS_THROUGH_BIT    7
	#define MPU6050_MST_I2C_SLV4_DONE_BIT   6
	#define MPU6050_MST_I2C_LOST_ARB_BIT    5
	#define MPU6050_MST_I2C_SLV4_NACK_BIT   4
	#define MPU6050_MST_I2C_SLV3_NACK_BIT   3
	#define MPU6050_MST_I2C_SLV2_NACK_BIT   2
	#define MPU6050_MST_I2C_SLV1_NACK_BIT   1
	#define MPU6050_MST_I2C_SLV0_NACK_BIT   0
	#define MPU6050_INTCFG_INT_LEVEL_BIT        7
	#define MPU6050_INTCFG_INT_OPEN_BIT         6
	#define MPU6050_INTCFG_LATCH_INT_EN_BIT     5
	#define MPU6050_INTCFG_INT_RD_CLEAR_BIT     4
	#define MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT  3
	#define MPU6050_INTCFG_FSYNC_INT_EN_BIT     2
	#define MPU6050_INTCFG_I2C_BYPASS_EN_BIT    1
	#define MPU6050_INTCFG_CLKOUT_EN_BIT        0
	#define MPU6050_INTMODE_ACTIVEHIGH  0x00
	#define MPU6050_INTMODE_ACTIVELOW   0x01
	#define MPU6050_INTDRV_PUSHPULL     0x00
	#define MPU6050_INTDRV_OPENDRAIN    0x01
	#define MPU6050_INTLATCH_50USPULSE  0x00
	#define MPU6050_INTLATCH_WAITCLEAR  0x01
	#define MPU6050_INTCLEAR_STATUSREAD 0x00
	#define MPU6050_INTCLEAR_ANYREAD    0x01
	#define MPU6050_INTERRUPT_FF_BIT            7
	#define MPU6050_INTERRUPT_MOT_BIT           6
	#define MPU6050_INTERRUPT_ZMOT_BIT          5
	#define MPU6050_INTERRUPT_FIFO_OFLOW_BIT    4
	#define MPU6050_INTERRUPT_I2C_MST_INT_BIT   3
	#define MPU6050_INTERRUPT_PLL_RDY_INT_BIT   2
	#define MPU6050_INTERRUPT_DMP_INT_BIT       1
	#define MPU6050_INTERRUPT_DATA_RDY_BIT      0
	#define MPU6050_DMPINT_5_BIT            5
	#define MPU6050_DMPINT_4_BIT            4
	#define MPU6050_DMPINT_3_BIT            3
	#define MPU6050_DMPINT_2_BIT            2
	#define MPU6050_DMPINT_1_BIT            1
	#define MPU6050_DMPINT_0_BIT            0
	#define MPU6050_MOTION_MOT_XNEG_BIT     7
	#define MPU6050_MOTION_MOT_XPOS_BIT     6
	#define MPU6050_MOTION_MOT_YNEG_BIT     5
	#define MPU6050_MOTION_MOT_YPOS_BIT     4
	#define MPU6050_MOTION_MOT_ZNEG_BIT     3
	#define MPU6050_MOTION_MOT_ZPOS_BIT     2
	#define MPU6050_MOTION_MOT_ZRMOT_BIT    0
	#define MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
	#define MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
	#define MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
	#define MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
	#define MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
	#define MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0
	#define MPU6050_PATHRESET_GYRO_RESET_BIT    2
	#define MPU6050_PATHRESET_ACCEL_RESET_BIT   1
	#define MPU6050_PATHRESET_TEMP_RESET_BIT    0
	#define MPU6050_DETECT_ACCEL_ON_DELAY_BIT       5
	#define MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH    2
	#define MPU6050_DETECT_FF_COUNT_BIT             3
	#define MPU6050_DETECT_FF_COUNT_LENGTH          2
	#define MPU6050_DETECT_MOT_COUNT_BIT            1
	#define MPU6050_DETECT_MOT_COUNT_LENGTH         2
	#define MPU6050_DETECT_DECREMENT_RESET  0x0
	#define MPU6050_DETECT_DECREMENT_1      0x1
	#define MPU6050_DETECT_DECREMENT_2      0x2
	#define MPU6050_DETECT_DECREMENT_4      0x3
	#define MPU6050_USERCTRL_FIFO_EN_BIT            6
	#define MPU6050_USERCTRL_I2C_MST_EN_BIT         5
	#define MPU6050_USERCTRL_I2C_IF_DIS_BIT         4
	#define MPU6050_USERCTRL_DMP_RESET_BIT          3
	#define MPU6050_USERCTRL_FIFO_RESET_BIT         2
	#define MPU6050_USERCTRL_I2C_MST_RESET_BIT      1
	#define MPU6050_USERCTRL_SIG_COND_RESET_BIT     0
	#define MPU6050_PWR1_DEVICE_RESET_BIT   7
	#define MPU6050_PWR1_SLEEP_BIT          6
	#define MPU6050_PWR1_CYCLE_BIT          5
	#define MPU6050_PWR1_TEMP_DIS_BIT       3
	#define MPU6050_PWR1_CLKSEL_BIT         2
	#define MPU6050_PWR1_CLKSEL_LENGTH      3
	#define MPU6050_CLOCK_INTERNAL          0x00
	#define MPU6050_CLOCK_PLL_XGYRO         0x01
	#define MPU6050_CLOCK_PLL_YGYRO         0x02
	#define MPU6050_CLOCK_PLL_ZGYRO         0x03
	#define MPU6050_CLOCK_PLL_EXT32K        0x04
	#define MPU6050_CLOCK_PLL_EXT19M        0x05
	#define MPU6050_CLOCK_KEEP_RESET        0x07
	#define MPU6050_PWR2_LP_WAKE_CTRL_BIT       7
	#define MPU6050_PWR2_LP_WAKE_CTRL_LENGTH    2
	#define MPU6050_PWR2_STBY_XA_BIT            5
	#define MPU6050_PWR2_STBY_YA_BIT            4
	#define MPU6050_PWR2_STBY_ZA_BIT            3
	#define MPU6050_PWR2_STBY_XG_BIT            2
	#define MPU6050_PWR2_STBY_YG_BIT            1
	#define MPU6050_PWR2_STBY_ZG_BIT            0
	#define MPU6050_WAKE_FREQ_1P25      0x0
	#define MPU6050_WAKE_FREQ_2P5       0x1
	#define MPU6050_WAKE_FREQ_5         0x2
	#define MPU6050_WAKE_FREQ_10        0x3
	#define MPU6050_BANKSEL_PRFTCH_EN_BIT       6
	#define MPU6050_BANKSEL_CFG_USER_BANK_BIT   5
	#define MPU6050_BANKSEL_MEM_SEL_BIT         4
	#define MPU6050_BANKSEL_MEM_SEL_LENGTH      5
	#define MPU6050_WHO_AM_I_BIT        6
	#define MPU6050_WHO_AM_I_LENGTH     6


	#define		GYRO_LSB		0.0010653

	#define	MPU6050_ReadByte(byAD,byRA,pdata)					IIC1_ReadData(byAD,byRA,pdata,1)
	#define	MPU6050_ReadBytes(byAD,byRA,count,pdata)			IIC1_ReadData(byAD,byRA,pdata,count)
	#define	MPU6050_WriteByte()									xx
	#define	MPU6050_WriteClassBytes()							xx
	#define	MPU6050_WriteBits(dev,reg,bitStart,length,data)		IIC1_WriteBits(dev,reg,bitStart,length,data)
	#define	MPU6050_WriteBit(dev,reg,bitNum,data)			 	IIC1_WriteBit(dev,reg,bitNum,data)
	#define	MPU6050_DelayUs(tim)								delay_us(tim)			
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	MPU6050_NewValues
Description       :		
Input parameter   :   				Name		Action
						int16_t ax
						int16_t ay
						int16_t az
						int16_t gx
						int16_t gy
						int16_t gz
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2015.4.28
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void  MPU6050_NewValues(int16_t ax,int16_t ay,int16_t az,int16_t gx,int16_t gy,int16_t gz)
{
	
	MPU6050_SumFIFO[0] -= MPU6050_FIFO[0][MPU6050_pInFIFO];
	MPU6050_SumFIFO[1] -= MPU6050_FIFO[1][MPU6050_pInFIFO];
	MPU6050_SumFIFO[2] -= MPU6050_FIFO[2][MPU6050_pInFIFO];
	MPU6050_SumFIFO[3] -= MPU6050_FIFO[3][MPU6050_pInFIFO];
	MPU6050_SumFIFO[4] -= MPU6050_FIFO[4][MPU6050_pInFIFO];
	MPU6050_SumFIFO[5] -= MPU6050_FIFO[5][MPU6050_pInFIFO];
	
	MPU6050_FIFO[0][MPU6050_pInFIFO] = ax;
	MPU6050_FIFO[1][MPU6050_pInFIFO] = ay;
	MPU6050_FIFO[2][MPU6050_pInFIFO] = az;
	MPU6050_FIFO[3][MPU6050_pInFIFO] = gx;
	MPU6050_FIFO[4][MPU6050_pInFIFO] = gy;
	MPU6050_FIFO[5][MPU6050_pInFIFO] = gz;	

	MPU6050_SumFIFO[0] += MPU6050_FIFO[0][MPU6050_pInFIFO];
	MPU6050_SumFIFO[1] += MPU6050_FIFO[1][MPU6050_pInFIFO];
	MPU6050_SumFIFO[2] += MPU6050_FIFO[2][MPU6050_pInFIFO];
	MPU6050_SumFIFO[3] += MPU6050_FIFO[3][MPU6050_pInFIFO];
	MPU6050_SumFIFO[4] += MPU6050_FIFO[4][MPU6050_pInFIFO];
	MPU6050_SumFIFO[5] += MPU6050_FIFO[5][MPU6050_pInFIFO];

	MPU6050_pInFIFO++;
	if(MPU6050_pInFIFO >= 10)
	{

		MPU6050_pInFIFO = 0;
	}
	MPU6050_FIFO[0][10] = MPU6050_SumFIFO[0] / 10;
	MPU6050_FIFO[1][10] = MPU6050_SumFIFO[1] / 10;
	MPU6050_FIFO[2][10] = MPU6050_SumFIFO[2] / 10;
	MPU6050_FIFO[3][10] = MPU6050_SumFIFO[3] / 10;
	MPU6050_FIFO[4][10] = MPU6050_SumFIFO[4] / 10;
	MPU6050_FIFO[5][10] = MPU6050_SumFIFO[5] / 10;
	
}
void MPU6050_SetClockSource(uint8_t source)
{
    MPU6050_WriteBits(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}
void MPU6050_SetFullScaleGyroRange(uint8_t range) 
{
    MPU6050_WriteBits(devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}
void MPU6050_SetFullScaleAccelRange(uint8_t range) 
{
    MPU6050_WriteBits(devAddr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}
void MPU6050_SetSleepEnabled(uint8_t enabled)
{
    MPU6050_WriteBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}
uint8_t MPU6050_GetDeviceID(void)
{

    MPU6050_ReadBytes(devAddr, MPU6050_RA_WHO_AM_I, 1, buffer);
    return buffer[0];
}
uint8_t MPU6050_TestConnection(void) {
   if(MPU6050_GetDeviceID() == 0x68)  //0b01101000;
   return 1;
   	else return 0;
}
void MPU6050_SetI2CMasterModeEnabled(uint8_t enabled) {
    MPU6050_WriteBit(devAddr, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, enabled);
}
void MPU6050_SetI2CBypassEnabled(uint8_t enabled) {
    MPU6050_WriteBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, enabled);
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	MPU6050_Configuation
Description       :	   	
						Input parameter   :   	Class			Name		Action
						uint8_t 		source

Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2015.4.28
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void MPU6050_Configuation(void)
 {
	int16_t temp[6];
	unsigned char i;
	MPU6050_SetClockSource(MPU6050_CLOCK_PLL_XGYRO);
	MPU6050_SetFullScaleGyroRange(MPU6050_GYRO_FS_1000);	
	MPU6050_SetFullScaleAccelRange(MPU6050_ACCEL_FS_2);	
	MPU6050_SetSleepEnabled(0); 						
	MPU6050_SetI2CMasterModeEnabled(0);						
	MPU6050_SetI2CBypassEnabled(1);	 					
														
	MPU6050_WriteBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_LEVEL_BIT, 0);
	MPU6050_WriteBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_OPEN_BIT, 0);
	MPU6050_WriteBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_LATCH_INT_EN_BIT, 1);
	MPU6050_WriteBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_INT_RD_CLEAR_BIT, 1);		
  MPU6050_WriteBit(devAddr, MPU6050_RA_INT_ENABLE, MPU6050_INTERRUPT_DATA_RDY_BIT, 1);

	for(i=0;i<10;i++)
	{													
		MPU6050_DelayUs(50);
		MPU6050_getMotion6(temp);
	}
																			 
//	MPU6050_InitGyro_Offset();
}

unsigned char MPU6050_is_DRY(void)
{
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==Bit_SET){
	  return 1;
	 }
	 else return 0;
}

int16_t MPU6050_Lastax,MPU6050_Lastay,MPU6050_Lastaz,MPU6050_Lastgx,MPU6050_Lastgy,MPU6050_Lastgz;

/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	MPU6050_getMotion6
Description       :	   	
Input parameter   :   	Class			Name		Action
						int16_t* ax
						int16_t* ay
						int16_t* az
						int16_t* gx
						int16_t* gY 
						int16_t* gz

Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2015.4.28
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void MPU6050_getMotion6(int16_t* accgyroval) 
{
  
	if(1){
	MPU6050_ReadBytes(devAddr, MPU6050_RA_ACCEL_XOUT_H, 14, buffer);
    MPU6050_Lastax=(((int16_t)buffer[0]) << 8) | buffer[1];
    MPU6050_Lastay=(((int16_t)buffer[2]) << 8) | buffer[3];
    MPU6050_Lastaz=(((int16_t)buffer[4]) << 8) | buffer[5];
	//Ìø¹ýÎÂ¶ÈADC
    MPU6050_Lastgx=(((int16_t)buffer[8]) << 8) | buffer[9];
    MPU6050_Lastgy=(((int16_t)buffer[10]) << 8) | buffer[11];
    MPU6050_Lastgz=(((int16_t)buffer[12]) << 8) | buffer[13];
		
	MPU6050_NewValues(MPU6050_Lastax,MPU6050_Lastay,MPU6050_Lastaz
		,MPU6050_Lastgx,MPU6050_Lastgy,MPU6050_Lastgz);
		
	*(accgyroval+0)  =MPU6050_FIFO[0][10];
	*(accgyroval+1)   =MPU6050_FIFO[1][10];
	*(accgyroval+2) = MPU6050_FIFO[2][10];
	*(accgyroval+3)  =MPU6050_FIFO[3][10]-Gx_offset; 
	*(accgyroval+4) = MPU6050_FIFO[4][10]-Gy_offset;
	*(accgyroval+5) = MPU6050_FIFO[5][10]-Gz_offset;
		
//	*(accgyroval+3)  =MPU6050_FIFO[3][10]; 
//	*(accgyroval+4) = MPU6050_FIFO[4][10];
//	*(accgyroval+5) = MPU6050_FIFO[5][10];
	} else {
	*(accgyroval+0)= MPU6050_FIFO[0][10];//=MPU6050_FIFO[0][10];
	*(accgyroval+1) = MPU6050_FIFO[1][10];//=MPU6050_FIFO[1][10];
	*(accgyroval+2) = MPU6050_FIFO[2][10];//=MPU6050_FIFO[2][10];
	*(accgyroval+3) = MPU6050_FIFO[3][10]-Gx_offset;//=MPU6050_FIFO[3][10];
	*(accgyroval+4) = MPU6050_FIFO[4][10]-Gy_offset;//=MPU6050_FIFO[4][10];
	*(accgyroval+5) = MPU6050_FIFO[5][10]-Gz_offset;//=MPU6050_FIFO[5][10];
	}
} 
#define	 BIT_GYRO 1000/32768
#define	 BIT_ACCEL 2/32768
void MPU6050_GetValues(float* accgyroval)
{
	int16_t temp[6];
	MPU6050_getMotion6(temp);
	for(int i = 0; i < 3; i++)
	{
		accgyroval[i] = temp[i];
		accgyroval[i] = accgyroval[i];
		accgyroval[i+3] = temp[i+3];
		accgyroval[i+3]  = accgyroval[i+3];
	}
}
void MPU6050_getlastMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz)
{
	*ax  =MPU6050_FIFO[0][10];
	*ay  =MPU6050_FIFO[1][10];
	*az = MPU6050_FIFO[2][10];
	*gx  =MPU6050_FIFO[3][10]-Gx_offset;
	*gy = MPU6050_FIFO[4][10]-Gy_offset;
	*gz = MPU6050_FIFO[5][10]-Gz_offset;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	MPU6050_InitGyro_Offset
Description       :	   	
Input parameter   :   	Class			Name		Action
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2015.4.28
Notes             :	
*/
/*----------------------------------------------------------------------------*/
//void MPU6050_InitGyro_Offset(void)
//{
//	unsigned char i;
//	int16_t temp[6];
//	int32_t	tempgx=0,tempgy=0,tempgz=0;
//	int32_t	tempax=0,tempay=0,tempaz=0;
//	Gx_offset=0;
//	Gy_offset=0;
//	Gz_offset=0;
//	for(i=0;i<50;i++){
//  		//MPU6050_DelayUs(100);
//  		MPU6050_getMotion6(temp);
//  	//	LED_Change();
//	}
// 	for(i=0;i<100;i++){
//	//	delay_us(200);
//		MPU6050_getMotion6(temp);
//		tempax+= temp[0];
//		tempay+= temp[1];
//		tempaz+= temp[2];
//		tempgx+= temp[3];
//		tempgy+= temp[4];
//		tempgz+= temp[5];
//	//	LED_Change();
//	}

//	Gx_offset=tempgx/100;//MPU6050_FIFO[3][10];
//	Gy_offset=tempgy/100;//MPU6050_FIFO[4][10];
//	Gz_offset=tempgz/100;//MPU6050_FIFO[5][10];
//	tempax/=100;
//	tempay/=100;
//	tempaz/=100;
//	
//	EepromIMUOffsetData.MPU6050GyroOffset.X = Gx_offset;
//	EepromIMUOffsetData.MPU6050GyroOffset.Y = Gy_offset;
//	EepromIMUOffsetData.MPU6050GyroOffset.Z = Gz_offset;
//}
void MPU6050_SetGyroOffset(float gx,float gy,float gz)
{
	Gx_offset = gx;
	Gy_offset = gy;
	Gz_offset = gz;
}


short MPU6050_GetDeviceWD(void)//温度
{
	u8 buffer_wd[2];
	short int raw;
	float sun;
	MPU6050_ReadBytes(devAddr, MPU6050_RA_TEMP_OUT_H, 2 , buffer_wd);
	    raw=((u16)buffer_wd[0]<<8)|buffer_wd[1];  
      sun=36.53+((double)raw)/340;  
     return sun*100;
	
//	*wd=buffer_wd[0];
//	*(wd+1)=buffer_wd[1];
	
}

void MPU_Get_Gyroscope(short *gx,short *gy,short *gz)   //X,Y,Z原始数据
{
    u8 buf[6];  
	MPU6050_ReadBytes(devAddr,MPU6050_RA_GYRO_XOUT_H ,6,buf);
	
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
		
   
}

void MPU_Get_Accelerometer(float *axc)//加速度
{
    u8 buf[6];  
	  int16_t ax,ay,az;
	  MPU6050_ReadBytes(devAddr,MPU6050_RA_ACCEL_XOUT_H,6,buf);
		
	
		ax=((u16)buf[0]<<8)|buf[1];
  
		ay=((u16)buf[2]<<8)|buf[3];
  
		az=((u16)buf[4]<<8)|buf[5];



	  *axc=(ax)*16/32767.0;
	  *(axc+1)=(ay)*16/32767.0;
	  *(axc+2)=(az)*16/32767.0;
	
}
