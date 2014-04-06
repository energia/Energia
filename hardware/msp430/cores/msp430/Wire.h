/*
  ************************************************************************
  *	Wire.h
  *
  *	Arduino core files for MSP430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *
  ***********************************************************************
  Derived from:
  TwoWire.h - TWI/I2C library for Arduino & Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

#ifndef TwoWire_h
#define TwoWire_h

#if !defined (__MSP430_HAS_USI__) && !defined (__MSP430_HAS_USCI__) && !defined (__MSP430_HAS_USCI_B0__) && !defined (__MSP430_HAS_EUSCI_B0__)
#ifndef __MSP430_HAS_USI__
#error "********** USI not available"
#endif

#if !defined (__MSP430_HAS_USCI__) && !defined (__MSP430_HAS_USCI_B0__) && !defined (__MSP430_HAS_EUSCI_B0__)
#error "********** USCI not available"
#endif
#endif

#include <inttypes.h>
#include "Stream.h"
#include <msp430.h>

#define BUFFER_LENGTH 16
#ifndef TWI_BUFFER_LENGTH
#define TWI_BUFFER_LENGTH 16
#endif

#ifndef TWI_FREQ
#define TWI_FREQ 100000L
#endif

#define TWI_READY 0
#define TWI_MRX   1
#define TWI_MTX   2
#define TWI_SRX   3
#define TWI_STX   4


#define TWI_SND_START 0
#define TWI_PREP_SLA_ADDR_ACK 1
#define TWI_MT_PROC_ADDR_ACK 2
#define TWI_MT_PREP_DATA_ACK 3
#define TWI_MT_PROC_DATA_ACK 4
#define TWI_MR_PREP_DATA_RECV 5
#define TWI_MR_PROC_DATA_RECV 6
#define TWI_MR_PREP_STOP 7

#define TWI_SL_START 8
#define TWI_SL_PROC_ADDR 9
#define TWI_SL_SEND_BYTE 10
#define TWI_SL_PREP_DATA_ACK 11
#define TWI_SL_PROC_DATA_ACK 12
#define TWI_SL_RECV_BYTE 13
#define TWI_SL_PROC_BYTE 14
#define TWI_SL_RESET 15
#define TWI_EXIT 16
#define TWI_IDLE 17


#define TWI_ERRROR_NO_ERROR 0
#define TWI_ERROR_BUF_TO_LONG 1
#define TWI_ERROR_ADDR_NACK 2
#define TWI_ERROR_DATA_NACK 3
#define TWI_ERROR_OTHER 4


#define USE_USCI_B1 1

#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) \
 || defined(__MSP430_HAS_USCI_B1__)

#ifndef USE_USCI_B1
#define TWISDAx       TWISDA
#define TWISCLx       TWISCL
#define TWISDA_SET_MODEx       TWISDA_SET_MODE
#define TWISCL_SET_MODEx       TWISCL_SET_MODE

#define UCBxCTLW0     UCB0CTLW0
#define UCBxCTL0      UCB0CTL0
#define UCBxCTL1      UCB0CTL1
#define UCBxBRW       UCB0BRW
#define UCBxBR0       UCB0BR0
#define UCBxBR1       UCB0BR1
#define UCBxMCTL      UCB0MCTL
#define UCBxMCTLW     UCB0MCTLW
#define UCBxSTAT      UCB0STAT
#define UCBxRXBUF     UCB0RXBUF
#define UCBxTXBUF     UCB0TXBUF
#define UCBxABCTL     UCB0ABCTL
#define UCBxIRCTL     UCB0IRCTL
#define UCBxIRTCTL    UCB0IRTCTL
#define UCBxIRRCTL    UCB0IRRCTL
#define UCBxICTL      UCB0ICTL
#define UCBxIE        UCB0IE
#define UCBxIFG       UCB0IFG
#define UCBxIV        UCB0IV
#define UCBxI2COA     UCB0I2COA
#define UCBxI2CSA     UCB0I2CSA

#else
#define TWISDAx       TWISDA2
#define TWISCLx       TWISCL2
#define TWISDA_SET_MODEx       TWISDA_SET_MODE1
#define TWISCL_SET_MODEx       TWISCL_SET_MODE1

#define UCBxCTLW0     UCB1CTLW0
#define UCBxCTL0      UCB1CTL0
#define UCBxCTL1      UCB1CTL1
#define UCBxBRW       UCB1BRW
#define UCBxBR0       UCB1BR0
#define UCBxBR1       UCB1BR1
#define UCBxMCTL      UCB1MCTL
#define UCBxMCTLW     UCB1MCTLW
#define UCBxSTAT      UCB1STAT
#define UCBxRXBUF     UCB1RXBUF
#define UCBxTXBUF     UCB1TXBUF
#define UCBxABCTL     UCB1ABCTL
#define UCBxIRCTL     UCB1IRCTL
#define UCBxIRTCTL    UCB1IRTCTL
#define UCBxIRRCTL    UCB1IRRCTL
#define UCBxICTL      UCB1ICTL
#define UCBxIE        UCB1IE
#define UCBxIFG       UCB1IFG
#define UCBxIV        UCB1IV
#define UCBxI2COA     UCB1I2COA
#define UCBxI2CSA     UCB1I2CSA
#endif
#endif

#if defined(__MSP430_HAS_USCI__)
#endif

#if defined(__MSP430_HAS_EUSCI_B0__)
#endif



class TwoWire : public Stream
{
  private:
    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t transmitting;
    static void (*user_onRequest)(void);
    static void (*user_onReceive)(int);
    static void onRequestService(void);
    static void onReceiveService(uint8_t*, int);

    static uint8_t twi_state;
    static uint8_t twi_sendStop;           // should the transaction end with a stop
    static uint8_t twi_inRepStart;         // in the middle of a repeated start

    static void (*twi_onSlaveTransmit)(void);
    static void (*twi_onSlaveReceive)(uint8_t*, int);

    static uint8_t twi_masterBuffer[];
    static uint8_t twi_masterBufferIndex;
    static uint8_t twi_masterBufferLength;

    static uint8_t twi_txBuffer[];
    static uint8_t twi_txBufferIndex;
    static uint8_t twi_txBufferLength;
    #if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_B0__) \
     || defined(__MSP430_HAS_USCI_B1__) || defined(__MSP430_HAS_EUSCI_B0__)
    static uint8_t twi_rxBuffer[];
    static uint8_t twi_rxBufferIndex;
    #endif

    static uint8_t twi_error;

    #if defined(__MSP430_HAS_USI__)
    static uint8_t twi_slarw;
    static uint8_t twi_my_addr;
    #endif

    void twi_init(void);
    void twi_setAddress(uint8_t address);
    uint8_t twi_readFrom(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop);
    uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop);
    uint8_t twi_transmit(const uint8_t* data, uint8_t length);
    void twi_attachSlaveRxEvent( void (*function)(uint8_t*, int) );
    void twi_attachSlaveTxEvent( void (*function)(void) );
    void send_start();


  public:
    TwoWire();
    void begin();
    void begin(uint8_t);
    void begin(int);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
#define USCI_ERROR "\n*********\nI2C Slave is not implemented for this MSP430. \nConsider using using a MSP430 with USCI peripheral e.g. MSP430G2553.\n*********\n"
#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_USCI_B0__) || defined(__MSP430_HAS_USCI_B1__)
    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );
#else
    void onReceive( void (*)(int) ) __attribute__ ((error(USCI_ERROR)));
    void onRequest( void (*)(void) ) __attribute__ ((error(USCI_ERROR)));
#endif
  
    void I2C_Usci_txrx_handler(void);
    void I2C_Usci_state_handler(void);
    void I2C_Eusci_handler(void);
    void I2C_Usi_handler(void);

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;
};

extern TwoWire Wire;

#endif

