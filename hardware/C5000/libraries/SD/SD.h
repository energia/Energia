//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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
/** @file SD.h
 *
 *  @brief SD library header file
 *
 */

#ifndef _SD_H_
#define _SD_H_

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "ata.h"
#include "csl_mmcsd.h"
#include "csl_sysctrl.h"
#include "csl_pll.h"
#include "chk_mmc.h"

/* Note: SD Library requires SD card to be formatted in a specific
         format for proper operation. It is recommended to use
         SD formatter from SD card org or HP format tool for
         formatting the SD card
*/

/**
 * \brief Enum to indicate the Mode of the file for opening
 */
typedef enum FILE_MODE
{
    FILE_READ,
    FILE_WRITE,
    FILE_APPEND
} FILE_MODE;

/**
 * \brief Enum to indicate base format for an integer
 */
typedef enum NUMBER_FORMAT_BASE
{
    FILE_BIN,
    FILE_OCT,
    FILE_DEC,
    FILE_HEX
} NUMBER_FORMAT_BASE;

class SD_Class;

/**
 * \brief File Class
 *
 * The File class allows for reading from and writing to individual files on
 * the SD card
 */
class File
{
    /** Making 'SD_Class' class friend of 'File' class, so that member
        functions of 'SD_Class' can access private member fields of 'File' */
    friend class SD_Class;

    private:
        /** Variable to hold the character to be flushed */
        char          charToFlush;
        /** Flag to indicate if the data should be flushed */
        Bool          flushData;
        /** Variable to hold the character which was read last */
        char          holdCharFromRead;
        /** File name buffer */
        char          fileName[13];
        /** Starting cluster */
        unsigned long startCluster;
        /** ATA file structure */
        AtaFile       ataFileStruct;
        /** Mode in which the file is opened */
        FILE_MODE     fileMode;
        /** Flag to indicate if a file is open or not */
        Bool          fileOpenStatus;
        /** TRUE if its a directory, else FALSE */
        Bool          fileOrDirectory;
        /** TRUE if the current File pointer is properly placed, else FALSE .
            This variable also denotes that the character read during seek
            operation is yet to be sent to the User */
        Bool          seekIsTocurrPos;
        /** TRUE if the last byte read during seek operation is yet to be
            flushed to the file, else FALSE */
        Bool          flushDataFromSeek;
        /** Variable that holds the current position in the file from which
            next byte will be read/written to */
        unsigned long currFilePosition;

        int writeData(File *fileHandle, char *buffer, int length);

    public:
        /** To check file open status */
        operator bool() const
        {
            return (fileOpenStatus && strlen(fileName));
        }

        File ();
        File (const File &fileObj);  /* copy constructor */
        unsigned long available ();
        void close ();
        void flush ();
        char peek ();
        unsigned long position ();
        int print (char character);
        int print (char *printString);
        int print (int integer);
        int print (long integer);
        int print (float value);
        int print (double value);
        int print (long integer, NUMBER_FORMAT_BASE base);
        int println(void);
        int println (char character);
        int println (char *printString);
        int println (int integer);
        int println (long integer);
        int println (float value);
        int println (double value);
        int println (long integer, NUMBER_FORMAT_BASE base);
        Bool seek (unsigned long posValue);
        unsigned long size ();
        char read ();
        int read (char *buffer, int length);
        int read (int *buffer, int length);
        int write (char character);
        int write (long integer);
        int write (char *printString);
        int write (char *buffer, int length);
        int write (int *buffer, int length);
        Bool isDirectory ();
        File openNextFile ();
        void rewindDirectory ();
        void getName(char *fileName);
} ;

/**
 * \brief SD Card Class
 *
 * The SD class provides functions for accessing the SD card and manipulating
 * its files and directories
 */
class SD_Class
{
    private:
        CSL_MmcsdHandle      mmcsdHandle;
        CSL_MMCControllerObj mmcsdContObj;
        CSL_MMCCardObj       mmcCardObj;
        CSL_MMCCardIdObj     sdCardIdObj;
        CSL_MMCCardCsdObj    sdCardCsdObj;
        AtaState             ataDriveStruct;
        AtaMMCState          ataMMCStateStruct;
        AtaFile              ataFirstFileStruct;
        CSL_DMA_Handle       dmaWriteHandle;
        CSL_DMA_Handle       dmaReadHandle;
        CSL_DMA_ChannelObj   dmaWriteChanObj;
        CSL_DMA_ChannelObj   dmaReadChanObj;

    public:
        SD_Class ();
        ~SD_Class ();
        Bool begin ();
        Bool begin (int opmode);
        Bool exists (char *fileName);
        Bool mkdir (char *fileName);
        File open (char *filePath);
        File open (char *filePath, FILE_MODE mode);
        Bool remove (char *fileName);
        Bool rmdir (char *fileName);
} ;

extern SD_Class SD;
/**< SD class instance extern which can used by application programs
 *   to access SD DSP APIs
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _SD_H_ */
