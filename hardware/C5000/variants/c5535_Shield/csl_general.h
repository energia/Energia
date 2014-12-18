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

/** @file csl_general.h
 *
 *  @brief CSL general header file
 *
 *  This file contains the general CSL macros or definitions that are required
 *  to enable few functionalities specific to the chip revision. This file is
 *  included in all the cslr files. All the CSL applications should include
 *  this file.
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 07-Jan-2009 Created
 * 28-Apr-2010 Added new macro definitions
 * 30-Jun-2010 Added new macro definitions for platforms
 * 13-Aug-2010 CSL v2.10 release
 * 06-Jul-2011 CSL v2.50 release
 * 20-Jun-2012 Removed VC5504/05 chip versions and added C5517 chip version
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */

#ifndef _CSL_GENERAL_H_
#define _CSL_GENERAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 ******************************************************
 * CAUTION: DEFINE EITHER THE MACROS IN PART1 OR PART2.
 * DO NOT DEFINE MACROS IN BOTH PARTS.
 ******************************************************
 */

/** ***************************************************************************
 * --------------------------------------------------
 * PART1: CHIP VERSION MACRO DEFINITION FOR PG2.1 CSL
 * --------------------------------------------------
 *
 * Below macros are used to enable the source code specific to chip version
 * TMS320C5517C5504.
 *
 * 'CHIP_C5517' indicates TMS320C5517 DSP.
 *
 * Defining the macro below will enable the code for the DSP TMS320C5517.
 */

/* TMS320C5517 */
//#define CHIP_C5517


/******************************* END OF PART1 *******************************/


/** ***************************************************************************
 * --------------------------------------------------
 * PART2: CHIP VERSION MACRO DEFINITION FOR PG2.0 CSL
 * --------------------------------------------------
 *
 * Below macros are used to enable the source code specific to chip versions
 * TMS320C5505, TMS320C5515, TMS320C5504, and TMS320C5514.
 * Design revision(DesignRev) of the DIE ID regsiter(0x1C43 & 0x1C44) will have
 * the value '5' for this chip set.
 *
 * 'CHIP_C5505_C5515' indicates TMS320C5505 and TMS320C5515.
 * 'CHIP_C5504_C5514' indicates TMS320C5504 and TMS320C5514.
 *
 * DSPs TMS320C5505 and TMS320C5515 are similar but certain LDOs not bonded out
 * for TMS320C5505 DSP.
 * DSPs TMS320C5504 and TMS320C5514 are similar but certain LDOs not bonded out
 * for TMS320C5504 DSP.
 *
 * DSPs TMS320C55x5 and TMS320C55x4 are having the same peripherals but
 * they differ in the internal memory available. 'x' stands for 0 or 1.
 *
 * Defining any of the below macros will enable the code for all the DSPs
 * TMS320C5504, TMS320C5505, TMS320C5514 and TMS320C5515.
 * Current CSL software does not have the code that is specific to TMS320C5504
 * and TMS320C5514 DSPs.
 */

#ifndef CHIP_C5517

/* TMS320C5505 and TMS320C5515 */
#define CHIP_C5505_C5515

/**
 * Below macro was the used to indicate TMS320C5505 and TMS320C5515 in old
 * CSL version. Here it is provided for backward compatibility
 */
#define CHIP_5515

/** Mapping of the old macros to the new macros */

#ifdef CHIP_5515
#define CHIP_C5505_C5515
#endif

/** TMS320C5504 and TMS320C5514 */
#define CHIP_C5504_C5514

/**
 * Below macro was the used to indicate TMS320C5504 and TMS320C5514 in old
 * CSL version. Here it is provided for backward compatibility
 */
#define CHIP_5514

/** Mapping of the old macros to the new macros */

#ifdef CHIP_5514
#define CHIP_C5504_C5514
#endif

#endif

/******************************* END OF PART2 *******************************/


/** ***************************************************************************
 * -----------------------------------------------------------
 * PART3: EVM VERSION MACRO DEFINITION FOR PG2.0 and PG2.1 CSL
 * -----------------------------------------------------------
 *
 * Below macros are used to enable the source code specific to EVM versions
 */

#if (defined(CHIP_C5517))
/** Macro to define platform as C5517 */
#define C5517_EVM

#else

//#define C5515_EVM

#if (!(defined(C5515_EVM)))
/** Macro to define platform as C5515 eZdsp */
//#define C5515_EZDSP
#endif

#if ( !((defined(C5515_EVM)) | (defined(C5515_EZDSP))) )
/** Macro to define platform as C5535 eZdsp */
//#define C5535_EZDSP
#endif


#endif
/******************************* END OF PART3 *******************************/

#ifdef __cplusplus
}
#endif

#endif    // _CSL_GENERAL_H_

