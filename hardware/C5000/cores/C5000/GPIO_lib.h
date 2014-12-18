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
/** @file GPIO_lib.h
 *
 *  @brief GPIO library header file
 *
 */
 
#ifndef GPIO_LIB_H
#define GPIO_LIB_H

#include "tistdtypes.h"
#include "csl_gpio.h"
#include "csl_sysctrl.h"
#include "core.h"

/** Macro for GPIO input */
#define INPUT      (0)
/** Macro for GPIO output */
#define OUTPUT     (1)
/** Macro for GPIO low */
#define LOW        (0)
/** Macro for GPIO high */
#define HIGH       (1)
/** Macro for GPIO pin 0 */
#define DSP_GPIO0  (0x00)
/** Macro for GPIO pin 1 */
#define DSP_GPIO1  (0x01)
/** Macro for GPIO pin 2 */
#define DSP_GPIO2  (0x02)
/** Macro for GPIO pin 3 */
#define DSP_GPIO3  (0x03)
/** Macro for GPIO pin 4 */
#define DSP_GPIO4  (0x04)
/** Macro for GPIO pin 5 */
#define DSP_GPIO5  (0x05)
/** Macro for GPIO pin 6 */
#define DSP_GPIO6  (0x06)
/** Macro for GPIO pin 7 */
#define DSP_GPIO7  (0x07)
/** Macro for GPIO pin 8 */
#define DSP_GPIO8  (0x08)
/** Macro for GPIO pin 9 */
#define DSP_GPIO9  (0x09)
/** Macro for GPIO pin 10 */
#define DSP_GPIO10 (0x0A)
/** Macro for GPIO pin 11 */
#define DSP_GPIO11 (0x0B)
/** Macro for GPIO pin 12 */
#define DSP_GPIO12 (0x0C)
/** Macro for GPIO pin 13 */
#define DSP_GPIO13 (0x0D)
/** Macro for GPIO pin 14 */
#define DSP_GPIO14 (0x0E)
/** Macro for GPIO pin 15 */
#define DSP_GPIO15 (0x0F)
/** Macro for GPIO pin 16 */
#define DSP_GPIO16 (0x10)
/** Macro for GPIO pin 17 */
#define DSP_GPIO17 (0x11)
/** Macro for GPIO pin 18 */
#define DSP_GPIO18 (0x12)
/** Macro for GPIO pin 19 */
#define DSP_GPIO19 (0x13)
/** Macro for GPIO pin 20 */
#define DSP_GPIO20 (0x14)
/** Macro for GPIO pin 21 */
#define DSP_GPIO21 (0x15)
/** Macro for GPIO pin 22 */
#define DSP_GPIO22 (0x16)
/** Macro for GPIO pin 23 */
#define DSP_GPIO23 (0x17)
/** Macro for GPIO pin 24 */
#define DSP_GPIO24 (0x18)
/** Macro for GPIO pin 25 */
#define DSP_GPIO25 (0x19)
/** Macro for GPIO pin 26 */
#define DSP_GPIO26 (0x1A)
/** Macro for GPIO pin 27 */
#define DSP_GPIO27 (0x1B)
/** Macro for GPIO pin 28 */
#define DSP_GPIO28 (0x1C)
/** Macro for GPIO pin 29 */
#define DSP_GPIO29 (0x1D)
/** Macro for GPIO pin 30 */
#define DSP_GPIO30 (0x1E)
/** Macro for GPIO pin 31 */
#define DSP_GPIO31 (0x1F)

/**
 *
 *  gpioHandleErrors(status)
 *
 *      Handle errors returned by CSL APIs.
 *
 */
void gpioHandleErrors(int status);

/**
 *
 *  gpioOpen()
 *
 *      Initialize GPIO Module.
 *
 */
int  gpioOpen();

/**
 *
 *  gpioSelectMode(pinNumber)
 *
 *      Configure the GPIO "mode" to be set in EBSR register.
 *
 *  32 GPIO pins available are routed through serial and parallel
 *  ports using pin multiplexing. This function configures proper pin
 *  multiplexing based on GPIO pin number passed.
 *
 *      unsigned short number    <- GPIO number
 */
int  gpioSelectMode(unsigned short pinNumber);

/**
 *
 *  gpioGetDirection(pinNumber)
 *
 *      Returns 0 if the GPIO "pinNumber" is input pin or 1 if it is
 *      an output pin.
 *
 *      int   <- GPIO number
 *
 *      Returns: unsigned short readVal -> 0 : GPIO pin is configured to input
 *                                         1 : GPIO pin is configured to output
 *                                         2 : If the GPIO configuration is not
 *                                             successfull
 */
int  gpioGetDirection(int pinNumber);

/**
 *
 *  gpioPinMode(pinNumber, direction)
 *
 *      Configure the GPIO "number" to input or output.
 *
 *      unsigned short number    <- GPIO number
 *      unsigned short direction <- 0 : Set GPIO as Input
 *                          1 : Set GPIO as Output
 */
int  gpioPinMode(unsigned short pinNumber, unsigned short direction);

/**
 *
 *  gpioWrite(pinNumber, gpioState)
 *
 *      Sets the GPIO "pinNumber" to the high or low state. The GPIO must
 *      be an output.
 *
 *      unsigned short pinNumber   <- GPIO number
 *      unsigned short gpioState   <- 0 : GPIO output is logic low
 *                                    1 : GPIO output is logic high
 */
void gpioWrite(unsigned short pinNumber, unsigned short gpioState);

/**
 *
 *  gpioRead(pinNumber)
 *
 *      Returns 0 if the GPIO "pinNumber" is in the low state or 1 if it is
 *      in the high state.
 *
 *      int pinNumber   <- GPIO number
 *
 *      Returns: unsigned short readVal -> 0 : Input to the GPIO is logic low
 *                                         1 : Input to the GPIO is logic high
 *                                         2 : If the GPIO read is not
 *                                             successfull
 */
int  gpioRead(int pinNumber);

#endif   /* GPIO_LIB_H */
