

//文件名	led.c
//作者		zhangqingwen 
//功能		程序开始运行后，led灯闪烁

#include "led.h"
#include "sys.h"
void led_gpio_configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 			//复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	PEout(5)=1;
}


