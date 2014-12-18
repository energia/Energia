/*****************************************************************************/
/* time.h     v4.4.1                                                         */
/*                                                                           */
/* Copyright (c) 1990-2012 Texas Instruments Incorporated                    */
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

#ifndef _TIME
#define _TIME

#include <linkage.h>


  #define CLOCKS_PER_SEC 200000000 /* 200 MHz */

#ifndef NULL
#define NULL      0
#endif

#ifdef __cplusplus
extern "C" namespace std {
#endif

typedef unsigned long clock_t;
typedef unsigned long time_t;

#ifndef _SIZE_T
#define _SIZE_T
typedef __SIZE_T_TYPE__ size_t;
#endif

struct tm 
{
    int tm_sec;      /* seconds after the minute   - [0,59]  */
    int tm_min;      /* minutes after the hour     - [0,59]  */
    int tm_hour;     /* hours after the midnight   - [0,23]  */
    int tm_mday;     /* day of the month           - [1,31]  */
    int tm_mon;      /* months since January       - [0,11]  */
    int tm_year;     /* years since 1900                     */
    int tm_wday;     /* days since Sunday          - [0,6]   */
    int tm_yday;     /* days since Jan 1st         - [0,365] */
    int tm_isdst;    /* Daylight Savings Time flag           */

};

/*************************************************************************/
/* TIME ZONE STRUCTURE DEFINITION                                        */
/*************************************************************************/
typedef struct 
{
    short daylight;
    long  timezone;
    char  tzname[4];
    char  dstname[4];
} TZ;

extern _DATA_ACCESS TZ _tz;

/****************************************************************************/
/* FUNCTION DECLARATIONS.  (NOTE : clock AND time ARE SYSTEM SPECIFIC)      */
/****************************************************************************/
_CODE_ACCESS clock_t    clock(void);             
_CODE_ACCESS time_t     time(time_t *_timer);   
 
_CODE_ACCESS time_t     mktime(struct tm *_tptr);
_CODE_ACCESS double     difftime(time_t _time1, time_t _time0);
      _IDECL char      *ctime(const time_t *_timer);
_CODE_ACCESS char      *asctime(const struct tm *_timeptr);
_CODE_ACCESS struct tm *gmtime(const time_t *_timer);
_CODE_ACCESS struct tm *localtime(const time_t *_timer);
_CODE_ACCESS size_t     strftime(char *_out, size_t _maxsize, 
				 const char *_format,
				 const struct tm *_timeptr);

#if defined(_INLINE) || defined(_CTIME_IMPLEMENTATION)

_IDEFN char *ctime(const time_t *timer)
{
   return(asctime(localtime(timer)));
}

#endif /* _INLINE || _CTIME_IMPLEMENTATION */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _TIME */

#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
using std::clock_t;
using std::time_t;
using std::size_t;
using std::tm;
using std::TZ;
using std::_tz;
using std::clock;
using std::time;
using std::mktime;
using std::difftime;
using std::ctime;
using std::asctime;
using std::gmtime;
using std::localtime;
using std::strftime;
#endif /* ! _CPP_STYLE_HEADER */

