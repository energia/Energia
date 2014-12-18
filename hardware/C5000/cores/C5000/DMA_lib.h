//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
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
/** @file DMA_lib.h
 *
 *  @brief DMA library header file
 *
 */
 
#ifndef _DMA_LIB_H_
#define _DMA_LIB_H_

#include "core.h"

/** Maximum number of channels */
#define DMA_CHANNEL_MAX         (16)

/* Macros to configure DMA HW events. Use these macros to set
   event field(dmaEvent) in DMA configuration structure (DMAConfig) */
/** No DMA event(SW trig./mem to mem)     */
#define DMA_EVENT_NONE            (0)
/** Tx of I2S0 data event triggers DMA    */
#define DMA_EVENT_I2S0_TX         (1)
/** Rx of I2S0 data event triggers DMA    */
#define DMA_EVENT_I2S0_RX         (2)
/** Tx of I2S1 data event triggers DMA    */
#define DMA_EVENT_I2S1_TX         (1)
/** Rx of I2S1 data event triggers DMA    */
#define DMA_EVENT_I2S1_RX         (2)
/** Tx of I2S2 data event triggers DMA    */
#define DMA_EVENT_I2S2_TX         (1)
/** Rx of I2S2 data event triggers DMA    */
#define DMA_EVENT_I2S2_RX         (2)
/** Tx of I2S3 data event triggers DMA    */
#define DMA_EVENT_I2S3_TX         (4)
/** Rx of I2S3 data event triggers DMA    */
#define DMA_EVENT_I2S3_RX         (5)
/** MCPSP TX event triggers DMA           */
#define DMA_EVENT_MCBSP_TX        (1)
/** MCPSP RX event triggers DMA           */
#define DMA_EVENT_MCBSP_RX        (2)
/** MCPSP TXA event triggers DMA          */
#define DMA_EVENT_MCBSP_TXA       (3)
/** MCPSP RXA event triggers DMA          */
#define DMA_EVENT_MCBSP_RXA       (4)
/** MMC/SD0 TX event triggers DMA         */
#define DMA_EVENT_MMC_SD0_TX      (5)
/** MMC/SD0 RX event triggers DMA         */
#define DMA_EVENT_MMC_SD0_RX      (6)
/** MMC/SD1 TX event triggers DMA         */
#define DMA_EVENT_MMC_SD1_TX      (7)
/** MMC/SD1 RX event triggers DMA         */
#define DMA_EVENT_MMC_SD1_RX      (8)
/** timer0 event triggers DMA             */
#define DMA_EVENT_TIMER0          (12)
/** timer1 event triggers DMA             */
#define DMA_EVENT_TIMER1          (13)
/** timer2 event triggers DMA             */
#define DMA_EVENT_TIMER2          (14)
/** Tx of UART data event triggers DMA    */
#define DMA_EVENT_UART_TX         (5)
/** Rx of UART data event triggers DMA    */
#define DMA_EVENT_UART_RX         (6)
/** Tx of I2C data event triggers DMA     */
#define DMA_EVENT_I2C_TX          (1)
/** Rx  of I2C data event triggers DMA    */
#define DMA_EVENT_I2C_RX          (2)
/** SAR A/D event triggers DMA            */
#define DMA_EVENT_SAR_AD          (3)
/**MCSPI CH0_RX triggers DMA              */
#define DMA_EVENT_MCSPI_CH0_RX    (3)
/**MCSPI CH0_TX triggers DMA              */
#define DMA_EVENT_MCSPI_CH0_TX    (4)
/**MCSPI CH1_RX triggers DMA              */
#define DMA_EVENT_MCSPI_CH1_RX    (9)
/**MCSPI CH1_TX triggers DMA              */
#define DMA_EVENT_MCSPI_CH1_TX    (10)
/**MCSPI CH2_RX triggers DMA              */
#define DMA_EVENT_MCSPI_CH2_RX    (11)
/**MCSPI CH2_TX triggers DMA              */
#define DMA_EVENT_MCSPI_CH2_TX    (15)

/* Macros to configure DMA burst length. Use these macros to set
   burst length field(burstLen) in DMA configuration structure (DMAConfig) */
/** One 32-bit transfer:1-word burst      */
#define DMA_BURST_1WORD    (0)
/** Two 32-bit transfer:2-word burst      */
#define DMA_BURST_2WORD    (1)
/** Four 32-bit transfer:4-word burst     */
#define DMA_BURST_4WORD    (2)
/** Eight 32-bit transfer:8-word burst    */
#define DMA_BURST_8WORD    (3)
/** Sixteen 32-bit transfer:16-word burst */
#define DMA_BURST_16WORD   (4)

/* Macros to configure DMA channel direction. Use these macros to set channel
   direction field(chanDir) in DMA configuration structure (DMAConfig) */
/** Reading data from an IO device        */
#define DMA_CHANNEL_DIRECTION_READ     (0)
/** Writing data to an IO device          */
#define DMA_CHANNEL_DIRECTION_WRITE    (1)

/**
 * \brief DMA configuration structure.
 *
 * Contains configuration parameters for DMA library.
 */
typedef struct
{
	/** Ping-Pong Mode configuration
	    0 - DMA Ping-Pong mode will be disabled
	    1 - DMA Ping-Pong mode will be enabled                              */
    bool           enablePingPong;
	/** Auto reload Mode configuration
	    0 - DMA auto reload mode will be disabled
	    1 - DMA auto reload mode will be enabled                            */
    bool           enableAutoReload;
	/** DMA interrupt configuration
	    0 - DMA transfer completion interrupt will be disabled
	    1 - DMA transfer completion interrupt will be enabled               */
    bool           enableDmaInt;
    /** Type of the DMA event
        Use the macros DMA_EVENT_XXX to select the DMA event type based
        on the modules involved in DMA transfer
        Note: Set DMA event to 'DMA_EVENT_NONE' if DMA transfer is done
        between two buffers in the internal memory or SDRAM                 */
    unsigned short dmaEvent;
    /** DMA burst length for each event trigger
        Use the macros DMA_BURST_XXX to select the DMA burst length based
        on the IO device involved in DMA transfer
        Note: Any burst length can be used if DMA transfer is done between
        two buffers in the internal memory or SDRAM                         */
    unsigned short burstLen;
    /** DMA channel direction
        Use DMA_CHANNEL_DIRECTION_READ if DMA is used to transfer data
        from an IO device to a buffer in internal memory.
        Use DMA_CHANNEL_DIRECTION_WRITE if DMA is used to transfer data
        from a buffer in internal memory to an IO device.
        Note: Channel direction can be set to DMA_CHANNEL_DIRECTION_READ or
        DMA_CHANNEL_DIRECTION_WRITE if DMA transfer is done between two
        buffers in the internal memory or SDRAM                             */
    unsigned short chanDir;
    /** Length of data to transfer in number of bytes                       */
    unsigned short dataLen;
    /** Address of source data buffer                                      */
    unsigned short *srcAddr;
    /** Address of destination data buffer                                 */
    unsigned short *destAddr;
} DMAConfig;

/**
 * \brief DMA class.
 *
 * Contains the variables and functions used by DMA library.
 */
class DMAClass {
	private:
	unsigned short isIfrValueValid;
	unsigned short ifrValueRead;

    public:
	    int init();
        int dmaInit(DMAConfig *dmaConfig, unsigned short bufferLength);
        void dmaDeInit(DMAConfig *dmaConfig);
        int openChannel(unsigned int chanNumber);
        int configChannel(unsigned int chanNumber, DMAConfig dmaConfigure);
        int start(unsigned int chanNumber);
		int getStatus(unsigned int chanNumber);
        int stop(unsigned int chanNumber);
        int closeChannel(unsigned int chanNumber);
        unsigned int getInterruptStatus(void);
        void clearInterruptStatus(unsigned int ifrValue);
        unsigned int readInterruptStatus(void);
        void resetInterruptStatus(void);
};

extern DMAClass DMA;
/**< DMA class instance extern which can used by application programs
 *   to access DMA DSP APIs
 */
#endif   /* _DMA_LIB_H_ */
