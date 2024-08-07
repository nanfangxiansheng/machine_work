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
//    HAL_TIM_Encoder_Start(&ENCODER_TIM_L, TIM_CHANNEL_ALL);      //������������ʱ��
//    __HAL_TIM_ENABLE_IT(&ENCODER_TIM_L,TIM_IT_UPDATE);           //������������ʱ�������ж�,���������

//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //����PWM
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //����PWM
//    __HAL_TIM_SET_COUNTER(&ENCODER_TIM_L, 10000);                //��������ʱ����ʼֵ�趨Ϊ10000
//    motor1.lastCount = 0;                                   //�ṹ�����ݳ�ʼ��
//    motor1.totalCount = 0;
//    motor1.overflowNum = 0;                                  
//    motor1.speed = 0;
//    motor1.direct = 0;

//	  HAL_TIM_Encoder_Start(&ENCODER_TIM_R, TIM_CHANNEL_ALL);      //������������ʱ��
//    __HAL_TIM_ENABLE_IT(&ENCODER_TIM_R,TIM_IT_UPDATE);           //������������ʱ�������ж�,���������

//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_3);            //����PWM
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_4);            //����PWM
//    __HAL_TIM_SET_COUNTER(&ENCODER_TIM_R, 10000);                //��������ʱ����ʼֵ�趨Ϊ10000
//    motor2.lastCount = 0;                                   //�ṹ�����ݳ�ʼ��
//    motor2.totalCount = 0;
//    motor2.overflowNum = 0;                                  
//    motor2.speed = 0;
//    motor2.direct = 0;
//		
//	  HAL_TIM_Base_Start_IT(&GAP_TIM);                       //����100ms��ʱ���ж�
//}

//#define SPEED_RECORD_NUM 20 // �����ԣ�50Hz������ֵ�����˲���Ч���ȽϺ�

//float speed_Record[SPEED_RECORD_NUM]={0};

///*
// * �����ٶȵ�ƽ���˲�
// * �����²��������ٶȣ�����ٶȵ����飬
// * �����˲�����ٶ�
// */
//float Speed_Low_Filter(float new_Spe,float *speed_Record)
//{
//    float sum = 0.0f;

//    test_Speed = new_Spe;
//    for(uint8_t i=SPEED_RECORD_NUM-1;i>0;i--)//���������ݺ���һλ
//    {
//        speed_Record[i] = speed_Record[i-1];
//        sum += speed_Record[i-1];
//    }
//    speed_Record[0] = new_Spe;//��һλ���µ�����
//    sum += new_Spe;
//    test_Speed = sum/SPEED_RECORD_NUM;
//    return sum/SPEED_RECORD_NUM;//���ؾ�ֵ
//}

////void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//��ʱ���ص����������ڼ����ٶȺ�PID����
////{	
////    if(htim->Instance==GAP_TIM.Instance)//�����ʱ���жϣ���ʱ������ٶ���
////    {
////        /**********************************�������************************************/
////			if(test==1){
////					motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
////					motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
////					
////					if(motor1.lastCount - motor1.totalCount > 19000) // �ڼ���ֵ���ʱ���з��������
////					{
////							motor1.overflowNum++;
////							motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
////					}
////					else if(motor1.totalCount - motor1.lastCount > 19000) // �ڼ���ֵ���ʱ���з��������
////					{
////							motor1.overflowNum--;
////							motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
////					}
////					
////					motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 3000;//���ÿ�����ת,����4����Ϊ4��Ƶ
////					motor1.speed = Speed_Low_Filter(motor1.speed,speed_Record);
////					motor1.lastCount = motor1.totalCount; //��¼��һ�εļ���ֵ

////					L_Now_Position = (float)(motor1.totalCount-10000);// �õ���ǰλ�� 10000��������������ĳ�ʼֵ
////					L_Target_Speed = Location_PID_Realize(&pid_l_position,L_Target_Position,L_Now_Position);//λ�û� Target_Posi

//					/***************************PID�ٶȻ�**********************************/
//					motor_Out_L = Speed_PID_Realize(&pid_l_speed,L_Target_Speed,motor1.speed);
//					//Target_Speed��Ŀ���ٶȣ����ж���ͺ�
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
//					motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
//					motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//					
//					if(motor1.lastCount - motor1.totalCount > 19000) // �ڼ���ֵ���ʱ���з��������
//					{
//							motor1.overflowNum++;
//							motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//					}
//					else if(motor1.totalCount - motor1.lastCount > 19000) // �ڼ���ֵ���ʱ���з��������
//					{
//							motor1.overflowNum--;
//							motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//					}
//					
//					motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 3000;//���ÿ�����ת,����4����Ϊ4��Ƶ
//					motor1.speed = Speed_Low_Filter(motor1.speed,speed_Record);
//					motor1.lastCount = motor1.totalCount; //��¼��һ�εļ���ֵ

//					R_Now_Position = (float)(motor1.totalCount-10000);// �õ���ǰλ�� 10000��������������ĳ�ʼֵ
//					R_Target_Speed = Location_PID_Realize(&pid_r_position,R_Target_Position,R_Now_Position);//λ�û� Target_Posi

//					/***************************PID�ٶȻ�**********************************/
//					motor_Out_R = Speed_PID_Realize(&pid_r_speed,R_Target_Speed,motor1.speed);
//					//Target_Speed��Ŀ���ٶȣ����ж���ͺ�
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//��ʱ���ص����������ڼ����ٶȺ�PID����
{	
//    if(htim->Instance==GAP_TIM.Instance)//�����ʱ���жϣ���ʱ������ٶ���
//    {
//        /**********************************�������************************************/
//        motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM_L);//������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
//        motor1.totalCount = COUNTERNUM_L + motor1.overflowNum * RELOADVALUE_L;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//        
//        if(motor1.lastCount - motor1.totalCount > 19000) // �ڼ���ֵ���ʱ���з��������
//        {
//            motor1.overflowNum++;
//            motor1.totalCount = COUNTERNUM_L + motor1.overflowNum * RELOADVALUE_L;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//        }
//        else if(motor1.totalCount - motor1.lastCount > 19000) // �ڼ���ֵ���ʱ���з��������
//        {
//            motor1.overflowNum--;
//            motor1.totalCount = COUNTERNUM_L + motor1.overflowNum * RELOADVALUE_L;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//        }
//        
//        motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 3000;//���ÿ�����ת,����4����Ϊ4��Ƶ
//        motor1.speed = Speed_Low_Filter(motor1.speed,speed_Record);
//        motor1.lastCount = motor1.totalCount; //��¼��һ�εļ���ֵ

//        /**********************************�������************************************/
//        motor2.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM_R);//������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
//        motor2.totalCount = COUNTERNUM_R + motor2.overflowNum * RELOADVALUE_R;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//        
//        if(motor2.lastCount - motor2.totalCount > 19000) // �ڼ���ֵ���ʱ���з��������
//        {
//            motor2.overflowNum++;
//            motor2.totalCount = COUNTERNUM_R + motor2.overflowNum * RELOADVALUE_R;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//        }
//        else if(motor2.totalCount - motor2.lastCount > 19000) // �ڼ���ֵ���ʱ���з��������
//        {
//            motor2.overflowNum--;
//            motor2.totalCount = COUNTERNUM_R + motor2.overflowNum * RELOADVALUE_R;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//        }
//        
//        motor2.speed = (float)(motor2.totalCount - motor2.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 3000;//���ÿ�����ת,����4����Ϊ4��Ƶ
//        motor2.speed = Speed_Low_Filter(motor2.speed,speed_Record);
//        motor2.lastCount = motor2.totalCount; //��¼��һ�εļ���ֵ
//        
//        /***************************PID�ٶȻ�**********************************/
//        motor_Out_L = Speed_PID_Realize(&pid_l_speed,L_Target_Speed,motor1.speed);
//				
//        motor_Out_R = Speed_PID_Realize(&pid_r_speed,R_Target_Speed,motor2.speed);
//        //Target_Speed��Ŀ���ٶȣ����ж���ͺ�
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
