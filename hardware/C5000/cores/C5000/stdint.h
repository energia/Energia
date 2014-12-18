/*****************************************************************************/
/* STDINT.H v4.4.1                                                           */
/*                                                                           */
/* Copyright (c) 2002-2012 Texas Instruments Incorporated                    */
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
#ifndef _STDINT_H_
#define _STDINT_H_

/* 7.18.1.1 Exact-width integer types */

#if defined(__MSP430__) || defined(__TMS320C55X_PLUS_BYTE__)
    typedef   signed char    int8_t;
    typedef unsigned char   uint8_t;
    typedef          int    int16_t;
    typedef unsigned int   uint16_t;
    typedef          long   int32_t;
    typedef unsigned long  uint32_t;
#else
    typedef          int    int16_t;
    typedef unsigned int   uint16_t;
    typedef          long   int32_t;
    typedef unsigned long  uint32_t;
#endif

    typedef          long long  int40_t;
    typedef unsigned long long uint40_t;


/* 7.18.1.2 Minimum-width integer types */

#if defined(_TMS320C6X) || defined(__TMS470__) || defined(__MSP430__) || \
    defined(__TMS320C55X_PLUS_BYTE__)  || defined(__ARP32__)
    typedef  int8_t   int_least8_t;
    typedef uint8_t  uint_least8_t;
#else
    typedef  int16_t  int_least8_t;
    typedef uint16_t uint_least8_t;
#endif

    typedef  int16_t  int_least16_t;
    typedef uint16_t uint_least16_t;
    typedef  int32_t  int_least32_t;
    typedef uint32_t uint_least32_t;

    typedef  int40_t  int_least40_t;
    typedef uint40_t uint_least40_t;

/* sorry, int_least64_t not implemented for C54x, C55x */

/* 7.18.1.3 Fastest minimum-width integer types */

    typedef  int16_t  int_fast8_t;
    typedef uint16_t uint_fast8_t;
    typedef  int16_t  int_fast16_t;
    typedef uint16_t uint_fast16_t;

    typedef  int32_t  int_fast32_t;
    typedef uint32_t uint_fast32_t;

    typedef  int40_t  int_fast40_t;
    typedef uint40_t uint_fast40_t;


/* 7.18.1.4 Integer types capable of holding object pointers */
    typedef          long intptr_t;
    typedef unsigned long uintptr_t;

/* 7.18.1.5 Greatest-width integer types */
    typedef          long long intmax_t;
    typedef unsigned long long uintmax_t;

/* 
   According to footnotes in the 1999 C standard, "C++ implementations
   should define these macros only when __STDC_LIMIT_MACROS is defined
   before <stdint.h> is included." 
*/
#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)

/* 7.18.2 Limits of specified width integer types */

#if defined(_TMS320C6X) || defined(__TMS470__) || defined(__MSP430__) || \
    defined(__TMS320C55X_PLUS_BYTE__)  || defined(__ARP32__)
    #define  INT8_MAX   0x7f
    #define  INT8_MIN   (-INT8_MAX-1)
    #define UINT8_MAX   0xff
#endif

    #define  INT16_MAX  0x7fff
    #define  INT16_MIN  (-INT16_MAX-1)
    #define UINT16_MAX  0xffff

    #define  INT32_MAX  0x7fffffff
    #define  INT32_MIN  (-INT32_MAX-1)
    #define UINT32_MAX  0xffffffff

    #define  INT40_MAX  0x7fffffffff
    #define  INT40_MIN  (-INT40_MAX-1)
    #define UINT40_MAX  0xffffffffff


#if defined(_TMS320C6X) || defined(__TMS470__) || defined(__MSP430__) || \
    defined(__TMS320C55X_PLUS_BYTE__) || defined(__ARP32__)
    #define  INT_LEAST8_MAX   INT8_MAX
    #define  INT_LEAST8_MIN   INT8_MIN
    #define UINT_LEAST8_MAX   UINT8_MAX
#else
    #define  INT_LEAST8_MAX   INT16_MAX
    #define  INT_LEAST8_MIN   INT16_MIN
    #define UINT_LEAST8_MAX   UINT16_MAX
#endif

    #define  INT_LEAST16_MAX  INT16_MAX
    #define  INT_LEAST16_MIN  INT16_MIN
    #define UINT_LEAST16_MAX  UINT16_MAX
    #define  INT_LEAST32_MAX  INT32_MAX
    #define  INT_LEAST32_MIN  INT32_MIN
    #define UINT_LEAST32_MAX  UINT32_MAX

    #define  INT_LEAST40_MAX  INT40_MAX
    #define  INT_LEAST40_MIN  INT40_MIN
    #define UINT_LEAST40_MAX  UINT40_MAX


    #define  INT_FAST8_MAX   INT16_MAX
    #define  INT_FAST8_MIN   INT16_MIN
    #define UINT_FAST8_MAX   UINT16_MAX
    #define  INT_FAST16_MAX  INT16_MAX
    #define  INT_FAST16_MIN  INT16_MIN
    #define UINT_FAST16_MAX  UINT16_MAX

    #define  INT_FAST32_MAX  INT32_MAX
    #define  INT_FAST32_MIN  INT32_MIN
    #define UINT_FAST32_MAX  UINT32_MAX

    #define  INT_FAST40_MAX  INT40_MAX
    #define  INT_FAST40_MIN  INT40_MIN
    #define UINT_FAST40_MAX  UINT40_MAX


    #define INTPTR_MAX   INT32_MAX
    #define INTPTR_MIN   INT32_MIN
    #define UINTPTR_MAX  UINT32_MAX

    #define INTMAX_MIN   INT40_MIN
    #define INTMAX_MAX   INT40_MAX
    #define UINTMAX_MAX  UINT40_MAX

/* 7.18.3 Limits of other integer types */

    #define PTRDIFF_MAX INT16_MAX
    #define PTRDIFF_MIN INT16_MIN

    #define SIG_ATOMIC_MIN INT16_MIN
    #define SIG_ATOMIC_MAX INT16_MAX

    #define SIZE_MAX INT16_MAX

#ifndef WCHAR_MAX
#if !defined(__TI_WCHAR_T_BITS__) || __TI_WCHAR_T_BITS__ == 16
#define WCHAR_MAX 0xffffu
#else 
#define WCHAR_MAX 0xffffffffu
#endif
#endif

#ifndef WCHAR_MIN
#define WCHAR_MIN 0
#endif

    #define WINT_MIN INT16_MIN
    #define WINT_MAX INT16_MAX

/* 7.18.4.1 Macros for minimum-width integer constants */

/*
   There is a defect report filed against the C99 standard concerning how 
   the (U)INTN_C macros should be implemented.  Please refer to --
   http://wwwold.dkuug.dk/JTC1/SC22/WG14/www/docs/dr_209.htm 
   for more information.  These macros are implemented according to the
   suggestion given at this web site.
*/

    #define  INT8_C(value)  ((int_least8_t)(value))
    #define UINT8_C(value)  ((uint_least8_t)(value))
    #define  INT16_C(value) ((int_least16_t)(value))
    #define UINT16_C(value) ((uint_least16_t)(value))
    #define  INT32_C(value) ((int_least32_t)(value))
    #define UINT32_C(value) ((uint_least32_t)(value))

    #define  INT40_C(value) ((int_least40_t)(value))
    #define UINT40_C(value) ((uint_least40_t)(value))


/* 7.18.4.2 Macros for greatest-width integer constants */

    #define  INTMAX_C(value) ((intmax_t)(value))
    #define UINTMAX_C(value) ((uintmax_t)(value))

#endif /* !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) */

#endif /* _STDINT_H_ */
