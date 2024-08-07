	#include "encoder.h"
	#include "pid.h"
  #include "tjc_usart_hmi.h"
	uint16_t motor_Out_L;
	uint16_t motor_Out_R;
	Motor motor1;
	Motor motor2;	
	float test_Speed;
	extern uint16_t test;
  extern uint16_t ITjishu1;
	extern uint16_t ITjishu2;
	extern uint16_t ITjishu3;
	extern uint16_t ITjishu4;
extern float quanshu1;
extern float quanshu2;
extern float quanshu3;
extern float quanshu4;
extern int usarflag;
	extern float L_Target_Speed ;
	extern float R_Target_Speed ;
	extern float L_Target_Position ;
	extern float R_Target_Position ;
	extern float L_Now_Position ;
	extern float R_Now_Position ;	
	
	extern PID pid_l_speed;
	extern PID pid_l_position;
	extern PID pid_r_speed;
	extern PID pid_r_position;
	
//void Motor_Init(void)
//{
//    HAL_TIM_Encoder_Start(&ENCODER_TIM_L, TIM_CHANNEL_ALL);      //开启编码器定时器
//    __HAL_TIM_ENABLE_IT(&ENCODER_TIM_L,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理

//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //开启PWM
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //开启PWM
//    __HAL_TIM_SET_COUNTER(&ENCODER_TIM_L, 10000);                //编码器定时器初始值设定为10000
//    motor1.lastCount = 0;                                   //结构体内容初始化
//    motor1.totalCount = 0;
//    motor1.overflowNum = 0;                                  
//    motor1.speed = 0;
//    motor1.direct = 0;

//	  HAL_TIM_Encoder_Start(&ENCODER_TIM_R, TIM_CHANNEL_ALL);      //开启编码器定时器
//    __HAL_TIM_ENABLE_IT(&ENCODER_TIM_R,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理

//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_3);            //开启PWM
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_4);            //开启PWM
//    __HAL_TIM_SET_COUNTER(&ENCODER_TIM_R, 10000);                //编码器定时器初始值设定为10000
//    motor2.lastCount = 0;                                   //结构体内容初始化
//    motor2.totalCount = 0;
//    motor2.overflowNum = 0;                                  
//    motor2.speed = 0;
//    motor2.direct = 0;
//		
//	  HAL_TIM_Base_Start_IT(&GAP_TIM);                       //开启100ms定时器中断
//}

//#define SPEED_RECORD_NUM 20 // 经测试，50Hz个采样值进行滤波的效果比较好

//float speed_Record[SPEED_RECORD_NUM]={0};

///*
// * 进行速度的平均滤波
// * 输入新采样到的速度，存放速度的数组，
// * 返回滤波后的速度
// */
//float Speed_Low_Filter(float new_Spe,float *speed_Record)
//{
//    float sum = 0.0f;

//    test_Speed = new_Spe;
//    for(uint8_t i=SPEED_RECORD_NUM-1;i>0;i--)//将现有数据后移一位
//    {
//        speed_Record[i] = speed_Record[i-1];
//        sum += speed_Record[i-1];
//    }
//    speed_Record[0] = new_Spe;//第一位是新的数据
//    sum += new_Spe;
//    test_Speed = sum/SPEED_RECORD_NUM;
//    return sum/SPEED_RECORD_NUM;//返回均值
//}

////void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//定时器回调函数，用于计算速度和PID计算
////{	
////    if(htim->Instance==GAP_TIM.Instance)//间隔定时器中断，是时候计算速度了
////    {
////        /**********************************电机测速************************************/
////			if(test==1){
////					motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//如果向上计数（正转），返回值为0，否则返回值为1
////					motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值
////					
////					if(motor1.lastCount - motor1.totalCount > 19000) // 在计数值溢出时进行防溢出处理
////					{
////							motor1.overflowNum++;
////							motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值
////					}
////					else if(motor1.totalCount - motor1.lastCount > 19000) // 在计数值溢出时进行防溢出处理
////					{
////							motor1.overflowNum--;
////							motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值
////					}
////					
////					motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 3000;//算得每秒多少转,除以4是因为4倍频
////					motor1.speed = Speed_Low_Filter(motor1.speed,speed_Record);
////					motor1.lastCount = motor1.totalCount; //记录这一次的计数值

////					L_Now_Position = (float)(motor1.totalCount-10000);// 得到当前位置 10000编码器脉冲计数的初始值
////					L_Target_Speed = Location_PID_Realize(&pid_l_position,L_Target_Position,L_Now_Position);//位置环 Target_Posi

//					/***************************PID速度环**********************************/
//					motor_Out_L = Speed_PID_Realize(&pid_l_speed,L_Target_Speed,motor1.speed);
//					//Target_Speed是目标速度，自行定义就好
//					if((motor_Out_L > 0)||(motor_Out_L == 0))
//				{
////					__HAL_TIM_SetCompare(&MOTOR1_TIM, MOTOR1_CHANNEL_FORWARD, 1000);
//					__HAL_TIM_SetCompare(&MOTOR1_TIM, MOTOR1_CHANNEL_FORWARD, 1000-motor_Out_L);
//				}
//				else
//				{
////					__HAL_TIM_SetCompare(&MOTOR1_TIM, MOTOR1_CHANNEL_BACKWARD, 1000);
//					__HAL_TIM_SetCompare(&MOTOR1_TIM, MOTOR1_CHANNEL_FORWARD, 1000+motor_Out_L);
//				}
//					/**********************************************************************/
//			}else{
//					motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//如果向上计数（正转），返回值为0，否则返回值为1
//					motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//					
//					if(motor1.lastCount - motor1.totalCount > 19000) // 在计数值溢出时进行防溢出处理
//					{
//							motor1.overflowNum++;
//							motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//					}
//					else if(motor1.totalCount - motor1.lastCount > 19000) // 在计数值溢出时进行防溢出处理
//					{
//							motor1.overflowNum--;
//							motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//					}
//					
//					motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 3000;//算得每秒多少转,除以4是因为4倍频
//					motor1.speed = Speed_Low_Filter(motor1.speed,speed_Record);
//					motor1.lastCount = motor1.totalCount; //记录这一次的计数值

//					R_Now_Position = (float)(motor1.totalCount-10000);// 得到当前位置 10000编码器脉冲计数的初始值
//					R_Target_Speed = Location_PID_Realize(&pid_r_position,R_Target_Position,R_Now_Position);//位置环 Target_Posi

//					/***************************PID速度环**********************************/
//					motor_Out_R = Speed_PID_Realize(&pid_r_speed,R_Target_Speed,motor1.speed);
//					//Target_Speed是目标速度，自行定义就好
//					if((motor_Out_R > 0)||(motor_Out_R == 0))
//				{
////					__HAL_TIM_SetCompare(&MOTOR2_TIM, MOTOR2_CHANNEL_FORWARD, 1000);
//					__HAL_TIM_SetCompare(&MOTOR2_TIM, MOTOR2_CHANNEL_FORWARD, 1000-motor_Out_L);
//				}
//				else
//				{
////					__HAL_TIM_SetCompare(&MOTOR2_TIM, MOTOR2_CHANNEL_BACKWARD, 1000);
//					__HAL_TIM_SetCompare(&MOTOR2_TIM, MOTOR2_CHANNEL_FORWARD, 1000+motor_Out_L);
//				}			
//			}
//		}
//}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//定时器回调函数，用于计算速度和PID计算
{	
//    if(htim->Instance==GAP_TIM.Instance)//间隔定时器中断，是时候计算速度了
//    {
//        /**********************************电机测速************************************/
//        motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM_L);//如果向上计数（正转），返回值为0，否则返回值为1
//        motor1.totalCount = COUNTERNUM_L + motor1.overflowNum * RELOADVALUE_L;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//        
//        if(motor1.lastCount - motor1.totalCount > 19000) // 在计数值溢出时进行防溢出处理
//        {
//            motor1.overflowNum++;
//            motor1.totalCount = COUNTERNUM_L + motor1.overflowNum * RELOADVALUE_L;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//        }
//        else if(motor1.totalCount - motor1.lastCount > 19000) // 在计数值溢出时进行防溢出处理
//        {
//            motor1.overflowNum--;
//            motor1.totalCount = COUNTERNUM_L + motor1.overflowNum * RELOADVALUE_L;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//        }
//        
//        motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 3000;//算得每秒多少转,除以4是因为4倍频
//        motor1.speed = Speed_Low_Filter(motor1.speed,speed_Record);
//        motor1.lastCount = motor1.totalCount; //记录这一次的计数值

//        /**********************************电机测速************************************/
//        motor2.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM_R);//如果向上计数（正转），返回值为0，否则返回值为1
//        motor2.totalCount = COUNTERNUM_R + motor2.overflowNum * RELOADVALUE_R;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//        
//        if(motor2.lastCount - motor2.totalCount > 19000) // 在计数值溢出时进行防溢出处理
//        {
//            motor2.overflowNum++;
//            motor2.totalCount = COUNTERNUM_R + motor2.overflowNum * RELOADVALUE_R;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//        }
//        else if(motor2.totalCount - motor2.lastCount > 19000) // 在计数值溢出时进行防溢出处理
//        {
//            motor2.overflowNum--;
//            motor2.totalCount = COUNTERNUM_R + motor2.overflowNum * RELOADVALUE_R;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//        }
//        
//        motor2.speed = (float)(motor2.totalCount - motor2.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 3000;//算得每秒多少转,除以4是因为4倍频
//        motor2.speed = Speed_Low_Filter(motor2.speed,speed_Record);
//        motor2.lastCount = motor2.totalCount; //记录这一次的计数值
//        
//        /***************************PID速度环**********************************/
//        motor_Out_L = Speed_PID_Realize(&pid_l_speed,L_Target_Speed,motor1.speed);
//				
//        motor_Out_R = Speed_PID_Realize(&pid_r_speed,R_Target_Speed,motor2.speed);
//        //Target_Speed是目标速度，自行定义就好
//        if(motor_Out_L >= 0)
//    	{
//        __HAL_TIM_SetCompare(&MOTOR1_TIM, MOTOR1_CHANNEL_FORWARD, 1000);
//        __HAL_TIM_SetCompare(&MOTOR1_TIM, MOTOR1_CHANNEL_BACKWARD, 1000-motor_Out_L);
//    	}
//    	else
//    	{
//        __HAL_TIM_SetCompare(&MOTOR1_TIM, MOTOR1_CHANNEL_BACKWARD, 1000);
//        __HAL_TIM_SetCompare(&MOTOR1_TIM, MOTOR1_CHANNEL_FORWARD, 1000+motor_Out_L);
//    	}
//			
//        if(motor_Out_R >= 0)
//    	{
//        __HAL_TIM_SetCompare(&MOTOR2_TIM, MOTOR2_CHANNEL_FORWARD, 1000);
//        __HAL_TIM_SetCompare(&MOTOR2_TIM, MOTOR2_CHANNEL_BACKWARD, 1000-motor_Out_R);
//    	}
//    	else
//    	{
//        __HAL_TIM_SetCompare(&MOTOR2_TIM, MOTOR2_CHANNEL_BACKWARD, 1000);
//        __HAL_TIM_SetCompare(&MOTOR2_TIM, MOTOR2_CHANNEL_FORWARD, 1000+motor_Out_R);
//    	}
//		}
   if (htim == (&htim8))
    {
	   ITjishu1++;
			ITjishu2++;
			ITjishu3++;
			ITjishu4++;
		 if(ITjishu1>=3200*quanshu1)	//3200???=1? 3200 count->360
		{
		__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, 0);//?????0,??????
			ITjishu1=0;
		}
		
		if (ITjishu2>=3200*quanshu2){
			
		__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,0);
			ITjishu2=0;
		}
		if(ITjishu3>=3200*quanshu3){
		__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,0);
		  ITjishu3=0;
    }
		if(ITjishu4>=3200*quanshu4){
			__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,0);
			ITjishu4=0;
		}
		
}		

}
