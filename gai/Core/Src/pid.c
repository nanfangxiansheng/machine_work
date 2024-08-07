#include "pid.h"

	float L_Target_Speed ;
  float R_Target_Speed ;
  float L_Target_Position ;
  float R_Target_Position ;
	float L_Now_Position;
	float R_Now_Position;
		
	PID pid_l_speed;
  PID pid_l_position;
  PID pid_r_speed;
  PID pid_r_position;
/**********************************
 * 功能：PID结构体参数初始化
 * 输入：无
 * 返回：无
 * *******************************/

void PID_Init(void)//PID参数初始化
{
    pid_l_speed.err = 0;
    pid_l_speed.integral = 0;
    pid_l_speed.maxIntegral = 10000;
    pid_l_speed.maxOutput = __HAL_TIM_GetAutoreload(&PWM_TIM);
    pid_l_speed.lastErr = 0;
    pid_l_speed.output = 0;
    pid_l_speed.kp = KP_speed;
    pid_l_speed.ki = KI_speed;
    pid_l_speed.kd = KD_speed;

//    pid_l_position.err = 0;
//    pid_l_position.integral = 0;
//    pid_l_position.maxIntegral = 80;
//    pid_l_position.maxOutput = __HAL_TIM_GetAutoreload(&PWM_TIM);
//    pid_l_position.lastErr = 0;
//    pid_l_position.output = 0;
//    pid_l_position.kp = KP_position;//这几个宏定义要自己补充
//    pid_l_position.ki = KI_position;
//    pid_l_position.kd = KD_position;
	
    pid_r_speed.err = 0;
    pid_r_speed.integral = 0;
    pid_r_speed.maxIntegral = 10000;
    pid_r_speed.maxOutput = __HAL_TIM_GetAutoreload(&PWM_TIM);
    pid_r_speed.lastErr = 0;
    pid_r_speed.output = 0;
    pid_r_speed.kp = KP_speed;
    pid_r_speed.ki = KI_speed;
    pid_r_speed.kd = KD_speed;

//    pid_r_position.err = 0;
//    pid_r_position.integral = 0;
//    pid_r_position.maxIntegral = 80;
//    pid_r_position.maxOutput = __HAL_TIM_GetAutoreload(&PWM_TIM);
//    pid_r_position.lastErr = 0;
//    pid_r_position.output = 0;
//    pid_r_position.kp = KP_position;
//    pid_r_position.ki = KI_position;
//    pid_r_position.kd = KD_position;
}

/****************************************
 * 作用：速度环PID计算
 * 参数：PID参数结构体地址；目标值；反馈值
 * 返回值：无
 * ****************************************/
float Speed_PID_Realize(PID* pid,float target,float feedback)//一次PID计算
{
    pid->err = target - feedback;
    if(pid->err < 0.4 && pid->err > -0.4) pid->err = 0;//pid死区
    pid->integral += pid->err;
    
    if(pid->ki * pid->integral < -pid->maxIntegral) pid->integral = -pid->maxIntegral / pid->ki;//积分限幅
    else if(pid->ki * pid->integral > pid->maxIntegral) pid->integral = pid->maxIntegral / pid->ki;

    if(target == 0) pid->integral = 0; // 刹车时清空i


    pid->output = (pid->kp * pid->err) + (pid->ki * pid->integral) + (pid->kd * (pid->err - pid->lastErr));//全量式PID

    //输出限幅
    if(target >= 0)//正转时
    {
        if(pid->output < 0) pid->output = 0;
        else if(pid->output > pid->maxOutput) pid->output = pid->maxOutput;
    }
    else if(target < 0)//反转时
    {
        if(pid->output < -pid->maxOutput) pid->output = -pid->maxOutput;
        else if(pid->output > 0) pid->output = 0;
    }

    pid->lastErr = pid->err;
    if(target == 0) pid->output = 0; // 刹车时直接输出0
    return pid->output;
}
