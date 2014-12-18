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

/** @file csl_mcbsp_tgt.h
 *
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 14-Oct-2010 Created
 * 06-Jul-2011 CSL v2.50 release
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */

#include "cslr.h"
#include "csl_error.h"
#include "csl_types.h"
#include "cslr_mcbsp.h"
#include "soc.h"
#include "csl_intc.h"
#include "csl_general.h"


/****************************************\
* MCBSP Targets global macro declarations
\****************************************/

                                     // GPIO DATA in 16 bit format
                                     // gpio[9:6] is connected to Mcbsp targer
                                     // ---- --++ ++-- ----
#define MCBSP_TGT_NO_LB       0x0000 // 0000 0000 0000 0000
#define MCBSP_TGT_LB_MODE0    0x0040 // 0000 0000 0100 0000
#define MCBSP_TGT_LB_MODE1    0x00C0 // 0000 0000 1100 0000
#define MCBSP_TGT_LB_MODE2    0x0140 // 0000 0001 0100 0000
#define MCBSP_TGT_LB_MODE3    0x01C0 // 0000 0001 1100 0000
#define MCBSP_TGT_LB_MODE4    0x0240 // 0000 0010 0100 0000
#define MCBSP_TGT_LB_MODE5    0x02C0 // 0000 0010 1100 0000
#define MCBSP_TGT_LB_MODE6    0x0340 // 0000 0011 0100 0000
#define MCBSP_TGT_LB_MODE7    0x03C0 // 0000 0011 1100 0000



