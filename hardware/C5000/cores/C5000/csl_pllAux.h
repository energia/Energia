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

/** @file csl_pllAux.h
 *
 * @brief PLL functional layer inline header file
 *       -Extra Inline functions
 *
 *  Path: \(CSLPATH)/inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 21-Aug-2008 Created
 * 13-Aug-2010 CSL v2.10 release
 * 06-Jul-2011 CSL v2.50 release
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */


#ifndef _CSL_PLLAUX_H_
#define _CSL_PLLAUX_H_

#include <csl_pll.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CSL_PLL_FUNCTION
@{*/

/** ============================================================================
 *   @n@b PLL_getTestLockMonStatus
 *
 *   @b Description
 *   @n This API is used to get the status of TEST LOCK bit in PLL CNTL2 reg
 *
 *   @b Arguments
 *   @verbatim
        hPll        Handle to the pll
     @endverbatim
 *
 *   <b> Return Value </b>  Bool
 *   @li                    TRUE             -  Test lock bit is set
 *
 *   @li                    FALSE            -  Test lock bit is not set.
 *
 *   <b> Pre Condition </b>
 *   @n  PLL_init and PLL_config should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n hPll variable
 *
 *   @b Example
 *   @verbatim
         CSL_Status              status;
         Bool                    bStatus;
         PLL_Obj                 pllObj;
         PLL_Config              configInfo;
         PLL_Handle              hPll;
         Uint32                  pllInstId;
         pllInstId = 0;
         status = PLL_init(&pllObj,pllInstId);
         hPll = &pllObj;
	     .......
         Configure the PLL for 12.288MHz
         configInfo.PLLCNTL1  = 0x82ed; //Give proper value
         configInfo.PLLCNTL2  = 0x8000;
         configInfo.PLLINCNTL = 0x0806;
         configInfo.PLLOUTCNTL = 0x0200;
         status = PLL_config(hPll, &configInfo);
         bStatus = PLL_getTestLockMonStatus(hPll);
     @endverbatim
 *  ============================================================================
 */
static inline
Bool PLL_getTestLockMonStatus(PLL_Handle hPll)
{
    Uint16 TstLckMon = 0;
#if (!(defined(CHIP_C5517)))
    TstLckMon = ((hPll->sysAddr->CGCR3 & (0x0008u)) >> (0x0003u));
#endif
    if( TstLckMon )
        return TRUE;
    return FALSE;
}

/** ============================================================================
 *   @n@b PLL_getConfig
 *
 *   @b Description
 *   @n This API is used to retrieve the current configuration of the pll.
 *
 *   @b Arguments
 *   @verbatim
        hPll        Handle to the pll
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            -  PLL config information is available
 *
 *   @li                    CSL_ESYS_BADHANDLE -  Handle is invalid
 *
 *   @li                    CSL_ESYS_INVPARAMS -  Pointer to the config structure is NULL
 *
 *   <b> Pre Condition </b>
 *   @n  PLL_init and PLL_config should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n pConfig variable
 *
 *   @b Example
 *   @verbatim
         CSL_Status              status;
         Bool                    bStatus;
         PLL_Obj                 pllObj;
         PLL_Config              configInfo;
         PLL_Config              gconfig;
         PLL_Handle              hPll;
         Uint32                  pllInstId;
         pllInstId = 0;
         status = PLL_init(&pllObj,pllInstId);
         hPll = &pllObj;
	     .......
         Configure the PLL for 12.288MHz
         configInfo.PLLCNTL1 = 0x82ed;
         configInfo.PLLINCNTL = 0x8000;
         configInfo.PLLCNTL2 = 0x0806;
         configInfo.PLLOUTCNTL = 0x0200;
         status = PLL_config(hPll, &configInfo);
         status = PLL_getConfig(hPll,&gconfig);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status PLL_getConfig(PLL_Handle hPll,PLL_Config *pConfig)
{
   	CSL_Status status = CSL_SOK;

    if(NULL == hPll)
    {
		status = CSL_ESYS_BADHANDLE;
		return status;
	}

	if(NULL == pConfig)
    {
		status = CSL_ESYS_INVPARAMS;
		return status;
	}
#if (!(defined(CHIP_C5517)))
    pConfig->PLLCNTL1   = hPll->sysAddr->CGCR1;
    pConfig->PLLCNTL2   = hPll->sysAddr->CGCR3;
    pConfig->PLLINCNTL  = hPll->sysAddr->CGCR2;
    pConfig->PLLOUTCNTL = hPll->sysAddr->CGCR4;
#else
    pConfig->PLLMR  = hPll->sysAddr->PMR;
    pConfig->PLLICR = hPll->sysAddr->PICR;
    pConfig->PLLCR  = hPll->sysAddr->PCR;
    pConfig->PLLODR = hPll->sysAddr->PODCR;
#endif
    return status;
}

#ifdef __cplusplus
}
#endif

/**
@} */
#endif// _CSL_PLLAUX_H_
