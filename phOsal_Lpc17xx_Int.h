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
* LPC12xx OSAL Component of Reader Library Framework.
* $Author: nxp62726 $
* $Revision: 286 $
* $Date: 2013-07-09 14:09:18 +0530 (Tue, 09 Jul 2013) $
*
* History:
*  PC: Generated 23. Aug 2012
*
*/

#ifndef PHOSAL_LPC17XX_INT_H
#define PHOSAL_LPC17XX_INT_H

#include <phOsal.h>
#include "phOsal_Stub.h"
#include "ph_NxpBuild.h"
#include "stm32f10x.h"
#include "Delay/Delay.h" 

#define LPC17XX_MAX_TIMERS		 		3U		   /* number of timers */
#define LPC17XX_DEFAULT_TIME_INTERVAL   10000U     /**< Default timer interval that will be loaded */
/**
* \ Initializes timers to the application
*/

void phOsal_Lpc17xx_Int_Timer_Init(phOsal_Stub_DataParams_t *pDataParams);

/**
* Creates a timer component.
* Internally, an array is maintained which stores timers along with
* information as to whether the timer is available or not. This
* function searches a free timer that is available and returns the
* timer id in \a pTimerId. If there are no free timers,
* then appropriate error code is returned.
*
* \return   status code
* \retval   #PH_ERR_SUCCESS on success
* \retval   #PH_OSAL_ERR_NO_FREE_TIMER if no timers are available
*
*/

void phOsal_Lpc17xx_Int_Timer_Create( phOsal_Stub_DataParams_t *pDataParams, uint32_t *pTimerId );

/**
* Timer Register.
* \retval  #PH_ERR_SUCCESS on success
*
*/

phStatus_t phOsal_Lpc17xx_Int_Timer_Register( phOsal_Stub_DataParams_t  *pDataParams,
                                             uint32_t                       dwTimerId,
                                             uint32_t                       dwRegTimeCnt,
                                             uint16_t                       wOption,
                                             ppCallBck_t                    pApplicationCallback,
                                             void                          *pContext
                                             );

/**
* Stops the said timer.
* This function does not free the timer. It only disables the timer.
* Use phOsal_Timer_Delete() to free the timer.
*
* \return  status code
* \retval  #PH_OSAL_ERR_INVALID_TIMER if the timer ID supplied was invalid
* \retval  #PH_ERR_SUCCESS            on success
*
*/

phStatus_t phOsal_Lpc17xx_Int_Timer_Stop( uint32_t dwTimerId );

/**
* Frees the timer.
* When this function is called, the timer with given ID is returned to the
* free timer pool.
*
* \return  status code
* \retval  #PH_OSAL_ERR_INVALID_TIMER if the timer ID supplied was invalid
* \retval  #PH_ERR_SUCCESS            on success
*
*/

phStatus_t phOsal_Lpc17xx_Int_Timer_Delete( phOsal_Stub_DataParams_t *pDataParams, uint32_t dwTimerId );

/**
* Delays the timer in milli seconds.
* When this function is called, the timer waits until delay time has elapsed.
*
*
*/

void phOsal_Lpc17xx_Int_Delay32Ms( uint32_t dwTimerId, uint32_t delayInMs );

/**
* Delays the timer in micro seconds.
* When this function is called, the timer waits until delay time has elapsed.
*
*
*/

void phOsal_Lpc17xx_Int_Delay32Us( uint32_t dwTimerId, uint32_t delayInUs );

/**
* IRQ Handler for Timer0.
*
*/

void phOsal_Lpc17xx_Int_TIMER0_IRQHandler(void);

/**
* IRQ Handler for Timer1.
*
*/

void phOsal_Lpc17xx_Int_TIMER1_IRQHandler(void);

/**
* IRQ Handler for Timer2.
*
*/

void phOsal_Lpc17xx_Int_TIMER2_IRQHandler(void);

/**
* Start the timer
* When this function is called with timer number provided
* as an argument, the corresponding timer is enabled.
*
*
*/

void phOsal_Lpc17xx_Int_Enable_Timer32( uint32_t dwTimerId );

/**
* Stop the timer.
* When this function is called with timer number provided
* as an argument, the corresponding timer is disabled.
*
*
*/

void phOsal_Lpc17xx_Int_Disable_Timer32( uint32_t dwTimerId );

/**
* Timer Reset
*
*/

void phOsal_Lpc17xx_Int_Reset_Timer32( uint32_t dwTimerId );

/**
* \ Initializes the timer.
*/

void phOsal_Lpc17xx_Int_Init_Timer32( uint32_t dwTimerId, uint32_t TimerInterval );

/**
* \ Load the given timer interval.
*/

void phOsal_Lpc17xx_Int_Load_TimerMs( uint32_t dwTimerId, uint32_t dwTimerInterval );

/**
* \ Load the given timer interval.
*/

void phOsal_Lpc17xx_Int_Load_TimerUs( uint32_t dwTimerId, uint32_t dwTimerInterval );

#endif /* PHOSAL_LPC17XX_H */
