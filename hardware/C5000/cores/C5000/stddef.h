/*****************************************************************************/
/* stddef.h   v4.4.1                                                         */
/*                                                                           */
/* Copyright (c) 1993-2012 Texas Instruments Incorporated                    */
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

#ifndef _STDDEF
#define _STDDEF

#ifdef __cplusplus
extern "C" namespace std {
#endif

#ifndef NULL
#define NULL 0
#endif

typedef __PTRDIFF_T_TYPE__ ptrdiff_t;

#ifndef _SIZE_T
#define _SIZE_T
typedef __SIZE_T_TYPE__ size_t;
#endif

#ifndef __cplusplus
#ifndef _WCHAR_T
#define _WCHAR_T

typedef __WCHAR_T_TYPE__ wchar_t;

#endif /* _WCHAR_T */
#endif /* ! __cplusplus */

#define offsetof(_type, _ident) \
    (__intaddr__( ((char *) &((_type *)0)->_ident) - ((char *) 0) ))

#ifdef __cplusplus
} /* extern "C" namespace std */
#endif  /* __cplusplus */

#endif  /* _STDDEF */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::ptrdiff_t;
using std::size_t;
/*using std::wchar_t;*/
#endif /* _CPP_STYLE_HEADER */

/*-----------------------------------------------------------------------*/
/* Define _win_t, for compiling GCC libraries with the TI compiler.      */
/* GCC's library (newlib) expects wint_t to be defined here, in stddef.h,*/
/* which is arguably incorrect, but we go along for compatibility.       */
/* This is outside the _STDDEF guard in case this file has already       */
/* been included without __need_wint_t.                                  */
/*-----------------------------------------------------------------------*/
#if defined(__need_wint_t) && !defined(_WINT_T) 
#if (__STDC_VERSION__ >= 199901L || !__TI_STRICT_ANSI_MODE__)

#undef __need_wint_t
#define _WINT_T
#ifdef __cplusplus
   extern "C" namespace std {
#endif /* __cplusplus */

typedef unsigned int wint_t;

#ifdef __cplusplus
   } /* extern "C" namespace std { */
#endif /* __cplusplus */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::wint_t;
#endif /* _CPP_STYLE_HEADER */

#endif /* __STDC_VERSION__ >= 199901L  */
#endif
