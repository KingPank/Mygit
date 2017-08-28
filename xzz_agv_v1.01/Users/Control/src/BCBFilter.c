#include "BCBFilter.h"
#include "BCBGlobalFunc.h"

static float angle_dot_kalman = 0;
static	float angle_kalman;
//-------------------------------------------------------
static float Q_angle=0.001, Q_gyro=0.003, R_angle=0.5 ;
//注意：dt的取值为kalman滤波器采样时间;
static float P[2][2] = {
    { 1, 0 },
    { 0, 1 }
};

static float Pdot[4] = {0,0,0,0};

static const char C_0 = 1;

static float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
//------------------------------------------------------

void Kalman_Init(void)
{
    q_bias = 0;
    angle_err = 0;
    PCt_0 = 0;
    PCt_1 = 0;
    E = 0;
    K_0 = 0;
    K_1 = 0;
    t_0 = 0;
    t_1 = 0;

}
void Kalman_Filter(float *pangle_m,float *pgyro_m,float dt)			//gyro_m:gyro_measure
{
	float angle_m,gyro_m;

	angle_m  = *pangle_m;
	gyro_m = *pgyro_m;
	
	
    angle_kalman +=(gyro_m-q_bias) * dt;

    Pdot[0]=Q_angle - P[0][1] - P[1][0];
    Pdot[1] = -P[1][1];
    Pdot[2] = -P[1][1];
    Pdot[3]= Q_gyro;

    P[0][0] += Pdot[0] * dt;
    P[0][1] += Pdot[1] * dt;
    P[1][0] += Pdot[2] * dt;
    P[1][1] += Pdot[3] * dt;


    angle_err = angle_m - angle_kalman;


    PCt_0 = C_0 * P[0][0];
    PCt_1 = C_0 * P[1][0];

    E = R_angle + C_0 * PCt_0;

    K_0 = PCt_0 / E; 
    K_1 = PCt_1 / E;

    t_0 = PCt_0;
    t_1 = C_0 * P[0][1];

    P[0][0] -= K_0 * t_0;
    P[0][1] -= K_0 * t_1;
    P[1][0] -= K_1 * t_0;
    P[1][1] -= K_1 * t_1;


    angle_kalman	+= K_0 * angle_err;
    q_bias	+= K_1 * angle_err;
    angle_dot_kalman = gyro_m-q_bias;
	
    *pangle_m =angle_kalman;
    *pgyro_m = angle_dot_kalman;
}
