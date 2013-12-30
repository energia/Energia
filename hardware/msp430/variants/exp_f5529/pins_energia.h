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
                          3.3v |1   12| P6.6 (CB6, A6)
           (UCA1RXD/SOMI) P4.5 |2   11| P8.1 (GPIO - LED2)
           (UCA1TXD/SIMO) P4.4 |3   10| P8.2 (GPIO - LED3)
		      (GPIO - RF) P4.6 |4    9| P8.0 (GPIO - POT)
              (GPIO - RF) P4.7 |5    -| P4.5 (UCA1RXD/SOMI)
                     (A9) P5.1 |6    -| P4.4 (UCA1TXD/SIMO)
                           GND |7    8| P6.7 (CB7, A7)
*/
/*						   		
								J5
                                +--\/--+
                           3.3v |13   24| P7.0 (CB8, A12)
       (UCB1SOMI/SCL - SD) P4.2 |14   23| P7.1 (CB9, A13)
   (UCB1SIMO/SDA - LCD/SD) P4.1 |15   22| P7.2 (CB10, A14)
(UCB1CLK/UCA1STE - LCD/SD) P4.3 |16   21| P7.3 (CB11, A15)
    (UCB1STE/UCA1CLK - RF) P4.0 |17    -| P4.1 (UCB1SIM0/UCB1SDA - LCD/SD)
    (TB0OUTH, SVMOUT - SD) P3.7 |18    -| P4.2 (UCB1SOMI/UCB1SCL - SD)
                            GND |19   20| P7.7 (TB0CLK)
*/
/*						
								 J12
                               +--\/--+
           (UCB0STE - RF) P2.6 |25  37| P3.0 (UCB0SIMO - RF)
          (UCB0SOMI - RF) P3.1 |26  36| P3.2 (UCB0CLK - RF)
        (TA2.0 - RF_GDO0) P2.3 |27  35| P2.1 (TA1.2 - RF_GDO2)
		          (TB0.3) P7.5 |28  34| GND
                   (GPIO) P4.7 |-   33| P2.4 (TA2.1)
           (UCA1RXD/SOMI) P4.5 |-    -| P4.6 (GPIO)
   		   (UCA1TXD/SIMO) P4.4 |-    -| P4.0 (UC 1)
            (GPIO - LED2) P1.0 |29  32| P2.0 (TA1.1)
						   GND |30  31| VCC
*/
/*
					  ----+
						38| P1.7 (PUSH1)
                        39| P2.2 (PUSH2)
						
                       -29| P1.0 (LED1)
                       -11| P8.1 (LED2)
					   -10| P8.2 (LED3)
					    -9| P8.0 (POT_EN)
						
						40| P6.5 (POT_READ - A5)
					
					TOUCHPADS
						41| P1.1 (TA0.0)
						46| P6.0 (CB0)
						42| P1.2 (TA0.1)
						47| P6.1 (CB1)
						43| 53| P1.3 (TA0.2)
						48| P6.2 (CB2)
						44| P1.4 (TA0.3)
						49| P6.3 (CB3)
						45| P1.5 (TA0.4)
						50| P6.4 (CB4)
*/
/*								   
					ACCEL-UCA0
						51| P3.6 (ACCEL_PWR)
						52| P3.4 (ACCEL_SOMI)
						53| P3.3 (ACCEL_SIMO)
						54| P2.7 (ACCEL_SCLK)
						55| P2.5 (ACCEL_INT)
						56| P3.5 (ACCEL_CS)
								   
					ezFET-UCA1
                        -2| P4.5 (UCA1RXD -> ezFET -> Serial)
                        -3| P4.4 (UCA1TXD -> ezFET -> Serial)
*/
/*								   
					LCD-UCB1
						57| P5.7 (LCD_RST)
					   -15| P4.1 (LCD_SIMO)
					   -16| P4.3 (LCD_SCLK)
						58| P5.6 (LCD_D/C)
						59| P7.4 (LCD_CS)
						60| P7.6 (LCD_BL_EN)
								   
					SD-UCB1
					   -14| P4.2 (SD_SOMI - DO)
					   -15| P4.1 (SD_SIMO - DI)
					   -16| P4.3 (SD_SCLK)
					   -18| P3.7 (SD_CS)								   
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
/*-*/
/*-*/
static const uint8_t P8_0 = 9;
static const uint8_t P8_2 = 10;
static const uint8_t P8_1 = 11;
static const uint8_t P6_6 = 12;

/* PIN13 = 3.3v */
static const uint8_t P4_2 = 14;
static const uint8_t P4_1 = 15;
static const uint8_t P4_3 = 16;
static const uint8_t P4_0 = 17;
static const uint8_t P3_7 = 18;
/* PIN19 is GND */

static const uint8_t P7_7 = 20;
/*-*/
/*-*/
static const uint8_t P7_3 = 21;
static const uint8_t P7_2 = 22;
static const uint8_t P7_1 = 23;
static const uint8_t P7_0 = 24;

static const uint8_t P2_6 = 25;
static const uint8_t P3_1 = 26;
static const uint8_t P2_3 = 27;
static const uint8_t P7_5 = 28;
/*-*/
/*-*/
/*-*/
static const uint8_t P1_0 = 29;
/* PIN30 is GND */

/* PIN31 = 3.3v */
static const uint8_t P2_0 = 32;
/*-*/
/*-*/
static const uint8_t P2_4 = 33;
/* PIN34 is GND */
static const uint8_t P2_1 = 35;
static const uint8_t P3_2 = 36;
static const uint8_t P3_0 = 37;

/* Extra pins not on the header + temp sensor */
static const uint8_t PUSH1 = 38;
static const uint8_t PUSH2 = 39;
static const uint8_t RED_LED = 29;
static const uint8_t GREEN_LED = 10;
static const uint8_t ORANGE_LED = 11;
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
	T2A1        /* 39 - P2.4 */
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
	P8,        /* 9 */
	P8,        /* 10 */
	P8,        /* 11 */
	P6,        /* 12 */
	NOT_A_PIN,        /* 13 */
	P4,        /* 14 */
	P4,        /* 15 */
	P4,		   /* 16 */
	P4,        /* 17 */
	P3,        /* 18 */
	NOT_A_PIN,        /* 19 */
	P7, /* 20 */
	P7, /* 21 */
	P7, /* 22 */
	P7,        /* 23 */
	P7,        /* 24 */
	P2,        /* 25 */
	P3,        /* 26 */
	P2,        /* 27 */
	P7,        /* 28 */
	P1,        /* 29 */
	NOT_A_PIN,        /* 30 */
	NOT_A_PIN,        /* 31 */
	P2,        /* 32 */
	P2,        /* 33 */
	NOT_A_PIN,        /* 34 */
	P2,        /* 35 */
	P3,        /* 36 */
	P3,        /* 37 */
	P1,        /* 38 */
	P2        /* 39 */
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
	BV(0),     /* 9 */
	BV(2),     /* 10 */
	BV(1),     /* 11 */
	BV(6),     /* 12 */
	NOT_A_PIN,     /* 13 */
	BV(2),     /* 14 */
	BV(1),     /* 15 */
	BV(3), /* 16 */
	BV(0),     /* 17 */
	BV(7),     /* 18 */
	NOT_A_PIN,     /* 19 */
	BV(7), /* 20 */
	BV(1), /* 21 */
	BV(2), /* 22 */
	BV(1),     /* 23 */
	BV(0),     /* 24 */
	BV(6),     /* 25 */
	BV(1),     /* 26 */
	BV(3),     /* 27 */
	BV(5),     /* 28 */
	BV(0),     /* 29 */
	NOT_A_PIN,     /* 30 */
	NOT_A_PIN,     /* 31 */
	BV(0),     /* 32 */
	BV(4),     /* 33 */
	NOT_A_PIN,     /* 34 */
	BV(1),     /* 35 */
	BV(2),     /* 36 */
	BV(0),     /* 37 */
	BV(7),     /* 38 */
	BV(2)     /* 39 */
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
