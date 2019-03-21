# -stm32-
用stm32制作简易电子琴
摘 要

基于32位的STM32F103的控制器，利用PWM产生的不同频率的音频信号驱动蜂鸣器发出声音，利用矩阵键盘通过按键，实现了简易电子琴的应用设计。该电子琴能实现从低音到高音的21个音阶，并能根据乐谱演奏完整的曲目。测试结果表明，PWM的输出信号与各音阶对应的声音频率基本一致，方案切实可行。这一方法也可用于电机控制、 简易音乐播放器等方面，具有较好的实用性。


关键词：STM32；PWM；矩阵键盘；蜂鸣器；定时器；音乐；
Simple electronic organ


Abstract

Abstract: Based on 32-bit STM32F103, using audio signals produced by PWM to drive a buzzer to play music, a Simple electronic organ is designed. The player can realize 21 scales from bass on treble and play complete songs according to music scores. Test results show that the output signals of PWM are consistent with the corresponding voice frequency of the scales, and the scheme is feasible. This method can also be used in motor control, music player and so on, showing good practicality.

Key Words: STM32; PWM; keyboard; buzzer; timer; music

单片机是大规模集成电路技术发展的产物，具有高性能、高速度、体积小、价格低廉、稳定可靠等特点。单片机渗透到我们生活的各个领域，几乎很难找到哪个领域没有单片机的踪迹。导弹的导航装置，飞机上各种仪表的控制，计算机的网络通讯与数据传输，工业自动化过程的实时控制和数据处理，广泛使用的各种智能IC卡，民用豪华轿车的安全保障系统，录像机、摄像机、全自动洗衣机的控制，以及程控玩具、电子宠物等等，这些都离不开单片机。更不用说自动控制领域的机器人、智能仪表、医疗器械以及各种智能机械了。因此，单片机的学习、开发与应用将造就一批计算机应用与智能化控制的科学家、工程师。

1.2 主要研究内容

在科研项目开发中，有时会遇到需要播放电话铃声、音乐等情况。简单的做法是购买专用音乐芯片，但该方法的缺点是播放的内容不可变，不能很好地满足项目需求。一般地，可采用普通51单片机实现音乐播放，其播放内容及歌曲数量都可以随时修改，使用上相对方便。随着STM32系列微处理器的出现，其基于ARM Cortex-M3内核的32位闪存微控制器，高达72MHz的主频，高集成度、实时性、数字信号处理、低功耗、低电压操作等众多特点，使得其应用越来越广泛。本文STM32基于处理器，根据乐曲简谱制作供程序识别的乐谱，并利用内部定时器产生PWM输出信号，驱动蜂鸣器完成自定义乐谱的播放。经测试，播放效果良好。


 
2 需求分析
2.1 设计任务
（1）设计一个简易电子琴，可以通过按键输入来控制输出不同的音符。
（2）演奏时可以通过按键自动演奏已存入的乐曲。
（3）能够自动演奏多首乐曲，且每首乐曲可重复演奏。
2.2音阶
音阶是音乐必不可少的要素，主要由声音的频率决定。通过给蜂鸣器不同频率的音频脉冲，可以产生不同的音阶， 而要产生某频率的音频脉冲，最简单的办法是算出该音频的周期，然后将此周期除以2即为半周期的时间。通过程序控制单片机某引脚半周期为高电平、半周期为低电平，不断交替变换，即可产生该频率的矩形波，接到蜂鸣器上就可发出该频率的声音。若想改变音阶，只需要改变半周期时间即可。表1为C调时音符频率对照表，据此可产生不同音阶的音符。“ ＃” 表示半音， 用于上升或下降半个音， 乘以2就提升该声音一个8度音阶，减半则降一个8度。








2.3 节拍
若要构成音乐，光有音阶是不够的，还需要节拍，也就是音符持续时间的长短，一般用拍数表示。至于1拍是多少秒，没有严格的规定，只要节拍适宜，声音悦耳即可。假如某首歌曲的节奏是每分钟120拍，那么1拍为0.5s，1/4拍为0.125ｓ，以此类推可得到其他节拍对应的时长。这样，利用不同的频率，加上与拍数对应的延时，就可以构成乐曲。

 
3 总体设计
3.1 工作原理
音阶的产生与声音频率有关，为了实现不同音阶，必须能为蜂鸣器提供不同频率的脉冲。为此，选择STM32芯片，利用其自带的定时器，通过PWM产生脉冲信号，STM32中总共有八个定时器，两个高级定时器TIM1和TIM8，时钟由APB2的输出产生。4个通用定时器TIM2~TIM5，两个基本定时器TIM6和TIM7，这六个定时器由时钟APB1的输出产生。基本定时器TIM6和TIM7只具备最基本的定时功能。通用定时器TIM2~TIM5就比基本定时器除了基本的定时外，它主要用在测量输入脉冲的频率、脉冲宽与输出PWM脉冲的场合，因此这里选用通用定时器TIM4。通过单片机引脚输出的PWM脉冲给蜂鸣器，不同频率可发出不同的音响。加上外接的矩阵键盘，可以通过按键来发出不同的音阶，还可以通过按键让蜂鸣器演奏事先存好的乐曲。

3.2 系统框图











	

图1 系统框图

3.3 硬件系统设计
整个硬件系统由STM32主控制器，外接矩阵键盘和蜂鸣器组成。
控制器使用STM32F103VET6，该控制器芯片使用的是ARM 公司为要求性能高、成本低、功耗低的嵌入式应用专门设计的32位的ARMCortex-M3内核。该系列单片机不仅功能强大而且功耗相当低。使用GPIOB6引脚输出PWM脉冲信号，与蜂鸣器的输入端相接。GPIOA端的0~7号引进分别与外接矩阵键盘的行线和列线连接起来。
 
由图2可知蜂鸣器是电平触发。











图2 蜂鸣器原理图

4×4矩阵键盘识别处理，每个按键有它的行值和列值，行值和列值的组合就是识别这个按键的编码。

图3 矩阵键盘原理图

3.4 定时时长的计算
定时器的一个主要功能就是到指定时间就会产生一个溢出事件，这个时间的设置与定时器时钟有关，在定时器时钟基础上进行预分频，设置计数溢出大小即可。
3.4.1 系统时钟设置 
	要保证定时的准确性，必须先确保系统时钟的设置是我们所预期的。定时器时钟分配如图1所示。通过编程使SYSCLK为72MHz，APB1预分频后得到PCLK1为36MHz，再经过TIM2~TIM7倍频器得到TIM2~ TIM7的时钟72MHz。时钟源多采用HSE（外部时钟源），对于STM32F103，其外部时钟为8MHz。
图1 定时器时钟分配图

3.4.2 定时器相关参数设置
    定时器的参数由结构体TimeBaseInitTypeDef定义，主要包括预分频系数、时钟分割、计数器模式、 计数溢出大小等。例如，要由TIM4产生一个时长为1s的定时，首先，应进行系统时钟的设置，得到TIM3CLCK72MHz，然后进行定时器设置。其中，预分频系数为35999，此时，TIM3时钟为72MHZ/36000=2KHz，无时钟分割。设置计数溢出大小为1999，即每次计2000个数就产生一个更新事件，输出频率为2KHz/2000=1Hz。
3.4.3 STM32的PWM输出
脉冲宽度调制(PWM)是利用微处理器的数字输出来对模拟电路进行控制的一种非常有效的技术，简而言之，就是实现对输出信号脉冲宽度的控制，一般用来控制步进电机等。STM32的定时器除了TIM6和TIM7之外，其他的定时器都可以用来产生PWM输出，其中，高级定时器TIM1和TIM8能够产生3对PWM互补输出，而TIM2~TIM5也能同时产生4路的PWM输出。STM32给不同的定时器分配了不同的输出引脚，考虑到引脚复用功能，STM32还提出了一个“重映射”的概念，就是通过设置某一些相关的寄存器，使得在其他非原始指定的引脚上也能输出PWM波形，但是这种重映像不是随意的， 使用方法可参考芯片手册。
占空比的计算。
占空比有如下含义：在一串理想的脉冲周期序列（如方波）中，正脉冲的持续时间与脉冲总周期的比值。 
占空比=(TIM_Pulse)/（TIM_Period+1） ×100%
当TIM_Period为1999时，若想得到占空比50%，则TIM_Pulse应设置为(1999+1)/2=1000。

3.5 程序设计
	主程序流程图：

















3.5.1 音阶设计
音阶的产生依赖于PWM输出信号的频率。为了简化设计，我们令定时器 的 TIM_Period为1999，且占空比始终为50%，根据公式算的TIM_Pulse为1000。此时，PWM输出信号频率仅与定时器预分频系数TIM_Prescaler有关，只需要调整该系数，即可得到所需信号频率。TIM_Prescaler由下式得到：
TIM_Prescaler=72MHz/(（TIM_Period+1）×f_sound )-1
式中，f_sound为音阶对应的频率，如低音Do频率为262Hz。要产生改音频，TIM_Prescaler应为136。通过函数buzzer_sound() 传入参数，计算需要的分频值，从而改变输入脉冲的频率。核心代码如下：
void buzzer_sound(unsigned freq)
{
	u16 val;  
    val = 36000 / freq - 1; 
	TIM4_Mode_Config(val);
	TIM_Cmd(TIM4, ENABLE);	
}
void TIM4_Mode_Config(u16 f)
{
TIM_TimeBaseStructure.TIM_Period = 1999;
TIM_TimeBaseStructure.TIM_Prescaler = f;	    //设置预分频,
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//配置为PWM模式1
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
TIM_OCInitStructure.TIM_Pulse = 1000;	//设置跳变值，当计数器计数到这个值时，电平发生跳变
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  //当定时器计数值小于CCR1_Val时为低电平
TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 //使能通道1
TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能预装载
TIM_ARRPreloadConfig(TIM4, ENABLE);		// 使能TIM4重载寄存器ARR
}

3.5.2 按键设计
将GPIOA的0~3号引脚初始化为推挽输出，4~7号引脚初始化为上拉输入。然后依次将0~3号引脚中的一个引脚置0，其他三个置1，分别读出GPIOA端口的值，判断是哪个按键按下，返回键值。
u16 Read_Key(void)
{
	u8 KeyValue = 0;
	if((GPIOA->IDR & 0xff)!= 0xf0){
		delay(0xfff);   //按键消抖
		if((GPIOA->IDR & 0xff)!= 0xf0){
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);	
			switch(GPIOA->IDR & 0xff)
			{
				case 0xee:KeyValue=1;break;
				case 0xde:KeyValue=5;break;
				case 0xbe:KeyValue=9;break;
				case 0x7e:KeyValue=13;break;
			}
		}		
	}
   return KeyValue;
}   

4 系统调试
    系统调试是整个系统功能否实现的关键步骤，我们将整个调试过程分为三大部分：硬件调试、软件调试和综合调试。

4.1 硬件调试
首先根据设计原理图，将开发板的PB.6引脚与蜂鸣器输入端相接，然后将PA.0~PA.6与矩阵键盘相接。首先写一个简单的程序，测试蜂鸣器是否能发出声音，进而测试连线是否正确。然后写一个矩阵键盘控制LED灯的程序，测试矩阵键盘是否实现功能。
测试过程中发现，矩阵键盘按键和设计的返回的键值不一样，经过检查发现是行线和列线与单片机接线顺序出错。改正后运行良好。

4.2 软件调试
    调试主要方法和技巧：通常一个调试程序应该具备至少四种性能：跟踪、断点、查看变量、更改数值。整个程序是一个主程序调用各个子程序实现功能的过程，要使主程序和整个程序都能平稳运行，各个模块的子程序的正确与平稳运行必不可少，所以在软件调试的最初阶段就是把各个子程序模块进行分别调试。

4.3 综合调试
将程序下载到开发板中，按下按键检查是否实现设计的功能。测试过程中发现的问题有：
   （1）多个按键发出的声音频率是一样的，有的按键按下没有声音。检查程序发现判断键值时候，GPIOA端口判断值写错。
   （2）按键按下，蜂鸣器声音不够清脆，有杂音。经指导老师提示，发现输出PWM方波的延时时间不够，增大延时时间后，声音变得清脆，没有杂音。
