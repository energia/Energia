/*****************************************************************************/
/* wctype.h    v4.4.1                                                        */
/*                                                                           */
/* Copyright (c) 2007-2012 Texas Instruments Incorporated                    */
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

/************************************************************************/
/*                                                                      */
/*  WIDE CHARACTER TYPING FUNCTIONS AND MACROS                          */
/*                                                                      */
/************************************************************************/
#ifndef _WCTYPE
#define _WCTYPE

#include <linkage.h>


#ifdef __cplusplus
//----------------------------------------------------------------------------
// <cwctype> IS RECOMMENDED OVER <wctype.h>.  <wctype.h> IS PROVIDED FOR
// COMPATIBILITY WITH C AND THIS USAGE IS DEPRECATED IN C++
//----------------------------------------------------------------------------
extern "C" namespace std
{
#endif /* __cplusplus */

#ifndef WEOF
#define WEOF ((wint_t)(-1))
#endif

/************************************************************************/
/*   TYPES                                                              */
/************************************************************************/
#ifndef _WINTT
#define _WINTT
typedef int   wint_t; 
#endif

typedef void *wctrans_t;
typedef void *wctype_t;

/************************************************************************/
/*   FUNCTION DECLARATIONS                                              */
/************************************************************************/
_CODE_ACCESS int       iswalnum(wint_t _c);
_CODE_ACCESS int       iswalpha(wint_t _c);
_CODE_ACCESS int       iswcntrl(wint_t _c);
_CODE_ACCESS int       iswdigit(wint_t _c);
_CODE_ACCESS int       iswgraph(wint_t _c);
_CODE_ACCESS int       iswlower(wint_t _c);
_CODE_ACCESS int       iswprint(wint_t _c);
_CODE_ACCESS int       iswpunct(wint_t _c);
_CODE_ACCESS int       iswspace(wint_t _c);
_CODE_ACCESS int       iswupper(wint_t _c);
_CODE_ACCESS int       iswxdigit(wint_t _c);
_CODE_ACCESS int       iswascii(wint_t _c);

_CODE_ACCESS wctype_t  wctype(const char *property); 
_CODE_ACCESS int       iswctype(wint_t c, wctype_t category); 

_CODE_ACCESS wint_t    towupper(wint_t _c);
_CODE_ACCESS wint_t    towlower(wint_t _c);
_CODE_ACCESS wint_t    towascii(wint_t _c);

_CODE_ACCESS wctrans_t wctrans(const char *property); 
_CODE_ACCESS wint_t    towctrans(wint_t c, wctrans_t category);

#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

#endif /* ! _WCTYPE */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::wint_t;
using std::wctrans_t;
using std::wctype_t;
using std::iswalnum;
using std::iswalpha;
using std::iswcntrl;
using std::iswdigit;
using std::iswgraph;
using std::iswlower;
using std::iswprint;
using std::iswpunct;
using std::iswspace;
using std::iswupper;
using std::iswxdigit;
using std::iswascii;
using std::wctype;
using std::iswctype;
using std::towupper;
using std::towlower;
using std::towascii;
using std::wctrans;
using std::towctrans;

#endif /* ! _CPP_STYLE_HEADER */
