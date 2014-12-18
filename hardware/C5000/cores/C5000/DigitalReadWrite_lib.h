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
/** @file DigitalReadWrite_lib.h
 *
 *  @brief Digital Read/Write Module header file
 *
 */
 
#ifndef DigitalReadWrite_h
#define DigitalReadWrite_h

#include "tistdtypes.h"
#include "csl_gpio.h"
#include "csl_sysctrl.h"
#include "core.h"

static Uint16 expander1_pinstatus = 0x0;
static Uint16 expander2_pinstatus = 0x0;
static Uint8 digitalWrite_exp1firstCall = 0x0; 
static Uint8 digitalWrite_exp2firstCall = 0x0; 

/**
 *
 *  handleErrors(status)
 *
 *      Handle errors returned by CSL APIs.
 *
 *      int status <- Error Status
 *
 */
void handleErrors(int status);

/**
 *
 *  pinMode(pinNumber, direction)
 *
 *      Configure the IO Expander pin as either input or output.
 *
 *      unsigned short pinNumber <- IO Expander pin number
 *      unsigned short direction <- 0 : Set IO Expander Pin as Input
 *                                  1 : Set IO Expander Pin as Output
 */
int pinMode(unsigned short pinNumber, unsigned short direction);

/**
 *
 *  digitalWrite(pinNumber, wValue)
 *
 *      Sets an IO Expander Pin to high or low state. The IO Expander Pin must
 *      be configured as output.
 *
 *      unsigned short pinNumber <- IO Expander Pin number
 *      unsigned short wValue    <- 0 : IO Expander Pin output is logic low
 *                                  1 : IO Expander Pin output is logic high
 */
int digitalWrite(unsigned short pinNumber, unsigned short wValue);

/**
 *
 *  digitalWritePort(unsigned char portNumber, unsigned char bValue)
 *
 *      Sets all 8 pins on an IO Expander port to high or low state. The IO Expander Pins affected must
 *      be configured as output to show changes.
 *
 *      unsigned char portNumber <- IO Expander Port number
 *      unsigned char bValue     <- byte containing bit flags for each of 8 pins on the port.
 *
 */
int digitalWrite_port(unsigned char portNumber, unsigned char bValue);

/**
 *
 *  digitalRead(pinNumber)
 *
 *      Returns 0 if the IO Expander Pin is in the low state and 1 if it is
 *      in the high state.
 *
 *      unsigned short pinNumber   <- IO Expander Pin number
 *
 *      Returns: unsigned int readVal -> 0 : Input to the IO Expander Pin is
 *                                           logic low
 *                                       1 : Input to the IO Expander Pin is
 *                                           logic high
 *                                       2 : If the IO Expander read is not
 *                                           successful
 */
unsigned int digitalRead(int pinNumber);

#endif
