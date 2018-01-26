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

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Energia.h>
#include <inttypes.h>

#if defined(__MSP430_HAS_USI__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__) || defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_EUSCI_B0__) || defined(__MSP430_HAS_EUSCI_B1__)
#include "utility/spi_430.h"
#endif

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 4

#if defined(__MSP430_HAS_EUSCI_B0__)
#define UCB0_BASE UCB0CTLW0_
#endif
#if defined(__MSP430_HAS_EUSCI_B1__)
#define UCB1_BASE UCB1CTLW0_
#endif
#if defined(__MSP430_HAS_EUSCI_B2__)
#define UCB2_BASE UCB2CTLW0_
#endif


class SPISettings {
public:
  uint8_t _bitOrder;  
  uint8_t _mode;
  uint8_t _rate;
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
      init_AlwaysInline(clock, bitOrder, dataMode);
  }
  SPISettings() {
    init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0);
  }
private:

  void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
    __attribute__((__always_inline__)) {

    // Pack into the SPISettings class
    _bitOrder = bitOrder;
    _mode     = dataMode ;
    _rate     =  F_CPU/clock;;
  }
  friend class SPIClass;  
};

extern uint8_t spiModule ;

class SPIClass {
public:
  
  inline static void beginTransaction(SPISettings settings);
  inline static void endTransaction(void);
  inline static uint8_t transfer(uint8_t data);
  inline static uint16_t transfer16(uint16_t data);
  inline static void transfer(void *buf, size_t count);
  inline static void transmit(uint8_t data);
  inline static void transmit16(uint16_t data);
  inline static void transmit(void *buf, size_t count);
  
  // SPI Configuration methods

  SPIClass(void);
  inline static void begin(); // Default
  inline static void begin(uint8_t module);
  inline static void end();

  inline static void setBitOrder(uint8_t);
  inline static void setDataMode(uint8_t);
  inline static void setClockDivider(uint8_t);

  inline static void attachInterrupt();
  inline static void detachInterrupt();

  void setModule(uint8_t);
};

extern SPIClass SPI;

void SPIClass::beginTransaction(SPISettings settings) {
	spi_set_bitorder(settings._bitOrder);
	spi_set_datamode(settings._mode);
	spi_set_divisor(settings._rate);
}


void SPIClass::begin(void) {
    spi_initialize();
}

void SPIClass::begin(uint8_t module) {
    SPI.setModule(module);
    begin();
}

uint8_t SPIClass::transfer(uint8_t data) {
    return spi_send(data);
}

uint16_t SPIClass::transfer16(uint16_t data) {
    return spi_send16(data);
}

void SPIClass::transfer(void *buf, size_t count) {
    return spi_send(buf, count);
}

void SPIClass::transmit(uint8_t data) {
    spi_transmit(data);
}

void SPIClass::transmit16(uint16_t data) {
    spi_transmit16(data);
}

void SPIClass::transmit(void *buf, size_t count) {
    spi_transmit(buf, count);
}

// After performing a group of transfers and releasing the chip select
// signal, this function allows others to access the SPI bus
void SPIClass::endTransaction(void) {
    spi_disable();
}

void SPIClass::end()
{
    spi_disable();
}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
    spi_set_bitorder(bitOrder);
}

void SPIClass::setDataMode(uint8_t mode)
{
    spi_set_datamode(mode);
}

void SPIClass::setClockDivider(uint8_t rate)
{
    spi_set_divisor(rate);
}

void SPIClass::attachInterrupt() {
    /* undocumented in Arduino 1.0 */
}

void SPIClass::detachInterrupt() {
    /* undocumented in Arduino 1.0 */
}


#endif
