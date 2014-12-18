/*
   USB - DMA mode example
   ----------------------------
   This example is to verify the operation of the USB module.This example
   runs in DMA mode. USB controller is having DMA module internal to it.
   This DMA can be used to exchange the data between USB FIFO and the CPU memory.
   USB interrupt are used to indicate the arrival of request from the host.
   USB interrupts are configured and ISR is  registered using Interrupt module.
   After initializing and configuring the USB module, when there is any request 
   from the USB host application USB ISR is triggered and the requested operation 
   is performed inside the ISR. Inside the ISR FIFO read and write operations are 
   performed using CPPI DMA module.
 
   This USB test can be verified by a host USB tool(c55xx_usb_ep_diag.exe which 
   has to be obtained from TI) which can send or receive 64 bytes of data to the 
   USB device. This tool should be installed on the host PC. This tool requires 
   Jungo USB driver which can be downloaded from the link www.jungo.com. inf file 
   should be installed for C5517 USB device using driver wizard of the windriver.
   This installation is required only when running this example for the first
   time.

   Test procedure
   --------------
   1. Connect Arduino to host PC using USB cable.
   2. Verify and Upload the example binary to DSP shield.
   3. Open the Windriver driver wizard and install the inf file for the USB
      device (Only when running for first time)
   4. Run the c55xx_usb_ep_diag.exe application. It displays following message

       DeviceAttach: received and accepted attach for vendor id 0x451, product id 0x901
		0, interface 0, device handle 0x00392AD8

       Main Menu (active Dev/Prod/Interface/Alt. Setting: 0x451/0x9010/0/0)
       ----------
       1. Display device configurations
       2. Change interface alternate setting
       3. Reset Pipe
       4. Read/Write from pipes
       6. Selective Suspend
       7. Refresh
       99. Exit
       Enter option:

   5. For read and write operations command number should be selected depending
      on the end points configured for IN and OUT USB transfers. As per the
      current implementation, all end points are configured for both IN and OUT.
      Data should be read back from the same end point to which data was written.
      For example, write data to EP1 and read back the data from EP1 itself.
   6. The first command should be read followed by write-read... for the
      proper synchronization of host and target USB device.
   7. For verifying the USB operations send write command from host and then
      read command. check whether the data sent by the host is transmitted back
      by the target or not.
   8. During read/write operations data will be displayed by the host USB tool
*/

#include "USB.h"

USB_pipeHandle    hPipe[USB_PIPE_COUNT];

unsigned short    deviceDesc[9] = {0x0112, 0x0200, 0x0000, 0x4000, 0x0451,
                                   0x9010, 0x0100, 0x0201, 0x0103};

unsigned short    deviceQualDesc[5] = {0x060A, 0x0200, 0x0000, 0x4000, 0x0002};

unsigned short    cfgDesc[40] = {0x0209, 0x004A, 0x0101, 0xC001, 0x0928,    
                                 0x0004, 0x0800, 0x0000, 0x0000,             
                                 0x0507, 0x0281, 0x0200, 0x0700,            
                                 0x0105, 0x0002, 0x0002,                     
                                 0x0507, 0x0282, 0x0200, 0x0700,            
                                 0x0205, 0x0002, 0x0002,                     
                                 0x0507, 0x0283, 0x0200, 0x0700,             
                                 0x0305, 0x0002, 0x0002,                    
                                 0x0507, 0x0284, 0x0200, 0x0700,             
                                 0x0405, 0x0002, 0x0002                        
                                };

unsigned short    OtherSpeedcfgDesc[40] = {0x0709, 0x004A, 0x0201, 0xC001, 0x0928,         
                                           0x0004, 0x0800, 0x0000, 0x0000,                   
                                           0x0507, 0x0281, 0x0040, 0x0700,            
                                           0x0105, 0x4002, 0x0000,                     
                                           0x0507, 0x0282, 0x0040, 0x0700,            
                                           0x0205, 0x4002, 0x0000,                     
                                           0x0507, 0x0283, 0x0040, 0x0700,             
                                           0x0305, 0x4002, 0x0000,                    
                                           0x0507, 0x0284, 0x0040, 0x0700,             
                                           0x0405, 0x4002, 0x0000                        
                                          };

unsigned short    strDesc[4][20] = {
                                    // string 0 English-USA
                                    {0x0304, 0x0409},
                                    // string 1 "Texas Instruments"
                                    {0x0324, 0x0045, 0x0054, 0x0041, 0x0058, 0x0020,
                                     0x0053, 0x004E, 0x0049, 0x0054, 0x0053, 0x0055,
                                     0x0052, 0x0045, 0x004D, 0x0054, 0x004E, 0x0053},
                                    // string 2 "C5515"
                                    {0x030C, 0x0043, 0x0035, 0x0035, 0x0031, 0x0037},
                                    // string 3 "00001"
                                    {0x030C, 0x0030, 0x0030, 0x0030, 0x0030, 0x0031}
                                   };

interrupt void usb_isr(void);
void suspendCallBack(int status);
void rxIntCallback(void *hPipe, 
                   unsigned short pipeNum, 
                   unsigned short bytes);
void rxCompleteCallback(void *hPipe, 
                        unsigned short pipeNum, 
                        unsigned short bytes);
void txIntCallback(void *hPipe, 
                   unsigned short epNum, 
                   unsigned short bytes);

void setup()
{
    Pipe_Config     epCfg;
    USB_Config      usbConfig; 
    int status;  
          
    attachInterrupt((INTERRUPT_NUMBER)USB_EVENT, (IRQ_IsrPtr)usb_isr, 0);

    /* Enabling Interrupt */
    enableInterrupt((INTERRUPT_NUMBER)USB_EVENT);
    
    usbConfig.opMode             = USB_OPMODE_DMA;
    usbConfig.appSuspendCallBack = (USB_APP_CALLBACK)suspendCallBack;
    usbConfig.rxIntCallback      = (USB_APP_INT_CALLBACK)rxIntCallback;
    usbConfig.txIntCallback      = (USB_APP_INT_CALLBACK)txIntCallback;
    usbConfig.rxCompleteCallback = (USB_APP_INT_CALLBACK)rxCompleteCallback;
    usbConfig.deviceDescPtr      = (unsigned short *)deviceDesc;
    usbConfig.deviceQualDescPtr  = (unsigned short *)deviceQualDesc;
    usbConfig.cfgDescPtr         = (unsigned short *)cfgDesc;
    usbConfig.cfgDescFSPtr       = (unsigned short *)OtherSpeedcfgDesc;
    usbConfig.strDescPtr[0]      = (unsigned short *)strDesc;

    status = USB.init();

    status = USB.config(usbConfig);

    hPipe[0] = USB.requestPipe(0, USB_OUT);

    epCfg.xferType = USB_CTRL;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[0], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[1] = USB.requestPipe(0, USB_IN);

    epCfg.xferType = USB_CTRL;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[1], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[3] = USB.requestPipe(1, USB_OUT);

    epCfg.xferType = USB_BULK;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[3], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[2] = USB.requestPipe(1, USB_IN);

    epCfg.xferType = USB_BULK;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[2], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[5] = USB.requestPipe(2, USB_OUT);

    epCfg.xferType = USB_BULK;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[5], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[4] = USB.requestPipe(2, USB_IN);

    epCfg.xferType = USB_BULK;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[4], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[7] = USB.requestPipe(3, USB_OUT);

    epCfg.xferType = USB_BULK;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[7], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[6] = USB.requestPipe(3, USB_IN);

    epCfg.xferType = USB_BULK;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[6], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[9] = USB.requestPipe(4, USB_OUT);

    epCfg.xferType = USB_BULK;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[9], epCfg);
    if(status != 0)
    {
        return;
    }

    hPipe[8] = USB.requestPipe(4, USB_IN);

    epCfg.xferType = USB_BULK;
    epCfg.maxPktSize = USB_HS_MAX_PACKET_SIZE;

    status = USB.configPipe(hPipe[8], epCfg);
    if(status != 0)
    {
        return;
    }

    status = USB.setParams(hPipe);
    if(status != 0)
    {
        return;
    }

    status = USB.connect();
    if(status != 0)
    {
        return;
    }
}

void loop()
{
}

interrupt void usb_isr()
{
    USB.handleInterrupts();
}

void rxIntCallback(void           *hPipe, 
                   unsigned short pipeNum, 
                   unsigned short bytes)
{
    if(pipeNum == USB_OUT_EP1)
    {
        USB.readPipe(hPipe, bytes, USB.usbBuffTxRxPtr1);
    }
    else if(pipeNum == USB_OUT_EP2)
    {
        USB.readPipe(hPipe, bytes, USB.usbBuffTxRxPtr2);
    }
    else if(pipeNum == USB_OUT_EP3)
    {
        USB.readPipe(hPipe, bytes, USB.usbBuffTxRxPtr3);
    }
    else
    {
        USB.readPipe(hPipe, bytes, USB.usbBuffTxRxPtr4);
    }
}  

void txIntCallback(void           *hPipe, 
                   unsigned short pipeNum, 
                   unsigned short bytes)
{
    if(pipeNum == USB_IN_EP1)
    {
        USB.writePipe(hPipe, bytes, USB.usbBuffTxRxPtr1);
    }
    else if(pipeNum == USB_IN_EP2)
    {
        USB.writePipe(hPipe, bytes, USB.usbBuffTxRxPtr2);
    }
    else if(pipeNum == USB_IN_EP3)
    {
        USB.writePipe(hPipe, bytes, USB.usbBuffTxRxPtr3);
    }
    else
    {
        USB.writePipe(hPipe, bytes, USB.usbBuffTxRxPtr4);
    }
} 

void rxCompleteCallback(void           *hPipeOut, 
                        unsigned short epNum, 
                        unsigned short bytes)  
{
    if(epNum == USB_EP1)
	{
        USB.writePipe(hPipe[2], bytes, USB.usbBuffTxRxPtr1);
	}
    else if(epNum == USB_EP2)
	{
        USB.writePipe(hPipe[4], bytes, USB.usbBuffTxRxPtr2);
	}
    else if(epNum == USB_EP3)
	{
        USB.writePipe(hPipe[6], bytes, USB.usbBuffTxRxPtr3);
	}
    else if(epNum == USB_EP4)
	{
        USB.writePipe(hPipe[8], bytes, USB.usbBuffTxRxPtr4);
	}
	else
	{
	    /* Do nothing for Ep0 */
	}
}

void suspendCallBack(int status)
{
    /* For future use */
}


