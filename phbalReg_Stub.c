/*
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
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
* BAL Stub Component of Reader Library Framework.
* $Author: nxp40786 $
* $Revision: 332 $
* $Date: 2013-08-07 17:57:29 +0530 (Wed, 07 Aug 2013) $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#include <ph_Status.h>
#include <phbalReg.h>
#include <ph_RefDefs.h>
#include "phhwConfig.h"

#ifdef NXPBUILD__PHBAL_REG_STUB

#include "phbalReg_Stub.h"
//#include <lpc17xx_ssp.h>
//#include <lpc17xx_i2c.h>
//#include <lpc17xx_pinsel.h>
//#include <lpc17xx_gpio.h>


phStatus_t phbalReg_Stub_Init(
                              phbalReg_Stub_DataParams_t * pDataParams,
                              uint16_t wSizeOfDataParams
                              )
{
    if (sizeof(phbalReg_Stub_DataParams_t) != wSizeOfDataParams)
    {
        return PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_BAL);
    }
	PH_ASSERT_NULL (pDataParams);

    pDataParams->wId = PH_COMP_BAL | PHBAL_REG_STUB_ID;

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Stub_GetPortList(
    phbalReg_Stub_DataParams_t * pDataParams,
    uint16_t wPortBufSize,
    uint8_t * pPortNames,
    uint16_t * pNumOfPorts
    )
{
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Stub_SetPort(
                            phbalReg_Stub_DataParams_t * pDataParams,
                            uint8_t * pPortName
                            )
{
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Stub_OpenPort(
                                  phbalReg_Stub_DataParams_t * pDataParams
                                  )
{
//#ifdef SPI_USED
//
//	PINSEL_CFG_Type PinCfg;
//	SSP_CFG_Type SSP_ConfigStruct;
//	uint32_t ClockRate = 1000000;
//
//	PinCfg.Pinmode = 0;
//	PinCfg.OpenDrain = 0;
//
//	PinCfg.Pinmode = 0;
//	PinCfg.OpenDrain = 0;
//	/* NSS has to be driven by hand because RC523 requires the NSS to be
//	 * LOW to be able to send several bytes in one data stream (see MFRC523
//	 * page 86) and LPC17XX SSP0 Port in mode CPHA = 0 and CPOL = 0 always
//	 * sets NSS to HIGH after byte transmission.
//	 * */
//	PinCfg.Portnum = 0;
//	PinCfg.Pinnum = MOSI_PINNUM;
//	PinCfg.Funcnum = 2;
//	PINSEL_ConfigPin(&PinCfg);
//
//	PinCfg.Portnum = 0;
//	PinCfg.Pinnum = MISO_PINNUM;
//	PinCfg.Funcnum = 2;
//	PINSEL_ConfigPin(&PinCfg);
//
//	PinCfg.Portnum = 0;
//	PinCfg.Pinnum = SCK_PINNUM;
//	PinCfg.Funcnum = 2;
//	PINSEL_ConfigPin(&PinCfg);
//
//	PinCfg.Portnum = 0;
//	PinCfg.Pinnum  = SSEL_PINNUM;
//	PinCfg.Funcnum = 0;
//	PINSEL_ConfigPin(&PinCfg);
//
//	GPIO_SetDir(0, PIN_SSEL, SET_OUT);
//	GPIO_SetValue(0, PIN_SSEL);
//
//	SSP_ConfigStruct.CPHA = SSP_CPHA_FIRST;
//	SSP_ConfigStruct.CPOL = SSP_CPOL_HI;
//
//	SSP_ConfigStruct.ClockRate = ClockRate;
//	SSP_ConfigStruct.Databit = SSP_DATABIT_8;
//	SSP_ConfigStruct.Mode = SSP_MASTER_MODE;
//	SSP_ConfigStruct.FrameFormat = SSP_FRAME_SPI;
//
//	SSP_Init(LPC_SSPx, &SSP_ConfigStruct);
//	SSP_Cmd(LPC_SSPx, ENABLE);
//
//	/* wait Startup time */
//	if(/*pDataParams->ic == PHBAL_REG_STUBI2C_CONFIG_IC_RC663*/1)
//	{
//		volatile uint32_t delay;
//		for(delay=0;delay<10000;delay++){}
//	}
//
//	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
//#endif /* SPI_USED */

//#ifdef I2C_USED
//	PINSEL_CFG_Type PinCfg;
//
//	PinCfg.OpenDrain = PINSEL_PINMODE_OPENDRAIN;
//	PinCfg.Pinmode = PINSEL_PINMODE_TRISTATE;
//	PinCfg.Funcnum = 2;
//	PinCfg.Portnum = 0;
//
//	PinCfg.Pinnum = 10;
//	PINSEL_ConfigPin(&PinCfg);
//
//	PinCfg.Pinnum = 11;
//	PINSEL_ConfigPin(&PinCfg);
//
//	I2C_Init(LPC_I2C2, 1000000);
//
//	I2C_Cmd(LPC_I2C2, ENABLE);
//
//	/* wait Startup time */
//	if(pDataParams->ic == PHBAL_REG_STUBI2C_CONFIG_IC_RC663)
//	{
//		volatile uint32_t delay;
//		for(delay=0;delay<10000;delay++){}
//	}
//
//	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
//#endif /* I2C_USED */
/* TUSA */
	SSP_Emul_GPIO_Config();
/* TUSA */
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Stub_ClosePort(
                                   phbalReg_Stub_DataParams_t * pDataParams
                                   )
{
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

phStatus_t phbalReg_Stub_Exchange(
                                  phbalReg_Stub_DataParams_t * pDataParams,
                                  uint16_t wOption,
                                  uint8_t * pTxBuffer,
                                  uint16_t wTxLength,
                                  uint16_t wRxBufSize,
                                  uint8_t * pRxBuffer,
                                  uint16_t * pRxLength
                                  )
{
#ifdef SPI_USED
	uint16_t xferLen;
	SSP_DATA_SETUP_Type xferConfig;

	xferConfig.length = wTxLength;
	xferConfig.rx_data = pRxBuffer;
	xferConfig.tx_data = pTxBuffer;

	/* chip select reader IC */
//	LPC_GPIO0->FIOCLR = PIN_SSEL;
    RC663_SPI_CS_GPIO_L();
	/* data exchange */
//	xferLen = SSP_ReadWrite (LPC_SSPx, &xferConfig, SSP_TRANSFER_POLLING);
    xferLen = SSP_Emul_GPIO_ReadWrite (&xferConfig);
	/* chip deselect reader IC */
//	LPC_GPIO0->FIOSET = PIN_SSEL;
    RC663_SPI_CS_GPIO_H();

	if (xferLen != wTxLength)
	{
		return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
	}

	*pRxLength = xferLen;

	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
#endif /* SPI_USED */
//#ifdef I2C_USED
//	I2C_M_SETUP_Type transferMCfg;
//
//	/* Only 7Bits of slave address should be initialized as Last bit(R/W) will be appended automatically
//	 * based on the operation done. */
//	transferMCfg.sl_addr7bit         = 0x28;
//	transferMCfg.tx_data              = pTxBuffer;
//	transferMCfg.tx_length              = (uint32_t)wTxLength;
//	transferMCfg.rx_data              = pRxBuffer;
//	transferMCfg.rx_length              = (uint32_t)wRxBufSize;
//	transferMCfg.retransmissions_max = 3;
//	if (SUCCESS != I2C_MasterTransferData(LPC_I2C2, &transferMCfg, I2C_TRANSFER_POLLING))
//	{
//		return PH_ADD_COMPCODE(PH_ERR_INTERFACE_ERROR, PH_COMP_BAL);
//	}
//
//	if(pRxLength != NULL)
//	{
//		*pRxLength = (uint16_t)(transferMCfg.rx_count & 0x0000FFFF);
//	}
//
//	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
//#endif /* I2C_USED */
}

phStatus_t phbalReg_Stub_SetConfig(
                                   phbalReg_Stub_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t wValue
                                   )
{
	switch (wConfig)
	{
	case PHBAL_REG_CONFIG_HAL_HW_TYPE:
		switch(wValue)
		{
		case PHBAL_REG_HAL_HW_RC523:
			pDataParams->wHalType = wValue;
			break;
		case PHBAL_REG_HAL_HW_RC663:
			pDataParams->wHalType = wValue;
			break;
		default:
			return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
		}
	case PHBAL_REG_STUBI2C_CONFIG_IC:
		switch(wValue)
		{
		case PHBAL_REG_STUBI2C_CONFIG_IC_RC663:
			pDataParams->ic = PHBAL_REG_STUBI2C_CONFIG_IC_RC663;
			break;
		case PHBAL_REG_STUBI2C_CONFIG_IC_RC523:
			pDataParams->ic = PHBAL_REG_STUBI2C_CONFIG_IC_RC523;
			break;
		default:
			return PH_ADD_COMPCODE(PH_ERR_INVALID_PARAMETER, PH_COMP_BAL);
		}
	default:
		return PH_ADD_COMPCODE(PH_ERR_UNSUPPORTED_PARAMETER, PH_COMP_BAL);
	}
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);

}

phStatus_t phbalReg_Stub_GetConfig(
                                   phbalReg_Stub_DataParams_t * pDataParams,
                                   uint16_t wConfig,
                                   uint16_t * pValue
                                   )
{
	return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_BAL);
}

#endif /* NXPBUILD__PHBAL_REG_STUB */
