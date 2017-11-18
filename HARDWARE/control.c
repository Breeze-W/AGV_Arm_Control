

//�ļ�����control.c
//���ߣ�zqw
//���ܣ�ʵ�ֻ�е�ֵ��ſ��ͱ���,PB1,���������ƣ�PB2��������ʹ�ܿ��ƣ���ȷ�������ͣ��


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "kg.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "delay.h"
#include "stm32f10x_tim.h"
#include "timer.h"


extern u8 cmd_back[4];
extern u8 cmd_begin[4];
extern u8 cmd_zq_end[4];
extern u8 cmd_sk_end[4];
extern u8 flag;
extern u16 tx_counter;
extern u16 run_counter;   //��¼ѭ��������
extern u16 infrared_counter;
extern u16 conllision_counter;
extern u16 pfin0_counter;
//extern u8 key_flag;
//extern u8 tim3_ena;
u8 flag1=0,flag2=0;					//flag1,ץȡ��־��flag2,�ɿ���־��

void gpio_control_config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		      	//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
}



u8 flag_zq=0,flag_zq_end=0,flag_sk_end=0,flag_close=0,flag_collision=0;

extern u8 begin; //begin Ϊ��λ���Ŀ���ָ���־λ
extern u8 cmd_run[4];
u8 cmd_pre_back[4]={0xaa,0x21,0xbb,0xcc};
void motor_control()
{
	u8 i;
	//tim3_config(0);
	if(begin==1)
	{
		if(tx_counter==0)
		{
			for(i=0;i<4;i++)
			{
				USART_SendData(USART1,cmd_run[i]);			         //AA00bbcc														
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
			}
			tx_counter++;
		}
		//*****************����ӽ�������Ӧ***************************//
		if(PFin(5)==0 && PFin(0)==1 && flag_close==0 )
		{
					if(infrared_counter==0)
					{
							for(i=0;i<4;i++)
						{
							USART_SendData(USART1,cmd_pre_back[i]);																	
							while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
						}
						infrared_counter++;
					}
																									//����ǰ��
					tim3_config(0);
					delay_us(5);
					tim3_config(2000);
					PBout(1)=0;	
					delay_ms(100);
					//tim3_ena=1;
					TIM_Cmd(TIM2, ENABLE);
			}
		//******************����������Ӧ*****************************//
	if(PFin(11)==0 || PFin(12)==0)			//��ʼץȡ
	{
		if(flag_zq==0 && PFin(0)==1 && flag_collision==0)      //PF0
		{
			flag_close++;
			flag_zq++;
			run_counter++;
			flag1=1;
			flag2=0;
			tim3_config(0);
		  delay_us(5);
			tim3_config(1000);
			PBout(1)=0;			
			//����ǰ��
			//tim3_ena=1;
			delay_ms(1000);
			TIM_Cmd(TIM2, ENABLE);
			if(conllision_counter==0)
			{
					for(i=0;i<4;i++)
				{
					USART_SendData(USART1,cmd_begin[i]);								//aa01bcc									
					while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				}
				conllision_counter++;
			}

//		PBout(2)=1;							    	//������ʹ��

		}
	}
	else
	{
		flag_zq=0;      //ץȡ��־λ
	//	tim3_config(0);
	}
	
	if(PFin(0)==0)			        	//ץȡ���
	{
		if(flag_zq_end==0)
		{
			flag_zq_end++;
			flag_collision++;
			run_counter++;
			flag1=0;
			flag2=0;
			//PBout(2)=0;	//������ʧ��
			tim3_config(0);
			//tim3_ena=0;
			delay_us(10);
			//key_flag=0;
			tim2_reset();
				if(pfin0_counter==0)
			{
				for(i=0;i<4;i++)
				{
					USART_SendData(USART1,cmd_zq_end[i]);																	
					while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				}
				pfin0_counter++;
				
			}
			
		}
	}
	else
		flag_zq_end=0;
	
	if(flag==1 && PFin(1)==1 && flag_collision!=0)				//��е���ɿ�
	{
		flag=0;
		flag1=0;
		flag2=1;
	
		PBout(1)=1;
		tim3_config(1000);
			
		//tim3_ena=1;
	  TIM_Cmd(TIM2, ENABLE);
		for(i=0;i<4;i++)
		{
			USART_SendData(USART1,cmd_back[i]);																	
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
		}
		delay_ms(1000);
			//�������
    //tim3_config(0);
	}
	
	if(PFin(1)==0)	
	{
		if(flag_sk_end==0)
		{
			flag_sk_end++;
			flag1=0;
			flag2=0;
			
			if(run_counter!=0)
			{
				begin=0; 
				run_counter=0;
				tx_counter=0;				//ץȡ������Ч
				flag_close=0;
				flag_collision=0;
				conllision_counter=0;
				infrared_counter=0;
				pfin0_counter=0;
				for(i=0;i<4;i++)
				{
					USART_SendData(USART1,cmd_sk_end[i]);																	
					while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				}
				
		  }
			
			//			PBout(2)=0;      //������ʧ��
				tim3_config(0);
			//tim3_ena=0;
			  delay_us(10);
			//	key_flag=0;        //���ر�־��Ч
			  tim2_reset();
		}
	}
	else
		flag_sk_end=0;
	
/*	if(flag1==1)
	{
		if(PFin(4)==0)
		{
			tim3_config(2000);
		}
	}
	
	if(flag2==1)
	{
		if(PFin(6)==0)
		{
			tim3_config(2000);
		}
	}*/
	
	}
}


void kg_set()
{
	//begin=0;
	if(PEin(2)==0&&PFin(1)!=0)         		       	          //����
	{
		delay_ms(10);
		if(PEin(2)==0&&PFin(1)!=0)
		{
			//key_flag++;
			begin=0;
			
			run_counter=0;
			tx_counter=0;				//ץȡ������Ч
			flag_close=0;
			flag_collision=0;
			conllision_counter=0;
			infrared_counter=0;
			pfin0_counter=0;
			PBout(1)=1;
			tim3_config(0);
			delay_us(50);
			tim3_config(1000);
			//tim3_ena=1;
			TIM_Cmd(TIM2, ENABLE);
		}
		//delay_ms(20);
	}
	else if(PFin(1)==0)
		{
			tim3_config(0);
			delay_us(10);
			tim2_reset();
		}
		
	
	
	if(PEin(3)==0&&PFin(0)!=0)							                //ǰ�� 
	{
		delay_ms(10);
		if(PEin(3)==0&&PFin(0)!=0)
		{
			//key_flag++;
			begin=0;
			run_counter=0;
			tx_counter=0;				//ץȡ������Ч
			flag_close=0;
			flag_collision=0;
			conllision_counter=0;
			infrared_counter=0;
			pfin0_counter=0;
			PBout(1)=0;
		  tim3_config(0);
			delay_us(50);
			tim3_config(1000);		
		//tim3_ena=1;
			TIM_Cmd(TIM2, ENABLE);
		}
	
		
		//delay_ms(20);
	}
	
	else if(PFin(0)==0)
		{
			tim3_config(0);
			delay_us(10);
			tim2_reset();
		}
		

}


/*/����Ը�λ
void moter_init()
{
	delay_ms(10);
	if(PFin(1)!=0)
	{
			begin=1;
			PBout(1)=1;													//����
			tim3_config(1000);
			TIM_Cmd(TIM2, ENABLE);              //��ʱ����
	}
	//tim3_config(0);
}*/













