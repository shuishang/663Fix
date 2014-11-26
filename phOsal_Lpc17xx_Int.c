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

/**
* \brief      TIMER IRQ Handlers
*/
void TIMER0_IRQHandler(void)
{
    if ( LPC_TMR32B0->IR & (0x01) )
    {
        LPC_TMR32B0->IR = 0x1;         /* clear interrupt flag */
    }
    /* This is the only timer we are going to use for call backs  */
    phOsal_Timer_ExecCallback(pTimerOsal, 0);

    return;
}

void TIMER1_IRQHandler(void)
{
    if ( LPC_TMR32B1->IR & (0x01) )
    {
        LPC_TMR32B1->IR = 0x1;         /* clear interrupt flag */
    }
    phOsal_Timer_ExecCallback(pTimerOsal, 1);

    return;
}

void TIMER2_IRQHandler(void)
{
    if ( LPC_TMR32B2->IR & (0x01) )
    {
        LPC_TMR32B2->IR = 0x1;         /* clear interrupt flag */
    }
    phOsal_Timer_ExecCallback(pTimerOsal, 2);

    return;
}


/*
 * Timers handling functions */
void phOsal_Lpc17xx_Int_Timer_Init(phOsal_Stub_DataParams_t *pDataParams)
{
    uint8_t count = 0;

    /* Initialize the timer structure */
    for (count = 0; count < LPC17XX_MAX_TIMERS; count++)
    {
        pDataParams->gTimers[count].dwTimerId   = count;
        pDataParams->gTimers[count].bTimerFree = TIMER_FREE;
    }

    /* Also keep the timers ready with all the default settings.
      This also does the job of registering the IRQ with NVIC */
    phOsal_Lpc17xx_Int_Init_Timer32(0, LPC17XX_DEFAULT_TIME_INTERVAL);
    phOsal_Lpc17xx_Int_Init_Timer32(1, LPC17XX_DEFAULT_TIME_INTERVAL);
    phOsal_Lpc17xx_Int_Init_Timer32(2, LPC17XX_DEFAULT_TIME_INTERVAL);
    phOsal_Lpc17xx_Int_Init_Timer32(3, LPC17XX_DEFAULT_TIME_INTERVAL);

    pTimerOsal = pDataParams;
}

void phOsal_Lpc17xx_Int_Timer_Create(phOsal_Stub_DataParams_t *pDataParams,
        uint32_t *pTimerId)
{
    uint8_t count = 0;

    *pTimerId = -1;
    /* Look for a free timer that is available for use */
    for (count = 0; count < LPC17XX_MAX_TIMERS; count++)
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
    if (dwTimerId == 0)
    {
        /* setup timer #0 for delay */
        LPC_TMR32B0->TCR = 0x02;        /* reset timer */
        LPC_TMR32B0->PR  = 0x00;        /* set prescaler to zero */
        LPC_TMR32B0->MR0 = delayInMs * ((SystemCoreClock) / 1000);
        LPC_TMR32B0->IR  = 0xff;        /* reset all interrrupts */
        LPC_TMR32B0->MCR = 0x04;        /* stop timer on match */
        LPC_TMR32B0->TCR = 0x01;        /* start timer */

        /* wait until delay time has elapsed */
        while (LPC_TMR32B0->TCR & 0x01);
    }
    else if (dwTimerId == 1)
    {
        /* setup timer #1 for delay */
        LPC_TMR32B1->TCR = 0x02;        /* reset timer */
        LPC_TMR32B1->PR  = 0x00;        /* set prescaler to zero */
        LPC_TMR32B1->MR0 = delayInMs * ((SystemCoreClock) / 1000);
        LPC_TMR32B1->IR  = 0xff;        /* reset all interrrupts */
        LPC_TMR32B1->MCR = 0x04;        /* stop timer on match */
        LPC_TMR32B1->TCR = 0x01;        /* start timer */

        /* wait until delay time has elapsed */
        while (LPC_TMR32B1->TCR & 0x01);
    }
    else if (dwTimerId == 2)
    {
        /* setup timer #1 for delay */
        LPC_TMR32B2->TCR = 0x02;        /* reset timer */
        LPC_TMR32B2->PR  = 0x00;        /* set prescaler to zero */
        LPC_TMR32B2->MR0 = delayInMs * ((SystemCoreClock) / 1000);
        LPC_TMR32B2->IR  = 0xff;        /* reset all interrrupts */
        LPC_TMR32B2->MCR = 0x04;        /* stop timer on match */
        LPC_TMR32B2->TCR = 0x01;        /* start timer */

        /* wait until delay time has elapsed */
        while (LPC_TMR32B2->TCR & 0x01);
    }
    else if (dwTimerId == 3)
    {
        /* setup timer #1 for delay */
        LPC_TMR32B3->TCR = 0x02;        /* reset timer */
        LPC_TMR32B3->PR  = 0x00;        /* set prescaler to zero */
        LPC_TMR32B3->MR0 = delayInMs * ((SystemCoreClock) / 1000);
        LPC_TMR32B3->IR  = 0xff;        /* reset all interrrupts */
        LPC_TMR32B3->MCR = 0x04;        /* stop timer on match */
        LPC_TMR32B3->TCR = 0x01;        /* start timer */

        /* wait until delay time has elapsed */
        while (LPC_TMR32B3->TCR & 0x01);
    }

    return;
}

void phOsal_Lpc17xx_Int_Delay32Us(uint32_t dwTimerId, uint32_t delayInUs)
{
    if (dwTimerId == 0)
    {
        /* setup timer #0 for delay */
        LPC_TMR32B0->TCR = 0x02;        /* reset timer */
        LPC_TMR32B0->PR  = 0x00;        /* set prescaler to zero */
        LPC_TMR32B0->MR0 = delayInUs * ((SystemCoreClock)/1000000);
        LPC_TMR32B0->IR  = 0xff;        /* reset all interrrupts */
        LPC_TMR32B0->MCR = 0x04;        /* stop timer on match */
        LPC_TMR32B0->TCR = 0x01;        /* start timer */

        /* wait until delay time has elapsed */
        while (LPC_TMR32B0->TCR & 0x01);
    }
    else if (dwTimerId == 1)
    {
        /* setup timer #1 for delay */
        LPC_TMR32B1->TCR = 0x02;        /* reset timer */
        LPC_TMR32B1->PR  = 0x00;        /* set prescaler to zero */
        LPC_TMR32B1->MR0 = delayInUs * ((SystemCoreClock)/1000000);
        LPC_TMR32B1->IR  = 0xff;        /* reset all interrrupts */
        LPC_TMR32B1->MCR = 0x04;        /* stop timer on match */
        LPC_TMR32B1->TCR = 0x01;        /* start timer */

        /* wait until delay time has elapsed */    
        while (LPC_TMR32B1->TCR & 0x01);
    }
    else if (dwTimerId == 2)
    {
        /* setup timer #1 for delay */
        LPC_TMR32B2->TCR = 0x02;        /* reset timer */
        LPC_TMR32B2->PR  = 0x00;        /* set prescaler to zero */
        LPC_TMR32B2->MR0 = delayInUs * ((SystemCoreClock)/1000000);
        LPC_TMR32B2->IR  = 0xff;        /* reset all interrrupts */
        LPC_TMR32B2->MCR = 0x04;        /* stop timer on match */
        LPC_TMR32B2->TCR = 0x01;        /* start timer */

        /* wait until delay time has elapsed */
        while (LPC_TMR32B2->TCR & 0x01);
    }
    else if (dwTimerId == 3)
    {
        /* setup timer #1 for delay */
        LPC_TMR32B3->TCR = 0x02;        /* reset timer */
        LPC_TMR32B3->PR  = 0x00;        /* set prescaler to zero */
        LPC_TMR32B3->MR0 = delayInUs * ((SystemCoreClock)/1000000);
        LPC_TMR32B3->IR  = 0xff;        /* reset all interrrupts */
        LPC_TMR32B3->MCR = 0x04;        /* stop timer on match */
        LPC_TMR32B3->TCR = 0x01;        /* start timer */

        /* wait until delay time has elapsed */
        while (LPC_TMR32B3->TCR & 0x01);
    }

    return;
}

void phOsal_Lpc17xx_Int_Enable_Timer32(uint32_t dwTimerId)
{
    if ( dwTimerId == 0 )
    {
        LPC_TMR32B0->TCR = 1;
    }
    else if ( dwTimerId == 1 )
    {
        LPC_TMR32B1->TCR = 1;
    }
    else if  ( dwTimerId == 2 )
    {
        LPC_TMR32B2->TCR = 1;
    }
    else
    {
        LPC_TMR32B3->TCR = 1;
    }

    return;
}

void phOsal_Lpc17xx_Int_Disable_Timer32(uint32_t dwTimerId)
{
    if ( dwTimerId == 0 )
    {
        LPC_TMR32B0->TCR = 0;
    }
    else if  ( dwTimerId == 1 )
    {
        LPC_TMR32B1->TCR = 0;
    }
    else if  ( dwTimerId == 2 )
    {
        LPC_TMR32B2->TCR = 0;
    }
    else
    {
        LPC_TMR32B3->TCR = 0;
    }

    return;
}

void phOsal_Lpc17xx_Int_Reset_Timer32(uint32_t dwTimerId)
{
    uint32_t regVal;

    if ( dwTimerId == 0 )
    {
        regVal = LPC_TMR32B0->TCR;
        regVal |= 0x02;
        LPC_TMR32B0->TCR = regVal;
    }
    else if (dwTimerId == 1)
    {
        regVal = LPC_TMR32B1->TCR;
        regVal |= 0x02;
        LPC_TMR32B1->TCR = regVal;
    }
    else if (dwTimerId == 2)
    {
        regVal = LPC_TMR32B2->TCR;
        regVal |= 0x02;
        LPC_TMR32B2->TCR = regVal;
    }
    else if (dwTimerId == 3)
    {
        regVal = LPC_TMR32B3->TCR;
        regVal |= 0x02;
        LPC_TMR32B3->TCR = regVal;
    }

    return;
}

void phOsal_Lpc17xx_Int_Init_Timer32(uint32_t dwTimerId, uint32_t TimerInterval)
{

    if ( dwTimerId == 0 )
    {
        LPC_TMR32B0->MR0 = TimerInterval;
        /* Interrupt and Reset on MR0 */
        LPC_TMR32B0->MCR = (0x5);

        /* Enable the TIMER0 Interrupt */
        NVIC_EnableIRQ(TIMER0_IRQn);
    }
    else if ( dwTimerId == 1 )
    {
        LPC_TMR32B1->MR0 = TimerInterval;
        /* Interrupt and Reset on MR0 */
        LPC_TMR32B1->MCR = (0x5);

        /* Enable the TIMER1 Interrupt */
        NVIC_EnableIRQ(TIMER1_IRQn);
    }
    else if ( dwTimerId == 2 )
    {
        /*On reset, Timer0/1 are enabled (PCTIM0/1 = 1), and Timer2/3 are disabled (PCTIM2/3 = 0)*/
        CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCTIM2, ENABLE);

        LPC_TMR32B2->MR0 = TimerInterval;

        /* Interrupt and Reset on MR0 */

        LPC_TMR32B2->MCR = (0x5);

        /* Enable the TIMER1 Interrupt */
        NVIC_EnableIRQ(TIMER2_IRQn);

    }
    else if ( dwTimerId == 3 )
    {
        /*On reset, Timer0/1 are enabled (PCTIM0/1 = 1), and Timer2/3 are disabled (PCTIM2/3 = 0)*/
        CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCTIM3, ENABLE);

        LPC_TMR32B3->MR0 = TimerInterval;
 
        /* Interrupt and Reset on MR0 */
        LPC_TMR32B3->MCR = (0x5);

        /* Enable the TIMER1 Interrupt */
        NVIC_EnableIRQ(TIMER3_IRQn);
    }

    return;
}

void phOsal_Lpc17xx_Int_Load_TimerMs(uint32_t dwTimerId, uint32_t dwTimerInterval)
{
    /* Load the given timer interval onto match register 0 */
    if (dwTimerId == 0)
    {
        LPC_TMR32B0->MR0 = dwTimerInterval* ((SystemCoreClock) / 1000);
    }
    else if (dwTimerId == 1)
    {
        LPC_TMR32B1->MR0 = dwTimerInterval* ((SystemCoreClock) / 1000);
    }
    else if (dwTimerId == 2)
    {
        LPC_TMR32B2->MR0 = dwTimerInterval* ((SystemCoreClock) / 1000);
    }
    else if (dwTimerId == 3)
    {
        LPC_TMR32B3->MR0 = dwTimerInterval* ((SystemCoreClock) / 1000);
    }

    return;
}

void phOsal_Lpc17xx_Int_Load_TimerUs(uint32_t dwTimerId, uint32_t dwTimerInterval)
{
    /* Load the given timer interval onto match register 0 */
    if (dwTimerId == 0)
    {
        LPC_TMR32B0->MR0 = dwTimerInterval* ((SystemCoreClock) / 1000000);
    }
    else if (dwTimerId == 1)
    {
        LPC_TMR32B1->MR0 = dwTimerInterval* ((SystemCoreClock) / 1000000);
    }
    else if (dwTimerId == 2)
    {
        LPC_TMR32B2->MR0 = dwTimerInterval* ((SystemCoreClock) / 1000000);
    }
    else if (dwTimerId == 3)
    {
        LPC_TMR32B3->MR0 = dwTimerInterval* ((SystemCoreClock) / 1000000);
    }

    return;
}

#endif /* NXPBUILD__PH_OSAL_STUB */
