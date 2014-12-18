/*****************************************************************************/
/*  C55X.H v4.4.1                                                            */
/*                                                                           */
/* Copyright (c) 2000-2012 Texas Instruments Incorporated                    */
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

#ifndef _C55X
#define _C55X

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

int        _sadd    (int, int);
int        _a_sadd  (int, int);
long       _lsadd   (long, long);
long       _a_lsadd (long, long);
long long  _llsadd  (long long, long long);
long long  _a_llsadd(long long, long long);

int        _ssub   (int, int);
long       _lssub  (long, long);
long long  _llssub (long long, long long);

int        _sneg   (int);
long       _lsneg  (long);
long long  _llsneg (long long);

int        _abss   (int);
long       _labss  (long);
long long  _llabss (long long);

int        _smpy     (int, int);
long       _lmpy     (int, int);
long       _lmpyu    (unsigned, unsigned);
long       _lmpysu   (int, unsigned);
long       _lsmpy    (int, int);
long       _lsmpyi   (int, int);
long       _lsmpyr   (int, int);
long       _lsmpyu   (unsigned, unsigned);
long       _lsmpyui  (unsigned, unsigned);
long       _lsmpysu  (int, unsigned);
long       _lsmpysui (int, unsigned);
long long  _llmpy    (int, int);
long long  _llsmpy   (int, int);
long long  _llsmpyi  (int, int);
long long  _llsmpyu  (unsigned, unsigned);
long long  _llsmpyui (unsigned, unsigned);
long long  _llsmpysu (int, unsigned);
long long  _llsmpysui(int, unsigned);

long       _smac     (long, int, int);
long       _a_smac   (long, int, int);
long       _smacr    (long, int, int);
long       _a_smacr  (long, int, int);
long       _smaci    (long, int, int);
long       _smacsu   (long, int, unsigned);
long       _smacsui  (long, int, unsigned);
long long  _llsmac   (long long, int, int);
long long  _llsmaci  (long long, int, int);
long long  _llsmacu  (long long, unsigned, unsigned);
long long  _llsmacui (long long, unsigned, unsigned);
long long  _llsmacsu (long long, int, unsigned);
long long  _llsmacsui(long long, int, unsigned);

long       _smas     (long, int, int);
long       _a_smas   (long, int, int);
long       _smasr    (long, int, int);
long       _a_smasr  (long, int, int);
long       _smasi    (long, int, int);
long       _smassu   (long, int, unsigned);
long       _smassui  (long, int, unsigned);
long long  _llsmas   (long long, int, int);
long long  _llsmasi  (long long, int, int);
long long  _llsmasu  (long long, unsigned, unsigned);
long long  _llsmasui (long long, unsigned, unsigned);
long long  _llsmassu (long long, int, unsigned);
long long  _llsmassui(long long, int, unsigned);

int        _shrs   (int, int);
long       _lshrs  (long, int);

int        _shl    (int, int);
long       _lshl   (long, int);
long long  _llshl  (long long, int);

int        _sshl   (int, int);
long       _lsshl  (long, int);
long long  _llsshl (long long, int);

void        _llsshlstore  (long long, int, int*);
void        _llshlstorer  (long long, int, int*);
void        _llsshlstorer (long long, int, int*);
void        _llshlstorern (long long, int, int*);
void        _llsshlstorern(long long, int, int*);

long       _round    (long);
long       _sround   (long);
long       _roundn   (long);
long       _sroundn  (long);
long long  _llround  (long long);
long long  _llsround (long long);
long long  _llroundn (long long);
long long  _llsroundn(long long);

int        _norm   (int);
int        _lnorm  (long);
int        _llnorm (long long);
long       _lsat   (long long);

int        _count  (unsigned long long, unsigned long long);

int        _max    (int, int);
long       _lmax   (long, long);
long long  _llmax  (long long, long long);
int        _min    (int, int);
long       _lmin   (long, long);
long long  _llmin  (long long, long long);

void         _enable_interrupts(void);
unsigned int _disable_interrupts(void);
void         _restore_interrupts(unsigned int);

    /* No C prototypes included for the following due to their */
    /* having "pass-by-reference" parameters.                  */

#ifdef __cplusplus
void       _firs           (int *, int *, int *, int&, long&);
void       _firsn          (int *, int *, int *, int&, long&);
void       _lms            (int *, int *, int&, long&);
void       _llslms         (int *, int *, long long&, long long&);
void       _llslmsi        (int *, int *, long long&, long long&);
void       _abdst          (int *, int *, int&, long&);
void       _sqdst          (int *, int *, int&, long&);
void       _max_diff_dbl   (long, long, long&, long&, unsigned int&);
void       _smax_diff_dbl  (long, long, long&, long&, unsigned int&);
void       _llmax_diff_dbl (long long,  long long,
			    long long&, long long&, unsigned int&);
void       _llsmax_diff_dbl(long long,  long long,
			    long long&, long long&, unsigned int&);
void       _min_diff_dbl   (long, long, long&, long&, unsigned int&);
void       _smin_diff_dbl  (long, long, long&, long&, unsigned int&);
void       _llmin_diff_dbl (long long,  long long,
			    long long&, long long&, unsigned int&);
void       _llsmin_diff_dbl(long long,  long long,
			    long long&, long long&, unsigned int&);
int        _exp_mant       (long, long&);
int        _llexp_mant     (long long, long long&);
void       _llsubc         (int, long long, long long&);
#endif /* __cplusplus */

    /* Deprecated names */

long       _rnd      (long);    /* old name for _sround */
long       _smpyr   (int, int); /* old name for _lsmpyr */

#ifdef __TMS320C55X_PLUS__

extern __cregister volatile unsigned long IER;
extern __cregister volatile unsigned int  IER0;
extern __cregister volatile unsigned int  IER1;
extern __cregister volatile unsigned long DBIER;
extern __cregister volatile unsigned int  DBIER0;
extern __cregister volatile unsigned int  DBIER1;
extern __cregister volatile unsigned int  IVPD;

extern __cregister volatile unsigned int  ST0;
extern __cregister volatile unsigned int  ST1;
extern __cregister volatile unsigned int  ST2;
extern __cregister volatile unsigned int  ST3;
extern __cregister volatile unsigned long XSP;
extern __cregister volatile unsigned long XSSP;
extern __cregister volatile unsigned long RETA;

extern __cregister volatile unsigned long IFR;
extern __cregister volatile unsigned int  IFR0;
extern __cregister volatile unsigned int  IFR1;
extern __cregister volatile unsigned int  BER;
extern __cregister volatile unsigned int  BIOS;

extern __cregister const volatile unsigned int IIR;
extern __cregister const unsigned int CPUCFG;
extern __cregister const unsigned int CPUREV;

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !_C55X */
