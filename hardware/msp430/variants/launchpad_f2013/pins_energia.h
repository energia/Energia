/*
  ************************************************************************
  *	pins_energia.h
  *
  *	Energia core files for MSP430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *     Contribution: Rei VILO
  *
  ***********************************************************************
  Derived from:
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#ifndef Pins_Energia_h
#define Pins_Energia_h
#ifndef BV
#define BV(x) (1 << (x))
#endif

#if defined(__MSP430_HAS_USI__)
static const uint8_t SS      = 6;
static const uint8_t SCK     = 7;  /* P3.2 */
static const uint8_t MOSI    = 8;
static const uint8_t MISO    = 9;
static const uint8_t TWISDA  = 9;
static const uint8_t TWISCL  = 8;
static const uint8_t DEBUG_UARTRXD = 3;  /* Receive  Data (RXD) at P4.5 */
static const uint8_t DEBUG_UARTTXD = 4;  /* Transmit Data (TXD) at P4.4 */
static const uint8_t AUX_UARTRXD = 3;  /* Receive  Data (RXD) at P4.5 */
static const uint8_t AUX_UARTTXD = 4;  /* Transmit Data (TXD) at P4.4 */
#define TWISDA_SET_MODE (PORT_SELECTION0)
#define TWISCL_SET_MODE (PORT_SELECTION0)
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define AUX_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define AUX_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define SPISCK_SET_MODE (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
#endif

#define DEBUG_UART_MODULE_OFFSET 0x40
#define AUX_UART_MODULE_OFFSET 0x0
#define SERIAL1_AVAILABLE 0

#if defined(__MSP430_HAS_USCI_A1__)
#define USE_USCI_A1
#endif

#define GREEN_LED 2
#define RED_LED 3

static const uint8_t A0  = 2;
static const uint8_t A1  = 4;
static const uint8_t A2  = 6;

/* Pin names based on the silkscreen */

/* PIN1 = 3.3v */
static const uint8_t P1_0 = 2;
static const uint8_t P1_1 = 3;
static const uint8_t P1_2 = 4;
static const uint8_t P1_3 = 5;
static const uint8_t P1_4 = 6;
static const uint8_t P1_5 = 7;
static const uint8_t P1_6 = 8;
static const uint8_t P1_7 = 9;
/* PIN10 is RST */
/* PIN11 is TEST */

static const uint8_t P2_7 = 12;
static const uint8_t P2_6 = 13;
/* PIN14 is Vss */

#ifdef ARDUINO_MAIN

const uint16_t port_to_input[] = {
	NOT_A_PORT,
	(uint16_t) &P1IN,
	(uint16_t) &P2IN,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3IN,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4IN,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5IN,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6IN,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7IN,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8IN,
#endif
};

const uint16_t port_to_output[] = {
	NOT_A_PORT,
	(uint16_t) &P1OUT,
	(uint16_t) &P2OUT,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3OUT,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4OUT,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5OUT,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6OUT,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7OUT,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8OUT,
#endif
};

const uint16_t port_to_dir[] = {
	NOT_A_PORT,
	(uint16_t) &P1DIR,
	(uint16_t) &P2DIR,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3DIR,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4DIR,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5DIR,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6DIR,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7DIR,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8DIR,
#endif
};

const uint16_t port_to_ren[] = {
	NOT_A_PORT,
	(uint16_t) &P1REN,
	(uint16_t) &P2REN,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3REN,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4REN,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5REN,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6REN,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7REN,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8REN,
#endif
};

const uint16_t port_to_sel0[] = {  /* put this PxSEL register under the group of PxSEL0 */
	NOT_A_PORT,
	(uint16_t) &P1SEL,
	(uint16_t) &P2SEL,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3SEL,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4SEL,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5SEL,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6SEL,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7SEL,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8SEL,
#endif
};

const uint16_t port_to_pmap[] = {
	NOT_A_PORT,	/* PMAP starts at port P1 */
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /*  dummy */
	NOT_ON_TIMER, /*  1 - 3.3v */
	NOT_ON_TIMER, /*  2 - P5.6 */
	T0A0,  
	T0A1,         /*  4 - P3.3 */
	NOT_ON_TIMER, /*  5 - P1.6 */
	NOT_ON_TIMER, /*  6 - P6.6 */
	NOT_ON_TIMER, /*  7 - P3.2 */
	NOT_ON_TIMER, /*  8 - P2.7 */
	NOT_ON_TIMER, /*  9 - P4.2 */
	NOT_ON_TIMER, /* 10 - P4.1 */
	NOT_ON_TIMER, /* 11 - P8.1 */
	NOT_ON_TIMER, /* 12 - P2.3 */
	NOT_ON_TIMER, /* 13 - P2.6 */
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN, /* dummy */
	NOT_A_PIN, /* 1 */
	P1,        /* 2 */
	P1,        /* 3 */
	P1,        /* 4 */
	P1,        /* 5 */
	P1,        /* 6 */
	P1,        /* 7 */
	P1,        /* 8 */
	P1,        /* 9 */
	NOT_A_PIN, /* 10 */
	NOT_A_PIN, /* 11 */
	P2,        /* 12 */
	P2,        /* 13 */
	NOT_A_PIN, /* 14 */
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN, /* 0,  pin count starts at 1 */
	NOT_A_PIN, /* 1 */
	BV(0),     /* 2 */
	BV(1),     /* 3 */
	BV(2),     /* 4 */
	BV(3),     /* 5 */
	BV(4),     /* 6 */
	BV(5),     /* 7 */
	BV(6),     /* 8 */
	BV(7),     /* 9 */
	NOT_A_PIN, /* 10 */
	NOT_A_PIN, /* 11 */
	BV(7),     /* 12 */
	BV(6),     /* 13 */
	NOT_A_PIN, /* 20 */
};

const uint32_t digital_pin_to_analog_in[] = {
        NOT_ON_ADC,     /*  dummy   */
        NOT_ON_ADC,     /*  1 - 3.3V*/
        0,				/*  2 - A5 */
        NOT_ON_ADC,     /*  3 - P3.4 */
        1,
        NOT_ON_ADC, 	/*  5 - P1.6 */
        2, 				/*  6 - A6 */
        NOT_ON_ADC,   	/*  7 - P3.2 */
        3,
        NOT_ON_ADC, 	/*  9 - P4.2 */
        NOT_ON_ADC, 	/*  10 - P4.1 */
        NOT_ON_ADC, 	/*  11 - P8.1 */
        NOT_ON_ADC, 	/*  12 - P2.3 */
        NOT_ON_ADC, 	/*  13 - P2.6 */
        NOT_ON_ADC,     /*  14 - P3.1 */
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
