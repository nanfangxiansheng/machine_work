#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "stm32f1xx.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

//���1�ı�������������
#define MOTO1_ENCODER1_PORT GPIOA
#define MOTO1_ENCODER1_PIN  GPIO_PIN_0
#define MOTO1_ENCODER2_PORT GPIOA
#define MOTO1_ENCODER2_PIN  GPIO_PIN_1

#define MOTO1_ENCODER3_PORT GPIOA
#define MOTO1_ENCODER3_PIN  GPIO_PIN_6
#define MOTO1_ENCODER4_PORT GPIOA
#define MOTO1_ENCODER4_PIN  GPIO_PIN_7
//��ʱ����
#define ENCODER_TIM_L htim2
#define ENCODER_TIM_R htim3
#define PWM_TIM     htim4
#define GAP_TIM     htim5

#define MOTOR_SPEED_RERATIO 369u    //������ٱ�
#define PULSE_PRE_ROUND 16 //һȦ���ٸ�����
#define RADIUS_OF_TYRE 34 //��̥�뾶����λ����
#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.14
#define RELOADVALUE_L __HAL_TIM_GetAutoreload(&ENCODER_TIM_L)    //��ȡ�Զ�װ��ֵ,������Ϊ20000
#define COUNTERNUM_L __HAL_TIM_GetCounter(&ENCODER_TIM_L)        //��ȡ��������ʱ���еļ���ֵ
#define RELOADVALUE_R __HAL_TIM_GetAutoreload(&ENCODER_TIM_R)    //��ȡ�Զ�װ��ֵ,������Ϊ20000
#define COUNTERNUM_R __HAL_TIM_GetCounter(&ENCODER_TIM_R)        //��ȡ��������ʱ���еļ���ֵ

#define MOTOR1_TIM htim4
#define MOTOR1_TIM htim4

#define MOTOR1_CHANNEL_FORWARD TIM_CHANNEL_1
#define MOTOR1_CHANNEL_BACKWARD TIM_CHANNEL_2

#define MOTOR2_TIM htim4
#define MOTOR2_TIM htim4

#define MOTOR2_CHANNEL_FORWARD TIM_CHANNEL_3
#define MOTOR2_CHANNEL_BACKWARD TIM_CHANNEL_4

typedef struct _Motor
{
    int32_t lastCount;   //��һ�μ���ֵ
    int32_t totalCount;  //�ܼ���ֵ
    int16_t overflowNum; //�������
    float speed;         //���ת��
    uint8_t direct;      //��ת����
}Motor;

void Motor_Init(void);
float Speed_Low_Filter(float new_Spe,float *speed_Record);

	
#endif

