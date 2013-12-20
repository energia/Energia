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

#if defined(__MSP430_HAS_USCI__)

static const uint8_t SS      = 9;  /* P3.0 */
static const uint8_t SCK     = 11;  /* P3.3 */
static const uint8_t MOSI    = 10;  /* P3.1 */
static const uint8_t MISO    = 8;  /* P3.2 */

static const uint8_t TWISDA  = 10;  /* P3.1 */
static const uint8_t TWISCL  = 8;  /* P3.2 */

static const uint8_t DEBUG_UARTRXD = 20;  /* Receive  Data (RXD) at P3.5 */
static const uint8_t DEBUG_UARTTXD = 19;  /* Transmit Data (TXD) at P3.4 */

#define TWISDA_SET_MODE (PORT_SELECTION0)
#define TWISCL_SET_MODE (PORT_SELECTION0)
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | (PORT_SELECTION1) | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | (PORT_SELECTION1) | OUTPUT)
#define SPISCK_SET_MODE (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
#endif

#define DEBUG_UART_MODULE_OFFSET 0x00

static const uint8_t A0  = 0;
static const uint8_t A1  = 1;
static const uint8_t A2  = 2;
static const uint8_t A3  = 3;
static const uint8_t A4  = 4;
static const uint8_t A5  = 5;
static const uint8_t A6  = 6;
static const uint8_t A7  = 7;
static const uint8_t A10 = 10; // special. This is the internal temp sensor
static const uint8_t A11  = 11;
static const uint8_t A12  = 12;
static const uint8_t A13  = 13;
static const uint8_t A14  = 14;
static const uint8_t A15  = 15;

/*
F2274 RF2500T pin mapping

								debug uart up

                               +--\/--+
                          VCC  |1   18| GND
                     (A1) P2.1 |2   17| P2.0 (A0)
                (TA1, A3) P2.3 |3   16| P2.2 (TA1, A2)
               (TB0, A12) P4.3 |4   15| P2.4 (TA2, A4)
               (TB2, A14) P4.5 |5   14| P4.4 (TB1, A13)
                           GND |6   13| P4.6 (A15)
             (XOUT, GDO2) P2.7 |7   12| P2.6 (XIN, GDO0)
                (UCB0CLK) P3.3 |8   11| P3.2 (UCB0SOMI)
               (UCB0SIMO) P3.1 |9   10| P3.0 (UCB0STE)
                               +------+

*/

/* Pin names based on the silkscreen */

/* PIN1 = VCC */
static const uint8_t P2_1 = 2;
static const uint8_t P2_3 = 3;
static const uint8_t P4_3 = 4;
static const uint8_t P4_5 = 5;
/* PIN6 = GND */
static const uint8_t P2_7 = 7;
static const uint8_t P3_3 = 8;
static const uint8_t P3_1 = 9;
static const uint8_t P3_0 = 10;
static const uint8_t P3_2 = 11;
static const uint8_t P2_6 = 12;
static const uint8_t P4_6 = 13;
static const uint8_t P4_4 = 14;
static const uint8_t P2_4 = 15;
static const uint8_t P2_2 = 16;
static const uint8_t P2_0 = 17;
/* PIN18 = GND */

/* Extra pins not on the header + temp sensor */
static const uint8_t P3_4 = 19;		//TXD0
static const uint8_t P3_5 = 20;		//RXD0

static const uint8_t P1_0 = 21;		//grn
static const uint8_t P1_1 = 22;		//red
static const uint8_t P1_2 = 23;		//button

static const uint8_t RED = 21;		//P1.0
static const uint8_t RED_LED = 21;
static const uint8_t GREEN = 22;	//P1.1
static const uint8_t GREEN_LED = 22;
static const uint8_t BUTTON = 23;	//P1.2

static const uint8_t TEMPSENSOR = 10;	//internal A10

/* Onboard CC2500 */
static const uint8_t GDO0 = 12;		//P2.6
static const uint8_t GDO2 = 7;		//P2.7

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

};


const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /*  dummy */
	NOT_ON_TIMER, /*  1 - VCC */
	NOT_ON_TIMER, /*  2 - P2.1 */
	T0A1,         /*  3 - P2.3 */
	T0B0,         /*  4 - P4.3 */
	T0B2,         /*  5 - P4.5 */
	NOT_ON_TIMER, /*  6 - GND */
	NOT_ON_TIMER, /*  7 - P2.7 */
	NOT_ON_TIMER, /*  8 - P3.3 */
	NOT_ON_TIMER, /*  9 - P3.1 */
	NOT_ON_TIMER, /* 10 - P3.0 */
	NOT_ON_TIMER, /* 11 - P3.2 */
	NOT_ON_TIMER, /* 12 - P2.6 */
	NOT_ON_TIMER, /* 13 - P4.6 */
	T0B1,         /* 14 - P4.4 */
	T0A2,         /* 15 - P2.4 */
	T0A0,         /* 16 - P2.2 */
	NOT_ON_TIMER, /* 17 - P2.0 */
	NOT_ON_TIMER, /* 18 - GND */
	NOT_ON_TIMER, /* 19 - P3.4 */
	NOT_ON_TIMER, /* 20 - P3.5 */
	NOT_ON_TIMER, /* 21 - P1.0 */
	T0A0,         /* 22 - P1.1 */
	T0A1          /* 23 - P1.2 */

};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN, /* dummy */
	NOT_A_PIN, /* 1 */
	P2,        /* 2 */
	P2,        /* 3 */
	P4,        /* 4 */
	P4,        /* 5 */
	NOT_A_PIN,        /* 6 */
	P2,        /* 7 */
	P3,        /* 8 */
	P3,        /* 9 */
	P3,        /* 10 */
	P3,        /* 11 */
	P2,        /* 12 */
	P4, 		/* 13 */
	P4,        /* 14 */
	P2,        /* 15 */
	P2,        /* 16 */
	P2,        /* 17 */
	NOT_A_PIN, /* 18 */
	P3,		   /* 19 */
	P3,		   /* 20 */
	P1,		   /* 21 */
	P1,		   /* 22 */
	P1		   /* 23 */
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN, /* 0,  pin count starts at 1 */
	NOT_A_PIN, /* 1 */
	BV(1),     /* 2 */
	BV(3),     /* 3 */
	BV(3),     /* 4 */
	BV(5),     /* 5 */
	NOT_A_PIN,     /* 6 */
	BV(5),     /* 7 */
	BV(3),     /* 8 */
	BV(1),     /* 9 */
	BV(0),     /* 10 */
	BV(2),     /* 11 */
	BV(6),     /* 12 */
	BV(6), 		/* 13 */
	BV(4),     /* 14 */
	BV(4),     /* 15 */
	BV(2),	   /* 16 */
	BV(0),     /* 17 */
	NOT_A_PIN, /* 18 */
	BV(4),     /* 19 */
	BV(5),	   /* 20 */
	BV(0),	   /* 21 */
	BV(1),	   /* 22 */
	BV(2),     /* 23 */

};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
