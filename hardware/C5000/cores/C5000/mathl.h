/****************************************************************************/
/*  mathl.h          v4.4.1                                                 */
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

#ifndef __mathl__
#define __mathl__

#ifndef EDOM
   #define EDOM   1
#endif

#ifndef ERANGE
   #define ERANGE 2
#endif

#include <float.h>
#include <access.h>

#if (LDBL_DIG == DBL_DIG) /* long double == double*/

#ifndef __math__
#include <math.h>
#endif

#if !defined(DNKLIB)
#define logl     log
#define log10l   log10
#define sinl     sin
#define cosl     cos
#define sinhl    sinh
#define coshl    cosh
#endif

#define sqrtl    sqrt
#define expl     exp
#define powl     pow
#define tanl     tan
#define asinl    asin
#define acosl    acos
#define atanl    atan
#define atan2l   atan2
#define tanhl    tanh

#define ceill    ceil
#define floorl   floor

#define fabsl    fabs

#define ldexpl   ldexp
#define frexpl   frexp
#define fmodl    fmod

#ifdef __cplusplus
namespace std {
#endif /* __cplusplus */

/* modfl() requires an actual function because the pointer arg cannot
   be implicitly converted.  */
__INLINE long double modfl (long double x, long double *ip);
#ifdef _INLINE
__INLINE long double modfl (long double x, long double *ip)
{
   return modf(x, (double *)ip); 
}
#endif

#ifdef __cplusplus
} /* namespace std */      
#endif

#ifdef _TI_ENHANCED_MATH_H

#define HUGE_VALL LDBL_MAX

#define rsqrtl   rsqrt
#define exp2l    exp2
#define exp10l   exp10
#define log2l    log2
#define powil    powi
#define cotl     cot
#define acotl    acot
#define acot2l   acot2
#define cothl    coth
#define asinhl   asinh
#define acoshl   acosh
#define atanhl   atanh
#define acothl   acoth
#define truncl   _trunc
#define roundl   _nround
#define __isnormall __isnormal
#define __isinfl   __isinf
#define __isnanl   __isnan
#define __isfinitel __isfinite
#define __fpclassifyl __fpclassify

#endif /* _TI_ENHANCED_MATH_H */

#else /* long double != double */
#ifdef __cplusplus
//----------------------------------------------------------------------------
// <cmathl> IS RECOMMENDED OVER <mathl.h>.  <mathl.h> IS PROVIDED FOR 
// COMPATIBILITY WITH C AND THIS USAGE IS DEPRECATED IN C++
//----------------------------------------------------------------------------
extern "C" namespace std {
#endif /* !__cplusplus */

__EXTERN long double sqrtl (long double x);
__EXTERN long double expl  (long double x);
__EXTERN long double logl  (long double x);
__EXTERN long double log10l(long double x);
__EXTERN long double powl  (long double x, long double y);
__EXTERN long double sinl  (long double x);
__EXTERN long double cosl  (long double x);
__EXTERN long double tanl  (long double x);
__EXTERN long double asinl (long double x);
__EXTERN long double acosl (long double x);
__EXTERN long double atanl (long double x);
__EXTERN long double atan2l(long double y, long double x);
__EXTERN long double sinhl (long double x);
__EXTERN long double coshl (long double x);
__EXTERN long double tanhl (long double x);

__INLINE long double ceill (long double x);
__INLINE long double floorl(long double x);

__EXTERN long double fabsl (long double x);

__EXTERN long double ldexpl(long double x, int n);
__EXTERN long double frexpl(long double x, int *exp);
__EXTERN long double modfl (long double x, long double *ip);
__EXTERN long double fmodl (long double x, long double y);

/* An inline version of fmod that works for limited domain only */
/* See comments in implementation below */
static __inline long double _FMODL(long double x, long double y);

__EXTERN long double _roundl(long double x); /* round-to-nearest */
__EXTERN long double _truncl(long double x); /* truncate towards 0 */

#ifdef _TI_ENHANCED_MATH_H
/* ------------------------------------------------- */
/* Routines below are an addition to ANSI math.h     */
/* Some (noted with "9x" in comment) will become ANSI*/
/* once C9x is approved.                             */
/* ------------------------------------------------- */

#define HUGE_VALL LDBL_MAX /* ## */

__EXTERN long double rsqrtl(long double x); /*   1/sqrtl(x) but *MUCH* faster*/
__EXTERN long double exp2l (long double x); /*9x math equiv to powl(2.0 ,x)  */
__EXTERN long double exp10l(long double x); /*   math equiv to powl(10.0,x)  */
__EXTERN long double log2l (long double x);/*9x math equiv to logl(x)/logl(2)*/

__EXTERN long double powil (long double x, int i); /* == powl(x,(long double)i)*/

__EXTERN long double cotl  (long double x);
__EXTERN long double acotl (long double x);
__EXTERN long double acot2l(long double x, long double y);

__EXTERN long double cothl (long double x);

__EXTERN long double asinhl(long double x); /* 9x */
__EXTERN long double acoshl(long double x); /* 9x */
__EXTERN long double atanhl(long double x); /* 9x */
__EXTERN long double acothl(long double x);

#ifndef __INLINE_ISINF__
#define __INLINE_ISINF__ 0
#endif

#if __INLINE_ISINF__
__INLINE int __isinfl(long double x);
#else
__EXTERN int __isinfl(long double x);
#endif

__INLINE int __isnanl(long double x);
__INLINE int __isfinitel(long double x);
__INLINE int __isnormall(long double x);
__EXTERN int __fpclassifyl(long double x);

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

#define roundl _roundl /* 9x round-to-nearest   */
#define truncl _truncl /* 9x truncate towards 0 */

#endif /* defined(_TI_ENHANCED_MATH_H) */


#ifdef _INLINE
/****************************************************************************/
/*  Inline versions of floorl, ceill, fmodl                                 */
/****************************************************************************/
static inline long double floorl(long double x) 
{
   long double y; 
   return (modfl(x, &y) < 0 ? y - 1 : y);
}

static inline long double ceill(long double x)
{
   long double y; 
   return (modfl(x, &y) > 0 ? y + 1 : y);
}

/* 
   The implementation below does not work correctly for all cases.
   Consider the case of fmod(Big, 3), for any Big > 2**(MANT_DIG+2).
   The correct result is one of 0,1, or 2.
   But the implementation below will *always* return 0 
   because the quotient is only an approximation.
*/
static inline long double _FMODL(long double x, long double y)
{
   long double d = fabsl(x); 
   if (d - fabsl(y) == d) return (0);
   modfl(x/y, &d);  
   return (x - d * y);
}

#ifdef _TI_ENHANCED_MATH_H

#if __INLINE_ISINF__
#ifndef REAL_TO_REALNUM
#error isinf can only be inlined in the compilation of the rts
#endif

static __inline int __isinfl(long double x)
{
  realnum _x;
  REAL_TO_REALNUM(x, _x);
  return _x.exp == (REAL_EMAX + 1) && (_x.mantissa << 1) == 0;
}

#endif /* __INLINE_ISINF__ */

static __inline int __isnanl(volatile long double x)
{
  return x != x;
}

static __inline int __isfinitel(long double x)
{
  return (!__isinfl(x) && !__isnanl(x));
}

static __inline int __isnormall(long double x)
{
  return (__isfinitel(x) && x != 0.0);
}

#endif /* defined(_TI_ENHANCED_MATH_H) */

#endif /* defined(_INLINE) */

#include <unaccess.h>
#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

#endif /* long double == double */

#endif /* __mathl__ */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER) && (LDBL_DIG != DBL_DIG)
using std::sqrtl;
using std::expl ;
using std::logl ;
using std::log10l;
using std::powl;
using std::sinl;
using std::cosl;
using std::tanl;
using std::asinl;
using std::acosl;
using std::atanl;
using std::atan2l;
using std::sinhl;
using std::coshl;
using std::tanhl;

using std::ceill;
using std::floorl;

using std::fabsl;

using std::ldexpl;
using std::frexpl;
using std::modfl;
using std::fmodl;

using std::_FMODL;

#ifdef _TI_ENHANCED_MATH_H
using std::rsqrtl; /*   1/sqrtl(x) but *MUCH* faster*/
using std::exp2l;  /*9x math equiv to powl(2.0 ,x)  */
using std::exp10l; /*   math equiv to powl(10.0,x)  */
using std::log2l;  /*9x math equiv to logl(x)/logl(2)*/

using std::powil; /* == powl(x,(long double)i)*/

using std::cotl;
using std::acotl;
using std::acot2l;

using std::cothl;

using std::asinhl; /* 9x */
using std::acoshl; /* 9x */
using std::atanhl; /* 9x */
using std::acothl;
#endif /* _TI_ENHANCED_MATH_H */

#endif /* ! _CPP_STYLE_HEADER */

#if defined(__cplusplus) && (LDBL_DIG != DBL_DIG) && defined(_TI_ENHANCED_MATH_H)
using std::__isnanl;
using std::__isinfl;
using std::__isfinitel;
using std::__isnormall;
using std::__fpclassifyl;
using std::_roundl; /* round-to-nearest */
using std::_truncl; /* truncate towards 0 */
#endif /* __cplusplus && LDBL_DIG != DBL_DIG && _TI_ENHANCED_MATH_H */
