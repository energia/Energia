//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2010 Spectrum Digital, Incorporated
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

/** @file core.h (was ezdsp5535.h)
 *
 *  @brief Board definitions.
 *
 */

#ifndef CORE_
#define CORE_

#include "tistdtypes.h"
#include "soc.h"
#include "board_mode.h"
#include "pins_dspshield.h"
#include "cslr_sysctrl.h"
#include "boot_update.h"
#include "tistdtypes.h"
#include "csl_rtc.h"
#include "csl_sar.h"
#include "AnalogReadWrite_lib.h"
#include "DigitalReadWrite_lib.h"
#include "GPIO_lib.h"
#include "DMA_lib.h"
#include "I2S_lib.h"
#include "Interrupt_lib.h"
#include "Serial_lib.h"
#include "Wire_lib.h"

/** Macro for software breakpoint */
#define SW_BREAKPOINT      while(1);

#ifndef C5000_h
/** Macro to define C5000 architecture */
#define C5000_h

/** Energia setup function prototype */
void setup();
/** Energia init function prototype */
void init();
/** Energia loop function prototype */
void loop();
#endif

#ifdef __cplusplus
extern "C" {
#endif

//#define ENABLE_DEBUG_MSG

#ifdef ENABLE_DEBUG_MSG

#define DBG_MSG_PRINT   Serial.print

#else
/** Macro for printing debug messages */
#define DBG_MSG_PRINT(msg);

#endif

/** Macro to indicate that a pin/bit value is zero(low) */
#define LOW (0)
/** Macro to indicate that a pin/bit value is one(high) */
#define HIGH (1)

/** PLL clock sorce value                                                    */
#define PLL_SRC_CLKIN  (12000000u)
/** PLL RTC   sorce value                                                    */
#define PLL_SRC_RTCIN  (32768u)

/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
/* Board Initialization */
Int16 csl_init( );

/* Wait Functions */
void csl_wait(Uint32 delay);
void csl_waitusec(Uint32 usec);
void delay(Uint32 msecs);

void xfOn();
void xfOff();
Int16 ioExpander_Setup(void);
Int16 ioExpander_Write(Uint16 port, Uint16 pin, Uint16 value);
Int16 ioExpander_Read(Uint16 port, Uint16 pin, Uint16 *rValue);
void boot_update();
CSL_Status RTC_getAlarm (CSL_RtcAlarm     *pGetRtcAlarm);

void SPI_setLoopBackMode(int value);

void* createBuffer(unsigned short size);
void deleteBuffer(void *buf);

void delayMicroseconds(Uint32 usecs);
void delayMilliseconds(Uint32 msecs);
void delaySeconds(Uint32 sec);

void setSarGPODir(CSL_SarHandleObj *SarHandle,
                  int              gpoPinNumber,
                  int              direction);
void setSarGPOValue(CSL_SarHandleObj *SarHandle,
                    int              gpoPinNumber,
                    int              value);

Int16 setSarA2DMeasParam (SAR_Handle       hSar,
                          CSL_SARMeasParam param,
                          CSL_SarChanSel   chanNo);
void copyShortBuf(void *input, void *output, unsigned short size);
void copyLongBuf(void *input, void *output, unsigned short size);
void fillShortBuf(void *buf, int value, unsigned short size);
void fillLongBuf(void *buf, long value, unsigned short size);

unsigned long getCpuClock();

#ifdef __cplusplus
}
#endif
#endif

