/*
 * SimpleLinkForEnergia.h - Energia Abstraction layer for SimpleLink functions
 *
 * Copyright (C) 2014 Noah Luskey | LuskeyNoah@gmail.com
 *
 * Contributors:
 *    Phil LaFayette (MH Electric Motor & Control Corp.) - Upgraded CC31xx/CC32xx Host Driver to v1.0.1.6, May 27, 2016
 *
 */


#ifndef _SIMPLELINK_FOR_ENERGIA_H_
#define _SIMPLELINK_FOR_ENERGIA_H_

#include "user.h"


#ifdef __cplusplus
extern "C" {
#endif

void CC3100_enable();
void CC3100_disable();
int spi_Open(char* pIfName , unsigned long flags);
int spi_Close(int Fd);
int spi_Read(int Fd , char* pBuff , int Len);
int spi_Write(int Fd , char* pBuff , int Len);
int registerInterruptHandler(void* InterruptHdl , void* pValue);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* inclusion guard end */
