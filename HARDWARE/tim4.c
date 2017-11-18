
//文件名：tim4.c
//作者：zqw
//功能：通过定时器的定时作用，来产生一路脉冲信号，来驱动步进电机

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "sys.h"


u8 data=1;
void gpio_pwm_config()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PAout(0)=data;
}

void tim4_config(u16 data)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = data;       								//当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	    								//设置预分频：不预分频，即为72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数模式
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );
	TIM_Cmd(TIM4, ENABLE); 
}

void nvic_tim4_config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//中断使能，重要！！！
	NVIC_Init(&NVIC_InitStructure);
}

void tim4_init()
{
	gpio_pwm_config();
	tim4_config(999);
	nvic_tim4_config();
}


void TIM4_IRQHandler()
{
if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		PAout(0)=~data;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}




