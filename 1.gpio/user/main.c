#include "stm32f10x.h"
#include "led.h"

int main(void)
{
	GPIO_Config();
	while(1)
	{
		/*LED1(ON);
		delay(50000);
		LED1(OFF);
		delay(50000);*/
		
		/*LED1(ON);
		delay(50000);
		LED1(OFF);
		delay(50000);*/
		
		/*unsigned char a,i;
		a=0x01;
		for(i=0;i<8;i++)
		{
			LED2(a);
			a=a<<1;
			a=a|0x01;
			delay(50000);
		} */
		
		/*GPIOB->BSRR=0xff;
		delay(50000);
		GPIOB->BRR=0xff;
		delay(50000);*/	
		
		unsigned char a,i;
		a=0x01;
		for(i=0;i<8;i++)
		{
			GPIOB->ODR=a;
			a=a<<1;
			//a=a|0x01;
			delay(0x1fffff);

		}
	}
}
