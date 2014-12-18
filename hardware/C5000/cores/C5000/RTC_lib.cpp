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

/** @file RTC_lib.cpp
 *
 *  @brief RTC implementation
 *
 */
 
#include "RTC_lib.h"
#include "core.h"
#include <stdio.h>
#include <string.h>


/**
 * Class identifier declaration
 */
RTCClass RTC;

/** ===========================================================================
 *   @n@b init()
 *
 *   @b Description
 *   @n Function initializes RTC Module.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void RTCClass::init(void)
{

	CSL_RtcConfig    rtcConfig;

    RTC_reset();

	rtcConfig.rtcyear  = 0;
	rtcConfig.rtcmonth = 0;
	rtcConfig.rtcday   = 0;
	rtcConfig.rtchour  = 0;
	rtcConfig.rtcmin   = 0;
	rtcConfig.rtcsec   = 0;
	rtcConfig.rtcmSec  = 0;

	rtcConfig.rtcyeara  = 0;
	rtcConfig.rtcmontha = 0;
	rtcConfig.rtcdaya   = 0;
	rtcConfig.rtchoura  = 0;
	rtcConfig.rtcmina   = 0;
	rtcConfig.rtcseca   = 0;
	rtcConfig.rtcmSeca  = 0;

	rtcConfig.rtcintcr  = 0x803F;

	RTC_config(&rtcConfig);
}

/** ===========================================================================
 *   @n@b start
 *
 *   @b Description
 *   @n Starts RTC
 *
 *  ===========================================================================
 */
void RTCClass::start(void)
{
    RTC_start();
}

/** ===========================================================================
 *   @n@b stop
 *
 *   @b Description
 *   @n Stops RTC
 *
 *  ===========================================================================
 */
void RTCClass::stop(void)
{
    RTC_stop();
}

/** ===========================================================================
 *   @n@b setTime
 *
 *   @b Description
 *   @n Sets RTC time.
 *
 *   @b Arguments
 *   @verbatim
 *      pRtcTime    - Pointer to RTC time structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Set time is successful
 *   @li                    CSL_ESYS_INVPARAMS  - Time Parameters are invalid
 *
 *  ===========================================================================
 */
int RTCClass::setTime(RTCTime *pRtcTime)
{
    CSL_Status     status;
    CSL_RtcTime    rtcTime;

	status = CSL_ESYS_INVPARAMS;

    if(pRtcTime != NULL)
	{
		rtcTime.mSecs = pRtcTime->msecs;
		rtcTime.secs  = pRtcTime->secs;
		rtcTime.mins  = pRtcTime->mins;
		rtcTime.hours = pRtcTime->hours;

        status = RTC_setTime(&rtcTime);
	}

    return status;
}

/** ===========================================================================
 *   @n@b setDate
 *
 *   @b Description
 *   @n Sets RTC date
 *
 *   @b Arguments
 *   @verbatim
 *      pRtcDate    - Pointer to RTC date structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Set date is successful
 *   @li                    CSL_ESYS_INVPARAMS  - Date Parameters are invalid
 *
 *  ===========================================================================
 */
int RTCClass::setDate(RTCDate *pRtcDate)
{
    CSL_Status     status;
    CSL_RtcDate    rtcDate;

	status = CSL_ESYS_INVPARAMS;

    if(pRtcDate != NULL)
	{
		rtcDate.day   = pRtcDate->day;
		rtcDate.month = pRtcDate->month;
		rtcDate.year  = pRtcDate->year;

        status = RTC_setDate(&rtcDate);
    }

    return status;
}

/** ===========================================================================
 *   @n@b getTime
 *
 *   @b Description
 *   @n Reads RTC time.
 *
 *   @b Arguments
 *   @verbatim
 *      pRtcTime    - Pointer to RTC time structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Reading time is successful
 *   @li                    CSL_ESYS_INVPARAMS  - Time Parameters are invalid
 *
 *  ===========================================================================
 */
int RTCClass::getTime(RTCTime *pRtcTime)
{
    CSL_Status     status;
    CSL_RtcTime    rtcTime;

	status = CSL_ESYS_INVPARAMS;

	if(pRtcTime != NULL)
	{
		status = RTC_getTime(&rtcTime);
		if(status == CSL_SOK)
		{
			pRtcTime->msecs = rtcTime.mSecs;
			pRtcTime->secs  = rtcTime.secs;
			pRtcTime->mins  = rtcTime.mins;
			pRtcTime->hours = rtcTime.hours;
		}
	}

    return status;
}

/** ===========================================================================
 *   @n@b getDate
 *
 *   @b Description
 *   @n Reads RTC date
 *
 *   @b Arguments
 *   @verbatim
 *      pRtcDate    - Pointer to RTC date structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Reading date is successful
 *   @li                    CSL_ESYS_INVPARAMS  - Date Parameters are invalid
 *
 *  ===========================================================================
 */
int RTCClass::getDate(RTCDate *pRtcDate)
{
    CSL_Status     status;
    CSL_RtcDate    rtcDate;

	status = CSL_ESYS_INVPARAMS;

	if(pRtcDate != NULL)
	{
		status = RTC_getDate(&rtcDate);
		if(status == CSL_SOK)
		{
			pRtcDate->day   = rtcDate.day;
			pRtcDate->month = rtcDate.month;
			pRtcDate->year  = rtcDate.year;
		}
	}

    return status;
}

/** ===========================================================================
 *   @n@b setAlarm
 *
 *   @b Description
 *   @n Sets RTC alarm.
 *
 *   @b Arguments
 *   @verbatim
 *      pRtcTime    - Pointer to RTC time structure
 *      pRtcDate    - Pointer to RTC date structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK
 *   @li                    CSL_ESYS_INVPARAMS
 *
 *  ===========================================================================
 */
int RTCClass::setAlarm(RTCTime *pRtcTime, RTCDate *pRtcDate)
{
    CSL_Status      status;
    CSL_RtcAlarm    rtcAlarm;

	status = CSL_ESYS_INVPARAMS;

    if((pRtcTime != NULL) && (pRtcDate != NULL))
	{
		rtcAlarm.day   = pRtcDate->day;
		rtcAlarm.month = pRtcDate->month;
		rtcAlarm.year  = pRtcDate->year;
		rtcAlarm.mSecs = pRtcTime->msecs;
		rtcAlarm.secs  = pRtcTime->secs;
		rtcAlarm.mins  = pRtcTime->mins;
		rtcAlarm.hours = pRtcTime->hours;

        status = RTC_setAlarm(&rtcAlarm);
	}

    return status;
}

/** ===========================================================================
 *   @n@b getAlarm
 *
 *   @b Description
 *   @n Reads RTC alarm time.
 *
 *   @b Arguments
 *   @verbatim
 *      pRtcTime    - Pointer to RTC time structure
 *      pRtcDate    - Pointer to RTC date structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK
 *   @li                    CSL_ESYS_INVPARAMS
 *
 *  ===========================================================================
 */
int RTCClass::getAlarm(RTCTime *pRtcTime, RTCDate *pRtcDate)
{
    CSL_Status      status;
    CSL_RtcAlarm    rtcAlarm;

	status = CSL_ESYS_INVPARAMS;

    if((pRtcTime != NULL) && (pRtcDate != NULL))
	{
		status = RTC_getAlarm(&rtcAlarm);

		pRtcDate->day   = rtcAlarm.day;
		pRtcDate->month = rtcAlarm.month;
		pRtcDate->year  = rtcAlarm.year;
		pRtcTime->msecs = rtcAlarm.mSecs;
		pRtcTime->secs  = rtcAlarm.secs;
		pRtcTime->mins  = rtcAlarm.mins;
		pRtcTime->hours = rtcAlarm.hours;
	}

    return status;
}



