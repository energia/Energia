/*****************************************************************************/
/* string.h   v4.4.1                                                         */
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

#ifndef _STRING
#define _STRING

#ifdef __cplusplus
//----------------------------------------------------------------------------
// <cstring> IS RECOMMENDED OVER <string.h>.  <string.h> IS PROVIDED FOR
// COMPATIBILITY WITH C AND THIS USAGE IS DEPRECATED IN C++
//----------------------------------------------------------------------------
extern "C" namespace std
{
#endif /* __cplusplus */
 
#ifndef NULL
#define NULL 0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef __SIZE_T_TYPE__ size_t;
#endif

#include <linkage.h>

#define _OPT_IDECL	_IDECL

_OPT_IDECL size_t  strlen(const char *_string);

_OPT_IDECL char *strcpy(char *_dest, const char *_src);
_OPT_IDECL char *strncpy(char *_to, const char *_from, size_t _n);
_OPT_IDECL char *strcat(char *_string1, const char *_string2);
_OPT_IDECL char *strncat(char *_to, const char *_from, size_t _n);
_OPT_IDECL char *strchr(const char *_string, int _c);
_OPT_IDECL char *strrchr(const char *_string, int _c);

_OPT_IDECL int  strcmp(const char *_string1, const char *_string2);
_OPT_IDECL int  strncmp(const char *_string1, const char *_string2, size_t _n);

_CODE_ACCESS int     strcoll(const char *_string1, const char *_string2);
_CODE_ACCESS size_t  strxfrm(char *_to, const char *_from, size_t _n);
_CODE_ACCESS char   *strpbrk(const char *_string, const char *_chs);
_CODE_ACCESS size_t  strspn(const char *_string, const char *_chs);
_CODE_ACCESS size_t  strcspn(const char *_string, const char *_chs);
_CODE_ACCESS char   *strstr(const char *_string1, const char *_string2);
_CODE_ACCESS char   *strtok(char *_str1, const char *_str2);
_CODE_ACCESS char   *strerror(int _errno);

_CODE_ACCESS void   *memmove(void *_s1, const void *_s2, size_t _n);
_CODE_ACCESS void   *memcpy(void *_s1, const void *_s2, size_t _n);

_OPT_IDECL int     memcmp(const void *_cs, const void *_ct, size_t _n);
_OPT_IDECL void   *memchr(const void *_cs, int _c, size_t _n);

_OPT_IDECL   void   *memset(void *_mem, int _ch, size_t _n);


#ifdef __cplusplus
} /* extern "C" namespace std */
#endif /* __cplusplus */

#if defined(_INLINE) || defined(_STRING_IMPLEMENTATION)


#ifdef __cplusplus
namespace std {
#endif

#define _OPT_IDEFN	_IDEFN

#if defined(_INLINE) || defined(_STRLEN)
_OPT_IDEFN size_t strlen(const char *string)
{
   size_t      n = (size_t)-1;
   const char *s = string;

   do n++; while (*s++);
   return n;
}
#endif /* _INLINE || _STRLEN */

#if defined(_INLINE) || defined(_STRCPY)
_OPT_IDEFN char *strcpy(register char *dest, register const char *src)
{
     register char       *d = dest;     
     register const char *s = src;

     while (*d++ = *s++);
     return dest;
}
#endif /* _INLINE || _STRCPY */

#if defined(_INLINE) || defined(_STRNCPY)
_OPT_IDEFN char *strncpy(register char *dest,
		     register const char *src,
		     register size_t n)
{
     if (n) 
     {
	 register char       *d = dest;
	 register const char *s = src;
	 while ((*d++ = *s++) && --n);              /* COPY STRING         */
	 if (n-- > 1) do *d++ = '\0'; while (--n);  /* TERMINATION PADDING */
     }
     return dest;
}
#endif /* _INLINE || _STRNCPY  */

#if defined(_INLINE) || defined(_STRCAT)
_OPT_IDEFN char *strcat(char *string1, const char *string2)
{
   char       *s1 = string1;
   const char *s2 = string2;

   while (*s1) s1++;		     /* FIND END OF STRING   */
   while (*s1++ = *s2++);	     /* APPEND SECOND STRING */
   return string1;
}
#endif /* _INLINE || _STRCAT */

#if defined(_INLINE) || defined(_STRNCAT)
_OPT_IDEFN char *strncat(char *dest, const char *src, register size_t n)
{
    if (n)
    {
	char       *d = dest;
	const char *s = src;

	while (*d) d++;                      /* FIND END OF STRING   */

	while (n--)
	  if (!(*d++ = *s++)) return dest; /* APPEND SECOND STRING */
	*d = 0;
    }
    return dest;
}
#endif /* _INLINE || _STRNCAT */

#if defined(_INLINE) || defined(_STRCHR)
_OPT_IDEFN char *strchr(const char *string, int c)
{
   char        tch, ch  = c;
   const char *s        = string;

   for (;;)
   {
       if ((tch = *s) == ch) return (char *) s;
       if (!tch)             return (char *) 0;
       s++;
   }
}
#endif /* _INLINE || _STRCHR */

#if defined(_INLINE) || defined(_STRRCHR)
_OPT_IDEFN char *strrchr(const char *string, int c)
{
   char        tch, ch = c;
   char       *result  = 0;
   const char *s       = string;

   for (;;)
   {
      if ((tch = *s) == ch) result = (char *) s;
      if (!tch) break;
      s++;
   }

   return result;
}
#endif /* _INLINE || _STRRCHR */

#if defined(_INLINE) || defined(_STRCMP)
_OPT_IDEFN int strcmp(register const char *string1,
		  register const char *string2)
{
   register int c1, res;

   for (;;)
   {
       c1  = (unsigned char)*string1++;
       res = c1 - (unsigned char)*string2++;

       if (c1 == 0 || res != 0) break;
   }

   return res;
}
#endif /* _INLINE || _STRCMP */

#if defined(_INLINE) || defined(_STRNCMP)
_OPT_IDEFN int strncmp(const char *string1, const char *string2, size_t n)
{
     if (n) 
     {
	 const char *s1 = string1;
	 const char *s2 = string2;
	 unsigned char cp;
	 int         result;

	 do 
	    if (result = (unsigned char)*s1++ - (cp = (unsigned char)*s2++))
                return result;
	 while (cp && --n);
     }
     return 0;
}
#endif /* _INLINE || _STRNCMP */

#if defined(_INLINE) || defined(_MEMCMP)
_OPT_IDEFN int memcmp(const void *cs, const void *ct, size_t n)
{
   if (n) 
   {
       const unsigned char *mem1 = (unsigned char *)cs;
       const unsigned char *mem2 = (unsigned char *)ct;
       int                 cp1, cp2;

       while ((cp1 = *mem1++) == (cp2 = *mem2++) && --n);
       return cp1 - cp2;
   }
   return 0;
}
#endif /* _INLINE || _MEMCMP */

#if defined(_INLINE) || defined(_MEMCHR)
_OPT_IDEFN void *memchr(const void *cs, int c, size_t n)
{
   if (n)
   {
      const unsigned char *mem = (unsigned char *)cs;   
      unsigned char        ch  = c;

      do 
         if ( *mem == ch ) return (void *)mem;
         else mem++;
      while (--n);
   }
   return NULL;
}
#endif /* _INLINE || _MEMCHR */

#if ((defined(_INLINE) || defined(_MEMSET)) && !defined(_TMS320C6X)) && !defined(__TMS470__) && !defined(__ARP32__)
_OPT_IDEFN void *memset(void *mem, register int ch, register size_t length)
{
     register char *m = (char *)mem;

     while (length--) *m++ = ch;
     return mem;
}
#endif /* _INLINE || _MEMSET */

#ifdef __cplusplus
} /* namespace std */
#endif


#endif /* (_INLINE || _STRING_IMPLEMENTATION) */

#endif /* ! _STRING */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::size_t;
using std::strlen;
using std::strcpy;
using std::strncpy;
using std::strcat;
using std::strncat;
using std::strchr;
using std::strrchr;
using std::strcmp;
using std::strncmp;
using std::strcoll;
using std::strxfrm;
using std::strpbrk;
using std::strspn;
using std::strcspn;
using std::strstr;
using std::strtok;
using std::strerror;
using std::memmove;
using std::memcpy;
using std::memcmp;
using std::memchr;
using std::memset;


#endif /* _CPP_STYLE_HEADER */

