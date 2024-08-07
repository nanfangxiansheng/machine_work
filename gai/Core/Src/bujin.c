#include "bujin.h"
void dianji_init(void)
	
{
	 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);//begin PWM out for servo
	 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);


}
void  dianji_kongzhi1(int fangxiang)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, fangxiang);
}
void  dianji_kongzhi2(int fangxiang)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, fangxiang);																											
}
void  dianji_kongzhi3(int fangxiang)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, fangxiang);
}
void  dianji_kongzhi4(int fangxiang)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, fangxiang);
}
