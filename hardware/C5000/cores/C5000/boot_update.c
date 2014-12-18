/******************************************************************************
 * This is proprietary information, not to be published -- TI INTERNAL DATA
 * Copyright (C) 2013, Texas Instruments, Inc.  All Rights Reserved.
 *
 * Bootloader Update utility
 *
 * Description :
 * This file contains the code for updating the bootloader by receiving it
 * through UART and writing it to the SD card.
 */

#include "boot_update.h"

#define USE_MSEC_WAIT_FOR_UART

/** Global variables required by the CSL MMCSD and UART modules */
CSL_MMCControllerObj    gMmcsdContObj;
CSL_MMCCardObj          gMmcCardObj;
CSL_MMCCardIdObj        gSdCardIdObj;
CSL_MMCCardCsdObj       gSdCardCsdObj;
CSL_UartObj             uartObj;

/** Global Variables required by the ATAFS module */
AtaState    gstrAtaDrive;
AtaState    *gpstrAtaDrive = &gstrAtaDrive;
AtaFile     strAtaFile;
AtaFile     *pAtaFile = &strAtaFile;

/** Internal Buffer used by AtaFs to transfer Data */
#pragma DATA_ALIGN(buAtaWrBuf ,4);
Uint16   buAtaWrBuf[256];

/** Global Variables used to hold the instance of MMC/SD module */
AtaMMCState gstrAtaMMCState;
AtaMMCState *gpstrAtaMMCState = &gstrAtaMMCState;

/** String used to read the file names of files present on the Media Card */
char fileName[15];

/** Buffer used for transfering the BOOTLOADER */
#pragma DATA_ALIGN(uartRdWrBuffer, 4);
AtaUint16 uartRdWrBuffer[UART_BUFFER_SIZE + 1];

/** Character array to hold the BOOTLOADER Filename */
char bootLoaderFileName[15];

extern Uint32 gCPUClock;

/**
 *  \brief  Function to initialize and configure SD card
 */
static CSL_Status configSdCard(CSL_MmcsdHandle   mmcsdHandle,
						       CSL_MMCCardObj    *pMmcCardObj,
						       CSL_MMCCardIdObj  *pSdCardIdObj,
						       CSL_MMCCardCsdObj *pSdCardCsdObj);

/**
 *  \brief  Function to read UART data
 */
static Int16 read_UART(CSL_UartHandle hUart,
					   Char           *pBuf,
					   Uint16         count,
					   Uint32         timeout,
					   Uint16         *bytesRead);

static Int16 ioExpander_Setup(void);

static Int16 ioExpander_Write(Uint16 port, Uint16 pin, Uint16 value);

/**
 * \brief Function for setting delay
 *
 * This function provides delay as per the milliseconds value passed
 * as parameter
 *
 * @param Uint32 msecs - milliseconds
 *
 * @return None
 */
static void delay_msecs(Uint32 msecs)
{
	volatile Uint32 index;
	volatile Uint32 delay;

#ifdef CHIP_C5517
    delay = msecs * 1000 * 9;
#else
    delay = msecs * 1000 * 6;
#endif

	for (index = 0; index < delay; index++)
	{
		asm("\tNOP");
	}
}

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
Uint16 updateBootLoader(void)
{
    CSL_Status      status;
    CSL_MmcsdHandle mmcsdHandle;
    CSL_UartHandle  hUart;
    CSL_UartSetup   uartSetup;
    CSL_MMCSDOpMode opMode;
    AtaError        ata_error;
    Uint16          diskType;
    Uint16          bytesRead;
    Char            *buffer;
    volatile Uint32 index;
    Uint32          commandReceived;
    Uint32          bytesReceived;
    Uint32          sysClk;
	Uint16          ledOn;
	char            tempFileName[15];

    status = TRUE;
    sysClk = gCPUClock;


    /* Clock gate all but MMC/SD0 */
    *(ioport volatile int *)0x1C02 = 0x7FCF;
    *(ioport volatile int *)0x1C03 = 0x007F;
    /* Set reset counter value */
    *(ioport volatile unsigned *)0x1C04=0x020;
    /* Reset all modules */
    *(ioport volatile unsigned *)0x1C05=0x00BB;

	ioExpander_Setup();

    /* Initialising the instance of UART */
    status = UART_init(&uartObj, CSL_UART_INST_0, UART_POLLED);
    if(status != CSL_SOK)
    {
        return (status);
    }

    hUart = &uartObj;

    /* Initialising the Config structure used to configure the UART */
    uartSetup.clkInput = sysClk;
    //uartSetup.baud = 115200;
    uartSetup.baud = 57600;
    uartSetup.wordLength = CSL_UART_WORD8;
    uartSetup.stopBits = 0;
    uartSetup.parity = CSL_UART_DISABLE_PARITY;
    uartSetup.fifoControl = CSL_UART_FIFO_DMA1_DISABLE_TRIG14;
    uartSetup.loopBackEnable = CSL_UART_NO_LOOPBACK;
    uartSetup.afeEnable = CSL_UART_NO_AFE;
    uartSetup.rtsEnable = CSL_UART_NO_RTS;

    /* Configuring the UART */
    status = UART_setup(hUart, &uartSetup);
    if(status != CSL_SOK)
    {
        return (status);
    }

    /* Buffer used for UART transmissions */
    buffer = (char *)uartRdWrBuffer;
    index = 0;

    for (index = 0; index < 256; index++)
    {
        buffer[index] = 0;
    }

    asm("	BIT(ST1, #13) = #0");

#ifdef USE_MSEC_WAIT_FOR_UART


#ifdef C5535_EZDSP
    /* Read the command to update the Bootloader */
    status = read_UART(hUart, buffer, COMMAND_SIZE_LENGTH, 8000,
	                   &bytesRead);
#else

#ifdef CHIP_C5517
    /* Read the command to update the Bootloader */
    status = read_UART(hUart, buffer, COMMAND_SIZE_LENGTH, 2500,
	                   &bytesRead);
#else
    /* Read the command to update the Bootloader */
    status = read_UART(hUart, buffer, COMMAND_SIZE_LENGTH, 3500, //2000
	                   &bytesRead);
#endif

#endif


#else /* #ifdef USE_MSEC_WAIT_FOR_UART */

#ifdef C5535_EZDSP
    /* Read the command to update the Bootloader */
    status = read_UART(hUart, buffer, COMMAND_SIZE_LENGTH, 0x1FFFFFF,
	                   &bytesRead);
#else

#ifdef CHIP_C5517
    /* Read the command to update the Bootloader */
    status = read_UART(hUart, buffer, COMMAND_SIZE_LENGTH, 0xFFFFFF,
	                   &bytesRead);
#else
    /* Read the command to update the Bootloader */
    status = read_UART(hUart, buffer, COMMAND_SIZE_LENGTH, 0x8FFFFF,
	                   &bytesRead);
#endif

#endif

#endif /* #ifdef USE_MSEC_WAIT_FOR_UART */

    asm("	BIT(ST1, #13) = #1");

    /* Convert the received String to an integer value */
    commandReceived = 0;
    for (index = 0; index < COMMAND_SIZE_LENGTH; index++)
    {
        commandReceived *= 10;
        commandReceived += (buffer[index] - '0');
    }

#ifdef DEBUG_ENABLED
    PRINT_MSG(("Received Command as: %d\n", commandReceived));
#endif

	if((status != CSL_EUART_TIMEOUT) && (commandReceived != COMMAND_TO_UPDATE_BOOTLOADER))
	{
		asm("	BIT(ST1, #13) = #1");
		exit(0);
	}

    if (commandReceived != COMMAND_TO_UPDATE_BOOTLOADER)
    {
	    asm("	BIT(ST1, #13) = #0");
		return (FALSE);
    }
	else
	{
		/* Keep Arduino in Reset */
		ioExpander_Write(1, 7, 1);
		ioExpander_Write(1, 6, 1);

#ifdef CHIP_C5517
		ioExpander_Write(1, 4, 1);
#else

#ifdef C55X_STANDALONE_MODE
        ioExpander_Write(1, 2, 1); /* For Standalone Mode */
#else
		ioExpander_Write(1, 2, 0); /* For Stacked Mode */
        ioExpander_Write(1, 3, 1);
        ioExpander_Write(1, 4, 1);
        ioExpander_Write(1, 5, 1);
#endif

#endif
	    /* Initialize the MMC/SD Driver */
	    status = MMC_init();
	    if(status != CSL_SOK)
	    {
	        return (status);
	    }

	    opMode = CSL_MMCSD_OPMODE_POLLED;

	    /* Open an instance of MMCSD module */
	    mmcsdHandle = MMC_open(&gMmcsdContObj, CSL_MMCSD0_INST, opMode,
		                       &status);
	    if(mmcsdHandle == NULL)
	    {
	        return (status);
	    }

	    /* Configure MMC/SD controller and SD card */
	    status = configSdCard(mmcsdHandle,
	                          &gMmcCardObj,
	                          &gSdCardIdObj,
	                          &gSdCardCsdObj);
	    if(status != CSL_SOK)
	    {
	        return (status);
	    }

	    /* Call init functions to initialize the ATA state structure */
	    gpstrAtaDrive->AtaInitAtaMediaState =
		                                   (AtaError(*)(void *))MMC_initState;
	    gpstrAtaMMCState->hMmcSd = mmcsdHandle;
	    gpstrAtaDrive->pAtaMediaState = gpstrAtaMMCState;
	    gpstrAtaDrive->AtaInitAtaMediaState(gpstrAtaDrive);

	    /* Set the temp write buffer used by the AtaFs module */
	    gpstrAtaDrive->_AtaWriteBuffer = buAtaWrBuf;

	    diskType = CSL_MMCSD_ATAFS_DISKTYPE;

	    ata_error = ATA_systemInit(gpstrAtaDrive, diskType);
	    if (ata_error != ATA_ERROR_NONE)
	    {
	        return (ata_error);
	    }

	    /* Find the first file available */
	    ata_error =  ATA_fileInit(gpstrAtaDrive, pAtaFile);
	    if(ata_error != ATA_ERROR_NONE)
	    {
	        return (ata_error);
	    }

	    /* Initialising the Temporary Bootloader filename */
	    strcpy(bootLoaderFileName, TEMP_BOOTLOADER_FILENAME);
	    strcat(bootLoaderFileName, ".");
	    strcat(bootLoaderFileName, BOOTLOADER_EXTENSION);

	    /* Searching whether the Temporary Boot Loader file exists on the card
	       or not */
	    do
	    {
	        ata_error = ATA_getLongName(pAtaFile, fileName, 0, 12);
	        if(ata_error != ATA_ERROR_NONE)
	        {
	            return (ata_error);
	        }

	        /* Checking whether the file is same as the Bootloader */
	        if(!(strcmp(bootLoaderFileName, fileName)))
	        {
			    ata_error = ATA_delete(pAtaFile);
			    if(ata_error != ATA_ERROR_NONE)
			    {
					return (ata_error);
			    }
	            break;
	        }
	        else
	        {
	            ata_error =  ATA_findNext(pAtaFile);
	            if(ata_error != ATA_ERROR_NONE)
	            {
	                break;
	            }
	        }
	    } while(ata_error == ATA_ERROR_NONE);

        /* Set the file name */
        ATA_setFileName(pAtaFile, TEMP_BOOTLOADER_FILENAME, BOOTLOADER_EXTENSION);

        /* Creating the Bootloader file */
        ata_error = ATA_create(pAtaFile);
        if(ata_error != ATA_ERROR_NONE)
        {
#ifdef DEBUG_ENABLED
            PRINT_MSG(("ATA_create Failed\n"));
#endif
            return (ata_error);
        }
        else
        {
#ifdef DEBUG_ENABLED
            PRINT_MSG(("\nFile Creation on SD card is Successful\n"));
#endif
        }

		/* Increase UART baudrate for data transfer */
		uartSetup.baud = 115200;
		status = UART_setupBaudRate(hUart, sysClk, uartSetup.baud);
		if(status != CSL_SOK)
		{
			ATA_delete(pAtaFile);
			return (status);
		}

	    buffer = (char *)uartRdWrBuffer;
		ledOn = 1;

		delay_msecs(500);

#ifdef USE_MSEC_WAIT_FOR_UART
		/* Dummy read to flush data */
		status = read_UART(hUart, buffer, 64, 10, &bytesRead);
#else
		/* Dummy read to flush data */
		status = read_UART(hUart, buffer, 64, 0xFFFF, &bytesRead);
#endif
		bytesReceived = 0;
	    while (1)
	    {
	        /* Writing the Acknowledgement String */
	        buffer[0] = 'O';
	        buffer[1] = 'K';
	        buffer[2] = '\0';
	        status = UART_write(hUart, buffer, 3, 0);

			if(ledOn == 1)
			{
			    asm("	BIT(ST1, #13) = #0");
				ledOn = 0;
			}
			else
			{
			    asm("	BIT(ST1, #13) = #1");
				ledOn = 1;
			}

#ifdef USE_MSEC_WAIT_FOR_UART
	        /* Reading the bootloader contents, in chunks of 512 bytes each */
	        status = read_UART(hUart, buffer, UART_BUFFER_SIZE, 20,
			                     &bytesRead);
#else
	        /* Reading the bootloader contents, in chunks of 512 bytes each */
	        status = read_UART(hUart, buffer, UART_BUFFER_SIZE, 0xFFFFF,
			                     &bytesRead);
#endif

	        //bytesRead = UART_BUFFER_SIZE - bytesRead;
	        bytesReceived += bytesRead;

	        for (index = 0; index < bytesRead; index += 2)
	        {
	            buffer[index / 2] = (buffer[index] << 8);
	            buffer[index / 2] |= buffer[index + 1];
	        }

	        /* Write data to the file */
	        ata_error = ATA_write(pAtaFile, (AtaUint16 *)buffer,
			                      bytesRead / 2);
	        if(ata_error != ATA_ERROR_NONE)
	        {
#ifdef DEBUG_ENABLED
	            PRINT_MSG(("ATA_write Failed\n"));
#endif
			    ATA_delete(pAtaFile);

	            return (ata_error);
	        }
	        else
	        {
#ifdef DEBUG_ENABLED
	            PRINT_MSG(("\nWriting Data successful\n"));
#endif
	        }

	        /* Checking whether all the contents have been read or not */
	        if(bytesRead < 512)
	        {
	            buffer[0] = 'O';
	            buffer[1] = 'K';
	            buffer[2] = '\0';
	            status = UART_write(hUart, buffer, 3, 0);

	            break;
	        }
	    }

	    if(bytesReceived == 0)
	    {
			ata_error = ATA_delete(pAtaFile);
			return (1);
		}

	    /* Closing the Bootloader File */
	    ata_error = ATA_close(pAtaFile);
	    if(ata_error != ATA_ERROR_NONE)
	    {
	        return (ata_error);
	    }

	    /* Initialising the Bootloader filename */
	    strcpy(bootLoaderFileName, BOOTLOADER_FILENAME);
	    strcat(bootLoaderFileName, ".");
	    strcat(bootLoaderFileName, BOOTLOADER_EXTENSION);

	    /* Find the first file available */
	    ata_error =  ATA_fileInit(gpstrAtaDrive, pAtaFile);
	    if(ata_error != ATA_ERROR_NONE)
	    {
	        return (ata_error);
	    }

	    /* Searching whether the Boot Loader file exists on the card or not.
	       If it exists deleting it */
	    do
	    {
	        ata_error = ATA_getLongName(pAtaFile, fileName, 0, 12);
	        if(ata_error != ATA_ERROR_NONE)
	        {
	            return (ata_error);
	        }

	        /* Checking whether the file is same as the Bootloader */
	        if(!(strcmp(bootLoaderFileName, fileName)))
	        {
			    ata_error = ATA_delete(pAtaFile);
			    if(ata_error != ATA_ERROR_NONE)
			    {
					return (ata_error);
			    }
	            break;
	        }
	        else
	        {
	            ata_error =  ATA_findNext(pAtaFile);
	            if(ata_error != ATA_ERROR_NONE)
	            {
	                break;
	            }
	        }
	    } while(ata_error == ATA_ERROR_NONE);

	    /* Initialising the Bootloader filename */
	    strcpy(tempFileName, TEMP_BOOTLOADER_FILENAME);
	    strcat(tempFileName, ".");
	    strcat(tempFileName, BOOTLOADER_EXTENSION);

	    /* Find the first file available */
	    ata_error =  ATA_fileInit(gpstrAtaDrive, pAtaFile);
	    if(ata_error != ATA_ERROR_NONE)
	    {
	        return (ata_error);
	    }

	    /* Searching whether the Boot Loader file exists on the card or not.
	       If it exists deleting it */
	    do
	    {
	        ata_error = ATA_getLongName(pAtaFile, fileName, 0, 12);
	        if(ata_error != ATA_ERROR_NONE)
	        {
	            return (ata_error);
	        }

	        /* Checking whether the file is same as the Bootloader */
	        if(!(strcmp(tempFileName, fileName)))
	        {
			    ata_error = ATA_renameLong(pAtaFile, bootLoaderFileName);
			    if(ata_error != ATA_ERROR_NONE)
			    {
					return (ata_error);
			    }
	            break;
	        }
	        else
	        {
	            ata_error =  ATA_findNext(pAtaFile);
	            if(ata_error != ATA_ERROR_NONE)
	            {
	                break;
	            }
	        }
	    } while(ata_error == ATA_ERROR_NONE);

	    /* Closing the MMCSD module */
	    status = MMC_close(mmcsdHandle);

		/* Reset Arduino and DSP Shield */
	    ioExpander_Write(1, 7, 0);

		for(index = 0; index < 0xffff; index++)
		{
		    asm(" NOP");
		}
	}

    return (status);
}

#ifdef USE_MSEC_WAIT_FOR_UART

/** ===========================================================================
 *   @n@b read_UART
 *
 *   @b Description
 *   @n read_UART attempts to read up to count characters
 *	    from RBR(Recieve Buffer Register) into the buffer starting at pBuf.
 *   @b Arguments
 *   @verbatim
		hUart      Handle to the UART.
	   	pBuf       Output buffer
      	count      No of characters to read.
        timeout    Timeout value
                   0 - wait indefinitely for DR bit to get set.
                   x - wait x value for DR bit to get set.
		bytesRead  Number of bytes read from UART
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li          CSL_SOK -  read_UART call is successful.
 *   @li          CSL_ESYS_BADHANDLE- Invalid UART Handle
 *   @li          CSL_ESYS_INVPARAMS- Invalid address of the  buffer.
 *   @li          CSL_EUART_TIMEOUT - Read had a timeout due to DR bit not set.
 *  ===========================================================================
 */
static Int16 read_UART(CSL_UartHandle hUart,
                       Char           *pBuf,
                       Uint16         count,
                       Uint32         timeout,
                       Uint16         *bytesRead)
{
	volatile Uint32 msecs;
	CSL_Status status = CSL_SOK;
	Uint16         byteCnt;
	Uint16         ledState;
	int            ledBlinkCnt;

	if(NULL == hUart)
	{
	 	return (CSL_ESYS_BADHANDLE);
	}

	if(NULL == pBuf)
	{
		return (CSL_ESYS_INVPARAMS);
	}

	*bytesRead = 0;
	byteCnt = 0;
	msecs = 0;
	ledState = 0;
	ledBlinkCnt = 0;

   	CSL_FINST(hUart->uartRegs->LCR, UART_LCR_DLAB, DLABON);

    if(UART_POLLED == hUart->opmode)
    {
        if(0 != timeout)
        {
            while(0 != (count--))
            {
                while((!UART_getDataReadyStatus(hUart)))
                {
					delay_msecs(1);
					msecs++;

#ifndef DISABLE_LED_BLINK_FOR_PROGRAM_WAIT

					if((msecs%100) == 0)
					{
						if(ledBlinkCnt == 4)
						{
							ledBlinkCnt = -1;
							ledState = 1;
						}
						else
						{
							ledBlinkCnt++;
							if(ledState == 1)
							{
								ledState = 0;
								asm("	BIT(ST1, #13) = #0");
							}
							else
							{
								ledState = 1;
								asm("	BIT(ST1, #13) = #1");
							}
						}
					}
#endif
					if (msecs >= timeout)
					{
						*bytesRead = byteCnt;
						return (CSL_EUART_TIMEOUT);
					}
				}

                *pBuf++ = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
                byteCnt++;
                msecs = 0;
            }
        }
        else
        {
            while(0 != (count--))
            {
                while(!UART_getDataReadyStatus(hUart));
                *pBuf++ = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
                byteCnt++;
            }
        }

        *bytesRead = byteCnt;

        return (status);
    }

    *pBuf++ = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
    *bytesRead = 1;

    return (status);
}

#else

/** ===========================================================================
 *   @n@b read_UART
 *
 *   @b Description
 *   @n read_UART attempts to read up to count characters
 *	    from RBR(Recieve Buffer Register) into the buffer starting at pBuf.
 *   @b Arguments
 *   @verbatim
		hUart      Handle to the UART.
	   	pBuf       Output buffer
      	count      No of characters to read.
        timeout    Timeout value
                   0 - wait indefinitely for DR bit to get set.
                   x - wait x value for DR bit to get set.
		bytesRead  Number of bytes read from UART
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li          CSL_SOK -  read_UART call is successful.
 *   @li          CSL_ESYS_BADHANDLE- Invalid UART Handle
 *   @li          CSL_ESYS_INVPARAMS- Invalid address of the  buffer.
 *   @li          CSL_EUART_TIMEOUT - Read had a timeout due to DR bit not set.
 *  ===========================================================================
 */
static Int16 read_UART(CSL_UartHandle hUart,
                       Char           *pBuf,
                       Uint16         count,
                       Uint32         timeout,
                       Uint16         *bytesRead)
{
	volatile Uint32 TimeOut    = timeout;
	CSL_Status status = CSL_SOK;
	Uint16         byteCnt;

	if(NULL == hUart)
	{
	 	return (CSL_ESYS_BADHANDLE);
	}

	if(NULL == pBuf)
	{
		return (CSL_ESYS_INVPARAMS);
	}

	*bytesRead = 0;
	byteCnt = 0;
   	CSL_FINST(hUart->uartRegs->LCR, UART_LCR_DLAB, DLABON);

    if(UART_POLLED == hUart->opmode)
    {
        if(0 != timeout)
        {
            while(0 != (count--))
            {
                while( ( !UART_getDataReadyStatus( hUart) ) && --TimeOut);
                if (0 == TimeOut)
                {
					*bytesRead = byteCnt;
                    return (CSL_EUART_TIMEOUT);
                }

                *pBuf++ = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
                byteCnt++;
                TimeOut = timeout;
            }
        }
        else
        {
            while(0 != (count--))
            {
                while(!UART_getDataReadyStatus(hUart));
                *pBuf++ = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
                byteCnt++;
            }
        }

        *bytesRead = byteCnt;

        return (status);
    }

    *pBuf++ = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
    *bytesRead = 1;

    return (status);
}

#endif  /* #ifdef USE_MSEC_WAIT_FOR_UART */

/**
 *  \brief  Function to initialize and configure SD card
 *
 *  \return Test result
 */
static CSL_Status configSdCard (CSL_MmcsdHandle   mmcsdHandle,
                                CSL_MMCCardObj    *pMmcCardObj,
                                CSL_MMCCardIdObj  *pSdCardIdObj,
                                CSL_MMCCardCsdObj *pSdCardCsdObj
)
{
    CSL_Status status;
	Uint16     rca;

    status = MMC_sendGoIdle(mmcsdHandle);
    if(status != CSL_SOK)
    {
        return (status);
    }

    status = MMC_selectCard(mmcsdHandle, pMmcCardObj);
    if(status != CSL_SOK)
    {
        return (status);
    }

    if(pMmcCardObj->cardType == CSL_SD_CARD)
    {
		status = MMC_sendOpCond(mmcsdHandle, 70);
		if(status != CSL_SOK)
		{
			return (status);
		}

		status = SD_sendAllCID(mmcsdHandle, pSdCardIdObj);
		if(status != CSL_SOK)
		{
			return (status);
		}

		status = SD_sendRca(mmcsdHandle, pMmcCardObj, &rca);
		if(status != CSL_SOK)
		{
			return (status);
		}

		status = SD_getCardCsd(mmcsdHandle, pSdCardCsdObj);
		if(status != CSL_SOK)
		{
			return (status);
		}
    }
    else
    {
        return(CSL_ESYS_FAIL);
	}

	status = MMC_sendOpCond(mmcsdHandle, MMCSD_CLOCK_DIV);
	if(status != CSL_SOK)
	{
		return (status);
	}

	/* Set Endian mode for read and write operations */
  	status = MMC_setEndianMode(mmcsdHandle, CSL_MMCSD_ENDIAN_LITTLE,
  	                           CSL_MMCSD_ENDIAN_LITTLE);
	if(status != CSL_SOK)
	{
		return(status);
	}

    return(status);
}

/**
 *  \brief  Function to configure IO expander
 *
 *  \return Error status
 */
static Int16 ioExpander_Setup(void)
{
	Int16 		 status;
	CSL_I2cSetup i2cSetup;
    Uint32       sysClk;

    sysClk = gCPUClock;
    sysClk = sysClk / (1000000);

	/* Initialize I2C module */
	status = I2C_init(CSL_I2C0);
	if(status != CSL_SOK)
	{
		return(status);
	}

	/* Setup I2C module */
	i2cSetup.addrMode    = CSL_I2C_ADDR_7BIT;
	i2cSetup.bitCount    = CSL_I2C_BC_8BITS;
	i2cSetup.loopBack    = CSL_I2C_LOOPBACK_DISABLE;
	i2cSetup.freeMode    = CSL_I2C_FREEMODE_DISABLE;
	i2cSetup.repeatMode  = CSL_I2C_REPEATMODE_DISABLE;
	i2cSetup.ownAddr     = CSL_I2C_OWN_ADDR;
	i2cSetup.sysInputClk = sysClk;
	i2cSetup.i2cBusFreq  = CSL_I2C_BUS_FREQ;

	status = I2C_setup(&i2cSetup);
	if(status != CSL_SOK)
	{
		return(status);
	}

	return status;
}

/**
 *  \brief  Function to write into IO expander
 *
 *  \return Error status
 */
static Int16 ioExpander_Write(Uint16 port, Uint16 pin, Uint16 wValue)
{
	Int16 	status;
	Uint16 	i2cWriteBuf[2];
	Uint16 	i2cReadBuf[1];
	Uint16	configOld;
	Uint16	driveOld;
	volatile Uint16 delay;

/*Read Old Config*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x06; /*Port0 Config Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x07; /*Port1 Config Cmd*/
	}

	for(delay=0; delay<0xFFFF; delay++);

	status = I2C_write(i2cWriteBuf, 1, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
		return(status);
	}

	for(delay=0; delay<0xFFFF; delay++);

	status = I2C_read(i2cReadBuf, 1, CSL_I2C_TCA6416_ADDR,
	                  i2cWriteBuf, 1, TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
	                  CSL_I2C_MAX_TIMEOUT, FALSE);
	if(status != CSL_SOK)
	{
		return(status);
	}

	configOld = i2cReadBuf[0];

/*Read Old Drive*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x02; /*Port0 Output Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x03; /*Port1 Output Cmd*/
	}

	for(delay=0; delay<0xFFFF; delay++);

	status = I2C_write(i2cWriteBuf, 1, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
		return(status);
	}

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_read(i2cReadBuf, 1, CSL_I2C_TCA6416_ADDR,
	                  i2cWriteBuf, 1, TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
	                  CSL_I2C_MAX_TIMEOUT, FALSE);
	if(status != CSL_SOK)
	{
		return(status);
	}

	driveOld = i2cReadBuf[0];

/*Configure pin as OUT*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x06; /*Port0 Config Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x07; /*Port1 Config Cmd*/
	}
	i2cWriteBuf[1] = configOld;
	i2cWriteBuf[1] &= (~((Uint16)0x1 << pin)); /*1-IN, 0-OUT*/;

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_write(i2cWriteBuf, 2, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
		return(status);
	}

/*Drive pin*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x02; /*Port0 Output Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x03; /*Port1 Output Cmd*/
	}
	i2cWriteBuf[1] = driveOld;
	if(wValue)
		i2cWriteBuf[1] |= ((Uint16)0x1 << pin);
	else
		i2cWriteBuf[1] &= (~((Uint16)0x1 << pin));

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_write(i2cWriteBuf, 2, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
		return(status);
	}

	return status;
}

