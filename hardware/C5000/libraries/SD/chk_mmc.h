/*
*  Copyright 2004 by Texas Instruments Incorporated.
*  All rights reserved. Property of Texas Instruments Incorporated.
*  Restricted rights to use, duplicate or disclose this code are
*  granted through contract.
*  
*/
/**************************************************************************
 * This is proprietary information, not to be published -- TI INTERNAL DATA   
 * Copyright (C) 2003, Texas Instruments, Inc.  All Rights Reserved.          
 *
 * Title: Header file for the MMC sanity check routines 
 **************************************************************************/
/** @file chk_mmc.h
 *
 *  @brief Header file for MMC checking routines
 *
 */
 #ifndef MMC_CHK
 #define MMC_CHK 
 
 #include "ata.h"
 #include "csl_mmcsd_ataIf.h"
 #include "ata_.h"
  
 /**
  * Return Values of chk_mmc.
  */
 typedef enum  {
 
 	MMC_ERR_NONE,
 	
 	MMC_ERR_BAD_CSD_FILE_FORMAT,
 	MMC_ERR_CARD_NOT_READABLE,
 	
 	MMC_ERR_MBR_BAD_NUM_PART_SECTORS,
 	MMC_ERR_MBR_BAD_PARTITIONS_234,
 	MMC_ERR_MBR_DSKSIZE_MISMATCH,    /* <susmit : : 04-Mar-2003> */
 	
 	MMC_ERR_BR_BAD_JMP_OPCODE,
 	MMC_ERR_BR_BAD_BYTES_PER_SECTOR,
 	MMC_ERR_BR_BAD_SECTORS_PER_CLUSTER,
 	MMC_ERR_BR_BAD_RESERVED_SECTORS,
 	MMC_ERR_BR_BAD_NUM_OF_ROOT_ENTRIES,
 	MMC_ERR_BR_BAD_NUM_PART_SECTORS,
 	MMC_ERR_BR_BAD_SECTORS_PER_FAT,
 	MMC_ERR_BR_BAD_FILE_SYS_TYPE,
 	MMC_ERR_BR_BAD_SIGNATURE
 
 } MMC_ERR_int16; 

 /** 
  * Structure to hold Partition table
  */
 typedef struct{
    /** Boot descriptor 1 byte  */
	unsigned int boot_descriptor:8;  
    /** Partition start head 1 byte  */	
	unsigned int partition_start_head:8;     
    /** Partition start sector 6 bits  */	    
	unsigned int partition_start_sector:6;
    /** Partition start cylinder 10 bits  */	
	unsigned int partition_start_cylinder:10;
    /** FS descriptor 1 byte  */	
	unsigned int fs_descriptor:8;
    /** Partition end head 1 byte  */		
	unsigned int partition_end_head:8;           
    /** Partition end sector 6 bits  */		
	unsigned int partition_end_sector:6;  
    /** Partition end cylinder 10 bits  */	
	unsigned int partition_end_cylinder:10;
    /** Byte 1 first sector position  */	
	unsigned int byte1_first_sector_position:8;
    /** Byte 2 first sector position  */	
	unsigned int byte2_first_sector_position:8;
    /** Byte 3 first sector position  */	
	unsigned int byte3_first_sector_position:8;
    /** Byte 4 first sector position  */	
	unsigned int byte4_first_sector_position:8;
    /** Byte 1 sectors in partition  */	
	unsigned int byte1_no_of_sectors_in_partition:8; 
    /** Byte 2 sectors in partition  */		
	unsigned int byte2_no_of_sectors_in_partition:8;
    /** Byte 3 sectors in partition  */		
	unsigned int byte3_no_of_sectors_in_partition:8;
    /** Byte 4 sectors in partition  */		
	unsigned int byte4_no_of_sectors_in_partition:8;

 } PARTITION_TABLE;

 /**
  * Structure to hold Master Boot Record (MBR) 
  */
 typedef struct{
    /** MBR code 432 bytes  */	
	unsigned int mbr_code[216];   
	/** MMC ID entry 14 bytes  */	
	unsigned int mmc_id_entry[7];    
	/** Partition 1 entry 16 bytes  */	
	PARTITION_TABLE partition_one;  
	/** Partition 2 entry 16 bytes  */	
	PARTITION_TABLE partition_two;   
	/** Partition 3 entry 16 bytes  */	
	PARTITION_TABLE partition_three; 
	/** Partition 4 entry 16 bytes  */	
	PARTITION_TABLE partition_four;  
	/** FS signature 2 bytes  */	
	unsigned int signature;
 } MBR_struct;

 /** 
  * Structure to hold Boot Record (BR) 
  */
 typedef struct{
	/** Short jump instruction byte 1  */
	unsigned int short_jump_instr_byte_1:8;
	/** Short jump instruction byte 2  */	
	unsigned int short_jump_instr_byte_2:8;
	/** Short jump instruction byte 3  */	
	unsigned int short_jump_instr_byte_3:8 ;
	/** OEM name byte 1  */	
	unsigned int  oem_name_byte_1:8;     
	/** OEM name byte 2  */	    
	unsigned int  oem_name_byte_2:8;
	/** OEM name byte 3  */
	unsigned int  oem_name_byte_3:8;
	/** OEM name byte 4  */		
	unsigned int  oem_name_byte_4:8;
	/** OEM name byte 5  */		
	unsigned int  oem_name_byte_5:8;
	/** OEM name byte 6  */		
	unsigned int  oem_name_byte_6:8;
	/** OEM name byte 7  */		
	unsigned int  oem_name_byte_7:8;
	/** OEM name byte 8  */		
	unsigned int  oem_name_byte_8:8;
	/** Bytes per sector lower byte  */		
	unsigned int LB_bytes_per_sector:8;  
	/** Bytes per sector upper byte  */		
	unsigned int UB_bytes_per_sector:8;        
	/** Sectors per cluster  */		
	unsigned int sectors_per_cluster:8;    
	/** Reserved sectors lower byte  */	
	unsigned int LB_reserved_sectors:8;
	/** Reserved sectors upper byte  */	
	unsigned int UB_reserved_sectors:8;
	/** Number of fats  */		
	unsigned int no_of_fats:8;
	/** Number of root directories lower byte  */		
	unsigned int LB_no_of_root_dir_entries:8;   
	/** Number of root directories upper byte  */	
	unsigned int UB_no_of_root_dir_entries:8;   
	/** Sectors in partition lower byte  */	
	unsigned int LB_no_of_sectors_on_partition:8;
	/** Sectors in partition upper byte  */		
	unsigned int UB_no_of_sectors_on_partition:8;
	/** Media descriptor  */	
	unsigned int media_descriptor:8;        
	/** Sectors per FAT lower byte  */
	unsigned int LB_sectors_per_fat:8;           
	/** Sectors per FAT upper byte  */	
	unsigned int UB_sectors_per_fat:8;
	/** Sectors per track lower byte  */	
	unsigned int LB_sectors_per_track:8; 
	/** Sectors per track upper byte  */	
	unsigned int UB_sectors_per_track:8;
	/** Number of heads lower byte  */	
	unsigned int LB_no_of_heads:8;        
	/** Number of heads upper byte  */	
	unsigned int UB_no_of_heads:8;
	/** Number of hidden sectors byte 1  */		
	unsigned int byte1_no_hidden_sectors:8;   
	/** Number of hidden sectors byte 2  */		
	unsigned int byte2_no_hidden_sectors:8;
	/** Number of hidden sectors byte 3  */		
	unsigned int byte3_no_hidden_sectors:8;
	/** Number of hidden sectors byte 4  */		
	unsigned int byte4_no_hidden_sectors:8;
	/** Extended no of sectors byte 1  */	
	unsigned int byte1_extended_no_of_sectors_on_partition:8; 
	/** Extended no of sectors byte 2  */	
	unsigned int byte2_extended_no_of_sectors_on_partition:8;
	/** Extended no of sectors byte 3  */	
	unsigned int byte3_extended_no_of_sectors_on_partition:8;
	/** Extended no of sectors byte 4  */	
	unsigned int byte4_extended_no_of_sectors_on_partition:8;
	/** Drive number  */		
	unsigned int drive_number:8;
	/** Reserved sectors  */		
	unsigned int reserved:8; 
	/** Extended boot signature  */		
	unsigned int extended_boot_signature:8; 
	/** Volume serial number byte 1  */	
	unsigned int vol_serial_number_byte_1:8;
	/** Volume serial number byte 2  */		
	unsigned int vol_serial_number_byte_2:8;	 
	/** Volume serial number byte 3  */		
	unsigned int vol_serial_number_byte_3:8;
	/** Volume serial number byte 4  */		
	unsigned int vol_serial_number_byte_4:8;
	/** Volume label byte 1  */	
	unsigned int byte1_vol_label:8;      
	/** Volume label byte 2  */		
	unsigned int byte2_vol_label:8; 
	/** Volume label byte 3  */		
	unsigned int byte3_vol_label:8; 
	/** Volume label byte 4  */		
	unsigned int byte4_vol_label:8; 
	/** Volume label byte 5  */		
	unsigned int byte5_vol_label:8; 
	/** Volume label byte 6  */		
	unsigned int byte6_vol_label:8; 
	/** Volume label byte 7  */		
	unsigned int byte7_vol_label:8; 
	/** Volume label byte 8  */		
	unsigned int byte8_vol_label:8; 
	/** Volume label byte 9  */		
	unsigned int byte9_vol_label:8; 
	/** Volume label byte 10  */		
	unsigned int byte10_vol_label:8; 
	/** Volume label byte 11  */		
	unsigned int byte11_vol_label:8; 
	/** FS type byte 1  */	
	unsigned int byte1_fs_type:8;	
	/** FS type byte 2  */	
	unsigned int byte2_fs_type:8;
	/** FS type byte 3  */	
	unsigned int byte3_fs_type:8;
	/** FS type byte 4  */	
	unsigned int byte4_fs_type:8;
	/** FS type byte 5  */	
	unsigned int byte5_fs_type:8;
	/** FS type byte 6  */	
	unsigned int byte6_fs_type:8;
	/** FS type byte 7  */	
	unsigned int byte7_fs_type:8;
	/** FS type byte 8  */	
	unsigned int byte8_fs_type:8;
	/** Partition boot code  */	
	unsigned int opt_partition_boot_code[224];
	/** Signature  */		
	unsigned int signature;				      

 }BR_struct;

/**
 * Function  prototypes 
 */
 /* <susmit : Added a new parameter unsigned int * disk_type : 04-Mar-2003> */
 MMC_ERR_int16  chk_mmc(AtaState *pAtaDrive, unsigned int *disk_type);
 
 /**
 *
 * MMC_ERR_int16  Check_boot_record(unsigned long boot_record_sector,
 *									unsigned long ref_num_of_sectors,
 *									unsigned int  boot_record_type,
 * 									AtaState  *pAtaDrive,
 *									BR_struct *pBootRecord
 *
 * boot_record_sector -> The sector number to fetch the BR from.
 * ref_num_of_sectors -> The reference number of sectors on disk to validate BR against.
 * boot_record_type   -> Indicates whether this is floppy type or hard disk type boot record.
 * pAtaDrive          -> Pointer to initialised AtaState structure.
 * pBootRecord        -> 512 byte buffer to read boot record.
 */ 
 MMC_ERR_int16  Check_boot_record(
		 			unsigned long boot_record_sector,
		  			unsigned long ref_num_of_sectors,
		  			unsigned int  boot_record_type,
		  			AtaState  *pAtaDrive,
		  			BR_struct *pBootRecord);
  
 /** 
  *  getMMCSize(AtaState *pAtaDrive)
  *
  *  This function will returns total number of sectors in the disk,
  *  Not the actual size of the disk  
  */  
 AtaUint32 getMMCSize(AtaState *pAtaDrive);
 
 /** 
  *  mmc_format(AtaState *pAtaDrive, AtaUint16 *MBRptr, AtaUint16 *BRptr)
  *
  *  This function will format the disk  
  */   
 AtaError mmc_format(AtaState *pAtaDrive, AtaUint16 *MBRptr, AtaUint16 *BRptr); /* <pramod : : 18-Dec-02> */
 
 /** HD boot record */
 #define HD_BOOT_RECORD 0
 /** FD boot record */
 #define FD_BOOT_RECORD 1

 #endif

