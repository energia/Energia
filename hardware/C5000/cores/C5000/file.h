/*****************************************************************************/
/*  FILE.H v4.4.1                                                            */
/*                                                                           */
/* Copyright (c) 1995-2012 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Macros and declarations used in lowlevel I/O functions.                   */
/*****************************************************************************/
#ifndef _FILE
#define _FILE

#include <linkage.h>

/*---------------------------------------------------------------------------*/
/* constants for file manipulations                                          */
/*---------------------------------------------------------------------------*/
#define  O_RDONLY    (0x0000) /* open for reading      */
#define  O_WRONLY    (0x0001) /* open for writing      */
#define  O_RDWR      (0x0002) /* open for read & write */
#define  O_APPEND    (0x0008) /* append on each write  */
#define  O_CREAT     (0x0200) /* open with file create */
#define  O_TRUNC     (0x0400) /* open with truncation  */
#define  O_BINARY    (0x8000) /* open in binary mode   */

/*---------------------------------------------------------------------------*/
/* lowlevel I/O declarations                                                 */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
#define _DECL extern "C"
#else /* ! __cplusplus */
#define _DECL extern
#endif

#ifndef _OFF_T
#define _OFF_T
typedef long off_t;
#endif /* _OFF_T */

#ifndef SEEK_SET
#define SEEK_SET  (0x0000)
#endif /* SEEK_SET */
#ifndef SEEK_CUR
#define SEEK_CUR  (0x0001)
#endif /*SEEK_CUR */
#ifndef SEEK_END
#define SEEK_END  (0x0002)
#endif /* SEEK_END */

_DECL _CODE_ACCESS int   open(const char *path, unsigned flags, int mode);
_DECL _CODE_ACCESS int   read(int fildes, char *bufptr, unsigned cnt);
_DECL _CODE_ACCESS int   write(int fildes, const char *bufptr, unsigned cnt);
_DECL _CODE_ACCESS off_t lseek(int fildes, off_t offset, int origin);
_DECL _CODE_ACCESS int   close(int fildes);
_DECL _CODE_ACCESS int   unlink(const char *path);
_DECL _CODE_ACCESS int   rename(const char *old_name, const char *new_name);

_DECL _CODE_ACCESS int add_device(
    char     *name,			           
    unsigned  flags,
    int      (*dopen)(const char *path, unsigned flags, int llv_fd),
    int      (*dclose)(int dev_fd),
    int      (*dread)(int dev_fd, char *buf, unsigned count),
    int      (*dwrite)(int dev_fd, const char *buf, unsigned count),
    off_t    (*dlseek)(int dev_fd, off_t offset, int origin),
    int      (*dunlink)(const char *path),
    int      (*drename)(const char *old_name, const char *new_name));

/*---------------------------------------------------------------------------*/
/* _NSTREAM defines the max number of files you can have open with fopen().  */
/* Since the standard streams(stdin/stdout/stderr) use 3 of them by default, */
/* (_NSTREAM - 3) will be available to users.                                */
/*---------------------------------------------------------------------------*/
#define _NSTREAM         10                  

#define _NDEVICE         3                   /* Size of device table        */

#define _SSA      (0x0000)             /* Single Stream allowed       */
#define _BUSY     (0x0001)             /* Device busy                 */
#define _MSA      (0x0002)             /* Multiple Streams Allowed    */

#undef _DECL

#endif /* _FILE */

