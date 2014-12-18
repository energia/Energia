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

/** @file csl_emif.h
 *
 *  @brief EMIF functional layer API header file
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 08-Feb-2013 Created
 * ============================================================================
 */

/** @defgroup CSL_EMIF_API EMIF
 *
 * @section Introduction
 *
 * @subsection xxx Overview
 *
 *  @subsection References
 *
 */

#ifndef _CSL_EMIF_H_
#define _CSL_EMIF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <cslr.h>
#include <csl_error.h>
#include <csl_types.h>
#include <cslr_emif.h>
#include <soc.h>
#include <csl_general.h>


/**
@defgroup CSL_EMIF_SYMBOL  EMIF Symbols Defined
@ingroup CSL_EMIF_API
*/
/**
@defgroup CSL_EMIF_DATASTRUCT  EMIF Data Structures
@ingroup CSL_EMIF_API
*/
/**
@defgroup CSL_EMIF_FUNCTION  EMIF Functions
@ingroup CSL_EMIF_API
*/
/**
@defgroup CSL_EMIF_ENUM EMIF Enumerated Data Types
@ingroup CSL_EMIF_API
*/

/**
@addtogroup CSL_EMIF_SYMBOL
@{
*/
/*****************************************************************************\
          EMIF global macro declarations                                      *
\*****************************************************************************/

/** EMIF general delay                                                       */
#define CSL_EMIF_DELAY                              (100)
/** EMIF reset counter register value                                        */
#define CSL_EMIF_RESET_COUNT_VAL                    (0x20)
/** EMIF clock division value for half rate of CPU clock                     */
#define CSL_EMIF_ECDR_EDIV_HALFRATE                 (0x0)

/**
 * \brief EMIF CSL Bit position macros
 */
/** LSB bit position for CS2 ECC1 register                                   */
#define CSL_EMIF_NCS2ECC1_LSB                       (0)
/** MSB bit position for CS2 ECC1 register                                   */
#define CSL_EMIF_NCS2ECC1_MSB                       (11)
/** LSB bit position for CS2 ECC2 register                                   */
#define CSL_EMIF_NCS2ECC2_LSB                       (0)
/** MSB bit position for CS2 ECC2 register                                   */
#define CSL_EMIF_NCS2ECC2_MSB                       (11)
/** LSB bit position for CS3 ECC1 register                                   */
#define CSL_EMIF_NCS3ECC1_LSB                       (0)
/** MSB bit position for CS3 ECC1 register                                   */
#define CSL_EMIF_NCS3ECC1_MSB                       (11)
/** LSB bit position for CS3 ECC2 register                                   */
#define CSL_EMIF_NCS3ECC2_LSB                       (0)
/** MSB bit position for CS3 ECC2 register                                   */
#define CSL_EMIF_NCS3ECC2_MSB                       (11)
/** LSB bit position for CS4 ECC1 register                                   */
#define CSL_EMIF_NCS4ECC1_LSB                       (0)
/** MSB bit position for CS4 ECC1 register                                   */
#define CSL_EMIF_NCS4ECC1_MSB                       (11)
/** LSB bit position for CS4 ECC2 register                                   */
#define CSL_EMIF_NCS4ECC2_LSB                       (0)
/** MSB bit position for CS4 ECC2 register                                   */
#define CSL_EMIF_NCS4ECC2_MSB                       (11)
/** LSB bit position for CS5 ECC1 register                                   */
#define CSL_EMIF_NCS5ECC1_LSB                       (0)
/** MSB bit position for CS5 ECC1 register                                   */
#define CSL_EMIF_NCS5ECC1_MSB                       (11)
/** LSB bit position for CS5 ECC2 register                                   */
#define CSL_EMIF_NCS5ECC2_LSB                       (0)
/** MSB bit position for CS5 ECC2 register                                   */
#define CSL_EMIF_NCS5ECC2_MSB                       (11)
/** Clock value of 100 MHZ in units of KHz                                   */
#define CSL_CLOCK_100MHz                            (100000)

/**
 * \brief SDRAM device timing values for SDRAM (MT48H4M16LF)
 */
/** tRFC = 80 ns (min)                                                      */
#define CSL_SDRAM_TRFC_VAL							(7)
/** tRP = 19 ns (min)								                        */
#define CSL_SDRAM_TRP_VAL							(1)
/** tRCD = 19 ns (min)                                                      */
#define CSL_SDRAM_TRCD_VAL							(1)
/** tRDL = 2 clocks = 20ns (min)                                            */
#define CSL_SDRAM_TWR_VAL							(1)
/** tRAS = 48 ns (min)                                                      */
#define CSL_SDRAM_TRAS_VAL							(4)
/** tRFC = 80 ns (min)                                                      */
#define CSL_SDRAM_TRC_VAL							(7)
/** tRRD = 16 ns (min)                                                      */
#define CSL_SDRAM_TRRD_VAL							(1)
/** tXSR = 80 ns (min)                                                      */
#define CSL_SDRAM_TXS_VAL							(7)
/** tRefresh_Period = 64 ms, ncycles = 4096                                 */
#define CSL_SDRAM_REFRATE_VAL						(0x61Au)

/**
 * \brief Default values of SDRAM Config structure
 */
/** To avoid placing the EMIF in Self-Refresh Mode                          */
#define CSL_SDRAM_SDCR2_SR_DEFAULT					(0)
/** To avoid placing the EMIF in Power Down Mode                            */
#define CSL_SDRAM_SDCR2_PD_DEFAULT					(0)
/** To disable refreshes during power down                                  */
#define CSL_SDRAM_SDCR2_PDWR_DEFAULT				(0)
/** To select 4 banks for refresh during SLFR command                       */
#define CSL_SDRAM_SDCR2_PASR_DEFAULT				(0)
/** To configure the EMIF to access the page in all banks                   */
#define CSL_SDRAM_SDCR2_IBANK_POS_DEFAULT			(0)
/** To select full drive strength when initializing the memory device       */
#define CSL_SDRAM_SDCR2_SDRAM_DRIVE_DEFAULT			(0)
/** To allow writes to PASR, ROWSIZE, IBANK_POS, and SDRAM_DRIVE            */
#define CSL_SDRAM_SDCR2_BIT_9_1_LOCK_DEFAULT		(1)
/** This bit should always be set to 1                                      */
#define CSL_SDRAM_SDCR1_NM_DEFAULT					(1)
/** To select a CAS latency of 3                                            */
#define CSL_SDRAM_SDCR1_CL_DEFAULT					(3)
/** To allow the CL field to be written                                     */
#define CSL_SDRAM_SDCR1_BIT_11_9_LOCK_DEFAULT		(1)
/** To select 4 internal SDRAM banks                                        */
#define CSL_SDRAM_SDCR1_IBANK_DEFAULT				(2)
/** To use a single chip select when communicating with the memory device   */
#define CSL_SDRAM_SDCR1_EBANK_DEFAULT				(0)
/** To select a page size of 256 words                                      */
#define CSL_SDRAM_SDCR1_PAGESIZE_DEFAULT			(0)
/** To enable powerdown mode                                                */
#define CSL_SDRAM_PD_PWRDN_EN              			(1u)
/** To disable powerdown mode                                               */
#define CSL_SDRAM_PDWR_EN               			(1u)
/** To enable self refresh mode                                             */ 
#define CSL_SDRAM_SR_EN                 			(1u)

/** Starting CPU address of SDRAM                                           */
#define CSL_SDRAM_START_ADDR						(0x28000)
/** Ending  CPU address of SDRAM                                            */
#define CSL_SDRAM_END_ADDR						    (0x400000)

/**
 * \brief NOR flash command address offsets and data values 
 */
/** Starting CPU address of NOR flash connected to CS2                      */
#define CSL_EMIF_NOR_BASE_ADDR                       (0x400000)
/** Starting CPU address of NOR flash connected to CS2                      */
#define CSL_NOR_START_ADDR                           (0x400000)
/** Ending CPU address of NOR flash connected to CS2                        */
#define CSL_NOR_END_ADDR                             (0x600000)
/** NOR flash memory Unlock command address 1                               */
#define CSL_NOR_UNLOCK_ADDR1                         (0x555)
/** NOR flash memory Unlock command 1                                       */
#define CSL_NOR_UNLOCK_CMD1                          (0x00AA)
/** NOR flash memory Unlock command address 2                               */
#define CSL_NOR_UNLOCK_ADDR2                         (0x2AA)
/** NOR flash memory Unlock command 2                                       */
#define CSL_NOR_UNLOCK_CMD2                          (0x0055)
/** NOR flash memory write program Setup command                            */
#define CSL_NOR_WRITE_PGM_SETUP_CMD                  (0x00A0)
/** NOR flash memory reset command                                          */
#define CSL_NOR_RESET_CMD                            (0x00F0)
/** NOR flash memory sector erase command                                   */
#define CSL_NOR_SECTOR_ERASE_CMD                     (0x0030)
/** NOR flash memory write  Setup command                                   */
#define CSL_NOR_WRITE_SETUP_CMD                      (0x0080)
/** NOR flash memory reset value                                            */
#define CSL_NOR_RESET_DATA                           (0x0080)
/** NOR flash timeout count for write operation                             */
#define CSL_NOR_WRITE_TIMEOUT                        (0x10000u)
/** NOR flash timeout count for erase operation                             */
#define CSL_NOR_ERASE_TIMEOUT                        (0x08000000u)
/** NOR flash command to read status                                        */
#define CSL_NOR_READ_STATUS_CMD                      (0x0070)
/** NOR flash read array command                                            */
#define CSL_NOR_READ_ARRAY_CMD                       (0x00FFu)
/** NOR flash block erase command                                           */
#define CSL_NOR_BLOCK_ERASE_CMD                      (0x0020u)
/** NOR flash command to resume from erase mode                             */
#define CSL_NOR_ERASE_PROGRAM_RESUME_CMD             (0x00D0u)
/** NOR flash mask1 to check status of operation completion                 */
#define CSL_NOR_OP_COMPLETION_STATUS1                (0x0080)
/** NOR flash mask2 to check status of operation completion                 */
#define CSL_NOR_OP_COMPLETION_STATUS2                (0x8000)
/** NOR flash configuration command for block locking                       */
#define CSL_NOR_CONFIG_BLOCK_LOCK_BITS_CMD           (0x0060)
/** NOR flash command to lock the configured bits                           */
#define CSL_NOR_SET_LOCK_BITS_CMD                    (0x0001)
/** NOR flash command to unlock the configured bits                         */
#define CSL_NOR_CLEAR_LOCK_BITS_CMD                  (0x00D0)
/** NOR flash word program command                                          */
#define CSL_NOR_WORD_PROGRAM_CMD                     (0x0040)
/** NOR flash mask1 for error checking                                      */
#define CSL_NOR_OP_ERROR_CHECK_MASK1                 (0x007F)
/** NOR flash mask2 for error checking                                      */
#define CSL_NOR_OP_ERROR_CHECK_MASK2                 (0x7F00)

/**
 * \brief NAND device standard commands
 */
/** Command to access low page                                               */
#define CSL_NAND_SB_CMD_LO_PAGE                      (0x00u)
/** Command to access high page                                              */
#define CSL_NAND_SB_CMD_HI_PAGE                      (0x01u)
/** Command to access spare area - not found in Big Block NANDs              */
#define CSL_NAND_SB_CMD_SPARE_AREA                   (0x50u)
/** Command to access device Id                                              */
#define CSL_NAND_CMD_DEVID                           (0x90u)
/** Command to access device address                                         */
#define CSL_NAND_CMD_DEVADD                          (0x00u)
/** Command to perform a reset                                               */
#define CSL_NAND_CMD_RESET                           (0xFFu)
/** Command to perform a set                                                 */
#define CSL_NAND_CMD_SET                             (0x00u)
/** Command to start programming NAND                                        */
#define CSL_NAND_CMD_PGRM_START                      (0x80u)
/** Command to stop programming NAND                                         */
#define CSL_NAND_CMD_PGRM_END                        (0x10u)
/** Command to erase block                                                   */
#define CSL_NAND_CMD_BLK_ERASE_CMD1                  (0x60u)
/** Command to erase block                                                   */
#define CSL_NAND_CMD_BLK_ERASE_CMD2                  (0xD0u)
/** Command to put NAND in ready state                                       */
#define CSL_NAND_CMD_READY                           (0x40u)
/** Command to get the status of NAND                                        */
#define CSL_NAND_CMD_STATUS                          (0x70u)
/** Command to read the start of NAND                                        */
#define CSL_NAND_CMD_READ_START                      (0x00u)
/** Command to read the end of NAND                                          */
#define CSL_NAND_CMD_READ_END                        (0x30u)

/**
 * \brief Big block NAND extra commands
 */
/** Command to perform a random data input <b>(Big block only command)</b>   */
#define CSL_NAND_BB_CMD_RANDOM_PGRM_START            (0x85u)
/** Command to start a random data output  <b>(Big block only command)</b>   */
#define CSL_NAND_BB_CMD_RANDOM_READ_START            (0x05u)
/** Command to end a random data output    <b>(Big block only command)</b>   */
#define CSL_NAND_BB_CMD_RANDOM_READ_END              (0xE0u)
/** Command to perform a Copy-back read    <b>(Big block only command)</b>   */
#define CSL_NAND_BB_CMD_COPY_BACK_READ               (0x35u)


/** First bit-position for NAND device flags                                 */
#define CSL_NAND_FLAG_FIRSTBITPOS                    (0u)
/** Write protected bit-flag                                                 */
#define CSL_NAND_MEDIA_WRITE_PROTECTED ((1L) << (CSL_NAND_FLAG_FIRSTBITPOS + 0))
/** Last bit-position for NAND device flags                                  */
#define CSL_NAND_FLAG_LASTBITPOS                     (1u)

/**
 * \brief NAND Status Bit definitions - Big Block
 *
 */
/** Program/erase operation passed                                           */
#define CSL_NAND_BB_CMD_PGRM_STATUS_PASS             (0x0000)
/** NAND Ready for command after a cache operation                           */
#define CSL_NAND_BB_CMD_CACHE_PGRM_READY             (0x0020u)
/** NAND Ready for commands after an operation                               */
#define CSL_NAND_BB_CMD_CMD_STATUS_READY             (0x0040u)
/** NAND device not write protected status                                   */
#define CSL_NAND_BB_CMD_WP_STATUS_OPEN               (0x0080u)
/** Status check for any Big block NAND operation                            */
#define CSL_NAND_BB_CMD_STATUS_READY    (CSL_NAND_BB_CMD_CMD_STATUS_READY | \
                                         CSL_NAND_BB_CMD_PGRM_STATUS_PASS)
/** BIg block nand command status success                                    */
#define CSL_NAND_BB_CMD_STATUS_SUCCESS               (CSL_NAND_BB_CMD_STATUS_READY)

/**
 * \brief NAND Status Bit definitions - Small Block
 *
 */
/** Program/erase operation passed                                           */
#define CSL_NAND_SB_CMD_PGRM_STATUS_PASS             (0x0000)
/** NAND Ready for commands after an operation                               */
#define CSL_NAND_SB_CMD_CMD_STATUS_READY             (0x0040u)
/** Not write protected                                                      */
#define CSL_NAND_SB_CMD_WP_STATUS_OPEN               (0x0080u)
/** Status check for any Small block NAND operation                          */
#define CSL_NAND_SB_CMD_STATUS_READY    (CSL_NAND_SB_CMD_CMD_STATUS_READY | \
                                         CSL_NAND_SB_CMD_PGRM_STATUS_PASS)
/** Small block nand command status success                                  */
#define CSL_NAND_SB_CMD_STATUS_SUCCESS               (CSL_NAND_SB_CMD_STATUS_READY)

/**
 * \brief Extended ID masks
 *
 */
/** Page size mask of extended ID                                            */
#define CSL_NAND_PAGE_SIZE_MASK                      (0x03u)
/** Block size mask of extended ID                                           */
#define CSL_NAND_BLOCK_SIZE_MASK                     (0x30u)
/** Redundant area size mask of extended ID                                  */
#define CSL_NAND_RED_AREA_SIZE_MASK                  (0x04u)
/** Organization (8/16 bit) mask of extended ID                              */
#define CSL_NAND_ORGANIZATION_MASK                   (0x40u)

/**
 * \brief ECC options for NAND Banks
 *
 */
/** Enable ECC calculation for bank 1 - maps to CS2ECC                       */
#define CSL_NAND_ECC_BANK1_ENABLE                    (0x100u)
/** Enable ECC calculation for bank 2 - maps to CS3ECC                       */
#define CSL_NAND_ECC_BANK2_ENABLE                    (0x200u)
/** Enable ECC calculation for bank 3 - maps to CS4ECC                       */
#define CSL_NAND_ECC_BANK3_ENABLE                    (0x400u)
/** Enable ECC calculation for bank 4 - maps to CS5ECC                       */
#define CSL_NAND_ECC_BANK4_ENABLE                    (0x800u)

/**
 * \brief Big block NAND extra features
 */
/** Big-Block NAND has cache programming command/feature                     */
#define CSL_NAND_BB_CACHE_PROG                      (0x01u)
/** Big-Block NAND has copy-back command/feature                             */
#define CSL_NAND_BB_COPY_BACK                       (0x02u)
/** Big-Block NAND has random read/random output command/feature             */
#define CSL_NAND_BB_RANDOM_PAGE_READ                (0x04u)
/** Big-Block NAND has random write/random input command/feature             */
#define CSL_NAND_BB_RANDOM_PAGE_WRITE               (0x08u)
/** Extra commands/options/features only for Big Block NAND devices          */
#define CSL_NAND_BB_OPTIONS                   (CSL_NAND_BB_CACHE_PROG       |\
                                               CSL_NAND_BB_COPY_BACK        |\
                                               CSL_NAND_BB_RANDOM_PAGE_READ |\
                                               CSL_NAND_BB_RANDOM_PAGE_WRITE )
/** NAND options for Bigblock MLC NAND flash                                 */
#define CSL_NAND_BB_MLC_NAND			        0x10

/** Maximum time-out for NAND                                                */
#define CSL_NAND_MAX_TIMEOUT                        (0x7FFFFFFFu)
/** NAND read status time out                                                */
#define CSL_NAND_READ_STATUS_TIMEOUT                (100000u)
/** Big block NAND page size                                                 */
#define CSL_NAND_BB_PAGE_SIZE                       (2048u)
/** NAND invalid interrupt number                                            */
#define CSL_NAND_INV_INTR_NUM                       (0xFFFF)

/** \brief Default values of EMIF Async Wait Config structure                */
/** Default value for wait polarity                                          */
#define CSL_EMIF_ASYNCWAITCFG_WAITPOL_DEFAULT       (0x00)
/** Default value for Nand port                                              */
#define CSL_EMIF_ASYNCWAITCFG_NANDPORT_DEFAULT      (0x00)
/** Default value maximum exteneded wait cycles                              */
#define CSL_EMIF_ASYNCWAITCFG_WAITCYCLE_DEFAULT     (0x80)

/** \brief Default values of NAND Async Config structure                     */
/** Default value for strobe mode select bit                                 */
#define CSL_EMIF_ASYNCCFG_SELECTSTROBE_DEFAULT      (0x00)
/** Default value for extended wait mode bit                                 */
#define CSL_EMIF_ASYNCCFG_WEMODE_DEFAULT            (0x00)
/** Default value for write setup cycles                                     */
#define CSL_EMIF_ASYNCCFG_WSETUP_DEFAULT            (0x0F)
/** Default value for write strobe cycles                                    */
#define CSL_EMIF_ASYNCCFG_WSTROBE_DEFAULT           (0x1F)
/** Default value for write hold cycles                                      */
#define CSL_EMIF_ASYNCCFG_WHOLD_DEFAULT             (0x07)
/** Default value for read setup cycles                                      */
#define CSL_EMIF_ASYNCCFG_RSETUP_DEFAULT            (0x0F)
/** Default value for read strobe cycles                                     */
#define CSL_EMIF_ASYNCCFG_RSTROBE_DEFAULT           (0x3F)
/** Default value for read hold cycles                                       */
#define CSL_EMIF_ASYNCCFG_RHOLD_DEFAULT             (0x07)
/** Default value for turn around cycles                                     */
#define CSL_EMIF_ASYNCCFG_TAROUND_DEFAULT           (0x03)
/** Default value for bus width                                              */
#define CSL_EMIF_ASYNCCFG_ASIZE_DEFAULT             (0x00)


/** Enables EMIF Word Acces                                                  */
#define CSL_EMIF_WORD_ACCESS                         (0)
/** Enables EMIF Low Byte Acces                                              */
#define CSL_EMIF_HIGHBYTE_ACCESS                     (1)
/** Enables EMIF High Byte Acces                                             */
#define CSL_EMIF_LOWBYTE_ACCESS                      (2)


/**
 * \brief NAND module specific errors
 */

/**
  *  \brief Macro to enable disable byte access
  *  byte = 0 - Enables word access
  *  byte = 1 - Enables High byte access
  *  byte = 2 - Enables Low byte access
  */
#define CSL_NAND_CHANGE_ACCESSTYPE(byte)                                                \
				     CSL_FINS(CSL_SYSCTRL_REGS->ESCR, SYS_ESCR_BYTEMODE, byte);

/** NAND Time out Error                                                      */
#define CSL_NAND_E_TIMEOUT                          (CSL_ENAND_FIRST - 0)

#if (defined(CHIP_C5505_C5515) || defined(CHIP_C5504_C5514) || defined(CHIP_C5517))

/** Macro for writing a word to nand device                                  */
#define CSL_NAND_WRITEWORD(hEmif, data)                                      \
        if(hEmif->nandWidth == CSL_EMIF_8_BIT)                               \
		{                                                                    \
			*(CSL_VUint8*)hEmif->bank.CExDATA = (Uint8)((data >> 8) & 0xFFu); \
			*(CSL_VUint8*)hEmif->bank.CExDATA = (Uint8)(data & 0xFFu);       \
		}                                                                    \
		else                                                                 \
		{                                                                    \
			*(CSL_VUint16*)hEmif->bank.CExDATA = (Uint16)data;               \
		}

/** Macro for reading a word from nand device                                */
#define CSL_NAND_READWORD(hEmif, data)                                    \
        if(hEmif->nandWidth == CSL_EMIF_8_BIT)                            \
		{                                                                 \
			data  = ((*(CSL_VUint8*)hEmif->bank.CExDATA) & 0xFFu);        \
			data  = ((*(CSL_VUint8*)hEmif->bank.CExDATA) | (data << 8));  \
		}                                                                 \
		else                                                              \
		{                                                                 \
			data = (*(CSL_VUint16*)hEmif->bank.CExDATA);                  \
		}
#else

/** Macro for writing a word to nand device                                  */
#define CSL_NAND_WRITEWORD(hEmif, data)                                      \
        if(hEmif->nandWidth == CSL_EMIF_8_BIT)                               \
		{                                                                    \
			*(CSL_VUint8*)hEmif->bank.CExDATA = (Uint8)(data & 0xFFu);       \
			*(CSL_VUint8*)hEmif->bank.CExDATA = (Uint8)((data >> 8) & 0xFF); \
		}                                                                    \
		else                                                                 \
		{                                                                    \
			*(CSL_VUint16*)hEmif->bank.CExDATA = (Uint16)data;               \
		}

/** Macro for reading a word from nand device                                */
#define CSL_NAND_READWORD(hEmif, data)                                  \
        if(hEmif->nandWidth == CSL_EMIF_8_BIT)                          \
		{                                                               \
			data  = ((*(CSL_VUint8*)hEmif->bank.CExDATA)  & 0xFFu);     \
			data |= ((*(CSL_VUint8*)hEmif->bank.CExDATA)  << 8);        \
		}                                                               \
		else                                                            \
		{                                                               \
			data = (*(CSL_VUint16*)hEmif->bank.CExDATA);                \
		}

#endif


/** Macro for writing a byte to nand device                                  */
#define CSL_NAND_WRITEBYTE(hEmif ,data)                                 \
        if(hEmif->nandWidth == CSL_EMIF_8_BIT)                          \
		{                                                               \
			*(CSL_VUint8*)hEmif->bank.CExDATA = (Uint8)(data);          \
		}                                                               \
		else                                                            \
		{                                                               \
			*(CSL_VUint16*)hEmif->bank.CExDATA = (Uint16)data;          \
		}

/** Macro for reading a byte from nand device                                */
#define CSL_NAND_READBYTE(hEmif ,addr)                                  \
        if(hEmif->nandWidth == CSL_EMIF_8_BIT)                          \
		{                                                               \
			*addr  = (*(CSL_VUint8*)hEmif->bank.CExDATA);               \
		}                                                               \
		else                                                            \
		{                                                               \
			*addr = (*(CSL_VUint16*)hEmif->bank.CExDATA);               \
		}

/** Macro to read a command from command latch address                       */
#define CSL_NANDGETCOMMAND(hEmif,cmd)                                   \
         cmd = (*(CSL_VUint16*)hEmif->bank.CExCLE);                     \

/** Macro to read address from command latch address                         */
#define CSL_NANDGETADDRESS(hEmif,addr)                                  \
         addr = *(CSL_VUint16*)hEmif->bank.CExALE;                      \

/** Macro to read nand async wait config register                            */
#define CSL_NANDGETWAITCFG(hEmif,value)                                 \
         value = (Uint32)((hEmif->regs->AWCCR1) | (hEmif->regs->AWCCR2 << 16));


/** Macro to read nand async 1 config register                               */
#define CSL_NANDGETCS2ASYNCCFG(hEmif,value)                             \
         value = (Uint32)(hEmif->regs->ACS2CR1 |                        \
                          (hEmif->regs->ACS2CR2 << 16));                \

/** Macro to read nand async 2 config register                               */
#define CSL_NANDGETCS3ASYNCCFG(hEmif,value)                             \
         value = (Uint32)(hEmif->regs->ACS3CR1 |                        \
                          (hEmif->regs->ACS3CR2 << 16));                \

/** Macro to read nand async 3 config register                               */
#define CSL_NANDGETCS4ASYNC3CFG(hEmif,value)                            \
         value = (Uint32)(hEmif->regs->ACS4CR1 |                        \
                          (hEmif->regs->ACS4CR2 << 16));                \

/** Macro to read nand async 4 config register                               */
#define CSL_NANDGETCS5ASYNC4CFG(hEmif,value)                            \
         value = (Uint32)(hEmif->regs->ACS5CR1 |                        \
                          (hEmif->regs->ACS5CR2 << 16));                \

/** Macro to read nand control register                                      */
#define CSL_NANDGETCTRL(hEmif,value)                                    \
         value = (Uint16)(CSL_FEXTR(hEmif->regs->NANDFCR, 13, 0));

/** Macro to read nand interrupt raw register                                */
#define CSL_NANDGETINTRAW(hEmif,intrStatus)                             \
         intrStatus = (Uint16)(CSL_FEXTR(hEmif->regs->EIRR, 5, 0));

/** Macro to read nand interrupt mask register                               */
#define CSL_NANDGETINTMASK(hEmif,intrStatus)                            \
         intrStatus = (Uint16)(CSL_FEXTR(hEmif->regs->EIMR, 5, 0));

/** Macro to read nand interrupt mask set register                           */
#define CSL_NANDGETINTMASKSET(hEmif,intrStatus)                         \
         intrStatus = (Uint16)(CSL_FEXTR(hEmif->regs->EIMSR, 5, 0));

/** Macro to read nand interrupt mask clear register                         */
#define CSL_NANDGETINTMASKCLEAR(hEmif,intrStatus)                       \
         intrStatus = (Uint16)(CSL_FEXTR(hEmif->regs->EIMCR, 5, 0));

/**
@} */


/**************************************************************************\
* EMIF global typedef declarations                                         *
\**************************************************************************/

/** @addtogroup CSL_EMIF_ENUM
 @{ */

/**
 * \brief EMIF Width enumeration
 */
typedef enum {
	/** External Device Bus Width 8 bit                                      */
    CSL_EMIF_8_BIT  = (0u),
    /** External Device Bus Width 16 bit                                     */
    CSL_EMIF_16_BIT = (1u)
} CSL_EmifWidth;

/**
 * \brief SDRAM CAS latency
 */
typedef enum {
	/** Reserved value                                                       */
    CSL_SDRAM_CL_RSV0        = (0u),
	/** Reserved value                                                       */
    CSL_SDRAM_CL_RSV1        = (1u),
	/** CAS latency set to 2 EM_SDCLK cycles                                 */
    CSL_SDRAM_CL_2_EM_SDCLK  = (2u),
    /** CAS latency set to 3 EM_SDCLK cycles                                 */
    CSL_SDRAM_CL_3_EM_SDCLK  = (3u),
	/** Reserved value                                                       */
    CSL_SDRAM_CL_RSV4        = (4u),
	/** Reserved value                                                       */
    CSL_SDRAM_CL_RSV5        = (5u),
	/** Reserved value                                                       */
    CSL_SDRAM_CL_RSV6        = (6u),
	/** Reserved value                                                       */
    CSL_SDRAM_CL_RSV7        = (7u)
} CSL_SdramCL;

/**
 * \brief SDRAM IBANK size
 */
typedef enum {
	/** 1 bank SDRAM devices                                                 */
    CSL_SDRAM_IBANK_SIZE_1    = (0u),
    /** 2 bank SDRAM devices                                                 */
    CSL_SDRAM_IBANK_SIZE_2    = (1u),
    /** 4 bank SDRAM devices                                                 */
    CSL_SDRAM_IBANK_SIZE_4    = (2u),
	/** Reserved value                                                       */
    CSL_SDRAM_IBANK_SIZE_RSV3 = (3u),
	/** Reserved value                                                       */
    CSL_SDRAM_IBANK_SIZE_RSV4 = (4u),
	/** Reserved value                                                       */
    CSL_SDRAM_IBANK_SIZE_RSV5 = (5u),
	/** Reserved value                                                       */
    CSL_SDRAM_IBANK_SIZE_RSV6 = (6u),
	/** Reserved value                                                       */
    CSL_SDRAM_IBANK_SIZE_RSV7 = (7u)
} CSL_SdramIbank;

/**
 * \brief SDRAM page size
 */
typedef enum {
	/** 8 column address bits (256 elements per row)                         */
    CSL_SDRAM_PAGE_SIZE_256   = (0u),
    /** 9 column address bits (512 elements per row)                         */
    CSL_SDRAM_PAGE_SIZE_512   = (1u),
    /** 10 column address bits (1024 elements per row)                       */
    CSL_SDRAM_PAGE_SIZE_1024  = (2u),
    /** 11 column address bits (2048 elements per row)                       */
    CSL_SDRAM_PAGE_SIZE_2048  = (3u),
	/** Reserved value                                                       */
    CSL_SDRAM_PAGE_SIZE_RSV4  = (4u),
	/** Reserved value                                                       */
    CSL_SDRAM_PAGE_SIZE_RSV5  = (5u),
	/** Reserved value                                                       */
    CSL_SDRAM_PAGE_SIZE_RSV6  = (6u),
	/** Reserved value                                                       */
    CSL_SDRAM_PAGE_SIZE_RSV7  = (7u)
} CSL_SdramPageSize;

/**
 * \brief SDRAM Partial array self refresh
 */
typedef enum {
	/** 4 banks will be refreshed                                            */
    CSL_SDRAM_PASR_4    = (0u),
	/** 2 banks will be refreshed                                            */
    CSL_SDRAM_PASR_2    = (1u),
	/** 1 banks will be refreshed                                            */
    CSL_SDRAM_PASR_1    = (2u),
	/** Reserved value                                                       */
    CSL_SDRAM_PASR_RSV0 = (3u),
	/** Reserved value                                                       */
    CSL_SDRAM_PASR_RSV1 = (4u),
	/** Half banks will be refreshed                                         */
    CSL_SDRAM_PASR_hf   = (5u),
	/** Quarter banks will be refreshed                                      */
    CSL_SDRAM_PASR_qt   = (6u),
	/** Reserved value                                                       */
    CSL_SDRAM_PASR_RSV3 = (7u)
} CSL_SdramSelfRefresh;

/**
 * \brief SDRAM Row size
 */
typedef enum {
	/** 9 row address bits                                                   */
    CSL_SDRAM_ROW_ADDR_BITS_9    = (0u),
	/** 10 row address bits                                                  */
    CSL_SDRAM_ROW_ADDR_BITS_10   = (1u),
	/** 11 row address bits                                                  */
    CSL_SDRAM_ROW_ADDR_BITS_11   = (2u),
	/** 12 row address bits                                                  */
    CSL_SDRAM_ROW_ADDR_BITS_12   = (3u),
	/** 13 row address bits                                                  */
    CSL_SDRAM_ROW_ADDR_BITS_13   = (4u),
	/** 14 row address bits                                                  */
    CSL_SDRAM_ROW_ADDR_BITS_14   = (5u),
	/** Reserved value                                                       */
    CSL_SDRAM_ROW_ADDR_BITS_RSV6 = (6u),
	/** Reserved value                                                       */
    CSL_SDRAM_ROW_ADDR_BITS_RSV7 = (7u)
} CSL_SdramRowSize;

/**
 * \brief SDRAM drive strength
 */
typedef enum {
	/** Full drive strength                                                 */
    CSL_SDRAM_DRIVE_FULL        = (0u),
	/** Half drive strength                                                 */
    CSL_SDRAM_DRIVE_HALF        = (1u),
	/** One fourth drive strength                                           */
    CSL_SDRAM_DRIVE_ONEFOURTH   = (2u),
	/** One eighth drive strength                                           */
    CSL_SDRAM_DRIVE_ONEEIGTH    = (3u)
} CSL_SdramDriveStrength;

/**
 * \brief Type of NAND detected.
 */
typedef enum {
	/** No NAND detected                                                     */
    CSL_NAND_NONE = 0u,
    /** Big Block NAND detected                                              */
    CSL_NAND_BIG_BLOCK,
	/** Small Block NAND detected                                            */
    CSL_NAND_SMALL_BLOCK,
    /** Unknown/Invalid NAND                                                 */
    CSL_NAND_INVALID
} CSL_NandType;

/**
 * \brief NAND Page size enumeration
 */
typedef enum {
	/** Page size is 256 + 8bytes                                            */
    CSL_NAND_PAGESZ_256  = (0u),
	/** Page size is 512 + 16bytes                                           */
    CSL_NAND_PAGESZ_512  = (1u),
	/** Page size is 1024 + 32 bytes                                         */
    CSL_NAND_PAGESZ_1024 = (2u),
    /** Page size is 2048 + 64 bytes                                         */
    CSL_NAND_PAGESZ_2048 = (3u)
} CSL_NandPageSize;

/**
 * \brief   NAND Asynchronous Bank number
 */
typedef enum {
	/** NAND Bank 0 - EMIF CS2                                               */
    CSL_NAND_BANK_0 = (0u),
	/** NAND Bank 1 - EMIF CS3                                               */
    CSL_NAND_BANK_1 = (1u),
    /** NAND Bank 2 - EMIF CS4                                               */
    CSL_NAND_BANK_2 = (2u),
    /** NAND Bank 3 - EMIF CS5                                               */
    CSL_NAND_BANK_3 = (3u),
    /** NAND Bank Max (Book-keep)                                            */
    CSL_NAND_BANK_MAX
} CSL_NandBankNo;

/**
 * \brief   NAND Chip selection
 */
typedef enum {
	/** EMIF Chip selsect 2                                                  */
    CSL_EMIF_CS2 = (0u),
	/** EMIF Chip selsect 3                                                  */
    CSL_EMIF_CS3 = (1u),
    /** EMIF Chip selsect 4                                                  */
    CSL_EMIF_CS4 = (2u),
    /** EMIF Chip selsect 5                                                  */
    CSL_EMIF_CS5 = (3u)
} CSL_EmifChipSelect;

/**
 * \brief   EMIF Wait pin mapping
 */
typedef enum {
	/** Use the EM_WAIT0 pin                                                 */
    CSL_EM_WAIT0  = (0u),
	/** Use the EM_WAIT1 pin                                                 */
    CSL_EM_WAIT1 = (1u),
    /** Use the EM_WAIT2 pin                                                 */
    CSL_EM_WAIT2 = (2u),
    /** Use the EM_WAIT3 pin                                                 */
    CSL_EM_WAIT3 = (3u)
} CSL_EmifWaitPin;

/**
 * \brief   EMIF wait polarity
 */
typedef enum {
	/** NAND wait polarity low                                               */
    CSL_EMIF_WP_LOW = (0u),
	/** NAND wait polarity high                                              */
    CSL_EMIF_WP_HIGH = (1u)
} CSL_EmifWaitPol;

/**
 * \brief   EMIF Operating mode
 */
typedef enum {
	/** EMIF polled mode of operation                                        */
    CSL_EMIF_OPMODE_POLLED = (0u),
	/** EMIF DMA mode of operation                                           */
    CSL_EMIF_OPMODE_DMA = (1u),
    /** EMIF Interrupt mode operation                                        */
    CSL_EMIF_OPMODE_INTRRUPT = (2u)
} CSL_EmifOpMode;

/**
 * \brief   EMIF Access width
 */
typedef enum {
	/** Emif 16-bit word access                                              */
    CSL_EMIF_16BIT = (0u),
	/** Emif 8-bit word access that selects the high byte                    */
    CSL_EMIF_8BIT_HIGH = (1u),
    /** Emif 8-bit word access that selects the low byte                     */
    CSL_EMIF_8BIT_LOW = (2u)
} CSL_EmifAccess;

/**
 * \brief   EMIF instance number
 */
typedef enum {
	/** NAND hardware instance 0                                             */ 
    CSL_NAND_INST_0  = (0u),
	/** SDRAM hardware instance 0                                            */
    CSL_SDRAM_INST_0 = (1u),
	/** NOR hardware instance 0                                              */
    CSL_NOR_INST_0   = (2u),
	/** Invalid hardware instance                                            */
    CSL_INST_INVALID = (3u)
} CSL_EmifInsId;


/**
@} */

/**************************************************************************\
* EMIF global data structure declarations                                  *
\**************************************************************************/

/**
\addtogroup CSL_EMIF_DATASTRUCT
@{ */
/**
 * \brief Current Asynchronous NAND Bank configuration.
 */
typedef struct CSL_NandAsyncBank {
	/** Current NAND Data register                                           */
    volatile Uint32     CExDATA;
    /** Current NAND Address latch register                                  */
    volatile Uint32     CExALE;
    /** Current NAND Command latch register                                  */
    volatile Uint32     CExCLE;
    /** Current NAND ECC register                                            */
    volatile Uint32     CExNUM;
} CSL_NandAsyncBank;

/**
 * \brief This object contains the reference to the instance of emif device
 *
 *  This object is initialized during emif initialization
 */
typedef struct CSL_EmifObj {
	/** EMIF register overlay structure                                      */
    CSL_EmifRegsOvly      regs;
    /** CPU system control register overlay structure                        */
    CSL_SysRegsOvly       sysCtrlRegs;
    /** Width of EMIF (8 or 16 bit)                                          */
    CSL_EmifWidth         emifWidth;
	/** External Device Width.                                               */
	CSL_EmifWidth         nandWidth;
	/** Interrupt number of EMIF                                             */
    Int                   intrNumEmif;
    /** EMIF Operating mode                                                  */
    CSL_EmifOpMode        emifOpMode;
	/** Nand chip select Id                                                  */
	CSL_EmifChipSelect    chipSelect;
	/** Wait pin selected for EMIF                                           */
	Uint8                 waitPin;
    /** Current NAND Asynchronous bank                                       */
    CSL_NandAsyncBank     bank;
	/** NAND page Size                                                       */
    CSL_NandPageSize      nandPageSize;
    /** NAND Address cycles for setting page/block address                   */
    Uint16                addrCycles;
    /** Type of the nand device                                              */
    CSL_NandType          nandType;
} CSL_EmifObj;

/**
 * \brief SDRAM config structure
 */
typedef struct CSL_SdramCfg {
	/** Self refresh mode selection                                          */
    Uint16    selfRefresh;
    /** Enable power dowm mode                                               */
    Uint16    pdMode;
    /** Perform refresh during powerdown                                     */
    Uint16    pdwr;
	/** Partial array self refresh                                           */
    Uint16    pasr;
    /** Number of row address bits of connected SDRAM devices                */
    Uint16    rowSize;
    /** Internal bank position                                               */
    Uint16    ibankPos;
    /** SDRAM drive strength                                                 */
	Uint16    sdramDrive;
    /** Bits 9 to 1 lock                                                     */
    Uint16    bit9to1Lock;
    /** Narrow mode bit                                                      */
	Uint16    NM;
    /** CAS latency cycles                                                   */
    Uint16    CasLatency;
    /** Bits 11 to 9 lock.                                                   */
    Uint16    bit11to9Lock;
    /** Number of internal SDRAM banks                                       */
    Uint16    num_ibank;
    /** External chip select setup                                           */
    Uint16    ebank;
    /** Internal page size of SDRAM                                          */
    Uint16    pageSize;
} CSL_SdramCfg;

/**
 * \brief SDRAM timer structure
 */
typedef struct CSL_SdramTimr {
	/** Row address strobe time                                              */
    Uint16    tRAS;
    /** Row cycle time                                                       */
    Uint16    tRC;
    /** Time between two row activate in different banks                     */
    Uint16    tRRD;
    /** Refresh to Active delay/ Refresh cycle time                          */
    Uint16    tRFC;
    /** RAS precharge delay                                                  */
    Uint16    tRP;
    /** RAS to CAS delay                                                     */
    Uint16    tRCD;
    /** Time between last write to precharge                                 */
    Uint16    tWR;
    /** Self Refresh Exit Timing                                             */
    Uint16    tXS;
    /** SDRAM Self Refresh Rate                                              */
    Uint16    refRate;
} CSL_SdramTimr;

/**
 * \brief Async wait config structure
 */
typedef struct CSL_EmifAsyncWaitCfg {
    /** Wait polarity for nand ports                                         */
	CSL_EmifWaitPol       waitPol;
	/** Wait pin mapping                                                     */
	CSL_EmifWaitPin       waitPin;
	/** EMIF maximum extended wait cycles                                    */
    Uint16              waitCycles;
} CSL_EmifAsyncWaitCfg;

/**
 * \brief Emif Async config structure
 */
typedef struct CSL_EmifAsyncCfg {
	/** Strobe mode selection                                                */
    Uint16    selectStrobe;
    /** Enable extended wait mode                                            */
    Uint16    ewMode;
    /** Write strobe setup cycles                                            */
    Uint16    w_setup;
    /** Write strobe duration cycles                                         */
    Uint16    w_strobe;
    /** Write strobe hold cycle                                              */
    Uint16    w_hold;
    /** Read strobe setup cycles                                             */
    Uint16    r_setup;
    /** Read strobe duration cycles                                          */
	Uint16    r_strobe;
	/** Read strobe hold cycle                                               */
    Uint16    r_hold;
    /** Turn around cycles                                                   */
    Uint16    turnAround;
	/** Asynchronous memory size                                             */
    Uint16    aSize;
} CSL_EmifAsyncCfg;


/**
 * \brief Nand Hw configuration structure
 */
typedef struct CSL_AsyncConfig {
    /** Byte mode of Emif access                                             */
    CSL_EmifAccess         emifAccess;
    /** Nand chip select Id                                                  */
	CSL_EmifChipSelect     chipSelect;
	/** Nand Async wait config structure                                     */
	CSL_EmifAsyncWaitCfg   *asyncWaitCfg;
	/** Nand Async config structure                                          */
	CSL_EmifAsyncCfg       *asyncCfg;
} CSL_AsyncConfig;

/**
 * \brief Nand Hw configuration structure
 */
typedef struct CSL_NandConfig {
	/** External Device Width.                                               */
	CSL_EmifWidth          nandWidth;
	/** NAND page Size                                                       */
    CSL_NandPageSize       nandPageSize;
    /** Asynchronous bank                                                    */
    CSL_NandBankNo         nandBankNo;
    /** NAND Operating mode                                                  */
    CSL_EmifOpMode         emifOpMode;
    /** Type of the nand device                                              */
    CSL_NandType           nandType;
} CSL_NandConfig;

/**  \brief Emif object structure pointer                                    */
typedef CSL_EmifObj *CSL_EmifHandle;

/**
@} */


/**************************************************************************\
* EMIF function declarations                                               *
\**************************************************************************/

/** @addtogroup CSL_EMIF_FUNCTION
 @{ */
/** ============================================================================
 *   @n@b EMIF_init
 *
 *   @b Description
 *   @n This is the initialization function for the emif CSL.
 *      It populates emif object structure information. This API should
 *      be called before calling any other emif CSL APIs.
 *
 *   @b Arguments
 *   @verbatim
            emifObj       Pointer to emif object structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand init is successful
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  EMIF object structure is populated
 *
 *   @b Modifies
 *   @n EMIF object structure
 *
 *   @b Example
 *   @verbatim
			CSL_EmifObj    emifObj;
			CSL_Status     status;

			status = EMIF_init(&emifObj);
     @endverbatim
 *  ============================================================================
 */
CSL_Status EMIF_init(CSL_EmifObj    *emifObj);

/** ============================================================================
 *   @n@b SDRAM_config
 *
 *   @b Description
 *   @n This API configures the sdram hardware registers.
 *
 *   @b Arguments
 *   @verbatim
            hemif         Handle to the emif object
            sdramConfig   SDRAM configuration structure
			sdramTimr     SDRAM timer configuration structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - SDRAM configurations are successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid config structure
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Configures sdram registers
 *
 *   @b Modifies
 *   @n sdram registers
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ...
            ...
            ...
            status = SDRAM_config(hEmif, &sdramConfig, &sdramTimr);
     @endverbatim
 *  ============================================================================
 */
CSL_Status SDRAM_config(CSL_EmifHandle      hEmif,
                        CSL_SdramCfg        *sdramConfig,
                        CSL_SdramTimr       *sdramTimr);
/** ============================================================================
 *   @n@b SDRAM_enablePowerDownMode
 *
 *   @b Description
 *   @n This API enables power dowm mode for SDRAM.
 *
 *   @b Arguments
 *   @verbatim
 *          hemif         Handle to the emif object
 *   @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - SDRAM power down mode set successfully
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and SDRAM configurations should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  SDRAM is in powerdown mode
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = SDRAM_config(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = SDRAM_enablePowerDownMode(hEmif);
     @endverbatim
 *  ============================================================================
 */
CSL_Status SDRAM_enablePowerDownMode(CSL_EmifHandle      hEmif);
/** ============================================================================
 *   @n@b SDRAM_disablePowerDownMode
 *
 *   @b Description
 *   @n This API disables power dowm mode for SDRAM.
 *
 *   @b Arguments
 *   @verbatim
 *          hemif         Handle to the emif object
 *   @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - SDRAM power down mode disabled successfully
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and SDRAM configurations and SDRAM must be in powerdown mode
 *       should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  SDRAM is out of powerdown mode
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = SDRAM_config(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = SDRAM_enablePowerDownMode(hEmif);
			...
			...
            status = SDRAM_disablePowerDownMode(hEmif);
     @endverbatim
 *  ============================================================================
 */
CSL_Status SDRAM_disablePowerDownMode(CSL_EmifHandle      hEmif);

/** ============================================================================
 *   @n@b SDRAM_enableSelfRefreshMode
 *
 *   @b Description
 *   @n This API enables self refresh mode for SDRAM.
 *
 *   @b Arguments
 *   @verbatim
 *          hemif         Handle to the emif object
 *   @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - SDRAM self refresh mode enabled successfully
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and SDRAM configurations and should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  SDRAM is in self refresh mode
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = SDRAM_config(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = SDRAM_enableSelfRefreshMode(hEmif);
     @endverbatim
 *  ============================================================================
 */
CSL_Status SDRAM_enableSelfRefreshMode(CSL_EmifHandle      hEmif);
/** ============================================================================
 *   @n@b SDRAM_disableSelfRefreshMode
 *
 *   @b Description
 *   @n This API disables self refresh mode for SDRAM.
 *
 *   @b Arguments
 *   @verbatim
 *          hemif         Handle to the emif object
 *   @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - SDRAM self refresh mode disabled successfully
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and SDRAM configurations and should be called successfully
 *       SDRAM must be in self refresh mode
 *
 *   <b> Post Condition </b>
 *   @n  SDRAM is out of self refresh mode
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = SDRAM_config(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = SDRAM_enableSelfRefreshMode(hEmif);
			...
			...
            status = SDRAM_disableSelfRefreshMode(hEmif);
     @endverbatim
 *  ============================================================================
 */
CSL_Status SDRAM_disableSelfRefreshMode(CSL_EmifHandle      hEmif);

/** ============================================================================
 *   @n@b SDRAM_read
 *
 *   @b Description
 *   @n This API reads numWords from sdram.
 *
 *   @b Arguments
 *   @verbatim
            hEmif         Handle to the emif object
            numWords      Number of words to be read
			sdramAddr     SDRAM address to start the read operation
            dataBuff      Data buffer to copy data read from SDRAM
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - SDRAM read is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid input parameters
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and SDRAM configurations should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Reads from sdram memory
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = SDRAM_config(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = SDRAM_read(hEmif, numWords, sdramAddr, &dataBuff);
     @endverbatim
 *  ============================================================================
 */
CSL_Status SDRAM_read(CSL_EmifHandle      hEmif,
                      Uint32              numWords,
                      Uint32              sdramAddr,
                      Uint16              *dataBuff);

/** ============================================================================
 *   @n@b SDRAM_write
 *
 *   @b Description
 *   @n This API writes numWords to sdram.
 *
 *   @b Arguments
 *   @verbatim
            hEmif         Handle to the emif object
            numWords      Number of words to be written
			sdramAddr     SDRAM address to start the write operation
            dataBuff      Data to be written to SDRAM
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - SDRAM write is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid config structure
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and SDRAM configurations should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Writes into sdram memory
 *
 *   @b Modifies
 *   @n sdram memory content
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = SDRAM_config(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = SDRAM_write(hEmif, numWords, sdramAddr, &dataBuff);
     @endverbatim
 *  ============================================================================
 */
CSL_Status SDRAM_write(CSL_EmifHandle      hEmif,
                       Uint32              numWords,
                       Uint32              sdramAddr,
                       Uint16              *dataBuff);

/** ============================================================================
 *   @n@b EMIF_asyncConfig
 *
 *   @b Description
 *   @n This API configures the asynchronous memory hardware registers.
 *
 *   @b Arguments
 *   @verbatim
            hEmif         Handle to the emif object
            emifConfig    Emif configuration structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Asynchronous configuration is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid config structure
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Configures asynchronous registers
 *
 *   @b Modifies
 *   @n emif registers
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;
            CSL_EmifAsyncWaitCfg   asyncWaitConfig;
            CSL_EmifAsyncCfg       asyncConfig;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ...
            emifCfg.emifWidth = CSL_EMIF_8_BIT;
            ...
            ...
            emifCfg.asyncWaitCfg = &asyncWaitConfig;
        	emifCfg.asyncCfg     = &asyncConfig;
            status = EMIF_asyncConfig(hEmif, &emifCfg);
     @endverbatim
 *  ============================================================================
 */
CSL_Status EMIF_asyncConfig(CSL_EmifHandle      hEmif,
                            CSL_AsyncConfig     *asyncConfig);

/** ============================================================================
 *   @n@b NOR_checkStatus
 *
 *   @b Description
 *   @n This API checks the status of Erase/Program command to the NOR device.
 *      This API must be called after sending the command to the NOR device.
 *
 *   @b Arguments
 *   @verbatim
            timeOut    Timeout count for the particular command
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - NOR status check is successful
 *   @li                    CSL_ESYS_FAIL     - Time-out or any errors has occured
 *
 *   <b> Pre Condition </b>
 *   @n  Erase or Write commands are be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Returns time-out condition(If occurs)
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_EmifHandle    hEmif;
            CSL_Status        status;
            . . .
            . . .
			status = NOR_checkStatus(timeOut);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NOR_checkStatus(Uint32 timeOut);

/** ============================================================================
 *   @n@b NOR_WriteNwords
 *
 *   @b Description
 *   @n This API writes numWords to NOR flash.
 *
 *   @b Arguments
 *   @verbatim
            hemif         Handle to the emif object
            numWords      Number of words to be written
			norAddr       NOR address to start the write operation
            dataBuff      Data to be written to NOR
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - NOR write is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid config structure
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and Asynchronous configurations should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Writes into NOR memory
 *
 *   @b Modifies
 *   @n NOR memory content
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = EMIF_asyncConfig(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = NOR_WriteNwords(hEmif, numWords, norAddr, &dataBuff);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NOR_WriteNwords(CSL_EmifHandle      hEmif,
                           Uint32              numWords,
                           Uint32              norAddr,
                           Uint16              *dataBuff);

/** ============================================================================
 *   @n@b NOR_readNwords
 *
 *   @b Description
 *   @n This API reads numWords from NOR flash.
 *
 *   @b Arguments
 *   @verbatim
            hEmif         Handle to the emif object
            numWords      Number of words to be read
			sdramAddr     NOR address to start the read operation
            dataBuff      Data buffer to copy data read from NOR
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - NOR read is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid input parameters
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and Asynchronous configurations should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Reads from NOR flash
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = EMIF_asyncConfig(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = NOR_readNwords(hEmif, numWords, norAddr, &dataBuff);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NOR_readNwords(CSL_EmifHandle      hEmif,
                          Uint32              numWords,
                          Uint32              norAddr,
                          Uint16              *dataBuff);

/** ============================================================================
 *   @n@b NOR_sendCommand
 *
 *   @b Description
 *   @n This API sends command to NOR flash.
 *
 *   @b Arguments
 *   @verbatim
            hEmif         Handle to the emif object
			norAddr       NOR address to start the write operation
            command       Command to be sent to the NOR flash
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - NOR command sent successfully
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameters
 *
 *   <b> Pre Condition </b>
 *   @n  Emif init and Asynchronous configurations should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends command to NOR flash
 *
 *   @b Modifies
 *   @n Writes command to the NOR flash
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj            emifObj;
            CSL_Status             status;
            CSL_EmifConfig         emifCfg;
            CSL_EmifHandle         hEmif;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            status = EMIF_asyncConfig(hEmif, &sdramConfig, &sdramTimr);
            ...
            ...
            ...
			status = NOR_sendCommand(hEmif, norAddr, command);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NOR_sendCommand(CSL_EmifHandle      hEmif,
                           Uint32              norAddr,
                           Uint16              command);

/** ============================================================================
 *   @n@b NAND_setup
 *
 *   @b Description
 *   @n This API configures the nand hardware registers.
 *
 *   @b Arguments
 *   @verbatim
            hEmif         Handle to the emif object
            nandConfig    Nand configuration structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand setup is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid config structure
 *
 *   <b> Pre Condition </b>
 *   @n  Nand init should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Configures nand registers
 *
 *   @b Modifies
 *   @n nand registers
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj            emifObj;
            CSL_Status             status;
            CSL_NandConfig         nandCfg;
            CSL_EmifHandle         hEmif;
            CSL_NandAsyncWaitCfg   asyncWaitConfig;
            CSL_NandAsyncCfg       asyncConfig;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ...
            nandCfg.nandWidth = CSL_EMIF_8_BIT;
            ...
            ...
            nandCfg.asyncWaitCfg = &asyncWaitConfig;
        	nandCfg.asyncCfg     = &asyncConfig;
            status = NAND_setup(hEmif, &nandCfg);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_setup(CSL_EmifHandle      hEmif,
                      CSL_NandConfig      *nandConfig);

/** ============================================================================
 *   @n@b NAND_getBankInfo
 *
 *   @b Description
 *   @n This API gives the bank details of the nand device. This API populates
 *      the base and offset address locations for the NAND flash based on the
 *      bank number passed as the parameter. Bank number should be decide based
 *      on the EMIF chip select connected to NAND flash as shown below.
 *      CSL_NAND_BANK_0 - EMIF_CS2
 *      CSL_NAND_BANK_1 - EMIF_CS3
 *      CSL_NAND_BANK_2 - EMIF_CS4
 *      CSL_NAND_BANK_3 - EMIF_CS5
 *
 *      NOTE: This API sets ALE and CLE address offset to default values assuming
 *      A11 address bit is connected to ALE signal of NAND flash and A12 address
 *      bit is connected to CLE signal of NAND flash.
 *      Use NAND_setLatchEnableOffset() to change the default offset values.
 *
 *   @b Arguments
 *   @verbatim
            hEmif      Handle to the emif object
            bank       Pointer to nand bank info structure
            bankNum    Nand bank number
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand get bank info is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Nand init should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Populates nand bank info structure
 *
 *   @b Modifies
 *   @n Nand bank info structure
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
			Uint16         bankNum;
			CSL_Status     status;
			CSL_EmifHandle hEmif;

			bankNum = 0;
			status = EMIF_init(&emifObj);
			hEmif  = &emifObj;
			....
			....
            status = NAND_getBankInfo(hEmif, (CSL_NandAsyncBank*)&hEmif->bank, bankNum);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_getBankInfo(CSL_EmifHandle      hEmif,
                            CSL_NandAsyncBank   *bank,
                            Uint16              bankNum);

/** ============================================================================
 *   @n@b NAND_setLatchEnableOffset
 *
 *   @b Description
 *   @n This API sets the CLE and ALE address offset.
 *      Any of the EMIF address lines can be used to drive ALE and CLE of the
 *      NAND flash. ALE and CLE address offset are decided based of the address
 *      lines used to drive ALE and CLE pins. This API should be called after
 *      calling NAND_getBankInfo() API to modify the ALE and CLE address from
 *      the default value.
 *
 *      NOTE: Addresses passed should be offset values from the base address.
 *      For example assume that EMIF A11 line is used to drive ALE pin and
 *      EMIF A12 line is used to driver CLE pin. Then the address offset for
 *      ALE will be 0x1000 and address offset for CLE will be 0x2000.
 *
 *      Calling this API is mandatory in case of NAND ALE and CLE connected to
 *      pins other than A11 and A12 respectively. Otherwise NAND CSL APIs
 *      will not function properly.
 *
 *   @b Arguments
 *   @verbatim
            hEmif         Handle to the emif object
            addrOffset    ALE offset location
            cmdOffset     CLE offset location
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Set address offset is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Nand init should be called successfully
 *   @n  NAND_getBankInfo() should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets the ALE and CLE address offset
 *
 *   @b Modifies
 *   @n NAND handle
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
			Uint16         bankNum;
			CSL_Status     status;
			CSL_EmifHandle hEmif;

			bankNum = 0;
			status = EMIF_init(&emifObj);
			hEmif  = &emifObj;
			....
			....
            status = NAND_getBankInfo(hEmif, (CSL_NandAsyncBank*)&hEmif->bank, bankNum);
            status = NAND_setLatchEnableOffset(hEmif, 0x2000, 0x4000);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_setLatchEnableOffset(CSL_EmifHandle    hEmif,
                                     Uint32            addrOffset,
                                     Uint32            cmdOffset);

/** ============================================================================
 *   @n@b NAND_isStatusWriteProtected
 *
 *   @b Description
 *   @n This is the API used to check if the nand device is write protected.
 *      It is not possible write any data to nand if it is write-protected.
 *      So this API must be called before calling the write API to check the
 *      nand status.
 *
 *   @b Arguments
 *   @verbatim
            hEmif         Handle to the emif object
            WPstatus      Write protect status pointer
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_init and NAND_getBankInfo should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Write protect status is returned in status variable
 *   @li    TRUE     - NAND device is write protected
 *   @li    FALSE    - NAND device is not write protected
 *
 *   @b Modifies
 *   @n Write protect status variable
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
            Uint16         bankNum;
            CSL_Status     status;
            CSL_EmifHandle hEmif;
            Uint16         wpstatus;

            bankNum = 0;
            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ....
            ....
            status = NAND_getBankInfo(hEmif, (CSL_NandAsyncBank*)&hEmif->bank, bankNum);
             ....
             ....
            status = NAND_isStatusWriteProtected(hEmif,&wpstatus);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_isStatusWriteProtected(CSL_EmifHandle      hEmif,
                                       Uint16              *WPstatus);

/** ============================================================================
 *   @n@b NAND_sendCommand
 *
 *   @b Description
 *   @n Any command to the nand device should be sent through this API.
 *      nand device is having specific commands for each operation.
 *
 *   @b Arguments
 *   @verbatim
            hEmif          Handle to the emif object
            cmd            Command to the nand device
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand send command is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_init and NAND_getBankInfo should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends command to the nand device
 *
 *   @b Modifies
 *   @n Writes command to the command latch address
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
            Uint16         bankNum;
            CSL_Status     status;
            CSL_EmifHandle hEmif;

            bankNum = 0;
            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ....
            ....
            status = NAND_getBankInfo(hEmif, (CSL_NandAsyncBank*)&hEmif->bank, bankNum);
            ....
            ....
            status = NAND_sendCommand(hEmif,CSL_NAND_CMD_READ_START);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_sendCommand(CSL_EmifHandle    hEmif,
                            CSL_VUint16       cmd);

/** ============================================================================
 *   @n@b NAND_checkCommandStatus
 *
 *   @b Description
 *   @n This API checks the status of any command to the nand device.
 *      This API must be called after sending any command to the nand device.
 *
 *   @b Arguments
 *   @verbatim
            hEmif    Handle to the emif object
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand status check is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_NAND_E_TIMEOUT - Time-out has occured
 *
 *   <b> Pre Condition </b>
 *   @n  NAND_sendCommand API should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Returns time-out condition(If occurs)
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_EmifHandle    hEmif;
            CSL_Status        status;

            status = NAND_sendCommand(hEmif, CSL_NAND_CMD_READ_START);

            if(status == CSL_SOK)
            {
                status = NAND_checkCommandStatus(hEmif);
            }
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_checkCommandStatus(CSL_EmifHandle    hEmif);

/** ============================================================================
 *   @n@b NAND_setAddress
 *
 *   @b Description
 *   @n This API used to set address of nand page to read/write data from/to
 *      nand device. Page address must be set to a valid nand page before
 *      calling read/write APIs.
 *
 *   @b Arguments
 *   @verbatim
            hEmif          Handle to the emif object
            addr           Addres value to set
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand set address is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_init and NAND_getBankInfo should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets nand address
 *
 *   @b Modifies
 *   @n Writes address to the address latch
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
            Uint16         bankNum;
            CSL_Status     status;
            CSL_EmifHandle hEmif;

            bankNum = 0;
            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ....
            ....
            status = NAND_getBankInfo(hEmif, (CSL_NandAsyncBank*)&hEmif->bank, bankNum);
            ....
            ....
            status = NAND_setAddress(hEmif,0x01);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_setAddress(CSL_EmifHandle    hEmif,
                           Uint16            addr);

/** ============================================================================
 *   @n@b NAND_enableHwECC
 *
 *   @b Description
 *   @n This API enables hardware ECC(Error Check and  Correction) of the
 *      nand device. ECC is used to check and correct errors occurred during
 *      nand data transfer.
 *
 *   @b Arguments
 *   @verbatim
            hEmif      Handle to the emif object
            csInput    Nand chip selection input
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand enable HW ECC is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Nand init should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Enables nand hardware error check and correction
 *
 *   @b Modifies
 *   @n Nand ECC registers
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj         emifObj;
            CSL_Status          status;
            CSL_EmifHandle      hEmif;
            CSL_EmifChipSelect  csInput;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ....
            ....
        	csInput = CSL_NAND_CE0;
            status = NAND_enableHwECC(hEmif,csInput);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_enableHwECC(CSL_EmifHandle        hEmif,
                            CSL_EmifChipSelect    csInput);

/** ============================================================================
 *   @n@b NAND_disableHwECC
 *
 *   @b Description
 *   @n This API disables hardware ECC of the nand device.
 *
 *   @b Arguments
 *   @verbatim
            hEmif      Handle to the emif object
            csInput    Nand chip selection input
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand disable HW ECC is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  NAND_enableHwECC API should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Disables nand hardware error check and correction
 *
 *   @b Modifies
 *   @n Nand ECC registers
 *
 *   @b Example
 *   @verbatim
            CSL_Status          status;
            CSL_EmifHandle      hEmif;
            CSL_EmifChipSelect  csInput;

            csInput = CSL_NAND_CE0;

            status = NAND_enableHwECC(hEmif, csInput);
            ...
            ...
            status = NAND_disableHwECC(hEmif, csInput);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_disableHwECC(CSL_EmifHandle        hEmif,
                             CSL_EmifChipSelect    csInput);

/** ============================================================================
 *   @n@b NAND_readECC
 *
 *   @b Description
 *   @n This API is used to read the information generated by ECC hardware.
 *      Hardware ECC must be enabled before calling this API.
 *
 *   @b Arguments
 *   @verbatim
            hEmif        Handle to the emif object
            eccBuffer    ECC Buffer pointer
            csInput      Chip select used for calculating Ecc
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand read is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  NAND_enableHwECC API should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Populates ECC data into eccBuffer
 *
 *   @b Modifies
 *   @n eccBuffer
 *
 *   @b Example
 *   @verbatim
            CSL_Status           status;
            CSL_EmifHandle       hEmif;
            Uint16               eccBuffer[8];
            CSL_EmifChipSelect   csInput;

            csInput = CSL_NAND_CE0;

            status = NAND_enableHwECC(hEmif, csInput);
            ...
            ...
            status = NAND_readECC(hEmif, eccBuffer, csInput);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_readECC(CSL_EmifHandle        hEmif,
                        Uint16                *eccBuffer,
                        CSL_EmifChipSelect    csInput);

/** ============================================================================
 *   @n@b NAND_readNBytes
 *
 *   @b Description
 *   @n This API reads N number of bytes from a nand physical page.
 *      Number of bytes to be read is sent as an argument to this API.
 *      A read command should be sent and nand page address should be set
 *      before calling this API.
 *
 *   @b Arguments
 *   @verbatim
            hEmif          Handle to the emif object
            readRequest    Number of bytes to read
            pReadBuffer    Read buffer pointer
            pack           Data pack flag
            spare          Spare area flag
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand read is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  NAND_sendCommand and NAND_setAddress APIs should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Reads the data from nand
 *
 *   @b Modifies
 *   @n Copies data from nand to read buffer
 *
 *   @b Example
 *   @verbatim
            #define  NAND_BUF_SIZE      (1024)

			CSL_Status     status;
			CSL_EmifHandle hEmif;
			Uint32         address;
			Uint16         nandReadBuf[NAND_BUF_SIZE];

			address = 0x40;
            status = NAND_sendCommand(hEmif,CSL_NAND_CMD_READ_START);

            // Set column address
			status = NAND_setAddress(hEmif,0x00);
	        status = NAND_setAddress(hEmif,0x00);
            // Set row address
			status = NAND_setAddress(hEmif,0x40);
			status = NAND_setAddress(hEmif,0x00);
			status = NAND_setAddress(hEmif,0x00);
            ....
            ....
            status = NAND_readNBytes(hEmif,NAND_BUF_SIZE,nandreadBuf,0,0);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_readNBytes(CSL_EmifHandle    hEmif,
                           Uint16            readRequest,
                           Uint16            *pReadBuffer,
                           Uint16            pack,
                           Bool				 spare);

/** ============================================================================
 *   @n@b NAND_writeNBytes
 *
 *   @b Description
 *   @n This API writes N number of bytes to a nand physical page.
 *      Number of bytes to be written is sent as an argument to this API.
 *      A page program command should be sent and nand page address
 *      should be set before calling this API. nand device should not be
 *      write-protected for proper functioning of this API.
 *
 *   @b Arguments
 *   @verbatim
            hEmif          Handle to the emif object
            writeRequest   Number of bytes to write
            pWriteBuffer   Write buffer pointer
            val            If a value needs to be wriiten directly without
                           using write buffer
            spare          Spare area flag
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Nand write is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *
 *   <b> Pre Condition </b>
 *   @n  NAND_sendCommand and NAND_setAddress APIs should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Writes the data to nand
 *
 *   @b Modifies
 *   @n Nand write registers
 *
 *   @b Example
 *   @verbatim
            #define  NAND_BUF_SIZE      (1024)

			CSL_Status     status;
			CSL_EmifHandle hEmif;
			Uint32         address;
			Uint16         nandWriteBuf[NAND_BUF_SIZE];

			address = 0x40;
            status = NAND_sendCommand(hEmif,CSL_NAND_CMD_READ_START);
            // Set column address
			status = NAND_setAddress(hEmif,0x00);
	        status = NAND_setAddress(hEmif,0x00);

            // Set row address
			status = NAND_setAddress(hEmif,0x40);
			status = NAND_setAddress(hEmif,0x00);
			status = NAND_setAddress(hEmif,0x00);
            ....
            ....
            status = NAND_writeNBytes(hEmif,NAND_BUF_SIZE,nandWriteBuf,0,0);
     @endverbatim
 *  ============================================================================
 */
CSL_Status NAND_writeNBytes(CSL_EmifHandle     hEmif,
                            Uint16             writeRequest,
                            Uint16             *pWriteBuffer,
                            Uint16             val,
                            Bool			   spare);

/** ============================================================================
 *   @n@b NAND_hasRandomRead
 *
 *   @b Description
 *   @n This API is used to check whether a nand device is having random
 *      page read or not. If nand is having random read we can set pointer
 *      to any address in the page and retrieve the data from there.
 *
 *   @b Arguments
 *   @verbatim
            nandOptions    Extra commands for big block nand
            RRstatus       Random read status pointer
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   @n
 *
 *   <b> Pre Condition </b>
 *   @n  nandOptions information needs to be computed from nand device Id
 *
 *   <b> Post Condition </b>
 *   @n  Random read status is returned in status variable
 *   @li                TRUE     - NAND device is having random read
 *   @li                FALSE    - NAND device is not having random read
 *
 *   @b Modifies
 *   @n Random read status variable
 *
 *   @b Example
 *   @verbatim
             Uint32    nandOptions;
             Uint16    RRstatus;

             //get the nandOptions information from nand device Id
             NAND_hasRandomRead(nandOptions, &RRstatus);
     @endverbatim
 *  ============================================================================
 */
void NAND_hasRandomRead(Uint32    nandOptions,
                        Uint16    *RRstatus);

/** ============================================================================
 *   @n@b NAND_hasRandomWrite
 *
 *   @b Description
 *   @n This API is used to check whether a nand device is having random
 *      page write or not. If nand is having random write we can set pointer
 *      to any address in the page and write the data from there.
 *
 *   @b Arguments
 *   @verbatim
            nandOptions    Extra commands for big block nand
            RWstatus       Random write status pointer
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   @n
 *
 *   <b> Pre Condition </b>
 *   @n  nandOptions information needs to be computed from nand device Id
 *
 *   <b> Post Condition </b>
 *   @n  Random write status is returned in status variable
 *   @li                TRUE     - NAND device is having random write
 *   @li                FALSE    - NAND device is not having random write
 *
 *   @b Modifies
 *   @n Random write status variable
 *
 *   @b Example
 *   @verbatim
             Uint32    nandOptions;
             Uint16    RWstatus;

             //get the nandOptions information from nand device Id
             NAND_hasRandomWrite(nandOptions, &RWstatus);
     @endverbatim
 *  ============================================================================
 */
void NAND_hasRandomWrite(Uint32    nandOptions,
                         Uint16    *RWstatus);

/** ============================================================================
 *   @n@b NAND_hasCacheProg
 *
 *   @b Description
 *   @n This API checks whether a nand device supports cache programming
 *      feature or not.
 *
 *   @b Arguments
 *   @verbatim
            nandOptions    Extra commands for big block nand
            CPstatus       Cache program status pointer
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   @n
 *
 *   <b> Pre Condition </b>
 *   @n  nandOptions information needs to be computed from nand device Id
 *
 *   <b> Post Condition </b>
 *   @n  Cache program status is returned in status variable
 *   @li                TRUE     - NAND device is having cache programming
 *   @li                FALSE    - NAND device is not having cache programming
 *
 *   @b Modifies
 *   @n Cache program status variable
 *
 *   @b Example
 *   @verbatim
             Uint32    nandOptions;
             Uint16    CPstatus;

             //get the nandOptions information from nand device Id
             NAND_hasCacheProg(nandOptions, &CPstatus);
     @endverbatim
 *  ============================================================================
 */
void NAND_hasCacheProg(Uint32    nandOptions,
                       Uint16    *CPstatus);

/** ============================================================================
 *   @n@b NAND_hasCopyBack
 *
 *   @b Description
 *   @n This API checks whether a nand device supports copy back
 *      feature or not.
 *
 *   @b Arguments
 *   @verbatim
            nandOptions    Extra commands for big block nand
            CBstatus       Copy back status pointer
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   @n
 *
 *   <b> Pre Condition </b>
 *   @n  nandOptions information needs to be computed from nand device Id
 *
 *   <b> Post Condition </b>
 *   @n  Copy back status is returned in status variable
 *   @li                TRUE     - NAND device support copy back feature
 *   @li                FALSE    - NAND device does not support copy back feature
 *
 *   @b Modifies
 *   @n Copy back status variable
 *
 *   @b Example
 *   @verbatim
            Uint32    nandOptions;
            Uint16    CBstatus;

            //get the nandOptions information from nand device Id
            NAND_hasCopyBack(nandOptions, &CBstatus);
     @endverbatim
 *  ============================================================================
 */
void NAND_hasCopyBack(Uint32    nandOptions,
                      Uint16    *CBstatus);

/** ============================================================================
 *   @n@b EMIF_intrEnable
 *
 *   @b Description
 *   @n This API enables emif interrupts. This API is used in interrupt
 *      mode of operation of the device.
 *
 *   @b Arguments
 *   @verbatim
            hEmif        Handle to the emif object
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Emif interrupt enable is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_init should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Enables emif interrupts
 *
 *   @b Modifies
 *   @n Emif interrupt registers
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
			CSL_Status     status;
			CSL_EmifHandle hEmif;

			status = EMIF_init(&emifObj);
			hEmif  = &emifObj;
			....
			....
            status = EMIF_intrEnable(hEmif);
     @endverbatim
 *  ============================================================================
 */
CSL_Status EMIF_intrEnable(CSL_EmifHandle    hEmif);

/** ============================================================================
 *   @n@b EMIF_intrDisable
 *
 *   @b Description
 *   @n This API is used to disable emif interrupts.
 *
 *   @b Arguments
 *   @verbatim
            hEmif        Handle to the emif object
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - emif interrupt disable is successful
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_intrEnable should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Disables emif interrupts
 *
 *   @b Modifies
 *   @n Emif interrupt registers
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
			CSL_Status     status;
			CSL_EmifHandle hEmif;

			status = EMIF_init(&emifObj);
			hEmif  = &emifObj;
			....
			....
            status = EMIF_intrEnable(hEmif);
            ...
            ...
            status = EMIF_intrDisable(hEmif);
     @endverbatim
 *  ============================================================================
 */
CSL_Status EMIF_intrDisable(CSL_EmifHandle    hEmif);

/** ============================================================================
 *   @n@b EMIF_intrReadAT
 *
 *   @b Description
 *   @n Reads Asynchronous time-out bit of emif interrupt raw register
 *
 *   @b Arguments
 *   @verbatim
            hEmif        Handle to the emif object
            ATstatus     Asynchronous time-out status variable
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_intrEnable should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Emif asynchronous time-out bit status is returned in status variable
 *
 *   @b Modifies
 *   @n Asynchronous time-out status variable
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
 			CSL_Status     status;
 			CSL_EmifHandle hEmif;
 			Uint16         ATstatus;

 			status = EMIF_init(&emifObj);
 			hEmif  = &emifObj;
 			....
 			....
            status = EMIF_intrEnable(hEmif);
            ...
            ...
            status = EMIF_intrReadAT(hEmif,&ATstatus);
     @endverbatim
 *  ============================================================================
 */
CSL_Status EMIF_intrReadAT(CSL_EmifHandle    hEmif,
                           Uint16            *ATstatus);

/** ============================================================================
 *   @n@b EMIF_intrReadLT
 *
 *   @b Description
 *   @n Reads Line-trap bit of emif interrupt raw register
 *
 *   @b Arguments
 *   @verbatim
            hEmif        Handle to the emif object
            LTstatus     Line trap status variable
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_intrEnable should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Emif line trap bit status is returned in status variable
 *
 *   @b Modifies
 *   @n Line trap status variable
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
 			CSL_Status     status;
 			CSL_EmifHandle hEmif;
 			Uint16         LTstatus;

 			status = EMIF_init(&emifObj);
 			hEmif  = &emifObj;
 			....
 			....
            status = EMIF_intrEnable(hEmif);
            ...
            ...
            status = EMIF_intrReadLT(hEmif,&LTstatus);
     @endverbatim
 *  ============================================================================
 */
CSL_Status EMIF_intrReadLT(CSL_EmifHandle    hEmif,
                           Uint16            *LTstatus);

/** ============================================================================
 *   @n@b EMIF_intrReadWR
 *
 *   @b Description
 *   @n Reads wait-rise bit of emif interrupt raw register
 *
 *   @b Arguments
 *   @verbatim
            hEmif        Handle to the emif object
            WRstatus     Wait-raise status variable
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_intrEnable should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Emif wait-rise bit status is returned in status variable
 *
 *   @b Modifies
 *   @n Wait-rise status variable
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj    emifObj;
 			CSL_Status     status;
 			CSL_EmifHandle hEmif;
 			Uint16         WRstatus;

 			status = EMIF_init(&emifObj);
 			hEmif  = &emifObj;
 			....
 			....
            status = EMIF_intrEnable(hEmif);
            ...
            ...
            status = EMIF_intrReadWR(hEmif,&WRstatus);
     @endverbatim
 *  ============================================================================
 */
CSL_Status EMIF_intrReadWR(CSL_EmifHandle    hEmif,
                           Uint16            *WRstatus);

/** ============================================================================
 *   @n@b EMIF_intrClear
 *
 *   @b Description
 *   @n Clears a emif interrupt
 *
 *   @b Arguments
 *   @verbatim
            hEmif        Handle to the emif object
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  EMIF_intrEnable should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Clears emif interrupt
 *
 *   @b Modifies
 *   @n Emif interrupt mask register
 *
 *   @b Example
 *   @verbatim
            CSL_EmifObj    emifObj;
            CSL_Status     status;
            CSL_EmifHandle hEmif;
            Uint16         WRstatus;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ....
            ....
            status = EMIF_intrEnable(hEmif);
            ...
            ...
            status = EMIF_intrClear(hEmif);
     @endverbatim
 *  ============================================================================
 */
CSL_Status EMIF_intrClear(CSL_EmifHandle    hEmif);

/** NAND query function                                                      */
/** ============================================================================
 *   @n@b NAND_getSetup
 *
 *   @b Description
 *   @n This API returns configuration of the nand hardware registers.
 *
 *   @b Arguments
 *   @verbatim
            hEmif            Handle to the emif object
			getAsynchConfig  Asynchronous configuration structure
            getNandConfig    Nand configuration structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_INVPARAMS - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  NAND_setup should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Returns the nand configuration
 *
 *   @b Modifies
 *   @n nand get config structure
 *
 *   @b Example
 *   @verbatim
            CSL_emifObj            emifObj;
            CSL_Status             status;
            CSL_NandConfig         nandCfg;
            CSL_NandConfig         getNandConfig;
            CSL_EmifHandle         hEmif;
            CSL_NandAsyncWaitCfg   asyncWaitConfig;
            CSL_NandAsyncCfg       asyncConfig;
            CSL_NandAsyncWaitCfg   getAsyncWaitConfig;
            CSL_NandAsyncCfg       getAsyncConfig;

            status = EMIF_init(&emifObj);
            hEmif  = &emifObj;
            ...
            nandCfg.nandWidth = CSL_EMIF_8_BIT;
            ...
            ...
            nandCfg.asyncWaitCfg = &asyncWaitConfig;
            nandCfg.asyncCfg     = &asyncConfig;
            status = NAND_setup(hEmif, &nandCfg);
            nandGetCfg.asyncWaitCfg = &getAsyncWaitConfig;
            nandGetCfg.asyncCfg     = &getAsyncConfig;
            status = NAND_getSetup(hEmif, &nandGetCfg);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status NAND_getSetup(CSL_EmifHandle      hEmif,
                         CSL_AsyncConfig     *getAsynchConfig,
                         CSL_NandConfig      *getNandConfig)
{
	volatile ioport Uint16    *asyncCfg0Addr;
    volatile ioport Uint16    *asyncCfg1Addr;
    Int16         loopCount;
	Uint16        tempVal;
	CSL_Status    result;

	result = CSL_SOK;

	if((hEmif != NULL) && (getAsynchConfig != NULL))
	{
		getNandConfig->nandWidth    = hEmif->nandWidth;
		getNandConfig->nandPageSize = hEmif->nandPageSize;
		getNandConfig->emifOpMode   = hEmif->emifOpMode;
		getNandConfig->nandType     = hEmif->nandType;

		/* Get the chip select */
		tempVal = CSL_FEXTR(hEmif->regs->NANDFCR,
		                    CSL_EMIF_NANDFCR_CS5_USE_NAND_SHIFT,
		                    CSL_EMIF_NANDFCR_CS2_USE_NAND_SHIFT);

		loopCount = -1;
		while(tempVal)
		{
			loopCount++;
			tempVal = (tempVal >> 1);
		}

		getAsynchConfig->chipSelect =  (CSL_EmifChipSelect)loopCount;

		/* Get async wait config register setting */
		switch(getAsynchConfig->chipSelect)
		{
			case CSL_EMIF_CS2:
				/* CS2 */
//				getAsynchConfig->asyncWaitCfg->waitPin =                            \
//	                        (CSL_EmifWaitPin)CSL_FEXT(hEmif->regs->AWCCR2,            \
//				                                   EMIF_AWCCR2_CS2_WAIT);

				asyncCfg0Addr = &(hEmif->regs->ACS2CR1);
				asyncCfg1Addr = &(hEmif->regs->ACS2CR2);
				break;

			case CSL_EMIF_CS3:
				/* CS3 */
//				getAsynchConfig->asyncWaitCfg->waitPin =                            \
//	                        (CSL_EmifWaitPin)CSL_FEXT(hEmif->regs->AWCCR2,            \
//				                                   EMIF_AWCCR2_CS3_WAIT);

				asyncCfg0Addr = &(hEmif->regs->ACS3CR1);
				asyncCfg1Addr = &(hEmif->regs->ACS3CR2);
				break;

			case CSL_EMIF_CS4:
				/* CS4 */
//				getAsynchConfig->asyncWaitCfg->waitPin =                            \
//	                        (CSL_EmifWaitPin)CSL_FEXT(hEmif->regs->AWCCR2,            \
//				                                   EMIF_AWCCR2_CS4_WAIT);

				asyncCfg0Addr = &(hEmif->regs->ACS4CR1);
				asyncCfg1Addr = &(hEmif->regs->ACS4CR2);
				break;

			case CSL_EMIF_CS5:
				/* CS5 */
//				getAsynchConfig->asyncWaitCfg->waitPin =                            \
//	                        (CSL_EmifWaitPin)CSL_FEXT(hEmif->regs->AWCCR2,            \
//				                                   EMIF_AWCCR2_CS5_WAIT);

				asyncCfg0Addr = &(hEmif->regs->ACS5CR1);
				asyncCfg1Addr = &(hEmif->regs->ACS5CR2);
				break;

			default:
				break;
		}

		/* Get the wait polarity */
//		getAsynchConfig->asyncWaitCfg->waitPol =                                     \
//                      (CSL_EmifWaitPol)CSL_FEXT(hEmif->regs->AWCCR2,               \
		                                        EMIF_AWCCR2_WP0);

		/* Get the extended wait cycles */
//		getAsynchConfig->asyncWaitCfg->waitCycles = CSL_FEXT(hEmif->regs->AWCCR1,    \
//		                                      			   EMIF_AWCCR1_MEWC);


		/* Get async configuration register values */
		/* Get strobe mode select bit */
		getAsynchConfig->asyncCfg->selectStrobe = CSL_FEXT(*asyncCfg1Addr,           \
                                                         EMIF_ACS2CR2_SS);
		/* Get extended wait mode bit */
		getAsynchConfig->asyncCfg->ewMode = CSL_FEXT(*asyncCfg1Addr,                 \
                                                   EMIF_ACS2CR2_EW);
		/* Get write srobe setup cycles */
		getAsynchConfig->asyncCfg->w_setup = CSL_FEXT(*asyncCfg1Addr,                \
                                                    EMIF_ACS2CR2_WSETUP);
		/* Get write duration cycles */
		getAsynchConfig->asyncCfg->w_strobe = CSL_FEXT(*asyncCfg1Addr,               \
                                                     EMIF_ACS2CR2_WSTROBE);
		/* Get write hold cycles */
		getAsynchConfig->asyncCfg->w_hold = CSL_FEXT(*asyncCfg1Addr,                 \
                                                   EMIF_ACS2CR2_WHOLD);
		/* Get read strobe setup cycles */
		getAsynchConfig->asyncCfg->r_setup = ((CSL_FEXT(*asyncCfg1Addr,              \
                                            EMIF_ACS2CR2_RSETUPMSB) << 3) |        \
                                            (CSL_FEXT(*asyncCfg0Addr,              \
                                            EMIF_ACS2CR1_RSETUPLSB) & 0x7));
		/* Get read strobe duration cycles */
		getAsynchConfig->asyncCfg->r_strobe = CSL_FEXT(*asyncCfg0Addr,               \
                                                     EMIF_ACS2CR1_RSTROBE);
		/* Get read strobe hold cycles */
		getAsynchConfig->asyncCfg->r_hold = CSL_FEXT(*asyncCfg0Addr,                 \
                                                   EMIF_ACS2CR1_RHOLD);
		/* Get turn around cycles */
		getAsynchConfig->asyncCfg->turnAround = CSL_FEXT(*asyncCfg0Addr,             \
                                                       EMIF_ACS2CR1_TA);
		/* Get asynchronous memory size */
		getAsynchConfig->asyncCfg->aSize = CSL_FEXT(*asyncCfg0Addr,                  \
                                                  EMIF_ACS2CR1_ASIZE);

		/* emif Byte access */
		getAsynchConfig->emifAccess =                                                \
		          (CSL_EmifAccess)CSL_FEXT(hEmif->sysCtrlRegs->ESCR,           \
		                                       SYS_ESCR_BYTEMODE);
	}
	else
	{
		result = CSL_ESYS_INVPARAMS;
	}

	return(result);
}

/**
@} */



#ifdef __cplusplus
}
#endif

#endif    // _CSL_NAND_H_

