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
/** @file USB.cpp
 *
 *  @brief USB implementation
 *
 */
 
#include "USB.h"

#pragma DATA_SECTION("USB_buffer1")
/** USB host packet descriptor for writing */
CSL_UsbHostPktDescr hpdtx;
#pragma DATA_SECTION("USB_buffer1")
/** USB host packet descriptor for reading */
CSL_UsbHostPktDescr hpdrx;
#pragma DATA_SECTION("USB_buffer2")
/** Linking RAM buffer */
unsigned long       linking_ram0[USB_LRAM_SIZE];
#pragma DATA_SECTION("USB_buffer3")
/** USB data buffer 1 */
unsigned short      usbDataBufferTxRx1[USB_DATA_SIZE];
#pragma DATA_SECTION("USB_buffer3")
/** USB data buffer 2 */
unsigned short      usbDataBufferTxRx2[USB_DATA_SIZE];
#pragma DATA_SECTION("USB_buffer3")
/** USB data buffer 3 */
unsigned short      usbDataBufferTxRx3[USB_DATA_SIZE];
#pragma DATA_SECTION("USB_buffer3")
/** USB data buffer 4 */
unsigned short      usbDataBufferTxRx4[USB_DATA_SIZE];	
/** USB class object */
USBClass            USB;
/** USB handle */
CSL_UsbDevHandle    hUsbDev = NULL;
/** USB configuration structure */
USB_Config          gUsbConfig;
/** Flag to indicate if a long data packet is being sent */
bool                sentLongEp0Pkt;

int startTransferCallback(void *vpContext, void *vpeps);

int completeTransferCallback(void *vpContext, void *vpeps);

static int getPipeNum(unsigned short epNum, unsigned short direction);

static int getEndPoint(unsigned short pipeNum);

static void USB_delay(unsigned long mSecs);

/**
 * USB Class Constructor
 */
USBClass::USBClass()
{
    usb_income_num_bytes_ep1 = 0;
    usb_income_num_bytes_ep2 = 0;
    usb_income_num_bytes_ep3 = 0;
    usb_income_num_bytes_ep4 = 0;
	configVal                = 0;
    saveIndex                = 0;
	endpt                    = 0;
    devAddr                  = 0;
	usbDevDisconnect         = TRUE;
	queuePend                = 0;
	usbBuffTxRxPtr1          = usbDataBufferTxRx1;
	usbBuffTxRxPtr2          = usbDataBufferTxRx2;
	usbBuffTxRxPtr3          = usbDataBufferTxRx3;
	usbBuffTxRxPtr4          = usbDataBufferTxRx4;
}

/** ===========================================================================
 *   @n@b init()
 *
 *   @b Description
 *   @n Function initializes USB module.
 *
 *   @b Arguments
 *   @verbatim
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::init()
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	USB_init();

	hUsbDev = USB_open(CSL_USB0);
	if(hUsbDev != NULL)
	{
	    sentLongEp0Pkt = FALSE;

		status = CSL_SOK;
	}

    return(status);
}

/** ===========================================================================
 *   @n@b config()
 *
 *   @b Description
 *   @n Configures the USB module
 *
 *   @b Arguments
 *   @verbatim
 *      usbConfig    <- Configuration structure
 *
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::config(USB_Config usbConfig)
{
    CSL_Status    status;
    CSL_UsbConfig cslUsbConfig;

	status = CSL_ESYS_FAIL;
	gUsbConfig = usbConfig;

	if(hUsbDev != NULL)
	{
		cslUsbConfig.opMode
		  = (CSL_UsbOpMode)usbConfig.opMode;
		cslUsbConfig.appSuspendCallBack
		  = (CSL_USB_APP_CALLBACK)usbConfig.appSuspendCallBack;
		cslUsbConfig.startTransferCallback
		  = (CSL_USB_APP_TRANSFER_CALLBACK)startTransferCallback;
		cslUsbConfig.completeTransferCallback
		  = (CSL_USB_APP_TRANSFER_CALLBACK)completeTransferCallback;
		cslUsbConfig.maxCurrent
		  = USB_MAX_CURRENT;

		hUsbDev->deviceDescPtr = usbConfig.deviceDescPtr;
     	hUsbDev->deviceQualDescPtr = usbConfig.deviceQualDescPtr;
	    hUsbDev->cfgDescPtr = usbConfig.cfgDescPtr;
	    hUsbDev->cfgDescFSPtr = usbConfig.cfgDescFSPtr;
	    hUsbDev->strDescPtr[0] = (unsigned short *)usbConfig.strDescPtr;

	    status = USB_config(hUsbDev, &cslUsbConfig);
		if(status == CSL_SOK)
		{
		    status = USB_resetDev(hUsbDev);
			if(status == CSL_SOK && usbConfig.opMode == USB_OPMODE_DMA)
			{
    		    USB_initQueueManager(&hpdtx, linking_ram0);
    		    USB_initDma();
			}
		}
	}

	return(status);
}

/** ===========================================================================
 *   @n@b connect()
 *
 *   @b Description
 *   @n This function connects the USB module to upstream port
 *
 *   @b Arguments
 *   @verbatim
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::connect()
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	if(hUsbDev != NULL)
	{
	    status = USB_connectDev(hUsbDev);
	}

	return(status);
}

/** ===========================================================================
 *   @n@b disconnect()
 *
 *   @b Description
 *   @n This function disconnects the USB module to upstream port
 *
 *   @b Arguments
 *   @verbatim
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::disconnect()
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	if(hUsbDev != NULL)
	{
	    status = USB_disconnectDev(hUsbDev);
		if(status == CSL_SOK)
		{
		    usbDevDisconnect = TRUE;
		}
	}

	return(status);
}

/** ===========================================================================
 *   @n@b suspend()
 *
 *   @b Description
 *   @n This function suspends the USB device. This function informs the
 *      application about the device suspend through a call back function.
 *
 *   @b Arguments
 *   @verbatim
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::suspend()
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	if(hUsbDev != NULL)
	{
	    status = USB_suspendDevice(hUsbDev);
	}

	return(status);
}

/** ===========================================================================
 *   @n@b requestPipe()
 *
 *   @b Description
 *   @n Function to request the endpoint for data communication
 *
 *   @b Arguments
 *   @verbatim
 *      pipeNum   <- Pipe number
 *      direction <- Transfer direction, USB_IN or USB_OUT
 *   @endverbatim
 *
 *   <b> Return Value </b> void *
 *   @li  Valid pipe handle if success
 *   @li  NULL if error
 *
 *  ===========================================================================
 */
void * USBClass::requestPipe(unsigned short pipeNum, unsigned short direction)
{
    CSL_Status     status;
    int            epNum;
	unsigned short index;

	status = CSL_ESYS_FAIL;

	if(hUsbDev != NULL)
	{
		epNum = getPipeNum(pipeNum, direction);
		if(epNum != -1)
		{
		    if(epNum < CSL_USB_OUT_EP5)
			{
			    index = epNum;
			}
			else
			{
			    index = epNum - CSL_USB_IN_EP0 + CSL_USB_OUT_EP5;
			}

		    hEp[index] = (void *)USB_requestEndpt(hUsbDev,
		                                          (CSL_UsbEpNum)epNum,
		                                          &status);
			if(status != CSL_SOK)
			{
			    return (NULL);
			}
		}
	}

	return(hEp[index]);
}

/** ===========================================================================
 *   @n@b closePipe()
 *
 *   @b Description
 *   @n Function to release an endpoint
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp    <- End point handle
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::closePipe(void *hEp)
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    status = USB_releaseEndpt((CSL_UsbEpHandle)hEp);
	}

	return (status);
}

/** ===========================================================================
 *   @n@b configPipe()
 *
 *   @b Description
 *   @n Function to configure endpoint
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp       <- End point handle
 *      pipeConfig <- End point config structure
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::configPipe(void *hEp, Pipe_Config pipeConfig)
{
    CSL_Status      status;
	CSL_UsbEpConfig epCfg;
	unsigned short  eventMask;

	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    switch(((CSL_UsbEpHandle)hEp)->epNum)
		{
		    case CSL_USB_OUT_EP0:
			case CSL_USB_OUT_EP1:
			case CSL_USB_OUT_EP2:
			case CSL_USB_OUT_EP3:
            case CSL_USB_OUT_EP4:
			    if(pipeConfig.xferType == USB_CTRL)
				{
				    eventMask = (CSL_USB_EVENT_RESET | CSL_USB_EVENT_SETUP |
		                         CSL_USB_EVENT_SUSPEND | CSL_USB_EVENT_RESUME |
		                         CSL_USB_EVENT_RESET | CSL_USB_EVENT_EOT);
				}
				else
				{
				    eventMask = (CSL_USB_EVENT_RESET | CSL_USB_EVENT_EOT);
				}
				break;
		    case CSL_USB_IN_EP0:
			case CSL_USB_IN_EP1:
			case CSL_USB_IN_EP2:
			case CSL_USB_IN_EP3:
            case CSL_USB_IN_EP4:
			    eventMask = CSL_USB_EVENT_EOT;
				break;
			default:
			    return(status);
		}

		epCfg.xferType   = (CSL_UsbXferType)pipeConfig.xferType;
	    epCfg.eventMask  = eventMask;
	    epCfg.maxPktSize = pipeConfig.maxPktSize;
	    epCfg.fxn        = (CSL_USB_EVENT_ISR)NULL;

	    status = USB_configEndpt((CSL_UsbEpHandle)hEp, &epCfg);
	}

	return(status);
}

/** ===========================================================================
 *   @n@b stallPipe()
 *
 *   @b Description
 *   @n This function stalls an end point
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp    <- End point handle
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::stallPipe(void *hEp)
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    status = USB_stallEndpt((CSL_UsbEpHandle)hEp);
	}

	return(status);
}

/** ===========================================================================
 *   @n@b clearPipe()
 *
 *   @b Description
 *   @n This function clears an end point stall
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp    <- End point handle
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::clearPipe(void *hEp)
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    status = USB_clearEndptStall((CSL_UsbEpHandle)hEp);
	}

	return(status);
}

/** ===========================================================================
 *   @n@b writePipe()
 *
 *   @b Description
 *   @n Function to write data to USB pipe
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp  <- End point handle
 *      bytes <- Number of bytes to be written
 *      *data <- Pointer to data buffer
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::writePipe(void           *hEp,
                        unsigned short bytes,
					    unsigned short *data)
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    if(gUsbConfig.opMode == USB_OPMODE_DMA)
		{
		    USB_confDmaTx(getEndPoint(((CSL_UsbEpHandle)hEp)->epNum),
		                  &hpdtx,
		                  bytes,
		                  (Uint16 *)data,
		                  FALSE);

		    USB_dmaTxStart(getEndPoint(((CSL_UsbEpHandle)hEp)->epNum));
		}
		else
		{
	        status = USB_postTransaction((CSL_UsbEpHandle)hEp,
		                                 bytes,
									     data,
									     CSL_USB_IN_TRANSFER);
		}
	}

	return(status);
}

/** ===========================================================================
 *   @n@b readPipe()
 *
 *   @b Description
 *   @n Function to read data from USB pipe
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp  <- End point handle
 *      bytes <- Number of bytes to be read
 *      *data <- Pointer to data buffer
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::readPipe(void           *hEp,
                       unsigned short bytes,
					   unsigned short *data)
{
    CSL_Status status;

	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    if(gUsbConfig.opMode == USB_OPMODE_DMA)
		{
		    USB_confDmaRx(&hpdrx, bytes, (Uint16 *)data);
		    USB_dmaRxStart(getEndPoint(((CSL_UsbEpHandle)hEp)->epNum));
		}
		else
		{
	        status = USB_postTransaction((CSL_UsbEpHandle)hEp,
		                                 bytes,
				    					 data,
					    				 CSL_USB_OUT_TRANSFER);
		}
	}

	return(status);
}

/** ===========================================================================
 *   @n@b setParams()
 *
 *   @b Description
 *   @n Function to initialize the endpoint structures
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp  <- End point handle
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::setParams(void *hEp)
{
	CSL_Status status;

	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    status = USB_setParams(hUsbDev, (CSL_UsbEpHandle *)hEp, FALSE);
	}

	return(status);
}

/** ===========================================================================
 *   @n@b dmaRxStop()
 *
 *   @b Description
 *   @n Stops DMA data receive operation
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp    <- End point handle
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::dmaRxStop(void *hEp)
{
    CSL_Status status;
	int        epNum;

	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    epNum = getEndPoint(((CSL_UsbEpHandle)hEp)->epNum);
		
		if(epNum != -1)
		{
	        USB_dmaRxStop(epNum, 
			              dataBuffer,
			              USB_HS_MAX_PACKET_SIZE, 
						  FALSE);
		}
	}

	return(status);
}

/** ===========================================================================
 *   @n@b dmaTxStop()
 *
 *   @b Description
 *   @n Stops DMA data transmit operation
 *
 *   @b Arguments
 *   @verbatim
 *      *hEp    <- End point handle
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::dmaTxStop(void *hEp)
{
    CSL_Status status;
    int        epNum;
	
	status = CSL_ESYS_FAIL;

	if((hUsbDev != NULL) && (hEp != NULL))
	{
	    epNum = getEndPoint(((CSL_UsbEpHandle)hEp)->epNum);
		
		if(epNum != -1)
		{
	        USB_dmaTxStop(epNum);
		}
	}

	return(status);
}

/** ===========================================================================
 *   @n@b handleInterrupts()
 *
 *   @b Description
 *   @n Function to handle the USB interrupts
 *
 *   @b Arguments
 *   @verbatim
 *   @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int USBClass::handleInterrupts(void)
{
    CSL_UsbSetupStruct usbSetup;
	unsigned short     tempLen; 
		
	/* Read the masked interrupt status register */
	hUsbDev->dwIntSourceL = usbRegisters->INTMASKEDR1;
	hUsbDev->dwIntSourceH = usbRegisters->INTMASKEDR2;

	if(gUsbConfig.opMode == USB_OPMODE_DMA)
	{
	    /* Read queue pending register1 */
	    queuePend = usbRegisters->PEND1;
	}

	/* Clear the interrupts */
	if(hUsbDev->dwIntSourceL != FALSE)
	{
		usbRegisters->INTCLRR1 = hUsbDev->dwIntSourceL;
	}

	if(hUsbDev->dwIntSourceH != FALSE)
	{
		usbRegisters->INTCLRR2 = hUsbDev->dwIntSourceH;
	}

	/* Reset interrupt */
	if(hUsbDev->dwIntSourceH & CSL_USB_GBL_INT_RESET)
	{
		saveIndex = usbRegisters->INDEX_TESTMODE;

		for(endpt = CSL_USB_EP1; endpt <= CSL_USB_EP4; endpt++)
		{
			CSL_FINS(usbRegisters->INDEX_TESTMODE,
					 USB_INDEX_TESTMODE_EPSEL, endpt);

			CSL_FINS(usbRegisters->PERI_RXCSR_INDX,
					 USB_PERI_RXCSR_INDX_DISNYET, TRUE);
		}

		usbRegisters->INDEX_TESTMODE = saveIndex;
	}

	/* Resume interrupt */
	if(hUsbDev->dwIntSourceH & CSL_USB_GBL_INT_RESUME)
	{
		status = USB_setRemoteWakeup(hUsbDev, CSL_USB_TRUE);
		if(status == CSL_SOK)
		{
		    status = USB_issueRemoteWakeup(hUsbDev, TRUE);
            if(status == 0)
			{
			    USB_delay(USB_WAKEUP_DELAY);

		    	status = USB_issueRemoteWakeup(hUsbDev, FALSE);
			}
		}
	}

	/* Check End point0 interrupts */
	if(hUsbDev->dwIntSourceL & CSL_USB_TX_RX_INT_EP0)
	{
		if(sentLongEp0Pkt == 1)
		{
			status = USB_processEP0In(hUsbDev);
		}
		else
		{
			saveIndex = usbRegisters->INDEX_TESTMODE;
			CSL_FINS(usbRegisters->INDEX_TESTMODE,
						 USB_INDEX_TESTMODE_EPSEL, CSL_USB_EP0);

			USB_getSetupPacket(hUsbDev, &usbSetup, TRUE);

			if((usbRegisters->PERI_CSR0_INDX
			    & CSL_USB_PERI_CSR0_INDX_RXPKTRDY_MASK)
				== CSL_USB_PERI_CSR0_INDX_RXPKTRDY_MASK)
			{
				/* Service the RXPKTRDY after reading the FIFO */
				CSL_FINS(usbRegisters->PERI_CSR0_INDX,
				         USB_PERI_CSR0_INDX_SERV_RXPKTRDY, TRUE);

				switch(usbSetup.bRequest)
				{
					/* zero data */
					case CSL_USB_SET_FEATURE:
						switch(usbSetup.wValue)
						{
							case CSL_USB_FEATURE_ENDPOINT_STALL:

								endpt = (usbSetup.wIndex) & 0xFF;

								hEPx = USB_epNumToHandle(hUsbDev, endpt);

								if(!(USB_getEndptStall((CSL_UsbEpHandle)hEPx,
								                       (CSL_Status *)&status)))
								{
									USB_stallEndpt((CSL_UsbEpHandle)hEPx);
								}

								break;

							case CSL_USB_FEATURE_REMOTE_WAKEUP:

								if(!(USB_getRemoteWakeupStat(hUsbDev)))
								{
									USB_setRemoteWakeup(hUsbDev, CSL_USB_TRUE);
								}

								break;

							default:
								break;
						}

						usbRegisters->PERI_CSR0_INDX |=
						           (CSL_USB_PERI_CSR0_INDX_SERV_RXPKTRDY_MASK |
									CSL_USB_PERI_CSR0_INDX_DATAEND_MASK);

						break;

					case CSL_USB_CLEAR_FEATURE:

						switch(usbSetup.wValue)
						{
							case CSL_USB_FEATURE_ENDPOINT_STALL:

								endpt = (usbSetup.wIndex) & 0xFF;

								hEPx = USB_epNumToHandle(hUsbDev, endpt);

								if(USB_getEndptStall((CSL_UsbEpHandle)hEPx,
								                     (CSL_Status *)&status))
								{
									USB_clearEndptStall((CSL_UsbEpHandle)hEPx);
								}

								break;

							case CSL_USB_FEATURE_REMOTE_WAKEUP:

								if(USB_getRemoteWakeupStat(hUsbDev))
								{
									USB_setRemoteWakeup(hUsbDev,
									                    CSL_USB_FALSE);
								}

								break;

							default:
								 break;
						}
						break;

					case CSL_USB_SET_CONFIGURATION :
					case CSL_USB_SET_INTERFACE:

						endpt = (usbSetup.wIndex) & 0xFF;

						hEPx = USB_epNumToHandle(hUsbDev, endpt);

						USB_postTransaction((CSL_UsbEpHandle)hEPx, 0, NULL,
						                    CSL_USB_IOFLAG_NONE);

						usbRegisters->PERI_CSR0_INDX |=
						      (CSL_USB_PERI_CSR0_INDX_SERV_RXPKTRDY_MASK |
							   CSL_USB_PERI_CSR0_INDX_DATAEND_MASK);

						configVal = usbSetup.wValue;

						break;

					case CSL_USB_GET_CONFIGURATION :
					case CSL_USB_GET_INTERFACE:

						dataBuffer[0] = configVal;

						hEPx = USB_epNumToHandle(hUsbDev, 0x80);

						status = USB_postTransaction((CSL_UsbEpHandle)hEPx,
						                 1, dataBuffer,
						                 CSL_USB_IN_TRANSFER);

						break;

					case CSL_USB_GET_DESCRIPTOR :

						switch(usbSetup.wValue >> 8)
						{
							case CSL_USB_DEVICE_DESCRIPTOR_TYPE:

								hEPx = USB_epNumToHandle(hUsbDev, 0x80);

								status = USB_postTransaction(
								               (CSL_UsbEpHandle)hEPx,
								               hUsbDev->deviceDescPtr[0]&0xFF,
								               hUsbDev->deviceDescPtr,
								               CSL_USB_IN_TRANSFER);

								break;

					    	case CSL_USB_OTHERSPEED_CFG_DESCRIPTOR_TYPE:

							    hEPx = USB_epNumToHandle(hUsbDev, 0x80);

								if(usbSetup.wLength == 0x0009)
								{
									status = USB_postTransaction(
									                  (CSL_UsbEpHandle)hEPx,
									                  9, hUsbDev->cfgDescFSPtr,
									                  CSL_USB_IN_TRANSFER);
								}
								else
								{
									if((hUsbDev->cfgDescFSPtr[1] & 0xFF) > 0x40)
									{
										sentLongEp0Pkt = 1;
									}

									status = USB_postTransaction(
									                 (CSL_UsbEpHandle)hEPx,
									                 hUsbDev->cfgDescFSPtr[1],
									                 hUsbDev->cfgDescFSPtr,
									                 CSL_USB_IN_TRANSFER);
								}

					         	break;

							case CSL_USB_CONFIGURATION_DESCRIPTOR_TYPE:

							    hEPx = USB_epNumToHandle(hUsbDev, 0x80);

								if(usbSetup.wLength == 0x0009)
								{
									status = USB_postTransaction(
									                   (CSL_UsbEpHandle)hEPx,
									                   9,
									                   hUsbDev->cfgDescPtr,
									                   CSL_USB_IN_TRANSFER);
								}
								else
								{
									if((hUsbDev->cfgDescPtr[1] & 0xFF) > 0x40)
									{
										sentLongEp0Pkt = 1;
									}

									status = USB_postTransaction(
									                   (CSL_UsbEpHandle)hEPx,
											           hUsbDev->cfgDescPtr[1],
											           hUsbDev->cfgDescPtr,
										               CSL_USB_IN_TRANSFER);
								}

								break;

							case CSL_USB_STRING_DESCRIPTOR_TYPE:

							    hEPx = USB_epNumToHandle(hUsbDev, 0x80);
								
								tempLen = usbSetup.wValue & 0xFF;

								status = USB_postTransaction(
									           (CSL_UsbEpHandle)hEPx,
									           hUsbDev->strDescPtr[tempLen][0]&0xFF,
									           hUsbDev->strDescPtr[tempLen],
									           CSL_USB_IN_TRANSFER);

								break;

							case CSL_USB_DEVICE_QUAL_DESCRIPTOR_TYPE:
							    hEPx = USB_epNumToHandle(hUsbDev, 0x80);

					    	    tempLen = hUsbDev->deviceQualDescPtr[0]&0xFF;

					            tempLen = (tempLen < usbSetup.wLength)
					                             ? tempLen : usbSetup.wLength;

								status = USB_postTransaction(
								                   (CSL_UsbEpHandle)hEPx,
								                   tempLen,
								                   hUsbDev->deviceQualDescPtr,
								                   CSL_USB_IN_TRANSFER);

								break;

							default:

	                            status =
	                                  USB_stallEndpt((CSL_UsbEpHandle)hEp[0]);

								break;
						}

						if(sentLongEp0Pkt != 1)
						{
						    usbRegisters->PERI_CSR0_INDX
						         |=   (CSL_USB_PERI_CSR0_INDX_TXPKTRDY_MASK |
								       CSL_USB_PERI_CSR0_INDX_DATAEND_MASK);
						}
						else
						{
						    sentLongEp0Pkt = sentLongEp0Pkt;
						}

						break;

					case CSL_USB_GET_STATUS:

						switch(usbSetup.bmRequestType)
						{
							case CSL_USB_REQUEST_TYPE_DEVICE_STATUS:

								hEPx = USB_epNumToHandle(hUsbDev, 0x80);

								dataBuffer[0] =
								(((unsigned short)USB_getRemoteWakeupStat(
								hUsbDev))<<1)|
								((hUsbDev->cfgDescPtr[3]>>14)&0x0001);

								USB_postTransaction((CSL_UsbEpHandle)hEPx,
								                    2, dataBuffer,
								                    CSL_USB_IOFLAG_NONE);

								break;

							case CSL_USB_REQUEST_TYPE_INTERFACE_STATUS:

							    hEPx = USB_epNumToHandle(hUsbDev, 0x80);

								/* Return 0x0000 (reserved for future use) */
								dataBuffer[0] = 0x0000;

								USB_postTransaction((CSL_UsbEpHandle)hEPx, 2,
								                    dataBuffer,
								                    CSL_USB_IOFLAG_NONE);

								break;

							case CSL_USB_REQUEST_TYPE_ENDPOINT_STATUS:

								endpt = (usbSetup.wIndex) & 0xFF;

								hEPx   =  USB_epNumToHandle(hUsbDev, endpt);

								dataBuffer[0] =
								(unsigned short)USB_getEndptStall(
								                        (CSL_UsbEpHandle)hEPx,
								                         (CSL_Status *)&status);

								USB_postTransaction((CSL_UsbEpHandle)hEPx,
								                    2,
								                    dataBuffer,
								                    CSL_USB_IOFLAG_NONE);
								break;

							default:
								status =
								      USB_stallEndpt((CSL_UsbEpHandle)hEp[0]);

								break;
						}

						break;

					case CSL_USB_SET_ADDRESS :

						devAddr = usbSetup.wValue;

						usbRegisters->PERI_CSR0_INDX |=
						          (CSL_USB_PERI_CSR0_INDX_SERV_RXPKTRDY_MASK |
								   CSL_USB_PERI_CSR0_INDX_DATAEND_MASK);

						break;

					default:

						status = USB_stallEndpt((CSL_UsbEpHandle)hEp[0]);

						break;
				}
			}
			else
			{
				if(usbSetup.bRequest == 0x05)
				{
					USB_setDevAddr(hUsbDev, devAddr);
				}
			}

			usbRegisters->INDEX_TESTMODE  = saveIndex;
		}
	}

	/* Check Data Out Ready */
	if(hUsbDev->dwIntSourceL & CSL_USB_RX_INT_EP1)
	{
	    intEp = CSL_USB_RX_INT_EP1;

		hEPx = USB_epNumToHandle(hUsbDev, CSL_USB_EP1);

		if (USB_isValidDataInFifoOut(&hUsbDev->pEpStatus[CSL_USB_EP1]))
		{
			usb_income_num_bytes_ep1 =
			              USB_getDataCountReadFromFifo((CSL_UsbEpHandle)hEPx);
		}

		gUsbConfig.rxIntCallback(hEPx,
		                         ((CSL_UsbEpHandle)hEPx)->epNum,
		                         usb_income_num_bytes_ep1);
	}

	if(hUsbDev->dwIntSourceL & CSL_USB_RX_INT_EP2)
	{
	    intEp = CSL_USB_RX_INT_EP2;

		hEPx = USB_epNumToHandle(hUsbDev, CSL_USB_EP2);

		if (USB_isValidDataInFifoOut(&hUsbDev->pEpStatus[CSL_USB_EP2]))
		{
			usb_income_num_bytes_ep2 = USB_getDataCountReadFromFifo(
			                                           (CSL_UsbEpHandle)hEPx);
		}

        gUsbConfig.rxIntCallback(hEPx,
                                 ((CSL_UsbEpHandle)hEPx)->epNum,
                                 usb_income_num_bytes_ep2);
	}

	if(hUsbDev->dwIntSourceL & CSL_USB_RX_INT_EP3)
	{
	    intEp = CSL_USB_RX_INT_EP3;

		hEPx = USB_epNumToHandle(hUsbDev, CSL_USB_EP3);

		if (USB_isValidDataInFifoOut(&hUsbDev->pEpStatus[CSL_USB_EP3]))
		{
			usb_income_num_bytes_ep3 = USB_getDataCountReadFromFifo(
			                                           (CSL_UsbEpHandle)hEPx);
		}

        gUsbConfig.rxIntCallback(hEPx,
                                 ((CSL_UsbEpHandle)hEPx)->epNum,
                                 usb_income_num_bytes_ep3);
	}

	if(hUsbDev->dwIntSourceL & CSL_USB_RX_INT_EP4)
	{
	    intEp = CSL_USB_RX_INT_EP4;

		hEPx = USB_epNumToHandle(hUsbDev, CSL_USB_EP4);

		if (USB_isValidDataInFifoOut(&hUsbDev->pEpStatus[CSL_USB_EP4]))
		{
			usb_income_num_bytes_ep4 = USB_getDataCountReadFromFifo(
			                                           (CSL_UsbEpHandle)hEPx);
		}

        gUsbConfig.rxIntCallback(hEPx,
                                 ((CSL_UsbEpHandle)hEPx)->epNum,
                                 usb_income_num_bytes_ep4);
	}

	if(gUsbConfig.opMode == USB_OPMODE_DMA)
	{
		if(queuePend & 0x0400)
		{
			if(intEp == CSL_USB_RX_INT_EP1)
			{
			    USB_dmaRxStop(CSL_USB_EP1, dataBuffer,
			                  USB_HS_MAX_PACKET_SIZE, FALSE);

				hEPx = USB_epNumToHandle(hUsbDev, 0x1);

                gUsbConfig.rxCompleteCallback(hEPx,
                                              CSL_USB_EP1, 
                                              usb_income_num_bytes_ep1);
			}

			if(intEp == CSL_USB_RX_INT_EP2)
			{
			    USB_dmaRxStop(CSL_USB_EP2, dataBuffer,
			                  USB_HS_MAX_PACKET_SIZE, FALSE);

				hEPx = USB_epNumToHandle(hUsbDev, 0x2);

                gUsbConfig.rxCompleteCallback(hEPx,
                                              CSL_USB_EP2, 
                                              usb_income_num_bytes_ep2);
			}

			if(intEp == CSL_USB_RX_INT_EP3)
			{
			    USB_dmaRxStop(CSL_USB_EP3, dataBuffer,
			                  USB_HS_MAX_PACKET_SIZE, FALSE);

				hEPx = USB_epNumToHandle(hUsbDev, 0x3);

                gUsbConfig.rxCompleteCallback(hEPx,
                                              CSL_USB_EP3, 
                                              usb_income_num_bytes_ep3);
			}

			if(intEp == CSL_USB_RX_INT_EP4)
			{
			    USB_dmaRxStop(CSL_USB_EP4, dataBuffer,
			                  USB_HS_MAX_PACKET_SIZE, FALSE);

				hEPx = USB_epNumToHandle(hUsbDev, 0x4);

                gUsbConfig.rxCompleteCallback(hEPx,
                                              CSL_USB_EP4, 
                                              usb_income_num_bytes_ep4);
			}

			queuePend = 0;
		}
		else if (queuePend & 0x100)
		{
			if(intEp == CSL_USB_TX_INT_EP1)
			{
	            USB_dmaTxStop(CSL_USB_EP1);
			}

			if(intEp == CSL_USB_TX_INT_EP2)
			{
	            USB_dmaTxStop(CSL_USB_EP2);
			}

			if(intEp == CSL_USB_TX_INT_EP3)
			{
	            USB_dmaTxStop(CSL_USB_EP3);
			}

			if(intEp == CSL_USB_TX_INT_EP4)
			{
	            USB_dmaTxStop(CSL_USB_EP4);
			}

			queuePend = 0;
		}
	}

	/* Check Data In Ready */
	if(hUsbDev->dwIntSourceL & CSL_USB_TX_INT_EP1)
	{
	    intEp = CSL_USB_TX_INT_EP1;

		USB_flushFifo(CSL_USB_EP1, 1);

		hEPx = USB_epNumToHandle(hUsbDev, 0x81);

        gUsbConfig.txIntCallback(hEPx, ((CSL_UsbEpHandle)hEPx)->epNum, usb_income_num_bytes_ep1);
	}

	if(hUsbDev->dwIntSourceL & CSL_USB_TX_INT_EP2)
	{
	    intEp = CSL_USB_TX_INT_EP2;

		USB_flushFifo(CSL_USB_EP2, 1);

		hEPx = USB_epNumToHandle(hUsbDev, 0x82);

        gUsbConfig.txIntCallback(hEPx, ((CSL_UsbEpHandle)hEPx)->epNum, usb_income_num_bytes_ep2);
	}

	if(hUsbDev->dwIntSourceL & CSL_USB_TX_INT_EP3)
	{
	    intEp = CSL_USB_TX_INT_EP3;

		USB_flushFifo(CSL_USB_EP3, 1);

		hEPx = USB_epNumToHandle(hUsbDev, 0x83);

        gUsbConfig.txIntCallback(hEPx, ((CSL_UsbEpHandle)hEPx)->epNum, usb_income_num_bytes_ep3);
	}

	if(hUsbDev->dwIntSourceL & CSL_USB_TX_INT_EP4)
	{
	    intEp = CSL_USB_TX_INT_EP4;

		USB_flushFifo(CSL_USB_EP4, 1);

		hEPx = USB_epNumToHandle(hUsbDev, 0x84);

        gUsbConfig.txIntCallback(hEPx, ((CSL_UsbEpHandle)hEPx)->epNum, usb_income_num_bytes_ep4);
	}

	/* Connect interrupt */
	if(hUsbDev->dwIntSourceH & CSL_USB_GBL_INT_DEVCONN)
	{
		status = USB_connectDev(hUsbDev);
	}

	/* Disconnect interrupt */
	if(hUsbDev->dwIntSourceH & CSL_USB_GBL_INT_DEVDISCONN)
	{
		status = USB_disconnectDev(hUsbDev);
		usbDevDisconnect = TRUE;
	}

	/* Suspend interrupt */
	if(hUsbDev->dwIntSourceH & CSL_USB_GBL_INT_SUSPEND)
	{
		status = USB_suspendDevice(hUsbDev);
	}

	if ((usbDevDisconnect == TRUE) &&
		(CSL_FEXT(usbRegisters->DEVCTL, USB_DEVCTL_VBUS) !=
	  	CSL_USB_DEVCTL_VBUS_ABOVEVBUSVALID))
	{
		while(CSL_FEXT(usbRegisters->DEVCTL, USB_DEVCTL_VBUS) !=
		         CSL_USB_DEVCTL_VBUS_ABOVEVBUSVALID);

		usbDevDisconnect = FALSE;

		USB_connectDev(hUsbDev);
	}

	hUsbDev->dwIntSourceL = 0;
	hUsbDev->dwIntSourceH = 0;

	CSL_FINS(usbRegisters->EOIR, USB_EOIR_EOI_VECTOR, CSL_USB_EOIR_RESETVAL);

	return(status);
}

/**
 *  \brief  Start transfer call back function
 *
 *  \param  vpContext - USB context structure
 *  \param  vpeps     - End point status structure pointer
 *
 *  \return CSL_Status
 */
int startTransferCallback(void *vpContext,
                          void *vpeps)
{
	pUsbContext      pContext;
	pUsbEpStatus     peps;
	pUsbTransfer     pTransfer;
	CSL_Status       status;

	status = CSL_SOK;

	pContext  = (pUsbContext)vpContext;
	peps      = (pUsbEpStatus)vpeps;

    if((pContext == NULL) || (peps == NULL))
    {
        return(CSL_ESYS_INVPARAMS);
	}

	if(!pContext->fMUSBIsReady)
	{
		return(CSL_ESYS_INVPARAMS);
	}

	/* The endpoint should be initialized */
	if(!peps->fInitialized)
	{
		return(CSL_ESYS_INVPARAMS);
	}

    pTransfer = peps->pTransfer;
    pTransfer->fComplete=FALSE;

	if(pTransfer->dwFlags == CSL_USB_OUT_TRANSFER)
	{
		if(peps->dwEndpoint == CSL_USB_EP0)
		{
			status = USB_processEP0Out(pContext);
		}
		else
		{
			status = USB_handleRx(pContext, peps->dwEndpoint);
		}
	}
	else if(pTransfer->dwFlags == CSL_USB_IN_TRANSFER)
	{
		if(peps->dwEndpoint == CSL_USB_EP0 )
		{
			status = USB_processEP0In(pContext);
		}
		else
		{
			status = USB_handleTx(pContext, peps->dwEndpoint);
		}
	}
	else
	{
		status = CSL_ESYS_INVPARAMS;
	}

	return(status);
}

/**
 *  \brief  Complete transfer call back function
 *
 *  \param  vpContext - USB context structure
 *  \param  vpeps     - End point status structure pointer
 *
 *  \return CSL_Status
 */
int completeTransferCallback(void *vpContext,
                             void *vpeps)
{
	pUsbEpStatus     peps;
	pUsbTransfer     pTransfer;
	USB_pipeHandle   hEPx;

	peps      = (pUsbEpStatus)vpeps;
    pTransfer = peps->pTransfer;

	if(sentLongEp0Pkt == 1)
	{
		sentLongEp0Pkt = 0;
	}

	if(pTransfer->ioFlags == CSL_USB_OUT_TRANSFER)
	{
	    hEPx = USB_epNumToHandle(hUsbDev, peps->dwEndpoint);

	    gUsbConfig.rxCompleteCallback(hEPx,
	                                  peps->dwEndpoint,
                                      pTransfer->cbTransferred);
	}

	return(CSL_SOK);
}

/**
 *  \brief  Function to get the pipe number
 *
 *  \param  epNum     - Pipe number
 *  \param  direction - Transfer direction, USB_IN or USB_OUT
 *
 *  \return CSL_Status
 */
static int getPipeNum(unsigned short epNum, unsigned short direction)
{
    int pipeNum;

    if(direction == USB_OUT)
	{
	    switch(epNum)
	    {
		    case 0:
			    pipeNum = CSL_USB_OUT_EP0;
				break;
			case 1:
			    pipeNum = CSL_USB_OUT_EP1;
				break;
		    case 2:
			    pipeNum = CSL_USB_OUT_EP2;
				break;
			case 3:
			    pipeNum = CSL_USB_OUT_EP3;
				break;
			case 4:
			    pipeNum = CSL_USB_OUT_EP4;
				break;
			default:
			    pipeNum = CSL_ESYS_FAIL;
				break;
		}
	}
	else if(direction == USB_IN)
	{
	    switch(epNum)
	    {
		    case 0:
			    pipeNum = CSL_USB_IN_EP0;
				break;
			case 1:
			    pipeNum = CSL_USB_IN_EP1;
				break;
		    case 2:
			    pipeNum = CSL_USB_IN_EP2;
				break;
			case 3:
			    pipeNum = CSL_USB_IN_EP3;
				break;
			case 4:
			    pipeNum = CSL_USB_IN_EP4;
				break;
			default:
			    pipeNum = CSL_ESYS_FAIL;
				break;
		}
	}
	else
	{
	    pipeNum = CSL_ESYS_FAIL;
	}

	return(pipeNum);
}

/**
 *  \brief  Function to get the end point number
 *
 *  \param  pipeNum   - Pipe number
 *
 *  \return CSL_Status
 */
static int getEndPoint(unsigned short pipeNum)
{
	int retEndPt;

	switch(pipeNum)
	{
		case CSL_USB_IN_EP1:
		case CSL_USB_OUT_EP1:
			retEndPt = CSL_USB_EP1;
			break;

		case CSL_USB_IN_EP2:
		case CSL_USB_OUT_EP2:
			retEndPt = CSL_USB_EP2;
			break;

		case CSL_USB_IN_EP3:
		case CSL_USB_OUT_EP3:
			retEndPt = CSL_USB_EP3;
			break;

		case CSL_USB_IN_EP4:
		case CSL_USB_OUT_EP4:
			retEndPt = CSL_USB_EP4;
			break;

		default:
		   	retEndPt = CSL_ESYS_FAIL;
			break;
	}

	return(retEndPt);
}

/**
 *  \brief  USB delay function
 *
 *  \param  mSecs - Delay in millisecs
 *
 *  \return None
 */
static void USB_delay(unsigned long mSecs)
{
	volatile unsigned long delay;
	volatile unsigned long msecCount;
	volatile unsigned long sysClk;  /* System clock value in KHz */

	sysClk = getCpuClock();

	for (msecCount = 0; msecCount < mSecs; msecCount++)
	{
		for (delay = 0; delay < sysClk; delay++)
		{
			asm ("\tNOP");
		}
	}
}
