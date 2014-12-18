//////////////////////////////////////////////////////////////////////////////
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
/** @file Wire_lib.h
 *
 *  @brief Wire library header file
 *
 */

#ifndef _WIRE_H_
#define _WIRE_H_

#include <string.h>
#include "csl_i2c.h"
#include "core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Macro to indicate buffer length for Wire */
#define WIRE_BUFFER_LENGTH (64)
/** I2C address */
#define I2C_OWN_ADDR         (0x2F)
/** I2C clock */
#define I2C_SYS_CLK          (150)
/** I2C bus frequency */
#define I2C_BUS_FREQ         (400)
/** Codec address */
#define I2C_CODEC_ADDR		 (0x18)
/** LCD address */
#define I2C_LCD_ADDR		 (0x3C)

/**
 * \brief Wire Class
 *
 *  Contains prototypes for functions in Wire library
 */
class TwoWire
{
    private:
        unsigned int rxBuffer[WIRE_BUFFER_LENGTH];
        unsigned int rxBufferIndex;
        unsigned int rxBufferLength;

        unsigned int txAddress;
        unsigned int txBuffer[WIRE_BUFFER_LENGTH];
        unsigned int txBufferIndex;
        unsigned int txBufferLength;

        unsigned int isInitialized;
        unsigned int transmitting;
    public:
        TwoWire();
        int begin();
        int beginTransmission(unsigned int);
        int endTransmission(void);
		int endTransmission(bool);
        int requestFrom(unsigned int, unsigned int, unsigned int *, unsigned int);
		int requestFrom(unsigned int, unsigned int, unsigned int *, unsigned int, bool);
        unsigned int write(unsigned int);
		unsigned int write(char *);
        unsigned int write(unsigned int *, unsigned int);
        unsigned int available(void);
        int read(void);
};

extern TwoWire Wire;
/**< Wire class instance extern which can used by application programs
 *   to access Wire DSP APIs
 */
#ifdef __cplusplus
}
#endif

#endif //_WIRE_H_
