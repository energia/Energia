/*****************************************************************************/
/* INTTYPES.H v4.4.1                                                         */
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
#ifndef _INTTYPES_H_
#define _INTTYPES_H_

#include <stdint.h>

/* 7.8 Format conversion of integer types */

typedef struct { intmax_t quot, rem; } imaxdiv_t;

/* 
   According to footnotes in the 1999 C standard, "C++ implementations
   should define these macros only when __STDC_FORMAT_MACROS is defined
   before <inttypes.h> is included." 
*/
#if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS)
#include "_fmt_specifier.h"
#endif /* !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS) */

/* 7.8.2 Functions for greatest-width integer types */
#include <linkage.h>

_CODE_ACCESS intmax_t  imaxabs(intmax_t j);
_CODE_ACCESS imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);
_CODE_ACCESS intmax_t  strtoimax(const char * restrict nptr, 
		    char ** restrict endptr, int base);
_CODE_ACCESS uintmax_t strtoumax(const char * restrict nptr, 
		    char ** restrict endptr, int base);

#endif /* _INTTYPES_H_ */
