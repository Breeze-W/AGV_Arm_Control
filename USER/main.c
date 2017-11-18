
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "kg.h"
#include "control.h"
#include "timer.h"

u8 cmd_run[4]={0xaa,0x00,0xbb,0xcc};     //上位机控制抓取运动指令
u8 cmd_back[4]={0xaa,0x11,0xbb,0xcc};    //上位机控制松开运动指令
u8 cmd_begin[4]={0xaa,0x01,0xbb,0xcc};   //下位机开始松开运动指令
u8 cmd_zq_end[4]={0xaa,0x02,0xbb,0xcc};  //下位机抓取结束运动指令
u8 cmd_sk_end[4]={0xaa,0x03,0xbb,0xcc};  //下位机松开结束运动指令

u16 run_counter=0;//运行全局变量，记录过程；
u16 tx_counter=0;
u16 conllision_counter=0;
u16 infrared_counter=0;
u16 pfin0_counter=0;
//u8  key_flag=0;//响应后，按键能控制电机
//u8  tim3_ena=0;

//u8 warning[4]={0xaa,0xff,0xbb,0xcc};     //下位机报错运动指令

int main()
{
	delay_init();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断分组配置	
	uart_init(115200);
	led_gpio_configuration();
	tim3_init();
	
	kg_init();
	tim2_init();
	gpio_control_config();
	
	tim3_config(0);
	//tim3_ena=0;
	//moter_init();
	
	while(1)
	{		
		kg_set();
		motor_control();
		
		/*/工作灯闪烁
		PBout(5)=0;
		delay_ms(50);
		PBout(5)=1;
		delay_ms(50);*/   
	}
}
//void gpio_kg_config()
/*{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
}*/
