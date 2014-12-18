/*****************************************************************************/
/* extaddr.h  v4.4.1                                                         */
/*                                                                           */
/* Copyright (c) 1996-2012 Texas Instruments Incorporated                    */
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

#ifndef _EXTADDR
#define _EXTADDR

/**************************************************************************/
/* Type of extended memory data address values                            */
/**************************************************************************/
typedef unsigned long FARPTR;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**************************************************************************/
/* Prototypes for Extended Memory Data Support Functions                  */
/*                                                                        */
/* far_peek         Read an int from extended memory address              */
/* far_peek_l       Read a long from extended memory address              */
/* far_poke         Write an int to extended memory address               */
/* far_poke_l       Write a long to extended memory address               */
/* far_memcpy       Block copy between extended memory addresses          */
/* far_near_memcpy  Block copy from extended memory address to page 0     */
/* near_far_memcpy  Block copy from page 0 to extended memory address     */
/*                                                                        */
/**************************************************************************/
int           far_peek(FARPTR);
unsigned long far_peek_l(FARPTR);
void          far_poke(FARPTR, int);
void          far_poke_l(FARPTR, unsigned long);

void          far_memcpy(FARPTR, FARPTR,  int);
void          far_near_memcpy(void *, FARPTR,  int);
void          near_far_memcpy(FARPTR, void *,  int);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_EXTADDR */
