

//�ļ�����kg.c
//���ߣ�zqw
//���ܣ�ʵ�ֿ�ʼץȡ�Ŀ�������⣬ץȡ��ɺ�ж������г̿��ؼ��,PF11-PF14

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "sys.h"

void gpio_kg_config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure); 
	

//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource13);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource14);
}

void exti_kg_config()
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line11; 								//ʹ���ⲿ�ж�ͨ��4
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 	//�½����ж�
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 								//ʹ��ͨ��
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line12; 								//ʹ���ⲿ�ж�ͨ��4
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 	//�½����ж�
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 								//ʹ��ͨ��
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line13; 								//ʹ���ⲿ�ж�ͨ��4
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 	//�½����ж�
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 								//ʹ��ͨ��
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line14; 								//ʹ���ⲿ�ж�ͨ��4
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 	//�½����ж�
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 								//ʹ��ͨ��
	EXTI_Init(&EXTI_InitStructure);
}

void nvic_kg_config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							//�ж�ʹ�ܣ���Ҫ������
	NVIC_Init(&NVIC_InitStructure);
}


void kg_init()
{
	gpio_kg_config();
//	exti_kg_config();
//	nvic_kg_config();
}

void EXTI15_10_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line11)==SET)
	{
		
		
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	
	if(EXTI_GetITStatus(EXTI_Line12)==SET)
	{
		
		
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
	
	if(EXTI_GetITStatus(EXTI_Line13)==SET)
	{
		
		
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	
	if(EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		
		
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}


