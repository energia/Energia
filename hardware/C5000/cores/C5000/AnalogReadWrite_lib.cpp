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

/** @file AnalogReadWrite_lib.cpp
 *
 *  @brief Analog Read/Write Module implementation
 *
 */

#include "AnalogReadWrite_lib.h"
#include <stdio.h>
#include <string.h>

/** Global SAR Object */
CSL_SarHandleObj SarObj;

/**
 *
 *  analogRW_handleErrors(status)
 *
 *      Handle errors returned by CSL APIs.
 *
 *      int status <- Error Status
 *
 */
static void analogRW_handleErrors (int status)
{

}

/**
 *
 *  analog_SarInit(SarHandle, chanNo)
 *
 *      Initialize and Configure a particular SAR Channel.
 *
 *      CSL_SarHandleObj *SarHandle <- SAR instance Handle
 *      CSL_SarChanSel chanNo       <- Channel number
 */
static CSL_Status analog_SarInit(CSL_SarHandleObj *SarHandle,
                                 CSL_SarChanSel   chanNo)
{
    CSL_Status       status;
    CSL_SarChSetup   param;

    status = SAR_init();
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
        return (status);
    }

    status = SAR_chanOpen(SarHandle, chanNo);
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
        return (status);
    }

    status = SAR_chanInit(SarHandle);
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
        return (status);
    }

    param.OpMode     = CSL_SAR_POLLING;
    param.MultiCh    = CSL_SAR_NO_DISCHARGE;
    param.RefVoltage = CSL_SAR_REF_VIN;
    param.SysClkDiv  = 0x0B ;
    status = SAR_chanSetup(SarHandle, &param);
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
        return (status);
    }

    status = SAR_chanCycSet(SarHandle, CSL_SAR_SINGLE_CONVERSION);
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
        return (status);
    }

    status = setSarA2DMeasParam(SarHandle, CSL_KEYPAD_MEAS, chanNo);
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
    }

    return (status);
}

/**
 *
 *  analogRead(pinNumber)
 *
 *      Returns the converted Digital value or -1 on failure.
 *
 *      int pinNumber   <- GPO Pin number
 *
 *      Returns: int retAdcData -> Converted Digital value
 *                                 -1 : On Failure
 */
int analogRead (int pinNumber)
{
    CSL_Status       status;
    CSL_SarHandleObj *SarHandle;
    CSL_SarChanSel   chanNo;
    int              retAdcData;

    SarHandle = &SarObj;

    if ((A1 == pinNumber) ||
        (A2 == pinNumber) ||
        (A3 == pinNumber))
    {
        chanNo = (CSL_SarChanSel)(pinNumber + 2);
    }
    else if (A0 == pinNumber)
    {
        chanNo = (CSL_SarChanSel)pinNumber;
    }
    else
    {
        return (-1);
    }

    status = analog_SarInit(SarHandle, chanNo);
    if (CSL_SOK != status)
    {
        return (-1);
    }

    /* Start the conversion */
    status = SAR_startConversion(SarHandle);
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
        return (-1);
    }

 	/* Check whether the ADC data is available or not */
	while(CSL_SAR_DATA_AVAILABLE != SAR_getStatus(SarHandle,&status));

	status = SAR_readData(SarHandle, (Uint16 *)&retAdcData);
	if (CSL_SOK != status)
	{
		analogRW_handleErrors(status);
		return (-1);
	}

    status = SAR_chanClose(SarHandle);
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
        return (-1);
    }

    status = SAR_deInit();
    if (CSL_SOK != status)
    {
        analogRW_handleErrors(status);
        return (-1);
    }

    return (retAdcData);
}

