#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "stm32f1xx.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

//电机1的编码器输入引脚
#define MOTO1_ENCODER1_PORT GPIOA
#define MOTO1_ENCODER1_PIN  GPIO_PIN_0
#define MOTO1_ENCODER2_PORT GPIOA
#define MOTO1_ENCODER2_PIN  GPIO_PIN_1

#define MOTO1_ENCODER3_PORT GPIOA
#define MOTO1_ENCODER3_PIN  GPIO_PIN_6
#define MOTO1_ENCODER4_PORT GPIOA
#define MOTO1_ENCODER4_PIN  GPIO_PIN_7
//定时器号
#define ENCODER_TIM_L htim2
#define ENCODER_TIM_R htim3
#define PWM_TIM     htim4
#define GAP_TIM     htim5

#define MOTOR_SPEED_RERATIO 369u    //电机减速比
#define PULSE_PRE_ROUND 16 //一圈多少个脉冲
#define RADIUS_OF_TYRE 34 //轮胎半径，单位毫米
#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.14
#define RELOADVALUE_L __HAL_TIM_GetAutoreload(&ENCODER_TIM_L)    //获取自动装载值,本例中为20000
#define COUNTERNUM_L __HAL_TIM_GetCounter(&ENCODER_TIM_L)        //获取编码器定时器中的计数值
#define RELOADVALUE_R __HAL_TIM_GetAutoreload(&ENCODER_TIM_R)    //获取自动装载值,本例中为20000
#define COUNTERNUM_R __HAL_TIM_GetCounter(&ENCODER_TIM_R)        //获取编码器定时器中的计数值

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
    int32_t lastCount;   //上一次计数值
    int32_t totalCount;  //总计数值
    int16_t overflowNum; //溢出次数
    float speed;         //电机转速
    uint8_t direct;      //旋转方向
}Motor;

void Motor_Init(void);
float Speed_Low_Filter(float new_Spe,float *speed_Record);

	
#endif

