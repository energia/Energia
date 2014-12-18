//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// *
// *  Redistribution and use in source and binary forms, with or without
// *  modification, are permitted provided that the following conditions
// *  are met:
// *
// *    Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// *
// *    Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the
// *    distribution.
// *
// *    Neither the name of Texas Instruments Incorporated nor the names of
// *    its contributors may be used to endorse or promote products derived
// *    from this software without specific prior written permission.
// *
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
//////////////////////////////////////////////////////////////////////////////
/** @file boot_update.h
 *
 *  @brief This file contains the function prototypes and macro defenitions  
 *  of thebootloader update utility.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csl_mmcsd.h"
#include "csl_mmcsd_ataIf.h"
#include "csl_uart.h"
#include "csl_uartAux.h"
#include "ata.h"
#include "csl_pll.h"
#include "csl_i2c.h"
#include "board_mode.h"

#ifdef __cplusplus
extern "C" {
#endif

/** I2C address */
#define CSL_I2C_OWN_ADDR		(0x2F)
/** I2C clock */
#define CSL_I2C_SYS_CLK			(150)
/** I2C bus frequency */
#define CSL_I2C_BUS_FREQ		(100)
/** IO expander address */
#define CSL_I2C_TCA6416_ADDR	(0x20)

/** Macro to enable/disable printf statements */
//#define ENABLE_PRINTF

#ifdef ENABLE_PRINTF
#define PRINT_MSG(x) printf x /**< This definition will print the messages */
#else
#define PRINT_MSG(x) /**< This definition will avoid printing any messages */
#endif

/** Macro to indicate the Disk type to ATAFS */
#define CSL_MMCSD_ATAFS_DISKTYPE   (0)

/** Macro to denote the Command length in terms of bytes */
#define COMMAND_SIZE_LENGTH (2)

/** Macro to hold the value of the Command, will be used to update the
    BootLoader */
#define COMMAND_TO_UPDATE_BOOTLOADER (29)

/** The size of buffer used while transfering the BOOTLOADER */
#define UART_BUFFER_SIZE (512)

/** Macro to hold the Temporary BootLoader Filename */
#define TEMP_BOOTLOADER_FILENAME "TEMPIMG"

/** Macro to hold the BootLoader Filename */
#define BOOTLOADER_FILENAME "BOOTIMG"

/** Macro to hold the BOOTLOADER File extension */
#define BOOTLOADER_EXTENSION "BIN"

/** SD card clock divider value to divide system clock */
#define MMCSD_CLOCK_DIV       (5u)

/**
 * \brief Function to read the new Bootloader through UART and write it on the
 * Storage Media Card
 *
 * This function reads the command, checks whether the received command is to
 * update the Bootloader or not. Depending on the command it receives the
 * Bootloader contents from the UART in chunks, and finally writes it to the
 * SD Card
 *
 * @return Error Status
 */
Uint16 updateBootLoader(void);

#ifdef __cplusplus
}
#endif
