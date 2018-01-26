/**
 * File: eusci_spi.c - msp430 USCI SPI implementation
 *
 * EUSCI flavor implementation by Robert Wessels <robertinant@yahoo.com>
 * Copyright (c) 2012 by Rick Kimball <rick@kimballsoftware.com>
 * spi abstraction api for msp430
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 */

#include <msp430.h>
#include <stdint.h>
#include "spi_430.h"
#include <Energia.h>

#ifdef __MSP430_HAS_EUSCI_B0__


#if defined(__MSP430_HAS_EUSCI_B0__)
#define UCB0_BASE ((uint16_t)&UCB0CTLW0)
#endif
#if defined(__MSP430_HAS_EUSCI_B1__)
#define UCB1_BASE ((uint16_t)&UCB1CTLW0)
#endif
#if defined(__MSP430_HAS_EUSCI_B2__)
#define UCB2_BASE ((uint16_t)&UCB2CTLW0)
#endif

#if defined(DEFAULT_SPI) && (DEFAULT_SPI == 1)
uint16_t SPI_baseAddress = UCB1_BASE;
#else
uint16_t SPI_baseAddress = UCB0_BASE;
#endif

#define UCBxCTLW0     (*((volatile uint16_t *)((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0CTLW0)  - UCB0_BASE))))
#define UCBxCTL0      (*((volatile uint8_t *) ((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0CTLW0)+1- UCB0_BASE))))
#define UCBxCTL1      (*((volatile uint8_t *) ((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0CTLW0)  - UCB0_BASE))))
#define UCBxBRW       (*((volatile uint16_t *)((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0BRW)    - UCB0_BASE))))
#define UCBxBR0       (*((volatile uint8_t *) ((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0BRW)    - UCB0_BASE))))
#define UCBxBR1       (*((volatile uint8_t *) ((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0BRW)+1  - UCB0_BASE))))
#define UCBxTXBUF     (*((volatile uint8_t *) ((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0TXBUF)  - UCB0_BASE))))
#define UCBxRXBUF     (*((volatile uint8_t *) ((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0RXBUF)  - UCB0_BASE))))
#define UCBxIFG       (*((volatile uint8_t *) ((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0IFG)    - UCB0_BASE))))
#define UCBxIE        (*((volatile uint8_t *) ((uint16_t)(SPI_baseAddress + ((uint16_t)&UCB0IE)     - UCB0_BASE))))


/**
 * USCI flags for various the SPI MODEs
 *
 * Note: The msp430 UCCKPL tracks the CPOL value. However,
 * the UCCKPH flag is inverted when compared to the CPHA
 * value described in Motorola documentation.
 */

#define SPI_MODE_0 (UCCKPH)		/* CPOL=0 CPHA=0 */
#define SPI_MODE_1 (0)			/* CPOL=0 CPHA=1 */
#define SPI_MODE_2 (UCCKPL | UCCKPH)	/* CPOL=1 CPHA=0 */
#define SPI_MODE_3 (UCCKPL)		/* CPOL=1 CPHA=1 */

#define SPI_MODE_MASK (UCCKPL | UCCKPH)

/**
 * spi_initialize() - Configure USCI UCBx for SPI mode
 *
 * P2.0 - CS (active low)
 * P1.5 - SCLK
 * P1.6 - MISO aka SOMI
 * P1.7 - MOSI aka SIMO
 *
 */
void spi_initialize(void)
{
	/* Put USCI in reset mode, source USCI clock from SMCLK. */
	UCBxCTLW0 = UCSWRST | UCSSEL_2;

	/* SPI in master MODE 0 - CPOL=0 SPHA=0. */
	UCBxCTLW0 |= SPI_MODE_0 | UCMSB | UCSYNC | UCMST;

	/* Set pins to SPI mode. */
#if defined(DEFAULT_SPI)
	if (SPI_baseAddress == UCB1_BASE) {
		pinMode_int(SCK1, SPISCK1_SET_MODE);
		pinMode_int(MOSI1, SPIMOSI1_SET_MODE);
		pinMode_int(MISO1, SPIMISO1_SET_MODE);
	}else{
		pinMode_int(SCK0, SPISCK0_SET_MODE);
		pinMode_int(MOSI0, SPIMOSI0_SET_MODE);
		pinMode_int(MISO0, SPIMISO0_SET_MODE);
	}
#else
	pinMode_int(SCK, SPISCK_SET_MODE);
	pinMode_int(MOSI, SPIMOSI_SET_MODE);
	pinMode_int(MISO, SPIMISO_SET_MODE);
#endif


	/* Set initial speed to 4MHz. */
	UCBxBR0 = SPI_CLOCK_DIV4 & 0xFF;
	UCBxBR1 = (SPI_CLOCK_DIV4 >> 8 ) & 0xFF;

	/* Release USCI for operation. */
	UCBxCTLW0 &= ~UCSWRST;
}

/**
 * spi_disable() - put USCI into reset mode.
 */
void spi_disable(void)
{
	/* Put USCI in reset mode. */
	UCBxCTLW0 |= UCSWRST;
}

/**
 * spi_send() - send a byte and recv response.
 */
uint8_t spi_send(const uint8_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCBxIFG & UCTXIFG));

	/* Setting TXBUF clears the TXIFG flag. */
	UCBxTXBUF = data;

	/* Wait for a rx character? */
	while (!(UCBxIFG & UCRXIFG));

	/* Reading clears RXIFG flag. */
	return UCBxRXBUF;
}

uint16_t spi_send16(const uint16_t data)
{
	uint16_t datain;
	/* Wait for previous tx to complete. */
	while (!(UCBxIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCBxTXBUF = data | 0xFF;
	/* Wait for previous tx to complete. */
	while (!(UCBxIFG & UCTXIFG));

	datain = UCBxRXBUF << 8;
	/* Setting TXBUF clears the TXIFG flag. */
	UCBxTXBUF = data >> 8;

	/* Wait for a rx character? */
	while (!(UCBxIFG & UCRXIFG));

	/* Reading clears RXIFG flag. */
	return (datain | UCBxRXBUF);
}

void spi_send(void *buf, uint16_t count)
{
    uint8_t *ptx = (uint8_t *)buf;
    uint8_t *prx = (uint8_t *)buf;
	if (count == 0) return;
	/* Wait for previous tx to complete. */
	while (!(UCBxIFG & UCTXIFG));
	while(count){
		if (UCBxIFG & UCRXIFG){
			/* Reading RXBUF clears the RXIFG flag. */
			*prx++ = UCBxRXBUF;
		}
		if (UCBxIFG & UCTXIFG){
			/* Setting TXBUF clears the TXIFG flag. */
			UCBxTXBUF = *ptx++;
			count--;
		}
	}
	/* Wait for last rx character? */
	while (!(UCBxIFG & UCRXIFG));
	*prx++ = UCBxRXBUF;
}

/**
 * spi_transmit() - send a byte.
 */
void spi_transmit(const uint8_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCBxIFG & UCTXIFG));

	/* Setting TXBUF clears the TXIFG flag. */
	UCBxTXBUF = data;

	/* Wait for a rx character? */
	while (!(UCBxIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCBxIFG &= ~UCRXIFG;
}

void spi_transmit16(const uint16_t data)
{
	/* Wait for previous tx to complete. */
	while (!(UCBxIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCBxTXBUF = data | 0xFF;
	/* Wait for previous tx to complete. */
	while (!(UCBxIFG & UCTXIFG));
	/* Setting TXBUF clears the TXIFG flag. */
	UCBxTXBUF = data >> 8;

	/* Wait for a rx character? */
	while (!(UCBxIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCBxIFG &= ~UCRXIFG;
}

void spi_transmit(void *buf, uint16_t count)
{
    uint8_t *ptx = (uint8_t *)buf;
	if (count == 0) return;
	while(count){
		if (UCBxIFG & UCTXIFG){
			/* Setting TXBUF clears the TXIFG flag. */
			UCBxTXBUF = *ptx++;
			count--;
		}
	}
	/* Wait for last rx character? */
	while (!(UCBxIFG & UCRXIFG));
	/* clear RXIFG flag. */
	UCBxIFG &= ~UCRXIFG;
}

/***SPI_MODE_0
 * spi_set_divisor() - set new clock divider for USCI.
 *
 * USCI speed is based on the SMCLK divided by BR0 and BR1.
 *
 */
void spi_set_divisor(const uint16_t clkdiv)
{
	/* Hold UCBx in reset. */
	UCBxCTLW0 |= UCSWRST;

	UCBxBR0 = clkdiv & 0xFF;
	UCBxBR1 = (clkdiv >> 8 ) & 0xFF;

	/* Release for operation. */
	UCBxCTLW0 &= ~UCSWRST;
}

/**
 * spi_set_bitorder(LSBFIRST=0 | MSBFIRST=1).
 */
void spi_set_bitorder(const uint8_t order)
{
	/* Hold UCBx in reset. */
	UCBxCTLW0 |= UCSWRST;

	UCBxCTLW0 = (UCBxCTLW0 & ~UCMSB) | ((order == 1 /*MSBFIRST*/) ? UCMSB : 0); /* MSBFIRST = 1 */

	/* Release for operation. */
	UCBxCTLW0 &= ~UCSWRST;
}

/**
 * spi_set_datamode() - mode 0 - 3.
 */
void spi_set_datamode(const uint8_t mode)
{
	/* Hold UCBx in reset. */
	UCBxCTL1 |= UCSWRST;
	switch(mode) {
	case 0: /* SPI_MODE0 */
		UCBxCTLW0 = (UCBxCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_0;
		break;
	case 1: /* SPI_MODE1 */
		UCBxCTLW0 = (UCBxCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_1;
		break;
	case 2: /* SPI_MODE2 */
		UCBxCTLW0 = (UCBxCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_2;
		break;
	case 4: /* SPI_MODE3 */
		UCBxCTLW0 = (UCBxCTLW0 & ~SPI_MODE_MASK) | SPI_MODE_3;
		break;
	default:
		break;
	}

	/* Release for operation. */
	UCBxCTL1 &= ~UCSWRST;
}
#endif
