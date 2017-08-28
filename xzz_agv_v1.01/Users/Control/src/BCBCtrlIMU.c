/*----------------------------------------------------------------------------*/
/*
	File Name			:	
	Description			:		
	Author				:  	Jones.Lee 
	Copyright			: 	Jones_Workspace
							Copyright (C) 2014, KeyBot, all right reserved.
	Version&Date		: 	<2015.4.28>  V1.0
	Connector Fuction 	:
	Notes				:	
*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
    /*---Head Files---*/
	#include "BCBCtrlIMU.h"
	#include "BCBMpu6050Driver.h"
	#include "BCBHmc5883LDriver.h"
	#include "BCBGlobalFunc.h"
	#include "BCBADXRS620Driver.h"
    /*---Macro Definition-----*/
	/*---Variable Definition--*/
	volatile float exInt, eyInt, ezInt;  	// Îó²î»ý·Ö
	volatile float q0, q1, q2, q3; 			// È«¾ÖËÄÔªÊý
	volatile float integralFBhand,handdiff;
	float halfT;
	float mygetqval[9];	
	
	float sampleFreq	 = 0;		// sample frequency in Hz
	#define betaDef		0.1f		// 2 * proportional gain
	volatile float beta = betaDef;								// 2 * proportional gain (Kp)
	
	
	#define twoKpDef	(2.0f * 0.5f)	// 2 * proportional gain
	#define twoKiDef	(2.0f * 0.0f)	// 2 * integral gain

//---------------------------------------------------------------------------------------------------
// Variable definitions

	volatile float twoKp = twoKpDef;											// 2 * proportional gain (Kp)
	volatile float twoKi = twoKiDef;											// 2 * integral gain (Ki)
	volatile float integralFBx = 0.0f,  integralFBy = 0.0f, integralFBz = 0.0f;	// integral error terms scaled by Ki

	/*---Function Definiton---*/
	void IMU_init(void);
	float invSqrt(float x);
	void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
	void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az) ;
	void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
	void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	
Description       :		
Input parameter   :   	Class			Name		Action
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}
/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	
Description       :	
						³õÊ¼»¯IMUÏà¹Ø	
						³õÊ¼»¯¸÷¸ö´«¸ÐÆ÷
						³õÊ¼»¯ËÄÔªÊý
						½«»ý·ÖÇåÁã
						¸üÐÂÏµÍ³Ê±¼ä
Input parameter   :   	Class			Name		Action
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void IMU_init(void)
{	
	delay_ms(10);
	MPU6050_Configuation();
	delay_ms(10);
//	HMC5883L_SetUp();
	delay_ms(10);
	// initialize quaternion
  	q0 = 1.0f;  //³õÊ¼»¯ËÄÔªÊý
  	q1 = 0.0f;
  	q2 = 0.0f;
  	q3 = 0.0f;
  	exInt = 0.0;
  	eyInt = 0.0;
  	ezInt = 0.0;
}
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az) {
	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;   

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_4q0 = 4.0f * q0;
		_4q1 = 4.0f * q1;
		_4q2 = 4.0f * q2;
		_8q1 = 8.0f * q1;
		_8q2 = 8.0f * q2;
		q0q0 = q0 * q0;
		q1q1 = q1 * q1;
		q2q2 = q2 * q2;
		q3q3 = q3 * q3;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * (1.0f / sampleFreq);
	q1 += qDot2 * (1.0f / sampleFreq);
	q2 += qDot3 * (1.0f / sampleFreq);
	q3 += qDot4 * (1.0f / sampleFreq);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}

void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz) {

	float recipNorm;
	float s0, s1, s2, s3;
	float qDot1, qDot2, qDot3, qDot4;
	float hx, hy;
	float _2q0mx, _2q0my, _2q0mz, _2q1mx, _2bx, _2bz, _4bx, _4bz, _2q0, _2q1, _2q2, _2q3, _2q0q2, _2q2q3, q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;

	// Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
	if((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)) {
		MadgwickAHRSupdateIMU(gx, gy, gz, ax, ay, az);
		return;
	}

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-q1 * gx - q2 * gy - q3 * gz);
	qDot2 = 0.5f * (q0 * gx + q2 * gz - q3 * gy);
	qDot3 = 0.5f * (q0 * gy - q1 * gz + q3 * gx);
	qDot4 = 0.5f * (q0 * gz + q1 * gy - q2 * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;   

		// Normalise magnetometer measurement
		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
		mx *= recipNorm;
		my *= recipNorm;
		mz *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0mx = 2.0f * q0 * mx;
		_2q0my = 2.0f * q0 * my;
		_2q0mz = 2.0f * q0 * mz;
		_2q1mx = 2.0f * q1 * mx;
		_2q0 = 2.0f * q0;
		_2q1 = 2.0f * q1;
		_2q2 = 2.0f * q2;
		_2q3 = 2.0f * q3;
		_2q0q2 = 2.0f * q0 * q2;
		_2q2q3 = 2.0f * q2 * q3;
		q0q0 = q0 * q0;
		q0q1 = q0 * q1;
		q0q2 = q0 * q2;
		q0q3 = q0 * q3;
		q1q1 = q1 * q1;
		q1q2 = q1 * q2;
		q1q3 = q1 * q3;
		q2q2 = q2 * q2;
		q2q3 = q2 * q3;
		q3q3 = q3 * q3;

		// Reference direction of Earth's magnetic field
		hx = mx * q0q0 - _2q0my * q3 + _2q0mz * q2 + mx * q1q1 + _2q1 * my * q2 + _2q1 * mz * q3 - mx * q2q2 - mx * q3q3;
		hy = _2q0mx * q3 + my * q0q0 - _2q0mz * q1 + _2q1mx * q2 - my * q1q1 + my * q2q2 + _2q2 * mz * q3 - my * q3q3;
		_2bx = sqrt(hx * hx + hy * hy);
		_2bz = -_2q0mx * q2 + _2q0my * q1 + mz * q0q0 + _2q1mx * q3 - mz * q1q1 + _2q2 * my * q3 - mz * q2q2 + mz * q3q3;
		_4bx = 2.0f * _2bx;
		_4bz = 2.0f * _2bz;

		// Gradient decent algorithm corrective step
		s0 = -_2q2 * (2.0f * q1q3 - _2q0q2 - ax) + _2q1 * (2.0f * q0q1 + _2q2q3 - ay) - _2bz * q2 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q3 + _2bz * q1) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q2 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s1 = _2q3 * (2.0f * q1q3 - _2q0q2 - ax) + _2q0 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q1 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + _2bz * q3 * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q2 + _2bz * q0) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q3 - _4bz * q1) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s2 = -_2q0 * (2.0f * q1q3 - _2q0q2 - ax) + _2q3 * (2.0f * q0q1 + _2q2q3 - ay) - 4.0f * q2 * (1 - 2.0f * q1q1 - 2.0f * q2q2 - az) + (-_4bx * q2 - _2bz * q0) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (_2bx * q1 + _2bz * q3) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + (_2bx * q0 - _4bz * q2) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		s3 = _2q1 * (2.0f * q1q3 - _2q0q2 - ax) + _2q2 * (2.0f * q0q1 + _2q2q3 - ay) + (-_4bx * q3 + _2bz * q1) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mx) + (-_2bx * q0 + _2bz * q2) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - my) + _2bx * q1 * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mz);
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
		qDot1 -= beta * s0;
		qDot2 -= beta * s1;
		qDot3 -= beta * s2;
		qDot4 -= beta * s3;
	}

	// Integrate rate of change of quaternion to yield quaternion
	q0 += qDot1 * (1.0f / sampleFreq);
	q1 += qDot2 * (1.0f / sampleFreq);
	q2 += qDot3 * (1.0f / sampleFreq);
	q3 += qDot4 * (1.0f / sampleFreq);

	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}
void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz) {
	float recipNorm;
    float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;  
	float hx, hy, bx, bz;
	float halfvx, halfvy, halfvz, halfwx, halfwy, halfwz;
	float halfex, halfey, halfez;
	float qa, qb, qc;

	// Use IMU algorithm if magnetometer measurement invalid (avoids NaN in magnetometer normalisation)
	if((mx == 0.0f) && (my == 0.0f) && (mz == 0.0f)) {
		MahonyAHRSupdateIMU(gx, gy, gz, ax, ay, az);
		return;
	}

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;     

		// Normalise magnetometer measurement
		recipNorm = invSqrt(mx * mx + my * my + mz * mz);
		mx *= recipNorm;
		my *= recipNorm;
		mz *= recipNorm;   

        // Auxiliary variables to avoid repeated arithmetic
        q0q0 = q0 * q0;
        q0q1 = q0 * q1;
        q0q2 = q0 * q2;
        q0q3 = q0 * q3;
        q1q1 = q1 * q1;
        q1q2 = q1 * q2;
        q1q3 = q1 * q3;
        q2q2 = q2 * q2;
        q2q3 = q2 * q3;
        q3q3 = q3 * q3;   

        // Reference direction of Earth's magnetic field
        hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
        hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
        bx = sqrt(hx * hx + hy * hy);
        bz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));

		// Estimated direction of gravity and magnetic field
		halfvx = q1q3 - q0q2;
		halfvy = q0q1 + q2q3;
		halfvz = q0q0 - 0.5f + q3q3;
        halfwx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
        halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
        halfwz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);  
	
		// Error is sum of cross product between estimated direction and measured direction of field vectors
		halfex = (ay * halfvz - az * halfvy) + (my * halfwz - mz * halfwy);
		halfey = (az * halfvx - ax * halfvz) + (mz * halfwx - mx * halfwz);
		halfez = (ax * halfvy - ay * halfvx) + (mx * halfwy - my * halfwx);

		// Compute and apply integral feedback if enabled
		if(twoKi > 0.0f) {
			integralFBx += twoKi * halfex * (1.0f / sampleFreq);	// integral error scaled by Ki
			integralFBy += twoKi * halfey * (1.0f / sampleFreq);
			integralFBz += twoKi * halfez * (1.0f / sampleFreq);
			gx += integralFBx;	// apply integral feedback
			gy += integralFBy;
			gz += integralFBz;
		}
		else {
			integralFBx = 0.0f;	// prevent integral windup
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}

		// Apply proportional feedback
		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}
	
	// Integrate rate of change of quaternion
	gx *= (0.5f * (1.0f / sampleFreq));		// pre-multiply common factors
	gy *= (0.5f * (1.0f / sampleFreq));
	gz *= (0.5f * (1.0f / sampleFreq));
	qa = q0;
	qb = q1;
	qc = q2;
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx); 
	
	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}

//---------------------------------------------------------------------------------------------------
// IMU algorithm update

void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az) {
	float recipNorm;
	float halfvx, halfvy, halfvz;
	float halfex, halfey, halfez;
	float qa, qb, qc;

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;        

		// Estimated direction of gravity and vector perpendicular to magnetic flux
		halfvx = q1 * q3 - q0 * q2;
		halfvy = q0 * q1 + q2 * q3;
		halfvz = q0 * q0 - 0.5f + q3 * q3;
	
		// Error is sum of cross product between estimated and measured direction of gravity
		halfex = (ay * halfvz - az * halfvy);
		halfey = (az * halfvx - ax * halfvz);
		halfez = (ax * halfvy - ay * halfvx);

		// Compute and apply integral feedback if enabled
		if(twoKi > 0.0f) {
			integralFBx += twoKi * halfex * (1.0f / sampleFreq);	// integral error scaled by Ki
			integralFBy += twoKi * halfey * (1.0f / sampleFreq);
			integralFBz += twoKi * halfez * (1.0f / sampleFreq);
			gx += integralFBx;	// apply integral feedback
			gy += integralFBy;
			gz += integralFBz;
		}
		else {
			integralFBx = 0.0f;	// prevent integral windup
			integralFBy = 0.0f;
			integralFBz = 0.0f;
		}

		// Apply proportional feedback
		gx += twoKp * halfex;
		gy += twoKp * halfey;
		gz += twoKp * halfez;
	}
	
	// Integrate rate of change of quaternion
	gx *= (0.5f * (1.0f / sampleFreq));		// pre-multiply common factors
	gy *= (0.5f * (1.0f / sampleFreq));
	gz *= (0.5f * (1.0f / sampleFreq));
	qa = q0;
	qb = q1;
	qc = q2;
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx); 
	
	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
}

/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	
Description       :		
Input parameter   :   	Class			Name		Action
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
#define Kp 1.0f   // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.01f   // integral gain governs rate of convergence of gyroscope biases
void IMU_AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz) {
  double norm;
  double hx, hy, hz, bx, bz;
  double vx, vy, vz, wx, wy, wz;
  double ex, ey, ez;
  double tempq0,tempq1,tempq2,tempq3;

  // ÏÈ°ÑÕâÐ©ÓÃµÃµ½µÄÖµËãºÃ

  double q0q0 = q0*q0;
  double q0q1 = q0*q1;
  double q0q2 = q0*q2;
  double q0q3 = q0*q3;
  double q1q1 = q1*q1;
  double q1q2 = q1*q2;
  double q1q3 = q1*q3;
  double q2q2 = q2*q2;
  double q2q3 = q2*q3;
  double q3q3 = q3*q3;

  norm = invSqrt(ax*ax + ay*ay + az*az);       
  ax = ax * norm;
  ay = ay * norm;
  az = az * norm;
  //°Ñ¼Ó¼ÆµÄÈýÎ¬ÏòÁ¿×ª³Éµ¥Î»ÏòÁ¿¡£

  norm = invSqrt(mx*mx + my*my + mz*mz);          
  mx = mx * norm;
  my = my * norm;
  mz = mz * norm;
  /*
  ÕâÊÇ°ÑËÄÔªÊý»»Ëã³É¡¶·½ÏòÓàÏÒ¾ØÕó¡·ÖÐµÄµÚÈýÁÐµÄÈý¸öÔªËØ¡£
¸ù¾ÝÓàÏÒ¾ØÕóºÍÅ·À­½ÇµÄ¶¨Òå£¬µØÀí×ø±êÏµµÄÖØÁ¦ÏòÁ¿£¬×ªµ½»úÌå×ø±êÏµ£¬ÕýºÃÊÇÕâÈý¸öÔ ªËØ¡£
ËùÒÔÕâÀïµÄvx\y\z£¬ÆäÊµ¾ÍÊÇµ±Ç°µÄÅ·À­½Ç£¨¼´ËÄÔªÊý£©µÄ»úÌå×ø±ê²ÎÕÕÏµÉÏ£¬»»Ëã³öÀ´µÄÖØÁ¦µ¥Î»ÏòÁ¿¡£
  */
  // compute reference direction of flux
  hx = 2*mx*(0.5f - q2q2 - q3q3) + 2*my*(q1q2 - q0q3) + 2*mz*(q1q3 + q0q2);
  hy = 2*mx*(q1q2 + q0q3) + 2*my*(0.5f - q1q1 - q3q3) + 2*mz*(q2q3 - q0q1);
  hz = 2*mx*(q1q3 - q0q2) + 2*my*(q2q3 + q0q1) + 2*mz*(0.5f - q1q1 - q2q2);         
  bx = sqrt((hx*hx) + (hy*hy));
  bz = hz;     
  
  // estimated direction of gravity and flux (v and w)
  vx = 2*(q1q3 - q0q2);
  vy = 2*(q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3;
  wx = 2*bx*(0.5 - q2q2 - q3q3) + 2*bz*(q1q3 - q0q2);
  wy = 2*bx*(q1q2 - q0q3) + 2*bz*(q0q1 + q2q3);
  wz = 2*bx*(q0q2 + q1q3) + 2*bz*(0.5 - q1q1 - q2q2);  
  
  // error is sum of cross product between reference direction of fields and direction measured by sensors
  ex = (ay*vz - az*vy) + (my*wz - mz*wy);
  ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
  ez = (ax*vy - ay*vx) + (mx*wy - my*wx);

  /*
  axyzÊÇ»úÌå×ø±ê²ÎÕÕÏµÉÏ£¬¼ÓËÙ¶È¼Æ²â³öÀ´µÄÖØÁ¦ÏòÁ¿£¬Ò²¾ÍÊÇÊµ¼Ê²â³öÀ´µÄÖØÁ¦ÏòÁ¿¡£
axyzÊÇ²âÁ¿µÃµ½µÄÖØÁ¦ÏòÁ¿£¬vxyzÊÇÍÓÂÝ»ý·ÖºóµÄ×ËÌ¬À´ÍÆËã³öµÄÖØÁ¦ÏòÁ¿£¬ËüÃÇ¶¼ÊÇ»úÌå×ø±ê²ÎÕÕÏµÉÏµÄÖØÁ¦ÏòÁ¿¡£
ÄÇËüÃÇÖ®¼äµÄÎó²îÏòÁ¿£¬¾ÍÊÇÍÓÂÝ»ý·ÖºóµÄ×ËÌ¬ºÍ¼Ó¼Æ²â³öÀ´µÄ×ËÌ¬Ö®¼äµÄÎó²î¡£
ÏòÁ¿¼äµÄÎó²î£¬¿ÉÒÔÓÃÏòÁ¿²æ»ý£¨Ò²½ÐÏòÁ¿Íâ»ý¡¢²æ³Ë£©À´±íÊ¾£¬exyz¾ÍÊÇÁ½¸öÖØÁ¦ÏòÁ¿µÄ²æ»ý¡£
Õâ¸ö²æ»ýÏòÁ¿ÈÔ¾ÉÊÇÎ»ÓÚ»úÌå×ø±êÏµÉÏµÄ£¬¶øÍÓÂÝ»ý·ÖÎó²îÒ²ÊÇÔÚ»úÌå×ø±êÏµ£¬¶øÇÒ²æ»ýµÄ´óÐ¡ÓëÍÓÂÝ»ý·ÖÎó²î³ÉÕý±È£¬ÕýºÃÄÃÀ´¾ÀÕýÍÓÂÝ¡££¨Äã¿ÉÒÔ×Ô¼ºÄÃ¶«Î÷ÏëÏóÒ»ÏÂ£©ÓÉÓÚÍÓÂÝÊÇ¶Ô»úÌåÖ±½Ó»ý·Ö£¬ËùÒÔ¶ÔÍÓÂÝµÄ¾ÀÕýÁ¿»áÖ±½ÓÌåÏÖÔÚ¶Ô»úÌå×ø±êÏµµÄ¾ÀÕý¡£
  */
if(ex != 0.0f && ey != 0.0f && ez != 0.0f){
  exInt = exInt + ex * Ki * halfT;
  eyInt = eyInt + ey * Ki * halfT;	
  ezInt = ezInt + ez * Ki * halfT;

  // ÓÃ²æ»ýÎó²îÀ´×öPIÐÞÕýÍÓÂÝÁãÆ«
  gx = gx + Kp*ex + exInt;
  gy = gy + Kp*ey + eyInt;
  gz = gz + Kp*ez + ezInt;

  }

  // ËÄÔªÊýÎ¢·Ö·½³Ì
  tempq0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
  tempq1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
  tempq2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
  tempq3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;  
  // ËÄÔªÊý¹æ·¶»¯
  norm = invSqrt(tempq0*tempq0 + tempq1*tempq1 + tempq2*tempq2 + tempq3*tempq3);
  q0 = tempq0 * norm;
  q1 = tempq1 * norm;
  q2 = tempq2 * norm;
  q3 = tempq3 * norm;
}

/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	
Description       :		
Input parameter   :   	Class			Name		Action
Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2014.12.20
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void IMU_getQ(float * q) {

	int16_t accgyroval[6];
//	float magvalue[3];
	//¶ÁÈ¡¼ÓËÙ¶ÈºÍÍÓÂÝÒÇµÄµ±Ç°ADC
	MPU6050_getMotion6(accgyroval);
//	ADXRS620_GetYaw(&yawgyro);
//	HMC58X3_GetValues(magvalue); 	
	mygetqval[0] = accgyroval[0];
	mygetqval[1] = accgyroval[1];
	mygetqval[2] = accgyroval[2];
	mygetqval[3] = accgyroval[3]*( M_PI/180 )/32.8f;
	mygetqval[4] = accgyroval[4]*( M_PI/180 )/32.8f;
	mygetqval[5] = accgyroval[5]*( M_PI/180 )/32.8f;
	mygetqval[6] = 1;
	mygetqval[7] =0;
	mygetqval[8] = 0;
//	MahonyAHRSupdate(	mygetqval[3], mygetqval[4], mygetqval[5],
//						mygetqval[0], mygetqval[1], mygetqval[2],
//						mygetqval[6], mygetqval[7], mygetqval[8]);
//		MahonyAHRSupdateIMU(	mygetqval[3], mygetqval[4], mygetqval[5],
//						mygetqval[0], mygetqval[1], mygetqval[2]);
	MahonyAHRSupdateIMU(	mygetqval[3], mygetqval[4], mygetqval[5],
						mygetqval[0], mygetqval[1], mygetqval[2]);
	
//	IMU_AHRSupdate(	mygetqval[3], mygetqval[4], mygetqval[5],
//						mygetqval[0], mygetqval[1], mygetqval[2],
//						mygetqval[6], mygetqval[7], mygetqval[8]);
	q[0] = q0;
	q[1] = q1;
	q[2] = q2;
	q[3] = q3;
}

/*----------------------------------------------------------------------------*/
/*
Fuction Name      :	 	IMU_getYawPitchRoll
Description       :	   	
Input parameter   :   	Class			Name		Action

Output parameter  :   	Class			Name		Action						
Author&Date       :		Jones.Lee & 2015.4.28
Notes             :	
*/
/*----------------------------------------------------------------------------*/
void IMU_getYawPitchRoll(Angle_t *angle,Gyro_t *gyro,float period)
{
	float q[4];
	halfT = period/2;
	sampleFreq = 1/period;
	IMU_getQ(q);
	angle->Yaw = -atan2(2 * q[1] * q[2] + 2 * q[0] * q[3], -2 * q[2]*q[2] - 2 * q[3] * q[3] + 1)* 180/M_PI; // yaw
	angle->Rol = -asin(-2 * q[1] * q[3] + 2 * q[0] * q[2])* 180/M_PI;
	angle->Pit = atan2(2 * q[2] * q[3] + 2 * q[0] * q[1], -2 * q[1] * q[1] - 2 * q[2] * q[2] + 1)* 180/M_PI; // roll		
	gyro->Pit = mygetqval[3]* 180/M_PI;
	gyro->Rol = mygetqval[4]* 180/M_PI;
	gyro->Yaw = mygetqval[5]* 180/M_PI;

	if(angle->Yaw<0)
	{
		angle->Yaw +=360.0f;  //½« -+180¶È  ×ª³É0-360¶È
	}
}
void CalcIMUInfo(Angle_t *angle,Gyro_t *gyro,float dt)
{
	IMU_getYawPitchRoll(angle,gyro,dt);
}
