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

/** @file csl_types.h
 *
 *  @brief CSL standard types definition file
 *
 *  Path: \(CSLPATH)\inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 11-Aug-2008 Created
 * 13-Aug-2010 CSL v2.10 release
 * 06-Jul-2011 CSL v2.50 release
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */

#ifndef _CSL_TYPES_H_
#define _CSL_TYPES_H_

#include <tistdtypes.h>

#ifndef TRUE

#define TRUE		((Bool) 1)
#define FALSE		((Bool) 0)

#endif

typedef Int16     CSL_Uid;
typedef Int16     CSL_ModuleId;
typedef Uint32    CSL_Xio;

typedef Uint8     CSL_BitMask8;
typedef Uint16    CSL_BitMask16;
typedef Uint32    CSL_BitMask32;

typedef volatile Uint8     CSL_Reg8;
typedef volatile Uint16    CSL_Reg16;
typedef volatile Uint32    CSL_Reg32;

typedef Int16    CSL_Status;
typedef Int16    CSL_InstNum;
typedef Int16    CSL_ChaNum;

typedef unsigned long long int     CSL_Uint64;
typedef volatile unsigned int      CSL_VUint32;
typedef volatile unsigned short    CSL_VUint16;
typedef volatile unsigned char     CSL_VUint8;

typedef Uint8      BYTE;
typedef Uint8*     PBYTE;
typedef Uint16     WORD;
typedef Uint16*    PWORD;
typedef Uint32     DWORD;
typedef Uint32*    PDWORD;
typedef void*      PVOID;
typedef void       VOID;
typedef Bool*      PBool;

typedef enum {
  CSL_EXCLUSIVE = 0,
  CSL_SHARED    = 1
} CSL_OpenMode;

typedef enum {
  CSL_FAIL      = 0,
  CSL_PASS      = 1
} CSL_Test;

#ifndef NULL
#define NULL            ((void*)0)
#endif

#endif /* _CSL_TYPES_H_ */

