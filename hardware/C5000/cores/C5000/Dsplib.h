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
#ifndef _DSPLIB
#define _DSPLIB

#include <tms320.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 32-bit fft */

void cfft32_SCALE(LDATA *x, ushort nx);
void cfft32_NOSCALE(LDATA *x, ushort nx);
void cifft32_SCALE (LDATA *x,  ushort nx);
void cifft32_NOSCALE (LDATA *x,  ushort nx);

/* 32-bit bit reversal */

void cbrev32 (LDATA *x, LDATA *y, ushort n);


/* 16-bit fft */

void cfft_SCALE(DATA *x, ushort nx);
void cfft_NOSCALE(DATA *x, ushort nx);
void cifft_SCALE (DATA *x,  ushort nx);
void cifft_NOSCALE (DATA *x,  ushort nx);

void unpack(DATA *x, ushort nx);
void unpacki(DATA *x, ushort nx);
void unpack32(LDATA *x, ushort nx);
void unpacki32(LDATA *x, ushort nx);
/* void rfft(DATA *x, ushort nx, ushort scale); */
/* void rifft(DATA *x,  ushort nx, ushort scale); */

/* 16-bit bit reversal */

void cbrev (DATA *x, DATA *y, ushort n);


/* correlations */

ushort acorr_raw(DATA *x, DATA *r, ushort nx, ushort nr);
ushort acorr_bias(DATA *x, DATA *r, ushort nx, ushort nr);
ushort acorr_unbias(DATA *x, DATA *r, ushort nx, ushort nr);

ushort corr_raw	(DATA *x, DATA *y, DATA *r, ushort nx, ushort ny);
ushort corr_bias  (DATA *x, DATA *y, DATA *r, ushort nx, ushort ny);
ushort corr_unbias  (DATA *x, DATA *y, DATA *r, ushort nx, ushort ny);

/* filtering and convolution */

ushort convol(DATA *x, DATA *h, DATA *r, ushort nr, ushort nh);
ushort convol1(DATA *x, DATA *h, DATA *r, ushort nr, ushort nh);
ushort convol2(DATA *x, DATA *h, DATA *r, ushort nr, ushort nh);

ushort fir(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);
ushort fir2(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);
ushort firs(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh2);
ushort cfir(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nx, ushort nh);

ushort iircas4(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);
ushort iircas5(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);
ushort iircas51(DATA *x, DATA *h,  DATA *r, DATA *dbuffer, ushort nbiq, ushort nx);

ushort firlat (DATA *x, DATA *h, DATA *r, DATA *pbuffer, int nx, int nh);
ushort iirlat (DATA *x, DATA *h, DATA *r, DATA *pbuffer, int nx, int nh);

ushort hilb16(DATA *x, DATA *h, DATA*r, DATA *dbuffer, ushort nx, ushort nh);
ushort firdec(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nh, ushort nx, ushort D);
ushort firinterp(DATA *x, DATA *h, DATA *r, DATA *dbuffer, ushort nh, ushort nx, ushort I);
ushort iir32(DATA *x,LDATA *h,DATA *r,LDATA *d, ushort nbiq, ushort nx);

/* adaptive filtering */

ushort dlms(DATA *x, DATA *h, DATA *r, DATA *des, DATA *dbuffer, DATA step, ushort nh,  ushort nx);
ushort dlmsfast(DATA *x, DATA *h, DATA *r, DATA *des, DATA *dbuffer, DATA step, ushort nh,  ushort nx);


/* math */
ushort add(DATA *x, DATA *y,  DATA *r,  ushort nx,  ushort scale);
ushort sub(DATA *x, DATA *y,  DATA *r,  ushort nx,  ushort scale);
ushort neg (DATA *x, DATA *r, ushort nx);
ushort neg32 (LDATA *x, LDATA *r, ushort nx);
ushort power (DATA *x, LDATA *r, ushort nx);

ushort sqrt_16(DATA *x, DATA *r, short nx);
void ldiv16(LDATA *x, DATA *y,DATA *r, DATA *rexp, ushort nx);
void recip16(DATA *x, DATA *r, DATA *rexp, ushort nx);

ushort mul32(LDATA *x, LDATA *y,  LDATA *r, ushort nx);

ushort expn(DATA *x, DATA *r, ushort nx);
ushort logn(DATA *x, LDATA *r, ushort nx);
ushort log_2(DATA *x, LDATA *r, ushort nx);
ushort log_10(DATA *x, LDATA *r, ushort nx);
short bexp (DATA *x, ushort nx);


short maxidx (DATA *x, ushort ng, ushort ng_size);
short maxidx34 (DATA *x, ushort nx);
short maxval (DATA *x, ushort nx);
short minidx (DATA *x, ushort ng, ushort ng_size);
short minval (DATA *x, ushort nx);

void maxvec (DATA *x, ushort nx, DATA *val, DATA *idx);
void minvec (DATA *x, ushort nx, DATA *val, DATA *idx);

/* matrix */

ushort mmul(DATA *x1,short row1,short col1,DATA *x2,short row2,short col2,DATA *r);
ushort mtrans(DATA *x, short row, short col, DATA *r);


/* trigonometric */

ushort atan16(DATA *x, DATA *r, ushort nx);
ushort atan2_16(DATA *i, DATA *q, DATA *r, ushort nx);
ushort sine(DATA *x, DATA *r, ushort nx);


/* miscellaneous */

ushort fltoq15(float *x, DATA *r, ushort nx);
ushort q15tofl(DATA *x, float *r, ushort nx);

ushort rand16(DATA *r, ushort nr);
void rand16init(void);




/* macro definition */

#define SCALE 1
#define NOSCALE 0

#define cfft(x,nx, type)   cfft_##type(x,nx)
#define cifft(x,nx, type)   cifft_##type(x,nx)


#define acorr(n1, n2, n3, n4, type) acorr_##type(n1, n2, n3, n4)
#define corr(n1, n2, n3, n4, n5, type) corr_##type(n1, n2, n3, n4, n5)
#define rfft(x,nx,type)\
    (\
         cfft_##type(x,nx/2),\
         cbrev(x,x,nx/2),\
         unpack(x,nx)\
    )

#define rifft(x,nx,type)\
    (\
        unpacki(x, nx),\
        cifft_##type(x,nx/2),\
        cbrev(x,x,nx/2)\
    )


#define rfft32(x,nx,type)\
    (\
         cfft32_##type(x,nx/2),\
         cbrev32(x,x,nx/2),\
         unpack32(x,nx)\
    )

#define rifft32(x,nx,type)\
    (\
        unpacki32(x, nx),\
        cifft32_##type(x,nx/2),\
        cbrev32(x,x,nx/2)\
    )

#ifdef __cplusplus
}
#endif

#endif
