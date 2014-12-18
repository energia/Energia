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

/** @file DigitalReadWrite_lib.cpp
 *
 *  @brief Digital Read/Write Module implementation
 *
 */

#include "DigitalReadWrite_lib.h"
#include <stdio.h>
#include <string.h>

/**
 *
 *  handleErrors(status)
 *
 *      Handle errors returned by CSL APIs.
 *
 *      int status <- Error Status
 *
 */
void handleErrors(int status)
{

}

/**
 *
 *  pinMode(pinNumber, direction)
 *
 *      Configure the IO Expander pin as either input or output.
 *
 *      unsigned short pinNumber <- IO Expander pin number
 *      unsigned short direction <- 0 : Set IO Expander Pin as Input
 *                                  1 : Set IO Expander Pin as Output
 */
int pinMode(unsigned short pinNumber, unsigned short direction)
{
    CSL_Status status;
    Uint16     expander;
    Uint16     port;
    Uint16     pin;
    Uint16     i2cWriteBuf[2];
    Uint16     configOld;

#ifdef CHIP_C5517
    if ((pinNumber > SW7) || ((direction != INPUT) && (direction != OUTPUT)))
#else
    if ((pinNumber > SW1) || ((direction != INPUT) && (direction != OUTPUT)))
#endif
    {
        return (-1);
    }

    expander = pinNumber < LED0?IO_EXPANDER1:IO_EXPANDER2;
    port     = digitalPinToPort(pinNumber);
    pin      = pinNumber % 8;

    /* Read Old Configuration of all the pins of the desired Port */
    if (0 == port)
    {
        i2cWriteBuf[0] = 0x06; /* Port0 Config Cmd */
    }
    else if (1 == port)
    {
        i2cWriteBuf[0] = 0x07; /* Port1 Config Cmd */
    }

    status = Wire.beginTransmission(expander);
    if (status != 0)
    {
        return (status);
    }

    status = Wire.write((unsigned int *)i2cWriteBuf, 1);
    if (1 != status)
    {
        return (1);
    }

    status = Wire.endTransmission();
    if (status != CSL_SOK)
    {
        return (status);
    }

    status = Wire.requestFrom(expander, 1, (unsigned int *)i2cWriteBuf, 1);
    if (status != CSL_SOK)
    {
        return (status);
    }

    if (1 != Wire.available())
    {
        return (-1);
    }

    configOld = Wire.read();

    /* Configure requested pin as INPUT/OUTPUT */
    if (0 == port)
    {
        i2cWriteBuf[0] = 0x06; /* Port0 Config Cmd */
    }
    else if (1 == port)
    {
        i2cWriteBuf[0] = 0x07; /* Port1 Config Cmd */
    }
    i2cWriteBuf[1] = configOld;

    if (OUTPUT == direction)
    {
        i2cWriteBuf[1] &= (~((Uint16)0x1 << pin)); /* 0-OUT */;
    }
    else
    {
        i2cWriteBuf[1] |= (((Uint16)0x1 << pin)); /* 1-IN */;
    }

    status = Wire.beginTransmission(expander);
    if (status != 0)
    {
        return (status);
    }

    status = Wire.write((unsigned int *)i2cWriteBuf, 2);
    if (2 != status)
    {
        return (1);
    }

    status = Wire.endTransmission();
    if (status != CSL_SOK)
    {
        return (status);
    }

    return (status);
}

/**
 *
 *  digitalWrite(pinNumber, wValue)
 *
 *      Sets an IO Expander Pin to high or low state. The IO Expander Pin must
 *      be configured as output.
 *
 *      unsigned short pinNumber <- IO Expander Pin number
 *      unsigned short wValue    <- 0 : IO Expander Pin output is logic low
 *                                  1 : IO Expander Pin output is logic high
 */
 int digitalWrite(unsigned short pinNumber, unsigned short wValue)
{
    CSL_Status   status;
    Uint16       port;
    Uint16       expander;
    Uint16       pin;
    Uint16       i2cWriteBuf[2];
    Uint16       driveOld;

    expander = pinNumber < LED0?IO_EXPANDER1:IO_EXPANDER2;
    port     = digitalPinToPort(pinNumber);
    pin      = pinNumber % 8;

    /* Read Old values of all the pins of the desired port */
    if (0 == port)
    {
        i2cWriteBuf[0] = 0x02; /* Port0 Output Cmd */
    }
    else if (1 == port)
    {
        i2cWriteBuf[0] = 0x03; /* Port1 Output Cmd */
    }
    
    if( (expander==IO_EXPANDER1 && !digitalWrite_exp1firstCall) ||
        (expander==IO_EXPANDER2 && !digitalWrite_exp2firstCall) )
    {
        if (expander==IO_EXPANDER1)
            digitalWrite_exp1firstCall=0x1;
        else if (expander==IO_EXPANDER2)
            digitalWrite_exp2firstCall=0x1;

        status = Wire.beginTransmission(expander);
        if (status != 0)
        {
            return (status);
        }
        status = Wire.write((unsigned int *)i2cWriteBuf, 1);
        if (1 != status)
        {
            return (1);
        }
        status = Wire.endTransmission();
        if (status != CSL_SOK)
        {
            return (status);
        }

        status = Wire.requestFrom(expander, 1, (unsigned int *)i2cWriteBuf, 1);
        if (status != CSL_SOK)
        {
            return (status);
        }

        if (1 != Wire.available())
        {
            return (-1);
        }

        driveOld = Wire.read();

        if (expander==IO_EXPANDER1)
        {
            expander1_pinstatus=driveOld;
        }
        else if (expander==IO_EXPANDER2)
        {
            expander2_pinstatus=driveOld;
        }
        
        
    }

    /* Write the requested value to the IO Expander Pin */
    if (0 == port)
    {
        i2cWriteBuf[0] = 0x02; /* Port0 Output Cmd */
    }
    else if (1 == port)
    {
        i2cWriteBuf[0] = 0x03; /* Port1 Output Cmd */
    }

    //i2cWriteBuf[1] = driveOld;
    if (expander==IO_EXPANDER1)
    {
        i2cWriteBuf[1]=expander1_pinstatus;
    }
    else if (expander==IO_EXPANDER2)
    {
        i2cWriteBuf[1]=expander2_pinstatus;
    }


    if (wValue)
    {
        i2cWriteBuf[1] |= ((Uint16)0x1 << pin);
    }
    else
    {
        i2cWriteBuf[1] &= (~((Uint16)0x1 << pin));
    }

    status = Wire.beginTransmission(expander);
    if (status != 0)
    {
        return (status);
    }
    status = Wire.write((unsigned int *)i2cWriteBuf, 2);
    if (2 != status)
    {
        return (1);
    }
    status = Wire.endTransmission();

    if (expander==IO_EXPANDER1)
    {
        expander1_pinstatus=i2cWriteBuf[1];
    }
    else if (expander==IO_EXPANDER2)
    {
        expander2_pinstatus=i2cWriteBuf[1];
    }

    return (status);
}


/**
 *
 *  digitalWritePort(unsigned char portNumber, unsigned char bValue)
 *
 *      Sets all 8 pins on an IO Expander port to high or low state. The IO Expander Pins affected must
 *      be configured as output to show changes.
 *
 *      unsigned char portNumber <- IO Expander Port number
 *      unsigned char bValue     <- byte containing bit flags for each of 8 pins on the port.
 *
 */
int digitalWrite_port(unsigned char portNumber, unsigned char bValue)
{

    CSL_Status   status;
    Uint16       port;
    Uint16       expander;
    Uint16       pin;
    Uint16       i2cWriteBuf[2];
    Uint16       driveOld;
    Uint16       wValue=0x0;

    if(portNumber>3)
        return (-1);
    expander = portNumber < 2?IO_EXPANDER1:IO_EXPANDER2;

    /* Read Old values of all the pins of the desired port */
    if (0 == portNumber%2)
    {
        i2cWriteBuf[0] = 0x02; /* Port0 Output Cmd */
    }
    else if (1 == portNumber%2)
    {
        i2cWriteBuf[0] = 0x03; /* Port1 Output Cmd */
    }
    
    if( (expander==IO_EXPANDER1 && !digitalWrite_exp1firstCall) ||
        (expander==IO_EXPANDER2 && !digitalWrite_exp2firstCall) )
    {
        if (expander==IO_EXPANDER1)
            digitalWrite_exp1firstCall=0x1;
        else if (expander==IO_EXPANDER2)
            digitalWrite_exp2firstCall=0x1;

        status = Wire.beginTransmission(expander);
        if (status != 0)
        {
            return (status);
        }
        status = Wire.write((unsigned int *)i2cWriteBuf, 1);
        if (1 != status)
        {
            return (1);
        }
        status = Wire.endTransmission();
        if (status != CSL_SOK)
        {
            return (status);
        }

        status = Wire.requestFrom(expander, 1, (unsigned int *)i2cWriteBuf, 1);
        if (status != CSL_SOK)
        {
            return (status);
        }

        if (1 != Wire.available())
        {
            return (-1);
        }

        driveOld = Wire.read();

        if (expander==IO_EXPANDER1)
        {
            expander1_pinstatus=driveOld;
        }
        else if (expander==IO_EXPANDER2)
        {
            expander2_pinstatus=driveOld;
        }
        
        
    }

    /* Write the requested value to the IO Expander Pin */
    if (0 == portNumber%2)
    {
        i2cWriteBuf[0] = 0x02; /* Port0 Output Cmd */
    }
    else if (1 == portNumber%2)
    {
        i2cWriteBuf[0] = 0x03; /* Port1 Output Cmd */
    }

    //i2cWriteBuf[1] = driveOld;
    if (expander==IO_EXPANDER1)
    {
        i2cWriteBuf[1]=expander1_pinstatus;
    }
    else if (expander==IO_EXPANDER2)
    {
        i2cWriteBuf[1]=expander2_pinstatus;
    }


        if(portNumber%2==0)
        {
            i2cWriteBuf[1] &= 0xFF00;
            i2cWriteBuf[1] |= bValue;
        }
        else if(portNumber%2==1)
        {
            i2cWriteBuf[1] &= 0x00FF;
            i2cWriteBuf[1] |= ((wValue | bValue) << 8);
        }

    status = Wire.beginTransmission(expander);
    if (status != 0)
    {
        return (status);
    }
    status = Wire.write((unsigned int *)i2cWriteBuf, 2);
    if (2 != status)
    {
        return (1);
    }
    status = Wire.endTransmission();

    if (expander==IO_EXPANDER1)
    {
        expander1_pinstatus=i2cWriteBuf[1];
    }
    else if (expander==IO_EXPANDER2)
    {
        expander2_pinstatus=i2cWriteBuf[1];
    }

    return (status);
}

/**
 *
 *  digitalRead(pinNumber)
 *
 *      Returns 0 if the IO Expander Pin is in the low state and 1 if it is
 *      in the high state.
 *
 *      unsigned short pinNumber   <- IO Expander Pin number
 *
 *      Returns: unsigned int readVal -> 0 : Input to the IO Expander Pin is
 *                                           logic low
 *                                       1 : Input to the IO Expander Pin is
 *                                           logic high
 *                                       2 : If the IO Expander read is not
 *                                           successful
 */
unsigned int digitalRead(int pinNumber)
{
    CSL_Status status;
    Uint16     port;
    Uint16     expander;
    Uint16     pin;
    Uint16     rValue;
    Uint16     i2cWriteBuf[2];

    expander = pinNumber < LED0?IO_EXPANDER1:IO_EXPANDER2;
    port     = digitalPinToPort(pinNumber);
    pin      = pinNumber % 8;

    /* Read the value of the requested IO Expander Pin */
    if (0 == port)
    {
        i2cWriteBuf[0] = 0x00; /* Port0 Input Cmd */
    }
    else if (1 == port)
    {
        i2cWriteBuf[0] = 0x01; /* Port1 Input Cmd */
    }

    status = Wire.requestFrom(expander, 1, (unsigned int *)i2cWriteBuf, 1);

    if (status != CSL_SOK)
    {
        Wire.endTransmission();
        Wire.begin();
        return (2);
    }

    if (1 != Wire.available())
    {
		return (2);
	}

    rValue = Wire.read();
    rValue = (rValue >> pin) & 0x1;

    return (rValue);
}