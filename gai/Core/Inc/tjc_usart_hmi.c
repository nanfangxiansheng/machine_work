/**
使用注意事项:
    1.将tjc_usart_hmi.c和tjc_usart_hmi.h 分别导入工程
    2.在需要使用的函数所在的头文件中添加 #include "tjc_usart_hmi.h"
    3.使用前请将 HAL_UART_Transmit_IT() 这个函数改为你的单片机的串口发送单字节函数
    3.TJCPrintf和printf用法一样

*/

#include "main.h"
//#include "stm32f1xx_hal.h"
//#include "stm32f1xx_hal_uart.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "tjc_usart_hmi.h"
#include <stddef.h>
#include <usart.h>
#include <time.h>
#include <tim.h>
#include <LobotServoController.h>
#include <bujin.h>
#include <servo.h>
#include <stdlib.h>
int usarflag;
uint16_t ITjishu1=0;
uint16_t ITjishu2=0;
uint16_t ITjishu3=0;
uint16_t ITjishu4=0;
int direction1;
int direction2;
int direction3;
int direction4;

float quanshu1=0;//bujin1
float quanshu2=0;//bujin2
float quanshu3=0;//bujin3
float quanshu4=0;//bujin4
extern float L_Target_Speed;
extern float R_Target_Speed;
#define STR_LENGTH 100
typedef struct
{
    uint16_t Head;
    uint16_t Tail;
    uint16_t Lenght;
    uint8_t  Ring_data[RINGBUFF_LEN];
}RingBuff_t;

RingBuff_t ringBuff;	//创建一个ringBuff的缓冲区
uint8_t RxBuff[1];



/********************************************************
函数名：  	TJCPrintf
作者：    	wwd
日期：    	2022.10.08
功能：    	向串口打印数据,使用前请将USART_SCREEN_write这个函数改为你的单片机的串口发送单字节函数
输入参数：		参考printf
返回值： 		打印到串口的数量
修改记录：
**********************************************************/

void TJCPrintf(const char *str, ...)
{


	uint8_t end = 0xff;
	char buffer[STR_LENGTH+1];  // 数据长度
	uint8_t i = 0;
	va_list arg_ptr;
	va_start(arg_ptr, str);
	vsnprintf(buffer, STR_LENGTH+1, str, arg_ptr);
	va_end(arg_ptr);
	while ((i < STR_LENGTH) && (i < strlen(buffer)))
	{
		HAL_UART_Transmit_IT(&huart1, (uint8_t *)(buffer) + i++, 1);
		while(huart1.gState != HAL_UART_STATE_READY);	//等待发送完毕
	}

	HAL_UART_Transmit_IT(&huart1, &end, 1);			//这个函数改为你的单片机的串口发送单字节函数
	while(huart1.gState != HAL_UART_STATE_READY);	//等待发送完毕
	HAL_UART_Transmit_IT(&huart1, &end, 1);			//这个函数改为你的单片机的串口发送单字节函数
	while(huart1.gState != HAL_UART_STATE_READY);	//等待发送完毕
	HAL_UART_Transmit_IT(&huart1, &end, 1);			//这个函数改为你的单片机的串口发送单字节函数
	while(huart1.gState != HAL_UART_STATE_READY);	//等待发送完毕

}
//this function is very important

void jiaozhun(){
//	  time_t currentTime;
//    struct tm *localTime;

//    // ??????
//    currentTime = time(NULL);

//    // ????????????
//    localTime = localtime(&currentTime);
	  TJCPrintf("rtc0=%d\xff\xff\xff",2004);
    TJCPrintf("rtc1=%02d\xff\xff\xff",04);
    TJCPrintf("rtc2=%02d\xff\xff\xff",15);
	  TJCPrintf("rtc3=%02d\xff\xff\xff",20);
    TJCPrintf("rtc4=%02d\xff\xff\xff",58);
    TJCPrintf("rtc5=%02d\xff\xff\xff",32);
	



}
uint16_t show(){
		TJCPrintf("zaizhi.n0.val=%d\xff\xff\xff",u(0));
		TJCPrintf("zaizhi.n1.val=%d\xff\xff\xff",u(1));
		TJCPrintf("zaizhi.n2.val=%d\xff\xff\xff",u(2));
	  TJCPrintf("zaizhi.n3.val=%d\xff\xff\xff",u(3));
	  TJCPrintf("zaizhi.n4.val=%d\xff\xff\xff",u(4));
	  TJCPrintf("zaizhi.n5.val=%d\xff\xff\xff",u(5));
	
	
}	
/********************************************************
函数名：  	HAL_UART_RxCpltCallback
作者：
日期：    	2022.10.08
功能：    	串口接收中断,将接收到的数据写入环形缓冲区
输入参数：
返回值： 		void
修改记录：
**********************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart->Instance == USART1)	// 判断是由哪个串口触发的中断
	{
		writeRingBuff(RxBuff[0]);
		HAL_UART_Receive_IT(&huart1,RxBuff,1);		// 重新使能串口2接收中断
		usarflag=1;
	}
}



/********************************************************
函数名：  	initRingBuff
作者：
日期：    	2022.10.08
功能：    	初始化环形缓冲区
输入参数：
返回值： 		void
修改记录：
**********************************************************/
void initRingBuff(void)
{
  //初始化相关信息
  ringBuff.Head = 0;
  ringBuff.Tail = 0;
  ringBuff.Lenght = 0;
}



/********************************************************
函数名：  	writeRingBuff
作者：
日期：    	2022.10.08
功能：    	往环形缓冲区写入数据
输入参数：
返回值： 		void
修改记录：
**********************************************************/
void writeRingBuff(uint8_t data)
{
  if(ringBuff.Lenght >= RINGBUFF_LEN) //判断缓冲区是否已满
  {
    return ;
  }
  ringBuff.Ring_data[ringBuff.Tail]=data;
  ringBuff.Tail = (ringBuff.Tail+1)%RINGBUFF_LEN;//防止越界非法访问
  ringBuff.Lenght++;

}




/********************************************************
函数名：  	deleteRingBuff
作者：
日期：    	2022.10.08
功能：    	删除串口缓冲区中相应长度的数据
输入参数：		要删除的长度
返回值： 		void
修改记录：
**********************************************************/
void deleteRingBuff(uint16_t size)
{
	if(size >= ringBuff.Lenght)
	{
	    initRingBuff();
	    return;
	}
	for(int i = 0; i < size; i++)
	{

		if(ringBuff.Lenght == 0)//判断非空
		{
		initRingBuff();
		return;
		}
		ringBuff.Head = (ringBuff.Head+1)%RINGBUFF_LEN;//防止越界非法访问
		ringBuff.Lenght--;

	}

}



/********************************************************
函数名：  	read1BFromRingBuff
作者：
日期：    	2022.10.08
功能：    	从串口缓冲区读取1字节数据
输入参数：		position:读取的位置
返回值： 		所在位置的数据(1字节)
修改记录：
**********************************************************/
uint8_t read1BFromRingBuff(uint16_t position)
{
	uint16_t realPosition = (ringBuff.Head + position) % RINGBUFF_LEN;

	return ringBuff.Ring_data[realPosition];
}




/********************************************************
函数名：  	getRingBuffLenght
作者：
日期：    	2022.10.08
功能：    	获取串口缓冲区的数据数量
输入参数：
返回值： 		串口缓冲区的数据数量
修改记录：
**********************************************************/
uint16_t getRingBuffLenght()
{
	return ringBuff.Lenght;
}


/********************************************************
函数名：  	isRingBuffOverflow
作者：
日期：    	2022.10.08
功能：    	判断环形缓冲区是否已满
输入参数：
返回值： 		1:环形缓冲区已满 , 2:环形缓冲区未满
修改记录：
**********************************************************/
uint8_t isRingBuffOverflow()
{
	return ringBuff.Lenght == RINGBUFF_LEN;
}

void judge(){
	while (usize>=6){
		if(u(0)!=0x11||u(3)!=0xff||u(4)!=0xff||u(5)!=0xff)
		  {
			  udelete(1);
		  }

		else
		  {
			  break;
		  }
	  }	
 //serial port and begin receiving
		if(u(0)==0x11&&u(3)==0xff&&u(4)==0xff&&u(5)==0xff){
			if(u(1)==0x01){//bottom wheels run forward
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
				udelete(6);
				show();
				
			
			
			}
			else if(u(1)==0x02){//bottom wheels run back
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,SET);
				udelete(6);
				show();
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

			else if (u(1)==0x03){//all run
				show();
				all();
				udelete(6);
				show();
			}

			else if(u(1)==0x0A){//conveyor belt forward rotation
				quanshu1=change(u(2))/10.0;
				ITjishu1=0;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,8);
				show();
				udelete(6);
				direction1=up;
				dianji_kongzhi1(direction1);
			
			}
			else if(u(1)==0x0B){//conveyor belt back rotation
				quanshu1=change(u(2))/10.0;
				ITjishu1=0;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,8);
				show();
				udelete(6);
				direction1=down;
				dianji_kongzhi1(direction1);
			}

			else if(u(1)==0x0E){//move claws forward
				quanshu3=change(u(2))/10.0;
				ITjishu3=0;
				quanshu2=change(u(2))/10.0;
				ITjishu2=0;
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,5);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,5);

				show();
				udelete(6);
				direction3=up;
				direction2=down;
				dianji_kongzhi3(direction3);
				dianji_kongzhi2(direction2);

			}
			else if(u(1)==0x0F){//move claws back
				quanshu3=change(u(2))/10.0;
				quanshu2=change(u(2))/10.0;
				ITjishu3=0;
				ITjishu2=0;
				direction3=down;
				direction2=up;
				dianji_kongzhi3(direction3);
				dianji_kongzhi2(direction2);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,5);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,5);
				show();
				udelete(6);

			}
			//bianma In3 ,IN4->left motor

			else if(u(1)==0x11){//left encoder motor forward totation
				HAL_GPIO_WritePin(bianma_IN3_GPIO_Port,bianma_IN3_Pin,1);
				HAL_GPIO_WritePin(bianma_IN4_GPIO_Port,bianma_IN4_Pin,0);

				HAL_Delay(200);
				HAL_GPIO_WritePin(bianma_IN3_GPIO_Port,bianma_IN3_Pin,0);
				HAL_GPIO_WritePin(bianma_IN4_GPIO_Port,bianma_IN4_Pin,0);
				
				show();
				udelete(6);
			
			}
			else if(u(1)==0x12){//left back rotation
				HAL_GPIO_WritePin(bianma_IN3_GPIO_Port,bianma_IN3_Pin,0);
				HAL_GPIO_WritePin(bianma_IN4_GPIO_Port,bianma_IN4_Pin,1);

				HAL_Delay(200);
				HAL_GPIO_WritePin(bianma_IN3_GPIO_Port,bianma_IN3_Pin,0);
				HAL_GPIO_WritePin(bianma_IN4_GPIO_Port,bianma_IN4_Pin,0);
				
				show();
				udelete(6);
			
			}
			else if(u(1)==0x13){//right forward
				HAL_GPIO_WritePin(bianmaIN1_GPIO_Port,bianmaIN1_Pin,1);
				HAL_GPIO_WritePin(bianma_IN2_GPIO_Port,bianma_IN2_Pin,0);

				HAL_Delay(200);
				HAL_GPIO_WritePin(bianmaIN1_GPIO_Port,bianmaIN1_Pin,0);
				HAL_GPIO_WritePin(bianma_IN2_GPIO_Port,bianma_IN2_Pin,0);
				show();
				udelete(6);
			}
			else if(u(1)==0x14){//right back
				HAL_GPIO_WritePin(bianmaIN1_GPIO_Port,bianmaIN1_Pin,0);
				HAL_GPIO_WritePin(bianma_IN2_GPIO_Port,bianma_IN2_Pin,1);

				HAL_Delay(200);
				HAL_GPIO_WritePin(bianmaIN1_GPIO_Port,bianmaIN1_Pin,0);
				HAL_GPIO_WritePin(bianma_IN2_GPIO_Port,bianma_IN2_Pin,0);
				show();
				udelete(6);
			}


			else if(u(1)==0x20){//show conveyor belt function
				show();
				quanshu1=8.5*1;//3 round
				ITjishu1=0;
				dianji_kongzhi1(up);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,5);	
				udelete(6);

				
			
			}
			else if(u(1)==0x21){//show recycling function
				show();
				quanshu1=85;
				ITjishu1=0;
				dianji_kongzhi1(up);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,5);

				udelete(6);
			
			
			}
			else if(u(1)==0x22){//clamp and move claw forward
				show();
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
				
				udelete(6);
				
			
			
			}
			else if(u(1)==0x23){//release and move claw back
				show();

				quanshu3=7.3;
				quanshu2=7.3;
				ITjishu3=0;
				ITjishu2=0;
				dianji_kongzhi3(down);
				dianji_kongzhi2(up);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,5);
				__HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,5);
				udelete(6);
			
			}
			else if(u(1)==0x24){//show encoder motor
				show();
				bianmayundong_right();
				HAL_Delay(2000);
				bianmayundong_right();
				HAL_Delay(2000);
				bianmayundong_right();

				




				udelete(6);
			}
			else if(u(1)==0x25){//conveyor belt turn one grid
				show();
				yunmiao();
				udelete(6);
			
			}
			else if(u(1)==0x26){//clamp close
				show();
				moveServo(7,580,1000);		
       	moveServo(5,560,1000);
				udelete(6);
			
			}
			else if(u(1)==0x27){//clamp open
				show();
				moveServo(7,470,1000);
			  moveServo(5,416,1000);
				udelete(6);
			
			}
				
}
}
int change(int hexnum){
	char hexString[10]; 
  sprintf(hexString, "%X", hexnum);
	long decimalNum = strtol(hexString, NULL, 16);
	return decimalNum;
}


