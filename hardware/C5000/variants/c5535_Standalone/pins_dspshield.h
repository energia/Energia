//TI DSP Shield DigitalReadWrite Library.
//////////////////////////////////////////////////////////////////////////////
// * File name: pins_dspshield.h
// *
// * Description:  Header file for DSP shield pin names.
// *
// * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
// *
// *  Redistribution and use in source and binary forms, with or without
// *  modification, are permitted provided that the following conditions
// *  are met:
// *
// *    Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// *
// *    Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the
// *    distribution.
// *
// *    Neither the name of Texas Instruments Incorporated nor the names of
// *    its contributors may be used to endorse or promote products derived
// *    from this software without specific prior written permission.
// *
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
//////////////////////////////////////////////////////////////////////////////

#ifndef _PINS_DSPSHIELD_H_
#define _PINS_DSPSHIELD_H_

#define A0 (0)
#define A1 (1)
#define A2 (2)
#define A3 (3)

#define INPUT                   (0)
#define OUTPUT                  (1)
#define LOW                     (0)
#define HIGH                    (1)

#define IOEXP_P0           (0)
#define IOEXP_P1           (1)

#define IO_EXPANDER1       (0x20)
#define IO_EXPANDER2       (0x21)

#define IO0                (0)
#define IO1                (1)
#define IO2                (2)
#define IO3                (3)
#define IO4                (4)
#define IO5                (5)
#define IO6                (6)
#define IO7                (7)
#define IO8                (8)
#define IO9                (9)
#define ARD_UART_CNTRL0    (10)
#define ARD_UART_CNTRL1    (11)
#define ARD_UART_CNTRL2    (12)
#define ARD_UART_CNTRL3    (13)
#define ARD_RST_CNTRL0     (14)
#define ARD_RST_CNTRL1     (15)
#define LED0               (16)
#define LED1               (17)
#define ARD_I2C_EN         (18)
#define SPI_RX_SEL         (19)
#define I2S2_MUX_SEL       (20)
#define UART_MUX_SEL       (21)
#define LED2               (22)
#define ARD_SPI_EN         (23)
#define E3                 (24)
#define E1                 (25)
#define E2                 (26)
#define E0                 (27)
#define SW4                (28)
#define SW3                (29)
#define SW2                (30)
#define SW1                (31)

static const short digital_pin_to_port[32] = {
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,

    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,

    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,
    IOEXP_P0,

    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1,
    IOEXP_P1
};

#define digitalPinToPort(P) (*(digital_pin_to_port + (P)))

#endif  /* _PINS_DSPSHIELD_H_ */
