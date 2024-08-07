#ifndef BUJIN_H 
#define BUJIN_H
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "yinyong.h"
extern int AutoReload_data;	
extern int MaiChong;	
#define up 1
#define down 0
extern uint16_t ITjishu;
void dianji_init(void);
void dianji_kongzhi1(int fangxiang);		
void dianji_kongzhi2(int fangxiang);		
void dianji_kongzhi3(int fangxiang);		
void dianji_kongzhi4(int fangxiang);
#endif
