/*
  ************************************************************************
  *   pins_energia.h
  *
  *   Pin definition functions for LaunchPad w/ msp430fr5994
  *      Copyright (c) 2015 Robert Wessels. All right reserved.
  *
  *     Contribution: Stefan Sch
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
static const uint8_t SS0     = 47;  /* P4.0 */
static const uint8_t SCK0    = 49;  /* P2.2 */
static const uint8_t MOSI0   = 48;  /* P1.6 aka SIMO */
static const uint8_t MISO0   = 50;  /* P1.7 aka SOMI */
static const uint8_t SS1     = 8;   /* P6.3 */
static const uint8_t SCK1    = 7;   /* P5.2 */
static const uint8_t MOSI1   = 15;  /* P5.0 aka SIMO */
static const uint8_t MISO1   = 14;  /* P5.1 aka SOMI */
static const uint8_t TWISDA0 = 48;  /* P1.6 UCB0 */
static const uint8_t TWISCL0 = 50;  /* P1.7 UCB0 */
static const uint8_t TWISDA1 = 15;  /* P5.0 UCB1 */
static const uint8_t TWISCL1 = 14;  /* P5.1 UCB1 */
static const uint8_t TWISDA2 = 10;  /* P7.0 UCB1 */
static const uint8_t TWISCL2 = 9;   /* P7.1 UCB1 */
#define TWISDA0_SET_MODE (PORT_SELECTION1 | INPUT_PULLUP)
#define TWISCL0_SET_MODE (PORT_SELECTION1 | INPUT_PULLUP)
#define TWISDA1_SET_MODE (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL1_SET_MODE (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISDA2_SET_MODE (PORT_SELECTION1 | INPUT_PULLUP)
#define TWISCL2_SET_MODE (PORT_SELECTION1 | INPUT_PULLUP)
#define SPISCK0_SET_MODE  (PORT_SELECTION1)
#define SPIMOSI0_SET_MODE (PORT_SELECTION1)
#define SPIMISO0_SET_MODE (PORT_SELECTION1)
#define SPISCK1_SET_MODE  (PORT_SELECTION0)
#define SPIMOSI1_SET_MODE (PORT_SELECTION0)
#define SPIMISO1_SET_MODE (PORT_SELECTION0)
/* Define the default SPI settings */
#define DEFAULT_SPI 1
#define SS     SS1
#define SCK    SCK1  
#define MOSI   MOSI1 
#define MISO   MISO1 
#define SPISCK_SET_MODE  SPISCK1_SET_MODE  
#define SPIMOSI_SET_MODE SPIMOSI1_SET_MODE 
#define SPIMISO_SET_MODE SPIMISO1_SET_MODE 
/* Define the default I2C settings */
#define DEFAULT_I2C 2
#define TWISDA TWISDA2
#define TWISCL TWISCL2
#define TWISDA_SET_MODE  TWISDA2_SET_MODE
#define TWISCL_SET_MODE  TWISCL2_SET_MODE
#endif

#if defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__)
static const uint8_t DEBUG_UARTRXD = 42;  /* Receive  Data (RXD) at P3.5 */
static const uint8_t DEBUG_UARTTXD = 41;  /* Transmit Data (TXD) at P3.4 */
static const uint8_t AUX_UARTRXD = 3;     /* Receive  Data (RXD) at P4.3 */
static const uint8_t AUX_UARTTXD = 4;     /* Transmit Data (TXD) at P4.2 */
#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION1 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION1 | OUTPUT)
#define AUX_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define AUX_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)
#define DEBUG_UART_MODULE_OFFSET 0x00
#define AUX_UART_MODULE_OFFSET 0x60
#define SERIAL1_AVAILABLE 1
#endif


/* Analog pins */

static const uint8_t A0  = 43;
static const uint8_t A1  = 44;
static const uint8_t A2  = 2;
static const uint8_t A3  = 6;
static const uint8_t A4  = 27;
static const uint8_t A5  = 28;
static const uint8_t A6  = 128 + 6; // Not available on BoosterPack header
static const uint8_t A7  = 128 + 7; // Not available on BoosterPack header;
static const uint8_t A8  = 31;
static const uint8_t A9  = 28;
static const uint8_t A10 = 32;
static const uint8_t A11 = 33;
static const uint8_t A12 = 23;
static const uint8_t A13 = 24;
static const uint8_t A14 = 25;
static const uint8_t A15 = 26;

/*
 FR6989 LaunchPad pin mapping - for all functions see docu

                               +--\/--+                                 +--\/--+
                          3.3v |1   21| 5.0v               (TB0.6) P3.7 |40  20| GND
                    (A10) P1.2 |2   22| GND                (TB0.5) P3.6 |39  19| P5.7 (TB0.5)
     (UCA3RXD -> Serial1) P6.1 |3   23| P3.0 (A7)          (TA1.1) P3.5 |38  18| P4.4
     (UCA3TXD -> Serial1) P6.0 |4   24| P3.1 (A6)          (TB0.2) P3.4 |37  17| P5.3 (A12)
                          P6.2 |5   25| P3.2 (A5)          (TB0.3) P7.3 |36  16| RST
                    (A11) P1.3 |6   26| P3.3 (A4)          (TB0.4) P2.6 |35  15| P5.0 (UCB1SIMO) (UCB1SDA)
                          P5.2 |7   27| P1.4 (A8)          (A3)    P2.5 |34  14| P5.1 (UCB1SOMI) (UCB1SCL)
                  (TB0.6) P6.3 |8   28| P1.5 (A9)                  P4.3 |33  13| P8.3 (TB0.4)
             (PM_UCB2SCL) P7.1 |9   29| P4.7 (A13)                 P4.2 |32  12| P8.2 (TB0.3)
             (PM_UCB2SDA) P7.0 |10  30| P8.0 (A14)                 P4.1 |31  11| P8.1 (TA1.2)
                               +------+                                 +------+

                                 ----+
                                   41| P2.0 (UCA0TXD -> ezFET -> Serial)
                                   42| P2.1 (UCA0RXD -> ezFET -> Serial)
                                   43| P1.0 (LED1 - RED)         (TA0.1)
                                   44| P1.1 (LED2 - GREEN)       (A15)
                                   45| P5.6 (PUSH1)
                                   46| P5.5 (PUSH2)
                                 ----+
                                 MMC
                                 ----+
                                   47| P4.0 (SD CS)
                                   48| P1.6 (SD MOSI)
                                   49| P2.2 (SD CLK)        (TA0.1)
                                   50| P1.7 (SD MISO)       (A15)
                                 ----+
*/

/* Pin names based on the silkscreen */

/* PIN1 = 3.3v */
static const uint8_t P1_2 = 2;
static const uint8_t P6_1 = 3;
static const uint8_t P6_0 = 4;
static const uint8_t P6_2 = 5;
static const uint8_t P1_3 = 6;
static const uint8_t P5_2 = 7;
static const uint8_t P6_3 = 8;
static const uint8_t P7_1 = 9;
static const uint8_t P7_0 = 10;

static const uint8_t P8_1 = 11;
static const uint8_t P8_2 = 12;
static const uint8_t P8_3 = 13;
static const uint8_t P5_1 = 14;
static const uint8_t P5_0 = 15;
/* PIN16 is RST */
static const uint8_t P5_3 = 17;
static const uint8_t P4_4 = 18;
static const uint8_t P5_7 = 19;
/* PIN20 is GND */

/* PIN21 is 5.0v */
/* PIN22 is GND */
static const uint8_t P3_0 = 23;
static const uint8_t P3_1 = 24;
static const uint8_t P3_2 = 25;
static const uint8_t P3_3 = 26;
static const uint8_t P1_4 = 27;
static const uint8_t P1_5 = 28;
static const uint8_t P4_7 = 29;
static const uint8_t P8_0 = 30;

static const uint8_t P4_1 = 31;
static const uint8_t P4_2 = 32;
static const uint8_t P4_3 = 33;
static const uint8_t P2_5 = 34;
static const uint8_t P2_6 = 35;
static const uint8_t P7_3 = 36;
static const uint8_t P3_4 = 37;
static const uint8_t P3_5 = 38;
static const uint8_t P3_6 = 39;
static const uint8_t P3_7 = 40;

/* Extra pins not on the header + temp sensor */
static const uint8_t P2_0 = 41;    /* on Pin 6 of J101 (Header to Debugger) */
static const uint8_t P2_1 = 42;    /* on Pin 8 of J101 (Header to Debugger) */
static const uint8_t P1_0 = 43;
static const uint8_t P1_1 = 44;
static const uint8_t P5_6 = 45;
static const uint8_t P5_5 = 46;

static const uint8_t P4_0 = 47;
static const uint8_t P1_6 = 48;
static const uint8_t P2_2 = 49;
static const uint8_t P1_7 = 50;

static const uint8_t PUSH1 = 45;
static const uint8_t PUSH2 = 46;
static const uint8_t RED_LED = 43;
static const uint8_t GREEN_LED = 44;
static const uint8_t TEMPSENSOR = 128 + 30;

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
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) &P9IN,
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) &P10IN,
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
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) &P9OUT,
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) &P10OUT,
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
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) &P9DIR,
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) &P10DIR,
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
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) &P9REN,
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) &P10REN,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
   (uint16_t) &PJREN,
#endif
};

const uint16_t port_to_sel0[] = {  /* put this PxSEL register under the group of PxSEL0 */
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
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) &P9SEL0,
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) &P10SEL0,
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
#ifdef __MSP430_HAS_PORT9_R__
   (uint16_t) &P9SEL1,
#endif
#ifdef __MSP430_HAS_PORT10_R__
   (uint16_t) &P10SEL1,
#endif
#ifdef __MSP430_HAS_PORTJ_R__
   (uint16_t) &PJSEL1,
#endif
};

const uint8_t digital_pin_to_timer[] = {
   NOT_ON_TIMER, /*  dummy */
   NOT_ON_TIMER, /*  1 - 3.3v */
   T1A1,         /*  2 - P1.2 */
   NOT_ON_TIMER, /*  3 - P6.1 */
   NOT_ON_TIMER, /*  4 - P6.0 */
   NOT_ON_TIMER, /*  5 - P6.2 */
   T1A2,         /*  6 - P1.3 */
   NOT_ON_TIMER, /*  7 - P5.2 */
   NOT_ON_TIMER, /*  8 - P6.3 */
   NOT_ON_TIMER, /*  9 - P7.1 */
   NOT_ON_TIMER, /* 10 - P7.0 */
   NOT_ON_TIMER, /* 11 - P8.1 */
   NOT_ON_TIMER, /* 12 - P8.2 */
   NOT_ON_TIMER, /* 13 - P8.3 */
   NOT_ON_TIMER, /* 14 - P5.1 */
   NOT_ON_TIMER, /* 15 - P5.0 */
   NOT_ON_TIMER, /* 16 - RST  */
   NOT_ON_TIMER, /* 17 - P5.3 */
   T0B5,         /* 18 - P4.4 */
   NOT_ON_TIMER, /* 19 - P5.7 */
   NOT_ON_TIMER, /* 20 - GND  */
   NOT_ON_TIMER, /* 21 - 5.0v */
   NOT_ON_TIMER, /* 22 - GND  */
   NOT_ON_TIMER, /* 23 - P3.0 */
   NOT_ON_TIMER, /* 24 - P3.1 */
   NOT_ON_TIMER, /* 25 - P3.2 */
   NOT_ON_TIMER, /* 26 - P3.3 */
   T0B1,         /* 27 - P1.4 */
   T0B2,         /* 28 - P1.5 */
   NOT_ON_TIMER, /* 29 - P4.7 */
   NOT_ON_TIMER, /* 30 - P8.0 */
   NOT_ON_TIMER, /* 31 - P4.1 */
   NOT_ON_TIMER, /* 32 - P4.2 */
   NOT_ON_TIMER, /* 33 - P4.3 */
   NOT_ON_TIMER, /* 34 - P2.5 */
   T0B1,         /* 35 - P2.6 */
   NOT_ON_TIMER, /* 36 - P7.3 */
   T0B3,         /* 37 - P3.4 */
   T0B4,         /* 38 - P3.5 */
   T0B5,         /* 39 - P3.6 */
   T0B6,         /* 40 - P3.7 */
   T0B6,         /* 41 - P2.0 */
   NOT_ON_TIMER, /* 42 - P2.1 */
   T0A1,         /* 43 - P1.0 */
   T0A2,         /* 44 - P1.1 */
   NOT_ON_TIMER, /* 45 - P5.6 */
   NOT_ON_TIMER, /* 46 - P5.5 */
   NOT_ON_TIMER, /* 47 - P4.0 */
   T0B3,         /* 48 - P1.6 */
   T0B2,         /* 49 - P2.2 */
   T0B4,         /* 50 - P1.7 */
};

const uint8_t digital_pin_to_port[] = {
   NOT_A_PIN, /* dummy */
   NOT_A_PIN, /* 1  - 3.3v */
   P1,        /* 2  - P1.2 */
   P6,        /* 3  - P6.1 */
   P6,        /* 4  - P6.0 */
   P6,        /* 5  - P6.2 */
   P1,        /* 6  - P1.3 */
   P5,        /* 7  - P5.2 */
   P6,        /* 8  - P6.3 */
   P7,        /* 9  - P7.1 */
   P7,        /* 10 - P7.0 */
   P8,        /* 11 - P8.1 */
   P8,        /* 12 - P8.2 */
   P8,        /* 13 - P8.3 */
   P5,        /* 14 - P5.1 */
   P5,        /* 15 - P5.0 */
   NOT_A_PIN, /* 16 - RST  */
   P5,        /* 17 - P5.3 */
   P4,        /* 18 - P4.4 */
   P5,        /* 19 - P5.7 */
   NOT_A_PIN, /* 20 - GND  */
   NOT_A_PIN, /* 21 - 5.0v */
   NOT_A_PIN, /* 22 - GND  */
   P3,        /* 23 - P3.0 */
   P3,        /* 24 - P3.1 */
   P3,        /* 25 - P3.2 */
   P3,        /* 26 - P3.3 */
   P1,        /* 27 - P1.4 */
   P1,        /* 28 - P1.5 */
   P4,        /* 29 - P4.7 */
   P8,        /* 30 - P8.0 */
   P4,        /* 31 - P4.1 */
   P4,        /* 32 - P4.2 */
   P4,        /* 33 - P4.3 */
   P2,        /* 34 - P2.5 */
   P2,        /* 35 - P2.6 */
   P7,        /* 36 - P7.3 */
   P3,        /* 37 - P3.4 */
   P3,        /* 38 - P3.5 */
   P3,        /* 39 - P3.6 */
   P3,        /* 40 - P3.7 */
   P2,        /* 41 - P2.0 */
   P2,        /* 42 - P2.1 */
   P1,        /* 43 - P1.0 */
   P1,        /* 44 - P1.1 */
   P5,        /* 45 - P5.6 */
   P5,        /* 46 - P5.5 */
   P4,        /* 47 - P4.0 */
   P1,        /* 48 - P1.6 */
   P2,        /* 49 - P2.2 */
   P1,        /* 50 - P1.7 */
};

const uint8_t digital_pin_to_bit_mask[] = {
   NOT_A_PIN, /* 0,  pin count starts at 1 */
   NOT_A_PIN, /* 1  - 3.3v */
   BV(2),     /* 2  - P1.2 */
   BV(1),     /* 3  - P6.1 */
   BV(0),     /* 4  - P6.0 */
   BV(2),     /* 5  - P6.2 */
   BV(3),     /* 6  - P1.3 */
   BV(2),     /* 7  - P5.2 */
   BV(3),     /* 8  - P6.3 */
   BV(1),     /* 9  - P7.1 */
   BV(0),     /* 10 - P7.0 */
   BV(1),     /* 11 - P8.1 */
   BV(2),     /* 12 - P8.2 */
   BV(3),     /* 13 - P8.3 */
   BV(1),     /* 14 - P5.1 */
   BV(0),     /* 15 - P5.0 */
   NOT_A_PIN, /* 16 - RST  */
   BV(3),     /* 17 - P5.3 */
   BV(4),     /* 18 - P4.4 */
   BV(7),     /* 19 - P5.7 */
   NOT_A_PIN, /* 20 - GND  */
   NOT_A_PIN, /* 21 - 5.0v */
   NOT_A_PIN, /* 22 - GND  */
   BV(0),     /* 23 - P3.0 */
   BV(1),     /* 24 - P3.1 */
   BV(2),     /* 25 - P3.2 */
   BV(3),     /* 26 - P3.3 */
   BV(4),     /* 27 - P1.4 */
   BV(5),     /* 28 - P1.5 */
   BV(7),     /* 29 - P4.7 */
   BV(0),     /* 30 - P8.0 */
   BV(1),     /* 31 - P4.1 */
   BV(2),     /* 32 - P4.2 */
   BV(3),     /* 33 - P4.3 */
   BV(5),     /* 34 - P2.5 */
   BV(6),     /* 35 - P2.6 */
   BV(3),     /* 36 - P7.3 */
   BV(4),     /* 37 - P3.4 */
   BV(5),     /* 38 - P3.5 */
   BV(6),     /* 39 - P3.6 */
   BV(7),     /* 40 - P3.7 */
   BV(0),     /* 41 - P2.0 */
   BV(1),     /* 42 - P2.1 */
   BV(0),     /* 43 - P1.0 */
   BV(1),     /* 44 - P1.1 */
   BV(6),     /* 45 - P5.6 */
   BV(5),     /* 46 - P5.5 */
   BV(0),     /* 47 - P4.0 */
   BV(6),     /* 48 - P1.6 */
   BV(2),     /* 49 - P2.2 */
   BV(7),     /* 50 - P1.7 */
};

const uint32_t digital_pin_to_analog_in[] = {
        NOT_ON_ADC,    /*  dummy   */
        NOT_ON_ADC,    /*  1  - 3.3v */
        2,             /*  2  - P1.2 */
        NOT_ON_ADC,    /*  3  - P6.1 */
        NOT_ON_ADC,    /*  4  - P6.0 */
        NOT_ON_ADC,    /*  5  - P6.2 */
        3,             /*  6  - P1.3 */
        NOT_ON_ADC,    /*  7  - P5.2 */
        NOT_ON_ADC,    /*  8  - P6.3 */
        NOT_ON_ADC,    /*  9  - P7.1 */
        NOT_ON_ADC,    /*  10 - P7.0 */
        NOT_ON_ADC,    /*  11 - P8.1 */
        NOT_ON_ADC,    /*  12 - P8.2 */
        NOT_ON_ADC,    /*  13 - P8.3 */
        NOT_ON_ADC,    /*  14 - P5.1 */
        NOT_ON_ADC,    /*  15 - P5.0 */
        NOT_ON_ADC,    /*  16 - RST  */
        NOT_ON_ADC,    /*  17 - P5.3 */
        NOT_ON_ADC,    /*  18 - P4.4 */
        NOT_ON_ADC,    /*  19 - P5.7 */
        NOT_ON_ADC,    /*  20 - GND  */
        NOT_ON_ADC,    /*  21 - 5.0v */
        NOT_ON_ADC,    /*  22 - GND  */
        12,            /*  23 - P3.0 */
        13,            /*  24 - P3.1 */
        14,            /*  25 - P3.2 */
        15,            /*  26 - P3.3 */
        4,             /*  27 - P1.4 */
        5,             /*  28 - P1.5 */
        NOT_ON_ADC,    /*  29 - P4.7 */
        NOT_ON_ADC,    /*  30 - P8.0 */
        9,             /*  31 - P4.1 */
        10,            /*  32 - P4.2 */
        11,            /*  33 - P4.3 */
        NOT_ON_ADC,    /*  34 - P2.5 */
        NOT_ON_ADC,    /*  35 - P2.6 */
        NOT_ON_ADC,    /*  36 - P7.3 */
        NOT_ON_ADC,    /*  37 - P3.4 */
        NOT_ON_ADC,    /*  38 - P3.5 */
        NOT_ON_ADC,    /*  39 - P3.6 */
        NOT_ON_ADC,    /*  40 - P3.7 */
        NOT_ON_ADC,    /*  41 - P2.0 */
        NOT_ON_ADC,    /*  42 - P2.1 */
        0,             /*  43 - P1.0 */
        1,             /*  44 - P1.1 */
        NOT_ON_ADC,    /*  45 - P5.6 */
        NOT_ON_ADC,    /*  46 - P5.5 */
        8,             /*  47 - P4.0 */
        NOT_ON_ADC,    /*  48 - P1.6 */
        NOT_ON_ADC,    /*  49 - P2.2 */
        NOT_ON_ADC,    /*  50 - P1.7 */
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
