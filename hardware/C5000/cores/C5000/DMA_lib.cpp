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

/** @file DMA_lib.cpp
 *
 *  @brief DMA implementation
 *
 */
 
#include "DMA_lib.h"
#include <stdio.h>
#include <string.h>

/** DMA channel objects */
CSL_DMA_ChannelObj     dmaObj[CSL_DMA_CHAN_MAX];
/** DMA channel handle */
CSL_DMA_Handle         hDMA[CSL_DMA_CHAN_MAX];
/** DMA class object */
DMAClass DMA;

/**
 *
 *  init( )
 *
 *      Initialize the DMA Module. This should be the first API to be called
 *      before configuring or starting the DMA transfer.
 *
 */
int DMAClass::init()
{
    CSL_Status status;

    status = DMA_init();
    isIfrValueValid = 0;
    ifrValueRead = 0;

    return (status);
}

/**
 *
 *  dmaInit( )
 *
 *      Dynamically creates source and destination buffers for the application
 *      and initializes the DMA Config structure.
 *
 *      This API is used to set DMA config structure values, only for memory to
 *      memory DMA transfers.
 *
 *      This API will disable the ping pong mode, auto reload mode and dma
 *      events. It will set the burst length as 8 words and the buffer length
 *      as requested by the Application.
 *
 *      DMAConfig dmaConfig         <- DMA config structure that is to be
 *                                     initialized
 *      unsigned short bufferLength <- Source and destination buffer Length
 */
int DMAClass::dmaInit(DMAConfig      *dmaConfig,
                      unsigned short bufferLength)
{
    if ((NULL == dmaConfig) || (0 == bufferLength))
    {
        return (-1);
	}

    /* Create buffers for DMA transfer */
    dmaConfig->srcAddr  = (unsigned short *)createBuffer(2*bufferLength);
    dmaConfig->destAddr = (unsigned short *)createBuffer(2*bufferLength);

    if((NULL == dmaConfig->srcAddr) || (NULL == dmaConfig->destAddr))
    {
   	    return (-1);
    }
    else
    {
	    dmaConfig->enablePingPong   = 0;
	    dmaConfig->enableAutoReload = 0;
	    dmaConfig->enableDmaInt     = 0;
	    dmaConfig->dmaEvent         = DMA_EVENT_NONE;
	    dmaConfig->burstLen         = DMA_BURST_8WORD;
	    dmaConfig->chanDir          = DMA_CHANNEL_DIRECTION_READ;
	    dmaConfig->dataLen          = bufferLength * 2;

	    return (0);
	}
}

/**
 *
 *  dmaDeInit( )
 *
 *      De-allocates the source and destination buffers used by the application
 *      for DMA transfers
 *
 *      It gets the source and destination buffer addresses from the DMA config
 *      structure, that holds these addresses.
 *
 *      DMAConfig dmaConfig  <- DMA config structure that is to be
 *                              de-initialized
 */
void DMAClass::dmaDeInit(DMAConfig *dmaConfig)
{
    /* Delete the buffers */
    deleteBuffer((void *)dmaConfig->srcAddr);
    deleteBuffer((void *)dmaConfig->destAddr);
}

/**
 *
 *  openChannel( )
 *
 *      API to open a particular DMA channel.
 *
 *      unsigned int chanNumber <- DMA channel number (0 to 15)
 */
int DMAClass::openChannel(unsigned int chanNumber)
{
    CSL_Status     status;

    hDMA[chanNumber] = DMA_open((CSL_DMAChanNum)chanNumber,
                                 &dmaObj[chanNumber], &status);

    return (status);
}

/**
 *
 *  configChannel(dmaConfigure)
 *
 *      Configure the DMA parameters for the given channel.
 *
 *      This API should be called after obtaining a channel using openChannel()
 *      API
 *
 *      DMAConfig dmaConfigure  <- DMA configurations
 */
int DMAClass::configChannel(unsigned int chanNumber, DMAConfig dmaConfigure)
{
    CSL_Status         status;
    CSL_DMA_Config     dmaCfg;

	dmaCfg.pingPongMode = (CSL_DMAPingPongMode)dmaConfigure.enablePingPong;
	dmaCfg.autoMode     = (CSL_DMAAutoReloadMode)dmaConfigure.enableAutoReload;
	dmaCfg.burstLen     = (CSL_DMATxBurstLen)dmaConfigure.burstLen;
	dmaCfg.dmaEvt       = (CSL_DMAEvtType)dmaConfigure.dmaEvent;
	dmaCfg.dmaInt       = (CSL_DMAInterruptState)dmaConfigure.enableDmaInt;
	dmaCfg.chanDir      = (CSL_DMAChanDir)dmaConfigure.chanDir;
	dmaCfg.dataLen      = dmaConfigure.dataLen;
	dmaCfg.srcAddr      = (Uint32)dmaConfigure.srcAddr;
	dmaCfg.destAddr     = (Uint32)dmaConfigure.destAddr;

	if(dmaConfigure.dmaEvent == DMA_EVENT_NONE)
	{
		dmaCfg.trigger = CSL_DMA_SOFTWARE_TRIGGER;
		dmaCfg.trfType = CSL_DMA_TRANSFER_MEMORY;
	}
	else
	{
		dmaCfg.trigger = CSL_DMA_EVENT_TRIGGER;
		dmaCfg.trfType = CSL_DMA_TRANSFER_IO_MEMORY;
	}

    /* Set configuration */
    status = DMA_config(hDMA[chanNumber], &dmaCfg);

    return (status);
}

/**
 *
 *  getStatus()
 *
 *      Read DMA transfer status.
 *
 *      unsigned int chanNumber <- DMA channel number (0 to 15)
 */
int DMAClass::getStatus(unsigned int chanNumber)
{
    CSL_Status           status;

    /* Get DMA transfer status */
    status = DMA_getStatus(hDMA[chanNumber]);

    return (status);
}

/**
 *
 *  start()
 *
 *      Triggers DMA data transfer for a particular DMA channel
 *
 *      unsigned int chanNumber <- DMA channel number (0 to 15)
 */
int DMAClass::start(unsigned int chanNumber)
{
    CSL_Status           status;

    /* Start DMA transfer */
    status = DMA_start(hDMA[chanNumber]);

    return (status);
}

/**
 *
 *  stop()
 *
 *      Stops DMA data transfer for a particular channel
 *
 *      unsigned int chanNumber <- DMA channel number (0 to 15)
 */
int DMAClass::stop(unsigned int chanNumber)
{
    CSL_Status           status;

    /* Start DMA transfer */
    status = DMA_stop(hDMA[chanNumber]);

    return (status);
}

/**
 *
 *  closeChannel()
 *
 *      Closes an already opened DMA channel
 *
 *      unsigned int chanNumber <- DMA channel number (0 to 15)
 */
int DMAClass::closeChannel(unsigned int chanNumber)
{
    CSL_Status           status;

    /* Close the DMA handle */
    status = DMA_close(hDMA[chanNumber]);

    return (status);
}

/**
 *
 *  getInterruptStatus()
 *
 *      API to get the DMA Interrupt Flag register values.
 *  This API always reads the interrupt status value from DMA HW registers
 *
 */
unsigned int DMAClass::getInterruptStatus(void)
{
    unsigned int ifrValue;

    ifrValue = CSL_SYSCTRL_REGS->DMAIFR;
    ifrValueRead = ifrValue;
    isIfrValueValid = 1;

    return (ifrValue);
}

/**
 *
 *  clearInterruptStatus()
 *
 *    API to clear interrupt status in DMA HW registers. Pass interrupt status
 *  value read using getInterruptStatus() or readInterruptStatus() to this
 *  function
 *
 */
void DMAClass::clearInterruptStatus(unsigned int ifrValue)
{
    CSL_SYSCTRL_REGS->DMAIFR = ifrValue;
}


/**
 *
 *  readInterruptStatus()
 *
 *  This API returns the DMA interrupt status value stored by DMA library.
 *  If the stored value is not valid, interrupt status shall be read
 *  from the DMA hardware registers.
 *
 *  Note: Use the function resetInterruptStatus() to reset the interrupt
 *  status value stored by DMA library
 *
 */
unsigned int DMAClass::readInterruptStatus(void)
{
    unsigned int ifrValue;

    if(isIfrValueValid)
    {
		ifrValue = ifrValueRead;
	}
	else
	{
		ifrValue = getInterruptStatus();
	}

    return (ifrValue);
}

/**
 *
 *  resetInterruptStatus()
 *
 *      API to reset the interrupt status value stored by DMA library
 */
void DMAClass::resetInterruptStatus(void)
{
    isIfrValueValid = 0;
    ifrValueRead = 0;
}

