#ifndef __EXTI_H
#define __EXIT_H	 

#include "stm32f10x_exti.h"
#include "stm32f10x.h"

//AS3911中断引脚						    
#define AS3911_EXIT_GPIO			GPIOB
#define AS3911_EXIT_CLK				RCC_APB2Periph_GPIOB
#define AS3911_EXIT_PIN				GPIO_Pin_0
#define AS3911_EXIT_GPIO_MODE   	GPIO_Mode_IPD
//#define AS3911_EXIT_GPIO_STATUS	(AS3911_EXIT_GPIO->IDR & AS3911_EXIT_PIN)
//#define AS3911_EXIT_GPIO_H		AS3911_EXIT_GPIO->ODR  |= AS3911_EXIT_PIN
//#define AS3911_EXIT_GPIO_L		AS3911_EXIT_GPIO->ODR  &= ~AS3911_EXIT_PIN
#define AS3911_EXIT_LINE			EXTI_Line0
#define AS3911_EXIT_GPIO_SOURCE		GPIO_PortSourceGPIOB
#define AS3911_EXIT_PIN_SOURCE		GPIO_PinSource0
#define AS3911_EXIT_IRQ				EXTI0_IRQn
#define AS3911_EXIT_IRQHandler		EXTI0_IRQHandler
	 
void EXTIx_Init(void);//IO初始化
void EXITx_OFF(void);//关闭中断
void EXITx_ON(void);//开启中断		 					    
#endif

