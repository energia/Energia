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

/** @file filter.h
 *
 *  @brief Filter API header file.
 *
 */

#ifndef FILTER_H
#define FILTER_H

#include "Dsplib.h"

/** ===========================================================================
 *
 * Second order IIR filter.
 *
 *         b0 + b1 z^-1 + b2 z^-2
 * H(z) = ------------------------
 *         a0 + a1 z^-1 + a2 z^-2
 * Note: a0 must be a power of two, i.e. a0 = 2^n0
 *
 * PARAMETERS:
 * length   -> (const int) number of output samples to be processed
 * input    -> (const int *) pointer to input buffer.
 * output   -> (int *) pointer to output buffer.
 * coeffs   -> (const int *) array of both denominator and numerator filter
 *           coefficients. The coefficients must be arranged like
 *           short coeffs[6] = {n0, a1, a2, b0, b1, b2};
 *           where a0 = 2^n0, this is a0 must be a power of two.
 * delayBuf -> (int *) pointer to a memory location were the last delay
 *           element is to be stored.  This "array" must be initialized to zeros
 *           before calling this function for first time and undisturbed
 *           from iteration to iteration.
 *           Note: 'delayBuf' MUST be at least of length 4 (8 bytes half word aligned).
 *
 * IMPLEMENTATION NOTES:
 * - The array delayBuf is updated with last N values of the input and outputs,
 * with N = filter order.
 * i.e. delayBuf[] -> {input[-1], ..., input[-order], output[-1], ...,output[-order]}.
 *  This is to allow proper block operation.
 *
 * BENCHMARK:
 * length   Cycles
 *  512     6706
 *
 * REVISION HISTORY:
 * 08/07/1998 Created, Fernando Mujica
 * 08/25/1998 Modified, to allow in-place operation.  An additional parameter
 *          w (short *) is added to save the state of the filter.
 * 12/05/2013 Changed the function and parameter names
 *
 *  ===========================================================================
 */
void filter_iirSecondOrder(const int length,
                           const int *input,
                           int       *output,
                           const int *coeffs,
                           long       *delayBuf);

/** ===========================================================================
 *
 * Arbitrary order IIR filter. This function cascades multiple second order
 * filter sections to achieve arbitrary order IIR filter
 *
 * This function supports only even 'order' as it cascades multiple
 * second order sections. However, first order filter can be realized
 * by setting the coefficients a2x = b2x = 0 of any second order section x.
 *
 *         b0 + b1 z^-1 + b2 z^-2
 * H(z) = ------------------------
 *         a0 + a1 z^-1 + a2 z^-2
 * Note: a0 must be a power of two, i.e. a0 = 2^n0
 *
 * PARAMETERS:
 * length   -> (const int) number of output samples to be processed
 * input    -> (const int *) pointer to input buffer.
 * output   -> (int *) pointer to output buffer.
 * coeffs   -> (const int *) array of both denominator and numerator filter
 *            coefficients. The coefficients must be arranged like
 *            short coeffs[6*N] = {n01, a11, a21, b01, b11, b21
 *                                 n02, a12, a22, b02, b12, b22
 *                                 ....
 *                                 ....
 *                                 n0N, a1N, a2N, b0N, b1N, b2N};
 *            where a0 = 2^n0, this is a0 must be a power of two.
 *            N is number of second order sections which is equal to 'order/2'
 *            It is mandatory that filter coefficient buffer length is 6*(order/2)
 * delayBuf -> (int *) pointer to a memory location were the last delay
 *           element is to be stored.  This "array" must be initialized to zeros
 *           before calling this function for first time and undisturbed
 *           from iteration to iteration.
 *           Note: 'delayBuf' MUST be at least of length 4*(order/2) (8 bytes half word aligned).
 * order    -> order of the filter, which should be an even value
 *
 * IMPLEMENTATION NOTES:
 * - The array delayBuf is updated with last two values of the input and outputs.
 *   i.e. delayBuf[] -> {input[-1], input[-2], output[-1], output[-2]}.
 *   This is to allow proper block operation.
 *
 *  ===========================================================================
 */
void filter_iirArbitraryOrder(int       length,
                              int       *input,
                              int       *output,
                              const int *coeffs,
                              long       *delayBuf,
                              int       order);
/** ===========================================================================
 *
 * Arbitrary order IIR filter. This function cascades multiple second order
 * filter sections to achieve arbitrary order IIR filter
 * In place variant
 * This function supports only even 'order' as it cascades multiple
 * second order sections. However, first order filter can be realized
 * by setting the coefficients a2x = b2x = 0 of any second order section x.
 *
 *         b0 + b1 z^-1 + b2 z^-2
 * H(z) = ------------------------
 *         a0 + a1 z^-1 + a2 z^-2
 * Note: a0 must be a power of two, i.e. a0 = 2^n0
 *
 * PARAMETERS:
 * length   -> (const int) number of output samples to be processed
 * input    -> (const int *) pointer to input buffer.
 * output   -> (int *) pointer to output buffer.
 * coeffs   -> (const int *) array of both denominator and numerator filter
 *            coefficients. The coefficients must be arranged like
 *            short coeffs[6*N] = {n01, a11, a21, b01, b11, b21
 *                                 n02, a12, a22, b02, b12, b22
 *                                 ....
 *                                 ....
 *                                 n0N, a1N, a2N, b0N, b1N, b2N};
 *            where a0 = 2^n0, this is a0 must be a power of two.
 *            N is number of second order sections which is equal to 'order/2'
 *            It is mandatory that filter coefficient buffer length is 6*(order/2)
 * delayBuf -> (int *) pointer to a memory location were the last delay
 *           element is to be stored.  This "array" must be initialized to zeros
 *           before calling this function for first time and undisturbed
 *           from iteration to iteration.
 *           Note: 'delayBuf' MUST be at least of length 4*(order/2) (8 bytes half word aligned).
 * order    -> order of the filter, which should be an even value
 *
 * IMPLEMENTATION NOTES:
 * - The array delayBuf is updated with last two values of the input and outputs.
 *   i.e. delayBuf[] -> {input[-1], input[-2], output[-1], output[-2]}.
 *   This is to allow proper block operation.
 *
 *  ===========================================================================
 */
void filter_iirArbitraryOrder(int       length,
                              int       *input,
                              const int *coeffs,
                              long       *delayBuf,
                              int       order);

/** ===========================================================================
 *
 * Wrapper API for the dsplib FIR filter API.
 *
 * int *input               <- Address of the Buffer containing Input
 *                             samples
 * int *coeffs              <- Address of the Buffer containing the
 *                             coefficients for FIR filter
 * int *output              <- Address of the Buffer to hold the output
 *                             samples
 * int *delayBuffer         <- Address of the Buffer to hold the delay
 *                             buffer of the FIR filter
 * unsigned int noOfSamples <- Length of the Input Samples Vector
 * unsigned int noOfCoeffs  <- Length of the Coefficient Vector
 *
 * Returns: int overFlow -> 0 : 32 bit Overflow hasn't occurred
 *                          1 : 32 bit Overflow has occurred
 *
 *  ===========================================================================
 */
int filter_fir(int          *input,
               int          *coeffs,
               int          *output,
               int          *delayBuffer,
               unsigned int noOfSamples,
               unsigned int noOfCoeffs);

#endif   /* FILTER_H */
