/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/***********************************************************/
/* Version 2.30.00                                         */
/***********************************************************/
#ifndef _DSPLIBC
#define _DSPLIBC

#include <tms320.h>


/* correlations */

void acorr_c_raw(DATA *x, DATA *r, ushort nx, ushort nr);
void acorr_c_bias(DATA *x, DATA *r, ushort nx, ushort nr);
void acorr_c_unbias(DATA *x, DATA *r, ushort nx, ushort nr);

/* filtering and convolution */


void fir_c(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);
void fir2_c(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);
void firs_c(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh2);
void cfir_c(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);

void iircas4_c(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);
void iircas5_c(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);
void iircas51_c(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);


/* adaptive filtering */

void dlms_c(DATA *x, DATA *h, DATA *r, DATA *des, DATA *dbuffer, DATA step, ushort nh,  ushort nx);


/* macro definition */


#define acorr_c(n1, n2, n3, n4, type) acorr_c_##type(n1, n2, n3, n4)

#endif
