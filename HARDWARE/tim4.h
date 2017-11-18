

//文件名：tim4.h
//作者：zqw
//功能：函数声明

#ifndef _TIM4_H
#define _TIM4_H

#include "sys.h"

void gpio_pwm_config(void);
void tim4_config(u16 data);
void nvic_tim4_config(void);
void tim4_init(void);



#endif 
