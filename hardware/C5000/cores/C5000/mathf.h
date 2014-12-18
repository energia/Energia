/****************************************************************************/
/*  mathf.h          v4.4.1                                                 */
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

#ifndef __mathf__
#define __mathf__

#ifndef EDOM
   #define EDOM   1
#endif

#ifndef ERANGE
   #define ERANGE 2
#endif

#include <float.h>

#if (FLT_DIG == DBL_DIG) /* float == double */

#ifndef __math__
#include <math.h>
#endif

#if !defined(DNKLIB)
#define sqrtf    sqrt
#define expf     exp
#define logf     log
#define log10f   log10
#define powf     pow
#define sinf     sin
#define cosf     cos
#define tanf     tan
#define asinf    asin
#define acosf    acos
#define atanf    atan
#define atan2f   atan2
#define sinhf    sinh
#define coshf    cosh
#define tanhf    tanh

#define ceilf    ceil
#define floorf   floor

#define fabsf    fabs

#define ldexpf   ldexp
#define frexpf   frexp
#define fmodf    fmod

#ifdef __cplusplus
namespace std {
#endif /* __cplusplus */

/*modff()requires an actual function because the pointer arg cannot
   be implicitly converted.  */
__INLINE float modff (float x, float *ip);
#ifdef _INLINE
__INLINE float modff (float x, float *ip)
{
   return modf(x, (double *)ip); 
}
#endif

#ifdef __cplusplus
} /* namespace std */      
#endif

#endif /* DNKLIB */

#ifdef _TI_ENHANCED_MATH_H

#define HUGE_VALF FLT_MAX
#if !defined(DNKLIB)
#define rsqrtf   rsqrt
#define exp2f    exp2
#define exp10f   exp10
#define log2f    log2
#define powif    powi
#define cotf     cot
#define acotf    acot
#define acot2f   acot2
#define cothf    coth
#define asinhf   asinh
#define acoshf   acosh
#define atanhf   atanh
#define acothf   acoth
#define truncf   _trunc
#define roundf   _nround
#define __isnormalf __isnormal
#define __isinff   __isinf
#define __isnanf   __isnan
#define __isfinitef __isfinite
#define __fpclassifyf __fpclassify
#endif /* DNKLIB */
#endif /* _TI_ENHANCED_MATH_H */

#else /* float != double */
#ifdef __cplusplus
//----------------------------------------------------------------------------
// <cmathf> IS RECOMMENDED OVER <mathf.h>.  <mathf.h> IS PROVIDED FOR 
// COMPATIBILITY WITH C AND THIS USAGE IS DEPRECATED IN C++
//----------------------------------------------------------------------------
extern "C" namespace std {
#endif /* !__cplusplus */

#include <access.h>

__EXTERN float sqrtf (float x);
__EXTERN float expf  (float x);
__EXTERN float logf  (float x);
__EXTERN float log10f(float x);
__EXTERN float powf  (float x, float y);
__EXTERN float sinf  (float x);
__EXTERN float cosf  (float x);
__EXTERN float tanf  (float x);
__EXTERN float asinf (float x);
__EXTERN float acosf (float x);
__EXTERN float atanf (float x);
__EXTERN float atan2f(float y, float x);
__EXTERN float sinhf (float x);
__EXTERN float coshf (float x);
__EXTERN float tanhf (float x);

__INLINE float ceilf (float x);
__INLINE float floorf(float x);

__EXTERN float fabsf (float x);

__EXTERN float ldexpf(float x, int n);
__EXTERN float frexpf(float x, int *exp);
__EXTERN float modff (float x, float *ip);
__EXTERN float fmodf (float x, float y);

/* An inline version of fmodf that works for limited domain only */
/* See comments in implementation below */
__INLINE float _FMODF(float x, float y);

/* these present in many linked images, so we'll tell you about them. */
__EXTERN float _roundf(float x); /* round-to-nearest */
__EXTERN float _truncf(float x); /* truncate towards 0 */

#ifdef _TI_ENHANCED_MATH_H
/* ------------------------------------------------- */
/* Routines below are an addition to ANSI math.h     */
/* Some (noted with "9x" in comment) will become ANSI*/
/* once C9x is approved.                             */
/* ------------------------------------------------- */

#define HUGE_VALF FLT_MAX /* 9x */

__EXTERN float rsqrtf(float x); /*   == 1/sqrtf(x) but *MUCH* faster         */
__EXTERN float exp2f (float x); /*9x mathematically equiv to powf(2.0 ,x)    */
__EXTERN float exp10f(float x); /*   mathematically equiv to powf(10.0,x)    */
__EXTERN float log2f (float x); /*9x mathematically equiv to logf(x)/logf(2.)*/

__EXTERN float powif (float x, int i); /* equiv to powf(x,(float)i) */

__EXTERN float cotf  (float x);
__EXTERN float acotf (float x);
__EXTERN float acot2f(float x, float y);

__EXTERN float cothf (float x);

__EXTERN float asinhf(float x); /* 9x */
__EXTERN float acoshf(float x); /* 9x */
__EXTERN float atanhf(float x); /* 9x */
__EXTERN float acothf(float x);

#ifndef __INLINE_ISINF__
#define __INLINE_ISINF__ 0
#endif

#if __INLINE_ISINF__
__INLINE int __isinff(float x);
#else
__EXTERN int __isinff(float x);
#endif

__INLINE int __isnanf(float x);
__INLINE int __isfinitef(float x);
__INLINE int __isnormalf(float x);
__EXTERN int __fpclassifyf(float x);

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

#define roundf _roundf /* 9x round-to-nearest   */
#define truncf _truncf /* 9x truncate towards 0 */

#endif /* defined(_TI_ENHANCED_MATH_H) */


#ifdef _INLINE
/****************************************************************************/
/*  Inline versions of floorf, ceilf, fmodf                                 */
/****************************************************************************/
static __inline float floorf(float x) 
{
   float y; 
   return (modff(x, &y) < 0 ? y - 1 : y);
}

static __inline float ceilf(float x)
{
   float y; 
   return (modff(x, &y) > 0 ? y + 1 : y);
}

/* 
   The implementation below does not work correctly for all cases.
   Consider the case of fmod(Big, 3), for any Big > 2**(MANT_DIG+2).
   The correct result is one of 0,1, or 2.
   But the implementation below will *always* return 0 
   because the quotient is only an approximation.
*/
static __inline float _FMODF(float x, float y)
{
   float d = fabsf(x); 
   if (d - fabsf(y) == d) return (0);
   modff(x/y, &d);  
   return (x - d * y);
}

#ifdef _TI_ENHANCED_MATH_H

#if __INLINE_ISINF__
#ifndef REAL_TO_REALNUM
#error isinf can only be inlined in the compilation of the rts
#endif

static __inline int __isinff(float x)
{
  realnum _x;
  REAL_TO_REALNUM(x, _x);
  return _x.exp == (REAL_EMAX + 1) && (_x.mantissa << 1) == 0;
}

#endif /* __INLINE_ISINF__ */

static __inline int __isnanf(volatile float x)
{
  return x != x;
}

static __inline int __isfinitef(float x)
{
  return (!__isinff(x) && !__isnanf(x));
}

static __inline int __isnormalf(float x)
{
  return (__isfinitef(x) && x != 0.0);
}

#endif /* defined(_TI_ENHANCED_MATH_H) */

#endif /* _INLINE */

#include <unaccess.h>

#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

#endif /*  float == double */

#endif /* __mathf__ */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER) && (FLT_DIG != DBL_DIG)
using std::sqrtf;
using std::expf;
using std::logf;
using std::log10f;
using std::powf;
using std::sinf;
using std::cosf;
using std::tanf;
using std::asinf;
using std::acosf;
using std::atanf;
using std::atan2f;
using std::sinhf;
using std::coshf;
using std::tanhf;

using std::ceilf;
using std::floorf;

using std::fabsf;

using std::ldexpf;
using std::frexpf;
using std::modff;
using std::fmodf;

using std::_FMODF;

#ifdef _TI_ENHANCED_MATH_H
using std::rsqrtf; /*   == 1/sqrtf(x) but *MUCH* faster         */
using std::exp2f;  /*9x mathematically equiv to powf(2.0 ,x)    */
using std::exp10f; /*   mathematically equiv to powf(10.0,x)    */
using std::log2f;  /*9x mathematically equiv to logf(x)/logf(2.)*/

using std::powif;  /* equiv to powf(x,(float)i) */

using std::cotf; 
using std::acotf;
using std::acot2f;

using std::cothf;

using std::asinhf; /* 9x */
using std::acoshf; /* 9x */
using std::atanhf; /* 9x */
using std::acothf;
#endif /* _TI_ENHANCED_MATH_H */

#endif /* ! _CPP_STYLE_HEADER */

#if defined(__cplusplus) && (FLT_DIG != DBL_DIG) && defined(_TI_ENHANCED_MATH_H)
using std::__isnanf;
using std::__isinff;
using std::__isfinitef;
using std::__isnormalf;
using std::__fpclassifyf;
using std::_roundf; /* round-to-nearest */
using std::_truncf; /* truncate towards 0 */
#endif /* __cplusplus && FLT_DIG != DBL_DIG && _TI_ENHANCED_MATH_H */
