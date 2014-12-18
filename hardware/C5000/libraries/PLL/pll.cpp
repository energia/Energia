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
/** @file pll.cpp
 *
 *  @brief PLL implementation
 *
 */
 
#include "pll.h"

/** Defining a global PLL Class Object which can be used by the User
    Application */
PLL_Class PLL;

/**
 *
 *  PLL pllClass
 *
 *  PLL Class Constructor.
 *
 */
PLL_Class::PLL_Class()
{
    int        status;
    PLL_Handle pllHandle;

    status    = -1;
    pllHandle = (PLL_Handle)&(this->pllObject);

    status = PLL_init(&pllObject, CSL_PLL_INST_0);
    if (0 == status)
    {
        status = (int)PLL_reset(pllHandle);
        if (0 != status)
        {
            pllHandle->pllConfig = 0x0000;
            pllHandle->sysAddr    = 0x0000;
        }
    }
}

/**
 *
 *  configure(&pllConfig)
 *
 *  Configure PLL
 *      PLL_Config *pConfigInfo    <- Config Structure, used to configure PLL
 */
int PLL_Class::configure (PLL_Config *pConfigInfo)
{
    int        status;
    PLL_Handle pllHandle;

    status    = -1;
    pllHandle = (PLL_Handle)&(this->pllObject);

    if (NULL != pllHandle)
    {
        status = (int)PLL_config (pllHandle, pConfigInfo);
    }

    return (status);
}

/**
 *
 *  getConfigure(&pllConfig)
 *
 *  Get PLL Configuration Values
 *      PLL_Config *pConfigInfo    <- Config Structure, used to store the PLL
 *                                    configurations
 */
int PLL_Class::getConfigure (PLL_Config *pConfigInfo)
{
    int        status;
    PLL_Handle pllHandle;

    status    = -1;
    pllHandle = (PLL_Handle)&(this->pllObject);

    if (NULL != pllHandle)
    {
        status = (int)PLL_getConfig (pllHandle, pConfigInfo);
    }

    return (status);
}

/**
 *
 *  getSystemClock()
 *
 *  Get System Clock frequency, it will return the CPU clock in terms of kHz
 */
long PLL_Class::getSystemClock ()
{
    return (getCpuClock());
}
