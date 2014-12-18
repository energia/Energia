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

/** @file csl_uhpiAccess.h
 *
 * @brief UHPI functional layer inline header file for HPI access from host
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
 * 02-Jul-2012 Documentation added
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */
 #ifndef _CSL_UHPI_ACCESS_H_
#define _CSL_UHPI_ACCESS_H_

/** ============================================================================
 *   @n@b HPIC_read()
 *
 *   @b Description
 *   @n This API is used to read the values from the HPIC register
 *
 *   @b Arguments
 *   @verbatim
           none
     @endverbatim
 *
 *   <b> Return Value </b> unsigned int
 *   @li value from HPIC register
 *
 *   <b> Pre Condition </b>
 *   @n  none
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

  unsigned int HPIC_read(void);

/** ============================================================================
 *   @n@b HPIA_read()
 *
 *   @b Description
 *   @n This API is used to read the values from the HPIA register
 *
 *   @b Arguments
 *   @verbatim
           none
     @endverbatim
 *
 *   <b> Return Value </b>  long unsigned int
 *   @li value from HPIA register
 *
 *   <b> Pre Condition </b>
 *   @n  none
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

  long unsigned int HPIA_read(void);

/** ============================================================================
 *   @n@b HPID_read_one()
 *
 *   @b Description
 *   @n This API is used to read the values from the HPID register once
 *
 *   @b Arguments
 *   @verbatim
           none
     @endverbatim
 *
 *   <b> Return Value </b> long unsigned int
 *   @li value from HPID register
 *
 *   <b> Pre Condition </b>
 *   @n  none
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

  long unsigned int HPID_read_one(void);

/** ============================================================================
 *   @n@b HPID_read_auto(int trans_length, long unsigned int *HPID_buffer)
 *
 *   @b Description
 *   @n This API is used to read the values from the HPID register as the values
 *   @n change with each data transfer
 *
 *   @b Arguments
 *   @verbatim
           int 					length of transfer
           long unsigned int	HPID buffer

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li none
 *
 *   <b> Pre Condition </b>
 *   @n  none
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

  void HPID_read_auto(int trans_length, long unsigned int *HPID_buffer);

/** ============================================================================
 *   @n@b HPIC_write(unsigned int HPIC_value_16b)
 *
 *   @b Description
 *   @n This API is used to write the value specified in the argument into the
 *   @n HPIC register
 *
 *   @b Arguments
 *   @verbatim
           unsigned int 		16-bit value to be transferred
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li none
 *
 *   <b> Pre Condition </b>
 *   @n  none
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

  void HPIC_write(unsigned int HPIC_value_16b);

/** ============================================================================
 *   @n@b HPIA_write(long unsigned int HPIA_value)
 *
 *   @b Description
 *   @n This API is used to wrte the value specified in the argument into the
 *   @n HPIA register
 *
 *   @b Arguments
 *   @verbatim
           long unsigned int	32-bit value to be transferred
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li none
 *
 *   <b> Pre Condition </b>
 *   @n  none
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

  void HPIA_write(long unsigned int HPIA_value_32b);

 /** ============================================================================
 *   @n@b HPID_write_one(long unsigned int HPID_data)
 *
 *   @b Description
 *   @n This API is used to write the values specified in the argument into the
 *   @n HPID register one time
 *
 *   @b Arguments
 *   @verbatim
           long unsigned int	HPID data
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li none
 *
 *   <b> Pre Condition </b>
 *   @n  none
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

  void HPID_write_one(long unsigned int HPID_data);

/** ============================================================================
 *   @n@b HPID_write_auto(int trans_length, long unsigned int *HPID_buffer)
 *
 *   @b Description
 *   @n This API is used to transfer values into the HPID register automatically
 *   @n after each transfer is done
 *
 *   @b Arguments
 *   @verbatim
           int 					length of transfer
           long unsigned int	HPID buffer

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li none
 *
 *   <b> Pre Condition </b>
 *   @n  none
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
  void HPID_write_auto(int trans_length, long unsigned int *HPID_buffer);

#endif /*_CSL_UHPI_ACCESS_H_*/
