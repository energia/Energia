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


static const uint8_t SS      = 10;  /* P2.0 */
static const uint8_t SCK     = 7;  /* P1.5 */
static const uint8_t MOSI    = 23; /* P1.7 */
static const uint8_t MISO    = 22; /* P1.6 */
static const uint8_t TWISCL1  = 11;   /* P2.1 SW I2C */
static const uint8_t TWISDA1  = 12;  /* P2.2 SW I2C */
static const uint8_t TWISDA0  = 23;  /* P1.7 */
static const uint8_t TWISCL0  = 22;  /* P1.6 */
static const uint8_t DEBUG_UARTRXD = 3;  /* Receive  Data (RXD) at P1.1 */
static const uint8_t DEBUG_UARTTXD = 4;  /* Transmit Data (TXD) at P1.2 */
#define TWISDA1_SET_MODE  (INPUT)
#define TWISCL1_SET_MODE  (INPUT)
#if defined(__MSP430_HAS_USCI__)
#define TWISDA0_SET_MODE  (PORT_SELECTION0 | PORT_SELECTION1 /* | INPUT_PULLUP*/) /* do not enable the pull ups for this device */
#define TWISCL0_SET_MODE  (PORT_SELECTION0 | PORT_SELECTION1 /* | INPUT_PULLUP*/)
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1 | OUTPUT)
#define SPISCK_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1)
#define SPIMOSI_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1)
#define SPIMISO_SET_MODE (PORT_SELECTION0 | PORT_SELECTION1)
#endif
#if defined(__MSP430_HAS_USI__)
#define TWISDA0_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL0_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define SPISCK_SET_MODE (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
#endif

/* Define the default I2C settings */
#define DEFAULT_I2C -1 /* indicates SW I2C on pseudo module 1 */
#define TWISDA TWISDA1
#define TWISCL TWISCL1
#define TWISDA_SET_MODE  TWISDA1_SET_MODE
#define TWISCL_SET_MODE  TWISCL1_SET_MODE

#define DEBUG_UART_MODULE_OFFSET 0x0

#define DEBUG_UART_MODULE 0x0

static const uint8_t A0  = 2;
static const uint8_t A1  = 3;
static const uint8_t A2  = 4;
static const uint8_t A3  = 5;
static const uint8_t A4  = 6;
static const uint8_t A5  = 7;
static const uint8_t A6  = 22;
static const uint8_t A7  = 23;
static const uint8_t A10 = 128 + 10; // special. This is the internal temp sensor

//                            +-\/-+
//               VCC         1|    |28  GND
//         (A0)  P1.0        2|    |27  P2.6/XIN/TA0.1
//         (A1)  P1.1/TA0.0  3|    |26  P2.7/XOUT
//         (A2)  P1.2/TA0.1  4|    |25  TEST
//         (A3)  P1.3        5|    |24  RST#
//         (A4)  P1.4        6|    |23  P1.7  (A7) (SCL) (MISO) depends on chip
//         (A5)  P1.5/TA0.0  7|    |22  P1.6/TA0.1  (A6) (SDA) (MOSI)
//               P3.1/TA1.0  8|    |21  P3.7/TA1CLK/CAOUT
//               P3.0/TA0.2  9|    |20  P3.6/TA0.2
//               P2.0/TA1.0 10|    |19  P3.5/TA0.1
//               P2.1/TA1.1 11|    |18  P2.5/TA1.2
//               P2.2/TA1.1 12|    |17  P2.4/TA1.2
//               P3.2/TA1.1 13|    |16  P2.3/TA1.0
//               P3.3/TA1.2 14|    |15  P3.4/TA0.0
//                            +----+
//

// Pin names based on the silkscreen
//
static const uint8_t P1_0 = 2;
static const uint8_t P1_1 = 3;
static const uint8_t P1_2 = 4;
static const uint8_t P1_3 = 5;
static const uint8_t P1_4 = 6;
static const uint8_t P1_5 = 7;
static const uint8_t P3_1 = 8;
static const uint8_t P3_0 = 9;
static const uint8_t P2_0 = 10;
static const uint8_t P2_1 = 11;
static const uint8_t P2_2 = 12;
static const uint8_t P3_2 = 13;
static const uint8_t P3_3 = 14;

static const uint8_t P3_4 = 15;
static const uint8_t P2_3 = 16;
static const uint8_t P2_4 = 17;
static const uint8_t P2_5 = 18;
static const uint8_t P3_5 = 19;
static const uint8_t P3_6 = 20;
static const uint8_t P3_7 = 21;
static const uint8_t P1_6 = 22;
static const uint8_t P1_7 = 23;
static const uint8_t P2_7 = 26;
static const uint8_t P2_6 = 27;

static const uint8_t RED_LED = 2;
static const uint8_t GREEN_LED = 14;
static const uint8_t PUSH2 = 5;
static const uint8_t TEMPSENSOR = 128 + 10; // depends on chip


#ifdef ARDUINO_MAIN

const uint16_t port_to_input[] = {
	NOT_A_PORT,
	(uint16_t) &P1IN,
	(uint16_t) &P2IN,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3IN,
#endif
};

const uint16_t port_to_output[] = {
	NOT_A_PORT,
	(uint16_t) &P1OUT,
	(uint16_t) &P2OUT,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3OUT,
#endif
};

const uint16_t port_to_dir[] = {
	NOT_A_PORT,
	(uint16_t) &P1DIR,
	(uint16_t) &P2DIR,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3DIR,
#endif
};

const uint16_t port_to_ren[] = {
	NOT_A_PORT,
	(uint16_t) &P1REN,
	(uint16_t) &P2REN,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3REN,
#endif
};

const uint16_t port_to_sel0[] = {  /* put this PxSEL register under the group of PxSEL0 */
	NOT_A_PORT,
	(uint16_t) &P1SEL,
	(uint16_t) &P2SEL,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3SEL,
#endif
};

const uint16_t port_to_sel2[] = {
	NOT_A_PORT,
#ifdef P1SEL2_
	(uint16_t) &P1SEL2,
#else
        NOT_A_PORT,
#endif
#ifdef P2SEL2_
	(uint16_t) &P2SEL2,
#else 
        NOT_A_PORT,
#endif
#ifdef P3SEL2_
	(uint16_t) &P3SEL2,
#else
        NOT_A_PORT,
#endif
};


/* 
 * Defines for devices with 2x TA3 timers (e.g. MSP430g2553). On the 20pin devices, upto 3 analog outputs are available
 * T0A1, T1A1 and T1A2 
 */
const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /*  dummy */
	NOT_ON_TIMER, /*  1 - VCC */
	NOT_ON_TIMER, /*  2 - P1.0 */
	T0A0,         /*  3 - P1.1, note: A0 output cannot be used with analogWrite */
	T0A1,         /*  4 - P1.2 */
	NOT_ON_TIMER, /*  5 - P1.3 */
	NOT_ON_TIMER, /*  6 - P1.4 note: special case. Leaving as no timer due to difficulty determining if available */
	T0A0,         /*  7 - P1.5 note: A0 output cannot be used with analogWrite  */
#if defined(__MSP430_HAS_T1A3__) 
	T1A0,         /*  8 - P3.1   */
	T0A2,         /*  9 - P3.0   */
	T1A0,         /* 10 - P2.0 note: A0 output cannot be used with analogWrite  */
	T1A1,         /* 11 - P2.1   */
	T1A1,         /* 12 - P2.2   */
	T1A1,         /* 13 - P3.2   */
	T1A2,         /* 14 - P3.3   */
	T0A0,         /*  15 - P3.4 note: A0 output cannot be used with analogWrite  */
	T1A0,         /*  16 - P2.3 note: A0 output cannot be used with analogWrite  */
	T1A2,         /*  17 - P2.4   */
	T1A2,         /*  18 - P2.5   */
	T0A1,         /*  19 - P3.5   */
	T0A2,         /*  20 - P3.6   */
#else
	NOT_ON_TIMER, /*  8 - P3.1   */
	NOT_ON_TIMER, /*  9 - P3.0   */
	NOT_ON_TIMER, /*  10 - P2.0   */
	NOT_ON_TIMER, /*  11 - P2.1   */
	NOT_ON_TIMER, /*  12 - P2.2   */
	NOT_ON_TIMER, /*  13 - P3.2   */
	NOT_ON_TIMER, /*  14 - P3.3   */
	NOT_ON_TIMER, /*  15 - P3.4   */
	NOT_ON_TIMER, /*  16 - P2.3   */
	NOT_ON_TIMER, /*  17 - P2.4   */
	NOT_ON_TIMER, /*  18 - P2.5   */
	NOT_ON_TIMER, /*  19 - P3.5   */
	NOT_ON_TIMER, /*  20 - P3.6   */
#endif
	NOT_ON_TIMER, /*  21 - P3.7 */
	T0A1,         /*  22 - P1.6 */
	NOT_ON_TIMER, /*  23 - P1.7 */
	NOT_ON_TIMER, /*  24 - /RESET */  
	NOT_ON_TIMER, /*  25 - TEST */  
	NOT_ON_TIMER, /*  26 - XOUT - P2.7 */
	T0A1,         /*  27 - XIN - P2.6: */
	NOT_ON_TIMER, /*  28 - GND */
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN, /* dummy */
	NOT_A_PIN, /* 1 */
	P1, /* 2 */
	P1, /* 3 */
	P1, /* 4 */
	P1, /* 5 */
	P1, /* 6 */
	P1, /* 7 */
	P3, /* 8 */
	P3, /* 9 */
	P2, /* 10 */
	P2, /* 11 */
	P2, /* 12 */
	P3, /* 13 */
	P3, /* 14 */
	P3, /* 15 */
	P2, /* 16 */
	P2, /* 17 */
	P2, /* 18 */
	P3, /* 19 */
	P3, /* 20 */
	P3, /* 21 */
	P1, /* 22 */
	P1, /* 23 */
	NOT_A_PIN, /* 24 */
	NOT_A_PIN, /* 25 */
	P2, /* 26 */
	P2, /* 27 */
	NOT_A_PIN, /* 28 */
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN, /* 0,  pin count starts at 1 */
	NOT_A_PIN, /* 1,  VCC */
	BV(0),     /* 2,  port P1.0 */
	BV(1),     /* 3,  port P1.1 */
	BV(2),     /* 4,  port P1.2 */
	BV(3),     /* 5,  port P1.3*/
	BV(4),     /* 6,  port P1.4 */
	BV(5),     /* 7,  port P1.5 */
	BV(1),     /* 8,  port P3.1 */
	BV(0),     /* 9,  port P3.0 */
	BV(0),     /* 10, port P2.0 */
	BV(1),     /* 11, port P2.1 */
	BV(2),     /* 12, port P2.2 */
	BV(2),     /* 13, port P3.2 */
	BV(3),     /* 14, port P3.3 */
	BV(4),     /* 15, port P3.4 */
	BV(3),     /* 16, port P2.3 */
	BV(4),     /* 17, port P2.4 */
	BV(5),     /* 18, port P2.5 */
	BV(5),     /* 19, port P3.5 */
	BV(6),     /* 20, port P3.6 */
	BV(7),     /* 21, port P3.7 */
	BV(6),     /* 22, port P1.6 */
	BV(7),     /* 23, port P1.7 */
        NOT_A_PIN, /* 24, RST */
	NOT_A_PIN, /* 25, TEST */
	BV(7),     /* 26, XOUT */
	BV(6),     /* 27, XIN */
	NOT_A_PIN, /* 28, GND */
};
const uint32_t digital_pin_to_analog_in[] = {
        NOT_ON_ADC,     /*  dummy   */
        NOT_ON_ADC,     /*  1 - 3.3V*/
        0,		/*  2 - A0 */
        1,     		/*  3 - A1 */
        2, 		/*  4 - A2 */
        3, 		/*  5 - A3 */
        4, 		/*  6 - A4 */
        5,   		/*  7 - A5 */
        NOT_ON_ADC, 	/*  8 - P3.1 */
        NOT_ON_ADC, 	/*  9 - P3.0 */
        NOT_ON_ADC, 	/*  10 - P2.0 */
        NOT_ON_ADC, 	/*  11 - P2.1 */
        NOT_ON_ADC, 	/*  12 - P2.2 */
        NOT_ON_ADC, 	/*  13 - P3.2 */
        NOT_ON_ADC, 	/*  14 - P3.3 */
        NOT_ON_ADC, 	/*  15 - P3.2 */
        NOT_ON_ADC, 	/*  16 - P2.3 */
        NOT_ON_ADC, 	/*  17 - P2.4 */
        NOT_ON_ADC, 	/*  18 - P2.5 */
        NOT_ON_ADC, 	/*  19 - P3.5 */
        NOT_ON_ADC, 	/*  20 - P3.6 */
        NOT_ON_ADC, 	/*  21 - P3.7 */
        6,     		/*  22 - A6 */
        7,     		/*  23 - A7 */
        NOT_ON_ADC, 	/*  24 - RST */
        NOT_ON_ADC,     /*  25 - PF0 */
        NOT_ON_ADC, 	/*  26 - PE0 */
        NOT_ON_ADC,     /*  27 - PB2 */
        NOT_ON_ADC  	/*  28 - GND */
};

#endif
#endif
