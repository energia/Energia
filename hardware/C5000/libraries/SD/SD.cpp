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
/** @file SD.cpp
 *
 *  @brief SD/File implementation
 *
 */

#include <SD.h>
#include <core.h>

/** Macro to indicate the maximum clock value for the SD/MMC Card*/
#define CSL_SD_CLOCK_MAX_KHZ      (20000u)

/** Macro to enable the Print messages to be displayed on the Serial */
//#define ENABLE_SERIAL_MSGS

#ifdef ENABLE_SERIAL_MSGS
#include <Serial_lib.h>
#endif

/** Macro to indicate the Size of Data buffer used by ATA File System for file
    Read and Write Operations */
#define CSL_MMCSD_ATA_BUF_SIZE     (512u)
/** Macro to indicate write cache size */
#define WRITE_CACHE_SIZE (512)

/**
 * \brief Node of the Linked List to hold the details of all the Opened files
 */
class fileNodesList
{
    public:
        /** Starting cluster of file */
        unsigned long        startCluster;
        /** Pointer to next file */
        struct fileNodesList *nextFileNode;

        fileNodesList()
        {
            startCluster = 0xFFFFFFFF;
            nextFileNode = (struct fileNodesList *)NULL;
        }
};

/** Pointer to the first node in the Linked List of File Nodes */
fileNodesList *fileListHeadNode;
/** Pointer to the last node in the Linked List of File Nodes */
fileNodesList *fileListLastNode;

/** Defining a global SD Class Object which can be used by the User
    Application */
SD_Class SD;

/** Data Buffer used for Read and Write Operations by the ATA File System */
#pragma DATA_ALIGN(4);
AtaUint16   AtaWrBuf[CSL_MMCSD_ATA_BUF_SIZE];

/** Data Buffer used for DSP API write operations */
char writeCacheBuffer[WRITE_CACHE_SIZE + 1];

/**
 * \brief API to print Debug messages
 *
 * This API will print the messages to either the Serial or the Output Console
 */
void LOG_MSG_print (char *printString);

/**
 * \brief  Function to calculate the memory clock rate
 *
 * This function computes the memory clock rate value depending on the
 * CPU frequency. This value is used as clock divider value for
 * calling the API MMC_sendOpCond(). Value of the clock rate computed
 * by this function will change depending on the system clock value
 * and MMC maximum clock value defined by macro 'CSL_SD_CLOCK_MAX_KHZ'.
 * Minimum clock rate value returned by this function is 0 and
 * maximum clock rate value returned by this function is 255.
 * Clock derived using the clock rate returned by this API will be
 * the nearest value to 'CSL_SD_CLOCK_MAX_KHZ'.
 *
 * \return Error Status
 */
static Uint16 computeClkRate(void)
{
    Uint32    sysClock;
    Uint32    remainder;
    Uint32    memMaxClk;
    Uint16    clkRate;

    sysClock  = 0;
    remainder = 0;
    memMaxClk = CSL_SD_CLOCK_MAX_KHZ;
    clkRate   = 0;

    /* Get the clock value at which CPU is running. getCpuClock() will return
       system clock in terms of kHz */
    sysClock = getCpuClock();

    if (sysClock > memMaxClk)
    {
        if (memMaxClk != 0)
        {
            clkRate   = sysClock / memMaxClk;
            remainder = sysClock % memMaxClk;

            /*
             * If the remainder is not equal to 0, increment clock rate to make
             * sure that memory clock value is less than the value of
             * 'CSL_SD_CLOCK_MAX_KHZ'.
             */
            if (remainder != 0)
            {
                clkRate++;
            }

            /*
             * memory clock divider '(2 * (CLKRT + 1)' will always
             * be an even number. Increment the clock rate in case of
             * clock rate is not an even number
             */
            if (clkRate%2 != 0)
            {
                clkRate++;
            }

            /*
             * AT this point 'clkRate' holds the value of (2 * (CLKRT + 1).
             * Get the value of CLKRT.
             */
            clkRate = clkRate/2;
            clkRate = clkRate - 1;

            /*
             * If the clock rate is more than the maximum allowed clock rate
             * set the value of clock rate to maximum value.
             * This case will become true only when the value of
             * 'CSL_SD_CLOCK_MAX_KHZ' is less than the minimum possible
             * memory clock that can be generated at a particular CPU clock.
             *
             */
            if (clkRate > CSL_MMC_MAX_CLOCK_RATE)
            {
                clkRate = CSL_MMC_MAX_CLOCK_RATE;
            }
        }
        else
        {
            clkRate = CSL_MMC_MAX_CLOCK_RATE;
        }
    }

    return (clkRate);
}

/**
 *
 * \brief SD_Class sdClass
 *
 *  SD Class Constructor.
 *
 * \return NONE
 */
SD_Class::SD_Class ()
{
    mmcsdHandle = (CSL_MmcsdHandle)NULL;
}

/**
 *
 * \brief delete (sdClass)
 *
 *  SD Class Destructor.
 *
 * \return NONE
 */
SD_Class::~SD_Class ()
{
    fileNodesList *currentNode;

    /* De-allocate all the memory that was previous allocated for the File
       objects of all the opened files */
    do
    {
        currentNode = fileListHeadNode;
        fileListHeadNode = fileListHeadNode->nextFileNode;

        delete (currentNode);
    } while (currentNode != NULL);

    mmcsdHandle = (CSL_MmcsdHandle)NULL;
}

/**
 *
 * \brief begin()
 *
 *  API to Initialize and Configure the SD Card
 *
 * \return TRUE  - Successful in initializing and configuring the SD Card
 *         FALSE - Unsuccessful in initializing and configuring the SD Card
 */
Bool SD_Class::begin ()
{
    return (this->begin(0));
}

/**
 *
 * \brief begin()
 *
 *  API to Initialize and Configure the SD Card
 *
 * \return TRUE  - Successful in initializing and configuring the SD Card
 *         FALSE - Unsuccessful in initializing and configuring the SD Card
 */
Bool SD_Class::begin (int opmode)
{
    CSL_Status     status;
    Uint16         clockDiv;
    Uint16         rca;
    unsigned int   diskType;
    AtaState       *ptrAtaDrive;
    AtaMMCState    *gpataMMCStateStruct;
    AtaError       ata_error;

    if ((0 != opmode) && (1 != opmode))
    {
        return (FALSE);
    }

    ptrAtaDrive         = &(this->ataDriveStruct);
    gpataMMCStateStruct = &(this->ataMMCStateStruct);

    /* Get the clock divider value for the current CPU frequency */
    clockDiv = computeClkRate();

    /* Initialize MMCSD CSL module */
    status = MMC_init();

    /* Select the Pin Muxing mode, to enable MMC/SD Module */
    status = SYS_setEBSR(CSL_EBSR_FIELD_SP0MODE,
                         CSL_EBSR_SP0MODE_0);
    status |= SYS_setEBSR(CSL_EBSR_FIELD_SP1MODE,
                         CSL_EBSR_SP1MODE_0);
    if(CSL_SOK != status)
    {
        LOG_MSG_print("SYS_setEBSR failed\n");
        return (FALSE);
    }

    /* Open MMCSD CSL module */
    if (0 == opmode)
    {
        mmcsdHandle = MMC_open(&mmcsdContObj, CSL_MMCSD0_INST,
                               CSL_MMCSD_OPMODE_POLLED, &status);
    }
    else
    {
        mmcsdHandle = MMC_open(&mmcsdContObj, CSL_MMCSD0_INST,
                               CSL_MMCSD_OPMODE_DMA, &status);
    }
    if (mmcsdHandle == NULL)
    {
        LOG_MSG_print("MMC_open Failed\n");
        return (FALSE);
    }

    /* Configure the DMA in case of operating mode is set to DMA */
    if (1 == opmode)
    {
        /* Initialize Dma */
        status = DMA_init();
        if (status != CSL_SOK)
        {
            LOG_MSG_print("DMA_init Failed!\n");
            return (FALSE);
        }

        /* Open Dma channel for MMCSD write */
        dmaWriteHandle = DMA_open(CSL_DMA_CHAN0, &dmaWriteChanObj, &status);
        if ((dmaWriteHandle == NULL) || (status != CSL_SOK))
        {
            LOG_MSG_print("DMA_open for MMCSD Write Failed!\n");
            return (FALSE);
        }

        /* Open Dma channel for MMCSD read */
        dmaReadHandle = DMA_open(CSL_DMA_CHAN1, &dmaReadChanObj, &status);
        if ((dmaReadHandle == NULL) || (status != CSL_SOK))
        {
            LOG_MSG_print("DMA_open for MMCSD Read Failed!\n");
            return (FALSE);
        }

        /* Set the DMA handle for MMC read */
        status = MMC_setDmaHandle(mmcsdHandle, dmaWriteHandle, dmaReadHandle);
        if (status != CSL_SOK)
        {
            LOG_MSG_print("API: MMC_setDmaHandle for MMCSD Failed\n");
            return (FALSE);
        }
    }

    /* Reset the SD card */
    status = MMC_sendGoIdle(mmcsdHandle);
    if(status != CSL_SOK)
    {
        LOG_MSG_print("MMC_sendGoIdle Failed\n");
        return (FALSE);
    }

    /* Check for the card */
    status = MMC_selectCard(mmcsdHandle, &mmcCardObj);
    if((status == CSL_ESYS_BADHANDLE) ||
       (status == CSL_ESYS_INVPARAMS))
    {
        LOG_MSG_print("MMC_selectCard Failed\n");
        return (FALSE);
    }

    /* Verify whether the SD card is detected or not */
    if(mmcCardObj.cardType == CSL_SD_CARD)
    {
        LOG_MSG_print("SD Card detected\n");

        /* Check if the card is high capacity card */
        if(mmcsdHandle->cardObj->sdHcDetected == TRUE)
        {
            LOG_MSG_print("SD card is High Capacity Card\n");
            LOG_MSG_print("Memory Access will use Block Addressing\n");
        }
        else
        {
            LOG_MSG_print("SD card is Standard Capacity Card\n");
            LOG_MSG_print("Memory Access will use Byte Addressing\n");
        }
    }
    else
    {
        if(mmcCardObj.cardType == CSL_CARD_NONE)
        {
            LOG_MSG_print("No Card detected\n");
        }
        else
        {
            LOG_MSG_print("SD Card not detected\n");
        }
        LOG_MSG_print("Please Insert SD Card\n");
        return (FALSE);
    }

    /* Set the init clock */
    status = MMC_sendOpCond(mmcsdHandle, 70);
    if(status != CSL_SOK)
    {
        LOG_MSG_print("MMC_sendOpCond Failed\n");
        return (FALSE);
    }

    /* Send the card identification Data */
    status = SD_sendAllCID(mmcsdHandle, &sdCardIdObj);
    if(status != CSL_SOK)
    {
        LOG_MSG_print("SD_sendAllCID Failed\n");
        return (FALSE);
    }

    /* Set the Relative Card Address */
    status = SD_sendRca(mmcsdHandle, &mmcCardObj, &rca);
    if(status != CSL_SOK)
    {
        LOG_MSG_print("SD_sendRca Failed\n");
        return (FALSE);
    }

    /* Read the SD Card Specific Data */
    status = SD_getCardCsd(mmcsdHandle, &sdCardCsdObj);
    if(status != CSL_SOK)
    {
        LOG_MSG_print("SD_getCardCsd Failed\n");
        return (FALSE);
    }

    /* Set clock for read-write access */
    status = MMC_sendOpCond(mmcsdHandle, clockDiv);
    if(status != CSL_SOK)
    {
        LOG_MSG_print("MMC_sendOpCond Failed\n");
        return (FALSE);
    }

    /* Set Endian mode for read and write operations */
    status = MMC_setEndianMode(mmcsdHandle, CSL_MMCSD_ENDIAN_LITTLE,
                                 CSL_MMCSD_ENDIAN_LITTLE);
    if(status != CSL_SOK)
    {
        LOG_MSG_print("MMC_setEndianMode Failed\n");
        return (FALSE);
    }

    /* Set block length for the memory card
     * For high capacity cards setting the block length will have
     * no effect
     */
    status = MMC_setBlockLength(mmcsdHandle, CSL_MMCSD_BLOCK_LENGTH);
    if(status != CSL_SOK)
    {
        LOG_MSG_print("MMC_setBlockLength Failed\n");
        return (FALSE);
    }


    /* Call init function initialize ATA state structure */
    gpataMMCStateStruct->hMmcSd = mmcsdHandle;
    ptrAtaDrive->pAtaMediaState = gpataMMCStateStruct;
    MMC_initState(ptrAtaDrive);

    /* Set the temp write buffer */
    ptrAtaDrive->_AtaWriteBuffer = AtaWrBuf;

    diskType  = 0;
    ata_error = ATA_systemInit(ptrAtaDrive, diskType);

    chk_mmc(ptrAtaDrive, &diskType);
    if(diskType != 0)
    {
        ata_error = ATA_systemInit(ptrAtaDrive, diskType);
        if(ata_error != ATA_ERROR_NONE)
        {
            LOG_MSG_print("ATA_systemInit Failed\n");
            LOG_MSG_print("Format the SD card\n");
            return (FALSE);
        }
    }

    LOG_MSG_print("\nATA File System Initialization successful\n");

    /* Find the first file available */
    ata_error = ATA_fileInit(ptrAtaDrive, &(this->ataFirstFileStruct));
    if(ata_error)
    {
        LOG_MSG_print("ATA_fileInit error \n");
        return (FALSE);
    }

    fileListHeadNode = new (fileNodesList);
    if (NULL == fileListHeadNode)
    {
        return (FALSE);
    }

    fileListLastNode = fileListHeadNode;
    fileListHeadNode->nextFileNode = NULL;

    return (TRUE);
}

/**
 * \brief API to extract the filename from a given file path
 *
 * \param filePath  [OUT] The string which holds the File's path
 * \param fileName  [OUT] The buffer which holds the extracted File Name
 *
 * \return NONE
 */
static void extractFileNameFromPath(char *filePath, char *fileName)
{
    char *tempPtr;
    char *prevPtr;

    tempPtr = filePath;
    prevPtr = filePath;

    /* Find the last occurence of the character '/', to extract the file name */
    do
    {
        tempPtr = strstr (tempPtr, "/");
        if (tempPtr != NULL)
        {
            prevPtr = ++tempPtr;
        }
    } while(tempPtr != NULL);

    strcpy (fileName, prevPtr);
}

/**
 * \brief API to extract the filename and extension from a given file name
 *
 * \param string    [IN]  The string which holds the File's name & Extension
 * \param fileName  [OUT] The buffer which holds the extracted File Name
 * \param extension [OUT] The buffer which holds the extracted File extension
 *
 * \return NONE
 */
static void extractFileNameAndExt (char *string, char *fileName, char *extension)
{
    char *tempPtr;
    char buffer[13];

    tempPtr = NULL;
    buffer[12] = '\0';
    strcpy (buffer, string);
    tempPtr = strstr (buffer, ".");

    if (tempPtr != NULL)
    {
        *tempPtr = '\0';
        strcpy (fileName, buffer);

        tempPtr++;
        strncpy (extension, tempPtr, 3);
        extension[3] = '\0';
    }
    else
    {
        extension[0] = '\0';
    }
}

/**
 *
 * \brief searchFile (AtaFile  *pAtaFile, char *fileNameWitExt)
 *
 *  API to search for a specific file in the ATA File System
 *
 * \param pAtaFile       [IN] AtaFile Pointer to the 1st file on the SD Card
 * \param fileNameWitExt [IN] Name of the File to be searched
 *
 * \return Pointer to an AtaFile Structure that matches the 'fileNameWitExt'
 *         file
 */
static AtaFile* searchFile (AtaFile  *pAtaFile, char *fileNameWitExt)
{
    char     FileName[256];
    char     nameUp[10];
    char     ext[10];
    char     extUp[10];
    short    counter;
    AtaError ata_error;
    char     fileName[13];

    ata_error = ATA_ERROR_NONE;

    strcpy (fileName, fileNameWitExt);
    counter = strlen (fileName) - 1;

    /* Extract the File Extension */
    while ('.' != fileName[counter])
    {
        counter--;
    }
    if (fileName[counter] == '.')
    {
        ext[0] = fileName[counter + 1];
        ext[1] = fileName[counter + 2];
        ext[2] = fileName[counter + 3];
        ext[3] = '\0';
        fileName[counter] = '\0';
    }

    /* check length of the filename */
    if (strlen(fileName) > 8)
    {
        return ((AtaFile*)NULL);
    }

    for (counter = 0; counter < strlen(fileName); counter++)
    {
        nameUp[counter] = toupper(fileName[counter]);
    }
    nameUp[counter] = 0;

    for (counter = 0; counter < strlen(ext); counter++)
    {
        extUp[counter] = toupper(ext[counter]);
    }
    extUp[counter] = 0;

    /* Find the first file in the current drive */
    ata_error = ATA_findFirst(pAtaFile);
    if (ATA_ERROR_FILE_NOT_FOUND == ata_error)
    {
        return ((AtaFile*)NULL);
    }

    /* Find the file, if it exists */
    do
    {
        // get the file name for this entry
        ata_error = ATA_getLongName(pAtaFile,
                                    &FileName[0],
                                    0,
                                    strlen(fileName) + strlen (ext) + 1);

		for (counter = 0; counter < strlen(FileName); counter++)
		{
			FileName[counter] = toupper(FileName[counter]);
		}
		FileName[counter] = 0;

        // Check whether the file name is the same or not
        if (strncmp(FileName, nameUp, strlen(nameUp)) != 0)
        {
            // if the file name is not the same, get the next entry
            ata_error = ATA_findNext(pAtaFile);
            // have we got an empty entry?
            if (ATA_ERROR_FILE_NOT_FOUND == ata_error)
            {
                break;
            }
        }
        else
        {
            // if the file name is same, compare the extension name
            for (counter = 0; counter < strlen(ext); counter++)
            {
                FileName[counter] = FileName[strlen(fileName) + 1 + counter];
            }

            if (strncmp(FileName, extUp, strlen(extUp)) != 0)
            {
                ata_error = ATA_findNext(pAtaFile);
                if (ATA_ERROR_FILE_NOT_FOUND == ata_error)
                {
                    break;
                }
            }
            else
            {
                // we have a match
                return (pAtaFile);
            }
        }
    } while (1);

    return ((AtaFile*)NULL);
}

/**
 *
 * \brief searchDirectory(pAtaFile, directoryName)
 *
 *  API to search for a specific directory in the ATA File System
 *
 * \param pAtaFile      [IN] AtaFile Pointer to the 1st file on the SD Card
 * \param directoryName [IN] Name of the directory to be searched
 *
 * \return Pointer to an AtaFile Structure that matches the 'directoryName'
 *         directory
 */
static AtaFile* searchDirectory (AtaFile  *pAtaFile, char *directoryName)
{
    char     FileName[256];
    char     nameUp[10];
    short    counter;
    AtaError ata_error;

    ata_error = ATA_ERROR_NONE;

    if (strlen(directoryName) > 8)
    {
        return ((AtaFile*)NULL);
    }

    for (counter = 0; counter < strlen(directoryName); counter++)
    {
        nameUp[counter] = toupper(directoryName[counter]);
    }
    nameUp[counter] = 0;

    // find the first file in the current directory
    ATA_findFirst(pAtaFile);

    // find the file, if it exists
    do
    {
        if (ATA_ATTR_DIRECTORY == pAtaFile->Attributes)
        {
            // get the file name for this entry
            ata_error = ATA_getLongName(pAtaFile,
                                        &FileName[0],
                                        0,
                                        strlen(directoryName));

            // Directory name is the same?
            if ((strncmp(FileName, directoryName, strlen(directoryName)) != 0) &&
                (strncmp(FileName, nameUp, strlen(nameUp)) != 0))
            {
                // if the file name is not the same, get the next entry
                ata_error = ATA_findNext(pAtaFile);
                // have we get the empty entry?
                if (ATA_ERROR_FILE_NOT_FOUND == ata_error)
                {
                    break;
                }
            }
            else
            {
                // we get the match here
                return (pAtaFile);
            }
        }
        else
        {
            ata_error = ATA_findNext(pAtaFile);
            // have we got the empty entry?
            if (ATA_ERROR_FILE_NOT_FOUND == ata_error)
            {
                break;
            }
        }
    } while (1);

    return ((AtaFile*)NULL);
}

/**
 *
 * \brief checkFilePathName(filePathName)
 *
 *  API to check whether a file/directory path is valid or not
 *
 * \param filePathName [IN] String containing the path that is to be verified
 *
 * \return TRUE  - If the file/directory path is valid
 *         FALSE - If the file/directory path is invalid
 */
static Bool checkFilePathName(char *filePathName)
{
    char *fileName;
    char *extension;
    char tempPath[256];

    if ((strlen(filePathName) > 255) || (strlen(filePathName) <= 0))
    {
        return (FALSE);
    }

    if (0 == strcmp(filePathName, "/"))
    {
        return (TRUE);
    }

    fileName  = NULL;
    extension = NULL;

    fileName = strrchr(filePathName, '/');
    if (NULL == fileName)
    {
        fileName = filePathName;
    }
    else
    {
        fileName++;
    }

    extension = strrchr(filePathName, '.');
    if ((extension != NULL) && (extension > fileName))
    {
        if (((extension - fileName) > 8) || (strlen(extension) > 4))
        {
            /* Here 'extension' will also include '.' */
            return (FALSE);
        }
    }
    else /* Here 'extension' will be NULL, if file name is a directory */
    {
        /* If the Directory path is in the form "../DIR_NAME/", extract the
           correct directory name */
        if ('/' == filePathName[strlen(filePathName) - 1])
        {
            strcpy(tempPath, filePathName);

            fileName = strrchr(tempPath, '/');
            fileName[0] = '\0';

            fileName = strrchr(tempPath, '/');
            if (NULL == fileName)
            {
                fileName = filePathName;
            }
            else
            {
                fileName++;
            }
        }

        if (strlen(fileName) > 8)
        {
            /* Length of file name is more than 8 */
            return (FALSE);
        }
    }

    return (TRUE);
}

/**
 *
 * \brief exists(filePath)
 *
 *  API to check whether a particular file exists in the ATA File System or not
 *
 * \param filePath [IN] Path of the File to be checked
 *
 * \return TRUE  - If the file exists
 *         FALSE - If the file doesn't exists
 */
Bool SD_Class::exists (char *filePath)
{
    AtaFile  *pAtaFile;
    AtaFile  *tmpAddr;
    char     directoryName[9];
    int      dirNameLen;
    char     fileName[13];
    char     *tempPtr;
    char     *prevPtr;

    prevPtr  = filePath;
    tempPtr  = filePath;

    if ((NULL == filePath) ||
        (FALSE == checkFilePathName(filePath)))
    {
		return (FALSE);
	}

    pAtaFile = new (AtaFile);
    tmpAddr  = pAtaFile;
    if (pAtaFile == NULL)
    {
        return (FALSE);
    }

    memcpy (pAtaFile, &(this->ataFirstFileStruct), sizeof(AtaFile));

    /* Navigate to the Directory path and check whether the intermediate
          directories (if any) in the path are present */
    do
    {
        tempPtr = strstr (tempPtr, "/");
        if (tempPtr != NULL)
        {
            dirNameLen = tempPtr - prevPtr;
            strncpy(directoryName, prevPtr, dirNameLen);
            directoryName[dirNameLen] = '\0';
            prevPtr = ++tempPtr;

            pAtaFile = searchDirectory (pAtaFile, directoryName);
            if (NULL == pAtaFile)
            {
                if (tempPtr != NULL)
                {
                    delete (tmpAddr);
                    return (FALSE);
                }
            }
            else
            {
                ATA_cd(pAtaFile);
            }
        }
        else
        {
            strcpy(fileName, prevPtr);
        }
    } while (tempPtr != NULL) ;

    if (NULL != tempPtr)
    {
        delete (tmpAddr);
        return (FALSE);
    }

    /* Check whether the file exists on the card or not */
    pAtaFile = searchFile (pAtaFile, fileName);
    if (NULL != pAtaFile)
    {
        delete (tmpAddr);
        return (TRUE);
    }

    delete (tmpAddr);
    return (FALSE);
}

/**
 *
 * \brief mkdir(directoryPath)
 *
 *  API to create a new directory
 *
 * \param directoryPath [IN] Path of the Directory that is to be created
 *
 * \return TRUE  - Successful in creating the requested directory
 *         FALSE - Unsuccessful in creating the requested directory
 */
Bool SD_Class::mkdir (char *directoryPath)
{
    AtaError ata_error;
    AtaFile  *pAtaFile;
    AtaFile  *parentDirAtaFile;
    AtaFile  *tmpAddr;
    AtaFile  *tmpParDirAddr;
    char     directoryName[9];
    char     extension[4];
    char     *tempPtr;
    char     *prevPtr;
    int      dirNameLen;

    /* The length of the directory path is restricted to 255 charcaters */
    if (FALSE == checkFilePathName(directoryPath))
    {
        return (FALSE);
    }

    /* Extracts file name along with its extension */
    extractFileNameFromPath(directoryPath, directoryName);
    extractFileNameAndExt(directoryName, directoryName, extension);
    if ((strlen(directoryName) > 8) || (strlen(extension) > 1))
    {
        return (FALSE);
    }

    pAtaFile         = new (AtaFile);
    parentDirAtaFile = new (AtaFile);
    tmpAddr          = pAtaFile;
    tmpParDirAddr    = parentDirAtaFile;
    prevPtr          = directoryPath;
    tempPtr          = directoryPath;

    if ((pAtaFile != NULL) && (parentDirAtaFile != NULL))
    {
        memcpy (pAtaFile, &(this->ataFirstFileStruct), sizeof(AtaFile));
        memcpy (parentDirAtaFile, &(this->ataFirstFileStruct), sizeof(AtaFile));

        /* Navigate to the directory in the path, if it doesn't exists create
           all the intermediary directories */
        do
        {
            tempPtr = strstr (tempPtr, "/");
            if (tempPtr != NULL)
            {
                dirNameLen = tempPtr - prevPtr;
                strncpy(directoryName, prevPtr, dirNameLen);
                directoryName[dirNameLen] = '\0';
                prevPtr = ++tempPtr;
            }
            else
            {
                strcpy(directoryName, prevPtr);
            }

            pAtaFile = searchDirectory (pAtaFile, directoryName);
            if (NULL == pAtaFile)
            {
                pAtaFile = tmpAddr;
                memcpy (pAtaFile, parentDirAtaFile, sizeof(AtaFile));

                ata_error = ATA_findFirst (pAtaFile);
                ata_error = ATA_setLongDirectoryName(pAtaFile, directoryName);
                if (ATA_ERROR_NONE == ata_error)
                {
                    /* Directory doesn't exists, create it */
                    ata_error = ATA_createDirectoryLong(pAtaFile, directoryName);
                    if (ATA_ERROR_NONE == ata_error)
                    {
                        pAtaFile = searchDirectory (pAtaFile, directoryName);
                        ata_error = ATA_cd(pAtaFile);
                        memcpy (parentDirAtaFile, pAtaFile, sizeof(AtaFile));
                    }
                }
                else
                {
                    delete (tmpAddr);
                    delete (tmpParDirAddr);
                    return (FALSE);
                }
            }
            else if (tempPtr != NULL)
            {
                ata_error = ATA_cd(pAtaFile);
                memcpy (parentDirAtaFile, pAtaFile, sizeof(AtaFile));
            }
        } while (tempPtr != NULL);

        delete (tmpParDirAddr);
        delete (tmpAddr);
    }

    return (TRUE);
}

/**
 * \brief API to add a new node in the Linked List of File Nodes
 *
 * \param startCluster [IN] Start Cluster no of the file to be added in the
 *                          Linked list
 *
 * \return NONE
 */
static void addFileNode (unsigned long startCluster)
{
    fileNodesList *nodeToAdd;

    nodeToAdd = new (fileNodesList);
    if (NULL != nodeToAdd)
    {
        nodeToAdd->startCluster = startCluster;
        nodeToAdd->nextFileNode = (fileNodesList *)NULL;
        /* Add the new fileNode to the End of the List of file Nodes */
        fileListLastNode->nextFileNode = nodeToAdd;
        fileListLastNode = fileListLastNode->nextFileNode;
    }
}

/**
 * \brief API to remove an already existing node from the Linked List of File
 *  Nodes
 *
 * \param nodeToDelete [IN] Address of the File Handle to be deleted from the
 *                          list
 *
 * \return NONE
 */
static void removeFileNode (fileNodesList *nodeToDelete)
{
    fileNodesList *currentNode;
    fileNodesList *previousNode;

    currentNode  = fileListHeadNode;
    previousNode = fileListHeadNode;

    /* Find the requested List node */
    while (NULL != currentNode)
    {
        if ((currentNode == nodeToDelete) &&
            (currentNode->startCluster == nodeToDelete->startCluster))
        {
            if (NULL == currentNode->nextFileNode) /* If its a Last Node */
            {
                fileListLastNode = previousNode;
            }

            previousNode->nextFileNode = currentNode->nextFileNode;
            delete (currentNode);
            break;
        }
        else
        {
            previousNode = currentNode;
            currentNode  = currentNode->nextFileNode;
        }
    }
}

/**
 * \brief API to search for a specific file in the Linked List of File Nodes
 *
 * \param startCluster [IN] Start CLuster number of the file to be searched for
 *
 * \return On successful search it returns Address of the File Node from the
 *         Linked List, else NULL pointer
 *
 */
static fileNodesList* searchFileList (unsigned long startCluster)
{
    fileNodesList *currentNode;

    currentNode = fileListHeadNode;
    while (currentNode != NULL)
    {
        if ((currentNode->startCluster != 0xFFFFFFFF)   &&
            (currentNode->startCluster == startCluster))
        {
            break; // We have found the desired node here
        }
        currentNode = currentNode->nextFileNode;
    }

    return (currentNode);
}

/**
 *
 * \brief open(filePath)
 *
 *  API to open an existing file
 *  Length of file name accepted by SD library is restricted to 8 characters
 *
 * \param filePath [IN] Path of the File that is to be opened
 *
 * \return Object of the 'File' class of the opened file
 */
File SD_Class::open (char *filePath)
{
    File          fileObj;
    AtaFile       *pAtaFile;
    AtaFile       *tmpAddr;
    fileNodesList *newFileNode;
    int           index;
    AtaError      ata_error;
    char          *tempPtr;
    char          *prevPtr;
    char          directoryName[32];
    int           dirNameLen;
    char          fileName[32];
    char          ext[4];

    prevPtr     = filePath;
    tempPtr     = filePath;
    newFileNode = (fileNodesList *)NULL;
    pAtaFile    = (AtaFile *)NULL;
    tmpAddr     = (AtaFile *)NULL;
    index       = 0;

    memset(&fileObj, 0, sizeof(File));

    if (FALSE == checkFilePathName(filePath))
    {
        return (fileObj);
    }

    fileObj.holdCharFromRead = -1;

    if (0 == strcmp(filePath, "/")) /* Request to open Root Directory */
    {
        /* Adding the File Node to the Linked list of File Nodes */
        newFileNode = new (fileNodesList);
        if (NULL != newFileNode)
        {
            newFileNode->nextFileNode = (fileNodesList *)NULL;

            /* Initialize the new File Node */
            memcpy (&(fileObj.ataFileStruct),
                    &(this->ataFirstFileStruct), sizeof(AtaFile));
            fileObj.fileMode = FILE_READ;
            fileObj.fileOpenStatus = TRUE;
            strcpy (fileObj.fileName, "/");

            fileObj.fileOrDirectory = TRUE;

            ATA_findFirst (&(fileObj.ataFileStruct));

            newFileNode->startCluster = 0;
            fileObj.startCluster      = 0;

            if (NULL != searchFileList(newFileNode->startCluster))
            {
                delete (newFileNode);
                newFileNode = NULL;
                memset(&fileObj, 0, sizeof(File));
            }
            else
            {
                /* Add this fileNode to the List of file Nodes */
                fileListLastNode->nextFileNode = newFileNode;
                fileListLastNode = fileListLastNode->nextFileNode;
            }

            return (fileObj);
        }
    }

    /* Extracts file name along with its extension */
    extractFileNameFromPath(filePath, fileName);
    extractFileNameAndExt(fileName, fileName, ext);
    if ((strlen(fileName) > 8) || (strlen(ext) > 3))
    {
        memset(&fileObj, 0, sizeof(File));
        return (fileObj);
    }

    /* Extract the file name of the requested file, which is to be opened
       Extracts file name along with its extension */
    extractFileNameFromPath(filePath, fileName);

    /* Check whether the file is present on the card */
    pAtaFile = new (AtaFile);
    tmpAddr  = pAtaFile;

    if (pAtaFile != NULL)
    {
        memcpy (pAtaFile, &(this->ataFirstFileStruct), sizeof(AtaFile));

        /* Navigate to the Directory and check whether the intermediate
          directories (if any) in the path are present */
        do
        {
            tempPtr = strstr (tempPtr, "/");
            if (tempPtr != NULL)
            {
                dirNameLen = tempPtr - prevPtr;
                strncpy(directoryName, prevPtr, dirNameLen);
                directoryName[dirNameLen] = '\0';
                prevPtr = ++tempPtr;

                pAtaFile = searchDirectory (pAtaFile, directoryName);
                if (NULL == pAtaFile)
                {
                    if (tempPtr != NULL)
                    {
                        /* Intermediate directory doesn't exists */
                        delete (tmpAddr);
                        memset(&fileObj, 0, sizeof(File));
                        return (fileObj);
                    }
                }
                else
                {
                    ata_error = ATA_cd(pAtaFile);
                }
            }
            else
            {
                /* Finished navigating to the directory */
                strcpy(fileName, prevPtr);
            }
        } while (tempPtr != NULL) ;

        if (NULL != tempPtr)
        {
            delete (tmpAddr);
            memset(&fileObj, 0, sizeof(File));
            return (fileObj);
        }

        pAtaFile = tmpAddr;

        /* Check whether the requested file to be opened is a directory or
           a file */
        while (index < strlen (fileName))
        {
            if ('.' ==  fileName[index])
            {
                break;
            }
            else
            {
                index++;
            }
        }

        if (index == strlen (fileName))
        {
            pAtaFile = searchDirectory (pAtaFile, fileName);
            if ((NULL == pAtaFile) ||
                (NULL != searchFileList((unsigned long)pAtaFile->StartCluster)))
            {
                /* Directory Not Found on the SD Card or the directory is already in use */
                delete (tmpAddr);
                memset(&fileObj, 0, sizeof(File));
                return (fileObj);
            }

            ata_error = ATA_cd(pAtaFile);
            if (ATA_ERROR_NONE != ata_error)
            {
                delete (tmpAddr);
                memset(&fileObj, 0, sizeof(File));
                return (fileObj);
            }
        }
        else
        {
            pAtaFile = searchFile (pAtaFile, fileName);
            if ((NULL == pAtaFile) ||
                (NULL != searchFileList((unsigned long)pAtaFile->StartCluster)))
            {
                /* File Not Found on the SD Card or the file is already in use */
                delete (tmpAddr);
                memset(&fileObj, 0, sizeof(File));
                return (fileObj);
            }
        }

        fileObj.startCluster = (unsigned long)pAtaFile->StartCluster;

        /* Add the File Node to the Linked list of Opened File Nodes */
        newFileNode = new (fileNodesList);
        if (NULL != newFileNode)
        {
            newFileNode->nextFileNode = (fileNodesList *)NULL;

            /* Initialize the new File Node */
            memcpy (&(fileObj.ataFileStruct),
                    pAtaFile,
                    sizeof(AtaFile));
            fileObj.fileMode = FILE_READ;
            fileObj.fileOpenStatus = TRUE;

            /* Extracts file name along with its extension */
            extractFileNameFromPath (filePath, fileObj.fileName);

            /* Add this fileNode to the List of file Nodes */
            fileListLastNode->nextFileNode = newFileNode;
            fileListLastNode = fileListLastNode->nextFileNode;

            delete (tmpAddr);

            if (ATA_ATTR_DIRECTORY == fileObj.ataFileStruct.Attributes)
            {
                fileObj.fileOrDirectory = TRUE;
                strcat (fileObj.fileName, "/");

                /* Its a directory, so find the find file under the directory.
                   Note that "." and ".." are also considered as files */
                ata_error = ATA_findFirst(&(fileObj.ataFileStruct));
                ata_error = ATA_findNext (&(fileObj.ataFileStruct));
                ata_error = ATA_findNext (&(fileObj.ataFileStruct));
            }
            newFileNode->startCluster = fileObj.startCluster;
            return (fileObj);
        }

        delete (tmpAddr);
    }

    memset(&fileObj, 0, sizeof(File));
    return (fileObj);
}

/**
 *
 * \brief open(filePath, mode)
 *
 *  API to open/create a new file
 *  Length of file name accepted by SD library is restricted to 8 characters
 *
 * \param  filePath [IN] Path of the File that is to be created
 * \param  mode     [IN] Mode of the File (Read/Write/RW)
 *
 * \return Object of the 'File' class of the opened file
 */
File SD_Class::open (char *filePath, FILE_MODE mode)
{
    File          fileObj;
    AtaError      ata_error;
    AtaFile       *pAtaFile;
    fileNodesList *newFileNode;
    char          fileName[32];
    char          extension[4];
    char          directoryName[32];
    int           dirNameLen;
    char          *tempPtr;
    char          *prevPtr;
    long          temp;

    prevPtr = filePath;
    tempPtr = filePath;

    memset(&fileObj, 0, sizeof(File));

    if ((FALSE == checkFilePathName(filePath)) ||
        ((FILE_READ != mode) && (FILE_WRITE != mode) && (FILE_APPEND != mode)))
    {
        return (fileObj);
    }

    fileObj.holdCharFromRead = -1;

    if ((FILE_WRITE == mode) || (FILE_APPEND == mode))
    {
        pAtaFile = &(fileObj.ataFileStruct);
        pAtaFile->pDrive = &ataDriveStruct;
        memcpy (pAtaFile, &(this->ataFirstFileStruct), sizeof(AtaFile));

        /* Navigate to the Directory path and check whether the intermediate
          directories (if any) in the path are present */
        do
        {
            tempPtr = strstr (tempPtr, "/");
            if (tempPtr != NULL)
            {
                dirNameLen = tempPtr - prevPtr;
                strncpy(directoryName, prevPtr, dirNameLen);
                directoryName[dirNameLen] = '\0';
                prevPtr = ++tempPtr;

                pAtaFile = searchDirectory (pAtaFile, directoryName);
                if (NULL == pAtaFile)
                {
                    if (tempPtr != NULL)
                    {
                        /* Intermediate directory doesn't exists */
                        memset(&fileObj, 0, sizeof(File));
                        return (fileObj);
                    }
                }
                else
                {
                    if (tempPtr != NULL)
                    {
                        ata_error = ATA_cd(pAtaFile);
                    }
                }
            }
            else
            {
                strcpy(fileName, prevPtr);
            }
        } while (tempPtr != NULL) ;

        if (NULL != tempPtr)
        {
            memset(&fileObj, 0, sizeof(File));
            return (fileObj);
        }

        /* Extracts file name along with its extension */
        extractFileNameFromPath(filePath, fileName);

        extractFileNameAndExt(fileName, fileName, extension);
        if ((strlen(fileName) > 8) || (strlen(extension) > 3))
        {
            memset(&fileObj, 0, sizeof(File));
            return (fileObj);
        }

        strcpy(fileName, prevPtr);

        pAtaFile = &(fileObj.ataFileStruct);

        pAtaFile = searchFile (pAtaFile, fileName);
        if (NULL != pAtaFile)
        {
            /* File already exists on the card */
            fileObj = this->open(filePath);
            if (fileObj)
            {
                fileObj.fileMode         = mode;
                fileObj.fileOpenStatus   = TRUE;

                if (FILE_APPEND == mode)
                {
                    temp = fileObj.size();
                    /* Seek to the end of the file */
                    if ((temp % 2) == 0)
                    {
                        fileObj.seek(temp);
                    }
                    else
                    {
                        /* Store the last byte */
                        fileObj.seek(temp - 1);
                        fileObj.charToFlush = fileObj.read();
                        fileObj.seek(temp - 1);

                        fileObj.ataFileStruct.Size--;
                        fileObj.flushData        = TRUE;
                        fileObj.currFilePosition = temp;
                    }
                }
            }

            if (FILE_WRITE == mode)
            {
                fileObj.ataFileStruct.Size = 0;
            }
            return (fileObj);
        }

        pAtaFile = &(fileObj.ataFileStruct);
        extractFileNameAndExt(fileName, fileName, extension);

        /* File doesn't exists on the card, create it and return the file handle */
        ata_error = ATA_setFileName(pAtaFile, fileName, extension);
        if (ATA_ERROR_NONE == ata_error)
        {
            ata_error = ATA_create(pAtaFile);
            if (ATA_ERROR_NONE != ata_error)
            {
                memset(&fileObj, 0, sizeof(File));
                return (fileObj);
            }

            newFileNode = new (fileNodesList);
            if (NULL != newFileNode)
            {
                newFileNode->nextFileNode = (fileNodesList *)NULL;

                /* Extracts file name along with its extension */
                extractFileNameFromPath (filePath, fileObj.fileName);

                /* Add this fileNode to the List of file Nodes */
                fileListLastNode->nextFileNode = newFileNode;
                fileListLastNode = fileListLastNode->nextFileNode;

                fileObj.fileMode       = mode;
                fileObj.fileOpenStatus = TRUE;

                fileObj.startCluster = (unsigned long)fileObj.ataFileStruct.StartCluster;
                newFileNode->startCluster = fileObj.startCluster;
                return (fileObj);
            }
            else
            {
                /* Error in memory allocation, delete the created file */
                ata_error = ATA_delete (pAtaFile);
                memset(&fileObj, 0, sizeof(File));
                return (fileObj);
            }
        }
        else
        {
            memset(&fileObj, 0, sizeof(File));
            return (fileObj);
        }
    }

    /* If the mode is 'Read' or the file already exists */
    fileObj = this->open(filePath);
    if (fileObj)
    {
        fileObj.fileMode       = mode;
        fileObj.fileOpenStatus = TRUE;
    }

    return (fileObj);
}

/**
 *
 * \brief remove(filePath)
 *
 *  API to delete a file
 *
 * \param filePath [IN] Path of the File to be deleted
 *
 * \return TRUE  - Successful in removing the file
 *         FALSE - Unsuccessful in removing the file
 */
Bool SD_Class::remove (char *filePath)
{
    AtaFile       *pAtaFile;
    AtaError      ata_error;
    AtaFile       *tmpAddr;
    char          fileName[13];
    char          extension[4];
    char          *tempPtr;
    char          *prevPtr;
    char          directoryName[9];
    int           dirNameLen;

    prevPtr     = filePath;
    tempPtr     = filePath;

    if (FALSE == checkFilePathName(filePath))
    {
		return (FALSE);
	}

    /* Extracts file name along with its extension */
    extractFileNameFromPath(filePath, fileName);

    extractFileNameAndExt(fileName, fileName, extension);
    if ((strlen(fileName) > 8) || (strlen(extension) > 3))
    {
        return (FALSE);
    }

    pAtaFile = new (AtaFile);
    tmpAddr  = pAtaFile;
    if (pAtaFile == NULL)
    {
        return (FALSE);
    }

    memcpy (pAtaFile, &(this->ataFirstFileStruct), sizeof(AtaFile));

    /* Navigate to the Directory path and check whether the intermediate
       directories (if any) in the path are present */
    do
    {
        tempPtr = strstr (tempPtr, "/");
        if (tempPtr != NULL)
        {
            dirNameLen = tempPtr - prevPtr;
            strncpy(directoryName, prevPtr, dirNameLen);
            directoryName[dirNameLen] = '\0';
            prevPtr = ++tempPtr;

            pAtaFile = searchDirectory (pAtaFile, directoryName);
            if (NULL == pAtaFile)
            {
                if (tempPtr != NULL)
                {
                    /* Intermediate directory doesn't exists */
                    delete (tmpAddr);
                    return (FALSE);
                }
            }
            else
            {
                ata_error = ATA_cd(pAtaFile);
            }
        }
        else
        {
            strcpy(fileName, prevPtr);
        }
    } while (tempPtr != NULL) ;

    if (NULL != tempPtr)
    {
        delete (tmpAddr);
        return (FALSE);
    }

    /* Extracts file name along with its extension */
    extractFileNameFromPath(filePath, fileName);
    pAtaFile = searchFile (pAtaFile, fileName);
    if (NULL != pAtaFile)
    {
        /* Checking whether File is already opened and is in use or not */
        if (NULL == searchFileList((unsigned long)pAtaFile->StartCluster))
        {
            /* We have navigated to the desired directory path, now delete the
               directory */
            ata_error = ATA_delete (pAtaFile);
            if (ATA_ERROR_NONE == ata_error)
            {
                delete (tmpAddr);
                return (TRUE);
            }
        }
    }

    delete (tmpAddr);
    return (FALSE);
}

/**
 *
 * \brief rmdir(directoryPath)
 *
 *  API to delete a directory
 *
 * \param directoryPath [IN] Path of the Directory to be deleted
 *
 * \return TRUE  - Successful in removing the directory
 *         FALSE - Unsuccessful in removing the directory
 */
Bool SD_Class::rmdir (char *directoryPath)
{
    AtaFile  *pAtaFile;
    AtaError ata_error;
    AtaFile  *tmpAddr;
    char     directoryName[9];
    char     extension[4];
    char     *tempPtr;
    char     *prevPtr;
    int      dirNameLen;

    if (FALSE == checkFilePathName(directoryPath))
    {
		return (FALSE);
	}

    /* Extracts file name along with its extension */
    extractFileNameFromPath(directoryPath, directoryName);
    extractFileNameAndExt(directoryName, directoryName, extension);
    if ((strlen(directoryName) > 8) || (strlen(extension) > 1))
    {
        return (FALSE);
    }

    pAtaFile = new (AtaFile);
    tmpAddr  = pAtaFile;
    prevPtr  = directoryPath;
    tempPtr  = directoryPath;

    if (pAtaFile != NULL)
    {
        memcpy (pAtaFile, &(this->ataFirstFileStruct), sizeof(AtaFile));

        /* Navigate to the Directory path and check whether the intermediate
          directories (if any) in the path are present */
        do
        {
            tempPtr = strstr (tempPtr, "/");
            if (tempPtr != NULL)
            {
                dirNameLen = tempPtr - prevPtr;
                strncpy(directoryName, prevPtr, dirNameLen);
                directoryName[dirNameLen] = '\0';
                prevPtr = ++tempPtr;
            }
            else
            {
                strcpy(directoryName, prevPtr);
            }

            pAtaFile = searchDirectory (pAtaFile, directoryName);
            if ((NULL != pAtaFile) && (NULL != tempPtr))
            {
                ata_error = ATA_cd(pAtaFile);
            }
            else
            {
                break;
            }
        } while (tempPtr != NULL);

        if (NULL == tempPtr)
        {
            /* We have navigated to the desired directory path, now delete the
               directory */
            ata_error = ATA_delete (pAtaFile);
            if (ATA_ERROR_NONE == ata_error)
            {
                delete (tmpAddr);
                return (TRUE);
            }
        }
        else
        {
            /* Intermediate directory doesn't exists */
            delete (tmpAddr);
            return (FALSE);
        }
    }

    delete (tmpAddr);
    return (FALSE);
}

/**
 *
 * \brief File fileClass
 *
 *  File Class Constructor.
 *
 * \return NONE
 */
File::File()
{
    fileOpenStatus   = FALSE;
    flushData        = FALSE;
    holdCharFromRead = -1;
    charToFlush      = -1;
    startCluster     = 0xFFFFFFFF;
    fileOrDirectory  = FALSE;
    seekIsTocurrPos  = TRUE;
    flushDataFromSeek = FALSE;
    fileName[0]      = '\0';
    currFilePosition = 0;
}

/**
 *
 * \brief File fileClass
 *
 *  File Class Copy Constructor.
 *
 * \param fileObj [IN] An existing File Object
 *
 * \return NONE
 */
File::File(const File &fileObj)
{
    charToFlush      = fileObj.charToFlush;
    flushData        = fileObj.flushData;
    holdCharFromRead = fileObj.holdCharFromRead;
    fileMode         = fileObj.fileMode;
    fileOpenStatus   = fileObj.fileOpenStatus;
    fileOrDirectory  = fileObj.fileOrDirectory;
    startCluster     = fileObj.startCluster;
    seekIsTocurrPos  = fileObj.seekIsTocurrPos;
    flushDataFromSeek= fileObj.flushDataFromSeek;
    currFilePosition = fileObj.currFilePosition;

    strcpy (fileName, fileObj.fileName);
    memcpy (&ataFileStruct, &(fileObj.ataFileStruct), sizeof(AtaFile));
}

/**
 *
 * \brief available()
 *
 *  API to Check if there are any bytes available for reading from the file
 *
 * \return Number of bytes available, that can be read
 */
unsigned long File::available ()
{
    unsigned long availableBytes;

    availableBytes = 0;
    if (this->fileOpenStatus == TRUE)
    {
        /* Bytes available to read is: File size minus current file seek
           position */
        availableBytes = this->size() - this->position();
    }

    return (availableBytes);
}

/**
 *
 * \brief close()
 *
 *  API to Close an opened file
 *
 * \return NONE
 */
void File::close ()
{
    AtaError       ata_error;
    fileNodesList *fileNode;

    if (this->fileOpenStatus == TRUE)
    {
        if (FALSE == this->isDirectory())
        {
            if (this->available())
            {
				this->seek(this->size());
			}
            /* Flush any data which is pending to be written */
            this->flush();

            ata_error = ATA_close(&(this->ataFileStruct));
        }
        else
        {
            ata_error = ATA_ERROR_NONE;
        }

        if (ATA_ERROR_NONE == ata_error)
        {
            this->fileOpenStatus = FALSE;

            /* Delete the file node from the list of opened file nodes */
            fileNode = searchFileList (this->startCluster);
            if (NULL != fileNode)
            {
                memset (&(this->ataFileStruct), 0, sizeof (AtaFile));
                removeFileNode (fileNode);
            }
        }
    }
}

/**
 *
 * \brief flush()
 *
 *  API to ensure that any bytes written to the file are physically saved to
 *  the SD card
 *
 * \return NONE
 */
void File::flush ()
{
    AtaUint16 dataToWrite;
    AtaError  ata_error;

    if ((this->fileOpenStatus != TRUE) ||
        ((this->fileMode == FILE_WRITE) && (this->fileMode == FILE_APPEND)))
    {
        return;
    }

    if (TRUE == this->flushData)
    {
        /* Setting Size as current File Pointer position, it will be valid
           when User seeks to some position (other than EOF) of the file */
        this->ataFileStruct.Size = (this->position() / 2) * 2;

        dataToWrite = (AtaUint16)(this->charToFlush & 0xFF);
        dataToWrite = (dataToWrite << 8);

        ata_error = ATA_write (&(this->ataFileStruct), &dataToWrite, 1);
        if (ATA_ERROR_NONE == ata_error)
        {
            /* Since we are writing only 1 byte, decrement file size by 1.
               ATA_write with a single data element will increment the file
               size by 2bytes */
            this->ataFileStruct.Size--;
            this->charToFlush = 0;
            this->flushData   = FALSE;
            this->currFilePosition++;
        }
    }
}

/**
 *
 * \brief peek()
 *
 *  API to Read a byte from the file without advancing to the next one
 *
 * \return The character that is read from the file
 */
char File::peek ()
{
    char          retValue;
    unsigned long currentPosition;
    AtaError      ata_error;
    AtaUint16     dataToRead;

    retValue = -1;
    if (this->fileOpenStatus == TRUE)
    {
        if (-1 == this->holdCharFromRead)
        {
            /* Obtain the current seek position */
            currentPosition = this->position();

            dataToRead = 0;
            ata_error = ATA_read (&(this->ataFileStruct), &dataToRead, 1);
            if ((ATA_ERROR_NONE == ata_error) || (ATA_ERROR_EOF == ata_error))
            {
                retValue = (char)(dataToRead & 0xFF00);
                retValue = (retValue >> 8);

                /* Seek to the current seek position obtained previously */
                this->seek(currentPosition);
            }
        }
        else
        {
            /* Return the data that was read from previous User Read Operation */
            retValue = this->holdCharFromRead;
        }
    }

    return (retValue);
}

/**
 *
 * \brief position()
 *
 *  API to Get the current position to which the next byte will be read from or
 *  written to
 *
 * \return The location to which the next byte will be read from or written to
 */
unsigned long File::position ()
{
    if (this->fileOpenStatus == TRUE)
    {
        /* Get the current file seek position */
        return (this->currFilePosition);
    }

    return (0);
}

/**
 * \brief API to pack a String which is in byte format into Word format
 *
 * \param valAsString [IN]  String which is in bytes
 * \param writeBuffer [OUT] The output Packed buffer
 * \param length      [IN]  Length of the String in bytes
 *
 * \return
 */
static void packDataToUint16(char      *valAsString,
                             AtaUint16 writeBuffer[],
                             int       length)
{
    int index;

    /* Pack the bytes of the buffer 'valAsString', into Words (16 bit) */
    for (index = 0; index < length;)
    {
        writeBuffer[index/2] = (AtaUint16)(valAsString[index] & 0xFF);
        writeBuffer[index/2] = writeBuffer[index/2] << 8;
        writeBuffer[index/2] |= (AtaUint16)(valAsString[index + 1] & 0xFF);
        index += 2;
    }
}

/**
 *
 * \brief print(character)
 *
 *  API to Print an ASCII character to the file
 *
 * \param character [IN] The ASCII character to be printed to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::print (char character)
{
    AtaError  ata_error;
    AtaUint16 dataToWrite;

    if ((this->fileOpenStatus == TRUE) &&
        ((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)))
    {
        /* Setting Size as current File Pointer position, it will be valid
           when User seeks to some position (other than EOF) of the file */
        this->ataFileStruct.Size = (this->position() / 2) * 2;

        /* Check whether data is already there to be flushed or not */
        if (TRUE == this->flushData)
        {
            if (this->seekIsTocurrPos == FALSE)
            {
                this->holdCharFromRead = -1;
                this->seekIsTocurrPos  = TRUE;
            }

            dataToWrite = (this->charToFlush & 0xFF) << 8;
            dataToWrite |= (character & 0xFF);

            ata_error = ATA_write (&(this->ataFileStruct), &dataToWrite, 1);
            if (ATA_ERROR_NONE == ata_error)
            {
                this->charToFlush       = 0;
                this->flushData         = FALSE;
                this->flushDataFromSeek = FALSE;
                this->currFilePosition++;
                return (1);
            }
        }
        else
        {
            /* Store the character in the flush data variable */
            this->charToFlush       = character;
            this->flushData         = TRUE;
            this->flushDataFromSeek = FALSE;
            this->currFilePosition++;
            return (1);
        }
    }

    return (0);
}

/**
 *
 * \brief print(printString)
 *
 *  API to Print a String(character array) to the file
 *
 * \param printString [IN] The String to be printed to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::print (char *printString)
{
    AtaError  ata_error;
    AtaUint16 *ataString;
    int       strLength;
    char      data;
    int       retValue;

    ataString = NULL;

    if ((this->fileOpenStatus == TRUE) &&
        ((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)) &&
        (printString != NULL) &&
        (strlen(printString) > 0))
    {
        strLength = strlen (printString);
        retValue  = strlen (printString);

        ataString = (AtaUint16 *)malloc(sizeof(AtaUint16) * strLength / 2);

        /* Check whether data is already there to be flushed */
        if (TRUE == this->flushData)
        {
            data = printString[0];
            this->print(data);
            printString++;
            strLength--;
        }

        if (1 == strLength)
        {
            this->flushData   = TRUE;
            this->charToFlush = printString[0];
            this->currFilePosition++;
            free(ataString);
            return (retValue);
        }

        /* Setting Size as current File Pointer position, it will be valid
           when User seeks to some position (other than EOF) of the file */
        this->ataFileStruct.Size = (this->position() / 2) * 2;

        /* Pack the bytes in a 16-bit integer Array */
        packDataToUint16 (printString, ataString, strLength);
        ata_error = ATA_write (&(this->ataFileStruct),
                               ataString,
                               strLength / 2);
        if (ATA_ERROR_NONE == ata_error)
        {
            this->currFilePosition += strLength;

            /* If the user requests odd no of bytes to write, hold the last byte
               in the 'flushData' variable */
            if (0 != (strLength % 2) )
            {
                this->flushData   = TRUE;
                this->charToFlush = printString[strLength - 1];
            }
            free(ataString);

            return (retValue);
        }

        free(ataString);
    }

    return (0);
}

/**
 *
 * \brief print(integer)
 *
 *  API to Print a 16 Bit integer(int) to the file
 *
 * \param integer [IN] The 16 Bit integer(int) to be printed to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::print (int integer)
{
    return (this->print((long)integer));
}

/**
 *
 * \brief print(integer)
 *
 *  API to Print a 32 Bit integer(long) to the file
 *
 * \param integer [IN] The 32 Bit integer(long) to be printed to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::print (long integer)
{
    char valAsString[20];
    int  retValue;

    retValue = 0;
    if ((this->fileOpenStatus == TRUE) &&
        ((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)))
    {
        /* Convert the integer to character array */
        retValue = sprintf(valAsString, "%ld", integer);
        valAsString[retValue] = '\0';

        retValue = this->print(valAsString);
        return (retValue);
    }

    return (0);
}

/**
 *
 *  \brief print(value)
 *
 *  API to Print a Floating Point Value to the file as human-readable ASCII text
 *
 * \param value [IN] Floating Point value that is to be written to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::print (float value)
{
    char valAsString[30];
    int  retValue;

    retValue = 0;
    if ((this->fileOpenStatus == TRUE) &&
        ((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)))
    {
        /* Convert the float to character array */
        retValue = sprintf(valAsString, "%.7f", value);
        valAsString[retValue] = '\0';

        retValue = this->print(valAsString);
        return (retValue);
    }

    return (0);
}

/**
 *
 *  \brief print(value)
 *
 *  API to Print a Double Precision Floating Point Value to the file as
 *  human-readable ASCII text
 *
 * \param value [IN] Double Precision Floating Point value that is to be
 *                   written to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::print (double value)
{
    char valAsString[30];
    int  retValue;

    retValue = 0;
    if ((this->fileOpenStatus == TRUE) &&
        ((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)))
    {
        /* Convert the float to character array */
        retValue = sprintf(valAsString, "%.15f", value);
        valAsString[retValue] = '\0';

        retValue = this->print(valAsString);
        return (retValue);
    }

    return (0);
}

/**
 *
 *  convertDecToBinOct(value, convString, base)
 *
 *  API to Convert a Decimal value to either Binary or Octal Form
 *
 *  int value        <-- The integer value that is to be converted
 *  char *convString <-- Character String to hold the converted value
 *  int base         <-- Indicates the base to which the decimal value needs
 *                       to be converted
 */
static void convertDecToBinOct (long value, char *convString, int base)
{
    int  index;
    int  strLength;
    char tempChar;

    if (value != 0)
    {
        index = 0;
        while (value > 0)
        {
            convString[index] = (value % base) + '0';

            value /= base;
            index++;
        }
        convString[index] = '\0';

        strLength = index;
        index     = 0;
        while (index < (strLength / 2))
        {
            tempChar = convString[index];
            convString[index] = convString[strLength - index - 1];
            convString[strLength - index - 1] = tempChar;
            index++;
        }
    }
    else
    {
        convString[0] = '0';
        convString[1] = '\0';
    }
}

/**
 *
 * \brief print(integer, base)
 *
 *  API to Print an integer in a specified base format to the file
 *
 * \param integer [IN] The integer to be printed to the file
 * \param base    [IN] The base in which to print numbers
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::print (long integer, NUMBER_FORMAT_BASE base)
{
    char valAsString[50];
    int  retValue;

    if ((base >= FILE_BIN) && (base <= FILE_HEX))
    {
		if ((this->fileOpenStatus == TRUE) &&
			((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)))
		{
			switch (base)
			{
				case FILE_BIN:
					convertDecToBinOct (integer, valAsString, 2);
					break;

				case FILE_OCT:
					retValue = sprintf(valAsString, "%o", integer);
					valAsString[retValue] = '\0';
					break;

				case FILE_DEC:
					retValue = sprintf(valAsString, "%ld", integer);
					valAsString[retValue] = '\0';
					break;

				case FILE_HEX:
					retValue = sprintf(valAsString, "0x%X", integer);
					valAsString[retValue] = '\0';
					break;

				default:
					return (0);
			}

			return (this->print(valAsString));
		}
	}

    return (0);
}

/**
 *
 * \brief println()
 *
 *  API to Print a carriage return and newline to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::println(void)
{
    char valAsString[3];

    if ((this->fileOpenStatus == TRUE) &&
        ((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)))
    {
        valAsString[0] = '\r';
        valAsString[1] = '\n';
        valAsString[2] = '\0';

        return (this->print(valAsString));
    }

    return (0);
}

/**
 *
 * \brief println(character)
 *
 *  API to Print an ASCII character, followed by a carriage return and newline
 *  to the file
 *
 * \param character [IN] The ASCII character to be printed to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::println (char character)
{
    int retValue;

    retValue = this->print (character);
    if (retValue != 0)
    {
        retValue += this->println();
    }

    return (retValue);
}

/**
 *
 * \brief println(printString)
 *
 *  API to Print a String(character array), followed by a carriage return and
 *  newline to the file
 *
 * \param printString [IN] The String to be printed to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::println (char *printString)
{
    int retValue;

    retValue = this->print (printString);
    if (retValue != 0)
    {
        retValue += this->println();
    }

    return (retValue);
}

/**
 *
 * \brief println(integer)
 *
 *  API to Print an integer, followed by a carriage return and newline to the
 *  file
 *
 * \param integer [IN] The integer to be printed to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::println (int integer)
{
    return (this->println((long)integer));
}

/**
 *
 * \brief println(integer)
 *
 *  API to Print an integer, followed by a carriage return and newline to the
 *  file
 *
 * \param integer [IN] The integer to be printed to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::println (long integer)
{
    int retValue;

    retValue = this->print (integer);
    if (retValue != 0)
    {
        retValue += this->println();
    }

    return (retValue);
}

/**
 *
 *  \brief print(value)
 *
 *  API to Print a Floating Point Value to the file as human-readable ASCII
 *  text, followed by a carriage return and newline to the file
 *
 * \param value [IN] Floating Point value that is to be written to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::println (float value)
{
    int retValue;

    retValue = this->print(value);
    if (retValue != 0)
    {
        retValue += this->println();
    }

    return (retValue);
}

/**
 *
 *  \brief print(value)
 *
 *  API to Print a Double Precision Floating Point Value to the file as
 *  human-readable ASCII text, followed by a carriage return and newline to the
 *  file
 *
 * \param value [IN] Double Precision  Floating Point value that is to be
 *                   written to the file
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::println (double value)
{
    int retValue;

    retValue = this->print(value);
    if (retValue != 0)
    {
        retValue += this->println();
    }

    return (retValue);
}

/**
 *
 * \brief println(integer, base)
 *
 *  API to Print an integer in a specified base format, followed by a carriage
 *  return and newline to the file
 *
 * \param integer [IN] The integer to be printed to the file
 * \param base    [IN] The base in which to print numbers
 *
 * \return The number of bytes printed to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::println (long integer, NUMBER_FORMAT_BASE base)
{
    int retValue;

    retValue = this->print (integer, base);
    if (retValue != 0)
    {
        retValue += this->println();
    }

    return (retValue);
}

/**
 *
 * \brief seek(posValue)
 *
 *  API to Seek to a new position in the file, which must be between 0 and the
 *  size of the file
 *
 * \param posValue [IN] The position to which to seek
 *
 * \return TRUE  - Successful in seeking to the requested position
 *         FALSE - Unsuccessful in seeking to the requested position
 */
Bool File::seek (unsigned long posValue)
{
    AtaError  ata_error;
    AtaUint16 dataRead;

    if ((this->fileOpenStatus == TRUE) && (posValue <= this->size()))
    {
        if (this->flushDataFromSeek == FALSE)
        {
            this->flush(); /* Flush any remaining data */
        }

        this->holdCharFromRead  = -1;
        this->seekIsTocurrPos   = TRUE;
        this->flushDataFromSeek = FALSE;
        this->flushData         = FALSE;

        ata_error = ATA_seek (&(this->ataFileStruct), (AtaUint32)posValue / 2);
        if (ATA_ERROR_NONE == ata_error)
        {
            if (posValue % 2) /* If request is to Seek odd no of bytes */
            {
                /* Read the next word and hold the LSB for next read
                   operation, also hold the MSB for next write operation */
                ata_error = ATA_read (&(this->ataFileStruct), &dataRead, 1);
                if ((ATA_ERROR_NONE == ata_error) || (ATA_ERROR_EOF == ata_error))
                {
                    if (ATA_ERROR_NONE == ata_error)
                    {
                        this->holdCharFromRead = dataRead & 0xFF;
                    }

                    ata_error = ATA_seek (&(this->ataFileStruct), (AtaUint32)posValue / 2);
                    this->seekIsTocurrPos = FALSE;

                    if (this->fileMode != FILE_READ)
                    {
                        this->charToFlush = (dataRead & 0xFF00) >> 8;
                        this->flushData   = TRUE;
                        this->flushDataFromSeek = TRUE;
                    }
                }
            }

            this->currFilePosition = posValue;
            return (TRUE);
        }
    }

    return (FALSE);
}

/**
 *
 * \brief size()
 *
 *  API to Get the size of the file
 *
 * \return The size of the file in bytes
 */
unsigned long File::size ()
{
    unsigned long fileSize;

    fileSize = 0;
    if (this->fileOpenStatus == TRUE)
    {
        fileSize = (unsigned long)this->ataFileStruct.Size;

        if ((TRUE == this->flushData) && ((FALSE == this->flushDataFromSeek)))
        {
            fileSize++;
        }
    }

    return (fileSize);
}

/**
 *
 * \brief read()
 *
 *  API to Read a byte from the file
 *
 * \return The next byte (or character)
 *         -1 if no data is available
 */
char File::read ()
{
    char       readCharacter;
    AtaUint16  dataToRead;
    AtaError   ata_error;

    if (this->fileOpenStatus == TRUE)
    {
        if (this->seekIsTocurrPos == FALSE)
        {
            ata_error = ATA_read (&(this->ataFileStruct), &dataToRead, 1);
            this->seekIsTocurrPos = TRUE;
        }

        /* ATA_read() will return 2 bytes as a single data element, so check
           whether any data is already read in previous calls to ATA_read(which
           will be stored in holdCharFromRead variable) */
        if (-1 == this->holdCharFromRead)
        {
            ata_error = ATA_read (&(this->ataFileStruct), &dataToRead, 1);
            if (ATA_ERROR_NONE == ata_error)
            {
                this->holdCharFromRead = (dataToRead & 0xFF);
                readCharacter = ((dataToRead & 0xFF00) >> 8);

                this->currFilePosition++;
                return (readCharacter);
            }
            else if (ATA_ERROR_EOF == ata_error)
            {
                if (1 == (this->ataFileStruct.CurrentByte - this->ataFileStruct.Size))
                {
                    readCharacter = ((dataToRead & 0xFF00) >> 8);
                    this->holdCharFromRead = -1;
                    this->currFilePosition++;
                    return (readCharacter);
                }
            }
            else
            {
                return (-1);
            }
        }
        else
        {
            readCharacter = this->holdCharFromRead;
            this->holdCharFromRead = -1;
            this->currFilePosition++;
            return (readCharacter);
        }
    }

    return (-1);
}

/**
 *
 * \brief read(buffer, length)
 *
 *  API to Read an array of bytes from the file
 *
 * \param buffer [IN] The Buffer to hold the data read from the file
 * \param length [IN] The length of the data to be read, in no of bytes
 *
 * \return The number of bytes read from the file
 *         Else zero, if the file is not opened
 */
int File::read (char *buffer, int length)
{
    AtaError      ata_error;
    int           index;
    int           retValue;
    unsigned long curValue;

    retValue = 0;
    if ((this->fileOpenStatus == TRUE) &&
        (buffer != NULL) &&
        (length > 0))
    {
        curValue = this->position();

        /* Check whether any data is already read in previous calls(which will
           be stored in holdCharFromRead variable) */
        if (this->holdCharFromRead != -1)
        {
            buffer[0] = this->read();

            buffer++; /* Incrementing the buffer pointer, so that the data in
                         'holdCharFromRead' variable will be stored later */
            length--;
            retValue++;
        }

        memset(buffer, 0, length);
        ata_error = ATA_read (&(this->ataFileStruct),
                              (AtaUint16 *)buffer,
                              (length / 2));
        if (ATA_ERROR_NONE != ata_error)
        {
            /* Revert back to previous read state */
            this->seek(curValue);
            if (1 == retValue)
            {
                this->holdCharFromRead = buffer[-1];
            }

            return (0);
        }

        index = (length / 2) * 2;

        /* Unpacking the 16-bit Integer to individual bytes */
        while (index != 0)
        {
            buffer[index - 1] = ((buffer[index / 2 - 1]) & 0x00FF);
            buffer[index - 2] = ((buffer[index / 2 - 1]) & 0xFF00) >> 8;
            index -= 2;
        }

        /* If length is an odd number(No of bytes to read is odd) */
        if (length % 2)
        {
            buffer[length - 1] = this->read();
        }
    }
    else
    {
        return (0);
    }

    this->currFilePosition += length;
    return (retValue + length);
}

/**
 *
 * \brief read(buffer, length)
 *
 *  API to Read an array of Words (16 bits) from the file
 *
 * \param buffer [IN] The Buffer to hold the data read from the file
 * \param length [IN] The length of the data to be read, in no of Words (16 bits)
 *
 * \return The number of Words read from the file
 *         Else zero, if the file is not opened
 */
int File::read (int *buffer, int length)
{
    AtaError      ata_error;
    int           retValue;
    unsigned long curValue;

    retValue = 0;
    if ((this->fileOpenStatus == TRUE) &&
        (buffer != NULL) &&
        (length > 0))
    {
        curValue = this->position();

        /* Check whether any data is already read in previous calls(which will
           be stored in holdCharFromRead variable) */
        if (this->holdCharFromRead != -1)
        {
            buffer[0] = this->read();

            buffer++; /* Incrementing the buffer pointer, so that the data in
                         'holdCharFromRead' variable will be stored later */
            length--;
            retValue++;
        }

        memset(buffer, 0, length);
        ata_error = ATA_read (&(this->ataFileStruct),
                              (AtaUint16 *)buffer,
                              length);
        if (ATA_ERROR_NONE != ata_error)
        {
            /* Revert back to previous read state */
            this->seek(curValue);
            if (1 == retValue)
            {
                this->holdCharFromRead = buffer[-1];
            }

            return (0);
        }
    }
    else
    {
        return (0);
    }

    this->currFilePosition += (2 *length);
    return (retValue + length);
}

/**
 *
 * \brief write(character)
 *
 *  API to Write an ASCII character to the file
 *
 * \param character [IN] The ASCII character to be written to the file
 *
 * \return The number of bytes written to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::write (char character)
{
    return(this->print (character));
}

/**
 *
 * \brief write(integer)
 *
 *  API to Write an integer to the file
 *
 * \param integer [IN] The integer to be written to the file
 *
 * \return The number of bytes written to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::write (long integer)
{
    return(this->print (integer));
}

/**
 *
 * \brief write(printString)
 *
 *  API to Write a String(character array) to the file
 *
 * \param printString [IN] The String to be written to the file
 *
 * \return The number of bytes written to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::write (char *printString)
{
    return(this->print (printString));
}

/**
 *
 * \brief writeData(fileHandle, buffer, length)
 *
 *  API to Write a String(character array) of specified length to the file
 *
 * \param fileHandle [IN] Pointer to the File object
 * \param buffer     [IN] The buffer to be written to the file
 * \param length     [IN] Length of the buffer to be written
 *
 * \return The number of bytes written to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::writeData(File *fileHandle, char *buffer, int length)
{
    AtaError  ata_error;
    AtaUint16 *ataString;
    char      data;
    int       retValue;

    retValue  = length;
    ataString = NULL;

    /* Check whether data is already there to be flushed */
    if (TRUE == fileHandle->flushData)
    {
        data = buffer[0];
        fileHandle->print(data);
        buffer++;
        length--;
    }

    ataString = (AtaUint16 *)malloc(sizeof(AtaUint16) * length / 2);

    /* Pack the bytes in a 16-bit integer Array */
    packDataToUint16 (buffer, ataString, length);
    ata_error = ATA_write (&(fileHandle->ataFileStruct),
                           ataString,
                           length / 2);
    if (ATA_ERROR_NONE == ata_error)
    {
        /* If the user requests odd no of bytes to write, hold the last byte
               in the 'flushData' variable */
        if (0 != (length % 2) )
        {
            fileHandle->flushData   = TRUE;
            fileHandle->charToFlush = buffer[length - 1];
        }
        free(ataString);
        return (retValue);
    }
    free(ataString);

    return (0);
}

/**
 *
 * \brief write(buffer, length)
 *
 *  API to Write a String(character array) of specified length to the file
 *
 * \param buffer [IN] The String to be written to the file
 * \param length [IN] The length of the String to be written
 *
 * \return The number of bytes written to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::write (char *buffer, int length)
{
    char *startAddr;
    int  retValue;
    int  noOfBytesWritten;

    retValue         = 0;
    noOfBytesWritten = 0;
    startAddr        = buffer;
    writeCacheBuffer[WRITE_CACHE_SIZE]  = '\0';

    if ((this->fileOpenStatus == TRUE) &&
        ((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)) &&
        (buffer != NULL) &&
        (length > 0))
    {
        /* Setting Size as current File Pointer position, it will be valid
           when User seeks to some position (other than EOF) of the file */
        this->ataFileStruct.Size = (this->position() / 2) * 2;

        while (length > WRITE_CACHE_SIZE)
        {
            /* Writing data in chunks of 512 bytes */
            memcpy (writeCacheBuffer, startAddr, WRITE_CACHE_SIZE);
            retValue = writeData(this, writeCacheBuffer, WRITE_CACHE_SIZE);

            if (0 == retValue)
            {
                return (0);
            }

            this->currFilePosition += WRITE_CACHE_SIZE;

            startAddr += WRITE_CACHE_SIZE;
            length    -= WRITE_CACHE_SIZE;
            noOfBytesWritten += retValue;
        }

        if (length != 0)
        {
            /* Write the left over bytes, which are lesser than 512 bytes */
            memcpy (writeCacheBuffer, startAddr, length);
            writeCacheBuffer[length] = '\0';
            retValue = writeData(this, writeCacheBuffer, length);
            if (0 == retValue)
            {
                return (0);
            }
            this->currFilePosition += length;
            noOfBytesWritten += length;
        }
    }

    return (noOfBytesWritten);
}

/**
 *
 * \brief write(buffer, length)
 *
 *  API to Write an Array of words, of specified length to the file
 *
 * \param buffer [IN] The Buffer (containing array of words) to be written to
 *                    the file
 * \param length [IN] No of Words (16 bits) to be written
 *
 * \return The number of Words written to the file
 *         Else zero, if the file is not opened or for invalid file operation
 */
int File::write (int *buffer, int length)
{
    int       noOfBytesWritten;
    AtaError  ata_error;
    AtaUint16 temp;

    noOfBytesWritten = 0;

    if ((this->fileOpenStatus == TRUE) &&
        ((this->fileMode == FILE_WRITE) || (this->fileMode == FILE_APPEND)) &&
        (buffer != NULL) &&
        (length > 0))
    {
        /* Setting Size as current File Pointer position, it will be valid
           when User seeks to some position (other than EOF) of the file */
        this->ataFileStruct.Size = (this->position() / 2) * 2;

        if (TRUE == this->flushData)
        {
            if (this->seekIsTocurrPos == FALSE)
            {
                this->holdCharFromRead = -1;
                this->seekIsTocurrPos  = TRUE;
            }

            temp = ((AtaUint16)this->charToFlush << 8);

            ata_error = ATA_write (&(this->ataFileStruct),
                                   &temp,
                                   1);

            if (ATA_ERROR_NONE == ata_error)
            {
                this->flushData   = FALSE;
                this->charToFlush = 0;
                this->currFilePosition += 2;
            }
        }

        ata_error = ATA_write (&(this->ataFileStruct),
                               (AtaUint16 *)buffer,
                               length);
        if (ATA_ERROR_NONE == ata_error)
        {
            this->currFilePosition += (2 * length);
            noOfBytesWritten = length;
        }
    }

    return (noOfBytesWritten);
}

/**
 *
 * \brief isDirectory()
 *
 *  API to report if the current file is a directory or not
 *
 * \return TRUE  - If the current file is a Directory
 *         FALSE - If the current file is not a Directory
 */
Bool File::isDirectory ()
{
    Bool retStatus;

    retStatus = FALSE;

    if ((this->fileOpenStatus == TRUE) &&
        (this->fileOrDirectory == TRUE))
    {
        retStatus = TRUE;
    }

    return (retStatus);
}

/**
 *
 * \brief openNextFile()
 *
 *  API to report the next file or folder in a directory
 *
 * \return Pointer to the 'File' class of the next file
 */
File File::openNextFile ()
{
    File          nextFileObj;
    AtaFile       *pAtaFile;
    AtaError      ata_error;
    int           index;

    memset(&nextFileObj, 0, sizeof(File));

    if ((this->fileOpenStatus != TRUE) ||
        (FALSE == this->fileOrDirectory))
    {
        return (nextFileObj);
    }

    if (this->ataFileStruct.Attributes)
    {
        pAtaFile = &(nextFileObj.ataFileStruct);
        memcpy (pAtaFile, &(this->ataFileStruct), sizeof(AtaFile));

        /* Initializing the Next File Handle */
        nextFileObj.fileMode       = FILE_READ;
        nextFileObj.fileOpenStatus = TRUE;
        strcpy (nextFileObj.fileName, pAtaFile->Filename);

        index = strlen(nextFileObj.fileName) - 1;
        nextFileObj.startCluster = (unsigned long)nextFileObj.ataFileStruct.StartCluster;

        /* Removing spaces are the end of file name */
        while (' ' == nextFileObj.fileName[index])
            index--;

        nextFileObj.fileName[index + 1] = '\0';

        if (ATA_ATTR_DIRECTORY == nextFileObj.ataFileStruct.Attributes)
        {
            /* Since its a directory, go inside the directory and find the 1st
               file under it, other than '.' and '..' files */
            strcat (nextFileObj.fileName, "/");
            nextFileObj.fileOrDirectory = TRUE;

            ata_error = ATA_cd(pAtaFile);
            if (ATA_ERROR_NONE != ata_error)
            {
                memset(&nextFileObj, 0, sizeof(File));
                return (nextFileObj);
            }

            ata_error = ATA_findFirst (pAtaFile);
            if (ATA_ERROR_NONE != ata_error)
            {
                memset(&nextFileObj, 0, sizeof(File));
                return (nextFileObj);
            }

            ata_error = ATA_findNext (pAtaFile);
            ata_error |= ATA_findNext (pAtaFile);
        }
        else
        {
            /* Since its file append the file extension to the file name */
            strcat (nextFileObj.fileName, ".");
            strcat (nextFileObj.fileName, pAtaFile->Ext);

            index = strlen(nextFileObj.fileName) - 1;

            /* Removing spaces are the end of file extension */
            while (' ' == nextFileObj.fileName[index])
                index--;
            nextFileObj.fileName[index + 1] = '\0';
        }

        ata_error = ATA_ERROR_NONE;
        while (1)
        {
            /* Find the next file under the Parent directory, which triggered
               the current 'openNextFile' API call */
            ATA_findNext (&(this->ataFileStruct));

            if ((this->ataFileStruct.Filename[0] == '.') &&
                (this->ataFileStruct.Filename[1] == '.') &&
                (this->ataFileStruct.Filename[2] == ' '))
            {
                ata_error |= ATA_findNext (&(this->ataFileStruct));
            }
            else if ((this->ataFileStruct.Filename[0] == '.') &&
                     (this->ataFileStruct.Filename[1] == ' '))
            {
                ata_error |= ATA_findNext (&(this->ataFileStruct));
            }
            else
            {
                break;
            }
        }

        if (ATA_ERROR_NONE != ata_error)
        {
            /* Next file not found */
            delete (&nextFileObj);
            memset(&nextFileObj, 0, sizeof(File));
            return (nextFileObj);
        }

        addFileNode(nextFileObj.startCluster);
        return (nextFileObj);
    }

    return (nextFileObj);
}

/**
 *
 * \brief rewindDirectory()
 *
 *  API to go back to the first file in the directory
 *
 * \return NONE
 */
void File::rewindDirectory ()
{
    if ((TRUE != this->fileOpenStatus) ||
        (FALSE == this->fileOrDirectory))
    {
        return;
    }

    ATA_findFirst (&this->ataFileStruct);
}

/**
 *
 * \brief getName(fileName)
 *
 *  API to get the name of the File
 *
 * \param fileName [IN] Buffer to hold the name of the file
 *
 * \return NONE
 */
void File::getName(char *fileName)
{
    if (fileName != NULL)
    {
		strcpy(fileName, this->fileName);
	}
}

/**
 * \brief API to print Debug messages
 *
 * This API will print the messages to either the Serial or the Output Console
 */
void LOG_MSG_print (char *printString)
{
#ifdef ENABLE_SERIAL_MSGS
    Serial.print(printString);
#else
    printf(printString);
#endif
}
