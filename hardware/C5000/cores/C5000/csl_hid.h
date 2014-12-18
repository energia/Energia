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

/** @file csl_hid.h
 *
 *  @brief USB HID Class functional layer API header file
 *
 *  Path: \(CSLPATH)\ inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 24-Dec-2012 Created
 * ============================================================================
 */

/** @defgroup CSL_HID_API HID
 *
 * @section Introduction
 *
 * @subsection xxx Overview
 * The USB Hid module provides a set of API’s that allow user Applications to
 * integrate support for the USB HID Class. The USB hid module takes
 * care of the communication between USB and the hid device.
 * Hid Class module implements interrupt mode of transfer for sending and
 * receiving data from the end points.
 *
 * @subsection References
 * USB Specification Ver 2.0
 * Universal Serial Bus Device Class Definition for Hid Devices Ver 1.0
 */

#ifndef _CSL_HID_CLASS_H_
#define _CSL_HID_CLASS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <cslr.h>
#include <csl_error.h>
#include <csl_types.h>
#include <cslr_usb.h>
#include <csl_usb.h>
#include <soc.h>
#include <csl_general.h>


/**
@defgroup CSL_HID_SYMBOL  USB HID Symbols Defined
@ingroup CSL_HID_API
*/
/**
@defgroup CSL_HID_DATASTRUCT  USB HID Data Structures
@ingroup CSL_HID_API
*/
/**
@defgroup CSL_HID_FUNCTION  USB HID Functions
@ingroup CSL_HID_API
*/
/**
@defgroup CSL_HID_ENUM USB HID Enumerated Data Types
@ingroup CSL_HID_API
*/


/*****************************************************************************\
          USB HID global macro declarations                                    *
\*****************************************************************************/
/**
@addtogroup CSL_HID_SYMBOL
@{
*/
/** \brief  USB HID Descriptor Type Values                                    */
/** USB HID device descriptor type macro                                      */
#define CSL_HID_DEVICE_DESCRIPTOR_TYPE                         (0x01)
/** USB HID configuration descriptor type macro                               */
#define CSL_HID_CONFIGURATION_DESCRIPTOR_TYPE                  (0x02)
/** USB HID string descriptor type macro                                      */
#define CSL_HID_STRING_DESCRIPTOR_TYPE                         (0x03)
/** USB HID interface descriptor type macro                                   */
#define CSL_HID_INTERFACE_DESCRIPTOR_TYPE                      (0x04)
/** USB HID end point descriptor type macro                                   */
#define CSL_HID_ENDPOINT_DESCRIPTOR_TYPE                       (0x05)
/** USB HID power descriptor type macro                                       */
#define CSL_HID_POWER_DESCRIPTOR_TYPE                          (0x06)
/** USB HID Human Interface Device descriptor type macro                      */
#define CSL_HID_DESCRIPTOR_TYPE                                (0x21)
/** USB HID Human Interface Device report descriptor type macro               */
#define CSL_HID_REPORT_DESCRIPTOR_TYPE                         (0x22)

/** \brief  USB HID Defined Feature selectors                                 */
/** Hid host request to set/clear end point stall                             */
#define CSL_HID_FEATURE_ENDPOINT_STALL                         (0x0000)
/** Hid host request to set/reset remote wakeup feature                       */
#define CSL_HID_FEATURE_REMOTE_WAKEUP                          (0x0001)

/** Maximum allowed length of device descriptor                              */
#define CSL_HID_DEVICE_DESCR_MAX_LEN                           (20)
/** Maximum allowed length of device qualifier descriptor                    */
#define CSL_HID_DEV_QUAL_DESCR_MAX_LEN                         (12)
/** Maximum allowed length of configuration descriptor                       */
//#define CSL_HID_CONFIG_DESCR_MAX_LEN                           (124)
#define CSL_HID_CONFIG_DESCR_MAX_LEN                           (400)
/** Maximum allowed length of interface descriptor                           */
#define CSL_HID_INTER_DESCR_MAX_LEN                            (12)
/** Maximum allowed length of string descriptor language Id                  */
#define CSL_HID_STRING_DESCR_LANGID_MAX_LEN                    (12)
/** Maximum allowed length of HID report descriptor                          */
#define CSL_HID_REPORT_DESCR_MAX_LEN                           (67+2)

/** Maximum allowed length of HID report descriptor                          */
#define CSL_HID_REPORT_DESCR_MAX_LEN_W   ((CSL_HID_REPORT_DESCR_MAX_LEN+1)/2)

/** HID Input report type (Get Report request)                               */
#define CSL_HID_INPUT_REPORT_TYPE                              (0x01)
/** HID Ouput report type (Get Report request)                               */
#define CSL_HID_OUTPUT_REPORT_TYPE                             (0x02)
/** HID Feature report type (Get Report request)                             */
#define CSL_HID_FEATURE_REPORT_TYPE                            (0x03)

/** \brief  USB HID status and size definitions                              */
/** HID verification passed                                                  */
#define CSL_HID_VERIFY_PASSED                                  (0x0)
/** HID verification failed                                                  */
#define CSL_HID_VERIFY_FAILED                                  (0x1)

/** HID logical unit is removable                                            */
#define CSL_HID_UNIT_REMOVEABLE                                (0x1)
/** Current USB device status                                                */
#define CSL_HID_CURRDEV_STAT                                   (0x01)
/** Current USB interface status                                             */
#define CSL_HID_CURRINTRF_STAT                                 (0x00)
/** No end point object is available                                         */
#define CSL_HID_NO_ENDPTOBJECT                                 (6)
/** Device descriptor length in words                                        */
#define CSL_HID_DEVDESC_LEN                                    (10)
/** Configuration descriptor length in words                                 */
#define CSL_HID_CONFDESC_LEN                                   (6)
/** Interface descriptor length in words                                     */
#define CSL_HID_MS_INTDESC_LEN                                 (6)
/** String descriptor length in words                                        */
#define CSL_HID_STRDESC_LANGID_LEN                             (4)
/** SCSI enquiry data length in words                                        */
#define CSL_HID_SCSI_INQUIRY_LEN                               (50)
/** Sense data length in words                                               */
#define CSL_HID_SENSEDATA_LEN                                  (15)
/** Maximum logical unit number                                              */
#define CSL_HID_LUN_MAX                                        (4)
/** Command block word size in words                                         */
#define CSL_HID_CBWSIZE                                        (17)
/** Command status word size in words                                        */
#define CSL_HID_CSWSIZE                                        (8)
/** HID read capacity                                                        */
#define CSL_HID_READCAP                                        (6)
/** Control buffer length in words                                           */
#define CSL_HID_CTRLBUFF_LEN                                   (5)
/** SCSI inquiry configuration length                                        */
#define CSL_HID_SCSI_INQUIRY_CONF_LEN                          (24)
/** Mass storage call definition macro                                       */
#define CSL_HID_DEVICE_CLASS_STORAGE                           (0x08)
/** SCSI data protect macro                                                  */
#define CSL_HID_SCSI_DATA_PROTECT                              (0x0007)
/** USB Hid Class specific request macro                                     */
#define CSL_HID_REQUEST_CLASS                                  (0x20)
/** Length of buffer to service get request from host                        */
#define CSL_HID_GET_BUF_LEN                                    (0x04)

/** Host request to set current                                              */
#define CSL_HID_REQUEST_SET_CUR                                (0x2001)
/** Host request to get current                                              */
#define CSL_HID_REQUEST_GET_CUR                                (0xA081)
/** Host request to set minimum                                              */
#define CSL_HID_REQUEST_SET_MIN                                (0x2002)
/** Host request to get minimum                                              */
#define CSL_HID_REQUEST_GET_MIN                                (0xA082)
/** Host request to set maximum                                              */
#define CSL_HID_REQUEST_SET_MAX                                (0x2003)
/** Host request to get maximum                                              */
#define CSL_HID_REQUEST_GET_MAX                                (0xA083)
/** Host request to set resolution                                           */
#define CSL_HID_REQUEST_SET_RES                                (0x2004)
/** Host request to get resolution                                           */
#define CSL_HID_REQUEST_GET_RES                                (0xA084)
/** Host request to get HID report using control transfer                    */
#define CSL_HID_REQUEST_HID_GET_REPORT                         (0xA001)
/** Host request to get idle rate from HID                                   */
#define CSL_HID_REQUEST_HID_GET_IDLE                           (0xA002)
/** Host request to get idle rate from HID                                   */
#define CSL_HID_REQUEST_HID_GET_PROTOCOL                       (0xA003)
/** Host request to send HID report using control transfer                   */
#define CSL_HID_REQUEST_HID_SET_REPORT                         (0x2009)
/** Host request to set HID idle rate                                        */
#define CSL_HID_REQUEST_HID_SET_IDLE                           (0x200A)
/** Host request to specify whether HID should use boot or report protocol   */
#define CSL_HID_REQUEST_HID_SET_PROTOCOL                       (0x200B)

/** \brief  Symbolic constants for USB HID requests                           */
/** Host request to get status                                               */
#define CSL_HID_REQUEST_GET_STATUS                              (0x8000)
/** Host request to clear feature                                            */
#define CSL_HID_REQUEST_CLEAR_FEATURE                           (0x0001)
/** Host request to set feature                                              */
#define CSL_HID_REQUEST_SET_FEATURE                             (0x0003)
/** Host request to set address                                              */
#define CSL_HID_REQUEST_SET_ADDRESS                             (0x0005)
/** Host request to get descriptor                                           */
#define CSL_HID_REQUEST_GET_DESCRIPTOR                          (0x8006)
/** Host request to set descriptor                                           */
#define CSL_HID_REQUEST_SET_DESCRIPTOR                          (0x0007)
/** Host request to get configuration                                        */
#define CSL_HID_REQUEST_GET_CONFIGURATION                       (0x8008)
/** Host request to set configuration                                        */
#define CSL_HID_REQUEST_SET_CONFIGURATION                       (0x0009)
/** Host request to get interface                                            */
#define CSL_HID_REQUEST_GET_INTERFACE                           (0x800A)
/** Host request to set interface                                            */
#define CSL_HID_REQUEST_SET_INTERFACE                           (0x000B)
/** Host request for the synchronization frame                               */
#define CSL_HID_REQUEST_SYNC_FRAME                              (0x800C)

/** Host request to get maximum logical unit number                          */
#define CSL_HID_REQUEST_GET_MAX_LUN                             (0xA0FE)
/** Base value for host request to get status                                */
#define CSL_HID_REQUEST_TYPE_BASE                               (0x80)
/** Host request to get device status                                        */
#define CSL_HID_REQUEST_TYPE_DEVICE_STATUS                      (0x0)
/** Host request to get interface status                                     */
#define CSL_HID_REQUEST_TYPE_INTERFACE_STATUS                   (0x1)
/** Host request to get end point status                                     */
#define CSL_HID_REQUEST_TYPE_EP_STATUS                          (0x2)

/** \brief  HID Status query API return values                               */
/** Return value for USB device suspended case                               */
#define CSL_HID_DEVICE_SUSPENDED                                (0x01)
/** Return value for USB device not suspended case                           */
#define CSL_HID_DEVICE_NOT_SUSPENDED                            (0x0)
/** Return value for Logical unit locked case                                */
#define CSL_HID_LUN_LOCKED                                      (0x01)
/** Return value for Logical unit not locked case                            */
#define CSL_HID_LUN_NOT_LOCKED                                  (0x0)
/** Return value for activity present case                                   */
#define CSL_HID_ACTIVITY_PRESENT                                (0x01)
/** Return value for activity not present case                               */
#define CSL_HID_ACTIVITY_NOT_PRESENT                            (0x0)

/** HID 16 bit Mask value                                                    */
#define CSL_HID_16BIT_MASK                                      (0xFFFF)
/** HID 16 bit shift value                                                   */
#define CSL_HID_16BIT_SHIFT                                     (16)

/** HID 24 bit shift value                                                   */
#define CSL_HID_24BIT_SHIFT                                     (24)

/** HID 8 bit Mask value                                                     */
#define CSL_HID_8BIT_MASK                                       (0xFF)
/** HID 8 bit Mask value                                                     */
#define CSL_HID_8BIT_HIGH_MASK                                  (0xFF00)
/** HID 8 bit shift value                                                    */
#define CSL_HID_8BIT_SHIFT                                      (8)

/** HID Unicode data size                                                    */
#define CSL_HID_UNICODE_SIZE                                    (66)

/** Error Code base                                                          */
#define CSL_HID_ERROR_BASE                             (CSL_EUSB_FIRST)
/** Returned when the HID request handler is invalid                         */
#define CSL_HID_INVALID_REQUEST_HANDLER                (CSL_HID_ERROR_BASE - 1)

/** \brief HID Request arguments                                             */
#define CSL_HID_REQUEST_ARGS    CSL_UsbDevHandle      devHandle,        \
                                CSL_UsbSetupStruct    *usbSetup,        \
                                CSL_UsbEpHandle       hInEp,            \
                                CSL_UsbEpHandle       hOutEp,           \
                                void                  *pHidObj

/**
@} */


/**************************************************************************\
* USB HID global typedef declarations                                       *
\**************************************************************************/

/** @addtogroup CSL_HID_ENUM
 @{ */

/**
 *  \brief This Enum defines the Hid request return values
 */
typedef enum {
    /* Don't call request again until new SETUP                              */
    CSL_HID_REQUEST_DONE = 0,
    /* STALL the control endpoint                                            */
    CSL_HID_REQUEST_STALL,
    /* Send a 0 length IN packet                                             */
    CSL_HID_REQUEST_SEND_ACK,
    /* Prepare to receive 0 length OUT packet                                */
    CSL_HID_REQUEST_GET_ACK,
    /* Notify handler when IN data has been transmitted                      */
    CSL_HID_REQUEST_DATA_IN,
    /* Notify handler when OUT data has been received                        */
    CSL_HID_REQUEST_DATA_OUT
} CSL_HidRequestRet;

/**
 *  \brief This Enum defines the HID media access status
 */
typedef enum {
    /** Media over flow error                                                */
    CSL_HID_MEDIACCESS_OVERFLOW,
    /** Media Access success                                                 */
    CSL_HID_MEDIACCESS_SUCCESS,
    /** Media not present on the system                                      */
    CSL_HID_MEDIACCESS_NOTPRESENT,
    /** Media is write protected                                             */
    CSL_HID_MEDIACCESS_WRITEPROTECT,
    /** Media is found as bad                                                */
    CSL_HID_MEDIACCESS_BADMEDIA
} CSL_HidMediaStatus;

/**
 *  \brief This Enum defines the HID media lock status
 */
typedef enum {
    /** Lock the media                                                       */
    CSL_HID_UNLOCK = 0,
    /** Unlock the media                                                     */
    CSL_HID_LOCK
} CSL_HidMediaLockStatus;

/**
 *  \brief This Enum defines types of descriptors used by the USB Hid class
 */
typedef enum {
    /** Device descriptor Id                                                 */
    CSL_HID_DEVICE_DESCR = 0,
    /** Device qualifier descriptor Id                                       */
    CSL_HID_DEVICE_QUAL_DESCR,
    /** Configuration descriptor Id                                          */
    CSL_HID_CONFIG_DESCR,
    /** Interface descriptor Id                                              */
    CSL_HID_INTERFACE_DESCR,
    /** String descriptor language Id                                        */
    CSL_HID_STRING_LANGID_DESC,
    /** HID Report descriptor Id                                             */
    CSL_HID_REPORT_DESC,
    /** Configuration descriptor Id                                          */
    CSL_HID_OTHER_SPEED_CONFIG_DESCR
} CSL_HidDescrId;

/**
@} */

/**************************************************************************\
* USB HID global data structure declarations                                *
\**************************************************************************/

/**
\addtogroup CSL_HID_DATASTRUCT
@{ */

/**
 *  \brief Hid Class control request structure
 *
 *  This structure holds the mapping of the Control Request to the
 *  Control Request handler
 */
typedef struct CSL_HidRequestStruct {
    /** \brief  HID control request                                           */
    WORD                request;
    /** \brief  HID control request handler pointer                           */
    CSL_HidRequestRet   (*fpRequestHandler)(CSL_HID_REQUEST_ARGS);
} CSL_HidRequestStruct;

/**
 *  \brief Hid Class application data structure
 *
 *  Holds the structure used by the application to fill in
 *  application specific data handler
 */
typedef struct CSL_HidInitStructApp {
    /** \brief  Pointer to Hid Class Handle defined in HID Module           */
    void                   *pHidObj;
    /** \brief  Device Descriptor units                                      */
    Uint16                 pId;
    /** \brief  Device Descriptor units                                      */
    Uint16                 vId;
    /** \brief  Logical unit number                                          */
    Uint16                 numLun;
    /** \brief  Size of the Tx packet for Isochronous end points             */
    Uint16                 txPktSize;
    /** \brief  Size of the Rx packet for Isochronous end points             */
    Uint16                 rxPktSize;
    /** \brief  Size of the Tx packet for HID interrupt end point            */
    Uint16                 hidTxPktSize;
    /** \brief  User specific string descriptor pointer                      */
    char                   **strDescrApp;

	/** \brief  Buffer ptr passed by the system to the module in order to
                enable HID report data transfer to USB API layer.            */
    Uint16                 *lbaBufferHidReportApp;
    /** \brief  Pointer to the request Table which is specified by user      */
    CSL_HidRequestStruct    *hidReqTableApp;

    /** \brief  Pointer to the Control Function Handler which is
                needed during Configuration of the Control Endpoint          */
    void                   (*ctrlHandler)();

    /** \brief  Pointer to the HID Function Handler which is
                needed during Configuration of the HID Endpoint              */
    void                   (*hidHandler)();

    /** \brief  Function to get the HID report                               */
    CSL_Status             (*getHidReportApp)(Uint16, Uint16 *);
	/** \brief  HID interface number                                         */
    Uint16                 hidIfNum;
    /** \brief  Hid Class HID report ID                                      */
    Uint16                 hidReportId;
    /** \brief  Hid Class HID report length                                  */
    Uint16                 hidReportLen;
} CSL_HidInitStructApp;

/** \brief  Hid Class application class handle                             */
typedef CSL_HidInitStructApp  *pHidAppClassHandle;

/**
 *  \brief HID application Logical unit attribute structure
 *
 *  Holds the attributes of every logical unit. This structure
 *  should be filled by the application.
 */
typedef struct CSL_HidLunAttribApp {
    /** \brief  Logical Block Size (size of each LB)                         */
    Uint32    lbaSizeApp;
    /** \brief  Total Number Of LB in the Media                                  */
    Uint32    mediaSizeApp;
    /** \brief  Removable or Non removable Media                             */
    Uint16    removeableApp;
    /** \brief  SCSI Inquiry Data  - User Configurable Items                 */
    Uint16    scsiInquiryConfData [CSL_HID_SCSI_INQUIRY_CONF_LEN];
    /** \brief  Media State                                                      */
    Uint16    mediaStateApp;
    /** \brief  Device is Readable and/or Writable                             */
    Uint16    readwriteApp;
} CSL_HidLunAttribApp;

/** \brief  Hid Class application Lun attribute handle                     */
typedef CSL_HidLunAttribApp   *pHidAppLunAttribHandle;

/** \brief  Hid Class request handler function pointer                     */
typedef  CSL_HidRequestRet (*fpHID_REQ_HANDLER)(CSL_HID_REQUEST_ARGS);

/**
 *  \brief Hid Class Logical unit structure
 *
 *  Holds all the components for the logical unit
 *  This structure is filled with the data given by the application
 *  through CSL_HidLunAttribApp structure
 */
typedef struct CSL_HidLogicalUnit {
    /** \brief  SCSI Inquiry Data                                            */
    Uint16    scsiInquiryData[CSL_HID_SCSI_INQUIRY_LEN];
    /** \brief  Number of logical blocks in the media
      *  During init this filed is set to value -1                           */
    Uint32    mediaSize;
    /** \brief  the current LBA                                              */
    Uint32    currLba;
    /** \brief  Logical Block Size                                           */
    Uint32    lbaSize;
    /** \brief  Removable or NonRemovable Media                              */
    Uint16    removeable;
    /** \brief  Media State                                                  */
    Uint16    mediaState;
    /** \brief  Device is Readable and/or writeable                          */
    Uint16    readwrite;
    /** \brief  Contains number of LB that has to be read/written            */
    Uint16    lbaCnt;
    /** \brief  Contains status of previous write in this variable           */
    Uint16    verifyFlag;
} CSL_HidLogicalUnit;

/**
 *  \brief USB Hid Class Object structure
 *
 *  Holds all the components for the Hid Class Object
 */
typedef struct CSL_HidObject {
    /** \brief  Function to get HID Report                                   */
    CSL_Status           (*getHidReport)(Uint16, Uint16 *);

    /** \brief  Data buffer pointer used to HID report data to usb           */
    Uint16               *lbaBufferHidReport;

     /** \brief  Data pertaining to Logical Units Supported                  */
    CSL_HidLogicalUnit   lun[CSL_HID_LUN_MAX];

    /** \brief  HID Interrupt In Endpoint Object Handle                      */
    CSL_UsbEpHandle      hidIntInEpHandle;
    /** \brief  HID Interrupt Out Endpoint Object Handle                     */
    CSL_UsbEpHandle      hidIntOutEpHandle;
    /** \brief  Maximum No.of Logical Units                                  */
    Uint16               noOfLun;
    /** \brief  The State the Class is in                                    */
    Uint16               mediaState;

    /** \brief  Buffer to hold the temporary data                            */
    Uint16               tempBuffer[4];
} CSL_HidObject;

/**
 *  \brief USB HID Control Object structure
 *
 *  Holds all the components for the Hid Class Control Object
 */
typedef struct CSL_HidCtrlObject {
    /** \brief  Control In Endpoint Object Handle                            */
    CSL_UsbEpHandle        ctrlInEpHandle;
    /** \brief  Object of Type Device Number                                 */
    CSL_UsbDevNum          devNum;
    /** \brief  Control Out Endpoint Object Handle                           */
    CSL_UsbEpHandle        ctrlOutEpHandle;
    /** \brief  Flag Used internally by APIs                                 */
    Uint16                 suspendFlag;
    /** \brief  NULL terminated array of Endpoint Objects                    */
    CSL_UsbEpHandle        hEpHandleArray[CSL_HID_NO_ENDPTOBJECT];
    /** \brief  Setup Structure                                              */
    CSL_UsbSetupStruct     usbSetup;

    /** \brief  Device qualifier descriptor (Used in Full soeed mode)        */
    Uint16                 deviceQualifierDescr[CSL_HID_DEV_QUAL_DESCR_MAX_LEN];
    /** \brief  Device descriptor                                            */
    Uint16                 deviceDescr[CSL_HID_DEVICE_DESCR_MAX_LEN];
    /** \brief  Configuration descriptor                                     */
    Uint16                 confDescr[CSL_HID_CONFIG_DESCR_MAX_LEN];
    /** \brief  Configuration descriptor                                     */
    Uint16                 osConfDescr[CSL_HID_CONFIG_DESCR_MAX_LEN];
    /** \brief  Hid Class Interface descriptor                             */
    Uint16                 hidClassIntDescr[CSL_HID_INTER_DESCR_MAX_LEN];

    /** \brief  Hid Class Interface descriptor Link                        */
    CSL_UsbDataStruct      hidClassInterfcLnk;

    /** \brief  String Descriptor Language ID                                */
    Uint16                 stringDescrLangid[CSL_HID_STRING_DESCR_LANGID_MAX_LEN];
    /** \brief  Current Device Configuration Status                          */
    Uint16                 curConfigStat;
    /** \brief  Array used for General Purpose                               */
    Uint16                 ctrlBuffer[CSL_HID_CTRLBUFF_LEN];
    /** \brief  Configuration Descriptor Link                                */
    CSL_UsbDataStruct      configDescrLnk;
    /** \brief  String descriptor pointer                                    */
    char                   **strDescr;
    /** \brief  Pointer to the request Table                                 */
    CSL_HidRequestStruct    *hidReqTable;
    /** \brief  Request handler function pointer                             */
    CSL_HidRequestRet        (*fpRequestHandler)(CSL_HID_REQUEST_ARGS);
    /** \brief  Hid Class HID report descriptor length                     */
    Uint16                 hidClassHidReportDescrLen;
    /** \brief  Hid Class HID report descriptor                            */
    Uint16                 hidClassHidReportDescr[CSL_HID_REPORT_DESCR_MAX_LEN_W];
    /** \brief  Hid Class HID interface number                             */
    Uint16                 hidIfNum;
    /** \brief  Hid Class HID report ID                                    */
    Uint16                 hidReportId;
    /** \brief  Hid Class HID report length                                */
    Uint16                 hidReportLen;
    /** \brief  Hid Class HID idle rate                                    */
    Uint16                 hidIdleRate;
} CSL_HidCtrlObject;

/**
 *  \brief HID Control Object structure
 *
 *  Holds all the components for the HID Control Object
 */
typedef struct CSL_HidClassStruct {
	/** \brief Handle to the selected USB Device instance                     */
	CSL_UsbDevHandle    usbDevHandle;
    /** \brief  Handle to Control Object                                      */
    CSL_HidCtrlObject    ctrlHandle;
    /** \brief  Handle to Iso Transfer Object                                 */
    CSL_HidObject        hidHandle;
} CSL_HidClassStruct;

/** \brief  Hid Class class handle                                          */
typedef CSL_HidClassStruct  *pHidClassHandle;

/**
@} */

/**************************************************************************\
* USB HID function declarations                                            *
\**************************************************************************/

/** @addtogroup CSL_HID_FUNCTION
 @{ */


/** ============================================================================
 *   @n@b HID_Open
 *
 *   @b Description
 *   @n This function Opens the Hid class module.
 *      It initializes Hid and Ctrl handles with the data given
 *      by the application
 *
 *   @b Arguments
 *   @verbatim
            pAppClassHandle      Application handle to the Hid Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK              - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE   - Invalid Hid class handle
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Initializes Hid and Ctrl handles
 *
 *   @b Modifies
 *   @n Hid and Ctrl handle data
 *
 *   @b Example
 *   @verbatim
            CSL_HidInitStructApp    hidAppHandle;
            pHidAppClassHandle      pAppClassHandle;
            Uint16                 hidAppBuffer[420];
            CSL_Status             status;

            pAppClassHandle = &hidAppHandle;

            // Assign values to all the members in hidAppHandle struct
            hidAppHandle.pHidObj = &hidAppBuffer[0];
            .....
            .....
            status = HID_Open(pAppClassHandle);
     @endverbatim
 *  ============================================================================
 */
CSL_Status HID_Open(pHidAppClassHandle    pAppClassHandle,
                    CSL_UsbConfig         *usbConfig);

/** ============================================================================
 *   @n@b HID_Close
 *
 *   @b Description
 *   @n This function Closes the Hid class module.
 *
 *   @b Arguments
 *   @verbatim
            pAppClassHandle       Application handle to the Hid Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK              - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE   - Invalid Hid class handle
 *
 *   <b> Pre Condition </b>
 *   @n  HID_Open function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Closes the Hid Class module
 *
 *   @b Modifies
 *   @n Hid and Ctl handles
 *
 *   @b Example
 *   @verbatim
            CSL_HidInitStructApp    hidAppHandle;
            pHidAppClassHandle      pAppClassHandle;
            Uint16                 hidAppBuffer[420];
            CSL_Status             status;

            pAppClassHandle = &hidAppHandle;

            // Assign values to all the members in hidAppHandle struct
            hidAppHandle.pHidObj = &hidAppBuffer[0];
            .....
            .....
            status = HID_Open(pAppClassHandle);
            ....
            ....
            status = HID_Close(pAppClassHandle);
     @endverbatim
 *  ============================================================================
 */
CSL_Status HID_Close(pHidAppClassHandle    pAppClassHandle);

/** ============================================================================
 *   @n@b HID_Ctrl
 *
 *   @b Description
 *   @n This function handles all USB traffic on the Control Endpoint.
 *      Detects the events on the Control Endpoint and takes
 *      the appropriate action
 *
 *   @b Arguments
 *   @verbatim
            pHidObj        Handle to the Hid Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li       CSL_SOK                          - Returned for success
 *   @li       CSL_ESYS_BADHANDLE               - Invalid Hid class handle
 *   @li       CSL_HID_INVALID_REQUEST_HANDLER   - Invalid request class handler
 *
 *   <b> Pre Condition </b>
 *   @n  HID_Open function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  Control end point events are serviced
 *
 *   @b Modifies
 *   @n USB Registers.
 *
 *   @b Example
 *   @verbatim
            CSL_HidInitStructApp    hidAppHandle;
            pHidAppClassHandle      pAppClassHandle;
            Uint16                 hidAppBuffer[420];
            CSL_Status             status;

            pAppClassHandle = &hidAppHandle;

            // Assign values to all the members in hidAppHandle struct
            hidAppHandle.pHidObj = &hidAppBuffer[0];
            .....
            .....
            status = HID_Open(pAppClassHandle);
            ....
            ....
            status = HID_Ctrl(pAppClassHandle->pHidObj);
     @endverbatim
 *  ============================================================================
 */
CSL_Status HID_Ctrl(void    *pHidObj);

/** ============================================================================
 *   @n@b HID_reportHandler
 *
 *   @b Description
 *   @n This function handles all USB traffic on the HID Interrupt Endpoint.
 *      Detects the events on the HID Endpoint and takes the appropriate action
 *
 *   @b Arguments
 *   @verbatim
            pHidObj        Handle to the Hid Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li       CSL_SOK                          - Returned for success
 *   @li       CSL_ESYS_BADHANDLE               - Invalid Hid class handle
 *   @li       CSL_HID_INVALID_REQUEST_HANDLER   - Invalid request class handler
 *
 *   <b> Pre Condition </b>
 *   @n  HID_Open function should be called successfully
 *
 *   <b> Post Condition </b>
 *   @n  HID interrupt end point events are serviced
 *
 *   @b Modifies
 *   @n USB Registers.
 *
 *   @b Example
 *   @verbatim
            CSL_HidInitStructApp    hidAppHandle;
            pHidAppClassHandle      pAppClassHandle;
            Uint16                 hidAppBuffer[420];
            CSL_Status             status;

            pAppClassHandle = &hidAppHandle;

            // Assign values to all the members in hidAppHandle struct
            hidAppHandle.pHidObj = &hidAppBuffer[0];
            .....
            .....
            status = HID_Open(pAppClassHandle);
            ....
            ....
            status = HID_reportHandler(pAppClassHandle->pHidObj);
     @endverbatim
 *  ============================================================================
 */
CSL_Status HID_reportHandler(void    *pHidObj);

/** ============================================================================
 *   @n@b HID_initDescriptors
 *
 *   @b Description
 *   @n This function initializes the descriptors used by the USB Hid class
 *
 *   @b Arguments
 *   @verbatim
            pHidObj      Hid Class object
            descBuf     Descriptor buffer pointer
            descrId     Id of the Descriptor to initialize
            descrLen    Length of the descriptor to initialize (in bytes)
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE - Invalid Ctrl handle
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Initializes descriptors
 *
 *   @b Modifies
 *   @n Descriptor buffers
 *
 *   @b Example
 *   @verbatim
            CSL_HidInitStructApp    hidAppHandle;
            pHidAppClassHandle      pAppClassHandle;
            Uint16                 hidAppBuffer[420];
            CSL_Status             status;

            pAppClassHandle = &hidAppHandle;

            // Assign values to all the members in hidAppHandle struct
            hidAppHandle.pHidObj = &hidAppBuffer[0];

            status = HID_initDescriptors(pAppClassHandle->pHidObj,
                                        CSL_HID_DEVICE_DESCR, 18);
     @endverbatim
 *  ============================================================================
 */
CSL_Status HID_initDescriptors(void             *pHidObj,
                               Uint16           *descBuf,
                               CSL_HidDescrId   descrId,
                               Uint16           descrLen);

/** ============================================================================
 *   @n@b HID_initHidVal
 *
 *   @b Description
 *   @n This function initializes the Hid Class object
 *
 *   @b Arguments
 *   @verbatim
            phidHandle        Handle to the Hid class Object
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK              - Returned for success
 *   @li                    CSL_ESYS_BADHANDLE   - Invalid Hid class handle
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Initializes Hid Class object
 *
 *   @b Modifies
 *   @n Hid Class object structure
 *
 *   @b Example
 *   @verbatim
            CSL_HidObject    hidObj;
            CSL_Status      status;

            status = HID_initHidVal(&hidObj);

     @endverbatim
 *  ============================================================================
 */
static CSL_Status HID_initVal(CSL_HidObject    *phidHandle);


/** ============================================================================
 *   @n@b  HID_reqHidGetReport
 *
 *   @b Description
 *   @n This function handles the request from host to get HID report
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
CSL_HidRequestRet HID_reqHidGetReport(CSL_UsbDevHandle      devHandle,
                                      CSL_UsbSetupStruct    *usbSetup,
                                      CSL_UsbEpHandle       hInEp,
                                      CSL_UsbEpHandle       hOutEp,
                                      void                  *pHidObj);

/** ============================================================================
 *   @n@b HID_eventHandler
 *
 *   @b Description
 *   @n This function handles all HID data transactions
 *
 *   @b Arguments
 *   @verbatim
			pContext		 Pointer to the USBContext structure
            hHidClass        Handle to the HID Class Obj
            usbSetUp         Structure to hold the USB Set up Values that were
                             used to configure the USB End Point
     @endverbatim
 *
 *   <b> Return Value </b>  - Status of the processing (CSL_Status)
 *   @li    CSL_SOK                    (0)         Success
 *   @li    CSL_ESYS_FAIL              (-1)        Generic failure
 *   @li    CSL_ESYS_BADHANDLE         (-5)        Handle passed to CSL was invalid
 *   @li    CSL_ESYS_INVPARAMS         (-6)        Invalid parameters
 *
 *   <b> Pre Condition </b>
 *   @n  HID module should be opened using HID_Open function
 *
 *   <b> Post Condition </b>
 *   @n  Returns request processing status
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_HidInitStructApp    pHidAppHandle;
			CSL_HidClassStruct      hidClassStruct;
			CSL_UsbSetupStruct      usbSetUp;
			CSL_Status              status;

			// Assign values to all the members in hidAppHandle struct
			hidAppHandle.pHidObj = &hidClassStruct;
			.....
			.....
			status = HID_Open(pHidAppHandle);
			....
			....

			in USB ISR:
			....
			....
			if (pContext->dwIntSourceL & (1<<CSL_USB_IN_EP0))
			{
				// Handle the HID Event
				HID_eventHandler(pContext, &pHidAppHandle, &usbSetUp);
			}
			....
			....
     @endverbatim
 *  ============================================================================
 */
void HID_eventHandler(pUsbContext        pContext,
                      pHidAppClassHandle pHidAppHandle,
                      CSL_UsbSetupStruct *usbSetUp);

/**
@} */


#ifdef __cplusplus
}
#endif

#endif    // _CSL_HID_CLASS_H_

