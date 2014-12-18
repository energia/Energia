/****************************************************************************/
/*  math.h           v4.4.1                                                 */
/*                                                                          */
/* Copyright (c) 1997-2012 Texas Instruments Incorporated                   */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/****************************************************************************/

#ifndef _TI_ENHANCED_MATH_H
#define _TI_ENHANCED_MATH_H
#endif

#ifndef __math__
#define __math__

#ifndef EDOM
#define EDOM   1
#endif

#ifndef ERANGE
#define ERANGE 2
#endif

#include <float.h>
#define HUGE_VAL DBL_MAX
#define HUGE_VALL LDBL_MAX

#include <access.h>
#include <elfnames.h>

#ifdef __cplusplus
//----------------------------------------------------------------------------
// <cmath> IS RECOMMENDED OVER <math.h>.  <math.h> IS PROVIDED FOR 
// COMPATIBILITY WITH C AND THIS USAGE IS DEPRECATED IN C++
//----------------------------------------------------------------------------
extern "C" namespace std {
#endif

__EXTERN double sqrt (double x);
__EXTERN double exp  (double x);
__EXTERN double log  (double x);
__EXTERN double log10(double x);
__EXTERN double pow  (double x, double y);
__EXTERN double sin  (double x);
__EXTERN double cos  (double x);
__EXTERN double tan  (double x);
__EXTERN double asin (double x);
__EXTERN double acos (double x);
__EXTERN double atan (double x);
__EXTERN double atan2(double y, double x);
__EXTERN double sinh (double x);
__EXTERN double cosh (double x);
__EXTERN double tanh (double x);

__INLINE double ceil (double x);
__INLINE double floor(double x);

__EXTERN double fabs (double x);

__EXTERN double ldexp(double x, int n);
__EXTERN double frexp(double x, int *exp);
__EXTERN double modf (double x, double *ip);
__EXTERN double fmod (double x, double y);

/* An inline version of fmod that works for limited domain only */
/* See comments in implementation below */
__INLINE double _FMOD(double x, double y);

/* these present in many linked images, so we'll tell you about them. */
__EXTERN double _nround(double x); /* round-to-nearest */
__EXTERN double _trunc(double x); /* truncate towards 0 */

#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

/* the ANSI-optional *f and *l routines */
#include <mathf.h>
#include <mathl.h>

#include <access.h>

#ifdef __cplusplus
extern "C" namespace std {
#endif

#ifdef _TI_ENHANCED_MATH_H
/* ------------------------------------------------- */
/* Routines below are an addition to ANSI math.h     */
/* Some (noted with "9x" in comment) will become ANSI*/
/* once C9x is approved.                             */
/* ------------------------------------------------- */

__EXTERN double rsqrt(double x); /*   == 1/sqrt(x) but *MUCH* faster         */
__EXTERN double exp2 (double x); /*9x mathematically equiv to pow(2.0 ,x)    */
__EXTERN double exp10(double x); /*   mathematically equiv to pow(10.0,x)    */
__EXTERN double log2 (double x); /*9x mathematically equiv to log(x)/log(2.0)*/

__EXTERN double powi(double x, int i); /* equiv to pow(x,(double)i) */

__EXTERN double cot  (double x);
__EXTERN double acot (double x);
__EXTERN double acot2(double x, double y);

__EXTERN double coth (double x);

__EXTERN double asinh(double x); /* 9x */
__EXTERN double acosh(double x); /* 9x */
__EXTERN double atanh(double x); /* 9x */
__EXTERN double acoth(double x);

#ifndef __INLINE_ISINF__
#define __INLINE_ISINF__ 0
#endif

#if __INLINE_ISINF__
__INLINE int __isinf(double x);
#else
__EXTERN int __isinf(double x);
#endif

__INLINE int __isnan(volatile double x);
__INLINE int __isfinite(double x);
__INLINE int __isnormal(double x);
__EXTERN int __fpclassify(double x);

#define isinf(x) (sizeof(x) == sizeof(double) ? __isinf(x) : \
                  sizeof(x) == sizeof(float) ? __isinff(x) : __isinfl(x))

#define isnan(x) (sizeof(x) == sizeof(double) ? __isnan(x) : \
                  sizeof(x) == sizeof(float) ? __isnanf(x) : __isnanl(x))

#define isfinite(x) (sizeof(x) == sizeof(double) ? __isfinite(x) : \
                     sizeof(x) == sizeof(float) ? __isfinitef(x) : \
                     __isfinitel(x))

#define isnormal(x) (sizeof(x) == sizeof(double) ? __isnormal(x) : \
                     sizeof(x) == sizeof(float) ? __isnormalf(x) : \
                     __isnormall(x))

#define fpclassify(x) (sizeof(x) == sizeof(double) ? __fpclassify(x) : \
                       sizeof(x) == sizeof(float) ? __fpclassifyf(x) : \
                       __fpclassifyl(x))

#define round _nround /* 9x round-to-nearest   */
#define trunc _trunc /* 9x truncate towards 0 */

/*Definitions of classification macros used in fp_classify 
  We do not support subnormal numbers yet, but the classification exists for
  when they are supported */

#define FP_INFINITE  1
#define FP_NAN       2
#define FP_NORMAL    3
#define FP_ZERO      4
#define FP_SUBNORMAL 5

#endif /* defined(_TI_ENHANCED_MATH_H) */

#ifdef __cplusplus
} /* extern "C" namespace std */

#endif /* __cplusplus */


#ifdef _INLINE
/****************************************************************************/
/*  Inline versions of floor, ceil, fmod                                    */
/****************************************************************************/

#ifdef __cplusplus
namespace std {
#endif

static __inline double floor(double x) 
{
   double y; 
   return (modf(x, &y) < 0 ? y - 1 : y);
}

static __inline double ceil(double x)
{
   double y; 
   return (modf(x, &y) > 0 ? y + 1 : y);
}

/* 
   The implementation below does not work correctly for all cases.
   Consider the case of fmod(Big, 3), for any Big > 2**(MANT_DIG+2).
   The correct result is one of 0,1, or 2.
   But the implementation below will *always* return 0 
   because the quotient is only an approximation.
*/
static __inline double _FMOD(double x, double y)
{
   double d = fabs(x); 
   if (d - fabs(y) == d) return (0);
   modf(x/y, &d);  
   return (x - d * y);
}

#ifdef _TI_ENHANCED_MATH_H

#if __INLINE_ISINF__
#ifndef REAL_TO_REALNUM
#error isinf can only be inlined in the compilation of the rts
#endif

static __inline int __isinf(double x)
{
  realnum _x;
  REAL_TO_REALNUM(x, _x);
  return _x.exp == (REAL_EMAX + 1) && (_x.mantissa << 1) == 0;
}

#endif /* __INLINE_ISINF___ */

#pragma diag_suppress 681
static __inline int __isnan(volatile double x)
{
  return x != x;
}
#pragma diag_default 681

static __inline int __isfinite(double x)
{
  return (!__isinf(x) && !__isnan(x));
}

static __inline int __isnormal(double x)
{
  return (__isfinite(x) && x != 0.0);
}

#endif /* defined(_TI_ENHANCED_MATH_H) */

#ifdef __cplusplus
} /* namespace std */
#endif /* __cplusplus */

#endif /* _INLINE */

/*******************************************************************************/
/* CQ35082 : Overloaded version of math functions for float and long double    */
/*           removed from here, and include in cmath instead (see Section 26.5 */
/*           of C++ standard for details). Thus cpp_inline_math.h is now       */
/*           included in cmath .                                               */
/*******************************************************************************/
#include <unaccess.h>

#endif /* __math__ */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::sqrt; 
using std::exp; 
using std::log; 
using std::log10; 
using std::pow; 
using std::sin; 
using std::cos; 
using std::tan; 
using std::asin; 
using std::acos;
using std::atan;
using std::atan2;
using std::sinh;
using std::cosh;
using std::tanh;
using std::ceil;
using std::floor;
using std::fabs;
using std::ldexp;
using std::frexp;
using std::modf;
using std::fmod;

#ifdef _TI_ENHANCED_MATH_H
using std::rsqrt;
using std::exp2;
using std::exp10;
using std::log2;
using std::powi;
using std::cot;
using std::acot;
using std::acot2;
using std::coth;
using std::asinh;
using std::acosh;
using std::atanh;
using std::acoth;
#endif /* _TI_ENHANCED_MATH_H */

#endif /* _CPP_STYLE_HEADER */

#if defined(__cplusplus) && defined(_TI_ENHANCED_MATH_H)
using std::__isnan;
using std::__isinf;
using std::__isfinite;
using std::__isnormal;
using std::__fpclassify;
using std::_nround; /* round-to-nearest */
using std::_trunc;
#endif /* __cplusplus && _TI_ENHANCED_MATH_H */
