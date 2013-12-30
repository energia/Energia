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

#if defined(__MSP430_HAS_USCI_A0__) || defined(__MSP430_HAS_USCI_A1__)
static const uint8_t SS      = 8;  /* P2.7 */
static const uint8_t SCK     = 7;  /* P3.2 */
static const uint8_t MOSI    = 15;  /* P3.0 */
static const uint8_t MISO    = 14;  /* P3.1 */
static const uint8_t TWISDA  = 15;  /* P3.0 */
static const uint8_t TWISCL  = 14;  /* P3.1 */
static const uint8_t DEBUG_UARTRXD = 45;  /* Receive  Data (RXD) at P4.5 */
static const uint8_t DEBUG_UARTTXD = 46;  /* Transmit Data (TXD) at P4.4 */
static const uint8_t AUX_UARTRXD = 3;  /* Receive  Data (RXD) at P4.5 */
static const uint8_t AUX_UARTTXD = 4;  /* Transmit Data (TXD) at P4.4 */
#define TWISDA_SET_MODE (PORT_SELECTION0)
#define TWISCL_SET_MODE (PORT_SELECTION0)
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | (PM_UCA1RXD << 8) | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | (PM_UCA1TXD << 8) | OUTPUT)
#define AUX_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define AUX_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define SPISCK_SET_MODE (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)
#endif

#define DEBUG_UART_MODULE_OFFSET 0x40
#define AUX_UART_MODULE_OFFSET 0x0
#define SERIAL1_AVAILABLE 1

#if defined(__MSP430_HAS_USCI_A1__)
#define USE_USCI_A1
#endif

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
 F5529 LaunchPad pin mapping
 
								J4
                               +--\/--+
                          3.3v |1   14| P6.6 (CB6, A6)
           (UCA1RXD/SOMI) P4.5 |2   13| P8.1 (GPIO - LED2)
           (UCA1TXD/SIMO) P4.4 |3   12| P8.2 (GPIO - LED3)
		      (GPIO - RF) P4.6 |4   11| P8.0 (GPIO - POT)
              (GPIO - RF) P4.7 |5   10| P4.5 (UCA1RXD/SOMI)
                     (A9) P5.1 |6    9| P4.4 (UCA1TXD/SIMO)
                           GND |7    8| P6.7 (CB7, A7)
*/
/*						   		
								J5
                                +--\/--+
                           3.3v |15   28| P7.0 (CB8, A12)
       (UCB1SOMI/SCL - SD) P4.2 |16   27| P7.1 (CB9, A13)
   (UCB1SIMO/SDA - LCD/SD) P4.1 |17   26| P7.2 (CB10, A14)
(UCB1CLK/UCA1STE - LCD/SD) P4.3 |18   25| P7.3 (CB11, A15)
    (UCB1STE/UCA1CLK - RF) P4.0 |19   24| P4.1 (UCB1SIM0/UCB1SDA - LCD/SD)
    (TB0OUTH, SVMOUT - SD) P3.7 |20   23| P4.2 (UCB1SOMI/UCB1SCL - SD)
                            GND |21   22| P7.7 (TB0CLK)
*/
/*						
								 J12
                               +--\/--+
           (UCB0STE - RF) P2.6 |29  46| P3.0 (UCB0SIMO - RF)
          (UCB0SOMI - RF) P3.1 |30  45| P3.2 (UCB0CLK - RF)
        (TA2.0 - RF_GDO0) P2.3 |31  44| P2.1 (TA1.2 - RF_GDO2)
		          (TB0.3) P7.5 |32  43| GND
                   (GPIO) P4.7 |33  42| P2.4 (TA2.1)
           (UCA1RXD/SOMI) P4.5 |34  41| P4.6 (GPIO)
   		   (UCA1TXD/SIMO) P4.4 |35  40| P4.0 (UC 1)
            (GPIO - LED2) P1.0 |36  39| P2.0 (TA1.1)
						   GND |37  38| VCC
*/
/*
					  ----+
						47| P1.7 (PUSH1)
                        48| P2.2 (PUSH2)
                        49| P1.0 (LED1)
                        50| P8.1 (LED2)
						51| P8.2 (LED3)
								   
						52| P8.0 (POT_EN)
						53| P6.5 (POT_READ - A5)
					
					TOUCHPADS
						54| P1.1 (TA0.0)
						55| P6.0 (CB0)
						56| P1.2 (TA0.1)
						57| P6.1 (CB1)
						58| 53| P1.3 (TA0.2)
						59| P6.2 (CB2)
						60| P1.4 (TA0.3)
						61| P6.3 (CB3)
						62| P1.5 (TA0.4)
						63| P6.4 (CB4)
*/
/*								   
					ACCEL-UCA0
						63| P3.6 (ACCEL_PWR)
						64| P3.4 (ACCEL_SOMI)
						65| P3.3 (ACCEL_SIMO)
						66| P2.7 (ACCEL_SCLK)
						67| P2.5 (ACCEL_INT)
						68| P3.5 (ACCEL_CS)
								   
					ezFET-UCA1
                        69| P4.5 (UCA1RXD -> ezFET -> Serial)
                        70| P4.4 (UCA1TXD -> ezFET -> Serial)
*/
/*								   
					LCD-UCB1
						71| P5.7 (LCD_RST)
						72| P4.1 (LCD_SIMO)
						73| P4.3 (LCD_SCLK)
						74| P5.6 (LCD_D/C)
						75| P7.4 (LCD_CS)
						76| P7.6 (LCD_BL_EN)
								   
					SD-UCB1
						77| P4.2 (SD_SOMI - DO)
						78| P4.1 (SD_SIMO - DI)
						79| P4.3 (SD_SCLK)
						80| P3.7 (SD_CS)								   
                      ----+
*/

/* Pin names based on the silkscreen */

/* PIN1 = 3.3v */
static const uint8_t P4_5 = 2;
static const uint8_t P4_4 = 3;
static const uint8_t P4_6 = 4;
static const uint8_t P4_7 = 5;
static const uint8_t P5_1 = 6;
/* PIN7 is GND */

static const uint8_t P6_7 = 8;
/*
static const uint8_t P4_4 = 9;
static const uint8_t P4_5 = 10;
*/
static const uint8_t P8_0 = 11;
static const uint8_t P8_2 = 12;
static const uint8_t P8_1 = 13;
static const uint8_t P6_6 = 14;

/* PIN15 = 3.3v */
static const uint8_t P4_2 = 16;
static const uint8_t P4_1 = 17;
static const uint8_t P4_3 = 18;
static const uint8_t P4_0 = 19;
static const uint8_t P3_7 = 20;
/* PIN21 is GND */

static const uint8_t P7_7 = 22;
/*
static const uint8_t P4_2 = 23;
static const uint8_t P4_1 = 24;
*/
static const uint8_t P7_3 = 25;
static const uint8_t P7_2 = 26;
static const uint8_t P7_1 = 27;
static const uint8_t P7_0 = 28;

static const uint8_t P2_6 = 29;
static const uint8_t P3_1 = 30;
static const uint8_t P2_3 = 31;
static const uint8_t P7_5 = 32;
/*
static const uint8_t P4_7 = 33;
static const uint8_t P4_5 = 34;
static const uint8_t P4_4 = 35;
*/
static const uint8_t P1_0 = 36;
/* PIN37 is GND */

/* PIN38 = 3.3v */
static const uint8_t P2_0 = 39;
/*
static const uint8_t P4_0 = 40;
static const uint8_t P4_6 = 41;
*/
static const uint8_t P2_4 = 42;
/* PIN37 is GND */
static const uint8_t P2_1 = 44;
static const uint8_t P3_2 = 45;
static const uint8_t P3_0 = 46;

/* Extra pins not on the header + temp sensor */
static const uint8_t PUSH1 = 47;
static const uint8_t PUSH2 = 48;
static const uint8_t RED_LED = 36;
static const uint8_t GREEN_LED = 50;
static const uint8_t ORANGE_LED = 51;
static const uint8_t TEMPSENSOR = 10;

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
	(uint16_t) &P4MAP0,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /*  dummy */
	NOT_ON_TIMER, /*  1 - 3.3v */
	T0B0,         /*  2 - P5.6 */
	NOT_ON_TIMER, /*  3 - P3.4 */
	NOT_ON_TIMER, /*  4 - P3.3 */
	NOT_ON_TIMER, /*  5 - P1.6 */
	NOT_ON_TIMER, /*  6 - P6.6 */
	NOT_ON_TIMER, /*  7 - P3.2 */
	NOT_ON_TIMER, /*  8 - P2.7 */
	NOT_ON_TIMER, /*  9 - P4.2 */
	NOT_ON_TIMER, /* 10 - P4.1 */
	NOT_ON_TIMER, /* 11 - P8.1 */
	T2A0,         /* 12 - P2.3 */
	NOT_ON_TIMER, /* 13 - P2.6 */
	NOT_ON_TIMER, /* 14 - P3.2 */
	NOT_ON_TIMER, /* 15 - P3.0 */
	NOT_ON_TIMER, /* 16 - RST */
	T0B2,         /* 17 - P7.4 */
	NOT_ON_TIMER, /* 18 - P2.2 */
	T1A1,         /* 19 - P2.0 */
	NOT_ON_TIMER, /* 20 - GND  */
	NOT_ON_TIMER, /* 21 - 5.0v */
	NOT_ON_TIMER, /* 22 - GND */
	NOT_ON_TIMER, /* 23 - P6.0 */
	NOT_ON_TIMER, /* 24 - P6.1 */
	NOT_ON_TIMER, /* 25 - P6.2 */
	NOT_ON_TIMER, /* 26 - P6.3 */
	NOT_ON_TIMER, /* 27 - P6.4 */
	NOT_ON_TIMER, /* 28 - P7.0 */
	T0B6,         /* 29 - P3.6 */
	T0B5,         /* 30 - P3.5 */
	NOT_ON_TIMER, /* 31 - P8.2 */
	NOT_ON_TIMER, /* 32 - P3.7 */
	NOT_ON_TIMER, /* 33 - P4.0 */
	NOT_ON_TIMER, /* 34 - P4.3 */
	T0A1,         /* 35 - P1.2 */
	T0A2,         /* 36 - P1.3 */
	T0A3,         /* 37 - P1.4 */
	T0A4,         /* 38 - P1.5 */
	T2A1,         /* 39 - P2.4 */
	T2A2,         /* 40 - P2.5 */
	NOT_ON_TIMER, /* 41 - P2.1 */
	NOT_ON_TIMER, /* 42 - P1.1 */
	NOT_ON_TIMER, /* 43 - P1.0 */
	T0B1,         /* 44 - P4.7 */
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN, /* dummy */
	NOT_A_PIN, /* 1 */
	P4,        /* 2 */
	P4,        /* 3 */
	P4,        /* 4 */
	P4,        /* 5 */
	P5,        /* 6 */
	NOT_A_PIN,        /* 7 */
	P6,        /* 8 */
	P4,        /* 9 */
	P4,        /* 10 */
	P8,        /* 11 */
	P8,        /* 12 */
	P8,        /* 13 */
	P6,        /* 14 */
	NOT_A_PIN,        /* 15 */
	P4,		   /* 16 */
	P4,        /* 17 */
	P4,        /* 18 */
	P4,        /* 19 */
	P3, /* 20 */
	NOT_A_PIN, /* 21 */
	P7, /* 22 */
	P4,        /* 23 */
	P4,        /* 24 */
	P7,        /* 25 */
	P7,        /* 26 */
	P7,        /* 27 */
	P7,        /* 28 */
	P2,        /* 29 */
	P3,        /* 30 */
	P2,        /* 31 */
	P7,        /* 32 */
	P4,        /* 33 */
	P4,        /* 34 */
	P4,        /* 35 */
	P1,        /* 36 */
	NOT_A_PIN,        /* 37 */
	NOT_A_PIN,        /* 38 */
	P2,        /* 39 */
	P4,        /* 40 */
	P4,        /* 41 */
	P2,        /* 42 */
	NOT_A_PIN,        /* 43 */
	P2,        /* 44 */
	P3,        /* 45 */
	P3,        /* 46 */
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN, /* 0,  pin count starts at 1 */
	NOT_A_PIN, /* 1 */
	BV(5),     /* 2 */
	BV(4),     /* 3 */
	BV(6),     /* 4 */
	BV(7),     /* 5 */
	BV(1),     /* 6 */
	NOT_A_PIN,     /* 7 */
	BV(7),     /* 8 */
	BV(4),     /* 9 */
	BV(5),     /* 10 */
	BV(0),     /* 11 */
	BV(1),     /* 12 */
	BV(1),     /* 13 */
	BV(6),     /* 14 */
	NOT_A_PIN,     /* 15 */
	BV(2), /* 16 */
	BV(1),     /* 17 */
	BV(3),     /* 18 */
	BV(0),     /* 19 */
	BV(7), /* 20 */
	NOT_A_PIN, /* 21 */
	BV(7), /* 22 */
	BV(2),     /* 23 */
	BV(1),     /* 24 */
	BV(3),     /* 25 */
	BV(2),     /* 26 */
	BV(1),     /* 27 */
	BV(0),     /* 28 */
	BV(6),     /* 29 */
	BV(1),     /* 30 */
	BV(3),     /* 31 */
	BV(5),     /* 32 */
	BV(7),     /* 33 */
	BV(5),     /* 34 */
	BV(4),     /* 35 */
	BV(0),     /* 36 */
	NOT_A_PIN,     /* 37 */
	NOT_A_PIN,     /* 38 */
	BV(0),     /* 39 */
	BV(0),     /* 40 */
	BV(6),     /* 41 */
	BV(4),     /* 42 */
	NOT_A_PIN,     /* 43 */
	BV(1),     /* 44 */
	BV(2),     /* 45 */
	BV(0),     /* 46 */
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
