#include <fengzhuang.h>
#include <yinyong.h>

extern float quanshu1;
extern float quanshu2;
extern float quanshu3;
extern float quanshu4;
extern uint16_t ITjishu1;
extern uint16_t ITjishu2;
extern uint16_t ITjishu3;
extern uint16_t ITjishu4;
extern int direction1;
extern int direction2;
extern int direction3;
extern int direction4;
void motor_init(){
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,40);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,40);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,40);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,40);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,40);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,40);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,RESET);

}


void yunmiao(){
	dianji_kongzhi1(up);//yunmiao->bujin1
	quanshu1=8.5;//one setp 
  __HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, 5);//?????0,??????
	ITjishu1=0;
}

void huishou(){
				quanshu1=85;
				ITjishu1=0;
				dianji_kongzhi1(up);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,5);
}


void bianmayundong(){
						HAL_GPIO_WritePin(bianmaIN1_GPIO_Port,bianmaIN1_Pin,1);
	HAL_GPIO_WritePin(bianma_IN2_GPIO_Port,bianma_IN2_Pin,0);
	HAL_GPIO_WritePin(bianma_IN4_GPIO_Port,bianma_IN4_Pin,0);	
	HAL_GPIO_WritePin(bianma_IN3_GPIO_Port,bianma_IN3_Pin,1);

				HAL_Delay(1000);
				moveServo(1,800,1000);//control clamp open and close
				moveServo(8,580,1000);
     	HAL_Delay(1000);

	
	
				moveServo(1,950,1000);
				moveServo(8,700,1000);
	HAL_Delay(1600);
									HAL_GPIO_WritePin(bianmaIN1_GPIO_Port,bianmaIN1_Pin,0);
	HAL_GPIO_WritePin(bianma_IN2_GPIO_Port,bianma_IN2_Pin,0);
	HAL_GPIO_WritePin(bianma_IN3_GPIO_Port,bianma_IN3_Pin,0);
	HAL_GPIO_WritePin(bianma_IN4_GPIO_Port,bianma_IN4_Pin,0);
	

}
void motor_rotate_forward(){
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,RESET);
				HAL_Delay(1000);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,RESET);


}
void clamp_and_move_claw_forward(){
			moveServo(7,580,1000);		
       	moveServo(5,560,1000);
				HAL_Delay(1000);
				quanshu3=7.3;
				quanshu2=7.3;
				ITjishu3=0;
				ITjishu2=0;
				dianji_kongzhi3(up);
				dianji_kongzhi2(down);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,5);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,5);
				HAL_Delay(2500);
				moveServo(7,470,1000);
			  moveServo(5,416,1000);
}
void release_and_move_claw_back(){

				
				quanshu3=7.3;
				quanshu2=7.3;
				ITjishu3=0;
				ITjishu2=0;
				dianji_kongzhi3(down);
				dianji_kongzhi2(up);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,5);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,5);


}
void motorstop(){
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,RESET);

}
void bianmayundong_right(){
	HAL_GPIO_WritePin(bianmaIN1_GPIO_Port,bianmaIN1_Pin,1);
	HAL_GPIO_WritePin(bianma_IN2_GPIO_Port,bianma_IN2_Pin,0);
	HAL_Delay(1000);
	moveServo(8,580,1000);
	HAL_Delay(1000);
	moveServo(8,700,1000);
	HAL_Delay(1600);
	HAL_GPIO_WritePin(bianmaIN1_GPIO_Port,bianmaIN1_Pin,0);
	HAL_GPIO_WritePin(bianma_IN2_GPIO_Port,bianma_IN2_Pin,0);



}
void all(){
	clamp_and_move_claw_forward();
	HAL_Delay(1500);
	bianmayundong();//for middle seed
	moveServo(3,740,1000);
	moveServo(4,655,1000);
	HAL_Delay(1500);
	bianmayundong();//for left seed
	moveServo(3,390,1000);
	moveServo(4,330,1000); 
	HAL_Delay(1500);
	bianmayundong();//for right seed
	moveServo(3,570,1000);//turn initial status
	moveServo(4,500,1000);
	yunmiao();
	HAL_Delay(2000);
	release_and_move_claw_back();
	HAL_Delay(3000);
	clamp_and_move_claw_forward();
	


	
	
	
	
	

}