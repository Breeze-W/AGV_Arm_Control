

//�ļ�����timer.c
//���ߣ�zqw
//���ܣ�ʵ�ֵ�����й����д��󱨾�

#include "timer.h"


void tim2_config()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 9999;       							//����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 71;	    								//����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );
	
	//TIM_Cmd(TIM2, ENABLE);
}

void nvic_tim2_config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//�ж�ʹ�ܣ���Ҫ������
	NVIC_Init(&NVIC_InitStructure);
}

void tim2_init()
{
	tim2_config();
	nvic_tim2_config();
}

u16 time=0;
u8 warning[4]={0xaa,0xff,0xbb,0xcc};                          //������Ϣ
void TIM2_IRQHandler()
{
	u8 i;
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		time++;
		if(time ==2000)
		{
			time=0;
			TIM_Cmd(TIM2, DISABLE);					//�ض�ʱ��
			
			if(PFin(0)==1 || PFin(1)==1)
			{
				tim3_config(0);
				for(i=0;i<4;i++)
				{
					USART_SendData(USART1,warning[i]);																	
					while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				}
			}
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void tim2_reset()
{
	time=0;
	TIM_Cmd(TIM2, DISABLE);
}

