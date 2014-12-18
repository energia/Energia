/* ============================================================================
 * Copyright (c) 2008-2012 Texas Instruments Incorporated.
 * Except for those rights granted to you in your license from TI, all rights
 * reserved.
 *
 * Software License Agreement
 * Texas Instruments (TI) is supplying this software for use solely and
 * exclusively on TI devices. The software is owned by TI and/or its suppliers,
 * and is protected under applicable patent and copyright laws.  You may not
 * combine this software with any open-source software if such combination would
 * cause this software to become subject to any of the license terms applicable
 * to such open source software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
 * NO WARRANTIES APPLY TO THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY.
 * EXAMPLES OF EXCLUDED WARRANTIES ARE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE AND WARRANTIES OF NON-INFRINGEMENT,
 * BUT ALL OTHER WARRANTY EXCLUSIONS ALSO APPLY. FURTHERMORE, TI SHALL NOT,
 * UNDER ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, CONSEQUENTIAL
 * OR PUNITIVE DAMAGES, FOR ANY REASON WHATSOEVER.
 * ============================================================================
 */

/*********************************************************************
* file: cslr_mcbsp_1.h
*
* Brief: This file contains the Register Description for mcbsp
*
*********************************************************************/
#ifndef _CSLR_MCBSP_H_
#define _CSLR_MCBSP_H_

#include <cslr.h>

#include <tistdtypes.h>


/* Minimum unit = 2 bytes */

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint16 DRRL;
    volatile Uint16 DRRU;
    volatile Uint16 RSVD0[2];
    volatile Uint16 DXRL;
    volatile Uint16 DXRU;
    volatile Uint16 RSVD1[2];
    volatile Uint16 SPCRL;
    volatile Uint16 SPCRU;
    volatile Uint16 RSVD2[2];
    volatile Uint16 RCRL;
    volatile Uint16 RCRU;
    volatile Uint16 RSVD3[2];
    volatile Uint16 XCRL;
    volatile Uint16 XCRU;
    volatile Uint16 RSVD4[2];
    volatile Uint16 SRGRL;
    volatile Uint16 SRGRU;
    volatile Uint16 RSVD5[2];
    volatile Uint16 MCRL;
    volatile Uint16 MCRU;
    volatile Uint16 RSVD6[2];
    volatile Uint16 RCERA;
    volatile Uint16 RCERB;
    volatile Uint16 RSVD7[2];
    volatile Uint16 XCERA;
    volatile Uint16 XCERB;
    volatile Uint16 RSVD8[2];
    volatile Uint16 PCRL;

#if (defined(CHIP_C5517))
    volatile Uint16 PCRU;
    volatile Uint16 RSVD9[2];
#else
    volatile Uint16 RSVD9[3];
#endif

    volatile Uint16 RCERC;
    volatile Uint16 RCERD;
    volatile Uint16 RSVD10[2];
    volatile Uint16 XCERC;
    volatile Uint16 XCERD;
    volatile Uint16 RSVD11[2];
    volatile Uint16 RCERE;
    volatile Uint16 RCERF;
    volatile Uint16 RSVD12[2];
    volatile Uint16 XCERE;
    volatile Uint16 XCERF;
    volatile Uint16 RSVD13[2];
    volatile Uint16 RCERG;
    volatile Uint16 RCERH;
    volatile Uint16 RSVD14[2];
    volatile Uint16 XCERG;
    volatile Uint16 XCERH;
    volatile Uint16 RSVD15[26];
} CSL_McbspRegs;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* DRRL */

#define CSL_MCBSP_DRRL_DR_MASK           (0xFFFFu)
#define CSL_MCBSP_DRRL_DR_SHIFT          (0x0000u)
#define CSL_MCBSP_DRRL_DR_RESETVAL       (0x0000u)

#define CSL_MCBSP_DRRL_RESETVAL          (0x0000u)

/* DRRU */

#define CSL_MCBSP_DRRU_DR_MASK           (0xFFFFu)
#define CSL_MCBSP_DRRU_DR_SHIFT          (0x0000u)
#define CSL_MCBSP_DRRU_DR_RESETVAL       (0x0000u)

#define CSL_MCBSP_DRRU_RESETVAL          (0x0000u)

/* DXRL */

#define CSL_MCBSP_DXRL_DX_MASK           (0xFFFFu)
#define CSL_MCBSP_DXRL_DX_SHIFT          (0x0000u)
#define CSL_MCBSP_DXRL_DX_RESETVAL       (0x0000u)

#define CSL_MCBSP_DXRL_RESETVAL          (0x0000u)

/* DXRU */

#define CSL_MCBSP_DXRU_DX_MASK           (0xFFFFu)
#define CSL_MCBSP_DXRU_DX_SHIFT          (0x0000u)
#define CSL_MCBSP_DXRU_DX_RESETVAL       (0x0000u)

#define CSL_MCBSP_DXRU_RESETVAL          (0x0000u)

/* SPCRL */

#define CSL_MCBSP_SPCRL_DLB_MASK         (0x8000u)
#define CSL_MCBSP_SPCRL_DLB_SHIFT        (0x000Fu)
#define CSL_MCBSP_SPCRL_DLB_RESETVAL     (0x0000u)
/*----DLB Tokens----*/
#define CSL_MCBSP_SPCRL_DLB_DISABLE      (0x0000u)
#define CSL_MCBSP_SPCRL_DLB_ENABLE       (0x0001u)

#define CSL_MCBSP_SPCRL_RJUST_MASK       (0x6000u)
#define CSL_MCBSP_SPCRL_RJUST_SHIFT      (0x000Du)
#define CSL_MCBSP_SPCRL_RJUST_RESETVAL   (0x0000u)
/*----RJUST Tokens----*/
#define CSL_MCBSP_SPCRL_RJUST_RJZFMSB    (0x0000u)
#define CSL_MCBSP_SPCRL_RJUST_RJSEMSB    (0x0001u)
#define CSL_MCBSP_SPCRL_RJUST_LJZFLSB    (0x0002u)
#define CSL_MCBSP_SPCRL_RJUST_RESV       (0x0003u)

#define CSL_MCBSP_SPCRL_CLKSTP_MASK      (0x1800u)
#define CSL_MCBSP_SPCRL_CLKSTP_SHIFT     (0x000Bu)
#define CSL_MCBSP_SPCRL_CLKSTP_RESETVAL  (0x0000u)
/*----CLKSTP Tokens----*/
#define CSL_MCBSP_SPCRL_CLKSTP_DISABLE   (0x0000u)
#define CSL_MCBSP_SPCRL_CLKSTP_WITHOUTDELAY (0x0002u)
#define CSL_MCBSP_SPCRL_CLKSTP_WITHDELAY (0x0003u)



#define CSL_MCBSP_SPCRL_DXENA_MASK       (0x0080u)
#define CSL_MCBSP_SPCRL_DXENA_SHIFT      (0x0007u)
#define CSL_MCBSP_SPCRL_DXENA_RESETVAL   (0x0000u)
/*----DXENA Tokens----*/
#define CSL_MCBSP_SPCRL_DXENA_OFF        (0x0000u)
#define CSL_MCBSP_SPCRL_DXENA_ON         (0x0001u)

#define CSL_MCBSP_SPCRL_ABIS_MASK        (0x0040u)
#define CSL_MCBSP_SPCRL_ABIS_SHIFT       (0x0006u)
#define CSL_MCBSP_SPCRL_ABIS_RESETVAL    (0x0000u)
/*----ABIS Tokens----*/
#define CSL_MCBSP_SPCRL_ABIS_DISABLE     (0x0000u)
#define CSL_MCBSP_SPCRL_ABIS_ENABLE      (0x0001u)

#define CSL_MCBSP_SPCRL_RINTM_MASK       (0x0030u)
#define CSL_MCBSP_SPCRL_RINTM_SHIFT      (0x0004u)
#define CSL_MCBSP_SPCRL_RINTM_RESETVAL   (0x0000u)
/*----RINTM Tokens----*/
#define CSL_MCBSP_SPCRL_RINTM_RRDY       (0x0000u)
#define CSL_MCBSP_SPCRL_RINTM_EOF        (0x0001u)
#define CSL_MCBSP_SPCRL_RINTM_NEWFS      (0x0002u)
#define CSL_MCBSP_SPCRL_RINTM_SYNCERR    (0x0003u)

#define CSL_MCBSP_SPCRL_RSYNCERR_MASK    (0x0008u)
#define CSL_MCBSP_SPCRL_RSYNCERR_SHIFT   (0x0003u)
#define CSL_MCBSP_SPCRL_RSYNCERR_RESETVAL (0x0000u)
/*----RSYNCERR Tokens----*/
#define CSL_MCBSP_SPCRL_RSYNCERR_NOSYNCERR (0x0000u)

#define CSL_MCBSP_SPCRL_RFULL_MASK       (0x0004u)
#define CSL_MCBSP_SPCRL_RFULL_SHIFT      (0x0002u)
#define CSL_MCBSP_SPCRL_RFULL_RESETVAL   (0x0000u)
/*----RFULL Tokens----*/
#define CSL_MCBSP_SPCRL_RFULL_NOTFULL    (0x0000u)
#define CSL_MCBSP_SPCRL_RFULL_FULL       (0x0001u)

#define CSL_MCBSP_SPCRL_RRDY_MASK        (0x0002u)
#define CSL_MCBSP_SPCRL_RRDY_SHIFT       (0x0001u)
#define CSL_MCBSP_SPCRL_RRDY_RESETVAL    (0x0000u)
/*----RRDY Tokens----*/
#define CSL_MCBSP_SPCRL_RRDY_BUSY        (0x0000u)
#define CSL_MCBSP_SPCRL_RRDY_READY       (0x0001u)

#define CSL_MCBSP_SPCRL_RRST_MASK        (0x0001u)
#define CSL_MCBSP_SPCRL_RRST_SHIFT       (0x0000u)
#define CSL_MCBSP_SPCRL_RRST_RESETVAL    (0x0000u)
/*----RRST Tokens----*/
#define CSL_MCBSP_SPCRL_RRST_DISABLE     (0x0000u)
#define CSL_MCBSP_SPCRL_RRST_ENABLE      (0x0001u)

#define CSL_MCBSP_SPCRL_RESETVAL         (0x0000u)

/* SPCRU */


#define CSL_MCBSP_SPCRU_FREE_MASK        (0x0200u)
#define CSL_MCBSP_SPCRU_FREE_SHIFT       (0x0009u)
#define CSL_MCBSP_SPCRU_FREE_RESETVAL    (0x0000u)
/*----FREE Tokens----*/
#define CSL_MCBSP_SPCRU_FREE_DISABLE     (0x0000u)
#define CSL_MCBSP_SPCRU_FREE_ENABLE      (0x0001u)

#define CSL_MCBSP_SPCRU_SOFT_MASK        (0x0100u)
#define CSL_MCBSP_SPCRU_SOFT_SHIFT       (0x0008u)
#define CSL_MCBSP_SPCRU_SOFT_RESETVAL    (0x0000u)
/*----SOFT Tokens----*/
#define CSL_MCBSP_SPCRU_SOFT_DISABLE     (0x0000u)
#define CSL_MCBSP_SPCRU_SOFT_ENABLE      (0x0001u)

#define CSL_MCBSP_SPCRU_FRST_MASK        (0x0080u)
#define CSL_MCBSP_SPCRU_FRST_SHIFT       (0x0007u)
#define CSL_MCBSP_SPCRU_FRST_RESETVAL    (0x0000u)
/*----FRST Tokens----*/
#define CSL_MCBSP_SPCRU_FRST_RESET       (0x0000u)
#define CSL_MCBSP_SPCRU_FRST_NOTRESET    (0x0001u)

#define CSL_MCBSP_SPCRU_GRST_MASK        (0x0040u)
#define CSL_MCBSP_SPCRU_GRST_SHIFT       (0x0006u)
#define CSL_MCBSP_SPCRU_GRST_RESETVAL    (0x0000u)
/*----GRST Tokens----*/
#define CSL_MCBSP_SPCRU_GRST_RESET       (0x0000u)
#define CSL_MCBSP_SPCRU_GRST_NOTRESET    (0x0001u)

#define CSL_MCBSP_SPCRU_XINTM_MASK       (0x0030u)
#define CSL_MCBSP_SPCRU_XINTM_SHIFT      (0x0004u)
#define CSL_MCBSP_SPCRU_XINTM_RESETVAL   (0x0000u)
/*----XINTM Tokens----*/
#define CSL_MCBSP_SPCRU_XINTM_XRDY       (0x0000u)
#define CSL_MCBSP_SPCRU_XINTM_EOF        (0x0001u)
#define CSL_MCBSP_SPCRU_XINTM_NEWFS      (0x0002u)
#define CSL_MCBSP_SPCRU_XINTM_SYNCERR    (0x0003u)

#define CSL_MCBSP_SPCRU_XSYNCERR_MASK    (0x0008u)
#define CSL_MCBSP_SPCRU_XSYNCERR_SHIFT   (0x0003u)
#define CSL_MCBSP_SPCRU_XSYNCERR_RESETVAL (0x0000u)
/*----XSYNCERR Tokens----*/
#define CSL_MCBSP_SPCRU_XSYNCERR_NOSYNCERR (0x0000u)

#define CSL_MCBSP_SPCRU_XEMPTY_MASK      (0x0004u)
#define CSL_MCBSP_SPCRU_XEMPTY_SHIFT     (0x0002u)
#define CSL_MCBSP_SPCRU_XEMPTY_RESETVAL  (0x0000u)
/*----XEMPTY Tokens----*/
#define CSL_MCBSP_SPCRU_XEMPTY_EMPTY     (0x0000u)
#define CSL_MCBSP_SPCRU_XEMPTY_NOTEMPTY  (0x0001u)

#define CSL_MCBSP_SPCRU_XRDY_MASK        (0x0002u)
#define CSL_MCBSP_SPCRU_XRDY_SHIFT       (0x0001u)
#define CSL_MCBSP_SPCRU_XRDY_RESETVAL    (0x0000u)
/*----XRDY Tokens----*/
#define CSL_MCBSP_SPCRU_XRDY_BUSY        (0x0000u)
#define CSL_MCBSP_SPCRU_XRDY_READY       (0x0001u)

#define CSL_MCBSP_SPCRU_XRST_MASK        (0x0001u)
#define CSL_MCBSP_SPCRU_XRST_SHIFT       (0x0000u)
#define CSL_MCBSP_SPCRU_XRST_RESETVAL    (0x0000u)
/*----XRST Tokens----*/
#define CSL_MCBSP_SPCRU_XRST_DISABLE     (0x0000u)
#define CSL_MCBSP_SPCRU_XRST_ENABLE      (0x0001u)

#define CSL_MCBSP_SPCRU_RESETVAL         (0x0000u)

/* RCRL */


#define CSL_MCBSP_RCRL_RFRLEN1_MASK      (0x7F00u)
#define CSL_MCBSP_RCRL_RFRLEN1_SHIFT     (0x0008u)
#define CSL_MCBSP_RCRL_RFRLEN1_RESETVAL  (0x0000u)

#define CSL_MCBSP_RCRL_RWDLEN1_MASK      (0x00E0u)
#define CSL_MCBSP_RCRL_RWDLEN1_SHIFT     (0x0005u)
#define CSL_MCBSP_RCRL_RWDLEN1_RESETVAL  (0x0000u)
/*----RWDLEN1 Tokens----*/
#define CSL_MCBSP_RCRL_RWDLEN1_8BITS     (0x0000u)
#define CSL_MCBSP_RCRL_RWDLEN1_12BITS    (0x0001u)
#define CSL_MCBSP_RCRL_RWDLEN1_16BITS    (0x0002u)
#define CSL_MCBSP_RCRL_RWDLEN1_20BITS    (0x0003u)
#define CSL_MCBSP_RCRL_RWDLEN1_24BITS    (0x0004u)
#define CSL_MCBSP_RCRL_RWDLEN1_32BITS    (0x0005u)

#define CSL_MCBSP_RCRL_RWDREVRS_MASK     (0x0010u)
#define CSL_MCBSP_RCRL_RWDREVRS_SHIFT    (0x0004u)
#define CSL_MCBSP_RCRL_RWDREVRS_RESETVAL (0x0000u)
/*----RWDREVRS Tokens----*/
#define CSL_MCBSP_RCRL_RWDREVRS_DISABLE  (0x0000u)
#define CSL_MCBSP_RCRL_RWDREVRS_ENABLE   (0x0001u)


#define CSL_MCBSP_RCRL_RESETVAL          (0x0000u)

/* RCRU */

#define CSL_MCBSP_RCRU_RPHASE_MASK       (0x8000u)
#define CSL_MCBSP_RCRU_RPHASE_SHIFT      (0x000Fu)
#define CSL_MCBSP_RCRU_RPHASE_RESETVAL   (0x0000u)
/*----RPHASE Tokens----*/
#define CSL_MCBSP_RCRU_RPHASE_SINGLEPHASE (0x0000u)
#define CSL_MCBSP_RCRU_RPHASE_DUALPHASE  (0x0001u)

#define CSL_MCBSP_RCRU_RFRLEN2_MASK      (0x7F00u)
#define CSL_MCBSP_RCRU_RFRLEN2_SHIFT     (0x0008u)
#define CSL_MCBSP_RCRU_RFRLEN2_RESETVAL  (0x0000u)

#define CSL_MCBSP_RCRU_RWDLEN2_MASK      (0x00E0u)
#define CSL_MCBSP_RCRU_RWDLEN2_SHIFT     (0x0005u)
#define CSL_MCBSP_RCRU_RWDLEN2_RESETVAL  (0x0000u)
/*----RWDLEN2 Tokens----*/
#define CSL_MCBSP_RCRU_RWDLEN2_8BITS     (0x0000u)
#define CSL_MCBSP_RCRU_RWDLEN2_12BITS    (0x0001u)
#define CSL_MCBSP_RCRU_RWDLEN2_16BITS    (0x0002u)
#define CSL_MCBSP_RCRU_RWDLEN2_20BITS    (0x0003u)
#define CSL_MCBSP_RCRU_RWDLEN2_24BITS    (0x0004u)
#define CSL_MCBSP_RCRU_RWDLEN2_32BITS    (0x0005u)

#define CSL_MCBSP_RCRU_RCOMPAND_MASK     (0x0018u)
#define CSL_MCBSP_RCRU_RCOMPAND_SHIFT    (0x0003u)
#define CSL_MCBSP_RCRU_RCOMPAND_RESETVAL (0x0000u)
/*----RCOMPAND Tokens----*/
#define CSL_MCBSP_RCRU_RCOMPAND_NCMSBFIRST (0x0000u)
#define CSL_MCBSP_RCRU_RCOMPAND_NCLSBFIRST (0x0001u)
#define CSL_MCBSP_RCRU_RCOMPAND_CULAW    (0x0002u)
#define CSL_MCBSP_RCRU_RCOMPAND_CALAW    (0x0003u)

#define CSL_MCBSP_RCRU_RFIG_MASK         (0x0004u)
#define CSL_MCBSP_RCRU_RFIG_SHIFT        (0x0002u)
#define CSL_MCBSP_RCRU_RFIG_RESETVAL     (0x0000u)
/*----RFIG Tokens----*/
#define CSL_MCBSP_RCRU_RFIG_DISABLE      (0x0000u)
#define CSL_MCBSP_RCRU_RFIG_ENABLE       (0x0001u)

#define CSL_MCBSP_RCRU_RDATDLY_MASK      (0x0003u)
#define CSL_MCBSP_RCRU_RDATDLY_SHIFT     (0x0000u)
#define CSL_MCBSP_RCRU_RDATDLY_RESETVAL  (0x0000u)
/*----RDATDLY Tokens----*/
#define CSL_MCBSP_RCRU_RDATDLY_0BIT      (0x0000u)
#define CSL_MCBSP_RCRU_RDATDLY_1BIT      (0x0001u)
#define CSL_MCBSP_RCRU_RDATDLY_2BIT      (0x0002u)

#define CSL_MCBSP_RCRU_RESETVAL          (0x0000u)

/* XCRL */


#define CSL_MCBSP_XCRL_XFRLEN1_MASK      (0x7F00u)
#define CSL_MCBSP_XCRL_XFRLEN1_SHIFT     (0x0008u)
#define CSL_MCBSP_XCRL_XFRLEN1_RESETVAL  (0x0000u)

#define CSL_MCBSP_XCRL_XWDLEN1_MASK      (0x00E0u)
#define CSL_MCBSP_XCRL_XWDLEN1_SHIFT     (0x0005u)
#define CSL_MCBSP_XCRL_XWDLEN1_RESETVAL  (0x0000u)
/*----XWDLEN1 Tokens----*/
#define CSL_MCBSP_XCRL_XWDLEN1_8BITS     (0x0000u)
#define CSL_MCBSP_XCRL_XWDLEN1_12BITS    (0x0001u)
#define CSL_MCBSP_XCRL_XWDLEN1_16BITS    (0x0002u)
#define CSL_MCBSP_XCRL_XWDLEN1_20BITS    (0x0003u)
#define CSL_MCBSP_XCRL_XWDLEN1_24BITS    (0x0004u)
#define CSL_MCBSP_XCRL_XWDLEN1_32BITS    (0x0005u)

#define CSL_MCBSP_XCRL_XWDREVRS_MASK     (0x0010u)
#define CSL_MCBSP_XCRL_XWDREVRS_SHIFT    (0x0004u)
#define CSL_MCBSP_XCRL_XWDREVRS_RESETVAL (0x0000u)
/*----XWDREVRS Tokens----*/
#define CSL_MCBSP_XCRL_XWDREVRS_DISABLE  (0x0000u)
#define CSL_MCBSP_XCRL_XWDREVRS_ENABLE   (0x0001u)


#define CSL_MCBSP_XCRL_RESETVAL          (0x0000u)

/* XCRU */

#define CSL_MCBSP_XCRU_XPHASE_MASK       (0x8000u)
#define CSL_MCBSP_XCRU_XPHASE_SHIFT      (0x000Fu)
#define CSL_MCBSP_XCRU_XPHASE_RESETVAL   (0x0000u)
/*----XPHASE Tokens----*/
#define CSL_MCBSP_XCRU_XPHASE_SINGLEPHASE (0x0000u)
#define CSL_MCBSP_XCRU_XPHASE_DUALPHASE  (0x0001u)

#define CSL_MCBSP_XCRU_XFRLEN2_MASK      (0x7F00u)
#define CSL_MCBSP_XCRU_XFRLEN2_SHIFT     (0x0008u)
#define CSL_MCBSP_XCRU_XFRLEN2_RESETVAL  (0x0000u)

#define CSL_MCBSP_XCRU_XWDLEN2_MASK      (0x00E0u)
#define CSL_MCBSP_XCRU_XWDLEN2_SHIFT     (0x0005u)
#define CSL_MCBSP_XCRU_XWDLEN2_RESETVAL  (0x0000u)
/*----XWDLEN2 Tokens----*/
#define CSL_MCBSP_XCRU_XWDLEN2_8BITS     (0x0000u)
#define CSL_MCBSP_XCRU_XWDLEN2_12BITS    (0x0001u)
#define CSL_MCBSP_XCRU_XWDLEN2_16BITS    (0x0002u)
#define CSL_MCBSP_XCRU_XWDLEN2_20BITS    (0x0003u)
#define CSL_MCBSP_XCRU_XWDLEN2_24BITS    (0x0004u)
#define CSL_MCBSP_XCRU_XWDLEN2_32BITS    (0x0005u)

#define CSL_MCBSP_XCRU_XCOMPAND_MASK     (0x0018u)
#define CSL_MCBSP_XCRU_XCOMPAND_SHIFT    (0x0003u)
#define CSL_MCBSP_XCRU_XCOMPAND_RESETVAL (0x0000u)
/*----XCOMPAND Tokens----*/
#define CSL_MCBSP_XCRU_XCOMPAND_NCMSBFIRST (0x0000u)
#define CSL_MCBSP_XCRU_XCOMPAND_NCLSBFIRST (0x0001u)
#define CSL_MCBSP_XCRU_XCOMPAND_CULAW    (0x0002u)
#define CSL_MCBSP_XCRU_XCOMPAND_CALAW    (0x0003u)

#define CSL_MCBSP_XCRU_XFIG_MASK         (0x0004u)
#define CSL_MCBSP_XCRU_XFIG_SHIFT        (0x0002u)
#define CSL_MCBSP_XCRU_XFIG_RESETVAL     (0x0000u)
/*----XFIG Tokens----*/
#define CSL_MCBSP_XCRU_XFIG_DISABLE      (0x0000u)
#define CSL_MCBSP_XCRU_XFIG_ENABLE       (0x0001u)

#define CSL_MCBSP_XCRU_XDATDLY_MASK      (0x0003u)
#define CSL_MCBSP_XCRU_XDATDLY_SHIFT     (0x0000u)
#define CSL_MCBSP_XCRU_XDATDLY_RESETVAL  (0x0000u)
/*----XDATDLY Tokens----*/
#define CSL_MCBSP_XCRU_XDATDLY_0BIT      (0x0000u)
#define CSL_MCBSP_XCRU_XDATDLY_1BIT      (0x0001u)
#define CSL_MCBSP_XCRU_XDATDLY_2BIT      (0x0002u)

#define CSL_MCBSP_XCRU_RESETVAL          (0x0000u)

/* SRGRL */

#define CSL_MCBSP_SRGRL_FWID_MASK        (0xFF00u)
#define CSL_MCBSP_SRGRL_FWID_SHIFT       (0x0008u)
#define CSL_MCBSP_SRGRL_FWID_RESETVAL    (0x0000u)

#define CSL_MCBSP_SRGRL_CLKGDV_MASK      (0x00FFu)
#define CSL_MCBSP_SRGRL_CLKGDV_SHIFT     (0x0000u)
#define CSL_MCBSP_SRGRL_CLKGDV_RESETVAL  (0x0001u)

#define CSL_MCBSP_SRGRL_RESETVAL         (0x0001u)

/* SRGRU */

#define CSL_MCBSP_SRGRU_GSYNC_MASK       (0x8000u)
#define CSL_MCBSP_SRGRU_GSYNC_SHIFT      (0x000Fu)
#define CSL_MCBSP_SRGRU_GSYNC_RESETVAL   (0x0000u)
/*----GSYNC Tokens----*/
#define CSL_MCBSP_SRGRU_GSYNC_FREERUN    (0x0000u)
#define CSL_MCBSP_SRGRU_GSYNC_RUN        (0x0001u)

#define CSL_MCBSP_SRGRU_CLKSP_MASK       (0x4000u)
#define CSL_MCBSP_SRGRU_CLKSP_SHIFT      (0x000Eu)
#define CSL_MCBSP_SRGRU_CLKSP_RESETVAL   (0x0000u)
/*----CLKSP Tokens----*/
#define CSL_MCBSP_SRGRU_CLKSP_RISINGEDGE (0x0000u)
#define CSL_MCBSP_SRGRU_CLKSP_FALLINGEDGE (0x0000u)

#define CSL_MCBSP_SRGRU_CLKSM_MASK       (0x2000u)
#define CSL_MCBSP_SRGRU_CLKSM_SHIFT      (0x000Du)
#define CSL_MCBSP_SRGRU_CLKSM_RESETVAL   (0x0001u)
/*----CLKSM Tokens----*/
#define CSL_MCBSP_SRGRU_CLKSM_ZERO       (0x0000u)
#define CSL_MCBSP_SRGRU_CLKSM_ONE        (0x0001u)

#define CSL_MCBSP_SRGRU_FSGM_MASK        (0x1000u)
#define CSL_MCBSP_SRGRU_FSGM_SHIFT       (0x000Cu)
#define CSL_MCBSP_SRGRU_FSGM_RESETVAL    (0x0000u)
/*----FSGM Tokens----*/
#define CSL_MCBSP_SRGRU_FSGM_ZERO        (0x0000u)
#define CSL_MCBSP_SRGRU_FSGM_ONE         (0x0001u)

#define CSL_MCBSP_SRGRU_FPER_MASK        (0x0FFFu)
#define CSL_MCBSP_SRGRU_FPER_SHIFT       (0x0000u)
#define CSL_MCBSP_SRGRU_FPER_RESETVAL    (0x0000u)

#define CSL_MCBSP_SRGRU_RESETVAL         (0x2000u)

/* MCRL */


#define CSL_MCBSP_MCRL_REMODE_MASK       (0x0400u)
#define CSL_MCBSP_MCRL_REMODE_SHIFT      (0x000Au)
#define CSL_MCBSP_MCRL_REMODE_RESETVAL   (0x0000u)
/*----REMODE Tokens----*/
#define CSL_MCBSP_MCRL_REMODE_ZERO       (0x0000u)
#define CSL_MCBSP_MCRL_REMODE_ONE        (0x0001u)

#define CSL_MCBSP_MCRL_RMCME_MASK        (0x0200u)
#define CSL_MCBSP_MCRL_RMCME_SHIFT       (0x0009u)
#define CSL_MCBSP_MCRL_RMCME_RESETVAL    (0x0000u)
/*----RMCME Tokens----*/
#define CSL_MCBSP_MCRL_RMCME_ZERO        (0x0000u)
#define CSL_MCBSP_MCRL_RMCME_ONE         (0x0001u)

#define CSL_MCBSP_MCRL_RPBBLK_MASK       (0x0180u)
#define CSL_MCBSP_MCRL_RPBBLK_SHIFT      (0x0007u)
#define CSL_MCBSP_MCRL_RPBBLK_RESETVAL   (0x0000u)
/*----RPBBLK Tokens----*/
#define CSL_MCBSP_MCRL_RPBBLK_BLOCK1     (0x0000u)
#define CSL_MCBSP_MCRL_RPBBLK_BLOCK3     (0x0001u)
#define CSL_MCBSP_MCRL_RPBBLK_BLOCK5     (0x0002u)
#define CSL_MCBSP_MCRL_RPBBLK_BLOCK7     (0x0003u)

#define CSL_MCBSP_MCRL_RPABLK_MASK       (0x0060u)
#define CSL_MCBSP_MCRL_RPABLK_SHIFT      (0x0005u)
#define CSL_MCBSP_MCRL_RPABLK_RESETVAL   (0x0000u)
/*----RPABLK Tokens----*/
#define CSL_MCBSP_MCRL_RPABLK_BLOCK0     (0x0000u)
#define CSL_MCBSP_MCRL_RPABLK_BLOCK2     (0x0001u)
#define CSL_MCBSP_MCRL_RPABLK_BLOCK4     (0x0002u)
#define CSL_MCBSP_MCRL_RPABLK_BLOCK6     (0x0003u)

#define CSL_MCBSP_MCRL_RCBLK_MASK        (0x001Cu)
#define CSL_MCBSP_MCRL_RCBLK_SHIFT       (0x0002u)
#define CSL_MCBSP_MCRL_RCBLK_RESETVAL    (0x0000u)
/*----RCBLK Tokens----*/
#define CSL_MCBSP_MCRL_RCBLK_BLOCK0      (0x0000u)
#define CSL_MCBSP_MCRL_RCBLK_BLOCK1      (0x0001u)
#define CSL_MCBSP_MCRL_RCBLK_BLOCK2      (0x0002u)
#define CSL_MCBSP_MCRL_RCBLK_BLOCK3      (0x0003u)
#define CSL_MCBSP_MCRL_RCBLK_BLOCK4      (0x0004u)
#define CSL_MCBSP_MCRL_RCBLK_BLOCK5      (0x0005u)
#define CSL_MCBSP_MCRL_RCBLK_BLOCK6      (0x0006u)
#define CSL_MCBSP_MCRL_RCBLK_BLOCK7      (0x0007u)

#define CSL_MCBSP_MCRL_RMCM_MASK         (0x0003u)
#define CSL_MCBSP_MCRL_RMCM_SHIFT        (0x0000u)
#define CSL_MCBSP_MCRL_RMCM_RESETVAL     (0x0000u)
/*----RMCM Tokens----*/
#define CSL_MCBSP_MCRL_RMCM_ZERO         (0x0000u)
#define CSL_MCBSP_MCRL_RMCM_ONE          (0x0001u)

#define CSL_MCBSP_MCRL_RESETVAL          (0x0000u)

/* MCRU */


#define CSL_MCBSP_MCRU_DX_MASK           (0x1800u)
#define CSL_MCBSP_MCRU_DX_SHIFT          (0x000Bu)
#define CSL_MCBSP_MCRU_DX_RESETVAL       (0x0000u)
/*----DX Tokens----*/
#define CSL_MCBSP_MCRU_DX_ZERO           (0x0000u)
#define CSL_MCBSP_MCRU_DX_ONE            (0x0001u)
#define CSL_MCBSP_MCRU_DX_TWO            (0x0002u)

#define CSL_MCBSP_MCRU_XEMODE_MASK       (0x0400u)
#define CSL_MCBSP_MCRU_XEMODE_SHIFT      (0x000Au)
#define CSL_MCBSP_MCRU_XEMODE_RESETVAL   (0x0000u)
/*----XEMODE Tokens----*/
#define CSL_MCBSP_MCRU_XEMODE_ZERO       (0x0000u)
#define CSL_MCBSP_MCRU_XEMODE_ONE        (0x0001u)

#define CSL_MCBSP_MCRU_XMCME_MASK        (0x0200u)
#define CSL_MCBSP_MCRU_XMCME_SHIFT       (0x0009u)
#define CSL_MCBSP_MCRU_XMCME_RESETVAL    (0x0000u)
/*----XMCME Tokens----*/
#define CSL_MCBSP_MCRU_XMCME_ZERO        (0x0000u)
#define CSL_MCBSP_MCRU_XMCME_ONE         (0x0001u)

#define CSL_MCBSP_MCRU_XPBBLK_MASK       (0x0180u)
#define CSL_MCBSP_MCRU_XPBBLK_SHIFT      (0x0007u)
#define CSL_MCBSP_MCRU_XPBBLK_RESETVAL   (0x0000u)
/*----XPBBLK Tokens----*/
#define CSL_MCBSP_MCRU_XPBBLK_BLOCK1     (0x0000u)
#define CSL_MCBSP_MCRU_XPBBLK_BLOCK3     (0x0001u)
#define CSL_MCBSP_MCRU_XPBBLK_BLOCK5     (0x0002u)
#define CSL_MCBSP_MCRU_XPBBLK_BLOCK7     (0x0003u)

#define CSL_MCBSP_MCRU_XPABLK_MASK       (0x0060u)
#define CSL_MCBSP_MCRU_XPABLK_SHIFT      (0x0005u)
#define CSL_MCBSP_MCRU_XPABLK_RESETVAL   (0x0000u)
/*----XPABLK Tokens----*/
#define CSL_MCBSP_MCRU_XPABLK_BLOCK0     (0x0000u)
#define CSL_MCBSP_MCRU_XPABLK_BLOCK2     (0x0001u)
#define CSL_MCBSP_MCRU_XPABLK_BLOCK4     (0x0002u)
#define CSL_MCBSP_MCRU_XPABLK_BLOCK6     (0x0003u)

#define CSL_MCBSP_MCRU_XCBLK_MASK        (0x001Cu)
#define CSL_MCBSP_MCRU_XCBLK_SHIFT       (0x0002u)
#define CSL_MCBSP_MCRU_XCBLK_RESETVAL    (0x0000u)
/*----XCBLK Tokens----*/
#define CSL_MCBSP_MCRU_XCBLK_BLOCK0      (0x0000u)
#define CSL_MCBSP_MCRU_XCBLK_BLOCK1      (0x0001u)
#define CSL_MCBSP_MCRU_XCBLK_BLOCK2      (0x0002u)
#define CSL_MCBSP_MCRU_XCBLK_BLOCK3      (0x0003u)
#define CSL_MCBSP_MCRU_XCBLK_BLOCK4      (0x0004u)
#define CSL_MCBSP_MCRU_XCBLK_BLOCK5      (0x0005u)
#define CSL_MCBSP_MCRU_XCBLK_BLOCK6      (0x0006u)
#define CSL_MCBSP_MCRU_XCBLK_BLOCK7      (0x0007u)

#define CSL_MCBSP_MCRU_XMCM_MASK         (0x0003u)
#define CSL_MCBSP_MCRU_XMCM_SHIFT        (0x0000u)
#define CSL_MCBSP_MCRU_XMCM_RESETVAL     (0x0000u)
/*----XMCM Tokens----*/
#define CSL_MCBSP_MCRU_XMCM_ZERO         (0x0000u)
#define CSL_MCBSP_MCRU_XMCM_ONE          (0x0001u)

#define CSL_MCBSP_MCRU_RESETVAL          (0x0000u)

/* RCERA */

#define CSL_MCBSP_RCERA_RCEA15_MASK      (0x8000u)
#define CSL_MCBSP_RCERA_RCEA15_SHIFT     (0x000Fu)
#define CSL_MCBSP_RCERA_RCEA15_RESETVAL  (0x0000u)
/*----RCEA15 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA15_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERA_RCEA15_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERA_RCEA14_MASK      (0x4000u)
#define CSL_MCBSP_RCERA_RCEA14_SHIFT     (0x000Eu)
#define CSL_MCBSP_RCERA_RCEA14_RESETVAL  (0x0000u)
/*----RCEA14 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA14_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERA_RCEA14_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERA_RCEA13_MASK      (0x2000u)
#define CSL_MCBSP_RCERA_RCEA13_SHIFT     (0x000Du)
#define CSL_MCBSP_RCERA_RCEA13_RESETVAL  (0x0000u)
/*----RCEA13 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA13_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERA_RCEA13_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERA_RCEA12_MASK      (0x1000u)
#define CSL_MCBSP_RCERA_RCEA12_SHIFT     (0x000Cu)
#define CSL_MCBSP_RCERA_RCEA12_RESETVAL  (0x0000u)
/*----RCEA12 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA12_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERA_RCEA12_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERA_RCEA11_MASK      (0x0800u)
#define CSL_MCBSP_RCERA_RCEA11_SHIFT     (0x000Bu)
#define CSL_MCBSP_RCERA_RCEA11_RESETVAL  (0x0000u)
/*----RCEA11 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA11_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERA_RCEA11_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERA_RCEA10_MASK      (0x0400u)
#define CSL_MCBSP_RCERA_RCEA10_SHIFT     (0x000Au)
#define CSL_MCBSP_RCERA_RCEA10_RESETVAL  (0x0000u)
/*----RCEA10 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA10_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERA_RCEA10_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERA_RCEA9_MASK       (0x0200u)
#define CSL_MCBSP_RCERA_RCEA9_SHIFT      (0x0009u)
#define CSL_MCBSP_RCERA_RCEA9_RESETVAL   (0x0000u)
/*----RCEA9 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA9_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA9_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA8_MASK       (0x0100u)
#define CSL_MCBSP_RCERA_RCEA8_SHIFT      (0x0008u)
#define CSL_MCBSP_RCERA_RCEA8_RESETVAL   (0x0000u)
/*----RCEA8 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA8_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA8_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA7_MASK       (0x0080u)
#define CSL_MCBSP_RCERA_RCEA7_SHIFT      (0x0007u)
#define CSL_MCBSP_RCERA_RCEA7_RESETVAL   (0x0000u)
/*----RCEA7 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA7_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA7_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA6_MASK       (0x0040u)
#define CSL_MCBSP_RCERA_RCEA6_SHIFT      (0x0006u)
#define CSL_MCBSP_RCERA_RCEA6_RESETVAL   (0x0000u)
/*----RCEA6 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA6_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA6_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA5_MASK       (0x0020u)
#define CSL_MCBSP_RCERA_RCEA5_SHIFT      (0x0005u)
#define CSL_MCBSP_RCERA_RCEA5_RESETVAL   (0x0000u)
/*----RCEA5 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA5_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA5_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA4_MASK       (0x0010u)
#define CSL_MCBSP_RCERA_RCEA4_SHIFT      (0x0004u)
#define CSL_MCBSP_RCERA_RCEA4_RESETVAL   (0x0000u)
/*----RCEA4 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA4_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA4_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA3_MASK       (0x0008u)
#define CSL_MCBSP_RCERA_RCEA3_SHIFT      (0x0003u)
#define CSL_MCBSP_RCERA_RCEA3_RESETVAL   (0x0000u)
/*----RCEA3 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA3_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA3_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA2_MASK       (0x0004u)
#define CSL_MCBSP_RCERA_RCEA2_SHIFT      (0x0002u)
#define CSL_MCBSP_RCERA_RCEA2_RESETVAL   (0x0000u)
/*----RCEA2 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA2_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA2_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA1_MASK       (0x0002u)
#define CSL_MCBSP_RCERA_RCEA1_SHIFT      (0x0001u)
#define CSL_MCBSP_RCERA_RCEA1_RESETVAL   (0x0000u)
/*----RCEA1 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA1_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA1_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RCEA0_MASK       (0x0001u)
#define CSL_MCBSP_RCERA_RCEA0_SHIFT      (0x0000u)
#define CSL_MCBSP_RCERA_RCEA0_RESETVAL   (0x0000u)
/*----RCEA0 Tokens----*/
#define CSL_MCBSP_RCERA_RCEA0_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERA_RCEA0_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERA_RESETVAL         (0x0000u)

/* RCERB */

#define CSL_MCBSP_RCERB_RCEB15_MASK      (0x8000u)
#define CSL_MCBSP_RCERB_RCEB15_SHIFT     (0x000Fu)
#define CSL_MCBSP_RCERB_RCEB15_RESETVAL  (0x0000u)
/*----RCEB15 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB15_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERB_RCEB15_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERB_RCEB14_MASK      (0x4000u)
#define CSL_MCBSP_RCERB_RCEB14_SHIFT     (0x000Eu)
#define CSL_MCBSP_RCERB_RCEB14_RESETVAL  (0x0000u)
/*----RCEB14 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB14_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERB_RCEB14_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERB_RCEB13_MASK      (0x2000u)
#define CSL_MCBSP_RCERB_RCEB13_SHIFT     (0x000Du)
#define CSL_MCBSP_RCERB_RCEB13_RESETVAL  (0x0000u)
/*----RCEB13 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB13_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERB_RCEB13_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERB_RCEB12_MASK      (0x1000u)
#define CSL_MCBSP_RCERB_RCEB12_SHIFT     (0x000Cu)
#define CSL_MCBSP_RCERB_RCEB12_RESETVAL  (0x0000u)
/*----RCEB12 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB12_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERB_RCEB12_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERB_RCEB11_MASK      (0x0800u)
#define CSL_MCBSP_RCERB_RCEB11_SHIFT     (0x000Bu)
#define CSL_MCBSP_RCERB_RCEB11_RESETVAL  (0x0000u)
/*----RCEB11 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB11_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERB_RCEB11_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERB_RCEB10_MASK      (0x0400u)
#define CSL_MCBSP_RCERB_RCEB10_SHIFT     (0x000Au)
#define CSL_MCBSP_RCERB_RCEB10_RESETVAL  (0x0000u)
/*----RCEB10 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB10_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERB_RCEB10_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERB_RCEB9_MASK       (0x0200u)
#define CSL_MCBSP_RCERB_RCEB9_SHIFT      (0x0009u)
#define CSL_MCBSP_RCERB_RCEB9_RESETVAL   (0x0000u)
/*----RCEB9 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB9_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB9_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB8_MASK       (0x0100u)
#define CSL_MCBSP_RCERB_RCEB8_SHIFT      (0x0008u)
#define CSL_MCBSP_RCERB_RCEB8_RESETVAL   (0x0000u)
/*----RCEB8 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB8_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB8_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB7_MASK       (0x0080u)
#define CSL_MCBSP_RCERB_RCEB7_SHIFT      (0x0007u)
#define CSL_MCBSP_RCERB_RCEB7_RESETVAL   (0x0000u)
/*----RCEB7 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB7_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB7_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB6_MASK       (0x0040u)
#define CSL_MCBSP_RCERB_RCEB6_SHIFT      (0x0006u)
#define CSL_MCBSP_RCERB_RCEB6_RESETVAL   (0x0000u)
/*----RCEB6 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB6_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB6_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB5_MASK       (0x0020u)
#define CSL_MCBSP_RCERB_RCEB5_SHIFT      (0x0005u)
#define CSL_MCBSP_RCERB_RCEB5_RESETVAL   (0x0000u)
/*----RCEB5 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB5_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB5_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB4_MASK       (0x0010u)
#define CSL_MCBSP_RCERB_RCEB4_SHIFT      (0x0004u)
#define CSL_MCBSP_RCERB_RCEB4_RESETVAL   (0x0000u)
/*----RCEB4 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB4_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB4_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB3_MASK       (0x0008u)
#define CSL_MCBSP_RCERB_RCEB3_SHIFT      (0x0003u)
#define CSL_MCBSP_RCERB_RCEB3_RESETVAL   (0x0000u)
/*----RCEB3 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB3_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB3_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB2_MASK       (0x0004u)
#define CSL_MCBSP_RCERB_RCEB2_SHIFT      (0x0002u)
#define CSL_MCBSP_RCERB_RCEB2_RESETVAL   (0x0000u)
/*----RCEB2 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB2_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB2_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB1_MASK       (0x0002u)
#define CSL_MCBSP_RCERB_RCEB1_SHIFT      (0x0001u)
#define CSL_MCBSP_RCERB_RCEB1_RESETVAL   (0x0000u)
/*----RCEB1 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB1_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB1_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RCEB0_MASK       (0x0001u)
#define CSL_MCBSP_RCERB_RCEB0_SHIFT      (0x0000u)
#define CSL_MCBSP_RCERB_RCEB0_RESETVAL   (0x0000u)
/*----RCEB0 Tokens----*/
#define CSL_MCBSP_RCERB_RCEB0_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERB_RCEB0_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERB_RESETVAL         (0x0000u)

/* XCERA */

#define CSL_MCBSP_XCERA_XCEA15_MASK      (0x8000u)
#define CSL_MCBSP_XCERA_XCEA15_SHIFT     (0x000Fu)
#define CSL_MCBSP_XCERA_XCEA15_RESETVAL  (0x0000u)
/*----XCEA15 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA15_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERA_XCEA15_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERA_XCEA14_MASK      (0x4000u)
#define CSL_MCBSP_XCERA_XCEA14_SHIFT     (0x000Eu)
#define CSL_MCBSP_XCERA_XCEA14_RESETVAL  (0x0000u)
/*----XCEA14 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA14_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERA_XCEA14_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERA_XCEA13_MASK      (0x2000u)
#define CSL_MCBSP_XCERA_XCEA13_SHIFT     (0x000Du)
#define CSL_MCBSP_XCERA_XCEA13_RESETVAL  (0x0000u)
/*----XCEA13 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA13_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERA_XCEA13_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERA_XCEA12_MASK      (0x1000u)
#define CSL_MCBSP_XCERA_XCEA12_SHIFT     (0x000Cu)
#define CSL_MCBSP_XCERA_XCEA12_RESETVAL  (0x0000u)
/*----XCEA12 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA12_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERA_XCEA12_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERA_XCEA11_MASK      (0x0800u)
#define CSL_MCBSP_XCERA_XCEA11_SHIFT     (0x000Bu)
#define CSL_MCBSP_XCERA_XCEA11_RESETVAL  (0x0000u)
/*----XCEA11 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA11_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERA_XCEA11_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERA_XCEA10_MASK      (0x0400u)
#define CSL_MCBSP_XCERA_XCEA10_SHIFT     (0x000Au)
#define CSL_MCBSP_XCERA_XCEA10_RESETVAL  (0x0000u)
/*----XCEA10 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA10_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERA_XCEA10_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERA_XCEA9_MASK       (0x0200u)
#define CSL_MCBSP_XCERA_XCEA9_SHIFT      (0x0009u)
#define CSL_MCBSP_XCERA_XCEA9_RESETVAL   (0x0000u)
/*----XCEA9 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA9_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA9_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA8_MASK       (0x0100u)
#define CSL_MCBSP_XCERA_XCEA8_SHIFT      (0x0008u)
#define CSL_MCBSP_XCERA_XCEA8_RESETVAL   (0x0000u)
/*----XCEA8 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA8_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA8_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA7_MASK       (0x0080u)
#define CSL_MCBSP_XCERA_XCEA7_SHIFT      (0x0007u)
#define CSL_MCBSP_XCERA_XCEA7_RESETVAL   (0x0000u)
/*----XCEA7 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA7_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA7_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA6_MASK       (0x0040u)
#define CSL_MCBSP_XCERA_XCEA6_SHIFT      (0x0006u)
#define CSL_MCBSP_XCERA_XCEA6_RESETVAL   (0x0000u)
/*----XCEA6 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA6_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA6_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA5_MASK       (0x0020u)
#define CSL_MCBSP_XCERA_XCEA5_SHIFT      (0x0005u)
#define CSL_MCBSP_XCERA_XCEA5_RESETVAL   (0x0000u)
/*----XCEA5 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA5_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA5_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA4_MASK       (0x0010u)
#define CSL_MCBSP_XCERA_XCEA4_SHIFT      (0x0004u)
#define CSL_MCBSP_XCERA_XCEA4_RESETVAL   (0x0000u)
/*----XCEA4 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA4_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA4_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA3_MASK       (0x0008u)
#define CSL_MCBSP_XCERA_XCEA3_SHIFT      (0x0003u)
#define CSL_MCBSP_XCERA_XCEA3_RESETVAL   (0x0000u)
/*----XCEA3 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA3_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA3_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA2_MASK       (0x0004u)
#define CSL_MCBSP_XCERA_XCEA2_SHIFT      (0x0002u)
#define CSL_MCBSP_XCERA_XCEA2_RESETVAL   (0x0000u)
/*----XCEA2 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA2_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA2_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA1_MASK       (0x0002u)
#define CSL_MCBSP_XCERA_XCEA1_SHIFT      (0x0001u)
#define CSL_MCBSP_XCERA_XCEA1_RESETVAL   (0x0000u)
/*----XCEA1 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA1_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA1_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_XCEA0_MASK       (0x0001u)
#define CSL_MCBSP_XCERA_XCEA0_SHIFT      (0x0000u)
#define CSL_MCBSP_XCERA_XCEA0_RESETVAL   (0x0000u)
/*----XCEA0 Tokens----*/
#define CSL_MCBSP_XCERA_XCEA0_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERA_XCEA0_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERA_RESETVAL         (0x0000u)

/* XCERB */

#define CSL_MCBSP_XCERB_XCEB15_MASK      (0x8000u)
#define CSL_MCBSP_XCERB_XCEB15_SHIFT     (0x000Fu)
#define CSL_MCBSP_XCERB_XCEB15_RESETVAL  (0x0000u)
/*----XCEB15 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB15_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERB_XCEB15_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERB_XCEB14_MASK      (0x4000u)
#define CSL_MCBSP_XCERB_XCEB14_SHIFT     (0x000Eu)
#define CSL_MCBSP_XCERB_XCEB14_RESETVAL  (0x0000u)
/*----XCEB14 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB14_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERB_XCEB14_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERB_XCEB13_MASK      (0x2000u)
#define CSL_MCBSP_XCERB_XCEB13_SHIFT     (0x000Du)
#define CSL_MCBSP_XCERB_XCEB13_RESETVAL  (0x0000u)
/*----XCEB13 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB13_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERB_XCEB13_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERB_XCEB12_MASK      (0x1000u)
#define CSL_MCBSP_XCERB_XCEB12_SHIFT     (0x000Cu)
#define CSL_MCBSP_XCERB_XCEB12_RESETVAL  (0x0000u)
/*----XCEB12 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB12_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERB_XCEB12_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERB_XCEB11_MASK      (0x0800u)
#define CSL_MCBSP_XCERB_XCEB11_SHIFT     (0x000Bu)
#define CSL_MCBSP_XCERB_XCEB11_RESETVAL  (0x0000u)
/*----XCEB11 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB11_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERB_XCEB11_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERB_XCEB10_MASK      (0x0400u)
#define CSL_MCBSP_XCERB_XCEB10_SHIFT     (0x000Au)
#define CSL_MCBSP_XCERB_XCEB10_RESETVAL  (0x0000u)
/*----XCEB10 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB10_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERB_XCEB10_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERB_XCEB9_MASK       (0x0200u)
#define CSL_MCBSP_XCERB_XCEB9_SHIFT      (0x0009u)
#define CSL_MCBSP_XCERB_XCEB9_RESETVAL   (0x0000u)
/*----XCEB9 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB9_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB9_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB8_MASK       (0x0100u)
#define CSL_MCBSP_XCERB_XCEB8_SHIFT      (0x0008u)
#define CSL_MCBSP_XCERB_XCEB8_RESETVAL   (0x0000u)
/*----XCEB8 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB8_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB8_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB7_MASK       (0x0080u)
#define CSL_MCBSP_XCERB_XCEB7_SHIFT      (0x0007u)
#define CSL_MCBSP_XCERB_XCEB7_RESETVAL   (0x0000u)
/*----XCEB7 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB7_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB7_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB6_MASK       (0x0040u)
#define CSL_MCBSP_XCERB_XCEB6_SHIFT      (0x0006u)
#define CSL_MCBSP_XCERB_XCEB6_RESETVAL   (0x0000u)
/*----XCEB6 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB6_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB6_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB5_MASK       (0x0020u)
#define CSL_MCBSP_XCERB_XCEB5_SHIFT      (0x0005u)
#define CSL_MCBSP_XCERB_XCEB5_RESETVAL   (0x0000u)
/*----XCEB5 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB5_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB5_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB4_MASK       (0x0010u)
#define CSL_MCBSP_XCERB_XCEB4_SHIFT      (0x0004u)
#define CSL_MCBSP_XCERB_XCEB4_RESETVAL   (0x0000u)
/*----XCEB4 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB4_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB4_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB3_MASK       (0x0008u)
#define CSL_MCBSP_XCERB_XCEB3_SHIFT      (0x0003u)
#define CSL_MCBSP_XCERB_XCEB3_RESETVAL   (0x0000u)
/*----XCEB3 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB3_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB3_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB2_MASK       (0x0004u)
#define CSL_MCBSP_XCERB_XCEB2_SHIFT      (0x0002u)
#define CSL_MCBSP_XCERB_XCEB2_RESETVAL   (0x0000u)
/*----XCEB2 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB2_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB2_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB1_MASK       (0x0002u)
#define CSL_MCBSP_XCERB_XCEB1_SHIFT      (0x0001u)
#define CSL_MCBSP_XCERB_XCEB1_RESETVAL   (0x0000u)
/*----XCEB1 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB1_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB1_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_XCEB0_MASK       (0x0001u)
#define CSL_MCBSP_XCERB_XCEB0_SHIFT      (0x0000u)
#define CSL_MCBSP_XCERB_XCEB0_RESETVAL   (0x0000u)
/*----XCEB0 Tokens----*/
#define CSL_MCBSP_XCERB_XCEB0_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERB_XCEB0_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERB_RESETVAL         (0x0000u)

/* PCRL */


#define CSL_MCBSP_PCRL_IDLE_EN_MASK      (0x4000u)
#define CSL_MCBSP_PCRL_IDLE_EN_SHIFT     (0x000Eu)
#define CSL_MCBSP_PCRL_IDLE_EN_RESETVAL  (0x0000u)
/*----IDLE_EN Tokens----*/
#define CSL_MCBSP_PCRL_IDLE_EN_RUNNING   (0x0000u)
#define CSL_MCBSP_PCRL_IDLE_EN_IDLE      (0x0001u)

#define CSL_MCBSP_PCRL_XIOEN_MASK        (0x2000u)
#define CSL_MCBSP_PCRL_XIOEN_SHIFT       (0x000Du)
#define CSL_MCBSP_PCRL_XIOEN_RESETVAL    (0x0000u)
/*----XIOEN Tokens----*/
#define CSL_MCBSP_PCRL_XIOEN_NOTGPIO     (0x0000u)
#define CSL_MCBSP_PCRL_XIOEN_GPIO        (0x0000u)

#define CSL_MCBSP_PCRL_RIOEN_MASK        (0x1000u)
#define CSL_MCBSP_PCRL_RIOEN_SHIFT       (0x000Cu)
#define CSL_MCBSP_PCRL_RIOEN_RESETVAL    (0x0000u)
/*----RIOEN Tokens----*/
#define CSL_MCBSP_PCRL_RIOEN_NOTGPIO     (0x0000u)
#define CSL_MCBSP_PCRL_RIOEN_GPIO        (0x0000u)

#define CSL_MCBSP_PCRL_FSXM_MASK         (0x0800u)
#define CSL_MCBSP_PCRL_FSXM_SHIFT        (0x000Bu)
#define CSL_MCBSP_PCRL_FSXM_RESETVAL     (0x0000u)
/*----FSXM Tokens----*/
#define CSL_MCBSP_PCRL_FSXM_ZERO         (0x0000u)
#define CSL_MCBSP_PCRL_FSXM_ONE          (0x0001u)

#define CSL_MCBSP_PCRL_FSRM_MASK         (0x0400u)
#define CSL_MCBSP_PCRL_FSRM_SHIFT        (0x000Au)
#define CSL_MCBSP_PCRL_FSRM_RESETVAL     (0x0000u)
/*----FSRM Tokens----*/
#define CSL_MCBSP_PCRL_FSRM_ZERO         (0x0000u)
#define CSL_MCBSP_PCRL_FSRM_ONE          (0x0001u)

#define CSL_MCBSP_PCRL_CLKXM_MASK        (0x0200u)
#define CSL_MCBSP_PCRL_CLKXM_SHIFT       (0x0009u)
#define CSL_MCBSP_PCRL_CLKXM_RESETVAL    (0x0000u)
/*----CLKXM Tokens----*/
#define CSL_MCBSP_PCRL_CLKXM_ZERO        (0x0000u)
#define CSL_MCBSP_PCRL_CLKXM_ONE         (0x0001u)

#define CSL_MCBSP_PCRL_CLKRM_MASK        (0x0100u)
#define CSL_MCBSP_PCRL_CLKRM_SHIFT       (0x0008u)
#define CSL_MCBSP_PCRL_CLKRM_RESETVAL    (0x0000u)
/*----CLKRM Tokens----*/
#define CSL_MCBSP_PCRL_CLKRM_ZERO        (0x0000u)
#define CSL_MCBSP_PCRL_CLKRM_ONE         (0x0001u)

#define CSL_MCBSP_PCRL_SCLKME_MASK       (0x0080u)
#define CSL_MCBSP_PCRL_SCLKME_SHIFT      (0x0007u)
#define CSL_MCBSP_PCRL_SCLKME_RESETVAL   (0x0000u)
/*----SCLKME Tokens----*/
#define CSL_MCBSP_PCRL_SCLKME_ZERO       (0x0000u)
#define CSL_MCBSP_PCRL_SCLKME_ONE        (0x0001u)

#define CSL_MCBSP_PCRL_CLKS_STAT_MASK    (0x0040u)
#define CSL_MCBSP_PCRL_CLKS_STAT_SHIFT   (0x0006u)
#define CSL_MCBSP_PCRL_CLKS_STAT_RESETVAL (0x0000u)
/*----CLKS_STAT Tokens----*/
#define CSL_MCBSP_PCRL_CLKS_STAT_LOW     (0x0000u)
#define CSL_MCBSP_PCRL_CLKS_STAT_HIGH    (0x0001u)

#define CSL_MCBSP_PCRL_DX_STAT_MASK      (0x0020u)
#define CSL_MCBSP_PCRL_DX_STAT_SHIFT     (0x0005u)
#define CSL_MCBSP_PCRL_DX_STAT_RESETVAL  (0x0000u)
/*----DX_STAT Tokens----*/
#define CSL_MCBSP_PCRL_DX_STAT_LOW       (0x0000u)
#define CSL_MCBSP_PCRL_DX_STAT_HIGH      (0x0001u)

#define CSL_MCBSP_PCRL_DR_STAT_MASK      (0x0010u)
#define CSL_MCBSP_PCRL_DR_STAT_SHIFT     (0x0004u)
#define CSL_MCBSP_PCRL_DR_STAT_RESETVAL  (0x0000u)
/*----DR_STAT Tokens----*/
#define CSL_MCBSP_PCRL_DR_STAT_LOW       (0x0000u)
#define CSL_MCBSP_PCRL_DR_STAT_HIGH      (0x0001u)

#define CSL_MCBSP_PCRL_FSXP_MASK         (0x0008u)
#define CSL_MCBSP_PCRL_FSXP_SHIFT        (0x0003u)
#define CSL_MCBSP_PCRL_FSXP_RESETVAL     (0x0000u)
/*----FSXP Tokens----*/
#define CSL_MCBSP_PCRL_FSXP_ACTIVEHIGH   (0x0000u)
#define CSL_MCBSP_PCRL_FSXP_ACTIVELOW    (0x0001u)

#define CSL_MCBSP_PCRL_FSRP_MASK         (0x0004u)
#define CSL_MCBSP_PCRL_FSRP_SHIFT        (0x0002u)
#define CSL_MCBSP_PCRL_FSRP_RESETVAL     (0x0000u)
/*----FSRP Tokens----*/
#define CSL_MCBSP_PCRL_FSRP_ACTIVEHIGH   (0x0000u)
#define CSL_MCBSP_PCRL_FSRP_ACTIVELOW    (0x0001u)

#define CSL_MCBSP_PCRL_CLKXP_MASK        (0x0002u)
#define CSL_MCBSP_PCRL_CLKXP_SHIFT       (0x0001u)
#define CSL_MCBSP_PCRL_CLKXP_RESETVAL    (0x0000u)
/*----CLKXP Tokens----*/
#define CSL_MCBSP_PCRL_CLKXP_RISINGEDGE  (0x0000u)
#define CSL_MCBSP_PCRL_CLKXP_FALLINGEDGE (0x0001u)

#define CSL_MCBSP_PCRL_CLKRP_MASK        (0x0001u)
#define CSL_MCBSP_PCRL_CLKRP_SHIFT       (0x0000u)
#define CSL_MCBSP_PCRL_CLKRP_RESETVAL    (0x0000u)
/*----CLKRP Tokens----*/
#define CSL_MCBSP_PCRL_CLKRP_FALLINGEDGE (0x0000u)
#define CSL_MCBSP_PCRL_CLKRP_RISINGEDGE  (0x0001u)

#define CSL_MCBSP_PCRL_RESETVAL          (0x0000u)

/* RCERC */

#define CSL_MCBSP_RCERC_RCEC15_MASK      (0x8000u)
#define CSL_MCBSP_RCERC_RCEC15_SHIFT     (0x000Fu)
#define CSL_MCBSP_RCERC_RCEC15_RESETVAL  (0x0000u)
/*----RCEC15 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC15_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERC_RCEC15_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERC_RCEC14_MASK      (0x4000u)
#define CSL_MCBSP_RCERC_RCEC14_SHIFT     (0x000Eu)
#define CSL_MCBSP_RCERC_RCEC14_RESETVAL  (0x0000u)
/*----RCEC14 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC14_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERC_RCEC14_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERC_RCEC13_MASK      (0x2000u)
#define CSL_MCBSP_RCERC_RCEC13_SHIFT     (0x000Du)
#define CSL_MCBSP_RCERC_RCEC13_RESETVAL  (0x0000u)
/*----RCEC13 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC13_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERC_RCEC13_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERC_RCEC12_MASK      (0x1000u)
#define CSL_MCBSP_RCERC_RCEC12_SHIFT     (0x000Cu)
#define CSL_MCBSP_RCERC_RCEC12_RESETVAL  (0x0000u)
/*----RCEC12 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC12_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERC_RCEC12_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERC_RCEC11_MASK      (0x0800u)
#define CSL_MCBSP_RCERC_RCEC11_SHIFT     (0x000Bu)
#define CSL_MCBSP_RCERC_RCEC11_RESETVAL  (0x0000u)
/*----RCEC11 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC11_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERC_RCEC11_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERC_RCEC10_MASK      (0x0400u)
#define CSL_MCBSP_RCERC_RCEC10_SHIFT     (0x000Au)
#define CSL_MCBSP_RCERC_RCEC10_RESETVAL  (0x0000u)
/*----RCEC10 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC10_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERC_RCEC10_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERC_RCEC9_MASK       (0x0200u)
#define CSL_MCBSP_RCERC_RCEC9_SHIFT      (0x0009u)
#define CSL_MCBSP_RCERC_RCEC9_RESETVAL   (0x0000u)
/*----RCEC9 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC9_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC9_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC8_MASK       (0x0100u)
#define CSL_MCBSP_RCERC_RCEC8_SHIFT      (0x0008u)
#define CSL_MCBSP_RCERC_RCEC8_RESETVAL   (0x0000u)
/*----RCEC8 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC8_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC8_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC7_MASK       (0x0080u)
#define CSL_MCBSP_RCERC_RCEC7_SHIFT      (0x0007u)
#define CSL_MCBSP_RCERC_RCEC7_RESETVAL   (0x0000u)
/*----RCEC7 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC7_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC7_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC6_MASK       (0x0040u)
#define CSL_MCBSP_RCERC_RCEC6_SHIFT      (0x0006u)
#define CSL_MCBSP_RCERC_RCEC6_RESETVAL   (0x0000u)
/*----RCEC6 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC6_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC6_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC5_MASK       (0x0020u)
#define CSL_MCBSP_RCERC_RCEC5_SHIFT      (0x0005u)
#define CSL_MCBSP_RCERC_RCEC5_RESETVAL   (0x0000u)
/*----RCEC5 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC5_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC5_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC4_MASK       (0x0010u)
#define CSL_MCBSP_RCERC_RCEC4_SHIFT      (0x0004u)
#define CSL_MCBSP_RCERC_RCEC4_RESETVAL   (0x0000u)
/*----RCEC4 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC4_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC4_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC3_MASK       (0x0008u)
#define CSL_MCBSP_RCERC_RCEC3_SHIFT      (0x0003u)
#define CSL_MCBSP_RCERC_RCEC3_RESETVAL   (0x0000u)
/*----RCEC3 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC3_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC3_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC2_MASK       (0x0004u)
#define CSL_MCBSP_RCERC_RCEC2_SHIFT      (0x0002u)
#define CSL_MCBSP_RCERC_RCEC2_RESETVAL   (0x0000u)
/*----RCEC2 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC2_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC2_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC1_MASK       (0x0002u)
#define CSL_MCBSP_RCERC_RCEC1_SHIFT      (0x0001u)
#define CSL_MCBSP_RCERC_RCEC1_RESETVAL   (0x0000u)
/*----RCEC1 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC1_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC1_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RCEC0_MASK       (0x0001u)
#define CSL_MCBSP_RCERC_RCEC0_SHIFT      (0x0000u)
#define CSL_MCBSP_RCERC_RCEC0_RESETVAL   (0x0000u)
/*----RCEC0 Tokens----*/
#define CSL_MCBSP_RCERC_RCEC0_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERC_RCEC0_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERC_RESETVAL         (0x0000u)

/* RCERD */

#define CSL_MCBSP_RCERD_RCED15_MASK      (0x8000u)
#define CSL_MCBSP_RCERD_RCED15_SHIFT     (0x000Fu)
#define CSL_MCBSP_RCERD_RCED15_RESETVAL  (0x0000u)
/*----RCED15 Tokens----*/
#define CSL_MCBSP_RCERD_RCED15_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERD_RCED15_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERD_RCED14_MASK      (0x4000u)
#define CSL_MCBSP_RCERD_RCED14_SHIFT     (0x000Eu)
#define CSL_MCBSP_RCERD_RCED14_RESETVAL  (0x0000u)
/*----RCED14 Tokens----*/
#define CSL_MCBSP_RCERD_RCED14_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERD_RCED14_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERD_RCED13_MASK      (0x2000u)
#define CSL_MCBSP_RCERD_RCED13_SHIFT     (0x000Du)
#define CSL_MCBSP_RCERD_RCED13_RESETVAL  (0x0000u)
/*----RCED13 Tokens----*/
#define CSL_MCBSP_RCERD_RCED13_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERD_RCED13_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERD_RCED12_MASK      (0x1000u)
#define CSL_MCBSP_RCERD_RCED12_SHIFT     (0x000Cu)
#define CSL_MCBSP_RCERD_RCED12_RESETVAL  (0x0000u)
/*----RCED12 Tokens----*/
#define CSL_MCBSP_RCERD_RCED12_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERD_RCED12_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERD_RCED11_MASK      (0x0800u)
#define CSL_MCBSP_RCERD_RCED11_SHIFT     (0x000Bu)
#define CSL_MCBSP_RCERD_RCED11_RESETVAL  (0x0000u)
/*----RCED11 Tokens----*/
#define CSL_MCBSP_RCERD_RCED11_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERD_RCED11_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERD_RCED10_MASK      (0x0400u)
#define CSL_MCBSP_RCERD_RCED10_SHIFT     (0x000Au)
#define CSL_MCBSP_RCERD_RCED10_RESETVAL  (0x0000u)
/*----RCED10 Tokens----*/
#define CSL_MCBSP_RCERD_RCED10_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERD_RCED10_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERD_RCED9_MASK       (0x0200u)
#define CSL_MCBSP_RCERD_RCED9_SHIFT      (0x0009u)
#define CSL_MCBSP_RCERD_RCED9_RESETVAL   (0x0000u)
/*----RCED9 Tokens----*/
#define CSL_MCBSP_RCERD_RCED9_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED9_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED8_MASK       (0x0100u)
#define CSL_MCBSP_RCERD_RCED8_SHIFT      (0x0008u)
#define CSL_MCBSP_RCERD_RCED8_RESETVAL   (0x0000u)
/*----RCED8 Tokens----*/
#define CSL_MCBSP_RCERD_RCED8_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED8_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED7_MASK       (0x0080u)
#define CSL_MCBSP_RCERD_RCED7_SHIFT      (0x0007u)
#define CSL_MCBSP_RCERD_RCED7_RESETVAL   (0x0000u)
/*----RCED7 Tokens----*/
#define CSL_MCBSP_RCERD_RCED7_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED7_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED6_MASK       (0x0040u)
#define CSL_MCBSP_RCERD_RCED6_SHIFT      (0x0006u)
#define CSL_MCBSP_RCERD_RCED6_RESETVAL   (0x0000u)
/*----RCED6 Tokens----*/
#define CSL_MCBSP_RCERD_RCED6_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED6_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED5_MASK       (0x0020u)
#define CSL_MCBSP_RCERD_RCED5_SHIFT      (0x0005u)
#define CSL_MCBSP_RCERD_RCED5_RESETVAL   (0x0000u)
/*----RCED5 Tokens----*/
#define CSL_MCBSP_RCERD_RCED5_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED5_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED4_MASK       (0x0010u)
#define CSL_MCBSP_RCERD_RCED4_SHIFT      (0x0004u)
#define CSL_MCBSP_RCERD_RCED4_RESETVAL   (0x0000u)
/*----RCED4 Tokens----*/
#define CSL_MCBSP_RCERD_RCED4_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED4_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED3_MASK       (0x0008u)
#define CSL_MCBSP_RCERD_RCED3_SHIFT      (0x0003u)
#define CSL_MCBSP_RCERD_RCED3_RESETVAL   (0x0000u)
/*----RCED3 Tokens----*/
#define CSL_MCBSP_RCERD_RCED3_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED3_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED2_MASK       (0x0004u)
#define CSL_MCBSP_RCERD_RCED2_SHIFT      (0x0002u)
#define CSL_MCBSP_RCERD_RCED2_RESETVAL   (0x0000u)
/*----RCED2 Tokens----*/
#define CSL_MCBSP_RCERD_RCED2_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED2_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED1_MASK       (0x0002u)
#define CSL_MCBSP_RCERD_RCED1_SHIFT      (0x0001u)
#define CSL_MCBSP_RCERD_RCED1_RESETVAL   (0x0000u)
/*----RCED1 Tokens----*/
#define CSL_MCBSP_RCERD_RCED1_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED1_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RCED0_MASK       (0x0001u)
#define CSL_MCBSP_RCERD_RCED0_SHIFT      (0x0000u)
#define CSL_MCBSP_RCERD_RCED0_RESETVAL   (0x0000u)
/*----RCED0 Tokens----*/
#define CSL_MCBSP_RCERD_RCED0_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERD_RCED0_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERD_RESETVAL         (0x0000u)

/* XCERC */

#define CSL_MCBSP_XCERC_XCEC15_MASK      (0x8000u)
#define CSL_MCBSP_XCERC_XCEC15_SHIFT     (0x000Fu)
#define CSL_MCBSP_XCERC_XCEC15_RESETVAL  (0x0000u)
/*----XCEC15 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC15_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERC_XCEC15_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERC_XCEC14_MASK      (0x4000u)
#define CSL_MCBSP_XCERC_XCEC14_SHIFT     (0x000Eu)
#define CSL_MCBSP_XCERC_XCEC14_RESETVAL  (0x0000u)
/*----XCEC14 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC14_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERC_XCEC14_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERC_XCEC13_MASK      (0x2000u)
#define CSL_MCBSP_XCERC_XCEC13_SHIFT     (0x000Du)
#define CSL_MCBSP_XCERC_XCEC13_RESETVAL  (0x0000u)
/*----XCEC13 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC13_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERC_XCEC13_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERC_XCEC12_MASK      (0x1000u)
#define CSL_MCBSP_XCERC_XCEC12_SHIFT     (0x000Cu)
#define CSL_MCBSP_XCERC_XCEC12_RESETVAL  (0x0000u)
/*----XCEC12 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC12_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERC_XCEC12_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERC_XCEC11_MASK      (0x0800u)
#define CSL_MCBSP_XCERC_XCEC11_SHIFT     (0x000Bu)
#define CSL_MCBSP_XCERC_XCEC11_RESETVAL  (0x0000u)
/*----XCEC11 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC11_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERC_XCEC11_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERC_XCEC10_MASK      (0x0400u)
#define CSL_MCBSP_XCERC_XCEC10_SHIFT     (0x000Au)
#define CSL_MCBSP_XCERC_XCEC10_RESETVAL  (0x0000u)
/*----XCEC10 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC10_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERC_XCEC10_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERC_XCEC9_MASK       (0x0200u)
#define CSL_MCBSP_XCERC_XCEC9_SHIFT      (0x0009u)
#define CSL_MCBSP_XCERC_XCEC9_RESETVAL   (0x0000u)
/*----XCEC9 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC9_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC9_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC8_MASK       (0x0100u)
#define CSL_MCBSP_XCERC_XCEC8_SHIFT      (0x0008u)
#define CSL_MCBSP_XCERC_XCEC8_RESETVAL   (0x0000u)
/*----XCEC8 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC8_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC8_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC7_MASK       (0x0080u)
#define CSL_MCBSP_XCERC_XCEC7_SHIFT      (0x0007u)
#define CSL_MCBSP_XCERC_XCEC7_RESETVAL   (0x0000u)
/*----XCEC7 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC7_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC7_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC6_MASK       (0x0040u)
#define CSL_MCBSP_XCERC_XCEC6_SHIFT      (0x0006u)
#define CSL_MCBSP_XCERC_XCEC6_RESETVAL   (0x0000u)
/*----XCEC6 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC6_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC6_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC5_MASK       (0x0020u)
#define CSL_MCBSP_XCERC_XCEC5_SHIFT      (0x0005u)
#define CSL_MCBSP_XCERC_XCEC5_RESETVAL   (0x0000u)
/*----XCEC5 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC5_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC5_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC4_MASK       (0x0010u)
#define CSL_MCBSP_XCERC_XCEC4_SHIFT      (0x0004u)
#define CSL_MCBSP_XCERC_XCEC4_RESETVAL   (0x0000u)
/*----XCEC4 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC4_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC4_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC3_MASK       (0x0008u)
#define CSL_MCBSP_XCERC_XCEC3_SHIFT      (0x0003u)
#define CSL_MCBSP_XCERC_XCEC3_RESETVAL   (0x0000u)
/*----XCEC3 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC3_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC3_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC2_MASK       (0x0004u)
#define CSL_MCBSP_XCERC_XCEC2_SHIFT      (0x0002u)
#define CSL_MCBSP_XCERC_XCEC2_RESETVAL   (0x0000u)
/*----XCEC2 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC2_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC2_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC1_MASK       (0x0002u)
#define CSL_MCBSP_XCERC_XCEC1_SHIFT      (0x0001u)
#define CSL_MCBSP_XCERC_XCEC1_RESETVAL   (0x0000u)
/*----XCEC1 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC1_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC1_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_XCEC0_MASK       (0x0001u)
#define CSL_MCBSP_XCERC_XCEC0_SHIFT      (0x0000u)
#define CSL_MCBSP_XCERC_XCEC0_RESETVAL   (0x0000u)
/*----XCEC0 Tokens----*/
#define CSL_MCBSP_XCERC_XCEC0_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERC_XCEC0_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERC_RESETVAL         (0x0000u)

/* XCERD */

#define CSL_MCBSP_XCERD_XCED15_MASK      (0x8000u)
#define CSL_MCBSP_XCERD_XCED15_SHIFT     (0x000Fu)
#define CSL_MCBSP_XCERD_XCED15_RESETVAL  (0x0000u)
/*----XCED15 Tokens----*/
#define CSL_MCBSP_XCERD_XCED15_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERD_XCED15_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERD_XCED14_MASK      (0x4000u)
#define CSL_MCBSP_XCERD_XCED14_SHIFT     (0x000Eu)
#define CSL_MCBSP_XCERD_XCED14_RESETVAL  (0x0000u)
/*----XCED14 Tokens----*/
#define CSL_MCBSP_XCERD_XCED14_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERD_XCED14_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERD_XCED13_MASK      (0x2000u)
#define CSL_MCBSP_XCERD_XCED13_SHIFT     (0x000Du)
#define CSL_MCBSP_XCERD_XCED13_RESETVAL  (0x0000u)
/*----XCED13 Tokens----*/
#define CSL_MCBSP_XCERD_XCED13_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERD_XCED13_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERD_XCED12_MASK      (0x1000u)
#define CSL_MCBSP_XCERD_XCED12_SHIFT     (0x000Cu)
#define CSL_MCBSP_XCERD_XCED12_RESETVAL  (0x0000u)
/*----XCED12 Tokens----*/
#define CSL_MCBSP_XCERD_XCED12_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERD_XCED12_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERD_XCED11_MASK      (0x0800u)
#define CSL_MCBSP_XCERD_XCED11_SHIFT     (0x000Bu)
#define CSL_MCBSP_XCERD_XCED11_RESETVAL  (0x0000u)
/*----XCED11 Tokens----*/
#define CSL_MCBSP_XCERD_XCED11_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERD_XCED11_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERD_XCED10_MASK      (0x0400u)
#define CSL_MCBSP_XCERD_XCED10_SHIFT     (0x000Au)
#define CSL_MCBSP_XCERD_XCED10_RESETVAL  (0x0000u)
/*----XCED10 Tokens----*/
#define CSL_MCBSP_XCERD_XCED10_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERD_XCED10_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERD_XCED9_MASK       (0x0200u)
#define CSL_MCBSP_XCERD_XCED9_SHIFT      (0x0009u)
#define CSL_MCBSP_XCERD_XCED9_RESETVAL   (0x0000u)
/*----XCED9 Tokens----*/
#define CSL_MCBSP_XCERD_XCED9_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED9_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED8_MASK       (0x0100u)
#define CSL_MCBSP_XCERD_XCED8_SHIFT      (0x0008u)
#define CSL_MCBSP_XCERD_XCED8_RESETVAL   (0x0000u)
/*----XCED8 Tokens----*/
#define CSL_MCBSP_XCERD_XCED8_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED8_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED7_MASK       (0x0080u)
#define CSL_MCBSP_XCERD_XCED7_SHIFT      (0x0007u)
#define CSL_MCBSP_XCERD_XCED7_RESETVAL   (0x0000u)
/*----XCED7 Tokens----*/
#define CSL_MCBSP_XCERD_XCED7_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED7_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED6_MASK       (0x0040u)
#define CSL_MCBSP_XCERD_XCED6_SHIFT      (0x0006u)
#define CSL_MCBSP_XCERD_XCED6_RESETVAL   (0x0000u)
/*----XCED6 Tokens----*/
#define CSL_MCBSP_XCERD_XCED6_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED6_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED5_MASK       (0x0020u)
#define CSL_MCBSP_XCERD_XCED5_SHIFT      (0x0005u)
#define CSL_MCBSP_XCERD_XCED5_RESETVAL   (0x0000u)
/*----XCED5 Tokens----*/
#define CSL_MCBSP_XCERD_XCED5_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED5_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED4_MASK       (0x0010u)
#define CSL_MCBSP_XCERD_XCED4_SHIFT      (0x0004u)
#define CSL_MCBSP_XCERD_XCED4_RESETVAL   (0x0000u)
/*----XCED4 Tokens----*/
#define CSL_MCBSP_XCERD_XCED4_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED4_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED3_MASK       (0x0008u)
#define CSL_MCBSP_XCERD_XCED3_SHIFT      (0x0003u)
#define CSL_MCBSP_XCERD_XCED3_RESETVAL   (0x0000u)
/*----XCED3 Tokens----*/
#define CSL_MCBSP_XCERD_XCED3_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED3_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED2_MASK       (0x0004u)
#define CSL_MCBSP_XCERD_XCED2_SHIFT      (0x0002u)
#define CSL_MCBSP_XCERD_XCED2_RESETVAL   (0x0000u)
/*----XCED2 Tokens----*/
#define CSL_MCBSP_XCERD_XCED2_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED2_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED1_MASK       (0x0002u)
#define CSL_MCBSP_XCERD_XCED1_SHIFT      (0x0001u)
#define CSL_MCBSP_XCERD_XCED1_RESETVAL   (0x0000u)
/*----XCED1 Tokens----*/
#define CSL_MCBSP_XCERD_XCED1_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED1_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_XCED0_MASK       (0x0001u)
#define CSL_MCBSP_XCERD_XCED0_SHIFT      (0x0000u)
#define CSL_MCBSP_XCERD_XCED0_RESETVAL   (0x0000u)
/*----XCED0 Tokens----*/
#define CSL_MCBSP_XCERD_XCED0_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERD_XCED0_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERD_RESETVAL         (0x0000u)

/* RCERE */

#define CSL_MCBSP_RCERE_RCEE15_MASK      (0x8000u)
#define CSL_MCBSP_RCERE_RCEE15_SHIFT     (0x000Fu)
#define CSL_MCBSP_RCERE_RCEE15_RESETVAL  (0x0000u)
/*----RCEE15 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE15_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERE_RCEE15_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERE_RCEE14_MASK      (0x4000u)
#define CSL_MCBSP_RCERE_RCEE14_SHIFT     (0x000Eu)
#define CSL_MCBSP_RCERE_RCEE14_RESETVAL  (0x0000u)
/*----RCEE14 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE14_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERE_RCEE14_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERE_RCEE13_MASK      (0x2000u)
#define CSL_MCBSP_RCERE_RCEE13_SHIFT     (0x000Du)
#define CSL_MCBSP_RCERE_RCEE13_RESETVAL  (0x0000u)
/*----RCEE13 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE13_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERE_RCEE13_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERE_RCEE12_MASK      (0x1000u)
#define CSL_MCBSP_RCERE_RCEE12_SHIFT     (0x000Cu)
#define CSL_MCBSP_RCERE_RCEE12_RESETVAL  (0x0000u)
/*----RCEE12 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE12_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERE_RCEE12_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERE_RCEE11_MASK      (0x0800u)
#define CSL_MCBSP_RCERE_RCEE11_SHIFT     (0x000Bu)
#define CSL_MCBSP_RCERE_RCEE11_RESETVAL  (0x0000u)
/*----RCEE11 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE11_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERE_RCEE11_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERE_RCEE10_MASK      (0x0400u)
#define CSL_MCBSP_RCERE_RCEE10_SHIFT     (0x000Au)
#define CSL_MCBSP_RCERE_RCEE10_RESETVAL  (0x0000u)
/*----RCEE10 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE10_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERE_RCEE10_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERE_RCEE9_MASK       (0x0200u)
#define CSL_MCBSP_RCERE_RCEE9_SHIFT      (0x0009u)
#define CSL_MCBSP_RCERE_RCEE9_RESETVAL   (0x0000u)
/*----RCEE9 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE9_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE9_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE8_MASK       (0x0100u)
#define CSL_MCBSP_RCERE_RCEE8_SHIFT      (0x0008u)
#define CSL_MCBSP_RCERE_RCEE8_RESETVAL   (0x0000u)
/*----RCEE8 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE8_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE8_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE7_MASK       (0x0080u)
#define CSL_MCBSP_RCERE_RCEE7_SHIFT      (0x0007u)
#define CSL_MCBSP_RCERE_RCEE7_RESETVAL   (0x0000u)
/*----RCEE7 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE7_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE7_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE6_MASK       (0x0040u)
#define CSL_MCBSP_RCERE_RCEE6_SHIFT      (0x0006u)
#define CSL_MCBSP_RCERE_RCEE6_RESETVAL   (0x0000u)
/*----RCEE6 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE6_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE6_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE5_MASK       (0x0020u)
#define CSL_MCBSP_RCERE_RCEE5_SHIFT      (0x0005u)
#define CSL_MCBSP_RCERE_RCEE5_RESETVAL   (0x0000u)
/*----RCEE5 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE5_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE5_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE4_MASK       (0x0010u)
#define CSL_MCBSP_RCERE_RCEE4_SHIFT      (0x0004u)
#define CSL_MCBSP_RCERE_RCEE4_RESETVAL   (0x0000u)
/*----RCEE4 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE4_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE4_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE3_MASK       (0x0008u)
#define CSL_MCBSP_RCERE_RCEE3_SHIFT      (0x0003u)
#define CSL_MCBSP_RCERE_RCEE3_RESETVAL   (0x0000u)
/*----RCEE3 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE3_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE3_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE2_MASK       (0x0004u)
#define CSL_MCBSP_RCERE_RCEE2_SHIFT      (0x0002u)
#define CSL_MCBSP_RCERE_RCEE2_RESETVAL   (0x0000u)
/*----RCEE2 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE2_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE2_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE1_MASK       (0x0002u)
#define CSL_MCBSP_RCERE_RCEE1_SHIFT      (0x0001u)
#define CSL_MCBSP_RCERE_RCEE1_RESETVAL   (0x0000u)
/*----RCEE1 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE1_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE1_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RCEE0_MASK       (0x0001u)
#define CSL_MCBSP_RCERE_RCEE0_SHIFT      (0x0000u)
#define CSL_MCBSP_RCERE_RCEE0_RESETVAL   (0x0000u)
/*----RCEE0 Tokens----*/
#define CSL_MCBSP_RCERE_RCEE0_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERE_RCEE0_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERE_RESETVAL         (0x0000u)

/* RCERF */

#define CSL_MCBSP_RCERF_RCEF15_MASK      (0x8000u)
#define CSL_MCBSP_RCERF_RCEF15_SHIFT     (0x000Fu)
#define CSL_MCBSP_RCERF_RCEF15_RESETVAL  (0x0000u)
/*----RCEF15 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF15_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERF_RCEF15_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERF_RCEF14_MASK      (0x4000u)
#define CSL_MCBSP_RCERF_RCEF14_SHIFT     (0x000Eu)
#define CSL_MCBSP_RCERF_RCEF14_RESETVAL  (0x0000u)
/*----RCEF14 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF14_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERF_RCEF14_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERF_RCEF13_MASK      (0x2000u)
#define CSL_MCBSP_RCERF_RCEF13_SHIFT     (0x000Du)
#define CSL_MCBSP_RCERF_RCEF13_RESETVAL  (0x0000u)
/*----RCEF13 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF13_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERF_RCEF13_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERF_RCEF12_MASK      (0x1000u)
#define CSL_MCBSP_RCERF_RCEF12_SHIFT     (0x000Cu)
#define CSL_MCBSP_RCERF_RCEF12_RESETVAL  (0x0000u)
/*----RCEF12 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF12_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERF_RCEF12_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERF_RCEF11_MASK      (0x0800u)
#define CSL_MCBSP_RCERF_RCEF11_SHIFT     (0x000Bu)
#define CSL_MCBSP_RCERF_RCEF11_RESETVAL  (0x0000u)
/*----RCEF11 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF11_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERF_RCEF11_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERF_RCEF10_MASK      (0x0400u)
#define CSL_MCBSP_RCERF_RCEF10_SHIFT     (0x000Au)
#define CSL_MCBSP_RCERF_RCEF10_RESETVAL  (0x0000u)
/*----RCEF10 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF10_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERF_RCEF10_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERF_RCEF9_MASK       (0x0200u)
#define CSL_MCBSP_RCERF_RCEF9_SHIFT      (0x0009u)
#define CSL_MCBSP_RCERF_RCEF9_RESETVAL   (0x0000u)
/*----RCEF9 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF9_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF9_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF8_MASK       (0x0100u)
#define CSL_MCBSP_RCERF_RCEF8_SHIFT      (0x0008u)
#define CSL_MCBSP_RCERF_RCEF8_RESETVAL   (0x0000u)
/*----RCEF8 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF8_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF8_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF7_MASK       (0x0080u)
#define CSL_MCBSP_RCERF_RCEF7_SHIFT      (0x0007u)
#define CSL_MCBSP_RCERF_RCEF7_RESETVAL   (0x0000u)
/*----RCEF7 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF7_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF7_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF6_MASK       (0x0040u)
#define CSL_MCBSP_RCERF_RCEF6_SHIFT      (0x0006u)
#define CSL_MCBSP_RCERF_RCEF6_RESETVAL   (0x0000u)
/*----RCEF6 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF6_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF6_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF5_MASK       (0x0020u)
#define CSL_MCBSP_RCERF_RCEF5_SHIFT      (0x0005u)
#define CSL_MCBSP_RCERF_RCEF5_RESETVAL   (0x0000u)
/*----RCEF5 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF5_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF5_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF4_MASK       (0x0010u)
#define CSL_MCBSP_RCERF_RCEF4_SHIFT      (0x0004u)
#define CSL_MCBSP_RCERF_RCEF4_RESETVAL   (0x0000u)
/*----RCEF4 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF4_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF4_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF3_MASK       (0x0008u)
#define CSL_MCBSP_RCERF_RCEF3_SHIFT      (0x0003u)
#define CSL_MCBSP_RCERF_RCEF3_RESETVAL   (0x0000u)
/*----RCEF3 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF3_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF3_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF2_MASK       (0x0004u)
#define CSL_MCBSP_RCERF_RCEF2_SHIFT      (0x0002u)
#define CSL_MCBSP_RCERF_RCEF2_RESETVAL   (0x0000u)
/*----RCEF2 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF2_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF2_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF1_MASK       (0x0002u)
#define CSL_MCBSP_RCERF_RCEF1_SHIFT      (0x0001u)
#define CSL_MCBSP_RCERF_RCEF1_RESETVAL   (0x0000u)
/*----RCEF1 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF1_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF1_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RCEF0_MASK       (0x0001u)
#define CSL_MCBSP_RCERF_RCEF0_SHIFT      (0x0000u)
#define CSL_MCBSP_RCERF_RCEF0_RESETVAL   (0x0000u)
/*----RCEF0 Tokens----*/
#define CSL_MCBSP_RCERF_RCEF0_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERF_RCEF0_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERF_RESETVAL         (0x0000u)

/* XCERE */

#define CSL_MCBSP_XCERE_XCEE15_MASK      (0x8000u)
#define CSL_MCBSP_XCERE_XCEE15_SHIFT     (0x000Fu)
#define CSL_MCBSP_XCERE_XCEE15_RESETVAL  (0x0000u)
/*----XCEE15 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE15_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERE_XCEE15_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERE_XCEE14_MASK      (0x4000u)
#define CSL_MCBSP_XCERE_XCEE14_SHIFT     (0x000Eu)
#define CSL_MCBSP_XCERE_XCEE14_RESETVAL  (0x0000u)
/*----XCEE14 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE14_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERE_XCEE14_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERE_XCEE13_MASK      (0x2000u)
#define CSL_MCBSP_XCERE_XCEE13_SHIFT     (0x000Du)
#define CSL_MCBSP_XCERE_XCEE13_RESETVAL  (0x0000u)
/*----XCEE13 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE13_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERE_XCEE13_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERE_XCEE12_MASK      (0x1000u)
#define CSL_MCBSP_XCERE_XCEE12_SHIFT     (0x000Cu)
#define CSL_MCBSP_XCERE_XCEE12_RESETVAL  (0x0000u)
/*----XCEE12 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE12_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERE_XCEE12_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERE_XCEE11_MASK      (0x0800u)
#define CSL_MCBSP_XCERE_XCEE11_SHIFT     (0x000Bu)
#define CSL_MCBSP_XCERE_XCEE11_RESETVAL  (0x0000u)
/*----XCEE11 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE11_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERE_XCEE11_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERE_XCEE10_MASK      (0x0400u)
#define CSL_MCBSP_XCERE_XCEE10_SHIFT     (0x000Au)
#define CSL_MCBSP_XCERE_XCEE10_RESETVAL  (0x0000u)
/*----XCEE10 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE10_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERE_XCEE10_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERE_XCEE9_MASK       (0x0200u)
#define CSL_MCBSP_XCERE_XCEE9_SHIFT      (0x0009u)
#define CSL_MCBSP_XCERE_XCEE9_RESETVAL   (0x0000u)
/*----XCEE9 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE9_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE9_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE8_MASK       (0x0100u)
#define CSL_MCBSP_XCERE_XCEE8_SHIFT      (0x0008u)
#define CSL_MCBSP_XCERE_XCEE8_RESETVAL   (0x0000u)
/*----XCEE8 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE8_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE8_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE7_MASK       (0x0080u)
#define CSL_MCBSP_XCERE_XCEE7_SHIFT      (0x0007u)
#define CSL_MCBSP_XCERE_XCEE7_RESETVAL   (0x0000u)
/*----XCEE7 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE7_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE7_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE6_MASK       (0x0040u)
#define CSL_MCBSP_XCERE_XCEE6_SHIFT      (0x0006u)
#define CSL_MCBSP_XCERE_XCEE6_RESETVAL   (0x0000u)
/*----XCEE6 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE6_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE6_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE5_MASK       (0x0020u)
#define CSL_MCBSP_XCERE_XCEE5_SHIFT      (0x0005u)
#define CSL_MCBSP_XCERE_XCEE5_RESETVAL   (0x0000u)
/*----XCEE5 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE5_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE5_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE4_MASK       (0x0010u)
#define CSL_MCBSP_XCERE_XCEE4_SHIFT      (0x0004u)
#define CSL_MCBSP_XCERE_XCEE4_RESETVAL   (0x0000u)
/*----XCEE4 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE4_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE4_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE3_MASK       (0x0008u)
#define CSL_MCBSP_XCERE_XCEE3_SHIFT      (0x0003u)
#define CSL_MCBSP_XCERE_XCEE3_RESETVAL   (0x0000u)
/*----XCEE3 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE3_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE3_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE2_MASK       (0x0004u)
#define CSL_MCBSP_XCERE_XCEE2_SHIFT      (0x0002u)
#define CSL_MCBSP_XCERE_XCEE2_RESETVAL   (0x0000u)
/*----XCEE2 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE2_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE2_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE1_MASK       (0x0002u)
#define CSL_MCBSP_XCERE_XCEE1_SHIFT      (0x0001u)
#define CSL_MCBSP_XCERE_XCEE1_RESETVAL   (0x0000u)
/*----XCEE1 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE1_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE1_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_XCEE0_MASK       (0x0001u)
#define CSL_MCBSP_XCERE_XCEE0_SHIFT      (0x0000u)
#define CSL_MCBSP_XCERE_XCEE0_RESETVAL   (0x0000u)
/*----XCEE0 Tokens----*/
#define CSL_MCBSP_XCERE_XCEE0_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERE_XCEE0_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERE_RESETVAL         (0x0000u)

/* XCERF */

#define CSL_MCBSP_XCERF_XCEF15_MASK      (0x8000u)
#define CSL_MCBSP_XCERF_XCEF15_SHIFT     (0x000Fu)
#define CSL_MCBSP_XCERF_XCEF15_RESETVAL  (0x0000u)
/*----XCEF15 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF15_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERF_XCEF15_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERF_XCEF14_MASK      (0x4000u)
#define CSL_MCBSP_XCERF_XCEF14_SHIFT     (0x000Eu)
#define CSL_MCBSP_XCERF_XCEF14_RESETVAL  (0x0000u)
/*----XCEF14 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF14_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERF_XCEF14_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERF_XCEF13_MASK      (0x2000u)
#define CSL_MCBSP_XCERF_XCEF13_SHIFT     (0x000Du)
#define CSL_MCBSP_XCERF_XCEF13_RESETVAL  (0x0000u)
/*----XCEF13 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF13_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERF_XCEF13_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERF_XCEF12_MASK      (0x1000u)
#define CSL_MCBSP_XCERF_XCEF12_SHIFT     (0x000Cu)
#define CSL_MCBSP_XCERF_XCEF12_RESETVAL  (0x0000u)
/*----XCEF12 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF12_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERF_XCEF12_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERF_XCEF11_MASK      (0x0800u)
#define CSL_MCBSP_XCERF_XCEF11_SHIFT     (0x000Bu)
#define CSL_MCBSP_XCERF_XCEF11_RESETVAL  (0x0000u)
/*----XCEF11 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF11_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERF_XCEF11_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERF_XCEF10_MASK      (0x0400u)
#define CSL_MCBSP_XCERF_XCEF10_SHIFT     (0x000Au)
#define CSL_MCBSP_XCERF_XCEF10_RESETVAL  (0x0000u)
/*----XCEF10 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF10_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERF_XCEF10_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERF_XCEF9_MASK       (0x0200u)
#define CSL_MCBSP_XCERF_XCEF9_SHIFT      (0x0009u)
#define CSL_MCBSP_XCERF_XCEF9_RESETVAL   (0x0000u)
/*----XCEF9 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF9_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF9_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF8_MASK       (0x0100u)
#define CSL_MCBSP_XCERF_XCEF8_SHIFT      (0x0008u)
#define CSL_MCBSP_XCERF_XCEF8_RESETVAL   (0x0000u)
/*----XCEF8 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF8_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF8_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF7_MASK       (0x0080u)
#define CSL_MCBSP_XCERF_XCEF7_SHIFT      (0x0007u)
#define CSL_MCBSP_XCERF_XCEF7_RESETVAL   (0x0000u)
/*----XCEF7 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF7_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF7_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF6_MASK       (0x0040u)
#define CSL_MCBSP_XCERF_XCEF6_SHIFT      (0x0006u)
#define CSL_MCBSP_XCERF_XCEF6_RESETVAL   (0x0000u)
/*----XCEF6 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF6_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF6_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF5_MASK       (0x0020u)
#define CSL_MCBSP_XCERF_XCEF5_SHIFT      (0x0005u)
#define CSL_MCBSP_XCERF_XCEF5_RESETVAL   (0x0000u)
/*----XCEF5 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF5_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF5_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF4_MASK       (0x0010u)
#define CSL_MCBSP_XCERF_XCEF4_SHIFT      (0x0004u)
#define CSL_MCBSP_XCERF_XCEF4_RESETVAL   (0x0000u)
/*----XCEF4 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF4_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF4_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF3_MASK       (0x0008u)
#define CSL_MCBSP_XCERF_XCEF3_SHIFT      (0x0003u)
#define CSL_MCBSP_XCERF_XCEF3_RESETVAL   (0x0000u)
/*----XCEF3 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF3_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF3_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF2_MASK       (0x0004u)
#define CSL_MCBSP_XCERF_XCEF2_SHIFT      (0x0002u)
#define CSL_MCBSP_XCERF_XCEF2_RESETVAL   (0x0000u)
/*----XCEF2 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF2_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF2_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF1_MASK       (0x0002u)
#define CSL_MCBSP_XCERF_XCEF1_SHIFT      (0x0001u)
#define CSL_MCBSP_XCERF_XCEF1_RESETVAL   (0x0000u)
/*----XCEF1 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF1_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF1_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_XCEF0_MASK       (0x0001u)
#define CSL_MCBSP_XCERF_XCEF0_SHIFT      (0x0000u)
#define CSL_MCBSP_XCERF_XCEF0_RESETVAL   (0x0000u)
/*----XCEF0 Tokens----*/
#define CSL_MCBSP_XCERF_XCEF0_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERF_XCEF0_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERF_RESETVAL         (0x0000u)

/* RCERG */

#define CSL_MCBSP_RCERG_RCEG15_MASK      (0x8000u)
#define CSL_MCBSP_RCERG_RCEG15_SHIFT     (0x000Fu)
#define CSL_MCBSP_RCERG_RCEG15_RESETVAL  (0x0000u)
/*----RCEG15 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG15_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERG_RCEG15_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERG_RCEG14_MASK      (0x4000u)
#define CSL_MCBSP_RCERG_RCEG14_SHIFT     (0x000Eu)
#define CSL_MCBSP_RCERG_RCEG14_RESETVAL  (0x0000u)
/*----RCEG14 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG14_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERG_RCEG14_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERG_RCEG13_MASK      (0x2000u)
#define CSL_MCBSP_RCERG_RCEG13_SHIFT     (0x000Du)
#define CSL_MCBSP_RCERG_RCEG13_RESETVAL  (0x0000u)
/*----RCEG13 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG13_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERG_RCEG13_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERG_RCEG12_MASK      (0x1000u)
#define CSL_MCBSP_RCERG_RCEG12_SHIFT     (0x000Cu)
#define CSL_MCBSP_RCERG_RCEG12_RESETVAL  (0x0000u)
/*----RCEG12 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG12_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERG_RCEG12_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERG_RCEG11_MASK      (0x0800u)
#define CSL_MCBSP_RCERG_RCEG11_SHIFT     (0x000Bu)
#define CSL_MCBSP_RCERG_RCEG11_RESETVAL  (0x0000u)
/*----RCEG11 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG11_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERG_RCEG11_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERG_RCEG10_MASK      (0x0400u)
#define CSL_MCBSP_RCERG_RCEG10_SHIFT     (0x000Au)
#define CSL_MCBSP_RCERG_RCEG10_RESETVAL  (0x0000u)
/*----RCEG10 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG10_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERG_RCEG10_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERG_RCEG9_MASK       (0x0200u)
#define CSL_MCBSP_RCERG_RCEG9_SHIFT      (0x0009u)
#define CSL_MCBSP_RCERG_RCEG9_RESETVAL   (0x0000u)
/*----RCEG9 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG9_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG9_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG8_MASK       (0x0100u)
#define CSL_MCBSP_RCERG_RCEG8_SHIFT      (0x0008u)
#define CSL_MCBSP_RCERG_RCEG8_RESETVAL   (0x0000u)
/*----RCEG8 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG8_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG8_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG7_MASK       (0x0080u)
#define CSL_MCBSP_RCERG_RCEG7_SHIFT      (0x0007u)
#define CSL_MCBSP_RCERG_RCEG7_RESETVAL   (0x0000u)
/*----RCEG7 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG7_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG7_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG6_MASK       (0x0040u)
#define CSL_MCBSP_RCERG_RCEG6_SHIFT      (0x0006u)
#define CSL_MCBSP_RCERG_RCEG6_RESETVAL   (0x0000u)
/*----RCEG6 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG6_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG6_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG5_MASK       (0x0020u)
#define CSL_MCBSP_RCERG_RCEG5_SHIFT      (0x0005u)
#define CSL_MCBSP_RCERG_RCEG5_RESETVAL   (0x0000u)
/*----RCEG5 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG5_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG5_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG4_MASK       (0x0010u)
#define CSL_MCBSP_RCERG_RCEG4_SHIFT      (0x0004u)
#define CSL_MCBSP_RCERG_RCEG4_RESETVAL   (0x0000u)
/*----RCEG4 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG4_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG4_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG3_MASK       (0x0008u)
#define CSL_MCBSP_RCERG_RCEG3_SHIFT      (0x0003u)
#define CSL_MCBSP_RCERG_RCEG3_RESETVAL   (0x0000u)
/*----RCEG3 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG3_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG3_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG2_MASK       (0x0004u)
#define CSL_MCBSP_RCERG_RCEG2_SHIFT      (0x0002u)
#define CSL_MCBSP_RCERG_RCEG2_RESETVAL   (0x0000u)
/*----RCEG2 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG2_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG2_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG1_MASK       (0x0002u)
#define CSL_MCBSP_RCERG_RCEG1_SHIFT      (0x0001u)
#define CSL_MCBSP_RCERG_RCEG1_RESETVAL   (0x0000u)
/*----RCEG1 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG1_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG1_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RCEG0_MASK       (0x0001u)
#define CSL_MCBSP_RCERG_RCEG0_SHIFT      (0x0000u)
#define CSL_MCBSP_RCERG_RCEG0_RESETVAL   (0x0000u)
/*----RCEG0 Tokens----*/
#define CSL_MCBSP_RCERG_RCEG0_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERG_RCEG0_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERG_RESETVAL         (0x0000u)

/* RCERH */

#define CSL_MCBSP_RCERH_RCEH15_MASK      (0x8000u)
#define CSL_MCBSP_RCERH_RCEH15_SHIFT     (0x000Fu)
#define CSL_MCBSP_RCERH_RCEH15_RESETVAL  (0x0000u)
/*----RCEH15 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH15_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERH_RCEH15_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERH_RCEH14_MASK      (0x4000u)
#define CSL_MCBSP_RCERH_RCEH14_SHIFT     (0x000Eu)
#define CSL_MCBSP_RCERH_RCEH14_RESETVAL  (0x0000u)
/*----RCEH14 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH14_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERH_RCEH14_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERH_RCEH13_MASK      (0x2000u)
#define CSL_MCBSP_RCERH_RCEH13_SHIFT     (0x000Du)
#define CSL_MCBSP_RCERH_RCEH13_RESETVAL  (0x0000u)
/*----RCEH13 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH13_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERH_RCEH13_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERH_RCEH12_MASK      (0x1000u)
#define CSL_MCBSP_RCERH_RCEH12_SHIFT     (0x000Cu)
#define CSL_MCBSP_RCERH_RCEH12_RESETVAL  (0x0000u)
/*----RCEH12 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH12_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERH_RCEH12_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERH_RCEH11_MASK      (0x0800u)
#define CSL_MCBSP_RCERH_RCEH11_SHIFT     (0x000Bu)
#define CSL_MCBSP_RCERH_RCEH11_RESETVAL  (0x0000u)
/*----RCEH11 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH11_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERH_RCEH11_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERH_RCEH10_MASK      (0x0400u)
#define CSL_MCBSP_RCERH_RCEH10_SHIFT     (0x000Au)
#define CSL_MCBSP_RCERH_RCEH10_RESETVAL  (0x0000u)
/*----RCEH10 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH10_DISABLE   (0x0000u)
#define CSL_MCBSP_RCERH_RCEH10_ENABLE    (0x0001u)

#define CSL_MCBSP_RCERH_RCEH9_MASK       (0x0200u)
#define CSL_MCBSP_RCERH_RCEH9_SHIFT      (0x0009u)
#define CSL_MCBSP_RCERH_RCEH9_RESETVAL   (0x0000u)
/*----RCEH9 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH9_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH9_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH8_MASK       (0x0100u)
#define CSL_MCBSP_RCERH_RCEH8_SHIFT      (0x0008u)
#define CSL_MCBSP_RCERH_RCEH8_RESETVAL   (0x0000u)
/*----RCEH8 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH8_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH8_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH7_MASK       (0x0080u)
#define CSL_MCBSP_RCERH_RCEH7_SHIFT      (0x0007u)
#define CSL_MCBSP_RCERH_RCEH7_RESETVAL   (0x0000u)
/*----RCEH7 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH7_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH7_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH6_MASK       (0x0040u)
#define CSL_MCBSP_RCERH_RCEH6_SHIFT      (0x0006u)
#define CSL_MCBSP_RCERH_RCEH6_RESETVAL   (0x0000u)
/*----RCEH6 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH6_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH6_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH5_MASK       (0x0020u)
#define CSL_MCBSP_RCERH_RCEH5_SHIFT      (0x0005u)
#define CSL_MCBSP_RCERH_RCEH5_RESETVAL   (0x0000u)
/*----RCEH5 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH5_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH5_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH4_MASK       (0x0010u)
#define CSL_MCBSP_RCERH_RCEH4_SHIFT      (0x0004u)
#define CSL_MCBSP_RCERH_RCEH4_RESETVAL   (0x0000u)
/*----RCEH4 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH4_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH4_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH3_MASK       (0x0008u)
#define CSL_MCBSP_RCERH_RCEH3_SHIFT      (0x0003u)
#define CSL_MCBSP_RCERH_RCEH3_RESETVAL   (0x0000u)
/*----RCEH3 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH3_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH3_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH2_MASK       (0x0004u)
#define CSL_MCBSP_RCERH_RCEH2_SHIFT      (0x0002u)
#define CSL_MCBSP_RCERH_RCEH2_RESETVAL   (0x0000u)
/*----RCEH2 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH2_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH2_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH1_MASK       (0x0002u)
#define CSL_MCBSP_RCERH_RCEH1_SHIFT      (0x0001u)
#define CSL_MCBSP_RCERH_RCEH1_RESETVAL   (0x0000u)
/*----RCEH1 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH1_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH1_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RCEH0_MASK       (0x0001u)
#define CSL_MCBSP_RCERH_RCEH0_SHIFT      (0x0000u)
#define CSL_MCBSP_RCERH_RCEH0_RESETVAL   (0x0000u)
/*----RCEH0 Tokens----*/
#define CSL_MCBSP_RCERH_RCEH0_DISABLE    (0x0000u)
#define CSL_MCBSP_RCERH_RCEH0_ENABLE     (0x0001u)

#define CSL_MCBSP_RCERH_RESETVAL         (0x0000u)

/* XCERG */

#define CSL_MCBSP_XCERG_XCEG15_MASK      (0x8000u)
#define CSL_MCBSP_XCERG_XCEG15_SHIFT     (0x000Fu)
#define CSL_MCBSP_XCERG_XCEG15_RESETVAL  (0x0000u)
/*----XCEG15 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG15_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERG_XCEG15_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERG_XCEG14_MASK      (0x4000u)
#define CSL_MCBSP_XCERG_XCEG14_SHIFT     (0x000Eu)
#define CSL_MCBSP_XCERG_XCEG14_RESETVAL  (0x0000u)
/*----XCEG14 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG14_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERG_XCEG14_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERG_XCEG13_MASK      (0x2000u)
#define CSL_MCBSP_XCERG_XCEG13_SHIFT     (0x000Du)
#define CSL_MCBSP_XCERG_XCEG13_RESETVAL  (0x0000u)
/*----XCEG13 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG13_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERG_XCEG13_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERG_XCEG12_MASK      (0x1000u)
#define CSL_MCBSP_XCERG_XCEG12_SHIFT     (0x000Cu)
#define CSL_MCBSP_XCERG_XCEG12_RESETVAL  (0x0000u)
/*----XCEG12 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG12_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERG_XCEG12_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERG_XCEG11_MASK      (0x0800u)
#define CSL_MCBSP_XCERG_XCEG11_SHIFT     (0x000Bu)
#define CSL_MCBSP_XCERG_XCEG11_RESETVAL  (0x0000u)
/*----XCEG11 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG11_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERG_XCEG11_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERG_XCEG10_MASK      (0x0400u)
#define CSL_MCBSP_XCERG_XCEG10_SHIFT     (0x000Au)
#define CSL_MCBSP_XCERG_XCEG10_RESETVAL  (0x0000u)
/*----XCEG10 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG10_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERG_XCEG10_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERG_XCEG9_MASK       (0x0200u)
#define CSL_MCBSP_XCERG_XCEG9_SHIFT      (0x0009u)
#define CSL_MCBSP_XCERG_XCEG9_RESETVAL   (0x0000u)
/*----XCEG9 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG9_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG9_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG8_MASK       (0x0100u)
#define CSL_MCBSP_XCERG_XCEG8_SHIFT      (0x0008u)
#define CSL_MCBSP_XCERG_XCEG8_RESETVAL   (0x0000u)
/*----XCEG8 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG8_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG8_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG7_MASK       (0x0080u)
#define CSL_MCBSP_XCERG_XCEG7_SHIFT      (0x0007u)
#define CSL_MCBSP_XCERG_XCEG7_RESETVAL   (0x0000u)
/*----XCEG7 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG7_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG7_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG6_MASK       (0x0040u)
#define CSL_MCBSP_XCERG_XCEG6_SHIFT      (0x0006u)
#define CSL_MCBSP_XCERG_XCEG6_RESETVAL   (0x0000u)
/*----XCEG6 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG6_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG6_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG5_MASK       (0x0020u)
#define CSL_MCBSP_XCERG_XCEG5_SHIFT      (0x0005u)
#define CSL_MCBSP_XCERG_XCEG5_RESETVAL   (0x0000u)
/*----XCEG5 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG5_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG5_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG4_MASK       (0x0010u)
#define CSL_MCBSP_XCERG_XCEG4_SHIFT      (0x0004u)
#define CSL_MCBSP_XCERG_XCEG4_RESETVAL   (0x0000u)
/*----XCEG4 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG4_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG4_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG3_MASK       (0x0008u)
#define CSL_MCBSP_XCERG_XCEG3_SHIFT      (0x0003u)
#define CSL_MCBSP_XCERG_XCEG3_RESETVAL   (0x0000u)
/*----XCEG3 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG3_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG3_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG2_MASK       (0x0004u)
#define CSL_MCBSP_XCERG_XCEG2_SHIFT      (0x0002u)
#define CSL_MCBSP_XCERG_XCEG2_RESETVAL   (0x0000u)
/*----XCEG2 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG2_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG2_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG1_MASK       (0x0002u)
#define CSL_MCBSP_XCERG_XCEG1_SHIFT      (0x0001u)
#define CSL_MCBSP_XCERG_XCEG1_RESETVAL   (0x0000u)
/*----XCEG1 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG1_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG1_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_XCEG0_MASK       (0x0001u)
#define CSL_MCBSP_XCERG_XCEG0_SHIFT      (0x0000u)
#define CSL_MCBSP_XCERG_XCEG0_RESETVAL   (0x0000u)
/*----XCEG0 Tokens----*/
#define CSL_MCBSP_XCERG_XCEG0_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERG_XCEG0_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERG_RESETVAL         (0x0000u)

/* XCERH */

#define CSL_MCBSP_XCERH_XCEH15_MASK      (0x8000u)
#define CSL_MCBSP_XCERH_XCEH15_SHIFT     (0x000Fu)
#define CSL_MCBSP_XCERH_XCEH15_RESETVAL  (0x0000u)
/*----XCEH15 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH15_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERH_XCEH15_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERH_XCEH14_MASK      (0x4000u)
#define CSL_MCBSP_XCERH_XCEH14_SHIFT     (0x000Eu)
#define CSL_MCBSP_XCERH_XCEH14_RESETVAL  (0x0000u)
/*----XCEH14 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH14_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERH_XCEH14_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERH_XCEH13_MASK      (0x2000u)
#define CSL_MCBSP_XCERH_XCEH13_SHIFT     (0x000Du)
#define CSL_MCBSP_XCERH_XCEH13_RESETVAL  (0x0000u)
/*----XCEH13 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH13_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERH_XCEH13_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERH_XCEH12_MASK      (0x1000u)
#define CSL_MCBSP_XCERH_XCEH12_SHIFT     (0x000Cu)
#define CSL_MCBSP_XCERH_XCEH12_RESETVAL  (0x0000u)
/*----XCEH12 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH12_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERH_XCEH12_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERH_XCEH11_MASK      (0x0800u)
#define CSL_MCBSP_XCERH_XCEH11_SHIFT     (0x000Bu)
#define CSL_MCBSP_XCERH_XCEH11_RESETVAL  (0x0000u)
/*----XCEH11 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH11_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERH_XCEH11_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERH_XCEH10_MASK      (0x0400u)
#define CSL_MCBSP_XCERH_XCEH10_SHIFT     (0x000Au)
#define CSL_MCBSP_XCERH_XCEH10_RESETVAL  (0x0000u)
/*----XCEH10 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH10_DISABLE   (0x0000u)
#define CSL_MCBSP_XCERH_XCEH10_ENABLE    (0x0001u)

#define CSL_MCBSP_XCERH_XCEH9_MASK       (0x0200u)
#define CSL_MCBSP_XCERH_XCEH9_SHIFT      (0x0009u)
#define CSL_MCBSP_XCERH_XCEH9_RESETVAL   (0x0000u)
/*----XCEH9 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH9_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH9_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH8_MASK       (0x0100u)
#define CSL_MCBSP_XCERH_XCEH8_SHIFT      (0x0008u)
#define CSL_MCBSP_XCERH_XCEH8_RESETVAL   (0x0000u)
/*----XCEH8 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH8_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH8_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH7_MASK       (0x0080u)
#define CSL_MCBSP_XCERH_XCEH7_SHIFT      (0x0007u)
#define CSL_MCBSP_XCERH_XCEH7_RESETVAL   (0x0000u)
/*----XCEH7 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH7_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH7_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH6_MASK       (0x0040u)
#define CSL_MCBSP_XCERH_XCEH6_SHIFT      (0x0006u)
#define CSL_MCBSP_XCERH_XCEH6_RESETVAL   (0x0000u)
/*----XCEH6 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH6_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH6_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH5_MASK       (0x0020u)
#define CSL_MCBSP_XCERH_XCEH5_SHIFT      (0x0005u)
#define CSL_MCBSP_XCERH_XCEH5_RESETVAL   (0x0000u)
/*----XCEH5 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH5_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH5_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH4_MASK       (0x0010u)
#define CSL_MCBSP_XCERH_XCEH4_SHIFT      (0x0004u)
#define CSL_MCBSP_XCERH_XCEH4_RESETVAL   (0x0000u)
/*----XCEH4 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH4_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH4_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH3_MASK       (0x0008u)
#define CSL_MCBSP_XCERH_XCEH3_SHIFT      (0x0003u)
#define CSL_MCBSP_XCERH_XCEH3_RESETVAL   (0x0000u)
/*----XCEH3 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH3_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH3_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH2_MASK       (0x0004u)
#define CSL_MCBSP_XCERH_XCEH2_SHIFT      (0x0002u)
#define CSL_MCBSP_XCERH_XCEH2_RESETVAL   (0x0000u)
/*----XCEH2 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH2_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH2_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH1_MASK       (0x0002u)
#define CSL_MCBSP_XCERH_XCEH1_SHIFT      (0x0001u)
#define CSL_MCBSP_XCERH_XCEH1_RESETVAL   (0x0000u)
/*----XCEH1 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH1_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH1_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_XCEH0_MASK       (0x0001u)
#define CSL_MCBSP_XCERH_XCEH0_SHIFT      (0x0000u)
#define CSL_MCBSP_XCERH_XCEH0_RESETVAL   (0x0000u)
/*----XCEH0 Tokens----*/
#define CSL_MCBSP_XCERH_XCEH0_DISABLE    (0x0000u)
#define CSL_MCBSP_XCERH_XCEH0_ENABLE     (0x0001u)

#define CSL_MCBSP_XCERH_RESETVAL         (0x0000u)

#endif
