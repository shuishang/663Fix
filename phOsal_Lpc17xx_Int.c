/*
*         Copyright (c), NXP Semiconductors Bangalore / India
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* LPC17xx OSAL Component of Reader Library Framework.
* $Author: nxp62726 $
* $Revision: 286 $
* $Date: 2013-07-09 14:09:18 +0530 (Tue, 09 Jul 2013) $
*
* History:
*  PC: Generated 23. Aug 2012
*
*/
#include <ph_Status.h>

#ifdef NXPBUILD__PH_OSAL_STUB

#include "phOsal_Lpc17xx_Int.h"
#include <phOsal.h>

static phOsal_Stub_DataParams_t* pTimerOsal;
static u32 TIM1_counter=0;
static u32 TIM2_counter=0;
static u32 TIM3_counter=0;

/**
* \brief      TIMER IRQ Handlers
*/
void TIM1_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET ) /*检查TIM1更新中断发生与否*/
    {
	   TIM_ClearITPendingBit(TIM1,TIM_IT_Update);/* clear interrupt flag */
	   if(TIM1_counter>0)
	   {
	      TIM1_counter--;
	   }
	   if(TIM1_counter==0)
	   {
	      phOsal_Timer_ExecCallback(pTimerOsal, 1);	      
		  TIM1_counter=0;
	   }
	}
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET ) /*检查TIM2更新中断发生与否*/
    {
	   TIM_ClearITPendingBit(TIM2,TIM_IT_Update);/* clear interrupt flag */
	   if(TIM2_counter>0)
	   {
	      TIM2_counter--;
	   }
	   if(TIM2_counter==0)
	   {
	      phOsal_Timer_ExecCallback(pTimerOsal, 2);	      
		  TIM2_counter=0;
	   }	
	}
}

void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET ) /*检查TIM3更新中断发生与否*/
    {
	   TIM_ClearITPendingBit(TIM3,TIM_IT_Update);/* clear interrupt flag */
	   if(TIM3_counter>0)
	   {
	      TIM3_counter--;
	   }
	   if(TIM3_counter==0)
	   {
	      phOsal_Timer_ExecCallback(pTimerOsal, 3);	      
		  TIM3_counter=0;
	   }
	}
}

/*
 * Timers handling functions */
void phOsal_Lpc17xx_Int_Timer_Init(phOsal_Stub_DataParams_t *pDataParams)
{
    uint8_t count = 1;

    /* Initialize the timer structure */
    for (count = 1; count < LPC17XX_MAX_TIMERS; count++)
    {
        pDataParams->gTimers[count].dwTimerId   = count;
        pDataParams->gTimers[count].bTimerFree = TIMER_FREE;
    }

    /* Also keep the timers ready with all the default settings.
      This also does the job of registering the IRQ with NVIC */
    phOsal_Lpc17xx_Int_Init_Timer32(1, LPC17XX_DEFAULT_TIME_INTERVAL);
    phOsal_Lpc17xx_Int_Init_Timer32(2, LPC17XX_DEFAULT_TIME_INTERVAL);
    phOsal_Lpc17xx_Int_Init_Timer32(3, LPC17XX_DEFAULT_TIME_INTERVAL);

    pTimerOsal = pDataParams;
}

void phOsal_Lpc17xx_Int_Timer_Create(phOsal_Stub_DataParams_t *pDataParams,
        uint32_t *pTimerId)
{
    uint8_t count = 1;

    *pTimerId = -1;
    /* Look for a free timer that is available for use */
    for (count = 1; count < LPC17XX_MAX_TIMERS; count++)
    {
        if (pDataParams->gTimers[count].bTimerFree == TIMER_FREE)
        {
            /* Use this timer */
            pDataParams->gTimers[count].bTimerFree = TIMER_USED;
            pDataParams->gTimers[count].dwTimerId = count;
            *pTimerId = pDataParams->gTimers[count].dwTimerId;

            break;
        }
    }
}

phStatus_t phOsal_Lpc17xx_Int_Timer_Register(phOsal_Stub_DataParams_t  *pDataParams,
                                             uint32_t                      dwTimerId,
                                             uint32_t                      dwRegTimeCnt,
                                             uint16_t                      wOption,
                                             ppCallBck_t                   pApplicationCallback,
                                             void                         *pContext
                                             )
{
    if (dwTimerId > LPC17XX_MAX_TIMERS ||  pDataParams->gTimers[dwTimerId].bTimerFree == TIMER_FREE)
    {
        /* Can't use a non existent timer */
        /* Can't start a free timer, first create the timer */
        
        return PH_ERR_INTERNAL_ERROR;
    }

    /* Remember the call back function as well as argument to be passed */
    pDataParams->gTimers[dwTimerId].pContext = pContext;
    pDataParams->gTimers[dwTimerId].pApplicationCallback = pApplicationCallback;

    phOsal_Lpc17xx_Int_Init_Timer32(dwTimerId, dwRegTimeCnt);
    if (wOption == 1)
    {
        /* Load the delay value in Milli seconds */
        phOsal_Lpc17xx_Int_Load_TimerMs(dwTimerId, dwRegTimeCnt);
    }
    else if (wOption == 0)
    {
        /* Load the delay value in Micro seconds */
        phOsal_Lpc17xx_Int_Load_TimerUs(dwTimerId, dwRegTimeCnt);
    }
    else
    {
        return PH_ERR_INTERNAL_ERROR;
    }

    /* Start the timer */
    phOsal_Lpc17xx_Int_Enable_Timer32(dwTimerId);

    return PH_ERR_SUCCESS;
}

phStatus_t phOsal_Lpc17xx_Int_Timer_Stop(uint32_t dwTimerId)
{
    if (dwTimerId > LPC17XX_MAX_TIMERS)
    {
        return PH_ERR_INTERNAL_ERROR;
    }
    /* Stop the timer */
    phOsal_Lpc17xx_Int_Disable_Timer32(dwTimerId);

    return PH_ERR_SUCCESS;
}

phStatus_t phOsal_Lpc17xx_Int_Timer_Delete(phOsal_Stub_DataParams_t *pDataParams,uint32_t dwTimerId)
{
    if (dwTimerId > LPC17XX_MAX_TIMERS)
    {
        return PH_ERR_INTERNAL_ERROR;
    }
    /* Stop the timer and also mark the timer as available */
    phOsal_Lpc17xx_Int_Disable_Timer32(dwTimerId);

    pDataParams->gTimers[dwTimerId].dwTimerId = -1;
    pDataParams->gTimers[dwTimerId].bTimerFree = TIMER_FREE;
    pDataParams->gTimers[dwTimerId].pApplicationCallback = NULL;

    return PH_ERR_SUCCESS;
}

void phOsal_Lpc17xx_Int_Delay32Ms(uint32_t dwTimerId, uint32_t delayInMs)
{
    if ((dwTimerId == 1)|(dwTimerId == 2)|(dwTimerId == 3))
    {		   
	   delay_ms(delayInMs);
    }
    return;
}

void phOsal_Lpc17xx_Int_Delay32Us(uint32_t dwTimerId, uint32_t delayInUs)
{
	if ((dwTimerId == 1)|(dwTimerId == 2)|(dwTimerId == 3))
    {		   
	   delay_us(delayInUs);
    }
    return;
}

void phOsal_Lpc17xx_Int_Enable_Timer32(uint32_t dwTimerId)
{

    if ( dwTimerId == 1 )
    {
	    TIM_Cmd(TIM1,ENABLE);
    }
    else if  ( dwTimerId == 2 )
    {
	    TIM_Cmd(TIM2,ENABLE);
    }
    else
    {
	    TIM_Cmd(TIM3,ENABLE);
    }

    return;
}

void phOsal_Lpc17xx_Int_Disable_Timer32(uint32_t dwTimerId)
{
    if  ( dwTimerId == 1 )
    {
	    TIM_Cmd(TIM1,DISABLE);
    }
    else if  ( dwTimerId == 2 )
    {
	    TIM_Cmd(TIM2,DISABLE);
    }
    else
    {
	    TIM_Cmd(TIM3,DISABLE);
    }

    return;
}

void phOsal_Lpc17xx_Int_Reset_Timer32(uint32_t dwTimerId)
{
    if (dwTimerId == 1)
    {
        TIM_DeInit(TIM1);
    }
    else if (dwTimerId == 2)
    {
        TIM_DeInit(TIM2);
    }
    else if (dwTimerId == 3)
    {
        TIM_DeInit(TIM3);
    }

    return;
}

void phOsal_Lpc17xx_Int_Init_Timer32(uint32_t dwTimerId, uint32_t TimerInterval)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    if ( dwTimerId == 1 )
    {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
		/* Enable the TIMx global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//优先级别最高
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		 
		TIM_TimeBaseStructure.TIM_Period = 12-1;//1us---12001更稳定准确
	    TIM_TimeBaseStructure.TIM_Prescaler = (6-1);	 
	    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	   	
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
		//1mS中断一次---.TIM_Period =12000
    }
    else if ( dwTimerId == 2 )
    {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
		/* Enable the TIMx global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//优先级别最高
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
		NVIC_Init(&NVIC_InitStructure);
	 
		TIM_TimeBaseStructure.TIM_Period = 12-1;//1us---12001更稳定准确
	    TIM_TimeBaseStructure.TIM_Prescaler = (6-1);	 
	    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	   	
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		//1mS中断一次---.TIM_Period =12000
    }
    else if ( dwTimerId == 3 )
    {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
		/* Enable the TIMx global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//优先级别最高
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
		NVIC_Init(&NVIC_InitStructure);
	
		TIM_TimeBaseStructure.TIM_Period = 12-1;//1us---12001更稳定准确
	    TIM_TimeBaseStructure.TIM_Prescaler = (6-1);	 
	    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	   	
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
		//1mS中断一次---.TIM_Period =12000
    }

    return;
}

void phOsal_Lpc17xx_Int_Load_TimerMs(uint32_t dwTimerId, uint32_t dwTimerInterval)
{
    /* Load the given timer interval onto match register 0 */
    if (dwTimerId == 1)
    {
        TIM1_counter= dwTimerInterval*1000;
    }
    else if (dwTimerId == 2)
    {
        TIM2_counter= dwTimerInterval*1000;
    }
    else if (dwTimerId == 3)
    {
        TIM3_counter= dwTimerInterval*1000;
    }

    return;
}

void phOsal_Lpc17xx_Int_Load_TimerUs(uint32_t dwTimerId, uint32_t dwTimerInterval)
{
    /* Load the given timer interval onto match register 0 */
    if (dwTimerId == 1)
    {
        TIM1_counter= dwTimerInterval;
    }
    else if (dwTimerId == 2)
    {
        TIM2_counter= dwTimerInterval;
    }
    else if (dwTimerId == 3)
    {
        TIM3_counter= dwTimerInterval;
    }

    return;
}

#endif /* NXPBUILD__PH_OSAL_STUB */
