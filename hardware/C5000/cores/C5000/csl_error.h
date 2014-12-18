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

/** @file csl_error.h
 *
 *  @brief CSL commonn error definition file
 *
 *  Path: /(CSLPATH)/inc
 */

#ifndef _CSL_ERROR_H_
#define _CSL_ERROR_H_

/* Below Error codes are Global across all CSL Modules */
#define CSL_SOK                    (0)    /**< Success                        */
#define CSL_ESYS_FAIL              (-1)   /**< Generic failure                */
#define CSL_ESYS_INUSE             (-2)   /**< Peripheral resource is already in
                                               use                            */
#define CSL_ESYS_XIO               (-3)   /**< Encountered a shared I/O(XIO) pin
                                               conflict                       */
#define CSL_ESYS_OVFL              (-4)   /**< Encoutered CSL system resource
                                              overflow                        */
#define CSL_ESYS_BADHANDLE         (-5)   /**< Handle passed to CSL was
                                               invalid                        */
#define CSL_ESYS_INVPARAMS         (-6)   /**< Invalid parameters             */
#define CSL_ESYS_INVCMD            (-7)   /**< Invalid command                */
#define CSL_ESYS_INVQUERY          (-8)   /**< Invalid query                  */
#define CSL_ESYS_NOTSUPPORTED      (-9)   /**< Action not supported           */
#define CSL_EMMCSD_TIMEOUT         (-10)  /**< Response not came in the definite
                                              time                           */
#define CSL_ESYS_BADMEDIA          (-11)  /**< Bad Media - used for USB-MSC   */
#define CSL_ESYS_MEDIA_NOTPRESENT  (-12)  /**< Media Not Present - used for
                                              USB-MSC                        */
#define CSL_EMMCSD_READ_ERROR      (-13)  /**< CSL MMC/SD Error during Read   */
#define CSL_EMMCSD_WRITE_ERROR     (-14)  /**< CSL MMC/SD Error during Write  */
#define CSL_EMMCSD_CRCERR          (-15)  /**< MMCSD command/data CRC error
                                              detected                       */
#define CSL_ESDIO_TIMEOUT          (-16)  /**< SDIO time out error            */
#define CSL_ESDIO_CRCERR           (-17)  /**< SDIO CRC error                 */


/* Peripheral IDs */
#define CSL_DAT_ID            (1)  /**< CSL DAT Module Instance ID            */
#define CSL_DMA_ID            (2)  /**< CSL DMA Module Instance ID            */
#define CSL_GPIO_ID           (3)  /**< CSL GPIO Module Instance ID           */
#define CSL_GPT_ID            (4)  /**< CSL GPT Module Instance ID            */
#define CSL_I2C_ID            (5)  /**< CSL I2C Module Instance ID            */
#define CSL_I2S_ID            (6)  /**< CSL I2S Module Instance ID            */
#define CSL_INTC_ID           (7)  /**< CSL INTC Module Instance ID           */
#define CSL_LCD_ID            (8)  /**< CSL LCD Module Instance ID            */
#define CSL_MMCSD_ID          (9)  /**< CSL MMC/SD Module Instance ID         */
#define CSL_NAND_ID           (10) /**< CSL NAND Module Instance ID           */
#define CSL_PLL_ID            (11) /**< CSL PLL Module Instance ID            */
#define CSL_PWR_ID            (12) /**< CSL PWR Module Instance ID            */
#define CSL_RTC_ID            (13) /**< CSL RTC Module Instance ID            */
#define CSL_SAR_ID            (14) /**< CSL SAR Module Instance ID            */
#define CSL_SPI_ID            (15) /**< CSL SPI Module Instance ID            */
#define CSL_UART_ID           (16) /**< CSL UART Module Instance ID           */
#define CSL_USB_ID            (17) /**< CSL USB Module Instance ID            */
#define CSL_WDTIM_ID          (18) /**< CSL WDTIM Module Instance ID          */

/* Error codes individual to various modules. */

/*----------Error codes for UART-------------*/
/** Instance id of UART is invalid                  */
#define CSL_EUART_INVALID_INST_ID (CSL_EUART_FIRST -1)
/** ISR mask is invalid                             */
#define CSL_EUART_INVALID_ISR_MASK (CSL_EUART_FIRST -2)
/** Timed out                                       */
#define CSL_EUART_TIMEOUT (CSL_UART_ID -3)
/** Invalid buffer size                             */
#define CSL_EUART_INVALID_BUFSIZE (CSL_UART_ID -3)
/** Invalid wordlength                              */
#define CSL_EUART_INVALID_WORDLENGTH (CSL_UART_ID -4)
/** Invalid  parity selection                       */
#define CSL_EUART_INVALID_PARITYSEL (CSL_UART_ID -5)


/* Error code for DMA, individual error would be assigned as
 * eg: #define CSL_E<Peripheral name>_<error code>  CSL_DMA_FIRST - 1
 */
#define CSL_EDAT_FIRST      -( ((CSL_DAT_ID + 1) << 5 ) + 1 )
/**< Error Code for DAT Module                                                */
#define CSL_EDAT_LAST       -( (CSL_DAT_ID + 1) << 6 )
/**< Error Code for DAT Module                                                */

#define CSL_EDMA_FIRST      -( ((CSL_DMA_ID + 1) << 5 ) + 1 )
/**< Error Code for DMA Module                                                */
#define CSL_EDMA_LAST       -( (CSL_DMA_ID + 1) << 6 )
/**< Error Code for DMA Module                                                */

#define CSL_EGPIO_FIRST     -( ((CSL_GPIO_ID + 1) << 5 ) + 1 )
/**< Error Code for GPIO Module                                               */
#define CSL_EGPIO_LAST      -( (CSL_GPIO_ID + 1) << 6 )
/**< Error Code for GPIO Module                                               */

#define CSL_EGPT_FIRST      -( ((CSL_GPT_ID + 1) << 5 ) + 1 )
/**< Error Code for GPT Module                                                */
#define CSL_EGPT_LAST       -( (CSL_GPT_ID + 1) << 6 )
/**< Error Code for GPT Module                                                */

#define CSL_EI2C_FIRST      -( ((CSL_I2C_ID + 1) << 5 ) + 1 )
/**< Error Code for I2C Module                                                */
#define CSL_EI2C_LAST       -( (CSL_I2C_ID + 1) << 6 )
/**< Error Code for I2C Module                                                */

#define CSL_EI2S_FIRST      -( ((CSL_I2S_ID + 1) << 5 ) + 1 )
/**< Error Code for I2S Module                                                */
#define CSL_EI2S_LAST       -( (CSL_I2S_ID + 1) << 6 )
/**< Error Code for I2S Module                                                */

#define CSL_EINTC_FIRST     -( ((CSL_INTC_ID + 1) << 5 ) + 1 )
/**< Error Code for INTC Module                                               */
#define CSL_EINTC_LAST      -( (CSL_INTC_ID + 1) << 6 )
/**< Error Code for INTC Module                                               */

#define CSL_ELCD_FIRST      -( ((CSL_LCD_ID + 1) << 5 ) + 1 )
/**< Error Code for LCD Module                                                */
#define CSL_ELCD_LAST       -( (CSL_LCD_ID + 1) << 6 )
/**< Error Code for LCD Module                                                */

#define CSL_EMMCSD_FIRST    -( ((CSL_MMCSD_ID + 1) << 5 ) + 1 )
/**< Error Code for MMC/SD Module                                             */
#define CSL_EMMCSD_LAST     -( (CSL_MMCSD_ID + 1) << 6 )
/**< Error Code for MMC/SD Module                                             */

#define CSL_ENAND_FIRST     -( ((CSL_NAND_ID + 1) << 5 ) + 1 )
/**< Error Code for NAND Module                                               */
#define CSL_ENAND_LAST      -( (CSL_NAND_ID + 1) << 6 )
/**< Error Code for NAND Module                                               */

#define CSL_EPLL_FIRST      -( ((CSL_PLL_ID + 1) << 5 ) + 1 )
/**< Error Code for PLL Module                                                */
#define CSL_EPLL_LAST       -( (CSL_PLL_ID + 1) << 6 )
/**< Error Code for PLL Module                                                */

#define CSL_EPWR_FIRST      -( ((CSL_PWR_ID + 1) << 5 ) + 1 )
/**< Error Code for PWR Module                                                */
#define CSL_EPWR_LAST       -( (CSL_PWR_ID + 1) << 6 )
/**< Error Code for PWR Module                                                */

#define CSL_ERTC_FIRST      -( ((CSL_RTC_ID + 1) << 5 ) + 1 )
/**< Error Code for RTC Module                                                */
#define CSL_ERTC_LAST       -( (CSL_RTC_ID + 1) << 6 )
/**< Error Code for RTC Module                                                */

#define CSL_ESAR_FIRST      -( ((CSL_SAR_ID + 1) << 5 ) + 1 )
/**< Error Code for SAR Module                                                */
#define CSL_ESAR_LAST       -( (CSL_SAR_ID + 1) << 6 )
/**< Error Code for SAR Module                                                */

#define CSL_ESPI_FIRST      -( ((CSL_SPI_ID + 1) << 5 ) + 1 )
/**< Error Code for DAT Module                                                */
#define CSL_ESPI_LAST       -( (CSL_SPI_ID + 1) << 6 )
/**< Error Code for DAT Module                                                */

#define CSL_EUART_FIRST     -( ((CSL_UART_ID + 1) << 5 ) + 1 )
/**< Error Code for UART Module                                               */
#define CSL_EUART_LAST      -( (CSL_UART_ID + 1) << 6 )
/**< Error Code for UART Module                                               */

#define CSL_EUSB_FIRST      -( ((CSL_USB_ID + 1) << 5 ) + 1 )
/**< Error Code for USB Module                                                */
#define CSL_EUSB_LAST       -( (CSL_USB_ID + 1) << 6 )
/**< Error Code for USB Module                                                */

#define CSL_EWDTIM_FIRST    -( ((CSL_WDTIM_ID + 1) << 5 ) + 1 )
/**< Error Code for Watch Dog Timer Module                                    */
#define CSL_EWDTIM_LAST     -( (CSL_WDTIM_ID + 1) << 6 )
/**< Error Code for Watch Dog Timer Module                                    */


#endif /* _CSL_ERROR_H_ */
