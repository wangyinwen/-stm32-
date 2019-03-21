#include "led.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //定义一个GPIO_InitTypeDef 结构体	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能外设时钟	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void LED(unsigned char a)
{
	if(a==1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	}
	else if(a==0)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
	}
}
void LED1(unsigned char a)
{
	if(a==1)
	{
		GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_SET);
	}
	else if(a==0)
	{
		GPIO_WriteBit(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
	}
	
}

void LED2(unsigned int portval)
{
	GPIO_Write(GPIOB,portval);
}

void delay(uint32_t n)
{
	while(n)
		n--;
}


