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
/** @file SAR.cpp
 *
 *  @brief SAR implementation
 *
 */
 
#include <core.h>
#include <SAR.h>

/** Defining the SAR Class global Member */
CSL_SarHandleObj SAR_Class::sarObject;

/** Defining a global SAR Class Object which can be used by the User
    Application */
SAR_Class SAR;

/** Macro to enable the Print messages to be displayed on the Serial */
//#define ENABLE_SERIAL_MSGS

#ifdef ENABLE_SERIAL_MSGS
#include <Serial_lib.h>
#endif

/** ===========================================================================
 *   @n@b SAR_LOG_MSG_PRINT()
 *
 *   @b Description
 *   @n API to display debug messages
 *
 *   @b Arguments
 *   @verbatim
        printString - String to be displayed
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void SAR_LOG_MSG_PRINT (char *printString);

/** ===========================================================================
 *   @n@b SAR_LOG_MSG_PRINT()
 *
 *   @b Description
 *   @n API to display debug messages
 *
 *   @b Arguments
 *   @verbatim
        integer - Integer to be displayed
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void SAR_LOG_MSG_PRINT (int integer);

/** ===========================================================================
 *   @n@b begin()
 *
 *   @b Description
 *   @n API to Initialize the SAR Module
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                  CSL_SOK            - SAR init successful
 *   @li                  CSL_ESYS_INVPARAMS - Invalid parameters
 *
 *  ===========================================================================
 */
int SAR_Class::begin()
{
    CSL_Status status;

    status = SAR_init();
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("begin(): SAR Init Failed\r\n");
    }

    return ((int)status);
}

/** ===========================================================================
 *   @n@b end()
 *
 *   @b Description
 *   @n API to Close and De-initialize the SAR Module
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                  CSL_SOK            - SAR close successful
 *   @li                  CSL_ESYS_INVPARAMS - Invalid parameters
 *
 *  ===========================================================================
 */
int SAR_Class::end()
{
    CSL_Status status;

    status = SAR_chanClose(&(this->sarObject));
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("end(): SAR_chanClose Failed\r\n");
    }
    else
    {
        status = SAR_deInit();
        if (CSL_SOK != status)
        {
            SAR_LOG_MSG_PRINT("end(): SAR_deInit Failed\r\n");
        }
    }

    return ((int)status);
}

/** ===========================================================================
 *   @n@b configChannel()
 *
 *   @b Description
 *   @n API to Configure the SAR module
 *
 *   @b Arguments
 *   @verbatim
        opmode     - SAR Operation Mode
        chanNum    - Channel Number to configure
        conversion - Conversion mode used to configure the SAR
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                  CSL_SOK            - SAR Config successful
 *   @li                  CSL_ESYS_INVPARAMS - Invalid parameters
 *
 *  ===========================================================================
 */
int SAR_Class::configChannel(int opmode, int chanNum, int conversion)
{
    CSL_Status     status;
    SAR_Handle     sarHandle;
    CSL_SarChSetup param;
    int            chanNo;

    if ((SAR_POLL_MODE != opmode) &&
        (SAR_INTERRUPT_MODE != opmode) &&
        (SAR_DMA_MODE != opmode))
    {
        SAR_LOG_MSG_PRINT("configChannel(): Invalid Operation Mode\r\n");
        return ((int)CSL_ESYS_INVPARAMS);
    }

    if ((chanNum < SAR_CHANNEL0) || (chanNum > SAR_CHANNEL5))
    {
        SAR_LOG_MSG_PRINT("configChannel(): Invalid Channel Number\r\n");
        return ((int)CSL_ESYS_INVPARAMS);
    }

    if ((SAR_CONTINUOUS_CONVERSION != conversion) &&
        (SAR_SINGLE_CONVERSION != conversion))
    {
        SAR_LOG_MSG_PRINT("configChannel(): Invalid Conversion Mode\r\n");
        return ((int)CSL_ESYS_INVPARAMS);
    }

    sarHandle = &(this->sarObject);

    status = SAR_chanOpen(sarHandle, (CSL_SarChanSel)chanNum);
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("configChannel(): SAR_chanOpen Failed\r\n");
        return ((int)status);
    }

    status = SAR_chanInit(sarHandle);
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("configChannel(): SAR_chanInit Failed\r\n");
        return ((int)status);
    }

    param.OpMode     = (CSL_SarOpMode)opmode;
    param.MultiCh    = CSL_SAR_NO_DISCHARGE;
    param.RefVoltage = CSL_SAR_REF_VIN;
    param.SysClkDiv  = 0x0b;

    status = SAR_chanSetup(sarHandle, &param);
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("configChannel(): SAR_chanConfig Failed\r\n");
        return ((int)status);
    }

    status = SAR_chanCycSet(sarHandle, (CSL_SarChanCyc)conversion);
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("configChannel(): SAR_chanCycSet Failed\r\n");
        return ((int)status);
    }

    status = SAR_A2DMeasParamSet(sarHandle,
                                 CSL_KEYPAD_MEAS,
                                 (CSL_SarChanSel *)&chanNo);
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("configChannel(): SAR_A2DMeasParamSet Failed\r\n");
        return ((int)status);
    }

    SAR_LOG_MSG_PRINT("configChannel(): Channel Number selected: ");
    SAR_LOG_MSG_PRINT(chanNo);
    SAR_LOG_MSG_PRINT("\r\n");

    return ((int)status);
}

/** ===========================================================================
 *   @n@b startConversion()
 *
 *   @b Description
 *   @n API to Start the ADC conversion
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                  CSL_SOK            - SAR Conversion Start successful
 *   @li                  CSL_ESYS_INVPARAMS - Invalid parameters
 *
 *  ===========================================================================
 */
int SAR_Class::startConversion()
{
    CSL_Status status;

    status = SAR_startConversion (&(this->sarObject));
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("startConversion(): SAR_startConversion Failed\r\n");
    }

    return ((int)status);
}

/** ===========================================================================
 *   @n@b stopConversion()
 *
 *   @b Description
 *   @n API to Stop the ADC conversion
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                  CSL_SOK            - SAR Conversion Stop successful
 *   @li                  CSL_ESYS_INVPARAMS - Invalid parameters
 *
 *  ===========================================================================
 */
int SAR_Class::stopConversion()
{
    CSL_Status status;

    status = SAR_stopConversion(&(this->sarObject));
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("stopConversion(): SAR_stopConversion Failed\r\n");
    }

    return ((int)status);
}

/** ===========================================================================
 *   @n@b getStatus()
 *
 *   @b Description
 *   @n API to read the status of the ADC conversion
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                  TRUE  - If Conversion is Complete
 *   @li                  FALSE - If Conversion is Pending
 *
 *  ===========================================================================
 */
Bool SAR_Class::getStatus()
{
    Bool       retValue;
    CSL_Status status;

    retValue = (Bool)SAR_getStatus (&(this->sarObject), &status);
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("getStatus(): SAR_getStatus Failed\r\n");
        retValue = FALSE;
    }

    return (retValue);
}

/** ===========================================================================
 *   @n@b readData()
 *
 *   @b Description
 *   @n API to read the digtal data converted by the SAR module
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                  The converted Digital data
 *
 *  ===========================================================================
 */
unsigned int SAR_Class::readData()
{
    CSL_Status status;
    Uint16     readBuffer;

    status = SAR_readData(&(this->sarObject), &readBuffer);
    if (CSL_SOK != status)
    {
        SAR_LOG_MSG_PRINT("readData(): SAR_readData Failed\r\n");
        readBuffer = 0;
    }

    return ((unsigned int)readBuffer);
}

/** ===========================================================================
 *   @n@b SAR_LOG_MSG_PRINT()
 *
 *   @b Description
 *   @n API to display debug messages
 *
 *   @b Arguments
 *   @verbatim
        printString - String to be displayed
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void SAR_LOG_MSG_PRINT (char *printString)
{
#ifdef ENABLE_SERIAL_MSGS
    Serial.print(printString);
#else
    printf("%s", printString);
#endif
}

/** ===========================================================================
 *   @n@b SAR_LOG_MSG_PRINT()
 *
 *   @b Description
 *   @n API to display debug messages
 *
 *   @b Arguments
 *   @verbatim
        integer - Integer to be displayed
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void SAR_LOG_MSG_PRINT (int integer)
{
#ifdef ENABLE_SERIAL_MSGS
    Serial.print((long)integer);
#else
    printf("%d", integer);
#endif
}
