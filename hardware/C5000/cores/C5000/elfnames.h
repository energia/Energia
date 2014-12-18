/****************************************************************************/
/*  elfnames.h          v4.4.1                                              */
/*                                                                          */
/* Copyright (c) 1997-2012 Texas Instruments Incorporated                   */
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

#ifndef __elfnames__
#define __elfnames__

#if defined(__TI_EABI__)


#define _divd __TI_P(divd)
#define _divf __TI_P(divf)
#define _absd __TI_P(absd)
#define _absf __TI_P(absf)
#define _addd __TI_P(addd)
#define _addf __TI_P(addf)
#define _cmpd __TI_P(cmpd)
#define _eqld __TI_P(eqld)
#define _neqd __TI_P(neqd)
#define _lssd __TI_P(lssd)
#define _gtrd __TI_P(gtrd)
#define _leqd __TI_P(leqd)
#define _geqd __TI_P(geqd)
#define _cmpf __TI_P(cmpf)
#define _eqlf __TI_P(eqlf)
#define _neqf __TI_P(neqf)
#define _lssf __TI_P(lssf)
#define _gtrf __TI_P(gtrf)
#define _leqf __TI_P(leqf)
#define _geqf __TI_P(geqf)

#define _nround __TI_P(nround)
#define _roundf __TI_P(roundf)
#define _roundl __TI_P(roundl)

#define _cvtdf __TI_P(cvtdf)
#define _cvtfd __TI_P(cvtfd)

#define _fixdi          __TI_P(fixdi)
#define _fixdli         __TI_P(fixdli)
#define _fixdlli        __TI_P(fixdlli)
#define _fixdu          __TI_P(fixdu)
#define _fixdul         __TI_P(fixdul)
#define _fixdull        __TI_P(fixdull)
#define _fixfi          __TI_P(fixfi)
#define _fixfli         __TI_P(fixfli)
#define _fixflli        __TI_P(fixflli)
#define _fixfu          __TI_P(fixfu)
#define _fixful         __TI_P(fixful)
#define _fixfull        __TI_P(fixfull)
#define _fltid          __TI_P(fltid)
#define _fltif          __TI_P(fltif)
#define _fltlid         __TI_P(fltlid)
#define _fltlif         __TI_P(fltlif)
#define _fltllid        __TI_P(fltllid)
#define _fltllif        __TI_P(fltllif)
#define _fltud          __TI_P(fltud)
#define _fltuf          __TI_P(fltuf)
#define _fltuld         __TI_P(fltuld)
#define _fltulf         __TI_P(fltulf)
#define _fltulld        __TI_P(fltulld)
#define _fltullf        __TI_P(fltullf)

#define __fpclassify    __TI_P(fpclassify)
#define __fpclassifyf   __TI_P(fpclassifyf)

#define __frcdivd       __TI_P(frcdivd)
#define __frcdivf       __TI_P(frcdivf)

#define _frcmpyd_div    __TI_P(frcmpyd_div)
#define _frcmpyf_div    __TI_P(frcmpyf_div)

#define __isfinite      __TI_P(isfinite)
#define __isfinitef     __TI_P(isfinitef)
#define __isinf         __TI_P(isinf)
#define __isinff        __TI_P(isinff)
#define __isnan         __TI_P(isnan)
#define __isnanf        __TI_P(isnanf)
#define __isnormal      __TI_P(isnormal)
#define __isnormalf     __TI_P(isnormalf)

#define _mpyd __TI_P(mpyd)
#define _mpyf __TI_P(mpyf)
#define _negd __TI_P(negd)
#define _negf __TI_P(negf)
#define _subd __TI_P(subd)
#define _subf __TI_P(subf)

#define _trunc  __TI_P(trunc)
#define _truncf __TI_P(truncf)
#define _truncl __TI_P(truncl)

#endif /* defined(__TI_EABI__) */

#endif /* __elfnames__ */
