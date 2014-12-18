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

/** @file csl_uhpiAux.h
 *
 * @brief UHPI functional layer inline header file
 *
 * @brief
 *  - The defines inline function definitions
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 30-Nov-2010 Created
 * 06-Jul-2011 CSL v2.50 release
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */
#ifndef _CSL_UHPI_AUX_H_
#define _CSL_UHPI_AUX_H_

#include "csl_uhpi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* UHPI Inline functions */

/** ============================================================================
 *   @n@b UHPI_HWOB_Getstatus
 *
 *   @b Description
 *   @n This API is used to get the HWOB bit staus
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  Bool
 *   @li                    0/1             -  HWOB bit status.
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 Uint16 UHPI_HWOB_Getstatus(CSL_UhpiHandle hUhpi)
{

    /* Extract the HWOB bit */
	return((Uint16)(CSL_FEXT(hUhpi->Regs->UHPICL,UHPI_UHPICL_HWOB)));

}


/** ============================================================================
 *   @n@b UHPI_hostTOdspInterrupt_Generate
 *
 *   @b Description
 *   @n This API is used to generate the dsp interrupt
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 void UHPI_hostTOdspInterrupt_Generate(CSL_UhpiHandle hUhpi)
{
    /* Generate the DSP interrupt */
	CSL_FINST(hUhpi->Regs->UHPICL, UHPI_UHPICL_DSP_INT, GENERATE);
}

/** ============================================================================
 *   @n@b UHPI_hostTOdspInterrupt_Clear
 *
 *   @b Description
 *   @n This API is used to clear the dsp interrupt
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 void UHPI_hostTOdspInterrupt_Clear(CSL_UhpiHandle hUhpi)
{
    /* Clear the DSP interrupt */
	CSL_FINST(hUhpi->Regs->UHPICL, UHPI_UHPICL_DSP_INT, CLEAR);
}


/** ============================================================================
 *   @n@b UHPI_hostTOdspInterrupt_Status
 *
 *   @b Description
 *   @n This API is used to get the dsp interrupt status
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 Uint16 UHPI_hostTOdspInterrupt_Status(CSL_UhpiHandle hUhpi)
{
    /* Status of the DSP interrupt */
	return((Uint16)(CSL_FEXT(hUhpi->Regs->UHPICL,UHPI_UHPICL_DSP_INT)));
}

/** ============================================================================
 *   @n@b UHPI_dspTOhostInterrupt_Generate
 *
 *   @b Description
 *   @n This API is used to generate the host interrupt
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 void UHPI_dspTOhostInterrupt_Generate(CSL_UhpiHandle hUhpi)
{
    /* Generate the Host interrupt */
	CSL_FINST(hUhpi->Regs->UHPICL, UHPI_UHPICL_HINT, GENERATE);
}

/** ============================================================================
 *   @n@b UHPI_dspTOhostInterrupt_Clear
 *
 *   @b Description
 *   @n This API is used to clear the host interrupt
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 void UHPI_dspTOhostInterrupt_Clear(CSL_UhpiHandle hUhpi)
{
    /* Clear the Host interrupt */
	CSL_FINST(hUhpi->Regs->UHPICL, UHPI_UHPICL_HINT, CLEAR);
}


/** ============================================================================
 *   @n@b UHPI_dspTOhostInterrupt_Status
 *
 *   @b Description
 *   @n This API is used to get the host interrupt status
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 Uint16 UHPI_dspTOhostInterrupt_Status(CSL_UhpiHandle hUhpi)
{
    /*Get the host interrupt status*/
	return((Uint16)(CSL_FEXT(hUhpi->Regs->UHPICL,UHPI_UHPICL_HINT)));
}


/** ============================================================================
 *   @n@b UHPI_HRDY_Status
 *
 *   @b Description
 *   @n This API is used to get the HPI ready status
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 Uint16 UHPI_HRDY_Status(CSL_UhpiHandle hUhpi)
{
    /* Get the HRDY status */
	return((Uint16)(CSL_FEXT(hUhpi->Regs->UHPICL,UHPI_UHPICL_HRDY)));
}

/** ============================================================================
 *   @n@b UHPI_FETCH_Status
 *
 *   @b Description
 *   @n This API is used to get the HPI fetch status. Always will read 0
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 Uint16 UHPI_FETCH_Status(CSL_UhpiHandle hUhpi)
{
    /* Get the Fetch bit status */
	return((Uint16)(CSL_FEXT(hUhpi->Regs->UHPICL,UHPI_UHPICL_FETCH)));
}

/** ============================================================================
 *   @n@b UHPI_XHPIA_Status
 *
 *   @b Description
 *   @n This API is used to get the extended HPI address status.
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 Uint16 UHPI_XHPIA_Status(CSL_UhpiHandle hUhpi)
{
    /* Get the XHPIA bit status */
	return((Uint16)(CSL_FEXT(hUhpi->Regs->UHPICL,UHPI_UHPICL_XHPIA)));
}

/** ============================================================================
 *   @n@b UHPI_RESET_Status
 *
 *   @b Description
 *   @n This API is used to get the RESET bit status.
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 Uint16 UHPI_RESET_Status(CSL_UhpiHandle hUhpi)
{
    /* Get the RESET bit status */
	return((Uint16)(CSL_FEXT(hUhpi->Regs->UHPICL,UHPI_UHPICL_RESET)));
}

/** ============================================================================
 *   @n@b UHPI_HPIRST_Generate
 *
 *   @b Description
 *   @n This API is used to generate the HPI reset.
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 void UHPI_HPIRST_Generate(CSL_UhpiHandle hUhpi)
{
	/* Generate the HPI reset */
	CSL_FINST(hUhpi->Regs->UHPICL, UHPI_UHPICL_HPI_RST, GENERATE);
}

/** ============================================================================
 *   @n@b UHPI_HPIRST_Clear
 *
 *   @b Description
 *   @n This API is used to clear the HPI reset.
 *
 *   @b Arguments
 *   @verbatim
            hUhpi        Handle to the UHPI
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  UHPI_open should be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n none
 *
 *   @b Modifies
 *   @n none
 *
 *   @endverbatim
 *  ============================================================================
 */
static inline
 void UHPI_HPIRST_Clear(CSL_UhpiHandle hUhpi)
{
	/* Generate the HPI reset */
	CSL_FINST(hUhpi->Regs->UHPICL, UHPI_UHPICL_HPI_RST, CLEAR);
}

#ifdef __cplusplus
 }
#endif

#endif /* _CSL_UHPI_AUX_H_ */
