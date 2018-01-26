/*
  ************************************************************************
  *	pins_energia.h
  *
  *	Pin definition functions for LaunchPad w/ msp430fr2311
  *		Copyright (c) 2015 Robert Wessels. All right reserved.
  *
  *     Contribution: Zilin Xu
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


#if defined(__MSP430_HAS_EUSCI_B0__)
static const uint8_t SS      = 8;   /* P2.1 */
static const uint8_t SCK     = 7;   /* P2.3 */
static const uint8_t MOSI    = 15;  /* P2.4 aka SIMO */
static const uint8_t MISO    = 14;  /* P2.5 aka SOMI */
static const uint8_t TWISCL1  = 9;   /* P1.3 SW I2C */
static const uint8_t TWISDA1  = 10;  /* P1.2 SW I2C */
static const uint8_t TWISDA0  = 15;  /* P2.4 UCB0 */
static const uint8_t TWISCL0  = 14;  /* P2.5 UCB0 */
#define TWISDA0_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL0_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISDA1_SET_MODE  (INPUT_PULLUP)
#define TWISCL1_SET_MODE  (INPUT_PULLUP)
#define SPISCK_SET_MODE  (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
/* Define the default I2C settings */
#define DEFAULT_I2C -1 /* indicates SW I2C on pseudo module 1 */
#define TWISDA TWISDA1
#define TWISCL TWISCL1
#define TWISDA_SET_MODE  TWISDA1_SET_MODE
#define TWISCL_SET_MODE  TWISCL1_SET_MODE
#endif

#if defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
static const uint8_t DEBUG_UARTRXD = 3;  /* Receive  Data (RXD) at P1.6 */
static const uint8_t DEBUG_UARTTXD = 4;  /* Transmit Data (TXD) at P1.7 */
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define DEBUG_UART_MODULE_OFFSET 0x00
#endif


/* Analog pins */

static const uint8_t A0  = 5;
static const uint8_t A1  = 11;
static const uint8_t A2  = 10;  
static const uint8_t A3  = 9;
static const uint8_t A4  = 2;
static const uint8_t A5  = 6;
static const uint8_t A6  = 3;
static const uint8_t A7  = 4;
static const uint8_t A8  = 128 + 8;  // Not available on FR2311
static const uint8_t A9  = 128 + 9;  // Not available on FR2311
static const uint8_t A10 = 128 + 10; // Not available on FR2311
static const uint8_t A11 = 128 + 11; // Not available on FR2311
static const uint8_t A12 = 128 + 12; // Not available on FR2311
static const uint8_t A13 = 128 + 13; // Not available on FR2311
static const uint8_t A14 = 128 + 14; // Not available on FR2311
static const uint8_t A15 = 128 + 15; // Not available on FR2311

//-------------------------------------------

/* Layout of the 2 - 10 pin headers.

   All pins support digitalWrite() and attachInterrupt()
   Pins marked with PWM support anaglogWrite()
   Pins marked with Ax support analogRead()

                                          +---\/---+
                                   VCC0  1|        |20  GND
                            (A4)   P1.4  2|        |19  P2.0         (PWM)
      (UCA0RXD -> Serial0)  (A6)   P1.6  3|        |18  P2.2       	 (I/O)
      (UCA0TXD -> Serial0)  (A7)   P1.7  4|        |17               (NC)
                            (A0)   P1.0  5|        |16  RST
                            (A5)   P1.5  6|        |15  P2.4         (MOSI)
                   (SCLK)          P2.3  7|        |14  P2.5 		 (MISO)
                                   P2.1  8|        |13  P2.7            
                    (SCL)   (A3)   P1.3  9|        |12  P2.6         (I/O) 
                    (SDA)   (A2)   P1.2 10|        |11  P1.1         (A1)
                                          +--------+


                                               ----+
                                                   |4   DebugUART TX  (P1.7) (A7)
                     J13 eZ-FET Connector          |3   DebugUART RX  (P1.6) (A6)
                                               ----+
                                               ----+
                                                   |5   LED1       (P1.0)   (A0) 
                     Extra LED's and Switches      |19  LED2       (P2.0)   (PWM)
                                                   |11  PUSH1      (P1.1)   (A1)
                                               ----+
*/

// Pin names based on the silkscreen
//

static const uint8_t P1_0 = 5;
static const uint8_t P1_1 = 11;
static const uint8_t P1_2 = 10;
static const uint8_t P1_3 = 9;
static const uint8_t P1_4 = 2;
static const uint8_t P1_5 = 6;
static const uint8_t P1_6 = 3;
static const uint8_t P1_7 = 4;

static const uint8_t P2_0 = 19;
static const uint8_t P2_1 = 8;
static const uint8_t P2_2 = 18;
static const uint8_t P2_3 = 7;
static const uint8_t P2_4 = 15;
static const uint8_t P2_5 = 14;
static const uint8_t P2_6 = 12;
static const uint8_t P2_7 = 13;

//static const uint8_t PJ_0 = ;
//static const uint8_t PJ_1 = ;
//static const uint8_t PJ_2 = ;
//static const uint8_t PJ_3 = ;
//static const uint8_t PJ_4 = ;
//static const uint8_t PJ_5 = ;
//static const uint8_t PJ_6 = ;
//static const uint8_t PJ_7 = ;


static const uint8_t LED1 = 5;
static const uint8_t LED2 = 19;
/* For LaunchPad compatability */
static const uint8_t RED_LED = 5;
static const uint8_t GREEN_LED = 19;

static const uint8_t PUSH1 = 11;
static const uint8_t TEMPSENSOR = 128 + 12; // depends on chip

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
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJIN,
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
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJOUT,
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
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJDIR,
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
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJREN,
#endif
};

const uint16_t port_to_sel0[] = {
	NOT_A_PORT,
	(uint16_t) &P1SEL0,
	(uint16_t) &P2SEL0,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3SEL0,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4SEL0,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5SEL0,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6SEL0,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7SEL0,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8SEL0,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJSEL0,
#endif
};

const uint16_t port_to_sel1[] = {
	NOT_A_PORT,
	(uint16_t) &P1SEL1,
	(uint16_t) &P2SEL1,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3SEL1,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4SEL1,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5SEL1,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6SEL1,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7SEL1,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8SEL1,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
	(uint16_t) &PJSEL1,
#endif
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER,  /*  0 - pin count starts at 1 */
	NOT_ON_TIMER,  /*  1 - Vcc */
	NOT_ON_TIMER,  /*  2 - P1.4 */
	T0B1,          /*  3 - P1.6 */
	T0B2,          /*  4 - P1.7 */
	NOT_ON_TIMER,  /*  5 - P1.0 */
	NOT_ON_TIMER,  /*  6 - P1.5 */
	NOT_ON_TIMER,  /*  7 - P2.3 */
	T1B2,          /*  8 - P2.1 */
	NOT_ON_TIMER,  /*  9 - P1.3 */
	NOT_ON_TIMER,  /* 10 - P1.2 */
	NOT_ON_TIMER,  /* 11 - P1.1 */
	NOT_ON_TIMER,  /* 12 - P2.6 */
	NOT_ON_TIMER,  /* 13 - P2.7 */
	NOT_ON_TIMER,  /* 14 - P2.5 */
	NOT_ON_TIMER,  /* 15 - P2.4 */
	NOT_ON_TIMER,  /* 16 - RST */
	NOT_ON_TIMER,  /* 17 - NC */
	NOT_ON_TIMER,  /* 18 - P2.2 */
	T1B1,          /* 19 - P2.0 */
	NOT_ON_TIMER,  /* 20 - GND */
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN,   /*  0 - pin count starts at 1 */
	NOT_A_PIN,   /*  1 - Vcc */
	P1,          /*  2 - P1.4 */
	P1,          /*  3 - P1.6 */
	P1,          /*  4 - P1.7 */
	P1,          /*  5 - P1.0 */
	P1,          /*  6 - P1.5 */
	P2,          /*  7 - P2.3 */
	P2,          /*  8 - P2.1 */
	P1,          /*  9 - P1.3 */
	P1,          /* 10 - P1.2 */
	P1,          /* 11 - P1.1 */
	P2,          /* 12 - P2.6 */
	P2,          /* 13 - P2.7 */
	P2,          /* 14 - P2.5 */
	P2,          /* 15 - P2.4 */
	NOT_A_PIN,   /* 16 - RST */
	NOT_A_PIN,   /* 17 - NC */
	P2,          /* 18 - P2.2 */
	P2,          /* 19 - P2.0 */
	NOT_A_PIN,   /* 20 - GND */
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN,   /*  0 - pin count starts at 1 */
	NOT_A_PIN,   /*  1 - Vcc */
	BV(4),       /*  2 - P1.4 */
	BV(6),       /*  3 - P1.6 */
	BV(7),       /*  4 - P1.7 */
	BV(0),       /*  5 - P1.0 */
	BV(5),       /*  6 - P1.5 */
	BV(3),       /*  7 - P2.3 */
	BV(1),       /*  8 - P2.1 */
	BV(3),       /*  9 - P1.3 */
	BV(2),       /* 10 - P1.2 */
	BV(1),       /* 11 - P1.1 */
	BV(6),       /* 12 - P2.6 */
	BV(7),       /* 13 - P2.7 */
	BV(5),       /* 14 - P2.5 */
	BV(4),       /* 15 - P2.4 */
	NOT_A_PIN,   /* 16 - RST */
	NOT_A_PIN,   /* 17 - NC */
	BV(2),       /* 18 - P2.2 */
	BV(0),       /* 19 - P2.0 */
	NOT_A_PIN,   /* 20 - GND */
};

const uint32_t digital_pin_to_analog_in[] = {
		NOT_ON_ADC,   	/*  0 - pin count starts at 1 */
		NOT_ON_ADC,   	/*  1 - Vcc */
		4,    			/*  2 - P1.4 */
		6,    			/*  3 - P1.6 */
		7,     			/*  4 - P1.7 */
		0,     			/*  5 - P1.0 */
		5,     			/*  6 - P1.5 */
		NOT_ON_ADC,     /*  7 - P2.3 */
		NOT_ON_ADC,     /*  8 - P2.1 */
		3,     			/*  9 - P1.3 */
		2,     			/* 10 - P1.2 */
		1,     			/* 11 - P1.1 */
		NOT_ON_ADC,     /* 12 - P2.6 */
		NOT_ON_ADC,     /* 13 - P2.7 */
		NOT_ON_ADC,     /* 14 - P2.5 */
		NOT_ON_ADC,     /* 15 - P2.4 */
		NOT_ON_ADC, 	/* 16 - RST */
		NOT_ON_ADC,     /* 17 - NC */
		NOT_ON_ADC,     /* 18 - P2.2 */
		NOT_ON_ADC,     /* 19 - P2.0 */
		NOT_ON_ADC,   	/* 20 - GND */
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
