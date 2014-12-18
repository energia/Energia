/****************************************************************************/
/*  _ISFUNCDEF.H v4.4.1                                                     */
/*                                                                          */
/* Copyright (c) 2005-2012 Texas Instruments Incorporated                   */
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
/* We need isblank for Dinkum math (C99 MATH support)  */

static __inline int isalnum(int c)  { return(_isalnum(c)); }
static __inline int isalpha(int c)  { return(_isalpha(c)); }
static __inline int isascii(int c)  { return(_isascii(c)); }
static __inline int iscntrl(int c)  { return(_iscntrl(c)); }
static __inline int isdigit(int c)  { return(_isdigit(c)); }
static __inline int isgraph(int c)  { return(_isgraph(c)); }
static __inline int islower(int c)  { return(_islower(c)); }
static __inline int isprint(int c)  { return(_isprint(c)); }
static __inline int ispunct(int c)  { return(_ispunct(c)); }
static __inline int isspace(int c)  { return(_isspace(c)); }
static __inline int isupper(int c)  { return(_isupper(c)); }
static __inline int isxdigit(int c) { return(_isxdigit(c));}
static __inline int toascii(int c)  { return(_toascii(c)); }
#ifdef _C99_MATH
static __inline int isblank(int c)  { return(_isblank(c));}
#endif
