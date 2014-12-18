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

/** @file Interrupt_lib.cpp
 *
 *  @brief Interrupt implementation
 *
 */

#include "Interrupt_lib.h"

/** Extern of VECSTART function */
extern "C" void VECSTART(void);

/**
 *
 *  initInterrupt(dispatchTable)
 *
 *  API to Initialize the CSL Interrupt Module
 *      INTERRUPT_DispatchTable *dispatchTable <- Dispatch Table to be used
 */
int initInterrupt (INTERRUPT_DispatchTable *dispatchTable)
{
	return (IRQ_init((CSL_IRQ_Dispatch *)dispatchTable, 0));
}

/**
 *
 *  attachInterrupt(intNumber, function, mode)
 *
 *  API to attach an ISR for a particular Interrupt
 *      int intNumber             <- Interrupt Number
 *      INTERRUPT_IsrPtr function <-- Address of the ISR Function
 *      int mode                  <-- Mode to indicate the Priority
 */
void attachInterrupt (INTERRUPT_NUMBER intNumber,
                      INTERRUPT_IsrPtr function,
                      int              mode)
{
    IRQ_globalDisable();

	IRQ_clearAll();

	//IRQ_disableAll();

    /* Set the Vector API address, which fetches the address of the ISRs of
       the corresponding interrupts */
    IRQ_setVecs((Uint32)(&VECSTART));
	IRQ_clear((int)intNumber);

	IRQ_plug ((int)intNumber, (IRQ_IsrPtr)function);

	IRQ_enable((int)intNumber);
	IRQ_globalEnable();
}

/**
 *
 *  detachInterrupt(intNumber)
 *
 *  API to detach a Particular interrupt from its ISR
 *      int intNumber       <- Interrupt Number
 */
void detachInterrupt (INTERRUPT_NUMBER intNumber)
{
    CSL_IRQ_Config irqConfig;

	/* Setting Null pointer as the ISR address */
	irqConfig.funcAddr  = (IRQ_IsrPtr)0x0000;
    irqConfig.funcArg   = 0;
    irqConfig.ierMask   = 0;
    irqConfig.cacheCtrl = 0;

    IRQ_config((int)intNumber, &irqConfig);
}

/**
 *
 *  enableInterrupt(intNumber)
 *
 *  API to enable a Particular interrupt
 *      int intNumber  <- Interrupt Number
 *
 *  attachInterrupt() API should have already been called, before calling this
 *  API
 */
int enableInterrupt (INTERRUPT_NUMBER intNumber)
{
    int  retStatus;

    retStatus  = IRQ_globalDisable();
    retStatus |= IRQ_clear((int)intNumber);
    retStatus |= IRQ_enable((int)intNumber);
    retStatus |= IRQ_globalEnable();

	return (retStatus);
}

/**
 *
 *  disableInterrupt(intNumber)
 *
 *  API to disable a Particular interrupt
 *      int intNumber <- Interrupt Number
 */
int disableInterrupt (INTERRUPT_NUMBER intNumber)
{
	return (IRQ_disable((int)intNumber));
}
