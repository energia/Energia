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

/** @file csl_cdcAux.h
 *
 *  @brief USB CDC functional layer Auxiliary header file
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 02-May-2011 Created
 * 06-Jul-2011 CSL v2.50 release
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */

#ifndef _CSL_CDCAUX_H_
#define _CSL_CDCAUX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "csl_usbAux.h"
#include "csl_cdc.h"

#include <stdio.h>

/** @addtogroup CSL_CDC_FUNCTION
 @{ */

/** ============================================================================
 *   @n@b  CDC_reqSetAddress
 *
 *   @b Description
 *   @n This function handles the request to set the device address
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                   CSL_CDC_REQUEST_DONE - Request handled successfully
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets the device address
 *
 *   @b Modifies
 *   @n USB FADDR_POWER register
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqSetAddress(CSL_UsbDevHandle      devHandle,
                                    CSL_UsbSetupStruct    *usbSetup,
                                    CSL_UsbEpHandle       hInEp,
                                    CSL_UsbEpHandle       hOutEp,
                                    void                  *pCdc)
{
    USB_setDevAddr(devHandle, (Uint16)(usbSetup->wValue));

    return(CSL_CDC_REQUEST_DONE);
}

/** ============================================================================
 *   @n@b  CDC_reqSetConfiguration
 *
 *   @b Description
 *   @n This function handles the request to set the device configuration
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_CDC_REQUEST_SEND_ACK - Send acknowledgement for request
 *   @li        CSL_CDC_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets the configuration
 *
 *   @b Modifies
 *   @n USB registers
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqSetConfiguration(CSL_UsbDevHandle      devHandle,
                                          CSL_UsbSetupStruct    *usbSetup,
                                          CSL_UsbEpHandle       hInEp,
                                          CSL_UsbEpHandle       hOutEp,
                                          void                  *pCdc)
{
	CSL_CdcRequestRet    retStat;

	pCdcClassHandle      pCdcClassHdl;
	CSL_CdcCtrlObject    *pCtrlHandle;

	pCdcClassHdl = (pCdcClassHandle)(pCdc);
	pCtrlHandle  = &pCdcClassHdl->ctrlHandle;

	if((usbSetup->wValue == FALSE) || (usbSetup->wValue == TRUE))
	{
		pCtrlHandle->curConfigStat = usbSetup->wValue;

		USB_setConfiguration(devHandle,usbSetup->wValue);

		retStat   = CSL_CDC_REQUEST_SEND_ACK;
	}
	else
	{
		/* configuration not supported, STALL the endpoint */
		retStat = CSL_CDC_REQUEST_STALL;
	}

	return(retStat);
}

/** ============================================================================
 *   @n@b  CDC_reqClearFeature
 *
 *   @b Description
 *   @n This function handles the request to clear the feature set
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_CDC_REQUEST_SEND_ACK - Send acknowledgement for request
 *   @li        CSL_CDC_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Clears the feature
 *
 *   @b Modifies
 *   @n USB registers
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqClearFeature(CSL_UsbDevHandle      devHandle,
                                      CSL_UsbSetupStruct    *usbSetup,
                                      CSL_UsbEpHandle       hInEp,
                                      CSL_UsbEpHandle       hOutEp,
                                      void                  *pCdc)
{
	CSL_CdcRequestRet    retStat;
	CSL_UsbEpHandle      hEPx;
	Uint16               endpt;  /* this is USB logical endpoint */

	retStat = CSL_CDC_REQUEST_SEND_ACK;

	switch(usbSetup->wValue)
	{
		case CSL_USB_FEATURE_ENDPOINT_STALL:
		  	endpt = (usbSetup->wIndex) & CSL_CDC_8BIT_MASK;
		  	hEPx = USB_epNumToHandle(devHandle, endpt);
			USB_clearEndptStall(hEPx);
			break;

		case CSL_USB_FEATURE_REMOTE_WAKEUP:
			USB_setRemoteWakeup(devHandle, (CSL_UsbBoolean)FALSE);
		 	break;

		default:
		    /* Unsupported Feature. STALL the endpoint */
			retStat = CSL_CDC_REQUEST_STALL;
			break;
	}

	return(retStat);
}

/** ============================================================================
 *   @n@b  CDC_reqGetStatus
 *
 *   @b Description
 *   @n This function handles the get status request from host
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_CDC_REQUEST_GET_ACK  - Get acknowledgement for request
 *   @li        CSL_CDC_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends the status
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqGetStatus(CSL_UsbDevHandle      devHandle,
                                   CSL_UsbSetupStruct    *usbSetup,
                                   CSL_UsbEpHandle       hInEp,
                                   CSL_UsbEpHandle       hOutEp,
                                   void                  *pCdc)
{
	CSL_CdcRequestRet     retStat;
	pCdcClassHandle       pCdcClassHdl;
	CSL_CdcCtrlObject     *pCtrlHandle;
	CSL_UsbEpHandle       hEPx;
	CSL_Status            status;
	Uint16                endpt;   /* this is USB logical endpoint */

	pCdcClassHdl = (pCdcClassHandle)(pCdc);
	pCtrlHandle  = &pCdcClassHdl->ctrlHandle;
	retStat      = CSL_CDC_REQUEST_GET_ACK;

	switch(usbSetup->bmRequestType - CSL_CDC_REQUEST_TYPE_BASE)
	{
		/* Device Status to be returned */
		case CSL_CDC_REQUEST_TYPE_DEVICE_STATUS:
			pCtrlHandle->ctrlBuffer[0] =
			(((Uint16)USB_getRemoteWakeupStat(devHandle))<<1) |
			 CSL_CDC_CURRDEV_STAT;
			USB_postTransaction(hInEp, 2, &pCtrlHandle->ctrlBuffer,
			                    CSL_USB_IOFLAG_NONE);
			break;

		/* Interface status is to be returned */
		case CSL_CDC_REQUEST_TYPE_INTERFACE_STATUS:
			pCtrlHandle->ctrlBuffer[0] = CSL_CDC_CURRDEV_STAT;
			USB_postTransaction(hInEp, 2, &pCtrlHandle->ctrlBuffer,
			                    CSL_USB_IOFLAG_NONE);
			break;

		/* Endpoint status to be returned */
		case CSL_CDC_REQUEST_TYPE_EP_STATUS:

			endpt  =  usbSetup->wIndex & 0xFF;
			hEPx   =  USB_epNumToHandle(devHandle, endpt);
			pCtrlHandle->ctrlBuffer[0] = (Uint16)USB_getEndptStall(hEPx,
			                                                       &status);
			USB_postTransaction(hInEp, 2, &pCtrlHandle->ctrlBuffer,
			                    CSL_USB_IOFLAG_NONE);
			break;

		default:
			/* STALL the endpoint */
			retStat = CSL_CDC_REQUEST_STALL;
			break;
	}

	return(retStat);
}

/** ============================================================================
 *   @n@b  CDC_reqSetFeature
 *
 *   @b Description
 *   @n This function handles the request from host to set feature
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_CDC_REQUEST_GET_ACK  - Get acknowledgement for request
 *   @li        CSL_CDC_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets the feature
 *
 *   @b Modifies
 *   @n USB regiters
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqSetFeature(CSL_UsbDevHandle      devHandle,
                                    CSL_UsbSetupStruct    *usbSetup,
                                    CSL_UsbEpHandle       hInEp,
                                    CSL_UsbEpHandle       hOutEp,
                                    void                  *pCdc)
{
	CSL_CdcRequestRet    retStat;
	CSL_UsbEpHandle      hEPx;
	Uint16               endpt;        /* this is USB logical endpoint */

	retStat = CSL_CDC_REQUEST_SEND_ACK;

	switch(usbSetup->wValue)
	{
		case CSL_USB_FEATURE_ENDPOINT_STALL:
			/* updated set and clear endpoint stall to work with logical endpoint num */
			endpt = (usbSetup->wIndex) & CSL_CDC_8BIT_MASK;
			hEPx = USB_epNumToHandle(devHandle, endpt);
			USB_stallEndpt(hEPx);
			break;

		case CSL_USB_FEATURE_REMOTE_WAKEUP:
			USB_setRemoteWakeup(devHandle, (CSL_UsbBoolean)TRUE);
			break;

		default:
			/* Feature not supported, STALL the endpoint */
			retStat = CSL_CDC_REQUEST_STALL;
			break;
	}

  return(retStat);
}

/** ============================================================================
 *   @n@b  CDC_reqGetConfiguration
 *
 *   @b Description
 *   @n This function handles the request from host to get configuration
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_CDC_REQUEST_GET_ACK  - Get acknowledgement for request
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends the configuration
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqGetConfiguration(CSL_UsbDevHandle      devHandle,
                                          CSL_UsbSetupStruct    *usbSetup,
                                          CSL_UsbEpHandle       hInEp,
                                          CSL_UsbEpHandle       hOutEp,
                                          void                  *pCdc)
{
	pCdcClassHandle       pCdcClassHdl;
	CSL_CdcCtrlObject*    pCtrlHandle;

	pCdcClassHdl = (pCdcClassHandle)(pCdc);
	pCtrlHandle  = &pCdcClassHdl->ctrlHandle;

	/* Send the current Configuration Value */
	pCtrlHandle->ctrlBuffer[1] = pCtrlHandle->curConfigStat;
	USB_postTransaction(hInEp, 1, (void*)&pCtrlHandle->ctrlBuffer,
				        CSL_USB_IOFLAG_NONE | CSL_USB_IOFLAG_NOSHORT);

	return(CSL_CDC_REQUEST_GET_ACK);
}


/** ============================================================================
 *   @n@b  CDC_reqGetMaxLUN
 *
 *   @b Description
 *   @n This function handles the request from host to send maximum logical
 *   unit number
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_CDC_REQUEST_GET_ACK  - Get acknowledgement for request\
 *   @li        CSL_CDC_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends the max lun number
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqGetMaxLUN(CSL_UsbDevHandle      devHandle,
                                   CSL_UsbSetupStruct    *usbSetup,
                                   CSL_UsbEpHandle       hInEp,
                                   CSL_UsbEpHandle       hOutEp,
                                   void                  *pCdc)
{
	pCdcClassHandle       pCdcClassHdl;
	CSL_CdcCtrlObject*    pCtrlHandle;
	CSL_CdcRequestRet     retStat;

	pCdcClassHdl = (pCdcClassHandle)(pCdc);
	pCtrlHandle  = &pCdcClassHdl->ctrlHandle;
	pCtrlHandle->ctrlBuffer[1] = pCdcClassHdl->cdcHandle.noOfPort;

	/*
	 * Verify the setup packet fields
	 * wValue - 0
     * wIndex - interface number, set 0
     * wLength - 1
     */
	if ((usbSetup->wIndex == 0) &&
	    (usbSetup->wLength == 1) &&
	    (usbSetup->wValue == 0))
	{
		USB_postTransaction(hInEp, 1, &pCtrlHandle->ctrlBuffer[0],
		                    CSL_USB_IOFLAG_NONE);

		/* Receive a 0 length packet for acknowledgement */
		retStat = CSL_CDC_REQUEST_GET_ACK;
	}
	else
	{
		retStat = CSL_CDC_REQUEST_STALL;
	}

	return (retStat);
}

/** ============================================================================
 *   @n@b  CDC_reqGetInterface
 *
 *   @b Description
 *   @n This function handles the request from host to get interface
 *   unit number
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_CDC_REQUEST_GET_ACK  - Get acknowledgement for request\
 *   @li        CSL_CDC_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends interface info
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqGetInterface(CSL_UsbDevHandle      devHandle,
                                      CSL_UsbSetupStruct    *usbSetup,
                                      CSL_UsbEpHandle       hInEp,
                                      CSL_UsbEpHandle       hOutEp,
                                      void                  *pCdc)
{
	pCdcClassHandle       pCdcClassHdl;
	CSL_CdcCtrlObject     *pCtrlHandle;
	CSL_CdcRequestRet     retStat;

	pCdcClassHdl = (pCdcClassHandle)(pCdc);
	pCtrlHandle  = &pCdcClassHdl->ctrlHandle;
	retStat      = CSL_CDC_REQUEST_GET_ACK;

	/* Compare the Interface with the bNumInterfaces byte of Configuration Descriptor */
	if(usbSetup->wIndex == 0)
	{
		/* Send the current Interface Value */
		pCtrlHandle->ctrlBuffer[1] = 0;
		USB_postTransaction(hInEp, 1, &pCtrlHandle->ctrlBuffer[0],
		  				    CSL_USB_IOFLAG_NONE);
	}
	else
	{
		/*  Interface specified doesn't exist, STALL the endpoint */
		retStat = CSL_CDC_REQUEST_STALL;
	}

	return retStat;
}

/** ============================================================================
 *   @n@b  CDC_reqSetInterface
 *
 *   @b Description
 *   @n This function handles the request from host to set interface
 *   unit number
 *
 *   @b Arguments
 *   @verbatim
            devNum   - USB device number
            usbSetup - USB setup structure pointer
            hInEp    - USB IN endpoint handle
            hOutEp   - USB OUT endpoint handle
            pCdc     - Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_CDC_REQUEST_SEND_ACK - Send acknowledgement for request
 *   @li        CSL_CDC_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  CDC_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends acknowledgement
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_CdcInitStructApp    cdcAppHandle;
             CSL_CdcObject           *pCdcHandle;
             CSL_CdcCtrlObject       *pCtrlHandle;
             CSL_UsbEpHandle         hUbOutEp;
             Uint16                  lunNum;
             Uint16                  cdcAppBuffer[420];
             CSL_Status              status;
             Uint16                  request;

             // Assign values to all the members in cdcAppHandle struct
             cdcAppHandle.pCdcObj = &cdcAppBuffer[0];
             .....
             .....
             status = CDC_Open(&cdcAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = CDC_lookupReqHandler(request,
                                                       pCtrlHandle->cdcReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pCDC);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_CdcRequestRet CDC_reqSetInterface(CSL_UsbDevHandle      devHandle,
                                      CSL_UsbSetupStruct    *usbSetup,
                                      CSL_UsbEpHandle       hInEp,
                                      CSL_UsbEpHandle       hOutEp,
                                      void                  *pCdc)
{
	CSL_CdcRequestRet    retStat;

	if(usbSetup->wIndex == 0)
	{
		if (usbSetup->wValue == 0)
		{
			USB_setConfiguration(devHandle,usbSetup->wValue);
			retStat = CSL_CDC_REQUEST_SEND_ACK;
		}
	}
	else
	{
		/* configuration not supported, STALL the endpoint */
		retStat = CSL_CDC_REQUEST_STALL;
	}

	return(retStat);
}


/**
@} */

#ifdef __cplusplus
}
#endif

#endif    // _CSL_CDCAUX_H_

