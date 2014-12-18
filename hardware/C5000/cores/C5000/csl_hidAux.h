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

/** @file csl_hidAux.h
 *
 *  @brief USB Hid Class functional layer Auxilliary header file
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 13-Dec-2012 Created
 * ============================================================================
 */

#ifndef _CSL_HIDCLASSAUX_H_
#define _CSL_HIDCLASSAUX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "csl_hid.h"
#include "csl_usbAux.h"

/** @addtogroup CSL_HID_FUNCTION
 @{ */

/** ============================================================================
 *   @n@b  HID_reqUnknown
 *
 *   @b Description
 *   @n This function handles the case where the request sent by the host is unknown
 *   unit number
 *
 *   @b Arguments
 *   @verbatim
            devNum       - USB device number
            usbSetup     - USb setup structure
            hInEp        - USB ISO In end point handle
            hOutEp       - USB ISO Out end point object
            pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends acknowledgement
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqUnknown(CSL_UsbDevHandle      devHandle,
                                 CSL_UsbSetupStruct    *usbSetup,
                                 CSL_UsbEpHandle       hInEp,
                                 CSL_UsbEpHandle       hOutEp,
                                 void                  *pHidObj)
{
	CSL_HidRequestRet    retStat;

	/* STALL the endpoint - the request is either not known or not supported */
	retStat = CSL_HID_REQUEST_STALL;

	return(retStat);
}

/** ============================================================================
 *   @n@b HID_lookupReqHandler
 *
 *   @b Description
 *   @n This functions maps the request sent by host to the Hid request table
 *   and returns the correspending request handler address
 *
 *   @b Arguments
 *   @verbatim
            request        -  Request sent by the host
            pUSB_ReqTable  -  Request table structure pointer
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  Request handler pointer
 *
 *   <b> Pre Condition </b>
 *   @n  Request table should be initialized and HID_Open function should be
 *       called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Returns the request handler pointer
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_HidRequestRet      (*fpRequestHandler)(CSL_HID_REQUEST_ARGS)
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);
     @endverbatim
 *  ============================================================================
 */
static inline
fpHID_REQ_HANDLER HID_lookupReqHandler(Uint16                 request,
                                     CSL_HidRequestStruct    *pUSB_ReqTable)
{
	Uint16    index;

	/* parse thru the end of request handler table */
	for(index = 0; pUSB_ReqTable[index].fpRequestHandler != NULL; index++)
	{
		/* if request handler exists return a pointer to the request handler routine */
		if(pUSB_ReqTable[index].request == request)
	  	{
			return(pUSB_ReqTable[index].fpRequestHandler);
	  	}
	}

	/* if request handler does not exist return a pointer to the USB_reqUnknown
	routine */
    //printf("unknown\n");
	return(HID_reqUnknown);
}

/** ============================================================================
 *   @n@b  HID_reqSetAddress
 *
 *   @b Description
 *   @n This function handles the request to set the device address
 *
 *   @b Arguments
 *   @verbatim
            devNum       - USB device number
            usbSetup     - USb setup structure
            hInEp        - USB ISO In end point handle
            hOutEp       - USB ISO Out end point object
            pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li                   CSL_HID_REQUEST_DONE - Request hadled successfully
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets the device address
 *
 *   @b Modifies
 *   @n USB FADDR_POWER register
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqSetAddress(CSL_UsbDevHandle      devHandle,
                                    CSL_UsbSetupStruct    *usbSetup,
                                    CSL_UsbEpHandle       hInEp,
                                    CSL_UsbEpHandle       hOutEp,
                                    void                  *pHidObj)
{
	CSL_FINS(usbRegisters->PERI_CSR0_INDX,
		 USB_PERI_CSR0_INDX_SERV_SETUPEND, TRUE);
	CSL_FINS(usbRegisters->PERI_CSR0_INDX,
		 USB_PERI_CSR0_INDX_DATAEND, TRUE);

    USB_setDevAddr(devHandle, (Uint16)(usbSetup->wValue));

    return(CSL_HID_REQUEST_DONE);
}

/** ============================================================================
 *   @n@b  HID_reqGetDescriptor
 *
 *   @b Description
 *   @n This function handles the request from host to get the descriptor
 *
 *   @b Arguments
 *   @verbatim
            CSL_HID_REQUEST_ARGS    - HID request arguments
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_GET_ACK  - Get acknowledgement for request\
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends the descriptor
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHID);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqGetDescriptor(CSL_UsbDevHandle      devHandle,
                                       CSL_UsbSetupStruct    *usbSetup,
                                       CSL_UsbEpHandle       hInEp,
                                       CSL_UsbEpHandle       hOutEp,
                                       void                  *pHidObj)
{
    Uint16    Desc_length;
    Uint16    incrPtr;
    Uint16    inOutFlag;
    char      *destPtr;
    pHidClassHandle       pHIDClassHdl;
    CSL_HidCtrlObject*    pCtrlHandle;

    pHIDClassHdl = (pHidClassHandle)(pHidObj);
    pCtrlHandle  = &pHIDClassHdl->ctrlHandle;
    destPtr      = NULL;

    switch(usbSetup->wValue >> CSL_HID_8BIT_SHIFT)
    {
        case CSL_USB_DEVICE_DESCRIPTOR_TYPE:
             Desc_length = pCtrlHandle->deviceDescr[1]&0xFF;
             destPtr     = (char *)&pCtrlHandle->deviceDescr[1];
             inOutFlag   = CSL_USB_IOFLAG_NONE;
             break;

        case CSL_USB_HID_DESCRIPTOR_TYPE:
		     inOutFlag = (CSL_USB_IOFLAG_LNK | CSL_USB_IOFLAG_CAT);
             Desc_length = pCtrlHandle->confDescr[10]&0xFF;
             destPtr     = (char *)&pCtrlHandle->confDescr[10];
             inOutFlag = CSL_USB_IOFLAG_NONE;

             if(Desc_length == usbSetup->wLength)
             {
                inOutFlag |= CSL_USB_IOFLAG_NOSHORT;
             }
             break;

        case CSL_USB_CONFIGURATION_DESCRIPTOR_TYPE:
             inOutFlag = (CSL_USB_IOFLAG_LNK | CSL_USB_IOFLAG_CAT);
             Desc_length = pCtrlHandle->confDescr[2]&0xFF;
             destPtr = (char *)&pCtrlHandle->confDescr[1];

             if(Desc_length == usbSetup->wLength)
             {
                inOutFlag |= CSL_USB_IOFLAG_NOSHORT;
             }
             break;

    	case CSL_USB_OTHERSPEED_CFG_DESCRIPTOR_TYPE:
             inOutFlag = (CSL_USB_IOFLAG_LNK | CSL_USB_IOFLAG_CAT);
             Desc_length = pCtrlHandle->osConfDescr[2]&0xFF;
             destPtr = (char *)&pCtrlHandle->osConfDescr[1];

             if(Desc_length == usbSetup->wLength)
             {
                inOutFlag |= CSL_USB_IOFLAG_NOSHORT;
             }
             break;

        case CSL_USB_STRING_DESCRIPTOR_TYPE:
//			if ((usbSetup->wValue&0x00FF)>3)
//	            return(CSL_HID_REQUEST_STALL);

                 /* strlen of the string requested */
			Desc_length = pCtrlHandle->strDescr[usbSetup->wValue&0x00FF][0]&0x00FF;
			destPtr = (char *)&(pCtrlHandle->strDescr[usbSetup->wValue&0x00FF][0]);
			inOutFlag = CSL_USB_IOFLAG_NONE;
            break;

        case CSL_USB_INTERFACE_DESCRIPTOR_TYPE:
             inOutFlag = (CSL_USB_IOFLAG_LNK | CSL_USB_IOFLAG_CAT);
             Desc_length = pCtrlHandle->confDescr[9]&0xFF;
             destPtr = (char *)&pCtrlHandle->confDescr[9];
             inOutFlag = CSL_USB_IOFLAG_NONE;

             if(Desc_length == usbSetup->wLength)
             {
                inOutFlag |= CSL_USB_IOFLAG_NOSHORT;
             }
        	break;

        case CSL_USB_ENDPOINT_DESCRIPTOR_TYPE:
             inOutFlag = (CSL_USB_IOFLAG_LNK | CSL_USB_IOFLAG_CAT);
             Desc_length = pCtrlHandle->confDescr[18]&0xFF;
             destPtr = (char *)&pCtrlHandle->confDescr[18];
             inOutFlag = CSL_USB_IOFLAG_NONE;

             if(Desc_length == usbSetup->wLength)
             {
                inOutFlag |= CSL_USB_IOFLAG_NOSHORT;
             }
        	break;

        case CSL_USB_DEVICE_QUAL_DESCRIPTOR_TYPE:
            Desc_length = pCtrlHandle->deviceQualifierDescr[1] & 0xFF;
            destPtr = (char *)&pCtrlHandle->deviceQualifierDescr[1];
            inOutFlag = CSL_USB_IOFLAG_NONE;
            break;

        case CSL_USB_HID_REPORT_DESCRIPTOR_TYPE:
            Desc_length = pCtrlHandle->hidClassHidReportDescrLen;
            destPtr = (char *)&pCtrlHandle->hidClassHidReportDescr[1];
            inOutFlag = CSL_USB_IOFLAG_NONE;
            break;

        default:
            return(CSL_HID_REQUEST_STALL);
    }

	if (Desc_length == 0)
	{
		return(CSL_HID_REQUEST_STALL);
	}
	else if ((usbSetup->wLength <= (Uint16)Desc_length) && (Desc_length <= 64))
	{
		USB_postTransaction(hInEp, usbSetup->wLength,
						    (void*)destPtr,
						    CSL_USB_IN_TRANSFER);
	}
    else if (usbSetup->wLength > ((Uint16)(Desc_length)) && Desc_length <= 64)
	{
		USB_postTransaction(hInEp, Desc_length,
						    (void*)destPtr,
						    CSL_USB_IN_TRANSFER);
	}
    else if (usbSetup->wLength <= 64 && Desc_length > 64)
	{
		USB_postTransaction(hInEp, usbSetup->wLength,
						    (void*)destPtr,
						    CSL_USB_IN_TRANSFER);
	}
    else if ((usbSetup->wLength > 64) && (Desc_length > 64))
	{
		incrPtr = 0;
		USB_postTransaction(hInEp, 64,
						    (void*)destPtr,
						    CSL_USB_IN_TRANSFER);

		if (usbSetup->wLength > ((Uint16)Desc_length))
		{
			Desc_length = Desc_length - 64;
		}
		else
		{
			Desc_length = usbSetup->wLength - 64;
		}

		incrPtr = 64;

		while (Desc_length > 0)
		{
			if (Desc_length > 64)
			{
				USB_postTransaction(hInEp, 64,
									(void*)(destPtr + incrPtr),
									CSL_USB_IN_TRANSFER);
				incrPtr += 64;
				Desc_length -= 64;
			}
			else
			{
				USB_postTransaction(hInEp, Desc_length,
									(void*)(destPtr + incrPtr),
									CSL_USB_IN_TRANSFER);
				Desc_length = 0;
			}
		}
	}
    else
    {
		return(CSL_HID_REQUEST_STALL);
	}

    return(CSL_HID_REQUEST_GET_ACK);
}

/** ============================================================================
 *   @n@b  HID_reqSetConfiguration
 *
 *   @b Description
 *   @n This function handles the request to set the device configuration
 *
 *   @b Arguments
 *   @verbatim
            devNum       - USB device number
            usbSetup     - USb setup structure
            hInEp        - USB ISO In end point handle
            hOutEp       - USB ISO Out end point object
            pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_SEND_ACK - Send acknowledgement for request
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets the configuration
 *
 *   @b Modifies
 *   @n USB registers
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqSetConfiguration(CSL_UsbDevHandle      devHandle,
                                          CSL_UsbSetupStruct    *usbSetup,
                                          CSL_UsbEpHandle       hInEp,
                                          CSL_UsbEpHandle       hOutEp,
                                          void                  *pHidObj)
{
	CSL_HidRequestRet    retStat;

	pHidClassHandle      pHidClassHdl;
	CSL_HidCtrlObject    *pCtrlHandle;

	pHidClassHdl = (pHidClassHandle)(pHidObj);
	pCtrlHandle  = &pHidClassHdl->ctrlHandle;

	if((usbSetup->wValue == FALSE) || (usbSetup->wValue == TRUE))
	{
		pCtrlHandle->curConfigStat = usbSetup->wValue;

		USB_setConfiguration(devHandle, usbSetup->wValue);

		retStat   = CSL_HID_REQUEST_SEND_ACK;
	}
	else
	{
		/* configuration not supported, STALL the endpoint */
		retStat = CSL_HID_REQUEST_STALL;
	}

	return(retStat);
}

/** ============================================================================
 *   @n@b  HID_reqClearFeature
 *
 *   @b Description
 *   @n This function handles the request to clear the feature set
 *
 *   @b Arguments
 *   @verbatim
            devNum       - USB device number
            usbSetup     - USb setup structure
            hInEp        - USB ISO In end point handle
            hOutEp       - USB ISO Out end point object
            pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_SEND_ACK - Send acknowledgement for request
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Clears the feature
 *
 *   @b Modifies
 *   @n USB registers
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqClearFeature(CSL_UsbDevHandle      devHandle,
                                      CSL_UsbSetupStruct    *usbSetup,
                                      CSL_UsbEpHandle       hInEp,
                                      CSL_UsbEpHandle       hOutEp,
                                      void                  *pHidObj)
{
	CSL_HidRequestRet    retStat;
	CSL_UsbEpHandle      hEPx;

	retStat = CSL_HID_REQUEST_SEND_ACK;

	switch(usbSetup->wValue)
	{
		case CSL_USB_FEATURE_ENDPOINT_STALL:
		  	hEPx = devHandle->hEpHandleArray[3];
			USB_clearEndptStall(hEPx);
			break;

		case CSL_USB_FEATURE_REMOTE_WAKEUP:
			USB_setRemoteWakeup(devHandle, (CSL_UsbBoolean)FALSE);
		 	break;

		default:
		    /* Unsupported Feature. STALL the endpoint */
			retStat = CSL_HID_REQUEST_STALL;
			break;
	}

	return(retStat);
}

/** ============================================================================
 *   @n@b  HID_reqGetStatus
 *
 *   @b Description
 *   @n This function handles the get status request from host
 *
 *   @b Arguments
 *   @verbatim
            devNum       - USB device number
            usbSetup     - USb setup structure
            hInEp        - USB ISO In end point handle
            hOutEp       - USB ISO Out end point object
            pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_GET_ACK  - Get acknowledgement for request
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends the status
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqGetStatus(CSL_UsbDevHandle      devHandle,
                                   CSL_UsbSetupStruct    *usbSetup,
                                   CSL_UsbEpHandle       hInEp,
                                   CSL_UsbEpHandle       hOutEp,
                                   void                  *pHidObj)
{
	CSL_HidRequestRet     retStat;
	pHidClassHandle       pHidClassHdl;
	CSL_HidCtrlObject     *pCtrlHandle;
	CSL_UsbEpHandle       hEPx;
	CSL_Status            status;

	pHidClassHdl = (pHidClassHandle)(pHidObj);
	pCtrlHandle  = &pHidClassHdl->ctrlHandle;
	retStat      = CSL_HID_REQUEST_GET_ACK;

	pCtrlHandle->ctrlBuffer[0] = 0x00;

	switch(usbSetup->bmRequestType - CSL_HID_REQUEST_TYPE_BASE)
	{
		/* Device Status to be returned */
		case CSL_HID_REQUEST_TYPE_DEVICE_STATUS:
			pCtrlHandle->ctrlBuffer[0] =
                (((Uint16)USB_getRemoteWakeupStat(devHandle))<<1) |
                0;//CSL_HID_CURRDEV_STAT;
			USB_postTransaction(hInEp, 2, &pCtrlHandle->ctrlBuffer,
			                    CSL_USB_IOFLAG_NONE);
			break;

		/* Interface status is to be returned */
		case CSL_HID_REQUEST_TYPE_INTERFACE_STATUS:
			//pCtrlHandle->ctrlBuffer[1] = CSL_HID_CURRDEV_STAT;
			pCtrlHandle->ctrlBuffer[0] = 0x0; /* request to interface returns 0 */
			USB_postTransaction(hInEp, 2, &pCtrlHandle->ctrlBuffer,
			                    CSL_USB_IOFLAG_NONE);
			break;

		/* Endpoint status to be returned */
		case CSL_HID_REQUEST_TYPE_EP_STATUS:
			hEPx   =  devHandle->hEpHandleArray[3];
			pCtrlHandle->ctrlBuffer[0] = (Uint16)USB_getEndptStall(hEPx,
			                                                       &status);
			USB_postTransaction(hInEp, 2, &pCtrlHandle->ctrlBuffer,
			                    CSL_USB_IOFLAG_NONE);
			break;

		default:
			/* STALL the endpoint */
			retStat = CSL_HID_REQUEST_STALL;
			break;
	}

	return(retStat);
}

/** ============================================================================
 *   @n@b  HID_reqSetFeature
 *
 *   @b Description
 *   @n This function handles the request from host to set feature
 *
 *   @b Arguments
 *   @verbatim
            devNum       - USB device number
            usbSetup     - USb setup structure
            hInEp        - USB ISO In end point handle
            hOutEp       - USB ISO Out end point object
            pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_GET_ACK  - Get acknowledgement for request
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sets the feature
 *
 *   @b Modifies
 *   @n USB regiters
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqSetFeature(CSL_UsbDevHandle      devHandle,
                                    CSL_UsbSetupStruct    *usbSetup,
                                    CSL_UsbEpHandle       hInEp,
                                    CSL_UsbEpHandle       hOutEp,
                                    void                  *pHidObj)
{
	CSL_HidRequestRet    retStat;
	CSL_UsbEpHandle      hEPx;

	retStat = CSL_HID_REQUEST_SEND_ACK;

	switch(usbSetup->wValue)
	{
		case CSL_USB_FEATURE_ENDPOINT_STALL:
			/* updated set and clear endpoint stall to work with logical endpoint num */
			hEPx = devHandle->hEpHandleArray[3];
			USB_stallEndpt(hEPx);
			break;

		case CSL_USB_FEATURE_REMOTE_WAKEUP:
			USB_setRemoteWakeup(devHandle, (CSL_UsbBoolean)TRUE);
			break;

		default:
			/* Feature not supported, STALL the endpoint */
			retStat = CSL_HID_REQUEST_STALL;
			break;
	}

  return(retStat);
}

/** ============================================================================
 *   @n@b  HID_reqGetConfiguration
 *
 *   @b Description
 *   @n This function handles the request from host to get configuration
 *
 *   @b Arguments
 *   @verbatim
            devNum       - USB device number
            usbSetup     - USb setup structure
            hInEp        - USB ISO In end point handle
            hOutEp       - USB ISO Out end point object
            pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_GET_ACK  - Get acknowledgement for request
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends the configuration
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqGetConfiguration(CSL_UsbDevHandle      devHandle,
                                          CSL_UsbSetupStruct    *usbSetup,
                                          CSL_UsbEpHandle       hInEp,
                                          CSL_UsbEpHandle       hOutEp,
                                          void                  *pHidObj)
{
	pHidClassHandle       pHidClassHdl;
	CSL_HidCtrlObject*    pCtrlHandle;

	pHidClassHdl = (pHidClassHandle)(pHidObj);
	pCtrlHandle  = &pHidClassHdl->ctrlHandle;

	/* Send the current Configuration Value */
	pCtrlHandle->ctrlBuffer[0] = pCtrlHandle->curConfigStat;
	USB_postTransaction(hInEp, 1, (void*)&pCtrlHandle->ctrlBuffer,
				        CSL_USB_IN_TRANSFER);//CSL_USB_IOFLAG_NONE | CSL_USB_IOFLAG_NOSHORT);

	return(CSL_HID_REQUEST_GET_ACK);
}

/** ============================================================================
 *   @n@b  HID_reqGetMaxLUN
 *
 *   @b Description
 *   @n This function handles the request from host to send maximum logical
 *   unit number
 *
 *   @b Arguments
 *   @verbatim
             devNum       - USB device number
             usbSetup     - USb setup structure
             hInEp        - USB ISO In end point handle
             hOutEp       - USB ISO Out end point object
             pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_GET_ACK  - Get acknowledgement for request\
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends the max lun number
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqGetMaxLUN(CSL_UsbDevHandle      devHandle,
                                   CSL_UsbSetupStruct    *usbSetup,
                                   CSL_UsbEpHandle       hInEp,
                                   CSL_UsbEpHandle       hOutEp,
                                   void                  *pHidObj)
{
	pHidClassHandle       pHidClassHdl;
	CSL_HidCtrlObject*    pCtrlHandle;
	CSL_HidRequestRet     retStat;

	pHidClassHdl = (pHidClassHandle)(pHidObj);
	pCtrlHandle  = &pHidClassHdl->ctrlHandle;
	pCtrlHandle->ctrlBuffer[1] = pHidClassHdl->hidHandle.noOfLun;

	if(pHidClassHdl->hidHandle.noOfLun > 0)
	{
		USB_postTransaction(hInEp, 1, &pCtrlHandle->ctrlBuffer[0],
		                    CSL_USB_IOFLAG_NONE);

		/*Receive a 0 length packet for acknowledgement */
		retStat = CSL_HID_REQUEST_GET_ACK;
	}
	else
	{
		retStat = CSL_HID_REQUEST_STALL;
	}

	return (retStat);
}

/** ============================================================================
 *   @n@b  HID_reqSetInterface
 *
 *   @b Description
 *   @n This function handles the request from host to set interafce
 *   unit number
 *
 *   @b Arguments
 *   @verbatim
             devNum       - USB device number
             usbSetup     - USb setup structure
             hInEp        - USB ISO In end point handle
             hOutEp       - USB ISO Out end point object
             pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_SEND_ACK - Send acknowledgement for request
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends acknowledgement
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqSetInterface(CSL_UsbDevHandle      devHandle,
                                      CSL_UsbSetupStruct    *usbSetup,
                                      CSL_UsbEpHandle       hInEp,
                                      CSL_UsbEpHandle       hOutEp,
                                      void                  *pHidObj)
{
    CSL_HidRequestRet    retStat;

    retStat     = CSL_HID_REQUEST_SEND_ACK;

    if ((usbSetup->wValue == 0) &&
        (usbSetup->wIndex == 0) &&
        (usbSetup->wLength == 0))
    {
        CSL_FINS(usbRegisters->PERI_CSR0_INDX,
				 USB_PERI_CSR0_INDX_DATAEND, TRUE);

		retStat = CSL_HID_REQUEST_SEND_ACK;
    }
    else
    {
        /* Interface not supported, STALL the endpoint */
        retStat = CSL_HID_REQUEST_STALL;
    }

    return(retStat);
}

/** ============================================================================
 *   @n@b  HID_reqGetInterface
 *
 *   @b Description
 *   @n This function handles the request from host to get interafce
 *   unit number
 *
 *   @b Arguments
 *   @verbatim
             devNum       - USB device number
             usbSetup     - USb setup structure
             hInEp        - USB ISO In end point handle
             hOutEp       - USB ISO Out end point object
             pHidObj       - USB Hid Class object
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li        CSL_HID_REQUEST_GET_ACK  - Get acknowledgement for request\
 *   @li        CSL_HID_REQUEST_STALL    - Request stall signal (Error)
 *
 *   <b> Pre Condition </b>
 *   @n  HID_lookupReqHandler should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Sends interface info
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
             CSL_HidInitStructApp   hidAppHandle;
             CSL_HidObject          *phidHandle;
             CSL_HidCtrlObject      *pCtrlHandle;
             CSL_UsbEpHandle        hUbOutEp;
             Uint16                 lunNum;
             Uint16                 hidAppBuffer[420];
             CSL_Status             status;
             Uint16                 request;

             // Assign values to all the members in hidAppHandle struct
             hidAppHandle.pHidObj = &hidAppBuffer[0];
             .....
             .....
             status = HID_Open(&hidAppHandle);
             ....
             ....
             pCtrlHandle->fpRequestHandler = HID_lookupReqHandler(request,
                                                       pCtrlHandle->hidReqTable);

             pCtrlHandle->fpRequestHandler(pCtrlHandle->devNum,
                                           &pCtrlHandle->usbSetup,hCtrlEpIn,hCtrlEpOut,pHidObj);
     @endverbatim
 *  ============================================================================
 */
static inline
CSL_HidRequestRet HID_reqGetInterface(CSL_UsbDevHandle      devHandle,
                                      CSL_UsbSetupStruct    *usbSetup,
                                      CSL_UsbEpHandle       hInEp,
                                      CSL_UsbEpHandle       hOutEp,
                                      void                  *pHidObj)
{
	pHidClassHandle       pHidClassHdl;
	CSL_HidCtrlObject     *pCtrlHandle;
	CSL_HidRequestRet     retStat;

	pHidClassHdl = (pHidClassHandle)(pHidObj);
	pCtrlHandle  = &pHidClassHdl->ctrlHandle;
	retStat      = CSL_HID_REQUEST_GET_ACK;

	/* Compare the Interface with the bNumInterfaces byte of Configuration Descriptor */
    if ((usbSetup->wValue == 0) &&
        (usbSetup->wIndex == 0) &&
        (usbSetup->wLength == 0))
    {
		/* Send the current Interface Value */
		pCtrlHandle->ctrlBuffer[1] = 0;
		USB_postTransaction(hInEp, 1, &pCtrlHandle->ctrlBuffer[0],
		  				    CSL_USB_IOFLAG_NONE);
	}
	else
	{
		/*  Interface specified doent exist, STALL the endpoint */
		retStat = CSL_HID_REQUEST_STALL;
	}

	return retStat;
}

/**
@} */

#ifdef __cplusplus
}
#endif

#endif    // _CSL_HIDCLASSAUX_H_

