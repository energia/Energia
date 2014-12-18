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
* file: cslr_ldo_1.h
*
* Brief: This file contains the Register Description for ldo
*
*********************************************************************/
#ifndef _CSLR_LDO_1_H_
#define _CSLR_LDO_1_H_

#include <cslr.h>

#include <tistdtypes.h>


/* Minimum unit = 2 bytes */

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint16 RSVD0[4];
    volatile Uint16 LDOCTRL;
} CSL_LdoRegs;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* LDOCTRL */


#define CSL_LDO_LDOCTRL_DSPLDOCNTL_MASK  (0x0002u)
#define CSL_LDO_LDOCTRL_DSPLDOCNTL_SHIFT (0x0001u)
#define CSL_LDO_LDOCTRL_DSPLDOCNTL_RESETVAL (0x0000u)
/*----DSPLDOCNTL Tokens----*/
#define CSL_LDO_LDOCTRL_DSPLDOCNTL_1PT3V  (0x0000u)
#define CSL_LDO_LDOCTRL_DSPLDOCNTL_1PT05V (0x0001u)

#define CSL_LDO_LDOCTRL_USBLDOEN_MASK    (0x0001u)
#define CSL_LDO_LDOCTRL_USBLDOEN_SHIFT   (0x0000u)
#define CSL_LDO_LDOCTRL_USBLDOEN_RESETVAL (0x0000u)
/*----USBLDOEN Tokens----*/
#define CSL_LDO_LDOCTRL_USBLDOEN_DISABLED (0x0000u)
#define CSL_LDO_LDOCTRL_USBLDOEN_ENABLED (0x0001u)

#define CSL_LDO_LDOCTRL_RESETVAL         (0x0000u)

#endif
