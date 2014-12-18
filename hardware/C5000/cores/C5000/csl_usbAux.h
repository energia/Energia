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

/** @file csl_usbAux.h
 *
 *  @brief USB MUSB functional layer Auxiliary header file
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 05-Sep-2008 Created
 * 21-Jan-2009 Modified for code review comments
 * 14-May-2009 Added DMA word swap work around for C5505 PG1.4
 * 26-May-2009 Modified as per review comments
 * 18-Jul-2009 Added support for DMA mode in USB_handleRx & USB_handleTx APIs
 * 28-Jul-2009 Removed the commented code as per the review comments
 * 13-Aug-2010 CSL v2.10 release
 * 06-Jul-2011 CSL v2.50 release
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */

#ifndef _CSL_USBAUX_H_
#define _CSL_USBAUX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl_intc.h>
#include <csl_usb.h>

/** Descriptor Type of the Host Packet, value is 16 (Bit 31-27)              */
#define HOST_PACKET_DESCR_TYPE (0x10)

/** Value to indicate the type of packet as USB, for the Host Descriptor
    Packet                                                                   */
#define PACKET_TYPE_FOR_USB (5u)

/** USB Register overlay structure pointer                                   */
extern CSL_UsbRegsOvly    usbRegisters;
/** CPU System control register overlay structure pointer                    */
extern CSL_SysRegsOvly    sysCtrlRegs;
/** @addtogroup CSL_USB_FUNCTION
 @{ */

/** ===========================================================================
 *   @n@b USB_swapWords
 *
 *   @b Description
 *   @n This function swaps words in a given buffer
 *
 *   @b Arguments
 *   @verbatim
            dataBuffer    Pointer to the buffer which words needs to be swapped
            dataLength    Length of data to be word swapped (In words)
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Reset successful
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameters
 *
 *   <b> Pre Condition </b>
 *   @n None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  Order of data in the given buffer
 *
 *   @b Example
 *   @verbatim
            #define USB_PACKET_SIZE (256)

            Uint16        usbBuf [USB_PACKET_SIZE];
            CSL_Status    status;

            status = USB_swapWords (usbBuf, USB_PACKET_SIZE);
     @endverbatim
 *  ===========================================================================
 */
static inline
CSL_Status USB_swapWords (Uint16 *dataBuffer,
                          Uint32 dataLength)
{
	CSL_Status    status;
	Uint32        looper;
	Uint16        tempData;

	status = CSL_SOK;

	/* Check the input parameters */
	if ((dataBuffer != NULL) && (dataLength > 0))
	{
		/* Swap the words in the given buffer */
		for (looper = 0; looper < dataLength/2; looper++)
		{
			tempData = *dataBuffer++;
			*(dataBuffer -1) = *dataBuffer;
			*dataBuffer++ = tempData;
		}
	}
	else
	{
		status = CSL_ESYS_INVPARAMS;
	}

	return (status);
}

/** ============================================================================
 *   @n@b USB_initDma
 *
 *   @b Description
 *   @n Initializes the Dma
 *
 *   @b Arguments
 *   @verbatim
			None
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  USB_init should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Initializes USB Dma
 *
 *   @b Modifies
 *   @n USB Dma registers
 *
 *   @b Example
 *   @verbatim
			USB_init();
			....
			....
			USB_initDma();
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_initDma(void)
{
	Bool  value;

	// save the
	// disable the hardware interrupt to make sure the
	// following operations are atomic
	value = IRQ_globalDisable();

	/* set TX channel 0 for EP1, queue manger 0 and TX completion queue number 24 */
    usbRegisters->CHANNEL[0].TXGCR1 = 0x0018;
    /* enable TX channel 0 for EP1, enable */
	usbRegisters->CHANNEL[0].TXGCR2 = CSL_USB_TXGCR2_TX_ENABLE_MASK;

	/* set TX channel 1 for EP2, queue manger 0 and TX completion queue number 24 */
    usbRegisters->CHANNEL[1].TXGCR1 = 0x0018;
    /* enable TX channel 1 for EP2, enable */
	usbRegisters->CHANNEL[1].TXGCR2 = CSL_USB_TXGCR2_TX_ENABLE_MASK;

	/* set TX channel 2 for EP3, queue manger 0 and TX completion queue number 24 */
    usbRegisters->CHANNEL[2].TXGCR1 = 0x0018;
    /* enable TX channel 2 for EP3, enable */
	usbRegisters->CHANNEL[2].TXGCR2 = CSL_USB_TXGCR2_TX_ENABLE_MASK;

	/* set TX channel 3 for EP4, queue manger 0 and TX completion queue number 24 */
    usbRegisters->CHANNEL[3].TXGCR1 = 0x0018;
    /* enable TX channel 3 for EP4, enable */
	usbRegisters->CHANNEL[3].TXGCR2 = CSL_USB_TXGCR2_TX_ENABLE_MASK;

    /* set RX channel 0 for EP1,  queue manager number 0, RX completion queue number 26
     * set descriptor type to Host (value 1) [15:14]
     */
    usbRegisters->CHANNEL[0].RXGCR1 = CSL_USB_RXGCR1_DEFVAL;
    /* enable RX channel 0. Channel 0 is for EP1
     * set Starvation error result in dropping packet [24]
     * set SOF offset 0 [23:16]
     */
	usbRegisters->CHANNEL[0].RXGCR2 = CSL_USB_RXGCR2_DEFVAL;
    usbRegisters->CHANNEL[0].RXHPCR1A = CSL_USB_RXHPCR1A_RESETVAL;
    usbRegisters->CHANNEL[0].RXHPCR2A = CSL_USB_RXHPCR2A_RESETVAL;
    usbRegisters->CHANNEL[0].RXHPCR1B = CSL_USB_RXHPCR1B_RESETVAL;
    usbRegisters->CHANNEL[0].RXHPCR2B = CSL_USB_RXHPCR2B_RESETVAL;

    /* set RX channel 1 for EP2,  queue manager number 0, RX completion queue number 26
     * set descriptor type to Host (value 1) [15:14]
     */
    usbRegisters->CHANNEL[1].RXGCR1 = CSL_USB_RXGCR1_DEFVAL;

    /* enable RX channel 1. Channel 1 is for EP2
     * set Starvation error result in dropping packet [24]
     * set SOF offset 0 [23:16]
     */
	usbRegisters->CHANNEL[1].RXGCR2 = CSL_USB_RXGCR2_DEFVAL;

    usbRegisters->CHANNEL[1].RXHPCR1A = CSL_USB_RXHPCR1A_RESETVAL;
    usbRegisters->CHANNEL[1].RXHPCR2A = CSL_USB_RXHPCR2A_RESETVAL;
    usbRegisters->CHANNEL[1].RXHPCR1B = CSL_USB_RXHPCR1B_RESETVAL;
    usbRegisters->CHANNEL[1].RXHPCR2B = CSL_USB_RXHPCR2B_RESETVAL;

    /* set RX channel 2 for EP3,  queue manager number 0, RX completion queue number 26
     * set descriptor type to Host (value 1) [15:14]
     */
    usbRegisters->CHANNEL[2].RXGCR1 = CSL_USB_RXGCR1_DEFVAL;
    /* enable RX channel 2. Channel 2 is for EP3
     * set Starvation error result in dropping packet [24]
     * set SOF offset 0 [23:16]
     */
	usbRegisters->CHANNEL[2].RXGCR2 = CSL_USB_RXGCR2_DEFVAL;
    usbRegisters->CHANNEL[2].RXHPCR1A = CSL_USB_RXHPCR1A_RESETVAL;
    usbRegisters->CHANNEL[2].RXHPCR2A = CSL_USB_RXHPCR2A_RESETVAL;
    usbRegisters->CHANNEL[2].RXHPCR1B = CSL_USB_RXHPCR1B_RESETVAL;
    usbRegisters->CHANNEL[2].RXHPCR2B = CSL_USB_RXHPCR2B_RESETVAL;

    /* set RX channel 3 for EP4,  queue manager number 0, RX completion queue number 26
     * set descriptor type to Host (value 1) [15:14]
     */
    usbRegisters->CHANNEL[3].RXGCR1 = CSL_USB_RXGCR1_DEFVAL;
    /* enable RX channel 3. Channel 3 is for EP4
     * set Starvation error result in dropping packet [24]
     * set SOF offset 0 [23:16]
     */
	usbRegisters->CHANNEL[3].RXGCR2 = CSL_USB_RXGCR2_DEFVAL;
    usbRegisters->CHANNEL[3].RXHPCR1A = CSL_USB_RXHPCR1A_RESETVAL;
    usbRegisters->CHANNEL[3].RXHPCR2A = CSL_USB_RXHPCR2A_RESETVAL;
    usbRegisters->CHANNEL[3].RXHPCR1B = CSL_USB_RXHPCR1B_RESETVAL;
    usbRegisters->CHANNEL[3].RXHPCR2B = CSL_USB_RXHPCR2B_RESETVAL;

    /* Related to Scheduler Initialization */
    /* setup Channel 0 (EP1) for RX and TX */
    usbRegisters->CDMASCHETBLWORD[0].ENTRYLSW = 0x0080;
    /* setup Channel 1 (EP2) for RX and TX */
    usbRegisters->CDMASCHETBLWORD[0].ENTRYMSW = 0x0181;
    /* setup Channel 2 (EP3) for RX and TX */
    usbRegisters->CDMASCHETBLWORD[1].ENTRYLSW = 0x0282;
    /* setup Channel 3 (EP4) for RX and TX */
    usbRegisters->CDMASCHETBLWORD[1].ENTRYMSW = 0x0383;

    /* setup 4 entries */
    usbRegisters->DMA_SCHED_CTRL1 = 7;

    /* enable scheduler */
    usbRegisters->DMA_SCHED_CTRL2 = CSL_USB_DMA_SCHED_CTRL2_ENABLE_MASK;
    /* Ends: Related to Scheduler Initialization */

	// enable the hardware interrupt
	IRQ_globalRestore(value);
}


/** ============================================================================
 *   @n@b USB_initQueueManager
 *
 *   @b Description
 *   @n Initializes the Dma queue manager.
 *
 *   @b Arguments
 *   @verbatim
 	        hpdtx         - Dma host packet transmit descriptor pointer
			pLinkingRam   - Pointer to linking RAM data buffer
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Reset successful
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameters
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initDma should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Initializes queue manager
 *
 *   @b Modifies
 *   @n USB Queue manager registers
 *
 *   @b Example
 *   @verbatim
			CSL_UsbHostPacketDescriptor    hpdtx;
			USB_init();
			....
			....
			USB_initDma();
			USB_initQueueManager(&hpdrx);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status USB_initQueueManager(CSL_UsbHostPktDescr *hpdtx,
                                Uint32              *pLinkingRam)
{
	Uint32        u32Addr;
	Uint16        u16CpyReg;
	CSL_Status    status;
	Bool		  value;

	status =  CSL_SOK;

	if((hpdtx != NULL) && (pLinkingRam != NULL))
	{
	    /* setup linking RAM 0 base address */
		u32Addr   = (Uint32)pLinkingRam;
		u16CpyReg = (Uint16)((u32Addr * 2) & CSL_USB_16BIT_REG_MASK);

		// disable the hardware interrupt to make sure the
		// following operations are atomic
		value = IRQ_globalDisable();
	    usbRegisters->LRAM0BASE1 = u16CpyReg;
		u16CpyReg = (Uint16)(((u32Addr * 2) >> CSL_USB_16BIT_REG_SHIFT) &
		                                       CSL_USB_16BIT_REG_MASK);
	    /* OR with 8 for SARAM */
	    usbRegisters->LRAM0BASE2 = u16CpyReg | 8;
	    /* setup linking RAM0 size */
	    usbRegisters->LRAM0SIZE  = CSL_USB_LRAM0SIZE_DEFVAL;

	    /* setup linking RAM 1 base address */
		u32Addr   = (Uint32)pLinkingRam;
		u16CpyReg = (Uint16)((u32Addr * 2) & CSL_USB_16BIT_REG_MASK);
	    usbRegisters->LRAM1BASE1 = (Uint16)u16CpyReg;
		u16CpyReg = (Uint16)(((u32Addr * 2) >> CSL_USB_16BIT_REG_SHIFT) &
		                                       CSL_USB_16BIT_REG_MASK);
	    /* OR with 8 for SARAM */
	    usbRegisters->LRAM1BASE2 = u16CpyReg | 8;

	    /* setup memory region 0 base address */
		u32Addr = (Uint32)(hpdtx);
		u16CpyReg = (Uint16)((u32Addr * 2) & CSL_USB_16BIT_REG_MASK);
	    usbRegisters->QMMEMREGR[0].QMEMRBASE1 = u16CpyReg;

	    /* OR with 8 for SARAM */
		u16CpyReg = (Uint16)( ((u32Addr * 2) >> CSL_USB_16BIT_REG_SHIFT) &
		                                        CSL_USB_16BIT_REG_MASK);
	    usbRegisters->QMMEMREGR[0].QMEMRBASE2 = u16CpyReg | 8;

	    /* setup memory region control register 32 byte per descriptor and 32 descriptors  allowed */
	    usbRegisters->QMMEMREGR[0].QMEMRCTRL1 = 0x0000;//CSL_USB_QMEMRCTRL1_DEFVAL;
	    usbRegisters->QMMEMREGR[0].QMEMRCTRL2 = CSL_USB_QMEMRCTRL2_DEFVAL;
		// enable the hardware interrupt
		IRQ_globalRestore(value);
	}
	else
	{
		status =  CSL_ESYS_INVPARAMS;
	}

	return(status);
}

/** ============================================================================
 *   @n@b USB_dmaPopQue
 *
 *   @b Description
 *   @n Function to popup the DMA queue. DMA descriptors will be removed from
 *      the queue.
 *
 *   @b Arguments
 *   @verbatim
 	        queueNum   - Queue number
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Reset successful
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameters
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Popup the queue
 *
 *   @b Modifies
 *   @n USB Queue manager registers
 *
 *   @b Example
 *   @verbatim

			USB_dmaPopQue(24);
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_dmaPopQue(Uint16 queueNum)
{
	Uint16 descTemp, countTemp;

	countTemp = usbRegisters->QMQNS[queueNum].QSTATA;

	while (countTemp > 0)
	{
		descTemp = usbRegisters->QMQN[queueNum].CTRL1D;
		countTemp = usbRegisters->QMQNS[queueNum].QSTATA;

		/* TO avoid compilation warnings */
		descTemp= descTemp;
		countTemp = countTemp;
	}
}

/** ============================================================================
 *   @n@b USB_dmaRxStart
 *
 *   @b Description
 *   @n Starts Dma Receive
 *
 *   @b Arguments
 *   @verbatim
 			dwEndpoint    - Endpoint number that is configured for Rx
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  USB_confDmaRx should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Starts Dma data receive
 *
 *   @b Modifies
 *   @n Data buffer
 *
 *   @b Example
 *   @verbatim
			#define CSL_USB_DATA_SIZE    (256)
			Uint16    usbDataBuf[CSL_USB_DATA_SIZE];

			CSL_UsbHostPacketDescriptor    hpdrx;

			USB_initDma();
			USB_initQueueManager(&hpdrx);
			....
			....
			USB_confDmaRx(&hpdrx, CSL_USB_DATA_SIZE, usbDataBuf);
			....
			....
			USB_dmaRxStart();
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_dmaRxStart(DWORD dwEndpoint)
{
	Uint16    saveIndex;

    /* save the index register value */
    saveIndex = usbRegisters->INDEX_TESTMODE;

    /* Write the endpoint configuration*/
    usbRegisters->INDEX_TESTMODE  &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
    usbRegisters->INDEX_TESTMODE  |= dwEndpoint;

#if 0 ///MW It clears the wrong bit
    // clear AutoClear (bit 15) and DMAMode (bit 11)
    usbRegisters->PERI_RXCSR_INDX &= 0x6FFF;
#else
    // clear AutoClear (bit 15) and DMAMode (bit 11)
    usbRegisters->PERI_RXCSR_INDX &= 0x77FF;
#endif

#if 0 ///MW, need set the DISNYET (bit 12) too
    /* Enable the USB DMA for Rx operation */
    usbRegisters->PERI_RXCSR_INDX |= CSL_USB_PERI_RXCSR_DMAEN_MASK;
#else
    /* Enable the USB DMA for Rx operation (bit 13) and set DSINYET (bit 12) */
    usbRegisters->PERI_RXCSR_INDX |= (CSL_USB_PERI_RXCSR_DMAEN_MASK|CSL_USB_PERI_RXCSR_DISNYET_MASK);
#endif

    /* restore the index register */
    usbRegisters->INDEX_TESTMODE   = saveIndex;
}

/** ============================================================================
 *   @n@b USB_confDmaRx
 *
 *   @b Description
 *   @n Configures Dma for Data receive
 *
 *   @b Arguments
 *   @verbatim
 	        hpdrx         - Dma host packet descriptor pointer
 	        packetsize    - Size of the packet to receive (In Bytes)
 	        pRxBuffer     - Receive Data Buffer pointer
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Reset successful
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameters
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initDma and USB_initQueueManager should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Receives the data from an end point
 *
 *   @b Modifies
 *   @n USB Dma registers
 *
 *   @b Example
 *   @verbatim
			#define CSL_USB_DATA_SIZE    (256)
			Uint16    usbDataBuf[CSL_USB_DATA_SIZE];

			CSL_UsbHostPacketDescriptor    hpdrx;

			USB_initDma();
			USB_initQueueManager(&hpdrx);
			....
			....
			USB_confDmaRx(&hpdrx, CSL_USB_DATA_SIZE, usbDataBuf);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status USB_confDmaRx(CSL_UsbHostPktDescr *hpdrx,
                         Uint32              packetsize,
                         Uint16              *pRxBuffer)
{
	volatile Uint16    index;
	CSL_Status         status;
	Bool			   value;

	status = CSL_SOK;

	if((hpdrx != NULL) && (pRxBuffer != NULL))
	{
	    /* Set packet info word 0 */
	    hpdrx->PacketInfoWord0 = ((Uint32)HOST_PACKET_DESCR_TYPE << 27) | packetsize;
	    /* set source port, channel, sub-channel to 0 */
	    hpdrx->PacketInfoWord1 = 0;

	    /* set USB packet, return policy to entire, off-chip memory,
	     * return to Q manager 0 and Q 26
	     */
	    hpdrx->PacketInfoWord2 = ((Uint32)PACKET_TYPE_FOR_USB << 26);
	    hpdrx->PacketInfoWord2 |= 26; /* Queue Number to be used for
	                                      transmission */

	    hpdrx->Buffer0InfoWord0 = packetsize;

	    /* buffer pointer in SARAM */
	    hpdrx->Buffer0InfoWord1 = ((Uint32)pRxBuffer) << 1 | 0x80000;

	    /* next descriptor */
	    hpdrx->LinkingWord = 0;
	    hpdrx->OriginalBuffer0InfoWord0 = packetsize;

	    /* buffer pointer in SARAM */
	    hpdrx->OriginalBuffer0InfoWord1 = ((Uint32)pRxBuffer) << 1 | 0x80000;

		// disable the hardware interrupt to make sure the
		// following operations are atomic
		value = IRQ_globalDisable();
	    usbRegisters->QMQN[0].CTRL1D = ((((Uint32)hpdrx) << 1) &
	                                       CSL_USB_16BIT_REG_MASK) | 2;
	    usbRegisters->QMQN[0].CTRL2D = (((((Uint32)hpdrx) >> 15) &
	                                       CSL_USB_16BIT_REG_MASK) | 8);
		// enable the hardware interrupt
		IRQ_globalRestore(value);
	}
	else
	{
		status = CSL_ESYS_INVPARAMS;
	}

	return(status);
}


/** ============================================================================
 *   @n@b USB_confDmaTx
 *
 *   @b Description
 *   @n Configures Dma for Data USB data transfer. For C5505 PG1.4 and earlier
 *      versions of the DSP, word swap is required for the data buffer before
 *      transferring the data. Parameter 'swapWords' provides facility to
 *      request for the word swap for the data buffer.
 *
 *   @b Arguments
 *   @verbatim
 	        hpdtx         - Dma host packet descriptor pointer
 	        packetsize    - Size of the packet to transmit (In Bytes)
 	        pTxBuffer     - Data Buffer pointer
			swapWords     - Flag to request for word swap
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Reset successful
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameters
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initDma and USB_initQueueManager should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  transmits data to an end point
 *
 *   @b Modifies
 *   @n USB Dma registers
 *
 *   @b Example
 *   @verbatim
			#define CSL_USB_DATA_SIZE    (256)
			Uint16    usbDataBuf[CSL_USB_DATA_SIZE];

			CSL_UsbHostPacketDescriptor    hpdtx;

			USB_initDma();
			USB_initQueueManager(&hpdrx);
			....
			....
			USB_confDmaTx(&hpdrx, CSL_USB_DATA_SIZE, usbDataBuf);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status USB_confDmaTx(DWORD    			 dwEndpoint,				
						 CSL_UsbHostPktDescr *hpdtx,
                         Uint32              packetsize,
                         Uint16              *pTxBuffer,
                         Bool                swapWords)
{
	CSL_Status    status;
	Bool		  value;

	status = CSL_SOK;

	if((hpdtx != NULL) && (pTxBuffer != NULL))
	{
		/* Swap the words in the data buffer */
		if(TRUE == swapWords)
		{
			/* On VC5505 DSP, DMA will perform a word swap on the source buffer
			   before transferring it to the destination. During USB Tx a word
			   swap by software is required before DMA data transfer to ensure
			   that the data is transferred to the destination in proper order.
			   HW word swap by DMA will be compensated by the software word swap.
			 */
			USB_swapWords (pTxBuffer, packetsize/2);
		}

	    /* Set packet info word 0 */
	    hpdtx->PacketInfoWord0 = ((Uint32)HOST_PACKET_DESCR_TYPE << 27) | packetsize;
	    /* set source port, channel, sub-channel to 0 */
	    ///hpdtx->PacketInfoWord1 = 0;
	    /* set source port to EP1, channel, sub-channel to 0 */
	    hpdtx->PacketInfoWord1 = 0;

	    /* set USB packet, return policy to entire, off-chip memory,
	     * return to Q manager 0 and Q 24
	     */
	    hpdtx->PacketInfoWord2 = ((Uint32)PACKET_TYPE_FOR_USB << 26);
	    hpdtx->PacketInfoWord2 |= 24; /* Queue Number to be used for
	                                      transmission */

	    hpdtx->Buffer0InfoWord0 = packetsize;

	    /* buffer pointer in SARAM */
	    hpdtx->Buffer0InfoWord1 = ((Uint32)pTxBuffer) << 1 | 0x80000;

		/* next descriptor */
		hpdtx->LinkingWord = 0;
	    hpdtx->OriginalBuffer0InfoWord0 = packetsize;

	    /* buffer pointer in SARAM */
	    hpdtx->OriginalBuffer0InfoWord1 = ((Uint32)pTxBuffer) << 1 | 0x80000;

		// disable the hardware interrupt to make sure the
		// following operations are atomic
		value = IRQ_globalDisable();
	    /* add packet descriptor to TX submission queue for the Endpoint */
		/* EP1 to 16 or 17, EP2 to 18 or 19, EP3 to 20 or 21, EP4 to 22 or 23 */ 
 		
	    usbRegisters->QMQN[14+dwEndpoint*2].CTRL1D = ((((Uint32)hpdtx) << 1) &
	                                          CSL_USB_16BIT_REG_MASK) | 2;
	    usbRegisters->QMQN[14+dwEndpoint*2].CTRL2D = (((((Uint32)hpdtx) >> 15) &
	                                         CSL_USB_16BIT_REG_MASK) | 8);

		// enable the hardware interrupt
		IRQ_globalRestore(value);
	}
	else
	{
		status = CSL_ESYS_INVPARAMS;
	}

	return(status);
}

/** ============================================================================
 *   @n@b USB_dmaRxStop
 *
 *   @b Description
 *   @n Stops Dma data Receive operation. For C5505 PG1.4 and earlier
 *      versions of the DSP, wordswap is required for the data buffer after
 *      completing the data reception. Parameter 'swapWords' provides facility
 *      to request for the word swap for the data buffer.
 *
 *   @b Arguments
 *   @verbatim
			dwEndpoint   - Endpoint number that is configured for Rx
 			pRxBuffer    -   DMA Receive data buffer
			packetsize   -   Size of the data received (In Bytes)
			swapWords    -   Flag to swap the words in the Rx buffer
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  USB_dmaRxStart should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Starts Dma data receive
 *
 *   @b Modifies
 *   @n USB Registers
 *
 *   @b Example
 *   @verbatim
			#define CSL_USB_DATA_SIZE    (256)
			Uint16    usbDataBuf[CSL_USB_DATA_SIZE];

			CSL_UsbHostPacketDescriptor    hpdrx;

			USB_confDmaRx(&hpdrx, CSL_USB_DATA_SIZE, usbDataBuf);
			....
			....
			USB_dmaRxStart();
			...
			...
			USB_dmaRxStop();
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_dmaRxStop(DWORD  dwEndpoint,
                   Uint16 *pRxBuffer,
                   Uint32 packetsize,
                   Bool   swapWords)
{
    Uint16  saveIndex = 0;

    /* save the index register value */
    saveIndex = usbRegisters->INDEX_TESTMODE;

    /*Write the endpoint configuration*/
    usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
    usbRegisters->INDEX_TESTMODE |= dwEndpoint;

    usbRegisters->PERI_RXCSR_INDX &= ~CSL_USB_PERI_RXCSR_DMAEN_MASK;

    /* restore the index register */
    usbRegisters->INDEX_TESTMODE = saveIndex;

	if(swapWords == TRUE)
	{
		/* Swap the words in Rx buffer */
		/* On VC5505 DSP, DMA will perform a word swap on the source buffer
		   before transferring it to the destination. During USB Rx a word swap
		   by software is required after DMA data transfer to ensure that
		   the data is received in proper order.HW word swap by DMA will
		   be compensated by the software word swap.
		 */
		USB_swapWords (pRxBuffer, packetsize/2);
	}
}

/** ============================================================================
 *   @n@b USB_dmaTxStart
 *
 *   @b Description
 *   @n Starts Dma data transmit. DMA should be configure for the data
 *      transmit operation before calling this function. Data will be
 *      transmitted by the DMA as per the configured values.
 *
 *   @b Arguments
 *   @verbatim
 			dwEndpoint    - Endpoint number that is configured for Tx
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  USB_confDmaTx should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Starts Dma data transfer
 *
 *   @b Modifies
 *   @n USB FIFO registers
 *
 *   @b Example
 *   @verbatim
			#define CSL_USB_DATA_SIZE    (256)
			Uint16    usbDataBuf[CSL_USB_DATA_SIZE];

			CSL_UsbHostPacketDescriptor    hpdtx;

			USB_initDma();
			USB_initQueueManager(&hpdtx);
			....
			....
			USB_confDmaTx(&hpdtx, CSL_USB_DATA_SIZE, usbDataBuf);
			....
			....
			USB_dmaTxStart();
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_dmaTxStart(DWORD dwEndpoint)
{
    Uint16  saveIndex;

    /* save the index register value */
    saveIndex = usbRegisters->INDEX_TESTMODE;

    /* Write the endpoint configuration */
    usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
    usbRegisters->INDEX_TESTMODE |= dwEndpoint;

	/* Flush the FIFO */
	CSL_FINS(usbRegisters->PERI_CSR0_INDX, USB_PERI_TXCSR_FLUSHFIFO, TRUE);

	/* clear auticlear (bit 15) and set DMA mode (bit 11) */
    usbRegisters->PERI_CSR0_INDX &= 0x7FFF;
    usbRegisters->PERI_CSR0_INDX |= 0x1000;

	/* Enable the USB DMA */
    usbRegisters->PERI_CSR0_INDX |= CSL_USB_PERI_TXCSR_DMAEN_MASK;

    /* restore the index register */
    usbRegisters->INDEX_TESTMODE = saveIndex;
}


/** ============================================================================
 *   @n@b USB_dmaTxStop
 *
 *   @b Description
 *   @n Stops Dma data transmit.
 *
 *   @b Arguments
 *   @verbatim
 			dwEndpoint    - Endpoint number that is configured for Tx
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  USB_dmaTxStart should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Stops Dma data receive
 *
 *   @b Modifies
 *   @n USB registers
 *
 *   @b Example
 *   @verbatim
			#define CSL_USB_DATA_SIZE    (256)
			Uint16    usbDataBuf[CSL_USB_DATA_SIZE];

			CSL_UsbHostPacketDescriptor    hpdtx;

			USB_confDmaTx(&hpdtx, CSL_USB_DATA_SIZE, usbDataBuf);
			....
			....
			USB_dmaTxStart();
			...
			...
			USB_dmaTxStop();
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_dmaTxStop(DWORD dwEndpoint)
{
    Uint16    saveIndex;

    /* save the index register value */
    saveIndex = usbRegisters->INDEX_TESTMODE;

    /* Write the endpoint configuration */
    usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
    usbRegisters->INDEX_TESTMODE |= dwEndpoint;

	/* Disable the USB DMA */
    usbRegisters->PERI_CSR0_INDX &= ~CSL_USB_PERI_TXCSR_DMAEN_MASK;

    /* restore the index register */
    usbRegisters->INDEX_TESTMODE = saveIndex;
}

/** ============================================================================
 *   @n@b USB_handleTx
 *
 *   @b Description
 *   @n Transmits the data over the non-control end points.
 *      This function can transmit the data in polled mode or using
 *      CPPI DMA. For the DMA mode operation opmode needs to be set to DMA
 *      using USB_init() API and CPPI DMA needs to be configured for USB Tx
 *      operation using USB_confDmaTx() API before calling this function.
 *
 *      USB DMA will be used when the data to be transferred is 64 or 512
 *      bytes. CPU will be used to transfer any other length of data.
 *
 *      Data to be sent will be copied to the Tx FIFO one packet at a time.
 *      Legth of the packet will be decided based on the maximum packet
 *      size assigned to the Tx FIFO. In case of poll mode operation complete
 *      transfer callback function will be invoked after copying all the packets
 *      to the Tx FIFO. In case of DMA mode operation complete transfer callback
 *      will be invoked for each packet transferred. Complete transfer callback
 *      function is supposed to wait for DMA transfer completion.
 *
 *      Number of bytes written to FIFO in each transaction will be stored in
 *      'pTransfer->prevTxferLen'. This value will be 64 or 512 when DMA mode
 *      is enabled and DMA is used for the data transfer. Other cases indicates
 *      that CPU mode is enabled or CPU is used for data transfer.
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev       -   USB device handle
 	        dwEndpoint    -   End point number
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Writes data to an end point
 *
 *   @b Modifies
 *   @n USB FIFO registers
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			status = USB_handleTx(hUsbDev, CSL_USB_EP1);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status USB_handleTx(CSL_UsbDevHandle hUsbDev,
                        DWORD            dwEndpoint)
{
	DWORD	        cbToWrite;
    WORD            *pwBuffer;
    DWORD           cbBuffer;
    DWORD 	        cbWritten;
	Uint16          count;
	Uint16          saveIndex;
	CSL_Status      status;
	pUsbEpStatus    peps;
    pUsbTransfer    pTransfer;
	volatile ioport Uint16    *pFifoAddr;
	volatile        Uint32 delay;

    status    = CSL_SOK;
    count     = 0;
    saveIndex = 0;
    cbWritten =0;

    if(hUsbDev != NULL)
    {
		peps = &hUsbDev->pEpStatus[dwEndpoint];
		pTransfer = peps->pTransfer;

		if((pTransfer != NULL) && (pTransfer->fComplete == FALSE))
		{
			pwBuffer  = (WORD*)pTransfer->pvBuffer + pTransfer->cbTransferred/2;
			cbBuffer  = (pTransfer->cbBuffer - pTransfer->cbTransferred);
			pFifoAddr = (volatile ioport Uint16*)peps->pFifoAddr;

			/* Min of input byte count and supported size */
			cbToWrite = CSL_USB_MIN(cbBuffer, peps->dwPacketSizeAssigned);

			/* No need to transfer the data if this flag is set */
			if(pTransfer->ioFlags == CSL_USB_IOFLAG_NOT)
			{
				pTransfer->fComplete = TRUE;
			}
			else
			{
				if(peps->fStalled != TRUE)
				{
					/* Check if USB is configured for DMA */
					if(((cbToWrite == 512) || (cbToWrite == 64)) &&
					   ((hUsbDev->opMode == CSL_USB_OPMODE_DMA) ||
					   (hUsbDev->opMode == CSL_USB_OPMODE_DMA_TXONLY)))
					{
						pTransfer->cbTransferred += cbToWrite;
						pTransfer->prevTxferLen   = cbToWrite;

						USB_dmaTxStart(dwEndpoint);

						if (pTransfer->cbTransferred == pTransfer->cbBuffer)
						{
							pTransfer->fComplete = TRUE;
						}
						else
						{
							status = hUsbDev->completeTransferCallback(hUsbDev, peps);
						}
					}
					else
					{

#if ((defined(CSL_MSC_TEST)) || (defined(CSL_AC_TEST)))

						/* TI MSC put the DATA length as the first WORD,
						   bypass it */
						if((cbToWrite != 512) && ((cbToWrite != 64)))
						{
							pwBuffer++;
						}
#endif

						/* save the index register value */
						saveIndex = usbRegisters->INDEX_TESTMODE;

						/* Select the end point for data transfer */
						CSL_FINS(usbRegisters->INDEX_TESTMODE,
								 USB_INDEX_TESTMODE_EPSEL,
								 CSL_USB_INDEX_TESTMODE_EPSEL_RESETVAL);

						CSL_FINS(usbRegisters->INDEX_TESTMODE,
								 USB_INDEX_TESTMODE_EPSEL,
								 dwEndpoint);

						/* Flush the FIFO */
						CSL_FINS(usbRegisters->PERI_CSR0_INDX,
								 USB_PERI_TXCSR_FLUSHFIFO, TRUE);

						if(cbToWrite > 0)
						{
							/* write out all the bytes */
							cbWritten = cbToWrite;

							for(count = 0; count < (cbToWrite/2); count++)
							{
								*pFifoAddr = *pwBuffer++;
							}

							if(cbToWrite % 2)
							{
								/* Enable byte access */
								CSL_FINST(sysCtrlRegs->USBSCR,
								          SYS_USBSCR_BYTEMODE, LOWER);
								CSL_FINS(*pFifoAddr, USB_FIFO1R1_DATA,
								         *pwBuffer);
								/* Disable byte access */
								CSL_FINST(sysCtrlRegs->USBSCR,
								          SYS_USBSCR_BYTEMODE, FULL);
							}
						}

						if(peps->xferType == CSL_USB_ISO)
						{
							usbRegisters->PERI_CSR0_INDX |=
							                CSL_USB_PERI_TXCSR_CLRDATATOG_MASK;
						}

						/* Commit Tx Packet */
						CSL_FINS(usbRegisters->PERI_CSR0_INDX,
								 USB_PERI_CSR0_INDX_RXPKTRDY, TRUE);

						/* restore the index register */
						usbRegisters->INDEX_TESTMODE = saveIndex;

						/* Update the Transferred count */
						pTransfer->cbTransferred += cbWritten;
						pTransfer->prevTxferLen   = cbWritten;

						if((pTransfer->cbTransferred == pTransfer->cbBuffer) ||
						   (cbWritten == 0))
						{
							pTransfer->fComplete = TRUE;
						}
					}
				}
			}

			if (pTransfer->fComplete)
			{
				hUsbDev->fWaitingOnFlagA = FALSE;
				status = hUsbDev->completeTransferCallback(hUsbDev, peps);
			}
		}
		else
		{
			status = CSL_ESYS_INVPARAMS;
		}
	}
	else
	{
		status = CSL_ESYS_INVPARAMS;
	}

	return(status);
}

/** ============================================================================
 *   @n@b USB_handleRx
 *
 *   @b Description
 *   @n Receives the data over the non-control end points
 *      This function can read the data in polled mode or using
 *      CPPI DMA. For the DMA mode operation opmode needs to be set to DMA
 *      using USB_init() API and CPPI DMA needs to be configured for USB Rx
 *      operation using USB_confDmaRx() API before calling this function.
 *
 *      USB DMA will be used when the data to be received is 64 or 512
 *      bytes. CPU will be used to receive any other length of data.
 *
 *      Data to be recived will be read from the Rx FIFO one packet at a time.
 *      Legth of the packet will be decided based on the maximum packet
 *      size assigned to the Rx FIFO. In case of poll mode operation complete
 *      transfer callback function will be invoked after reading all the packets
 *      from the Rx FIFO. In case of DMA mode operation complete transfer callback
 *      will be invoked for each packet read. Complete transfer callback
 *      function is supposed to wait for DMA transfer completion.
 *
 *      Number of bytes read from FIFO in each transaction will be stored in
 *      'pTransfer->prevTxferLen'. This value will be 64 or 512 when DMA mode
 *      is enabled and DMA is used for the data transfer. Other cases indicates
 *      that CPU mode is enabled or CPU is used for data transfer.
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev       -   USB device handle
 	        dwEndpoint    -   End point number
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Reads data from an end point
 *
 *   @b Modifies
 *   @n USB Data buffer
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			status = USB_handleRx(hUsbDev, CSL_USB_EP2);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status USB_handleRx(CSL_UsbDevHandle hUsbDev,
                        DWORD            dwEndpoint)
{
	DWORD	            cbToRead;
    DWORD  		        cbBuffer;
    DWORD 		        dwBytesRead;
	WORD                *pwBuffer;
    pUsbTransfer        pTransfer;
    CSL_Status          status;
	Uint16              saveIndex;
	pUsbEpStatus        peps;
	volatile Uint16     count;
	volatile ioport Uint16    *pFifoAddr;

	status      = CSL_SOK;
	dwBytesRead = 0;

	if(hUsbDev != NULL)
    {
		peps = &hUsbDev->pEpStatus[dwEndpoint];
		pTransfer = peps->pTransfer;

		if((pTransfer != NULL) && (pTransfer->fComplete == FALSE))
		{
			cbBuffer = pTransfer->cbBuffer - pTransfer->cbTransferred;
			pwBuffer = (WORD*)pTransfer->pvBuffer + pTransfer->cbTransferred/2;
			pFifoAddr   = (volatile ioport Uint16*)peps->pFifoAddr;

			/* Min of input byte count and supported size */
			cbToRead = CSL_USB_MIN(cbBuffer, peps->dwPacketSizeAssigned);

			if(((cbToRead == 512) || (cbToRead == 64)) &&
			    (hUsbDev->opMode == CSL_USB_OPMODE_DMA))
			{
				pTransfer->cbTransferred += cbToRead;
				pTransfer->prevTxferLen   = cbToRead;

				USB_dmaRxStart(dwEndpoint);

				if (pTransfer->cbTransferred == pTransfer->cbBuffer)
				{
					pTransfer->fComplete = TRUE;
					hUsbDev->fWaitingOnFlagB = FALSE;
				}

				status = hUsbDev->completeTransferCallback(hUsbDev, peps);
			}
			else
			{

#if ((defined(CSL_MSC_TEST)) || (defined(CSL_AC_TEST)))

				/* TI MSC put the DATA length as the first WORD, bypass it */
				if((cbToRead != 512) && ((cbToRead != 64)))
				{
					pwBuffer++;
				}
#endif

				if(cbToRead > 0)
				{
					/* Write out all the bytes */
					dwBytesRead = cbToRead;

					for(count = 0; count < (cbToRead/2); count++)
					{
						*pwBuffer++ = *pFifoAddr;
					}

					if(cbToRead % 2)
					{
						/* Enable byte access */
						CSL_FINST(sysCtrlRegs->USBSCR,
								  SYS_USBSCR_BYTEMODE, LOWER);
						*pwBuffer = *pFifoAddr & 0xFF;

						/* Disable byte access */
						CSL_FINST(sysCtrlRegs->USBSCR,
								  SYS_USBSCR_BYTEMODE, FULL);
					}
				}

				pTransfer->cbTransferred += dwBytesRead;
				pTransfer->prevTxferLen   = dwBytesRead;

				if((pTransfer->cbTransferred == pTransfer->cbBuffer) ||
				   (dwBytesRead == 0))
				{
					pTransfer->fComplete = TRUE;
				}

				/* Save the index register value */
				saveIndex = usbRegisters->INDEX_TESTMODE;

				CSL_FINS(usbRegisters->INDEX_TESTMODE,
						 USB_INDEX_TESTMODE_EPSEL,
						 CSL_USB_INDEX_TESTMODE_EPSEL_RESETVAL);

				CSL_FINS(usbRegisters->INDEX_TESTMODE,
						 USB_INDEX_TESTMODE_EPSEL, dwEndpoint);

				if(peps->xferType == CSL_USB_ISO)
				{
					/* Clear the data toggle bit */
					usbRegisters->PERI_RXCSR_INDX |= (CSL_USB_PERI_RXCSR_CLRDATATOG_MASK);
				}

				/* Clear the rxpktrdy bit */
				CSL_FINS(usbRegisters->PERI_RXCSR_INDX,
						 USB_PERI_RXCSR_RXPKTRDY, FALSE);

				/* Restore the index register */
				usbRegisters->INDEX_TESTMODE = saveIndex;

				if(pTransfer->fComplete == TRUE)
				{
					hUsbDev->fWaitingOnFlagB = FALSE;

					/* This transfer is completed */
#if ((defined(CSL_MSC_TEST)) || (defined(CSL_AC_TEST)))
					/* TI MSC put the DATA length as the first WORD, bypass it */
					if((cbToRead != 512) && (cbToRead != 64))
					{
						*(PWORD)pTransfer->pvBuffer = pTransfer->cbTransferred;
					}
#endif

					status = hUsbDev->completeTransferCallback(hUsbDev, peps);
				}
			}
		}
		else
		{
			status = CSL_ESYS_INVPARAMS;
		}
	}
	else
	{
		status = CSL_ESYS_INVPARAMS;
	}

    return(status);
}

/** ============================================================================
 *   @n@b USB_processEP0Out
 *
 *   @b Description
 *   @n Reads the data from End point 0
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev      -   USB device handle
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Reads data from end point0
 *
 *   @b Modifies
 *   @n Ep0 data buffer
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			status = USB_processEP0Out(hUsbDev);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status USB_processEP0Out(CSL_UsbDevHandle hUsbDev)
{
    pUsbEpStatus    peps;
    pUsbTransfer    pTransfer;
    WORD            *pwBuffer;
    CSL_Status      status;

    status = CSL_SOK;

    if(hUsbDev != NULL)
    {
		peps = &hUsbDev->pEpStatus[CSL_USB_EP0];
		pTransfer = peps->pTransfer;

		if((pTransfer != NULL) && (pTransfer->fComplete == FALSE))
		{
			/* for none-last packet, it is always WORD align */
			pwBuffer = (WORD*)pTransfer->pvBuffer + pTransfer->cbTransferred/2;

#if ((defined(CSL_MSC_TEST)) || (defined(CSL_AC_TEST)))

			/* TI MSC put the DATA length as the first WORD, bypass it */
			(WORD*)pwBuffer++;
#endif

			/* move data from ep0 fifo to ep buffer */
			pTransfer->cbTransferred = CSL_USB_MIN(hUsbDev->cbOutEP0Buf,
			                                       pTransfer->cbBuffer);

			memcpy(pwBuffer, (PVOID)hUsbDev->dwOutEP0Buf,
			       (pTransfer->cbTransferred+1)/2);

			hUsbDev->fOutPhaseCmd  = FALSE;
			pTransfer->fComplete    = TRUE;
			pTransfer->prevTxferLen = pTransfer->cbTransferred;

#if ((defined(CSL_MSC_TEST)) || (defined(CSL_AC_TEST)))
			/* This transfer is completed */
			*(PWORD)pTransfer->pvBuffer = pTransfer->cbTransferred;
#endif
			status = hUsbDev->completeTransferCallback(hUsbDev, peps);
		}
		else
		{
			status = CSL_ESYS_INVPARAMS;
		}
	}
	else
	{
		status = CSL_ESYS_INVPARAMS;
	}
    return(status);
}

/** ============================================================================
 *   @n@b USB_processEP0In
 *
 *   @b Description
 *   @n Writes data to End point 0
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev      -  USB device handle
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Writes data to end point0
 *
 *   @b Modifies
 *   @n Ep0 FIFO registers
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			status = USB_processEP0In(hUsbDev);
     @endverbatim
 *  ============================================================================
 */
#if 1
static inline
CSL_Status USB_processEP0In(CSL_UsbDevHandle hUsbDev)
{
    pUsbEpStatus    peps;
    pUsbTransfer    pTransfer;
    CSL_Status      status;
    PWORD 	        pwBuffer;
    DWORD 	        cbBuffer;
	WORD	        cbToWrite;
	Uint16          count;
	Uint16          flag;
	Uint16          saveIndex;

	flag   = 0;
	status = CSL_SOK;

	if(hUsbDev != NULL)
	{
		peps = &hUsbDev->pEpStatus[CSL_USB_EP0];
		pTransfer = peps->pTransfer;

		if((pTransfer != NULL) && (pTransfer->fComplete == FALSE))
		{
			/* for none-last packet, it is always WORD align */
			pwBuffer = (PWORD)pTransfer->pvBuffer + pTransfer->cbTransferred/2;
			cbBuffer = pTransfer->cbBuffer - pTransfer->cbTransferred;

#if ((defined(CSL_MSC_TEST)) || (defined(CSL_AC_TEST)))
			/* TI MSC put the DATA length as the first WORD, bypass it */
			pwBuffer++;
#endif

			/* Min of input byte count and supported size */
			cbToWrite = CSL_USB_MIN(cbBuffer, peps->dwPacketSizeAssigned);

			while(TRUE)
			{
				/* write data to EP0 FIFO */
				for(count = 0; count < cbToWrite/2;count++)
				{
					usbRegisters->FIFO0R1 = (*pwBuffer);
					pwBuffer++;
				}

				if(cbToWrite % 2 == TRUE)
				{
					/* Enable byte access */
					CSL_FINST(sysCtrlRegs->USBSCR, SYS_USBSCR_BYTEMODE, LOWER);
					usbRegisters->FIFO0R1 = (*pwBuffer);
					/* Disable byte access */
					CSL_FINST(sysCtrlRegs->USBSCR, SYS_USBSCR_BYTEMODE, FULL);
				}

				/* update the remainder data length, we may need zero length */
				if(cbToWrite <= CSL_USB_MAX_EP0_FIFO_LEN)
				{
					break;
				}
				else
				{
					cbToWrite -= CSL_USB_MAX_EP0_FIFO_LEN;
				}
			}

			hUsbDev->fEP0BUFAvailable = FALSE;

			pTransfer->cbTransferred += cbToWrite;
			pTransfer->prevTxferLen   = cbToWrite;
			if(pTransfer->cbTransferred == pTransfer->cbBuffer)
			{
				pTransfer->fComplete  = TRUE;
			}

			/* save the index register value */
			saveIndex = usbRegisters->INDEX_TESTMODE;

			/* Reset Index register end point selection field */
			CSL_FINS(usbRegisters->INDEX_TESTMODE,
					 USB_INDEX_TESTMODE_EPSEL,
					 CSL_USB_INDEX_TESTMODE_EPSEL_RESETVAL);

			/* Select Ep 0 */
			CSL_FINS(usbRegisters->INDEX_TESTMODE,
					 USB_INDEX_TESTMODE_EPSEL,
					 CSL_USB_EP0);

			if(pTransfer->fComplete  == TRUE)
			{
				hUsbDev->fWaitingOnEP0BUFAvail = FALSE;

				/* set txpktrdy and data end */
				flag = (CSL_USB_PERI_CSR0_INDX_DATAEND_MASK |
				        CSL_USB_PERI_CSR0_INDX_TXPKTRDY_MASK);
				/* change ep0 state to EP0_IDLE */
				hUsbDev->ep0State = CSL_USB_EP0_IDLE;
				/* Commit Tx packet */
				usbRegisters->PERI_CSR0_INDX |= flag;

				status = hUsbDev->completeTransferCallback(hUsbDev, peps);
			}
			else
			{
				/* set txpktrdy */
				flag = CSL_USB_PERI_CSR0_INDX_TXPKTRDY_MASK;

				/* Commit Tx packet */
				usbRegisters->PERI_CSR0_INDX |= flag;
			}

			/* restore the index register */
			usbRegisters->INDEX_TESTMODE = saveIndex;
		}
		else
		{
			status = CSL_ESYS_INVPARAMS;
		}
	}
	else
	{
		status = CSL_ESYS_INVPARAMS;
	}

	return(status);
}
#endif

/** ============================================================================
 *   @n@b USB_handleRxIntr
 *
 *   @b Description
 *   @n This function handles USb receive interrupts.
 *      This function is provided to be used with MSC module.
 *      For standalone MUSB operation this function is not required
 *      This function works only if EP2 configured for Rx
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev      -  USB device handle
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Handles Rx interrupt
 *
 *   @b Modifies
 *   @n USb registers
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			status = USB_handleRxIntr(hUsbDev);
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_handleRxIntr(CSL_UsbDevHandle hUsbDev)
{
	Uint16          saveIndex;
	pUsbEpStatus    peps;

	peps = &hUsbDev->pEpStatus[CSL_USB_EP2];
	saveIndex = 0;

	/* save the index register value */
	saveIndex = usbRegisters->INDEX_TESTMODE;

   	usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
   	usbRegisters->INDEX_TESTMODE |= CSL_USB_EP2;

	/* Check if sendstall bit is set */
    if((usbRegisters->PERI_CSR0_INDX & CSL_USB_PERI_TXCSR_INDX_SENDSTALL_MASK)
       == CSL_USB_PERI_TXCSR_INDX_SENDSTALL_MASK)
	{
		CSL_FINS(usbRegisters->PERI_CSR0_INDX, USB_PERI_TXCSR_SENDSTALL, FALSE);
	}

	/* check if RxPktRdy bit is set */
    if((usbRegisters->PERI_RXCSR_INDX & CSL_USB_PERI_RXCSR_RXPKTRDY_MASK)
       == CSL_USB_PERI_RXCSR_RXPKTRDY_MASK)
	{
		if(peps->xferType == CSL_USB_ISO)
		{
			hUsbDev->fSetupPktCmd = TRUE;
		}
		else
		{
			hUsbDev->fWaitingOnFlagB = TRUE;
		}
	}

	/* restore the index register */
	usbRegisters->INDEX_TESTMODE = saveIndex;
}

/** ============================================================================
 *   @n@b USB_handleTxIntr
 *
 *   @b Description
 *   @n This function handles USB transmit interrupts.
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev      -  USB device handle
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Handles Tx interrupt
 *
 *   @b Modifies
 *   @n USb registers
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			status = USB_handleTxIntr(hUsbDev);
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_handleTxIntr(CSL_UsbDevHandle hUsbDev)
{
	Uint16          saveIndex;

	saveIndex = 0;

	/* Save the index register value */
	saveIndex = usbRegisters->INDEX_TESTMODE;

   	usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
   	///usbRegisters->INDEX_TESTMODE |= CSL_USB_EP1;
   	usbRegisters->INDEX_TESTMODE |= CSL_USB_EP2;

	/* Check if sendstall bit is set */
    if((usbRegisters->PERI_CSR0_INDX & CSL_USB_PERI_TXCSR_INDX_SENDSTALL_MASK)
       == CSL_USB_PERI_TXCSR_INDX_SENDSTALL_MASK)
	{
		CSL_FINS(usbRegisters->PERI_CSR0_INDX, USB_PERI_TXCSR_SENDSTALL, FALSE);
	}

	/* Restore the index register */
	usbRegisters->INDEX_TESTMODE = saveIndex;
}

/** ============================================================================
 *   @n@b USB_checkSpeed
 *
 *   @b Description
 *   @n This function checks the USB bus speed
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev       -   USB device handle
 	        pBusSpeed     -   USB Bus speed variable pointer
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                    TRUE  - Bus speed is valid
 *   @li                    FALSE - Bus speed is invalid
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Checks the USB bus speed
 *
 *   @b Modifies
 *   @n Bus speed variable
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			busSpeedStat = USB_checkSpeed(hUsbDev, hUsbDev->busSpeed);
     @endverbatim
 *  ============================================================================
 */
static inline
Bool USB_checkSpeed(CSL_UsbDevHandle hUsbDev,
			  		CSL_UsbBusSpeed  *pBusSpeed)
{
	Uint16    wPower;

	wPower = usbRegisters->FADDR_POWER;

	if((wPower == 0) || (pBusSpeed == NULL))
	{
		return (FALSE);
	}

	/*
	 * Highspeed mode bit of the power register will be set if the USB
	 * successfully negotiates with host for operating in highspeed mode
	 */
    if((usbRegisters->FADDR_POWER & CSL_USB_FADDR_POWER_HSMODE_MASK) != 0)
    {
        *pBusSpeed = CSL_USB_BS_HIGH_SPEED;
	}
    else
    {
        *pBusSpeed = CSL_USB_BS_FULL_SPEED;
	}

    return (TRUE);
}

/** ============================================================================
 *   @n@b USB_readEP0Buf
 *
 *   @b Description
 *   @n This function reads the End point0 buffer
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev       -   USB device handle
 	        pBusSpeed     -   USB Bus speed variable pointer
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK         - Returned for success
 *   @li                    CSL_ESYS_FAIL   - Returned for failure
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Reads Ep0 data
 *
 *   @b Modifies
 *   @n Ep0 Buffer
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			status = USB_readEP0Buf(hUsbDev, hUsbDev->dwOutEP0Buf);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_Status USB_readEP0Buf(CSL_UsbDevHandle hUsbDev,
                          DWORD            *pBuf)
{
	WORD	packetSize;
	Uint16 	saveIndex;
	WORD    count = 0;
	Uint32  tempStore;
	Uint16  flag;

	saveIndex  = 0;
	packetSize = 0;
	flag       = 0;

	/* save the index register value */
	saveIndex = (usbRegisters->INDEX_TESTMODE &
	             CSL_USB_INDEX_TESTMODE_EPSEL_MASK);

    /* select EP0 registers */
    usbRegisters->INDEX_TESTMODE &= ~(CSL_USB_INDEX_TESTMODE_EPSEL_MASK);
	/* get RX packet size */
    packetSize = ((usbRegisters->COUNT0_INDX) &
                  CSL_USB_COUNT0_INDX_EP0RXCOUNT_MASK);

    if((packetSize > CSL_USB_MAX_EP0_FIFO_LEN) ||
	   (packetSize > hUsbDev->cbOutEP0DataReceived))
	{
		/* restore the index register */
        usbRegisters->INDEX_TESTMODE &= ~(CSL_USB_INDEX_TESTMODE_EPSEL_MASK);
        usbRegisters->INDEX_TESTMODE |= saveIndex;

        flag = CSL_USB_PERI_CSR0_INDX_SERV_RXPKTRDY_MASK;
        usbRegisters->PERI_CSR0_INDX |= flag;

        return (CSL_ESYS_FAIL);
	}

	pBuf = hUsbDev->dwOutEP0Buf;

	for(count = 0; count < packetSize; count += 4)
	{
		*pBuf = 0;
		tempStore = 0;
	 	*pBuf =	usbRegisters->FIFO0R1;
	 	tempStore = usbRegisters->FIFO0R1;
	 	*pBuf |= (tempStore << 16);
		pBuf++;
	}

    hUsbDev->cbOutEP0DataReceived -= packetSize;

	if(hUsbDev->cbOutEP0DataReceived == 0)
	{
		/* set DataEnd bit */
       	flag = CSL_USB_PERI_CSR0_INDX_DATAEND_MASK;
	}

	/* set the ServicedRxPktRdy bit */
    flag |= CSL_USB_PERI_CSR0_INDX_SERV_RXPKTRDY_MASK;
    usbRegisters->PERI_CSR0_INDX |= flag;

	/* restore the index register */
	usbRegisters->INDEX_TESTMODE &= ~(CSL_USB_INDEX_TESTMODE_EPSEL_MASK);
	usbRegisters->INDEX_TESTMODE |= saveIndex;

	return (CSL_SOK);
}

/** ============================================================================
 *   @n@b USB_setConfiguration
 *
 *   @b Description
 *   @n This function sets the end point configuration
 *      This is provided to use with MSC module
 *      This function is not required for standalone MUSB testing
 *
 *   @b Arguments
 *   @verbatim
 	        hUsbDev       -   USB device handle
 	        confVal       -   configuration value
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets the end point configuration
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			....
			....
			status = USB_setConfiguration(hUsbDev, 0x02);
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_setConfiguration(CSL_UsbDevHandle hUsbDev,
                          Uint16           confVal)
{
	Uint16 saveIndex;
	Uint16  tempVal;

	saveIndex = 0;

	if(hUsbDev->devNum == CSL_USB0)
	{
		/* save the index register value */
		saveIndex = usbRegisters->INDEX_TESTMODE;

		/* Configure EP1 for Tx and Rx */
		/* Select EP1 */
		usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
		usbRegisters->INDEX_TESTMODE |= CSL_USB_EP1;

		/* set ClrDataTog bit (TxCSR.D6) */
		usbRegisters->PERI_CSR0_INDX |= (CSL_USB_PERI_TXCSR_CLRDATATOG_MASK);
		/* set ClrDataTog bit (RxCSR.D7) */
		usbRegisters->PERI_RXCSR_INDX |= (CSL_USB_PERI_RXCSR_CLRDATATOG_MASK);

		/* Flush FIFO if not empty */
		if((usbRegisters->PERI_CSR0_INDX & CSL_USB_PERI_TXCSR_FIFONOTEMPTY_MASK) ==
		   CSL_USB_PERI_TXCSR_FIFONOTEMPTY_MASK)
		{
			//usbRegisters->PERI_CSR0_INDX |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;

			tempVal = usbRegisters->PERI_CSR0_INDX;

			tempVal |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;
			tempVal &= ~(0x03);

			usbRegisters->PERI_CSR0_INDX = tempVal;
		}

		/* Configure EP2 for Tx and Rx */
		/* Select EP2 */
		usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
		usbRegisters->INDEX_TESTMODE |= CSL_USB_EP2;

		/* set ClrDataTog bit (TxCSR.D6) */
		usbRegisters->PERI_CSR0_INDX |= (CSL_USB_PERI_TXCSR_CLRDATATOG_MASK);
		/* set ClrDataTog bit (RxCSR.D7) */
		usbRegisters->PERI_RXCSR_INDX |= (CSL_USB_PERI_RXCSR_CLRDATATOG_MASK);

		/* Flush FIFO if not empty */
		if((usbRegisters->PERI_CSR0_INDX & CSL_USB_PERI_TXCSR_FIFONOTEMPTY_MASK) ==
		   CSL_USB_PERI_TXCSR_FIFONOTEMPTY_MASK)
		{
			//usbRegisters->PERI_CSR0_INDX |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;

			tempVal = usbRegisters->PERI_CSR0_INDX;

			tempVal |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;
			tempVal &= ~(0x03);

			usbRegisters->PERI_CSR0_INDX = tempVal;
		}

		/* Configure EP3 for Tx and Rx */
		/* Select EP3 */
		usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
		usbRegisters->INDEX_TESTMODE |= CSL_USB_EP3;

		/* set ClrDataTog bit (TxCSR.D6) */
		usbRegisters->PERI_CSR0_INDX |= (CSL_USB_PERI_TXCSR_CLRDATATOG_MASK);
		/* set ClrDataTog bit (RxCSR.D7) */
		usbRegisters->PERI_RXCSR_INDX |= (CSL_USB_PERI_RXCSR_CLRDATATOG_MASK);

		/* Flush FIFO if not empty */
		if((usbRegisters->PERI_CSR0_INDX & CSL_USB_PERI_TXCSR_FIFONOTEMPTY_MASK) ==
		   CSL_USB_PERI_TXCSR_FIFONOTEMPTY_MASK)
		{
			//usbRegisters->PERI_CSR0_INDX |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;

			tempVal = usbRegisters->PERI_CSR0_INDX;

			tempVal |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;
			tempVal &= ~(0x03);

			usbRegisters->PERI_CSR0_INDX = tempVal;
		}

		/* Configure EP4 for Tx and Rx */
		/* Select EP4 */
		usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
		usbRegisters->INDEX_TESTMODE |= CSL_USB_EP4;

		/* set ClrDataTog bit (TxCSR.D6) */
		usbRegisters->PERI_CSR0_INDX |= (CSL_USB_PERI_TXCSR_CLRDATATOG_MASK);
		/* set ClrDataTog bit (RxCSR.D7) */
		usbRegisters->PERI_RXCSR_INDX |= (CSL_USB_PERI_RXCSR_CLRDATATOG_MASK);

		/* Flush FIFO if not empty */
		if((usbRegisters->PERI_CSR0_INDX & CSL_USB_PERI_TXCSR_FIFONOTEMPTY_MASK) ==
		   CSL_USB_PERI_TXCSR_FIFONOTEMPTY_MASK)
		{
			//usbRegisters->PERI_CSR0_INDX |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;

			tempVal = usbRegisters->PERI_CSR0_INDX;

			tempVal |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;
			tempVal &= ~(0x03);

			usbRegisters->PERI_CSR0_INDX = tempVal;
		}

		/* restore the index register */
		usbRegisters->INDEX_TESTMODE = saveIndex;
	}
}

/** ============================================================================
 *   @n@b USB_isValidDataInFifoOut
 *
 *   @b Description
 *   @n This function checks validity of the data in the output FIFO
 *
 *   @b Arguments
 *   @verbatim
 	        peps      -   End point status structure pointer
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                    TRUE  - FIFO out has valid data
 *   @li                    FALSE - FIFO out no has valid data
 *
 *   <b> Pre Condition </b>
 *   @n  USB_initEndptObj function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Checks the data in FIFO Out
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			Bool             fifoStatus;
			pUsbEpStatus     peps;
			CSL_UsbDevHandle hUsbDev;
			CSL_Status       status;
            CSL_UsbConfig    usbCfg
			CSL_UsbEpConfig  epCfg
			CSL_UsbEpHandle  hEp
            .....
            .....
            USB_init();
			hUsbDev = USB_open(CSL_USB0);
			status = USB_config(hUsbDev, &usbCfg);
			hEp = USB_requestEndpt(hUsbDev, CSL_USB_OUT_EP0, &status);
			status = USB_configEndpt(hEp, &epCfg);
			....
			....
			fifoStatus = USB_isValidDataInFifoOut(peps);
     @endverbatim
 *  ============================================================================
 */
static inline
Bool USB_isValidDataInFifoOut(pUsbEpStatus peps)
{
	Uint16    saveIndex;
	Uint16    wByteCount;
	Uint16    flag;

	saveIndex  = 0;
	wByteCount = 0;
	flag       = FALSE;

	if((CSL_USB_EP1 == peps->dwEndpoint) ||
	   (CSL_USB_EP2 == peps->dwEndpoint) ||
	   (CSL_USB_EP3 == peps->dwEndpoint) ||
	   (CSL_USB_EP4 == peps->dwEndpoint))
	{
		/* save the index register value */
		saveIndex = usbRegisters->INDEX_TESTMODE;

		usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
        	usbRegisters->INDEX_TESTMODE |= peps->dwEndpoint;

		/* check if RxPktRdy is set */
        if((usbRegisters->PERI_RXCSR_INDX & CSL_USB_PERI_RXCSR_RXPKTRDY_MASK) ==
            CSL_USB_PERI_RXCSR_RXPKTRDY_MASK)
		{
			wByteCount = usbRegisters->COUNT0_INDX & 0x1FFF;
			peps->dataReadFromFifo = wByteCount;

			if(peps->xferType != CSL_USB_ISO)
			{
			if((wByteCount <= peps->dwPacketSizeAssigned))
			{
				/* packet is valid only if RxPktRdy is TRUE and
				  Bytes in FIFO is <= max pkt size assigned for the EP */
				flag = TRUE;
			}
		}
			else
			{
				flag = TRUE;
			}
		}

		/* restore the index register */
	   usbRegisters->INDEX_TESTMODE = saveIndex;
	}

	return(flag);
}

/** ============================================================================
 *   @n@b USB_flushFifo
 *
 *   @b Description
 *   @n Function to flush the Tx and Rx FIFO of the USB
 *
 *   @b Arguments
 *   @verbatim
 	        dwEndpoint  - End point to which FIFO flush is required
 	        fifoDirFlag - Flag to indicate the FIFO direction
 	                      1 - Tx FIFO, 0 - Rx FIFO
     @endverbatim
 *
 *   <b> Return Value </b> None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Flushes Tx/Rx FIFO
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            //Flush Tx FIFO
			USB_flushFifo (CSL_USB_EP1, 1);

            //Flush Rx FIFO
			USB_flushFifo (CSL_USB_EP2, 0);
     @endverbatim
 *  ============================================================================
 */
static inline
void USB_flushFifo(DWORD dwEndpoint,
                   Bool  fifoDirFlag)
{
	Uint16 saveIndex;
	Uint16 tempVal;

	saveIndex = 0;

	/* save the index register value */
	saveIndex = usbRegisters->INDEX_TESTMODE;

	/* Select end point */
	usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
   	usbRegisters->INDEX_TESTMODE |= dwEndpoint;

	if (dwEndpoint == CSL_USB_EP0)
	{
		/* Flush EP0 FIFO */
		usbRegisters->PERI_CSR0_INDX |= CSL_USB_PERI_CSR0_INDX_FLUSHFIFO_MASK;
	}
	else
	{
		if (1 == fifoDirFlag)
		{
			/* Flush Tx FIFO of given end point */
			//usbRegisters->PERI_CSR0_INDX |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;
			tempVal = usbRegisters->PERI_CSR0_INDX;

			tempVal |= CSL_USB_PERI_TXCSR_FLUSHFIFO_MASK;
			tempVal &= ~(0x03);

			usbRegisters->PERI_CSR0_INDX = tempVal;
		}
		else
		{
			/* Flush Rx FIFO of given end point */
			usbRegisters->PERI_RXCSR_INDX |=CSL_USB_PERI_RXCSR_FLUSHFIFO_MASK;
		}
	}

	/* Restore the index register */
	usbRegisters->INDEX_TESTMODE = saveIndex;
}

/** ============================================================================
 *   @n@b USB_serviceEp0RxPkt
 *
 *   @b Description
 *   @n Function to service the RxPkt for the Ep0
 *
 *   @b Arguments
 *   @verbatim
 	        periCsr0Val - Value of 'PERI_CSR0_INDX' register
     @endverbatim
 *
 *   <b> Return Value </b> None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Services EP0 Rx packet
 *
 *   @b Modifies
 *   @n USB registers
 *
 *   @b Example
 *   @verbatim
			USB_serviceEp0RxPkt (CSL_USB_PERI_CSR0_INDX_SERV_RXPKTRDY_MASK);
     @endverbatim
 *  ============================================================================
 */

/**
@} */
static inline
void USB_serviceEp0RxPkt(Uint16 periCsr0Val)
{
	usbRegisters->PERI_CSR0_INDX |= periCsr0Val;
}

/**
 * \brief API to send Zero length packet to a End Point
 *
 * \param dwEndpoint [in] End Point
 *
 * \return NONE
 */
static inline
void USB_sendEpZLP(DWORD dwEndpoint)
{
	Uint16 saveIndex;

	/* save the index register value */
	saveIndex = usbRegisters->INDEX_TESTMODE;

	/* Select end point */
	usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
   	usbRegisters->INDEX_TESTMODE |= dwEndpoint;

	// send zero length packet
	CSL_FINS(usbRegisters->PERI_CSR0_INDX,
	         USB_PERI_CSR0_INDX_TXPKTRDY, TRUE);
	CSL_FINS(usbRegisters->PERI_CSR0_INDX,
	         USB_PERI_CSR0_INDX_DATAEND, TRUE);

	/* Restore the index register */
	usbRegisters->INDEX_TESTMODE = saveIndex;
}

/**
 * \brief API to clear End Point Rx Packet ready bit
 *
 * \param dwEndpoint [in] End Point
 *
 * \return NONE
 */
static inline
void USB_clearEpRxPktRdy(DWORD dwEndpoint)
{
	Uint16 saveIndex;

	/* save the index register value */
	saveIndex = usbRegisters->INDEX_TESTMODE;

	/* Select end point */
	usbRegisters->INDEX_TESTMODE &= ~CSL_USB_INDEX_TESTMODE_EPSEL_MASK;
   	usbRegisters->INDEX_TESTMODE |= dwEndpoint;

	// send zero length packet
	CSL_FINS(usbRegisters->PERI_CSR0_INDX,
	         USB_PERI_CSR0_INDX_SERV_RXPKTRDY, TRUE);
	CSL_FINS(usbRegisters->PERI_CSR0_INDX,
	         USB_PERI_CSR0_INDX_DATAEND, TRUE);

	/* Restore the index register */
	usbRegisters->INDEX_TESTMODE = saveIndex;
}

#ifdef __cplusplus
}
#endif

#endif    //_CSL_USBAUX_H_

