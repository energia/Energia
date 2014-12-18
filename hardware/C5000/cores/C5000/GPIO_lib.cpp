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

/** @file GPIO_lib.cpp
 *
 *  @brief GPIO implementation
 *
 */

#include "GPIO_lib.h"

#include <stdio.h>
#include <string.h>

/** Macro for masking pin value */
#define PINMASK (0x0001)

/** GPIO object */
CSL_GpioObj GpioObj;
/** GPIO object handle */
CSL_GpioObj *hGpio;

/**
 *
 *  gpioHandleErrors(status)
 *
 *      Handle errors returned by CSL APIs.
 *
 */
void gpioHandleErrors(int status)
{

}

/**
 *
 *  gpioOpen()
 *
 *      Initialize GPIO Module.
 *
 *  Returns '0' on success else error code
 */
int gpioOpen()
{
    CSL_Status status;

    hGpio = GPIO_open(&GpioObj, &status);
    if (CSL_SOK != status)
	{
	    handleErrors(status);
	}

    return (status);
}

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
 *
 *  Returns '0' on success else error code
 */
int gpioSelectMode(unsigned short pinNumber)
{
    CSL_Status status;

    status = CSL_ESYS_INVPARAMS;

    /* Configure the mode in EBSR depending on the GPIO pin number */
    if (pinNumber <= 5)
    {
		status = SYS_setEBSR(CSL_EBSR_FIELD_SP0MODE, CSL_EBSR_SP0MODE_2);
    }
    else if ((pinNumber >= 6) && (pinNumber <= 11))
    {
        status = SYS_setEBSR(CSL_EBSR_FIELD_SP1MODE, CSL_EBSR_SP1MODE_2);
    }
    else if ((pinNumber >= 12) && (pinNumber <= 17))
    {
        status = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_1);
	}
    else if ((pinNumber >= 18) && (pinNumber <= 31))
    {
       status = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_2);
	}

    if (CSL_SOK != status)
	{
	    handleErrors(status);
	}

    return (status);
}

/**
 *
 *  gpioPinMode(pinNumber, direction)
 *
 *      Configure the GPIO "number" to input or output.
 *
 *      unsigned short number    <- GPIO number
 *      unsigned short direction <- 0 : Set GPIO as Input
 *                          1 : Set GPIO as Output
 *
 *  Returns '0' on success else error code
 */
int gpioPinMode(unsigned short pinNumber, unsigned short direction)
{
    CSL_Status        status;
    CSL_GpioPinConfig config;

	gpioSelectMode(pinNumber);

    /* Configure the requested GPIO pin direction */
    config.pinNum    = (CSL_GpioPinNum)pinNumber;
    config.direction = (CSL_GpioDirection)direction;
    config.trigger   = CSL_GPIO_TRIG_CLEAR_EDGE;

    /* Set configuration */
    status = GPIO_configBit(hGpio,&config);
    if (CSL_SOK != status)
	{
	    handleErrors(status);
	}

    return (status);
}

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
int gpioGetDirection(int pinNumber)
{
    CSL_Status     status;
	CSL_GpioConfig gpioConfig;

    /* Get input/output directions of all GPIO pins */
    status = GPIO_getConfig(hGpio, &gpioConfig);
    if (CSL_SOK == status)
    {
        if (pinNumber < CSL_GPIO_PIN16)
		{
		    return (((gpioConfig.GPIODIRL) >> pinNumber) & PINMASK);
		}
		else
		{
		    return (((gpioConfig.GPIODIRH) >> pinNumber) & PINMASK);
		}
    }
    else
    {
	    handleErrors(status);
        return (2);
    }
}

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
int gpioRead(int pinNumber)
{
    CSL_Status     status;
    unsigned short gpioState;

    gpioState = 0;

    /* Get GPIO pin state */
    status = GPIO_read(hGpio, (CSL_GpioPinNum)pinNumber, &gpioState);
    if (CSL_SOK == status)
    {
        return gpioState;
    }
    else
    {
	    handleErrors(status);
        return (2);
    }
}

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
void gpioWrite(unsigned short pinNumber, unsigned short gpioState)
{
    CSL_Status status;

    /* Set GPIO Pin state */
    status = GPIO_write(hGpio, (CSL_GpioPinNum)pinNumber, gpioState);
    if (CSL_SOK != status)
	{
	    handleErrors(status);
	}
}
