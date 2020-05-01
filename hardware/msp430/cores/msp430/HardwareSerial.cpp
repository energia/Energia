/*
  ************************************************************************
  *	HardwareSerial.cpp
  *
  *	Arduino core files for MSP430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *
  ***********************************************************************
  Derived from:
  HardwareSerial.cpp - Hardware serial library for Wiring
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
  
  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Energia.h"
#include "wiring_private.h"
#include "usci_isr_handler.h"

#if defined(__MSP430_HAS_USCI__) || defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__) || defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)

#include "HardwareSerial.h"

#define UCAxCTLW0     UCA0CTLW0 
#define UCAxCTL0      UCA0CTL0
#define UCAxCTL1      UCA0CTL1
#define UCAxBRW       UCA0BRW
#define UCAxBR0       UCA0BR0
#define UCAxBR1       UCA0BR1
#define UCAxMCTL      UCA0MCTL
#define UCAxMCTLW     UCA0MCTLW
#define UCAxMCTLW_L   UCA0MCTLW_L
#define UCAxMCTLW_H   UCA0MCTLW_H
#define UCAxSTAT      UCA0STAT
#if defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
#define UCAxRXBUF     UCA0RXBUF_L
#define UCAxTXBUF     UCA0TXBUF_L
#else
#define UCAxRXBUF     UCA0RXBUF
#define UCAxTXBUF     UCA0TXBUF
#endif
#define UCAxABCTL     UCA0ABCTL
#define UCAxIRCTL     UCA0IRCTL
#define UCAxIRTCTL    UCA0IRTCTL
#define UCAxIRRCTL    UCA0IRRCTL
#define UCAxICTL      UCA0ICTL
#if defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
#define UCAxIE        UCA0IE_L
#define UCAxIFG       UCA0IFG_L
#else
#define UCAxIE        UCA0IE
#define UCAxIFG       UCA0IFG
#endif
#define UCAxIV        UCA0IV

#define SERIAL_BUFFER_SIZE_DEFAULT 16

struct ring_buffer
{
	unsigned char *buffer;
	volatile unsigned int head;
	volatile unsigned int tail;
	#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
	unsigned int size;
	#endif
};

/* Non-dynamic allocation/adjustable buffer sized chips need to have a
 * SERIAL_BUFFER_SIZE_DEFAULT-sized pair of buffers preallocated.
 */
#ifndef HARDWARESERIAL_MSP430_USE_MALLOC
unsigned char rx0_buff[SERIAL_BUFFER_SIZE_DEFAULT];
unsigned char tx0_buff[SERIAL_BUFFER_SIZE_DEFAULT];
#ifdef SERIAL1_AVAILABLE
unsigned char rx1_buff[SERIAL_BUFFER_SIZE_DEFAULT];
unsigned char tx1_buff[SERIAL_BUFFER_SIZE_DEFAULT];
#endif
#endif

#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
ring_buffer rx_buffer  =  { NULL, 0, 0, SERIAL_BUFFER_SIZE_DEFAULT };
ring_buffer tx_buffer  =  { NULL, 0, 0, SERIAL_BUFFER_SIZE_DEFAULT };
#ifdef SERIAL1_AVAILABLE
ring_buffer rx_buffer1  =  { NULL, 0, 0, SERIAL_BUFFER_SIZE_DEFAULT };
ring_buffer tx_buffer1  =  { NULL, 0, 0, SERIAL_BUFFER_SIZE_DEFAULT };
#endif
#else
ring_buffer rx_buffer  =  { rx0_buff, 0, 0 };
ring_buffer tx_buffer  =  { tx0_buff, 0, 0 };
#ifdef SERIAL1_AVAILABLE
ring_buffer rx_buffer1  =  { rx1_buff, 0, 0 };
ring_buffer tx_buffer1  =  { tx1_buff, 0, 0 };
#endif
#endif

inline void store_char(unsigned char c, ring_buffer *buffer)
{
	#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
	unsigned int i = (unsigned int)(buffer->head + 1) % buffer->size;
	#else
	unsigned int i = (unsigned int)(buffer->head + 1) % SERIAL_BUFFER_SIZE_DEFAULT;
	#endif

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != buffer->tail) {
		buffer->buffer[buffer->head] = c;
		buffer->head = i;
	}
}

void serialEvent() __attribute__((weak));
void serialEvent() {}
#ifdef SERIAL1_AVAILABLE
void serialEvent1() __attribute__((weak));
void serialEvent1() {}
#endif

void serialEventRun(void)
{
	if (Serial.available()) serialEvent();
#ifdef SERIAL1_AVAILABLE
	if (Serial1.available()) serialEvent1();
#endif
}

// Public Methods //////////////////////////////////////////////////////////////
#define SMCLK F_CPU //SMCLK = F_CPU for now

void HardwareSerial::begin(unsigned long baud)
{
	unsigned int mod;
	unsigned long divider;
	unsigned char oversampling;
	
	// Allocate TX & RX buffers (malloc-use only)
	#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
	if (_tx_buffer->buffer != NULL)
		free(_tx_buffer->buffer);
	_tx_buffer->buffer = (unsigned char *)malloc(_tx_buffer->size);

	if (_rx_buffer->buffer != NULL)
		free(_rx_buffer->buffer);
	_rx_buffer->buffer = (unsigned char *)malloc(_rx_buffer->size);
	#endif


	/* Calling this dummy function prevents the linker
	 * from stripping the USCI interupt vectors.*/ 
	usci_isr_install();
	if (SMCLK/baud>=48) {                                                // requires SMCLK for oversampling
		oversampling = 1;
	}
	else {
		oversampling= 0;
	}

	divider=(SMCLK<<4)/baud;

	pinMode_int(rxPin, rxPinMode);
	pinMode_int(txPin, txPinMode);

	delay(10);

	*(&(UCAxCTL1) + uartOffset) = UCSWRST;
	*(&(UCAxCTL1) + uartOffset) |= UCSSEL_2;                                // SMCLK
	*(&(UCAxCTL0) + uartOffset) = 0;
	*(&(UCAxABCTL) + uartOffset) = 0;
#if defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
	if(!oversampling) {
		mod = ((divider&0xF)+1)&0xE;                    // UCBRSx (bit 1-3)
		divider >>=4;
	} else {
		mod = divider&0xFFF0;                           // UCBRFx = INT([(N/16) – INT(N/16)] × 16)
		divider>>=8;
	}
	*(&(UCAxBR0) + uartOffset) = divider;
	*(&(UCAxBR1) + uartOffset) = divider>>8;

	uint16_t reg = (oversampling ? UCOS16:0) | mod;
	*(&(UCAxMCTLW_L) + uartOffset) = reg;
	*(&(UCAxMCTLW_H) + uartOffset)= reg>>8;
#else
	if(!oversampling) {
		mod = ((divider&0xF)+1)&0xE;                    // UCBRSx (bit 1-3)
		divider >>=4;
	} else {
		mod = ((divider&0xf8)+0x8)&0xf0;                // UCBRFx (bit 4-7)
		divider>>=8;
	}
	*(&(UCAxBR0) + uartOffset)= divider;
	*(&(UCAxBR1) + uartOffset) = divider>>8;
	*(&(UCAxMCTL) + uartOffset) = (unsigned char)(oversampling ? UCOS16:0) | mod;
#endif	
	*(&(UCAxCTL1) + uartOffset) &= ~UCSWRST;
#if defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__) || defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
	*(&(UCAxIE) + uartOffset) |= UCRXIE;
#else
	*(&(UC0IE) + uartOffset) |= UCA0RXIE;
#endif	
}

void HardwareSerial::end()
{
	// wait for transmission of outgoing data
	while (_tx_buffer->head != _tx_buffer->tail);

	_rx_buffer->head = _rx_buffer->tail;

	#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
	free(_tx_buffer->buffer);
	free(_rx_buffer->buffer);
	#endif
}

int HardwareSerial::available(void)
{
	#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
	return (unsigned int)(_rx_buffer->size + _rx_buffer->head - _rx_buffer->tail) % _rx_buffer->size;
	#else
	return (unsigned int)(SERIAL_BUFFER_SIZE_DEFAULT + _rx_buffer->head - _rx_buffer->tail) % SERIAL_BUFFER_SIZE_DEFAULT;
	#endif
}

int HardwareSerial::peek(void)
{
	if (_rx_buffer->head == _rx_buffer->tail) {
		return -1;
	} else {
		return _rx_buffer->buffer[_rx_buffer->tail];
	}
}

int HardwareSerial::read(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
	if (_rx_buffer->head == _rx_buffer->tail) {
		return -1;
	} else {
		unsigned char c = _rx_buffer->buffer[_rx_buffer->tail];
		#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
		_rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % _rx_buffer->size;
		#else
		_rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % SERIAL_BUFFER_SIZE_DEFAULT;
		#endif
		return c;
	}
}

void HardwareSerial::flush()
{
	while (_tx_buffer->head != _tx_buffer->tail);
}

size_t HardwareSerial::write(uint8_t c)
{
	#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
	unsigned int i = (_tx_buffer->head + 1) % _tx_buffer->size;
	#else
	unsigned int i = (_tx_buffer->head + 1) % SERIAL_BUFFER_SIZE_DEFAULT;
	#endif
	
	// If the output buffer is full, there's nothing for it other than to
	// wait for the interrupt handler to empty it a bit
	// ???: return 0 here instead?
	while (i == _tx_buffer->tail);
	
	_tx_buffer->buffer[_tx_buffer->head] = c;
	_tx_buffer->head = i;

#if defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__) || defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
	*(&(UCAxIE) + uartOffset) |= UCTXIE;
#else
	*(&(UC0IE) + uartOffset) |= UCA0TXIE;
#endif	

	return 1;
}

void HardwareSerial::setBufferSize(unsigned int txSize, unsigned int rxSize)
{
	#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
	if (txSize == 0)
		txSize = 2;  // prevent inadvertent divide by 0 errors
	if (rxSize == 0)
		rxSize = 2;
	_tx_buffer->size = txSize;
	_rx_buffer->size = rxSize;
	#endif
}

HardwareSerial::operator bool() {
	return true;
}

void uart_rx_isr(uint8_t offset)
{
#ifdef SERIAL1_AVAILABLE
	/* Debug uart aka Serial always gets rx_buffer and aux aka Serial1 gets rx_buffer1 */
	ring_buffer *rx_buffer_ptr = (offset == DEBUG_UART_MODULE_OFFSET) ? &rx_buffer:&rx_buffer1;
#else
	ring_buffer *rx_buffer_ptr = &rx_buffer;
#endif
	unsigned char c = *(&(UCAxRXBUF) + offset);
	store_char(c, rx_buffer_ptr);
}

void uart_tx_isr(uint8_t offset)
{
#ifdef SERIAL1_AVAILABLE
	/* Debug uart aka Serial always gets rx_buffer and aux aka Serial1 gets rx_buffer1 */
	ring_buffer *tx_buffer_ptr = (offset == DEBUG_UART_MODULE_OFFSET) ? &tx_buffer : &tx_buffer1;
#else
	ring_buffer *tx_buffer_ptr = &tx_buffer;
#endif
	if (tx_buffer_ptr->head == tx_buffer_ptr->tail) {
		// Buffer empty, so disable interrupts
#if defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__) || defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
		*(&(UCAxIE) + offset) &= ~UCTXIE;
		*(&(UCAxIFG) + offset) |= UCTXIFG;    // Set Flag again
#else
		*(&(UC0IE) + offset) &= ~UCA0TXIE;
#endif	
		return;
	}

	unsigned char c = tx_buffer_ptr->buffer[tx_buffer_ptr->tail];
	#ifdef HARDWARESERIAL_MSP430_USE_MALLOC
	tx_buffer_ptr->tail = (tx_buffer_ptr->tail + 1) % tx_buffer_ptr->size;
	#else
	tx_buffer_ptr->tail = (tx_buffer_ptr->tail + 1) % SERIAL_BUFFER_SIZE_DEFAULT;
	#endif
	*(&(UCAxTXBUF) + offset) = c;
}
// Preinstantiate Objects //////////////////////////////////////////////////////

HardwareSerial Serial(&rx_buffer, &tx_buffer, DEBUG_UART_MODULE_OFFSET, DEBUG_UARTRXD_SET_MODE, DEBUG_UARTTXD_SET_MODE, DEBUG_UARTRXD, DEBUG_UARTTXD);
#ifdef SERIAL1_AVAILABLE
HardwareSerial Serial1(&rx_buffer1, &tx_buffer1, AUX_UART_MODULE_OFFSET, AUX_UARTRXD_SET_MODE, AUX_UARTTXD_SET_MODE, AUX_UARTRXD, AUX_UARTTXD);
#endif

#endif
