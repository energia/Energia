/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * 2012-04-29 rick@kimballsoftware.com - added msp430 support.
 *
 */

#include <Energia.h>

#include "SPI.h"

#if defined(DEFAULT_SPI)
    uint8_t spiModule = DEFAULT_SPI;
#else
    uint8_t spiModule = 0;
#endif

SPIClass::SPIClass(void) {
#if defined(DEFAULT_SPI)
   setModule(DEFAULT_SPI);
#else
   setModule(0);
#endif
}

void SPIClass::setModule(uint8_t module)
{
    spiModule = module;
   if (module == 0)
   {
#if defined(__MSP430_HAS_EUSCI_B0__)
      SPI_baseAddress = UCB0_BASE;
#endif
   }
   if (module == 1)
   {
#if defined(__MSP430_HAS_EUSCI_B1__)
      SPI_baseAddress = UCB1_BASE;
#endif
   }

}

/*
 * Pre-Initialize a SPI instances
 */
SPIClass SPI;
