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
/** @file FFT.h
 *
 *  @brief FFT library header file
 *
 */

#ifndef _FFT_H_
#define _FFT_H_

#include "tistdtypes.h"
#include "dsplib.h"
#include "core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Fast Fourier Transform for real inputs                   */
#define FFT_REAL                 (0)
/** Fast Fourier Transform for complex inputs                */
#define FFT_COMPLEX              (1)
/** Fast Fourier Transform for 16 bit inputs in Q15 format   */
#define FFTQ15                   (0)
/** Fast Fourier Transform for 32 bit inputs in Q31 format   */
#define FFTQ31                   (1)
/** Parameters are invalid                                   */
#define FFT_BAD_PARAMS           (-1)
/** Fast Fourier Transform is successful                     */
#define FFT_SUCCESS              (0)
/** Mask required to convert a 32 bit value to 16 bit        */
#define CONVERT_32_TO_16_MASK    (0x0000FFFF)
/** Shift required to convert a 32 bit value to 16 bit       */
#define CONVERT_32_TO_16_SHIFT   (16)
/** Shift required to convert a 32 bit value to Q15 format   */
#define Q15_MULT_SHIFT           (15)
/** Scaling is enabled                                       */
#define ENABLE_SCALE             (1)
/** Scaling is disabled                                       */
#define DISABLE_SCALE            (0)

/**
 * \brief FFT Class
 *
 *  Contains prototypes for functions in FFT library
 */
class FFTClass {
    public:
       void FFT_init(void);
       void FFT_filter(short *input, short *output, short *overlap, int length);
};

extern FFTClass FFTransform;
/**< FFT class instance extern which can used by application programs
 *   to access FFT DSP APIs
 */

#ifdef __cplusplus
}
#endif

#endif //_FFT_H_

