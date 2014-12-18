/****************************************************************************/
/*  gsm.h  v4.4.1                                                           */
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

#ifndef _GSMHDR
#define _GSMHDR

/*--------------------------------------------------------------------------*/
/* Definitions for the Basic DSP Operations defined by the European         */
/* Telecommunications Standards Institute (ETSI).                           */
/*                                                                          */
/* Details about these functions may be found in Chapter 13 (BASOP: ITU-T   */
/* Basic Operators) of "ITU-T Software Tool Library 2005 User's Manual"     */
/* available at //www.itu.int/rec/T-REC-G.191-200508-I/en.                  */
/*--------------------------------------------------------------------------*/

#include <linkage.h>

#define MAX_16 0x7fff
#define MIN_16 (-MAX_16-1)
#define MAX_32 0x7fffffff
#define MIN_32 (-MAX_32-1)

/*--------------------------------------------------------------------------*/
/* External variables used by ETSI basicop functions                        */
/*--------------------------------------------------------------------------*/
extern int Overflow;
extern int Carry;

/*--------------------------------------------------------------------------*/
/* Mappings for ETSI functions to built-in compiler intrinsics              */
/*--------------------------------------------------------------------------*/
#define L_add(a,b)     (_lsadd((a),(b)))
#define L_sub(a,b)     (_lssub((a),(b)))
#define L_negate(a)    (_lsneg(a))             
#define L_deposit_h(a) ((long)(a)<<16)        
#define L_deposit_l(a) ((long)(a))
#define L_abs(a)       (_labss((a)))              
#define L_mult(a,b)    (_lsmpy((a),(b)))
#define L_mac(a,b,c)   (_smac((a),(b),(c)))   
#define L_macNs(a,b,c) (L_add_c((a),L_mult((b),(c))))
#define L_msu(a,b,c)   (_smas((a),(b),(c)))   
#define L_msuNs(a,b,c) (L_sub_c((a),L_mult((b),(c))))
#define L_shl(a,b)     (_lsshl((a),(b)))
#define L_shr(a,b)     (_lshrs((a),(b)))
#define L_shr_r(a,b)   (L_crshft_r((a),(b)))
#define L_shift_r(a,b) (L_shr_r(a,-(b)))

#define abs_s(a)       (_abss((a)))               
#define add(a,b)       (_sadd((a),(b)))   
#define sub(a,b)       (_ssub((a),(b)))   
#define extract_h(a)   ((unsigned)((a)>>16))  
#define extract_l(a)   ((int)(a))               
#define	round(a)       (short)(_sround(a)>>16)                  
#define mac_r(a,b,c)   ((short)(_smacr((a),(b),(c))>>16))
#define msu_r(a,b,c)   ((short)(_smasr((a),(b),(c))>>16))
#define mult_r(a,b)    ((short)(_lsmpyr((a),(b))>>16))
#define mult(a,b)      (_smpy((a),(b)))  
#define norm_l(a)      (_lnorm(a))
#define norm_s(a)      (_norm(a))                
#define negate(a)      (_sneg(a))                
#define shl(a,b)       (_sshl((a),(b)))
#define shr(a,b)       (_shrs((a),(b)))
#define shr_r(a,b)     (crshft_r((a),(b)))
#define shift_r(a,b)   (shr_r(a,-(b)))
#define div_s(a,b)     (divs(a,b))

/*--------------------------------------------------------------------------*/
/* Declarations for ETSI functions implemented as function calls (or        */
/* inline functions)                                                        */
/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

int          crshft_r(int x, int y);
long         L_crshft_r(long x, int y);
int          divs(int x, int y);
_IDECL long  L_add_c(long, long);
_IDECL long  L_sub_c(long, long);
_IDECL long  L_sat(long); 


/*--------------------------------------------------------------------------*/
/* Definitions of ETSI functions implemented as inline functions.           */
/*--------------------------------------------------------------------------*/

#ifdef _INLINE
/******************************************************************************/
/* Integer (32-bit) add with carry and overflow testing.                      */
/******************************************************************************/
static inline long L_add_c (long L_var1, long L_var2)
{   
    unsigned long     uv1   = L_var1;       
    unsigned long     uv2   = L_var2;
    int      cin            = Carry;
    unsigned long  result   = uv1 + uv2 + cin;
    
    Carry     = ((~result & (uv1 | uv2)) | (uv1 & uv2)) >> 31;
    Overflow  = ((~(uv1 ^ uv2)) & (uv1 ^ result)) >> 31;

    if (cin && result == 0x80000000) Overflow = 1;

    return (long)result;
}       

/******************************************************************************/
/* Integer (32-bit) subtract with carry and overflow testing.                 */
/******************************************************************************/
static inline long L_sub_c (long L_var1, long L_var2)
{
    unsigned long     uv1   = L_var1;       
    unsigned long     uv2   = L_var2;
    int      cin            = Carry;
    unsigned long  result   = uv1 + ~uv2 + cin;
    
    Carry     = ((~result & (uv1 | ~uv2)) | (uv1 & ~uv2)) >> 31;
    Overflow  = ((uv1 ^ uv2) & (uv1 ^ result)) >> 31;

    if (!cin && result == 0x7fffffff) Overflow = 1;

    return (long)result;
}

/******************************************************************************/
/* Saturate any result after L_addc or L_sub_c if overflow is set.            */
/******************************************************************************/
static inline long L_sat (long L_var1)
{
    int cin = Carry;

    return !Overflow ? L_var1 : (Carry = Overflow = 0, 0x7fffffff+cin);
}
#endif /* !_INLINE */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !_GSMHDR */

