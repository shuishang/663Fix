==============================================================================
Readme - Software for the PNEV512B Blueboard and CLEV663B Blueboard
==============================================================================

1. Document purpose

This document describes the content of the source package as well as known
problems and restrictions.
A separate User Manual describes the first steps how to use the software in
combination with the Hardware.

2. Known problems and restrictions

* Restrictions
The Software is restricted to the PNEV512B Blueboard and CLEV663B Blueboard. The API is intended for
the NXP contactless/contact reader ICs, as such the API is not to be ported to any technology from
any other vendor.
The Software is running on a Cortex M0 LPC1769 controller from NXP. 
NXP will not support porting to any other vendor platform. 

This project is intended to be used together with a
NFC Reader Library project and a application project.

* Known Problems

  - none
	
3. Content

LPC17xx (Eclipse project) content:
¦   .cproject
¦   .project
¦   phhwConfig.c
¦   phhwConfig.h
¦   Readme.txt (this file)
¦
+---CMSIS
¦   +---inc
¦   ¦       core_cm3.h
¦   ¦       core_cmFunc.h
¦   ¦       core_cmInstr.h
¦   ¦       LPC17xx.h
¦   ¦       system_LPC17xx.h
¦   ¦
¦   +---src
¦           core_cm3.c
¦           system_LPC17xx.c
¦
+---drivers
¦   +---inc
¦   ¦       lpc17xx_adc.h
¦   ¦       lpc17xx_can.h
¦   ¦       lpc17xx_clkpwr.h
¦   ¦       lpc17xx_dac.h
¦   ¦       lpc17xx_emac.h
¦   ¦       lpc17xx_exti.h
¦   ¦       lpc17xx_gpdma.h
¦   ¦       lpc17xx_gpio.h
¦   ¦       lpc17xx_i2c.h
¦   ¦       lpc17xx_i2s.h
¦   ¦       lpc17xx_libcfg_default.h
¦   ¦       lpc17xx_mcpwm.h
¦   ¦       lpc17xx_nvic.h
¦   ¦       lpc17xx_pinsel.h
¦   ¦       lpc17xx_qei.h
¦   ¦       lpc17xx_rit.h
¦   ¦       lpc17xx_rtc.h
¦   ¦       lpc17xx_spi.h
¦   ¦       lpc17xx_ssp.h
¦   ¦       lpc17xx_systick.h
¦   ¦       lpc17xx_timer.h
¦   ¦       lpc17xx_uart.h
¦   ¦       lpc17xx_wdt.h
¦   ¦       lpc_types.h
¦   ¦
¦   +---src
¦           lpc17xx_clkpwr.c
¦           lpc17xx_gpdma.c
¦           lpc17xx_gpio.c
¦           lpc17xx_i2c.c
¦           lpc17xx_i2s.c
¦           lpc17xx_libcfg_default.c
¦           lpc17xx_nvic.c
¦           lpc17xx_pinsel.c
¦           lpc17xx_rtc.c
¦           lpc17xx_spi.c
¦           lpc17xx_ssp.c
¦           lpc17xx_systick.c
¦           lpc17xx_timer.c
¦           lpc17xx_wdt.c
¦
+---startup
¦       cr_startup_lpc17.c
¦
+---Stub
        phbalReg_Stub.c
        phOsal_Lpc17xx_Int.c
        phOsal_Lpc17xx_Int.h
        phOsal_Stub.c

4. Mandatory material, not included

* LPCXpresso IDE as described on the web site:
	http://www.lpcware.com/lpcxpresso
* LPCXpresso LPC1769 development board

5. Revision History

V1.0:
* First packaged version.