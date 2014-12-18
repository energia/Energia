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

/** @file csl_mcspi.h
 *
 *  @brief mcspi functional layer API header file
 *
 *  Path: \\(CSLPATH)\\inc
 *
 */

/* ============================================================================
 * Revision History
 * ================
 * 06-Dec-2010 Added MCSPI for CSL
 * 06-Jul-2011 CSL v2.50 release
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */

/** @defgroup CSL_McSPI_API McSPI
 *
 * @section Introduction
 *
 * @subsection xxx Overview
 * The Multichannel Serial Port Interface is a master/slave synchronous serial bus.
 * It supports up to three peripherals
 *
 */

#ifndef _CSL_MCSPI_H_
#define _CSL_MCSPI_H_

/**
@defgroup CSL_McSPI_SYMBOL  McSPI Symbols Defined
@ingroup CSL_McSPI_API
*/
/**
@defgroup CSL_McSPI_DATASTRUCT  McSPI Data Structures
@ingroup CSL_McSPI_API
*/
/**
@defgroup CSL_McSPI_FUNCTION  McSPI Functions
@ingroup CSL_McSPI_API
*/

/**
@defgroup CSL_McSPI_ENUM McSPI Enumerated Data Types
@ingroup CSL_McSPI_API
*/

/**
@addtogroup CSL_McSPI_SYMBOL
@{ */

/**  IP supports channel 3 but PHOENIX CH3 not enabled */
#define CH3_ENABLE 0

/** Return Status to indicate Success */
#define SUCCESS 1
/** Return Status to indicate Failure */
#define FAILURE 0


#ifdef __cplusplus
extern "C" {
#endif

#include "cslr.h"
#include "soc.h"
#include "cslr_mcspi.h"
#include "csl_error.h"
#include "csl_types.h"
#include "csl_general.h"


/*****************************************************************************\
          MCSPI global macro declarations
\*****************************************************************************/


#define	McSPI_READ_CMD		(Uint16) 1  /**< Read Command for McSPI  */
#define	McSPI_WRITE_CMD		(Uint16) 2  /**< Write Command for McSPI */
#define	McSPI_DISABLE			(0)     /**< Value to indicate McSPI is
                                             Disabled */
#define	McSPI_ENABLE			(1)     /**< Value to indicate McSPI is
                                             Enabled */
#define	McSPI_ACTIVE			(0)     /**< Value to indicate McSPI is
                                             Active */


#define CSL_McSPI_CSNUM_CS0   (0x0000u) /**< McSPI Chip Select 0 */
#define CSL_McSPI_CSNUM_CS1   (0x0001u) /**< McSPI Chip Select 1 */
#define CSL_McSPI_CSNUM_CS2   (0x0002u) /**< McSPI Chip Select 2 */

#if	(CH3_ENABLE == 1)
	#define CSL_McSPI_CSNUM_CS3   (0x0003u)  /**< McSPI Chip Select 3 */
#endif

/**
@} */



/**

@addtogroup CSL_McSPI_ENUM

@{*/

/**
 * \brief McSPI instance numbers
 *
 */
typedef enum
{
   McSPI_CS_NUM_0,
   McSPI_CS_NUM_1,
   McSPI_CS_NUM_2,
#if	(CH3_ENABLE == 1)
   McSPI_CS_NUM_3,
#endif
   McSPI_CS_NUM_INVALID
}McSPI_ch;


typedef enum
{
   McSPI_MASTER,
   McSPI_SLAVE
}McSPI_mode;


typedef enum
{
   McSPI_FULL_DUPLEX,
   McSPI_HALF_DUPLEX_RX,
   McSPI_HALF_DUPLEX_TX
}McSPI_duplex;

typedef enum
{
   McSPI_POLLING_MODE,
   McSPI_INTERRUPT_MODE,
   McSPI_DMA_MODE
}McSPI_OperMode;

typedef enum
{
    McSPI_WORD_LENGTH_4=3,
    McSPI_WORD_LENGTH_5,
    McSPI_WORD_LENGTH_6,
    McSPI_WORD_LENGTH_7,
    McSPI_WORD_LENGTH_8,
    McSPI_WORD_LENGTH_9,
    McSPI_WORD_LENGTH_10,
    McSPI_WORD_LENGTH_11,
    McSPI_WORD_LENGTH_12,
    McSPI_WORD_LENGTH_13,
    McSPI_WORD_LENGTH_14,
    McSPI_WORD_LENGTH_15,
    McSPI_WORD_LENGTH_16,
    McSPI_WORD_LENGTH_17,
    McSPI_WORD_LENGTH_18,
    McSPI_WORD_LENGTH_19,
    McSPI_WORD_LENGTH_20,
    McSPI_WORD_LENGTH_21,
    McSPI_WORD_LENGTH_22,
    McSPI_WORD_LENGTH_23,
    McSPI_WORD_LENGTH_24,
    McSPI_WORD_LENGTH_25,
    McSPI_WORD_LENGTH_26,
    McSPI_WORD_LENGTH_27,
    McSPI_WORD_LENGTH_28,
    McSPI_WORD_LENGTH_29,
    McSPI_WORD_LENGTH_30,
    McSPI_WORD_LENGTH_31,
    McSPI_WORD_LENGTH_32,
    McSPI_MAX_WORD_LEN
}McSPI_WordLen;


typedef enum
{
    McSPI_DATA_NODLY = 0,
    McSPI_DATA_DLY1,
    McSPI_DATA_DLY2,
    McSPI_DATA_DLY3,
    McSPI_DATA_DLY4
}McSPI_DataDly;


typedef enum
{
    McSPI_CLKP_HIGH = 0,
    McSPI_CLKP_LOW
}McSPI_ClkPolarity;


typedef enum
{
    McSPI_CSP_ACTIVE_HIGH = 0,
    McSPI_CSP_ACTIVE_LOW
}McSPI_ChipSelPol;


typedef enum
{
    McSPI_CLK_PH_ODD_EDGE = 0,
    McSPI_CLK_PH_EVEN_EDGE
}McSPI_ClkPh;

typedef enum
{
    McSPI_RX_SPIDAT0 = 0,
    McSPI_RX_SPIDAT1
}McSPI_InputSel;

typedef enum
{
    McSPI_TX_ENABLE_SPIDAT0 = 0,
    McSPI_TX_ENABLE_SPIDAT1
}McSPI_TxEn_Dat0_1;

typedef enum
{
    McSPI_FIFO_DIS = 0,
    McSPI_FIFO_EN
}McSPI_Fifo;

/**
@} */


/**
\addtogroup CSL_McSPI_DATASTRUCT
@{ */

/** \brief  McSPI Config
*/
typedef struct
{
    Uint16		ClkDiv;
    McSPI_WordLen	wLen;
    McSPI_mode          mode;
    McSPI_duplex        duplex;
    McSPI_DataDly	dataDelay;
    McSPI_ClkPolarity	clkPol;
    McSPI_ChipSelPol	csPol;
    McSPI_ClkPh		clkPh;
    McSPI_InputSel	inSel;
    McSPI_TxEn_Dat0_1   enDat0_1;
	McSPI_Fifo 	fifo;
}McSPI_Config;

/** \brief  McSPI Object
*/
typedef struct
{
    Uint16	    configured;
	Uint16      open;
    McSPI_ch        ch;
    McSPI_OperMode  opMode;
   	CSL_McspiRegsOvly Regs;
    CSL_SysRegsOvly sysRegs;
    McSPI_Config McSPIHwConfig;
}CSL_McSpiObj;

typedef CSL_McSpiObj *CSL_McSpiHandle;
/**
@} */


/** @addtogroup CSL_McSPI_FUNCTION
 @{ */

/*****************************************************************************\
          MCSPI Funtion prototypes
\*****************************************************************************/


Uint16 McSPI_init(unsigned int clock_divider);

CSL_McSpiHandle  McSPI_open(McSPI_OperMode opMode,CSL_McSpiObj *McSpiObj,CSL_Status 	*status);


CSL_Status  McSPI_close(CSL_McSpiHandle hMcSPI);

CSL_Status  McSPI_config (CSL_McSpiHandle hMcSPI);

CSL_Status  McSPI_write (CSL_McSpiHandle hMcSPI, Uint16	*writeBuffer, Uint16 bufLen);


CSL_Status  McSPI_read (CSL_McSpiHandle hMcSPI, Uint16	*readBuffer, Uint16 bufLen);


Uint16  McSPI_RxFullInt_Chk (CSL_McSpiHandle hMcSPI);

Uint16  McSPI_TxEmptyInt_Chk (CSL_McSpiHandle hMcSPI);


#ifdef __cplusplus
}
#endif

/**
@} */
#endif /* _CSL_MCSPI_H_ */

