

//�ļ�����timer.h
//���ߣ�zqw
//���ܣ�

#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "sys.h"
#include "pwm.h"

void tim2_config(void);
void nvic_tim2_config(void);
void tim2_init(void);
void tim2_reset(void);


#endif

