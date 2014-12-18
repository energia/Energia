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
/** @file FFT.cpp
 *
 *  @brief FFT implementation
 *
 */

#include <stdio.h>
#include "FFT.h"

/**
 * Class identifier declaration
 */
FFTClass FFTransform;

/** Macro to enable/disable Filtering */
#define ENABLE_FILTER

#include <stdlib.h>
#include <math.h>
#include <dsplib.h>

#include "coeffdef_fft.h"

/** Buffer for FFT processing */
//#pragma DATA_ALIGN (32)
#pragma DATA_SECTION ("fft_buf")
short buf[FFTLEN*2];

/** ===========================================================================
 *   @n@b IR2FR()
 *
 *   @b Description
 *   @n API to convert samples from Real Impulse response to complex Frequency
 *      response. Real and imaginary parts are alternated
 *
 *   @b Arguments
 *   @verbatim
        ir - Input Buffer containing audio samples in Real form
        fr - Output Buffer to hold the converted audio samples in complex form
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void IR2FR(short *ir,
           short *fr)
{
	short i;
	short *ir_ptr;

	ir_ptr = ir;

	/* Arranging the data so that real and imaginary parts alternate.
	 * Zero padding the second half of the buffer
	 */
	for( i = 0; i < WINLEN; i++)
	{
		fr[2*i] = *ir_ptr++;	//real
		fr[2*i + 1] = 0;	//imag

		// zero padding
		fr[2*WINLEN + 2*i] = 0;		//real
		fr[2*WINLEN + 2*i + 1] = 0;	//imag
	}
	/* No Scale FFT to preserve the dynamic range and resolution*/
	cfft(fr, FFTLEN, NOSCALE);
	cbrev(fr, fr, FFTLEN);

}

/** ===========================================================================
 *   @n@b CPLX_Mul()
 *
 *   @b Description
 *   @n API to perform multiplication between two complex numbers
 *
 *   @b Arguments
 *   @verbatim
        op1 - First Input to be used in Complex multiplication
        op2 - Second Input to be used in Complex multiplication
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li   The product of the complex numbers, passed as inputs to this API
 *
 *  ===========================================================================
 */
long CPLX_Mul(short *op1,
              short *op2)
{
	short op1_r, op1_i, op2_r, op2_i;
	long op1_op2_r, op1_op2_i;
	short op1_op2_r16, op1_op2_i16;
	long cplx_prod;

	/* Extract the real and imag parts from the input data = (real:imag) */
	op1_r = *op1;
	op1_i = *(op1+1);
	op2_r = *op2;
	op2_i = *(op2+1);

	/* Generate the real and imag part of the product */
	op1_op2_i	= (long)op1_r*op2_i + (long)op1_i*op2_r;
	op1_op2_r	= (long)op1_r*op2_r - (long)op1_i*op2_i;

	op1_op2_i16 = (short)(op1_op2_i >> 15);
	op1_op2_r16 = (short)(op1_op2_r >> 15);

	cplx_prod = (((long)op1_op2_r16 & 0x0000FFFF)<< 16);
	cplx_prod = cplx_prod | ((long)op1_op2_i16 & 0x0000FFFF);

	return (cplx_prod);
}

/** ===========================================================================
 *   @n@b downScaleData()
 *
 *   @b Description
 *   @n API to down scale data by an amount specified by 'scale' parameter
 *
 *   @b Arguments
 *   @verbatim
        data   - Data buffer
        length - Length of data
        scale  - Scaling factor
     @endverbatim
 *
 *   <b> Return Value </b>
 *   none
 *
 *  ===========================================================================
 */
void downScaleData(short *data,
                   int   length,
                   short scale)
{
	int index;

	for (index = 0; index < length; index++)
	{
		data[index] = data[index]/scale;
	}
}

/** ===========================================================================
 *   @n@b upScaleData()
 *
 *   @b Description
 *   @n API to up scale data by an amount specified by 'scale' parameter
 *
 *   @b Arguments
 *   @verbatim
        data   - Data buffer
        length - Length of data
        scale  - Scaling factor
     @endverbatim
 *
 *   <b> Return Value </b>
 *   none
 *
 *  ===========================================================================
 */
void upScaleData(short *data,
                 int   length,
                 short scale)
{
	int index;

	for (index = 0; index < length; index++)
	{
		data[index] = scale * data[index];
	}
}

/** ===========================================================================
 *   @n@b FFT_init()
 *
 *   @b Description
 *   @n API to initialize the buffers used by the FFT algorithm
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
void FFTClass::FFT_init(void)
{

	short k;

	/* Initialize output buffer with zeroes */
	for(k = 0; k < NX; k++)
	{
		x_filter[k] = 0;
	}

	/* Converting the filter impulse response to its frequency response.
	 * FFT - NOSCALE, to maintain the dynamic range and resolution.
	 */
	IR2FR(ir, fr);
}

/** ===========================================================================
 *   @n@b FFT_filter()
 *
 *   @b Description
 *   @n API to perform FFT-filter(lpf)-IFFT on the samples passed as input
 *
 *   @b Arguments
 *   @verbatim
        input   - Buffer containing the Input samples
        output  - Buffer to hold the FFT-filtered output samples
        overlap - Buffer to hold the overlap data, which will be used in next
                  FFT-filtering
        length  - Number of input data samples
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void FFTClass::FFT_filter(short *input,
                          short *output,
                          short *overlap,
                          int   length)
{
	long  numFrames;
	short i;
	short k;
	short *x_ptr; /* pointer to keep track of input data, and output data */
	long  result;

	numFrames = length / WINLEN; /* number of frames to be processed */

	for (k = 0; k < numFrames; k++)
	{

		x_ptr = &input[k*WINLEN];

		/* Preparing the data for the FFT function. The real and imaginary
		 * parts of the signal are alternated. Since the input signal is real,
		 * the imaginary part is zero. Moreover since FFTLEN = 2*WINLEN, zero
		 * padding the input buffer.
		 */
		for( i = 0; i < WINLEN; i++)
		{
			buf[2*i] = *x_ptr++;	// real part
			buf[2*i + 1] = 0;	    // imag part

			// zero padding
			buf[2*WINLEN + 2*i] = 0;		// real part
			buf[2*WINLEN + 2*i + 1] = 0;	// imag part
		}

		/* Taking the FFT of the signal. Using the scaled version of the FFT
		   so that FFT values do not overflow. Bit-reversing the output. */
		cfft(buf, FFTLEN, SCALE);
		cbrev(buf, buf,FFTLEN);

		/* Filtering the data. Filter the data in the frequency domain is equal
		   to a complex multiplication. */

		/* Need to perform only filtering on half the spectrum, the other half
		 * of the spectrum will be generated as the complex conjugate of the
		 * first half.
		 * The FFT spectrum of a real signal satisfies the following symmetry:
		 * X(k) = complex conjugate of X(N-k)., where N  = FFTLEN, and k is the
		 * frequency index. If N is even, X(0) & X(N/2) are real valued.
		 */

		for (i = 0; i <= FFTLEN/2; i++)
		{
#ifdef ENABLE_FILTER
			// Need pointer to only real values
			result = CPLX_Mul(&buf[2*i], &fr[2*i]);

			//Splitting the 32-bit result into the real parts and imaginary parts.
			buf[2*i] = result >> 16;
			buf[2*i+1] = result & 0x0000FFFF;
#endif
			//The 0-th index and the FFTLEN/2 index are only real values.
			// 2*FFTLEN since the real and imaginary parts of the complex values are alternated.
			if(i != 0 || i!= FFTLEN/2)
			{
				buf[2*FFTLEN - 2*i] = buf[2*i];
				buf[2*FFTLEN - 2*i + 1] = -buf[2*i+1];
			}
		}

		/* Downscale data to avoid overflow/saturation */
		downScaleData(buf, 2*FFTLEN, 8);

		/* Taking the inverse FFT. Using the NOSCALE version to get the
		   original scale of the signal back.*/
		cifft(buf, FFTLEN, NOSCALE);
		cbrev(buf,buf,FFTLEN);


		/* Reconstructing the output using overlap and add technique. */
		x_ptr = &output[k*WINLEN];

		for( i = 0; i < WINLEN; i++)
		{
			*x_ptr++ = overlap[2*i] + buf[2*i];	// real part

			// preserving the second half of the buffer for over lap and add.
			overlap[2*i] = buf[2*WINLEN + 2*i];		        // real part
			overlap[2*i + 1]  = buf[2*WINLEN + 2*i + 1];	// imag part
		}
	}
}

