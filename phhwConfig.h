/***********************************************************************************************
 *   config.h:  config file f	or example for NXP LPC122x Family
 *   Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2012.07.20  ver 1.00    First Release
 *
 ***********************************************************************************************/


/*----------------------------------------------------------------------------------------------
 * Includes
 ---------------------------------------------------------------------------------------------*/
#ifndef __PHHW_CONFIG_H__
#define __PHHW_CONFIG_H__

//#include <LPC17xx.h>
#include "stm32f10x.h"
#include <phhalHw.h>
#include <ph_NxpBuild.h>
#include <phOsal.h>

/***********************************************************************************************
 **	Global macros and definitions
 ***********************************************************************************************/

//#define TUSA

#if defined(TUSA) & !defined(NXPBUILD__PHHAL_HW_RC663)
#error ** Mismatch in hardware configuration - TUSA board includes RC663 reader IC **
#endif

#define SPI_USED

#if defined (SPI_USED) && defined (I2C_USED)
#error ** Mismatch interface definition - I2C and SPI not alloved together **
#endif

#ifdef SPI_USED
#define PHHAL_HW_BUS	PHHAL_HW_BAL_CONNECTION_SPI
#endif /* SPI_USED */
//#ifdef I2C_USED
//#define PHHAL_HW_BUS	PHHAL_HW_BAL_CONNECTION_I2C
//#define READER_CHIP_ADDR 0x50
//#endif /* I2C_USED */

/* ------------------------------------------------ */
/* general ports definition                         */
/* ------------------------------------------------ */
#define PORT0			   0
#define PORT1              1
#define PORT2              2
#define PORT3			   3
#define PORT4			   4
//#define LED_PORT           PORT0    // Port for LED
/* ------------------------------------------------ */
/* value/state definition                           */
/* ------------------------------------------------ */
#define SET_OUT            1   		  // a pin of chip is configured to output direction
#define SET_IN             0   		  // a pin of chip is configured to input direction
#define SET_HIGH           1
#define SET_LOW            0

//#define LED_BIT            1 << 22     // Bit on port for led
//#define LED_ON             1     	   // Level to set port to turn on led
//#define LED_OFF            0     	   // Level to set port to turn off led
/* ------------------------------------------------ */
/* pins definition                                  */
/* ------------------------------------------------ */
#ifdef NXPBUILD__PHHAL_HW_RC663
#define RC663_SPI_CS_GPIO		    GPIOA
#define RC663_SPI_CS_GPIO_CLK	    RCC_APB2Periph_GPIOA
#define RC663_SPI_CS_GPIO_PIN	    GPIO_Pin_4
#define RC663_SPI_CS_GPIO_MODE    	GPIO_Mode_Out_PP
#define RC663_SPI_CS_GPIO_H()		RC663_SPI_CS_GPIO->ODR  |= RC663_SPI_CS_GPIO_PIN
#define RC663_SPI_CS_GPIO_L()		RC663_SPI_CS_GPIO->ODR  &= ~RC663_SPI_CS_GPIO_PIN

#define RC663_SPI_MOSI_GPIO			GPIOA
#define RC663_SPI_MOSI_GPIO_CLK		RCC_APB2Periph_GPIOA
#define RC663_SPI_MOSI_GPIO_PIN		GPIO_Pin_7
#define RC663_SPI_MOSI_GPIO_MODE  	GPIO_Mode_Out_PP
#define RC663_SPI_MOSI_GPIO_H()		RC663_SPI_MOSI_GPIO->ODR  |= RC663_SPI_MOSI_GPIO_PIN
#define RC663_SPI_MOSI_GPIO_L()		RC663_SPI_MOSI_GPIO->ODR  &= ~RC663_SPI_MOSI_GPIO_PIN

#define RC663_SPI_SCLK_GPIO			GPIOA
#define RC663_SPI_SCLK_GPIO_CLK		RCC_APB2Periph_GPIOA
#define RC663_SPI_SCLK_GPIO_PIN		GPIO_Pin_5
#define RC663_SPI_SCLK_GPIO_MODE  	GPIO_Mode_Out_PP
#define RC663_SPI_SCLK_GPIO_H()		RC663_SPI_SCLK_GPIO->ODR  |= RC663_SPI_SCLK_GPIO_PIN
#define RC663_SPI_SCLK_GPIO_L()		RC663_SPI_SCLK_GPIO->ODR  &= ~RC663_SPI_SCLK_GPIO_PIN

#define RC663_SPI_MISO_GPIO			GPIOA
#define RC663_SPI_MISO_GPIO_CLK		RCC_APB2Periph_GPIOA
#define RC663_SPI_MISO_GPIO_PIN		GPIO_Pin_6
#define RC663_SPI_MISO_GPIO_MODE  	GPIO_Mode_IPU	 

#define RC663_PDOWN_GPIO		    	GPIOB
#define RC663_PDOWN_GPIO_CLK	    	RCC_APB2Periph_GPIOB
#define RC663_PDOWN_GPIO_PIN	    	GPIO_Pin_11
#define RC663_PDOWN_GPIO_MODE    		GPIO_Mode_Out_PP
#define RC663_PDOWN_GPIO_H()	    	RC663_PDOWN_GPIO->ODR  |= RC663_PDOWN_GPIO_PIN
#define RC663_PDOWN_GPIO_L()	    	RC663_PDOWN_GPIO->ODR  &= ~RC663_PDOWN_GPIO_PIN

//	#define PIN_AD0			   1 << 17
//	#define PIN_AD1	   		   1 << 15
//	#define PIN_IFSEL0         1 << 4    	 // select pin to define com. interface type for RC663
//	#define PIN_IFSEL1         1 << 5    	 // select pin to define com. interface type for RC663
//	#ifndef TUSA
//		#define PIN_RESET	   1 << 5   	 // for reset pin for Blueboard CLEV663B
//		#define PIN_SSEL       1 << 10       // SSEL pin for SSP periphery for Blueboard CLEV663B
//		#define MOSI_PINNUM	   9
//		#define MISO_PINNUM    8
//		#define SCK_PINNUM	   7
//		#define SSEL_PINNUM    10
//		#define LPC_SSPx	   LPC_SSP1
//	#else /* TUSA */
//		#define PIN_RESET	   1 << 11		 // reset pin for Silica TUSA board
//		#define PIN_SSEL       1 << 10		 // SSEL pin for SSP periphery for Silica TUSA board
//		#define MOSI_PINNUM	   18
//		#define MISO_PINNUM    17
//		#define SCK_PINNUM	   15
//		#define SSEL_PINNUM    10
//		#define LPC_SSPx	   LPC_SSP0
//	#endif /* TUSA */

#endif /* NXPBUILD__PHHAL_HW_RC663 */
//#ifdef NXPBUILD__PHHAL_HW_RC523
//	#define PIN_AD0			   1 << 23
//	#define PIN_AD1	   		   1 << 24
//	#define PIN_AD2	   		   1 << 25
//	#define PIN_RESET	       1 << 27  	// for reset pin for Blueboard PNEV512B
//	#define PIN_SSEL           1 << 6       // SSEL pin for SSP periphery for Blueboard PNEV512B
//	#define MOSI_PINNUM	   	   9
//	#define MISO_PINNUM    	   8
//	#define SCK_PINNUM	   	   7
//	#define SSEL_PINNUM    	   10
//	#define LPC_SSPx	   	   LPC_SSP1
//#endif /* NXPBUILD__PHHAL_HW_RC523 */

#define ADDR_CLEAR		   0
#define ADDR_SET		   1

#define SSEL_ASR           0
#define SSEL_DEASR         1
#define READER_CHIP_ADDR 0x50

#define I2C_SDA            1 << 10
#define I2C_SCL            1 << 11
#define SSP_CLK            1 << 7
#define SSP_MISO           1 << 8
#define SSP_MOSI           1 << 9

/***********************************************************************************************
 **	Global variables
 ***********************************************************************************************/

/***********************************************************************************************
 **	Global function prototypes
 ***********************************************************************************************/
extern void Set_Interface_Link(void);
//extern void GPIO_Init(void);
extern void Set_Port(void);
extern void Reset_reader_device(void);
extern void LedOn(void);
extern void LedOff(void);
#ifdef NXPBUILD__PHHAL_HW_RC523
void Set_Interrupt(uint8_t bState);
void appDataInit( void *pHal, void *pOsal, void *pData);
#endif /* NXPBUILD__PHHAL_HW_RC523 */
/******************************************************************************************
 * Reader IC specific soft reset function - command
 ******************************************************************************************/
#ifdef NXPBUILD__PHHAL_HW_RC523
	#define SoftReset_reader_device(pHal)	phhalHw_Rc523_Cmd_SoftReset(pHal)
#endif
#ifdef NXPBUILD__PHHAL_HW_RC663
	#define SoftReset_reader_device(pHal)	phhalHw_Rc663_Cmd_SoftReset(pHal)
#endif

#endif	// __PHHW_CONFIG_H__

/***********************************************************************************************
 **                            End Of File
 ***********************************************************************************************/





