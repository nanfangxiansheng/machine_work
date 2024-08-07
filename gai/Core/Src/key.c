#include "key.h"


/*
 * ����ϵͳ˯�ߣ�PA0��������
 * �ں�ֹͣ��Ƭ������Ҳֹͣ
 * �ں˼Ĵ������ڴ�����ݻᶪʧ
 * PA0����ϵͳ��λ
 */
void SYS_SLEEP(void){
        /*��� WU ״̬λ*/
        __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
        /* ʹ�� WKUP ���ŵĻ��ѹ��� ��ʹ�� PA0*/
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
        /* �������ģʽ */
        HAL_PWR_EnterSTANDBYMode();
}

/*
 * ��������
 * �ж�NVIC
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	if(GPIO_Pin==KEY0_Pin)//PC5--EXTI5
	{
		__HAL_GPIO_EXTI_CLEAR_FLAG(KEY0_Pin);//��ֹ�󴥷�
		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);		
		
        // �Զ���Ӧ�ó���
        SYS_SLEEP();
		
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);		
	}
}

