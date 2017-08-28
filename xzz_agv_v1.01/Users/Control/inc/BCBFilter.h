#ifndef _KALMAN_FILTER_H_
#define _KALMAN_FILTER_H_

void Kalman_Init(void);

void Kalman_Filter(float *pangle_m,float *pgyro_m,float dt);

#endif
