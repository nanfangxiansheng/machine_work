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
 * ���ܣ�PID�ṹ�������ʼ��
 * ���룺��
 * ���أ���
 * *******************************/

void PID_Init(void)//PID������ʼ��
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
//    pid_l_position.kp = KP_position;//�⼸���궨��Ҫ�Լ�����
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
 * ���ã��ٶȻ�PID����
 * ������PID�����ṹ���ַ��Ŀ��ֵ������ֵ
 * ����ֵ����
 * ****************************************/
float Speed_PID_Realize(PID* pid,float target,float feedback)//һ��PID����
{
    pid->err = target - feedback;
    if(pid->err < 0.4 && pid->err > -0.4) pid->err = 0;//pid����
    pid->integral += pid->err;
    
    if(pid->ki * pid->integral < -pid->maxIntegral) pid->integral = -pid->maxIntegral / pid->ki;//�����޷�
    else if(pid->ki * pid->integral > pid->maxIntegral) pid->integral = pid->maxIntegral / pid->ki;

    if(target == 0) pid->integral = 0; // ɲ��ʱ���i


    pid->output = (pid->kp * pid->err) + (pid->ki * pid->integral) + (pid->kd * (pid->err - pid->lastErr));//ȫ��ʽPID

    //����޷�
    if(target >= 0)//��תʱ
    {
        if(pid->output < 0) pid->output = 0;
        else if(pid->output > pid->maxOutput) pid->output = pid->maxOutput;
    }
    else if(target < 0)//��תʱ
    {
        if(pid->output < -pid->maxOutput) pid->output = -pid->maxOutput;
        else if(pid->output > 0) pid->output = 0;
    }

    pid->lastErr = pid->err;
    if(target == 0) pid->output = 0; // ɲ��ʱֱ�����0
    return pid->output;
}
