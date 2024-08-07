#ifndef _PID_H_
#define _PID_H_

#include "stm32f1xx.h"
#include "encoder.h"
#include <stdio.h>
//#include "control.h"

//PID����������ֵ
#define KP_speed 75
#define KI_speed 8
#define KD_speed 3

#define KP_position 2
#define KI_position 0
#define KD_position 0


	
typedef struct _PID//PID�����ṹ��
{
    float kp,ki,kd;
    float err,lastErr;
    float integral,maxIntegral; //����ֵ
    float output,maxOutput;
}PID;

void PID_Init(void);
float Speed_PID_Realize(PID* pid,float target,float feedback);//һ��PID����
float Location_PID_Realize(PID* pid,float target,float feedback);
#endif
