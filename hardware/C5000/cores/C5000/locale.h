/*****************************************************************************/
/* locale.h v4.4.1                                                           */
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
#ifndef _LOCALE
#define _LOCALE


#ifdef __cplusplus
extern "C" namespace std {
#endif

#ifndef NULL
 #define NULL	0
#endif

		/* LOCALE CATEGORY INDEXES */

#define LC_ALL                  0
#define LC_COLLATE		1
#define LC_CTYPE		2
#define LC_MONETARY	        3
#define LC_NUMERIC		4
#define LC_TIME		        5
#define LC_MESSAGES	        6


		/* TYPE DEFINITIONS */
struct lconv
{
    /* LC_NUMERIC */
    char *decimal_point;
    char *grouping;
    char *thousands_sep;
    /* LC_MONETARY */
    char *mon_decimal_point;
    char *mon_grouping;
    char *mon_thousands_sep;

    char *negative_sign;
    char *positive_sign;

    char *currency_symbol;

    char frac_digits;
    char n_cs_precedes;
    char n_sep_by_space;
    char n_sign_posn;
    char p_cs_precedes;
    char p_sep_by_space;
    char p_sign_posn;

    char *int_curr_symbol;
    char int_frac_digits;
};

		/* DECLARATIONS */
struct lconv *localeconv(void);

char *setlocale(int, const char *);

#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

#endif /* _LOCALE */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)

using std::lconv; using std::localeconv; using std::setlocale;


#endif /* _CPP_STYLE_HEADER */

