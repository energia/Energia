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
/** @file Interrupt_lib.h
 *
 *  @brief Interrupt library header file
 *
 */

#ifndef _INTERRUPT_LIB_H_
#define _INTERRUPT_LIB_H_

#include "csl_intc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief  Enumeration for Interrupt Events
*/
typedef enum INTERRUPT_NUMBER
{
    INTERRUPT_RESET = 0, /**< Reset Interrupt                                */
    INTERRUPT_NMI,       /**< Non Maskable Interrupt                         */
    INTERRUPT_INT0,      /**< External User Interrupt 0                      */
    INTERRUPT_INT1,      /**< External User Interrupt 1                      */
    INTERRUPT_TINT,      /**< TIMER Interrupt                                */
    INTERRUPT_PROG0,     /**< Programmable transmit Interrupt 0 (I2S0 Tx or
                              MMC/SD0 Interrupt)                             */
    INTERRUPT_UART,      /**< UART Interrupt                                 */
    INTERRUPT_PROG1,     /**< Programmable Receive Interrupt 0 (I2S0 Rx or
                              MMC/SD0 SDIO Interrupt)                        */
    INTERRUPT_DMA,       /**< DMA Interrupt                                  */
    INTERRUPT_PROG2,     /**< Programmable transmit Interrupt 1 (I2S1 Tx or
                              MMC/SD1 Interrupt)                             */
    INTERRUPT_CoProc,    /**< CoProcessor Interrupt                          */
    INTERRUPT_PROG3,     /**< Programmable Receive Interrupt 1 (I2S1 Rx or
                              MMC/SD1 SDIO Interrupt)                        */
    INTERRUPT_LCD,       /**< LCD Interrupt                                  */
    INTERRUPT_SAR,       /**< SAR Interrupt                                  */
    INTERRUPT_XMT2,      /**< I2S2 Transmit Interrupt                        */
    INTERRUPT_RCV2,      /**< I2S2 Receive Interrupt                         */
    INTERRUPT_XMT3,      /**< I2S3 Transmit Interrupt                        */
    INTERRUPT_RCV3,      /**< I2S3 Receive Interrupt                         */
    INTERRUPT_RTC,       /**< Wakeup or RTC Interrupt                        */
    INTERRUPT_SPI,       /**< SPI Interrupt                                  */
    INTERRUPT_USB,       /**< USB Interrupt                                  */
    INTERRUPT_GPIO,      /**< GPIO Interrupt                                 */
    INTERRUPT_EMIF,      /**< EMIF Interrupt                                 */
    INTERRUPT_I2C,       /**< I2C Interrupt                                  */
    INTERRUPT_BERR,      /**< Bus Error Interrupt                            */
    INTERRUPT_DLOG,      /**< Emulation Interrupt DLOG                       */
    INTERRUPT_RTOS,      /**< Emulation Interrupt RTOS                       */
    INTERRUPT_RTDXRCV,   /**< Emulation Interrupt RTDX Receive               */
    INTERRUPT_RTDXXMT,   /**< Emulation Interrupt RTDX Transmit              */
    INTERRUPT_EMUINT,    /**< Emulation monitor mode                         */
    INTERRUPT_SINT30,    /**< Software Interrupt 30                          */
    INTERRUPT_SINT31     /**< Software Interrupt 31                          */
} INTERRUPT_NUMBER;


/** \brief  ISR Prototype
*/
typedef void (*INTERRUPT_IsrPtr)(void);


/** \brief INTC dispatch structure parameters
*/
typedef struct
{
   INTERRUPT_IsrPtr funcAddr; /**< ISR Function Address       */
   Uint32 funcArg;            /**< Arguments for ISR function */
   Uint32 ierMask;            /**< IER Interrupt CPU Register */
   Uint32 cacheCtrl;          /**< cacheCtrl                  */
} INTERRUPT_DispatchTable;

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
                      int              mode);

/**
 *
 *  detachInterrupt(intNumber)
 *
 *  API to detach a Particular interrupt from its ISR
 *      int intNumber       <- Interrupt Number
 */
void detachInterrupt (INTERRUPT_NUMBER intNumber);

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
int enableInterrupt (INTERRUPT_NUMBER intNumber);

/**
 *
 *  disableInterrupt(intNumber)
 *
 *  API to disable a Particular interrupt
 *      int intNumber <- Interrupt Number
 */
int disableInterrupt (INTERRUPT_NUMBER intNumber);

/**
 *
 *  initInterrupt(dispatchTable)
 *
 *  API to Initialize the CSL Interrupt Module
 *      INTERRUPT_DispatchTable *dispatchTable <- Dispatch Table to be used
 */
int initInterrupt (INTERRUPT_DispatchTable *dispatchTable);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _INTERRUPT_LIB_H_ */
