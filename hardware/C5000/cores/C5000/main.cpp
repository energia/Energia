//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
// *
// *  Redistribution and use in source and binary forms, with or without
// *  modification, are permitted provided that the following conditions
// *  are met:
// *
// *    Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// *
// *    Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the
// *    distribution.
// *
// *    Neither the name of Texas Instruments Incorporated nor the names of
// *    its contributors may be used to endorse or promote products derived
// *    from this software without specific prior written permission.
// *
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
//////////////////////////////////////////////////////////////////////////////

/** @file main.cpp
 *
 *  @brief Energia main function implementation
 *
 */

#include "C5000.h"
#include "csl_pll.h"
#include "stdio.h"
#include "tistdtypes.h"
#include "core.h"

/** PLL configuration structure */
PLL_Config *pConfigInfo;
/** PLL object */
PLL_Obj pllObj;
/** PLL handle */
PLL_Handle hPll;
/** CPU clock value in Hz */
Uint32 gCPUClock;

#ifdef ENABLE_OLED_DBG
#include <OLED_lib.h>
void (*fn_oled_display)(char *sring);

/**
 *
 *  oled_display(char *sring)
 *
 *  API to display string on OLED
 *      char *sring <- String to be displayed
 */
void oled_display(char *sring)
{
	disp.clear(0);
	disp.print(sring);
}
#endif

/**
 *
 *  setupPll(int speed)
 *
 *  API to setup the PLL
 *      int speed <- CPU speed value to be set
 */
void setupPll(int speed)	//This function sets the DSP up to operate at a defined frequency. Without it, the system will default to running at 12MHz.
{
/*
	PLL_Config pllCfg_40MHz     = {0x8988, 0x8000, 0x0806, 0x0201};
	PLL_Config pllCfg_60MHz     = {0x8724, 0x8000, 0x0806, 0x0000};
	PLL_Config pllCfg_75MHz     = {0x88ED, 0x8000, 0x0806, 0x0000};
*/

#ifdef CHIP_C5517
	PLL_Config pllCfg_100MHz    = {0x41AB, 0x0003, 0x0010, 0x0000};
	PLL_Config pllCfg_150MHz 	= {0x3100, 0x0003, 0x0000, 0x0020};
#else
	PLL_Config pllCfg_100MHz;

	if(CSL_FEXT(CSL_SYSCTRL_REGS->CCR2, SYS_CCR2_CLKSELSTAT) == CSL_SYS_CCR2_CLKSELSTAT_CLKIN)
	{
		PLL_Config pllCfg_100MHz_CLKIN    = {0x833E, 0x0060, 0x0806, 0x0000};
		pllCfg_100MHz = pllCfg_100MHz_CLKIN;
	}
	else
	{
		PLL_Config pllCfg_100MHz_RTC    = {0x8BE8, 0x8000, 0x0806, 0x0000};
		pllCfg_100MHz = pllCfg_100MHz_RTC;
	}

#endif

	PLL_init(&pllObj, CSL_PLL_INST_0);
	hPll = (PLL_Handle)(&pllObj);
	PLL_reset(hPll);

	/* Configure the PLL for xMHz */
	switch(speed)
	{
/*
		case 40:
			pConfigInfo = &pllCfg_40MHz;
			break;
		case 60:
			pConfigInfo = &pllCfg_60MHz;
			break;
		case 75:
			pConfigInfo = &pllCfg_75MHz;
			break;
*/
		case 100:
			pConfigInfo = &pllCfg_100MHz;
			break;
#ifdef CHIP_C5517
/*
		case 120:
			pConfigInfo = &pllCfg_120MHz;
			break;
*/

		case 150:
			pConfigInfo = &pllCfg_150MHz;
			break;
#endif

		default:	//default to 100MHz
			pConfigInfo = &pllCfg_100MHz;
			break;
	}

	PLL_config (hPll, pConfigInfo);
	PLL_enable(hPll);

	gCPUClock = (getCpuClock()*1000);
}

/**
 *
 *  sys_init(void)
 *
 *  API for initializing the system
 */
void sys_init(void)
{
	DMA.init();
	//Serial.begin(9600);
	Wire.begin();
	gpioOpen();
	initInterrupt(0x0000);
	I2S.init();
}

/**
 *
 *  main(void)
 *
 *  main function
 */
int main(void)
{
	csl_init();

#ifdef CHIP_C5517
	setupPll(150);
#else
	setupPll(100);
#endif

#ifdef ENABLE_OLED_DBG
    disp.oledInit();
    disp.clear();
    disp.setline(0);
    disp.setOrientation(1);

    disp.print("Calling Boot      ");

    fn_oled_display = oled_display;
#endif

    SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_1);

	boot_update();

	/* Initialize the libraries which are commonly used by different modules */
	csl_init();
	sys_init();

	setup();

	for (;;) {
		loop();
	}
}

