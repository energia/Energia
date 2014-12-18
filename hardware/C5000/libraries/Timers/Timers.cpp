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
/** @file Timers.cpp
 *
 *  @brief Timers implementation
 *
 */

#include "Timers.h"

/** GPT object */
CSL_GptObj         gptObj[TIMER_INSTANCE_COUNT];
/** GPT handle */
CSL_Handle         hGpt;
/** WDT handle */
CSL_WdtHandle      hWdt;
/** WDT object */
CSL_WdtObj         wdtObj;

/**
 * Class identifier declaration
 */
TimerClass Timer;

/**
 *
 *  handleErrors(int status)
 *
 *      Handle errors returned by CSL APIs.
 *
 */
void TimerClass::handleErrors(int status)
{

}

/**
 *
 *  selectTimer(GPT_Instance gptInstance)
 *
 *      Initialize Timers Module for the given timer instance.
 *
 *      unsigned short timerInstance   <- Timers instance number (0 to 2)
 */
int TimerClass::selectTimer(unsigned short	gptInstance)
{
    CSL_Status     status;

    hGpt = GPT_open((CSL_Instance)gptInstance, &gptObj[gptInstance], &status);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

	status = GPT_reset(hGpt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  configTimer(Timers_config)
 *
 *      Configure the Timers parameters for the given timer.
 *
 *      CSL_Config gptConfig  <- Timer configurations
 */
int TimerClass::configTimer(GPT_Config gptConfig)
{
    CSL_Status           status;
	CSL_Config           cslConfig;

    status = CSL_ESYS_FAIL;

    if(&gptConfig != NULL)
	{
	    cslConfig.autoLoad    = (CSL_AutoReLoad)gptConfig.autoLoad;
		cslConfig.ctrlTim     = (CSL_CtrlTimer)gptConfig.ctrlTim;
		cslConfig.prdHigh     = (Uint16)gptConfig.prdHigh;
		cslConfig.prdLow      = (Uint16)gptConfig.prdLow;
		cslConfig.preScaleDiv = (CSL_PreScale)gptConfig.preScaleDiv;

	    /* Configure GPT for a given timer */
	    status = GPT_config(hGpt, &cslConfig);
		if(status != CSL_SOK)
		{
		    Timer.handleErrors(status);
		}
	}
	else
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  initialize(period)
 *
 *      Set the given period for the selected timer.
 *
 *      long int period  <- Timer period
 */
void TimerClass::initialize(long period)
{
    CSL_Status           status;
    CSL_Config           gptConfig;

    gptConfig.autoLoad     = GPT_AUTO_ENABLE;
	gptConfig.ctrlTim      = GPT_TIMER_ENABLE;
	gptConfig.prdHigh      = (Uint16)((period & HIGH_WORD_MASK) >> WORD_LENGTH);
	gptConfig.prdLow       = (Uint16)(period & LOW_WORD_MASK);
	gptConfig.preScaleDiv  = (CSL_PreScale)GPT_PRE_SC_DIV_0;

   /* Configure GPT for a given timer */
    status = GPT_config(hGpt, &gptConfig);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return;
}

/**
 *
 *  setPeriod(period)
 *
 *      Set the given period for the selected timer.
 *
 *      long period  <- Timer period
 */
void TimerClass::setPeriod(long period)
{
    CSL_Status           status;
    CSL_Config           gptConfig;

    gptConfig.autoLoad     = GPT_AUTO_ENABLE;
	gptConfig.ctrlTim      = GPT_TIMER_ENABLE;
	gptConfig.prdHigh      = (Uint16)((period & HIGH_WORD_MASK) >> WORD_LENGTH);
	gptConfig.prdLow       = (Uint16)(period & LOW_WORD_MASK);
	gptConfig.preScaleDiv  = (CSL_PreScale)GPT_PRE_SC_DIV_0;

   /* Configure GPT for a given timer */
    status = GPT_config(hGpt, &gptConfig);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return;
}

/**
 *
 *  start()
 *
 *      Starts to load value from period register to
 *      count down register.
 *
 */
void TimerClass::start()
{
    CSL_Status     status;

    status = GPT_start(hGpt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return;
}

/**
 *
 *  stop()
 *
 *      Stops loading from period register to
 *      count down register.
 *
 */
void TimerClass::stop()
{
    CSL_Status     status;

    status = GPT_stop(hGpt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}
	status = GPT_reset(hGpt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return;
}

/**
 *
 *  read()
 *
 *      Returns timer count value read from the timer.
 *
 */
unsigned long TimerClass::read()
{
    CSL_Status     status;
    unsigned long  timeCnt;

    status = GPT_getCnt(hGpt, &timeCnt);

    if(status != CSL_SOK)
    {
        Timer.handleErrors(status);
    }

    return timeCnt;
}

/**
 *
 *  close()
 *
 *      Closes the specified handle of GPT
 */
int TimerClass::close()
{
    CSL_Status           status;

    status = GPT_close(hGpt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  configTimer(GPT_Config gptConfig, unsigned short gptInstance)
 *
 *      Configure the Timers parameters for the given timer.
 *
 *      CSL_Config gptConfig  <- Timer configurations
 *      unsigned short timerInstance   <- Timers instance number (0 to 2)
 */
int TimerClass::configTimer(GPT_Config     gptConfig,
                            unsigned short gptInstance)
{
    CSL_Status           status;

    status = CSL_ESYS_FAIL;

    if(&gptConfig != NULL)
	{
	    hGpt = &gptObj[gptInstance];

		status = configTimer(gptConfig);
		if(status != CSL_SOK)
		{
		    Timer.handleErrors(status);
		}
	}
	else
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  initialize(long period, unsigned short gptInstance)
 *
 *      Set the given period for the selected timer.
 *
 *      long int period  <- Timer period
 *      unsigned short timerInstance   <- Timers instance number (0 to 2)
 */
void TimerClass::initialize(long           period,
                            unsigned short gptInstance)
{
    hGpt = &gptObj[gptInstance];

    initialize(period);

    return;
}

/**
 *
 *  setPeriod(long period, unsigned short gptInstance)
 *
 *      Set the given period for the selected timer.
 *
 *      long period  <- Timer period
 *      unsigned short timerInstance   <- Timers instance number (0 to 2)
 */
void TimerClass::setPeriod(long           period,
                           unsigned short gptInstance)
{
    hGpt = &gptObj[gptInstance];

    setPeriod(period);

    return;
}

/**
 *
 *  start(unsigned short gptInstance)
 *
 *      Starts to load value from period register to
 *      count down register.
 *
 *      unsigned short timerInstance   <- Timers instance number (0 to 2)
 *
 */
void TimerClass::start(unsigned short gptInstance)
{
	hGpt = &gptObj[gptInstance];

    start();

    return;
}

/**
 *
 *  stop(unsigned short gptInstance)
 *
 *      Stops loading from period register to
 *      count down register.
 *
 *      unsigned short timerInstance   <- Timers instance number (0 to 2)
 */
void TimerClass::stop(unsigned short gptInstance)
{
	hGpt = &gptObj[gptInstance];

    stop();

    return;
}

/**
 *
 *  read(unsigned short gptInstance)
 *
 *      Returns timer count value read from the timer.
 *
 *      unsigned short timerInstance   <- Timers instance number (0 to 2)
 */
unsigned long TimerClass::read(unsigned short gptInstance)
{
    CSL_Status     status;
    unsigned long  timeCnt;

	hGpt = &gptObj[gptInstance];

    status = GPT_getCnt(hGpt, &timeCnt);

    if(status != CSL_SOK)
    {
        Timer.handleErrors(status);
    }

    return timeCnt;
}

/**
 *
 *  close(unsigned short gptInstance)
 *
 *      Closes the specified handle of GPT
 *
 *      unsigned short timerInstance   <- Timers instance number (0 to 2)
 */
int TimerClass::close(unsigned short gptInstance)
{
    CSL_Status status;

    status = close();
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  setWdt(WDTIM_Instance wdtInstance, WDT_Config config)
 *
 *      Configure the Watchdog Timer's parameters for the given instance.
 *
 *      WDTIM_Instance wdtInstance  <- Watchdog timer instance
 *      WDT_Config config           <- Watchdog timer configurations
 */
int TimerClass::setWdt(unsigned short wdtInstance, WDT_Config wdtConfig)
{
    CSL_Status           status;
	WDTIM_Config         wdtimConfig;

    status = CSL_ESYS_FAIL;

    hWdt = WDTIM_open((WDT_Instance)wdtInstance, &wdtObj, &status);

    if((status == CSL_SOK) && (&wdtConfig != NULL))
    {
        wdtimConfig.counter  = wdtConfig.counter;
		wdtimConfig.prescale = wdtConfig.prescale;

        status = WDTIM_config(hWdt, &wdtimConfig);
		if(status != CSL_SOK)
		{
		    Timer.handleErrors(status);
		}
    }
	else
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  serviceWdt()
 *
 *      Services watch dog timer
 */
int TimerClass::serviceWdt()
{
    CSL_Status           status;

    status = WDTIM_service(hWdt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  startWdt()
 *
 *      Starts to loading value from counter register to kick register
 */
int TimerClass::startWdt()
{
    CSL_Status           status;

    status = WDTIM_start(hWdt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  stopWdt()
 *
 *      Stops loading value from counter register to kick register
 */
int TimerClass::stopWdt()
{
    CSL_Status           status;

    status = WDTIM_stop(hWdt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  closeWdt()
 *
 *      Closes the specified handle of watchdog timer
 */
int TimerClass::closeWdt()
{
    CSL_Status           status;

    status = WDTIM_close(hWdt);
	if(status != CSL_SOK)
	{
	    Timer.handleErrors(status);
	}

    return status;
}

/**
 *
 *  closeWdt()
 *
 *      Closes the specified handle of watchdog timer
 */
void TimerClass::clearInterrupt()
{
    CSL_SYSCTRL_REGS->TIAFR |= CSL_SYSCTRL_REGS->TIAFR;
}
