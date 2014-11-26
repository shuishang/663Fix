#include "Exti.h"

//初始化中断输入引脚.
//初始化As3911的中断引脚

void EXTIx_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;


  	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag

  	RCC_APB2PeriphClockCmd(AS3911_EXIT_CLK|RCC_APB2Periph_AFIO,ENABLE);

 // 初始化 AS3911_PORT_INTR-->GPIOn	  下拉输入
  	GPIO_InitStructure.GPIO_Pin  = AS3911_EXIT_PIN;
  	GPIO_InitStructure.GPIO_Mode = AS3911_EXIT_GPIO_MODE; 
  	GPIO_Init(AS3911_EXIT_GPIO, &GPIO_InitStructure);

  
 	GPIO_EXTILineConfig(AS3911_EXIT_GPIO_SOURCE,AS3911_EXIT_PIN_SOURCE);		//GPIOn	  中断线以及中断初始化配置

 	EXTI_InitStructure.EXTI_Line=AS3911_EXIT_LINE;				  //选择中断线
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 
  	NVIC_InitStructure.NVIC_IRQChannel = AS3911_EXIT_IRQ;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

}

//*****关闭中断*********************//
void EXITx_OFF(void)
{ 
	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	EXTI_InitStructure.EXTI_Line=AS3911_EXIT_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = AS3911_EXIT_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);
}

