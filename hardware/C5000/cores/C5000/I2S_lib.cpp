//TI DSP Shield I2S Library.
//////////////////////////////////////////////////////////////////////////////
// * File name: I2S_lib.cpp
// *
// * Description:  I2S implementation.
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

/** @file I2S_lib.cpp
 *
 *  @brief I2S implementation
 *
 */

#include "I2S_lib.h"
#ifdef SERIAL
#include <Serial_lib.h>
#endif


/**
 * Global Class object, that can be used by User Applications to access I2S
 * module
 */
I2SClass I2S;

/** I2S handle */
CSL_I2sHandle hI2s;

/** ===========================================================================
 *   @n@b init()
 *
 *   @b Description
 *   @n Function initializes I2S Module.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
int I2SClass::init(void)
{
    I2S_Config hwConfig;
    CSL_Status status = CSL_ESYS_FAIL;

#ifdef SERIAL
	Serial.print("\n I2S init!\n");
#endif

    /* Open the device with instance 2 (AIC3206 is connected to I2S2 on DSP shield) */
    hI2s = I2S_open(I2S_INSTANCE2, DMA_INTERRUPT, I2S_CHAN_STEREO);
    if(NULL == hI2s)
    {
        this->handleErrors(CSL_ESYS_FAIL);
#ifdef SERIAL
        Serial.print("\n I2S open failed! \n");
#endif
    }
	else
    {
		/* Configure I2S signals, multiplexed parallel port pins using EBSR */
		status = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_1);
		if(status != CSL_SOK)
		{
			this->handleErrors(status);
#ifdef SERIAL
			Serial.print("\n EBSR setting fail \n");
#endif
		}
		else
		{
			/* Set the value for the configure structure */
			hwConfig.dataFormat     = I2S_DATAFORMAT_LJUST;
			hwConfig.dataType       = I2S_STEREO_ENABLE;
			hwConfig.loopBackMode   = I2S_LOOPBACK_DISABLE;
			hwConfig.fsPol          = I2S_FSPOL_LOW;
			hwConfig.clkPol         = I2S_RISING_EDGE;
			hwConfig.datadelay      = I2S_DATADELAY_ONEBIT;
			hwConfig.datapack       = I2S_DATAPACK_ENABLE;
			hwConfig.signext        = I2S_SIGNEXT_DISABLE;
			hwConfig.wordLen        = I2S_WORDLEN_16;
			hwConfig.i2sMode        = I2S_SLAVE;
			hwConfig.clkDiv         = I2S_CLKDIV2; // don't care for slave mode
			hwConfig.fsDiv          = I2S_FSDIV32; // don't care for slave mode
			hwConfig.FError         = I2S_FSERROR_DISABLE;
			hwConfig.OuError        = I2S_OUERROR_DISABLE;

			/* Configure hardware registers */
			status = I2S_setup(hI2s, &hwConfig);
			if(status != CSL_SOK)
			{
				this->handleErrors(status);
#ifdef SERIAL
				Serial.print("\n I2S setup failed");
#endif
			}
		}
	}

	return (status);
}

/** ===========================================================================
 *   @n@b enable
 *
 *   @b Description
 *   @n Function Enables I2S transfer.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void I2SClass::enable(void)
{
    CSL_Status status;

    status = I2S_transEnable(hI2s, TRUE);
	if(status != CSL_SOK)
	{
	    I2SClass::handleErrors(status);
#ifdef SERIAL
        Serial.print("\n I2S enable failed");
#endif
	}
}


/** ===========================================================================
 *   @n@b close
 *
 *   @b Description
 *   @n Function Disables I2S transfer and closes handle.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
int I2SClass::close(void)
{
    CSL_Status status;

    /* Disable I2S module */
    status = I2S_transEnable(hI2s, FALSE);
	if(status == CSL_SOK)
	{
	    status = I2S_close(hI2s);
	}

	return (status);
}

/** ===========================================================================
 *   @n@b handleErrors(status)
 *
 *   @b Description
 *   @n Handles errors returned by CSL APIs
 *
 *   @b Arguments
 *   @verbatim
 *       CSL_Status status  <- return status of the CSL_API
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void I2SClass::handleErrors(CSL_Status status)
{

}
