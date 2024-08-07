#include "key.h"


/*
 * 进行系统睡眠，PA0按键唤醒
 * 内核停止，片上外设也停止
 * 内核寄存器、内存的数据会丢失
 * PA0等于系统复位
 */
void SYS_SLEEP(void){
        /*清除 WU 状态位*/
        __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
        /* 使能 WKUP 引脚的唤醒功能 ，使能 PA0*/
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
        /* 进入待机模式 */
        HAL_PWR_EnterSTANDBYMode();
}

/*
 * 按键触发
 * 中断NVIC
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	if(GPIO_Pin==KEY0_Pin)//PC5--EXTI5
	{
		__HAL_GPIO_EXTI_CLEAR_FLAG(KEY0_Pin);//防止误触发
		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);		
		
        // 自定义应用程序
        SYS_SLEEP();
		
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);		
	}
}

