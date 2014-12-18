//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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
/** @file Timers.h
 *
 *  @brief Timers library header file
 *
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include "core.h"
#include "csl_gpt.h"
#include "csl_wdt.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************\
          Timer global macro declarations
\*****************************************************************************/

/** Timer instace 0						*/
#define	GPT0    (0)
/** Timer instace 1						*/
#define	GPT1    (1)
/** Timer instace 2						*/
#define	GPT2    (2)
/** Timer instace count					*/
#define	TIMER_INSTANCE_COUNT    (3)

/** Pre scale Divide input clock by 2	    */
#define	GPT_PRE_SC_DIV_0     (0)
/** Pre scale Divide input clock by 4		*/
#define	GPT_PRE_SC_DIV_1     (1)
/** Pre scale Divide input clock by 8		*/
#define	GPT_PRE_SC_DIV_2     (2)
/** Pre scale Divide input clock by 16		*/
#define	GPT_PRE_SC_DIV_3     (3)
/** Pre scale Divide input clock by 32		*/
#define	GPT_PRE_SC_DIV_4     (4)
/** Pre scale Divide input clock by 64		*/
#define	GPT_PRE_SC_DIV_5     (5)
/** Pre scale Divide input clock by 128	*/
#define	GPT_PRE_SC_DIV_6     (6)
/** Pre scale Divide input clock by 256	*/
#define	GPT_PRE_SC_DIV_7     (7)
/** Pre scale Divide input clock by 512	*/
#define	GPT_PRE_SC_DIV_8     (8)
/** Pre scale Divide input clock by 1024	*/
#define	GPT_PRE_SC_DIV_9     (9)
/** Pre scale Divide input clock by 2048	*/
#define	GPT_PRE_SC_DIV_10    (10)
/** Pre scale Divide input clock by 4096	*/
#define	GPT_PRE_SC_DIV_11    (11)
/** Pre scale Divide input clock by 8192	*/
#define	GPT_PRE_SC_DIV_12    (12)
/** Mask for upper word of a 32bit value */
#define HIGH_WORD_MASK     (0xFFFF0000)
/** Mask for lower word of a 32bit value */
#define LOW_WORD_MASK      (0x0000FFFF)
/** Length of a word */
#define WORD_LENGTH        (16)

/**
 * \brief Configuration structure.
 *
 * Contains the Information of a GPT configuration.
 */
typedef struct{
	Bool        	autoLoad;      /**< Auto reload						*/
	unsigned short	preScaleDiv;   /**< Prescale division				*/
	Bool        	ctrlTim;       /**< control timer					*/
	unsigned short	prdLow;        /**< period low						*/
	unsigned short	prdHigh;       /**< period high						*/
}GPT_Config;

/**
 *   \brief Configuration structure.
 *
 *   Hardware register configuration structure for WDT
 */
typedef struct {
	unsigned short	counter;       /**< Counter value for the WDT         */
	unsigned short	prescale;	   /**< Prescale value for the WDT        */
}WDT_Config;

/**
 * \brief Timers Class
 *
 *  Contains prototypes for functions in Timers DSP API library
 */
class TimerClass {
    private:
	    void handleErrors(int status);
	public:
		int  selectTimer(unsigned short	gptInstance);
        int  configTimer(GPT_Config gptConfig);
		int  configTimer(GPT_Config gptConfig, unsigned short gptInstance);
		void initialize(long period);
		void initialize(long period, unsigned short gptInstance);
		void setPeriod(long period);
		void setPeriod(long period, unsigned short gptInstance);
		unsigned long read();
		unsigned long read(unsigned short gptInstance);
		void start();
		void start(unsigned short gptInstance);
		void stop();
		void stop(unsigned short gptInstance);
		int  close();
		int  close(unsigned short gptInstance);
		int  setWdt(unsigned short wdtInstance, WDT_Config wdtConfig);
		int  serviceWdt();
		int  startWdt();
		int  stopWdt();
		int  closeWdt();
		void clearInterrupt();
};

extern TimerClass Timer;
/**< Timers class instance extern which can be used by application programs
 *   to access Timers DSP APIs
 */

#ifdef __cplusplus
}
#endif

#endif //_TIMER_H_
