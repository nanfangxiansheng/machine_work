#ifndef __TJCUSARTHMI_H_
#define __TJCUSARTHMI_H_


#include <stdio.h>
#include <stm32f1xx_hal.h>
/**
	��ӡ����Ļ����
*/
void TJCPrintf(const char *cmd, ...);
void initRingBuff(void);
void writeRingBuff(uint8_t data);
void deleteRingBuff(uint16_t size);
uint16_t getRingBuffLenght(void);
uint8_t read1BFromRingBuff(uint16_t position);

uint16_t show();//show sent order
void jiaozhun(void);//calibrate the clock
#define RINGBUFF_LEN	(500)     //�����������ֽ��� 500

#define usize getRingBuffLenght()
#define code_c() initRingBuff()
#define udelete(x) deleteRingBuff(x)
#define u(x) read1BFromRingBuff(x)

void judge(void);
int change(int hexnum);
extern uint8_t RxBuff[1];
extern int usarflag;

#endif
