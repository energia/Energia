//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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
/** @file SAR.h
 *
 *  @brief SAR library header file
 *
 */

#ifndef _SAR_H_
#define _SAR_H_

#include <stdio.h>
#include "csl_sar.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SAR_POLL_MODE      (0)
/**< Macro to indicate the mode of SAR as Polled Mode    */
#define SAR_INTERRUPT_MODE (1)
/**< Macro to indicate the mode of SAR as Interrupt Mode */
#define SAR_DMA_MODE       (2)
/**< Macro to indicate the mode of SAR as DMA Mode       */

#define SAR_CHANNEL0 (0)
/**< Macro to indicate Channel No 0 for SAR */
#define SAR_CHANNEL1 (1)
/**< Macro to indicate Channel No 1 for SAR */
#define SAR_CHANNEL2 (2)
/**< Macro to indicate Channel No 2 for SAR */
#define SAR_CHANNEL3 (3)
/**< Macro to indicate Channel No 3 for SAR */
#define SAR_CHANNEL4 (4)
/**< Macro to indicate Channel No 4 for SAR */
#define SAR_CHANNEL5 (5)
/**< Macro to indicate Channel No 5 for SAR */

#define SAR_CONTINUOUS_CONVERSION (0)
/**< Macro to indicate SAR to perform Continous Conversion */
#define SAR_SINGLE_CONVERSION     (1)
/**< Macro to indicate SAR to perform Single Conversion    */

/**
 * \brief SAR Class
 *
 *  Contains prototypes for functions in SAR library
 */
class SAR_Class
{
    private:
        static CSL_SarHandleObj sarObject;

    public:
        int begin();
        int end();
        int configChannel(int opmode,  int chanNum, int conversion);
        int startConversion();
        int stopConversion();
        Bool getStatus();
        unsigned int readData();
} ;

extern SAR_Class SAR;
/**< SAR class instance extern which can used by application programs
 *   to access SAR DSP APIs
 */
#ifdef __cplusplus
}
#endif

#endif /* #ifndef _SAR_H_ */
