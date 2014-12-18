/*
*  Copyright 2004 by Texas Instruments Incorporated.
*  All rights reserved. Property of Texas Instruments Incorporated.
*  Restricted rights to use, duplicate or disclose this code are
*  granted through contract.
*  
*/
/********************************************************************************/
/* $Id: ata_.h,2.4+ $														    */
/*										    									*/
/* This is proprietary information, not to be published -- TI INTERNAL DATA   	*/
/* Copyright (C) 2000, Texas Instruments, Inc.  All Rights Reserved.		  	*/
/*																				*/
/* Author: Susmit Pal													  		*/
/* Date: November 6, 2002														*/
/* Modified Date: November 28, 2002												*/
/* Last Modified Date: February 11, 2003										*/
/********************************************************************************/
#ifndef _ATA__H_
#define _ATA__H_

#include "ata.h"

#define ATA_WORDS_PER_PHY_SECTOR  0x100
//#define ATA_WORDS_PER_PHY_SECTOR  0x400/*Mistral*/
#define ATA_INVALID_SECTOR        0xFFFFFFFFL
#define ATA_INVALID_WORD		  0xFFFF
#define ATA_FAT_TYPE_12           0x01
#define ATA_FAT_TYPE_16           0x04         /* 16-bit FAT. Partitions smaller than 32MB */
#define ATA_FAT_TYPE_32           0x0B         /* 32-bit FAT. Partitions up to 2047GB */
#if 1
#define ATA_FAT_TYPE_EXT          0x05         /* Extended MS-DOS Partition */
#define ATA_FAT_TYPE_16_DOS4      0x06         /* 16-bit FAT. Partitions larger than or equal to 32MB */
#define ATA_FAT_TYPE_32           0x0B         /* 32-bit FAT. Partitions up to 2047GB */
#define ATA_FAT_TYPE_32X          0x0C         /* Same as 32(0Bh), but uses Logical Block Address Int 13h extensions. */
#define ATA_FAT_TYPE_32X13        0x0E         /* Same as 16_DOS4(06h), but uses Logical Block Address Int 13h extensions. */
#define ATA_FAT_TYPE_32X13X       0x0F         /* Same as EXT(05h), but uses Logical Block Address Int 13h extensions. */
#endif
#define ATA_FIRST_CLUSTER         2

AtaError _AtaGetDirEntry(AtaFile *pAtaFile);
AtaError _AtaFindNextBrokenCluster(AtaFile *pAtaFile, int SetNewCluster);
unsigned long _AtaCalculatePhySectorAndOffsetFromOffsetFromBootSector(unsigned long OffsetFromBootSector, unsigned short *OffsetInSector);
unsigned long _AtaCalculatePhySectorAndOffsetFromDirEntry(AtaUint32 DirEntry, AtaUint16 *OffsetInSector, AtaFile *pAtaFile, AtaError *ret_stat);
AtaError _AtaFindNext(AtaFile *pAtaFile, int available);
AtaError _AtaFindNextAvailableCluster(AtaFile *pAtaFile, int write_fat);
AtaError _AtaWriteFatEntry(AtaFile *pAtaFile, int ZeroFlag);
AtaError _AtaCreate(AtaFile *pAtaFile, AtaUint16 ClusterFlag, AtaUint32 currdirentry);
AtaError _AtaCreateDirectory(AtaFile *pAtaFile, AtaUint32 currdirentry);
int _AtaIncrementFatEntryOffsetAndAlignment(unsigned short *Offset, unsigned short *Alignment);

/*************************************** Intenal FAT Function Prototypes *******************************/

AtaError _AtaRead(AtaFile *pAtaFile, AtaUint16 *Data, AtaUint16 Words);
char _AtaReadByte(AtaSector PhySector, AtaState *pAtaDrive, AtaUint16 ByteOffset);
AtaUint16 _AtaReadWord(AtaSector PhySector, AtaState* pAtaDrive, AtaUint16 ByteOffset);
AtaUint32 _AtaReadDoubleWord(AtaSector PhySector, AtaState* pAtaDrive, AtaUint16 ByteOffset);

AtaError _AtaFlush(AtaState* pAtaDrive);
AtaError _AtaReadSector(AtaSector PhySector, AtaState* pAtaDrive, AtaUint16 *Word, int ByteSwap);
AtaError _AtaReadFatEntry(AtaCluster Cluster, AtaState *pAtaDrive, int *last_cluster, AtaCluster *NeededCluster);

AtaSector _AtaCalculatePhySectorAndOffsetFromCluster(AtaFile *pAtaFile, AtaUint16 *OffsetInSector);

AtaUint32 _AtaCalculatePhySectorAndOffsetOfFatEntry
(
  AtaCluster Cluster,
  AtaState *pAtaDrive,
  AtaUint16  *FatEntryOffset,
  AtaUint16 *FatEntryAlignment
);
AtaError _AtaReadFatEntryAtPhySector
(
  AtaSector  PhySector,
  AtaState *pAtaDrive,
  AtaCluster Offset,
  AtaUint16  Alignment,
  int *last_cluster,
  AtaCluster *NeededCluster
);
AtaError _AtaWriteFatEntryAtPhySector
(
  AtaSector	 PhySector,
  AtaState *pAtaDrive,
  AtaCluster	FatEntry,
  AtaUint16	 FatEntryOffset,
  AtaUint16	 FatEntryAlignment,
  int FlushSector,
/*Susmit - Scandisk bug fix*/
  unsigned long eofflag
/*Susmit - Scandisk bug fix*/
);
AtaError _AtaCreateLFNEntry(AtaFile *pAtaFile, char *longname, AtaUint16 clusterflag, int dirflag, int dirrename); 
AtaError _AtaWriteFatEntry4(AtaFile *pAtaFile, int ZeroFlag);  
AtaError _AtaFindVol(AtaFile *pAtaFile);
int _Ata_lfn_checksum(AtaFile *pAtaFile);
AtaError AtaGetLFN(AtaSector ll, AtaState *pAtaDrive, char *LongName, AtaUint16 *icnt, AtaUint16 kk, short jj, AtaUint16 Length, AtaUint16 NumLFNEntry);
/*SUSMIT - Byte Level File Handling Requirements*/
AtaError _AtaRead_b(AtaFile *pAtaFile, AtaUint16 *Data, AtaUint16 bytes);
/*SUSMIT - Byte Level File Handling Requirements*/

#ifdef __TMS320C55X__
#define CPLD_REG0   *(volatile unsigned int *)0x80
#define CPLD_REG1   *(volatile unsigned int *)0x81
#define CPLD_REG2   *(volatile unsigned int *)0x82
#define CPLD_REG4   *(volatile unsigned int *)0x84
#define CPLD_REG5   *(volatile unsigned int *)0x85
#define CPLD_REG6   *(volatile unsigned int *)0x86
#define CPLD_REG7   *(volatile unsigned int *)0x87
#else
#if 0
ioport unsigned port80;
ioport unsigned port81;
ioport unsigned port82;
ioport unsigned port84;
ioport unsigned port85;
ioport unsigned port86;
ioport unsigned port87;
ioport unsigned portB000;
ioport unsigned portB001;
ioport unsigned portB002;
ioport unsigned portB003;
ioport unsigned portB004;
ioport unsigned portB005;
ioport unsigned portB006;
ioport unsigned portB007;
ioport unsigned portA000;
ioport unsigned portA001;
ioport unsigned portA002;
ioport unsigned portA003;
ioport unsigned portA004;
ioport unsigned portA005;
ioport unsigned portA006;
ioport unsigned portA007;
ioport unsigned portA008;
ioport unsigned portA00D;
ioport unsigned portA00E;
ioport unsigned portA00F;
ioport unsigned portAC08;
ioport unsigned portAC09;
#endif 

#define CPLD_REG0   port80
#define CPLD_REG1   port81
#define CPLD_REG2   port82
#define CPLD_REG4   port84
#define CPLD_REG5   port85
#define CPLD_REG6   port86
#define CPLD_REG7   port87
#endif

#ifdef __TMS320C55X__
#define BYTDATREG   *(volatile unsigned int *)0xD00000 /* even read data/odd write data */
#define ERRFEAREG   *(volatile unsigned int *)0xD00001 /* read error/write feature */
#define SECTCOUNT   *(volatile unsigned int *)0xD00002 /* sector count */
#define SECTORNO	*(volatile unsigned int *)0xD00003 /* sector number */
#define CYLINDLOW   *(volatile unsigned int *)0xD00004 /* cylinder low */
#define CYLINDHI	*(volatile unsigned int *)0xD00005 /* cylinder high */
#define SCARDHEAD   *(volatile unsigned int *)0xD00006 /* select card/head */
#define STATCOMMD   *(volatile unsigned int *)0xD00007 /* read status/write command */
#else
#define BYTDATREG   portB000 /* even read data/odd write data */
#define ERRFEAREG   portB001 /* read error/write feature */
#define SECTCOUNT   portB002 /* sector count */
#define SECTORNO    portB003 /* sector number */
#define CYLINDLOW   portB004 /* cylinder low */
#define CYLINDHI    portB005 /* cylinder high */
#define SCARDHEAD   portB006 /* select card/head */
#define STATCOMMD   portB007 /* read status/write command */
#endif

#if 0
#ifdef LEIA
#define BYTDATREG   *(volatile unsigned int *)0xB000 /* even read data/odd write data */
#define ERRFEAREG   *(volatile unsigned int *)0xB001 /* read error/write feature */
#define SECTCOUNT   *(volatile unsigned int *)0xB002 /* sector count */
#define SECTORNO	*(volatile unsigned int *)0xB003 /* sector number */
#define CYLINDLOW   *(volatile unsigned int *)0xB004 /* cylinder low */
#define CYLINDHI	*(volatile unsigned int *)0xB005 /* cylinder high */
#define SCARDHEAD   *(volatile unsigned int *)0xB006 /* select card/head */
#define STATCOMMD   *(volatile unsigned int *)0xB007 /* read status/write command */
#else
#define BYTDATREG   *(volatile unsigned int *)0xA000 /* even read data/odd write data */
#define ERRFEAREG   *(volatile unsigned int *)0xA001 /* read error/write feature */
#define SECTCOUNT   *(volatile unsigned int *)0xA002 /* sector count */
#define SECTORNO	*(volatile unsigned int *)0xA003 /* sector number */
#define CYLINDLOW   *(volatile unsigned int *)0xA004 /* cylinder low */
#define CYLINDHI	*(volatile unsigned int *)0xA005 /* cylinder high */
#define SCARDHEAD   *(volatile unsigned int *)0xA006 /* select card/head */
#define STATCOMMD   *(volatile unsigned int *)0xA007 /* read status/write command */
#endif
#endif /* #if 0 */

#if 0 /*susmit - 54/55 fix*/
#ifdef LEIA
#define BYTDATREG   *(volatile unsigned int *)0xD00000 /* even read data/odd write data */
#define ERRFEAREG   *(volatile unsigned int *)0xD00001 /* read error/write feature */
#define SECTCOUNT   *(volatile unsigned int *)0xD00002 /* sector count */
#define SECTORNO	*(volatile unsigned int *)0xD00003 /* sector number */
#define CYLINDLOW   *(volatile unsigned int *)0xD00004 /* cylinder low */
#define CYLINDHI	*(volatile unsigned int *)0xD00005 /* cylinder high */
#define SCARDHEAD   *(volatile unsigned int *)0xD00006 /* select card/head */
#define STATCOMMD   *(volatile unsigned int *)0xD00007 /* read status/write command */
#else
#define BYTDATREG   *(volatile unsigned int *)0xD00000 /* even read data/odd write data */
#define ERRFEAREG   *(volatile unsigned int *)0xD00001 /* read error/write feature */
#define SECTCOUNT   *(volatile unsigned int *)0xD00002 /* sector count */
#define SECTORNO	*(volatile unsigned int *)0xD00003 /* sector number */
#define CYLINDLOW   *(volatile unsigned int *)0xD00004 /* cylinder low */
#define CYLINDHI	*(volatile unsigned int *)0xD00005 /* cylinder high */
#define SCARDHEAD   *(volatile unsigned int *)0xD00006 /* select card/head */
#define STATCOMMD   *(volatile unsigned int *)0xD00007 /* read status/write command */
#endif
#endif /*susmit - 54/55 fix*/

#if 0								   /* not used */
#define DUPEVEDAT   *(volatile unsigned int *)0xA008 /* duplicate even data */
#define DUPODDDAT   *(volatile unsigned int *)0xA009 /* duplicate odd data */
#define DUPERRFEA   *(volatile unsigned int *)0xA00D /* duplicate read error/write feature */
#define ASTSDEVCTL  *(volatile unsigned int *)0xA00E /* alternate status/device control */
#define DRVADDRESS  *(volatile unsigned int *)0xA00F /* drive address (only when -IORD=0) */
#define EVENDATA	*(volatile unsigned int *)0xAC08 /* even data */
#define ODDDATA	 *(volatile unsigned int *)0xAC09 /* odd data */
#endif

/* I/O Mapped Registers' Definitions  */
#define ATA_READY		 0xE000

/* ATA (CompactFlash) Command Set */
#define ATA_READSECTOR	0x0020
#define ATA_WRITESECTOR   0x0030
#define ATA_IDENTIFY	  0x00EC
#define ATA_IDLEIMMEDIATE 0x00E1
#define ATAPI_IDENTIFY	0x00A1  /* ATAPI version of the ATA Identify command; ECh fails on an ATAPI device */

#define DRIVE_0		   0x00E0


#ifdef OLD_ATA_API

typedef struct ata_globals_definition
{
  unsigned long  BootPhySector;
  unsigned short FatType;
  unsigned short WordsPerLogSector;
  unsigned short LogSectorsPerCluster;
  unsigned short RootDirEntries;
  unsigned long  LogSectorsPerFat;
  unsigned long  FirstFatSector;
  unsigned long  RootDirSector;
  unsigned long  FirstDataSector;
  unsigned long  TotalSectors;
  unsigned short Data;
  unsigned short CurrentWord;
  unsigned long  CurrentPhySector;
  unsigned short WordsPerCluster;
  unsigned short SerialNumber[10];
  unsigned short NumberOfFats;
  int Nested;
} ata_globals;

#endif
#endif /* #define _ATA__H_ */

