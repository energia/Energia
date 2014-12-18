//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
// *
// *  Redistribution and use in source and binary forms, with or without
// *  modification, are permitted provided that the following conditions
// *  are met:
// *
// *    Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// *
// *    Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the
// *    distribution.
// *
// *    Neither the name of Texas Instruments Incorporated nor the names of
// *    its contributors may be used to endorse or promote products derived
// *    from this software without specific prior written permission.
// *
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
//////////////////////////////////////////////////////////////////////////////
/** @file RTC_lib.h
 *
 *  @brief RTC library header file
 *
 */

#ifndef _RTC_H_
#define _RTC_H_

#include "tistdtypes.h"
#include "csl_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief RTC date structure.
 *
 *  Contains fields of year, month and day for RTC date.
 */
typedef struct RTCDate {
	unsigned short    year;  /**< Year field of RTC date  : 0 - 99 */
	unsigned short    month; /**< Month field of RTC date : 1 - 12 */
	unsigned short    day;   /**< Day field of RTC date   : 1 - 31 */
} RTCDate;

/**
 * \brief RTC time structure.
 *
 *  Contains field of hours, minutes, seconds and milliseconds for RTC time
 */
typedef struct RTCTime {
	unsigned short    hours; /**< Hours field of RTC time        : 0 - 23   */
	unsigned short    mins;  /**< Minutes field of RTC time      : 0 - 59   */
	unsigned short    secs;  /**< Seconds field of RTC time      : 0 - 59   */
	unsigned short    msecs; /**< Milliseconds field of RTC time : 0 - 1023 */
} RTCTime;

/**
 * \brief RTC Class
 *
 *  Contains prototypes for functions in RTC library
 */
class RTCClass {
    public:
	    void init(void);
	    void start(void);
	    void stop(void);
	    int setTime(RTCTime *pRtcTime);
	    int setDate(RTCDate *pRtcDate);
	    int getTime(RTCTime *pRtcTime);
	    int getDate(RTCDate *pRtcDate);
	    int setAlarm(RTCTime *pRtcTime, RTCDate *pRtcDate);
	    int getAlarm(RTCTime *pRtcTime, RTCDate *pRtcDate);
};

extern RTCClass RTC;
/**< RTC class instance extern which can used by application programs
 *   to access RTC DSP APIs
 */

#ifdef __cplusplus
}
#endif

#endif //_RTC_H_

