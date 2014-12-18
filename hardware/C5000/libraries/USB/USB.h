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
/** @file USB.h
 *
 *  @brief USB library header file
 *
 */

#ifndef _USB_H_
#define _USB_H_

#include <stdio.h>
#include <string.h>
#include "tistdtypes.h"
#include "csl_usb.h"
#include "csl_usbAux.h"
#include "csl_pll.h"
#include "core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** USB highspeed maximum packet size */
#define USB_HS_MAX_PACKET_SIZE (64)
/** Maximum USB data size */
#define USB_DATA_SIZE          (USB_HS_MAX_PACKET_SIZE / 2)
/** Linking RAM size */
#define USB_LRAM_SIZE          (256)
/** USB maximum current */
#define USB_MAX_CURRENT        (50)
/** USB wakeup delay */
#define USB_WAKEUP_DELAY       (10)
/** USB OUT endpoint number */
#define USB_OUT                (1)
/** USB IN endpoint number */
#define USB_IN                 (2)
/** Number of pipes supported */
#define USB_PIPE_COUNT         (CSL_USB_ENDPOINT_COUNT + 2)
/** String descriptor count */
#define USB_STRDESC_COUNT      (4)
/** Macro to indicate Endpoint 0 */
#define USB_EP0                (CSL_USB_EP0)
/** Macro to indicate Endpoint 1 */
#define USB_EP1                (CSL_USB_EP1)
/** Macro to indicate Endpoint 2 */
#define USB_EP2                (CSL_USB_EP2)
/** Macro to indicate Endpoint 3 */
#define USB_EP3                (CSL_USB_EP3)
/** Macro to indicate Endpoint 4 */
#define USB_EP4                (CSL_USB_EP4)
/** Macro to indicate OUT Endpoint 0 */
#define USB_OUT_EP0            (CSL_USB_OUT_EP0)
/** Macro to indicate OUT Endpoint 1 */
#define USB_OUT_EP1            (CSL_USB_OUT_EP1)
/** Macro to indicate OUT Endpoint 2 */
#define USB_OUT_EP2            (CSL_USB_OUT_EP2)
/** Macro to indicate OUT Endpoint 3 */
#define USB_OUT_EP3            (CSL_USB_OUT_EP3)
/** Macro to indicate OUT Endpoint 4 */
#define USB_OUT_EP4            (CSL_USB_OUT_EP4)
/** Macro to indicate IN Endpoint 0 */
#define USB_IN_EP0             (CSL_USB_IN_EP0)
/** Macro to indicate IN Endpoint 1 */
#define USB_IN_EP1             (CSL_USB_IN_EP1)
/** Macro to indicate IN Endpoint 2 */
#define USB_IN_EP2             (CSL_USB_IN_EP2)
/** Macro to indicate IN Endpoint 3 */
#define USB_IN_EP3             (CSL_USB_IN_EP3)
/** Macro to indicate IN Endpoint 4 */
#define USB_IN_EP4             (CSL_USB_IN_EP4)

/** USB application call back pointer                                        */
typedef void (*USB_APP_CALLBACK)(Uint16 flag);
/** USB application call back pointer for tx and rx interrupts               */
typedef int (*USB_APP_INT_CALLBACK)(void *, unsigned short, unsigned short);
/** USB pipe handle                                                          */
typedef void * USB_pipeHandle;

/**
 * \brief Enum to indicate operation mode
 */
typedef enum USB_opMode
{
	USB_OPMODE_POLLED = 0,
	USB_OPMODE_DMA
} USB_opMode;

/**
 * \brief Enum to indicate the transfer type
 */
typedef enum USB_xferType{
	USB_CTRL  = 0,
	USB_BULK
} USB_xferType;

/**
 * \brief USB confuguration Class
 */
class USB_Config
{
    public:
	    /** USB operation mode */
        USB_opMode                   opMode;
		/** Callback function for suspend operation */
        USB_APP_CALLBACK             appSuspendCallBack;
		/** Callback function for RX interrupt */
		USB_APP_INT_CALLBACK         rxIntCallback;
		/** Callback function for TX interrupt */
		USB_APP_INT_CALLBACK         txIntCallback;
		/** Callback function for RX complete interrupt */
		USB_APP_INT_CALLBACK         rxCompleteCallback;
		/** Device descriptor pointer */
		unsigned short               *deviceDescPtr;
		/** Device qualifier descriptor pointer */
        unsigned short               *deviceQualDescPtr;
		/** Config descriptor pointer */
        unsigned short               *cfgDescPtr;
		/** Full speed config descriptor pointer */
        unsigned short               *cfgDescFSPtr;
		/** String descriptor pointer */
        unsigned short               *strDescPtr[USB_STRDESC_COUNT];
};

/**
 * \brief Pipe confuguration Class
 */
class Pipe_Config
{
    public:
	    /** Transfer type */
        USB_xferType   xferType;
		/** Max packet size */
        unsigned short maxPktSize;
};

/**
 * \brief USB Class
 *
 *  Contains prototypes for functions in USB library
 */
class USBClass {
    private:
        USB_pipeHandle   hEp[USB_PIPE_COUNT];
	    USB_pipeHandle   hEPx;
		int              status;
		bool             usbDevDisconnect;
		unsigned short   configVal;
		unsigned short   dataBuffer[10];
        unsigned short   usb_income_num_bytes_ep1;
        unsigned short   usb_income_num_bytes_ep2;
        unsigned short   usb_income_num_bytes_ep3;
        unsigned short   usb_income_num_bytes_ep4;
    	unsigned short   saveIndex;
		unsigned short   endpt;
		unsigned short   tempLen;
		unsigned short   devAddr;
      	unsigned short   intEp;
		unsigned short   queuePend;
    public:
	    /** USB data buffer 1 pointer */
	    unsigned short   *usbBuffTxRxPtr1;
	    /** USB data buffer 2 pointer */
		unsigned short   *usbBuffTxRxPtr2;
	    /** USB data buffer 3 pointer */
		unsigned short   *usbBuffTxRxPtr3;
	    /** USB data buffer 4 pointer */
		unsigned short   *usbBuffTxRxPtr4;

	    USBClass();
	    int init();
        int config(USB_Config);
        int connect();
		int disconnect();
        int suspend();
        void * requestPipe(unsigned short, unsigned short);
		int closePipe(void *);
		int configPipe(void *, Pipe_Config);
        int stallPipe(void *);
		int clearPipe(void *);
		int writePipe(void *,
                      unsigned short,
					  unsigned short *);
		int readPipe(void *,
                     unsigned short,
					 unsigned short *);
		int handleInterrupts();
		int setParams(void *);
		int dmaRxStop(void *);
		int dmaTxStop(void *);
};

extern USBClass USB;
/**< USB class instance extern which can used by application programs
 *   to access USB DSP APIs
 */
#ifdef __cplusplus
}
#endif

#endif //_USB_H_

