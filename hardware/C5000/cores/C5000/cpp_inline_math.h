/*****************************************************************************/
/*  CPP_INLINE_MATH.H v4.4.1                                                 */
/*                                                                           */
/* Copyright (c) 1995-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/
#ifndef _CPP_INLINE_MATH_H
#define _CPP_INLINE_MATH_H

#if defined(__cplusplus)


namespace std
{
/*****************************************************************************/
/* These two inline functions for double, the other 23 should be default math*/
/* function defined in ANSI                                                  */
/*****************************************************************************/
inline double abs(double x)	// OVERLOADS
	{	// return absolute value
	return (fabs(x));
	}

inline double pow(double x, int y)
	{	// raise to integer power
	     return (pow(x, (double)y));
	}

/*****************************************************************************/
/* 24 float math functions defined by C++ ISO/IEC 14882 26.5                 */
/*****************************************************************************/
inline float abs(float x)	// OVERLOADS
	{	// return absolute value
	return (float)(fabsf((double)x));
	}

inline float acos(float x)
	{	// return arccosine
	return (float)(acosf((double)x));
	}

inline float asin(float x)
	{	// return arcsine
	return (float)(asinf((double)x));
	}

inline float atan(float x)
	{	// return arctangent
	return (float)(atanf((double)x));
	}

inline float atan2(float x, float y)
	{	// return arctangent
	return (float)(atan2f((double)x, (double)y));
	}

inline float ceil(float x)
	{	// return ceiling
	return (float)(ceilf((double)x));
	}

inline float cos(float x)
	{	// return cosine
	return (float)(cosf((double)x));
	}

inline float cosh(float x)
	{	// return hyperbolic cosine
	return (float)(coshf((double)x));
	}

inline float exp(float x)
	{	// return exponential
	return (float)(expf((double)x));
	}

inline float fabs(float x)
	{	// return absolute value
	return (float)(fabsf((double)x));
	}

inline float floor(float x)
	{	// return floor
	return (float)(floorf((double)x));
	}

inline float fmod(float x, float y)
	{	// return modulus
	return (float)(fmodf((double)x, (double)y));
	}

inline float frexp(float x, int *y)
	{	// unpack exponent
	return (float)(frexpf((double)x, y));
	}

inline float ldexp(float x, int y)
	{	// pack exponent
	return (float)(ldexpf((double)x, y));
	}

inline float log(float x)
	{	// return natural logarithm
	return (float)(logf((double)x));
	}

inline float log10(float x)
	{	// return base-10 logarithm
	return (float)(log10f((double)x));
	}

inline float modf(float x, float *y)
	{	// unpack fraction
	return (float)(modff((float)x, (float *)y));
	}

inline float pow(float x, float y)
	{	// raise to power
	return (float)(powf((double)x, (double)y));
	}

inline float pow(float x, int y)
	{	// raise to integer power
	return (float)(powif((double)x, y));
	}

inline float sin(float x)
	{	// return sine
	return (float)(sinf((double)x));
	}

inline float sinh(float x)
	{	// return hyperbolic sine
	return (float)(sinhf((double)x));
	}

inline float sqrt(float x)
	{	// return square root
	return (float)(sqrtf((double)x));
	}

inline float tan(float x)
	{	// return tangent
	return (float)(tanf((double)x));
	}

inline float tanh(float x)
	{	// return hyperbolic tangent
	return (float)(tanhf((double)x));
	}
/*****************************************************************************/
/* 24 long double math functions defined by C++ ISO/IEC 14882 26.5           */
/*****************************************************************************/
inline long double abs(long double x)	// OVERLOADS
	{	// return absolute value
	return (long double)(fabsl((double)x));
	}

inline long double acos(long double x)
	{	// return arccosine
	return (long double)(acosl((double)x));
	}

inline long double asin(long double x)
	{	// return arcsine
	return (long double)(asinl((double)x));
	}

inline long double atan(long double x)
	{	// return arctangent
	return (long double)(atanl((double)x));
	}

inline long double atan2(long double x, long double y)
	{	// return arctangent
	return (long double)(atan2l((double)x, (double)y));
	}

inline long double ceil(long double x)
	{	// return ceiling
	return (long double)(ceill((double)x));
	}

inline long double cos(long double x)
	{	// return cosine
	return (long double)(cosl((double)x));
	}

inline long double cosh(long double x)
	{	// return hyperbolic cosine
	return (long double)(coshl((double)x));
	}

inline long double exp(long double x)
	{	// return exponential
	return (long double)(expl((double)x));
	}

inline long double fabs(long double x)
	{	// return absolute value
	return (long double)(fabsl((double)x));
	}

inline long double floor(long double x)
	{	// return floor
	return (long double)(floorl((double)x));
	}

inline long double fmod(long double x, long double y)
	{	// return modulus
	return (long double)(fmodl((double)x, (double)y));
	}

inline long double frexp(long double x, int *y)
	{	// unpack exponent
	return (long double)(frexpl((double)x, y));
	}

inline long double ldexp(long double x, int y)
	{	// pack exponent
	return (long double)(ldexpl((double)x, y));
	}

inline long double log(long double x)
	{	// return natural logarithm
	return (long double)(logl((double)x));
	}

inline long double log10(long double x)
	{	// return base-10 logarithm
	return (long double)(log10l((double)x));
	}

inline long double modf(long double x, long double *y)
	{	// unpack fraction
	return (long double)(modfl((long double)x, (long double *)y));
	}

inline long double pow(long double x, long double y)
	{	// raise to power
	return (long double)(powl((double)x, (double)y));
	}

inline long double pow(long double x, int y)
	{	// raise to integer power
	return (long double)(powil((double)x, y));
	}

inline long double sin(long double x)
	{	// return sine
	return (long double)(sinl((double)x));
	}

inline long double sinh(long double x)
	{	// return hyperbolic sine
	return (long double)(sinhl((double)x));
	}

inline long double sqrt(long double x)
	{	// return square root
	return (long double)(sqrtl((double)x));
	}

inline long double tan(long double x)
	{	// return tangent
	return (long double)(tanl((double)x));
	}

inline long double tanh(long double x)
	{	// return hyperbolic tangent
	return (long double)(tanhl((double)x));
	}
} /* namespace std */
#endif /* __cplusplus */

#endif /* _CPP_INLINE_MATH_H */
