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

/** @file Wire_lib.cpp
 *
 *  @brief Wire/I2C implementation
 *
 */

#include "Wire_lib.h"
#define CSL_TIMEOUT 0x01FF//CSL_I2C_MAX_TIMEOUT//0x07FF //0x01FF
TwoWire Wire;

/**
 * TwoWire Class Constructor
 */
TwoWire::TwoWire()
{
    rxBufferIndex  = 0;
    rxBufferLength = 0;

    txAddress      = 0;
    txBufferIndex  = 0;
    txBufferLength = 0;

	isInitialized  = 0;
    transmitting   = 0;
}

/** ===========================================================================
 *   @n@b begin()
 *
 *   @b Description
 *   @n Function initializes Wire module.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int TwoWire::begin(void)
{
    CSL_Status   status;
    CSL_I2cSetup i2cSetup;
    Uint32       sysClk;

    sysClk = getCpuClock(); /* getCpuClock() will return CPU clock in kHz */
    sysClk = sysClk / 1000;

    rxBufferIndex  = 0;
    rxBufferLength = 0;
    txBufferIndex  = 0;
    txBufferLength = 0;

	status = I2C_init(CSL_I2C0);
	if(status == CSL_SOK)
	{
		i2cSetup.addrMode    = CSL_I2C_ADDR_7BIT;
		i2cSetup.bitCount    = CSL_I2C_BC_8BITS;
		i2cSetup.loopBack    = CSL_I2C_LOOPBACK_DISABLE;
		i2cSetup.freeMode    = CSL_I2C_FREEMODE_DISABLE;
		i2cSetup.repeatMode  = CSL_I2C_REPEATMODE_DISABLE;
		i2cSetup.ownAddr     = I2C_OWN_ADDR;
		i2cSetup.sysInputClk = sysClk;
		i2cSetup.i2cBusFreq  = I2C_BUS_FREQ;

		status = I2C_setup(&i2cSetup);
		if(status == CSL_SOK)
		{
		    isInitialized = 1;
		}
		else
		{
		    isInitialized = 0;
		}
	}

	return ((int)status);
}

/** ===========================================================================
 *   @n@b requestFrom()
 *
 *   @b Description
 *   @n Used by the master to request bytes from a slave device.
 *      The bytes may then be retrieved with available() and read() functions.
 *
 *   @b Arguments
 *   @verbatim
 *      unsigned int address    <- Slave device address
 *      unsigned int quantity   <- Number of bytes to read
 *      unsigned int *subAddr   <- Pointer to sub address
 *      unsigned int subAddrLen <- Sub address length
 *
     @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int TwoWire::requestFrom(unsigned int address,
                         unsigned int quantity,
						 unsigned int *subAddr,
						 unsigned int subAddrLen)
{
    CSL_Status   status;
	unsigned int startStop;
	if(isInitialized != 1)
	{
	    status = CSL_ESYS_FAIL;
	}
	else
	{
	    if(quantity > WIRE_BUFFER_LENGTH)
	    {
	        quantity = WIRE_BUFFER_LENGTH;
	    }

		startStop = ((CSL_I2C_START) | (CSL_I2C_STOP));
		//asm(" BIT(ST1, #13) = #1");
		status = I2C_read((Uint16 *)rxBuffer, quantity, address,
		                  (Uint16 *)subAddr, subAddrLen,TRUE, startStop,
		                  CSL_TIMEOUT, FALSE); //CSL_I2C_MAX_TIMEOUT 
							//changed bus busy flag FALSE -> TRUE
		//asm(" BIT(ST1, #13) = #0");
	    if(status == CSL_SOK)
		{
	        rxBufferIndex = 0;
	        rxBufferLength = quantity;
		}

		//delayMicroseconds(250);
	}
	return ((int)status);
}

/** ===========================================================================
 *   @n@b requestFrom()
 *
 *   @b Description
 *   @n Used by the master to request bytes from a slave device.
 *      The bytes may then be retrieved with available() and read() functions.
 *      requestFrom() accepts a boolean argument changing its behavior for
 *      compatibility with certain I2C devices.
 *
 *   @b Arguments
 *   @verbatim
 *      unsigned int address    <- Slave device address
 *      unsigned int quantity   <- Number of bytes to read
 *      unsigned int *subAddr   <- Pointer to sub address
 *      unsigned int subAddrLen <- Sub address length
 *      Bool stop         <- If true, requestFrom() sends a stop message after
 *                           the request, releasing the I2C bus.
 *                           If false, requestFrom() sends a restart message
 *                           after the request. The bus will not be released,
 *                           which prevents another master device from
 *                           requesting between messages. This allows one
 *                           master device to send multiple requests while
 *                           in control.
 *
     @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int TwoWire::requestFrom(unsigned int address,
                         unsigned int quantity,
						 unsigned int *subAddr,
						 unsigned int subAddrLen,
						 bool         stop)
{
    CSL_Status   status;
	unsigned int startStop;
	if(isInitialized != 1)
	{
	    status = CSL_ESYS_FAIL;
	}
	else
	{
	    if(stop == TRUE)
		{
		    startStop = ((CSL_I2C_START) | (CSL_I2C_STOP));
		}
		else
		{
		    startStop = CSL_I2C_START;
		}

	    if(quantity > WIRE_BUFFER_LENGTH)
	    {
	        quantity = WIRE_BUFFER_LENGTH;
	    }

		status = I2C_read((Uint16 *)rxBuffer, quantity, address,
		                  (Uint16 *)subAddr, subAddrLen,TRUE, startStop,
		                  CSL_TIMEOUT, FALSE); //CSL_I2C_MAX_TIMEOUT
	    if(status == CSL_SOK)
		{
	        rxBufferIndex = 0;
	        rxBufferLength = quantity;
		}

		//delayMicroseconds(250);
	}

	return ((int)status);
}

/** ===========================================================================
 *   @n@b beginTransmission()
 *
 *   @b Description
 *   @n Begin a transmission to the I2C slave device with the given address.
 *      Subsequently, queue bytes for transmission with the write() function
 *      and transmit them by calling endTransmission().
 *
 *   @b Arguments
 *   @verbatim
 *      unsigned int address    <- Slave device address
 *
     @endverbatim
 *
 *   <b> Return Value </b> int
 *   @li  0:Success
 *   @li  Error status
 *
 *  ===========================================================================
 */
int TwoWire::beginTransmission(unsigned int address)
{
    CSL_Status status;

	if(isInitialized != 1)
	{
	    status = CSL_ESYS_FAIL;
	}
	else
	{
	    /* indicate that we are transmitting */
	    transmitting = 1;
	    /* set address of targeted slave */
	    txAddress = address;
	    /* reset tx buffer iterator vars */
	    txBufferIndex = 0;
	    txBufferLength = 0;

		status = CSL_SOK;
	}

	return ((int)status);
}

/** ===========================================================================
 *   @n@b endTransmission()
 *
 *   @b Description
 *   @n Ends a transmission to a slave device that was begun by
 *      beginTransmission() and transmits the bytes that were queued
 *      by write().
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>int
 *   @li  0:success
 *   @li  1:data too long to fit in transmit buffer
 *   @li  2:data too long to fit in transmit buffer
 *   @li  Appropriate CSL error code for NACK with transmit/receive
 *
 *  ===========================================================================
 */
int TwoWire::endTransmission(void)
{
    CSL_Status   status;
    unsigned int startStop;

	if(txBufferLength > WIRE_BUFFER_LENGTH)
	{
	    status = 1;
	}
	else if(isInitialized != 1)
	{
	    status = 2;
	}
	else
	{
	    startStop = ((CSL_I2C_START) | (CSL_I2C_STOP));

		status = I2C_write((Uint16 *)txBuffer, txBufferLength, txAddress,
		                   TRUE, startStop, CSL_TIMEOUT); //CSL_I2C_MAX_TIMEOUT
		if(status == CSL_SOK)
		{
		    /* reset tx buffer iterator vars */
		    txBufferIndex = 0;
		    txBufferLength = 0;
		    /* indicate that we are done transmitting */
		    transmitting = 0;
	    }

		/* Small delay is required to execute consecutive write operations successfully */
		delayMicroseconds(80);
	}

	return ((int)status);
}

/** ===========================================================================
 *   @n@b endTransmission()
 *
 *   @b Description
 *   @n Ends a transmission to a slave device that was begun by
 *      beginTransmission() and transmits the bytes that were queued
 *      by write(). endTransmission() accepts a boolean argument changing its
 *      behavior for compatibility with certain I2C devices.
 *
 *   @b Arguments
 *   @verbatim
 *      Bool stop  <- If true, endTransmission() sends a stop message after
 *                    transmission, releasing the I2C bus.
 *
 *                    If false, endTransmission() sends a restart message
 *                    after transmission. The bus will not be released, which
 *                    prevents another master device from transmitting between
 *                    messages. This allows one master device to send
 *                    multiple transmissions while in control.
     @endverbatim
 *
 *   <b> Return Value </b>int
 *   @li  0:success
 *   @li  1:data too long to fit in transmit buffer
 *   @li  2:data too long to fit in transmit buffer
 *   @li  Appropriate CSL error code for NACK with transmit/receive
 *
 *  ===========================================================================
 */
int TwoWire::endTransmission(bool stop)
{
    CSL_Status   status;
    unsigned int startStop;

	if(txBufferLength > WIRE_BUFFER_LENGTH)
	{
	    status = 1;
	}
	else if(isInitialized != 1)
	{
	    status = 2;
	}
	else
	{
	    if(stop == TRUE)
		{
		    startStop = ((CSL_I2C_START) | (CSL_I2C_STOP));
		}
		else
		{
		    startStop = CSL_I2C_START;
		}

		status = I2C_write((Uint16 *)txBuffer, txBufferLength, txAddress,
		                   TRUE, startStop, CSL_TIMEOUT); //CSL_I2C_MAX_TIMEOUT
		if(status == CSL_SOK)
		{
		    /* reset tx buffer iterator vars */
		    txBufferIndex = 0;
		    txBufferLength = 0;
		    /* indicate that we are done transmitting */
		    transmitting = 0;
	    }

		/* Small delay is required to execute consecutive write operations successfully */
		delayMicroseconds(80);
	}

	return ((int)status);
}

/** ===========================================================================
 *   @n@b write()
 *
 *   @b Description
 *   @n Queues bytes for transmission from a master to slave device
 *      (in-between calls to beginTransmission() and endTransmission()).
 *
 *   @b Arguments
 *   @verbatim
 *      unsigned int data    <- Data to be written
     @endverbatim
 *
 *   <b> Return Value </b>unsigned int
 *   @li 0 if any error
 *   @li Number of bytes written
 *
 *  ===========================================================================
 */
unsigned int TwoWire::write(unsigned int data)
{
    unsigned int bytesWritten;

    if(isInitialized != 1)
	{
	    bytesWritten = 0;
	}
	else
	{
	    if(transmitting)
	    {
	        if(txBufferLength > WIRE_BUFFER_LENGTH)
	        {
	            return 0;
	        }
		    else
		    {
	            txBuffer[txBufferIndex] = data;
	            ++txBufferIndex;
	            txBufferLength = txBufferIndex;

				bytesWritten = 1;
		    }
	    }
	    else
	    {
	        /* Not supported in master mode */
	    }
	}

    return (bytesWritten);
}

/** ===========================================================================
 *   @n@b write()
 *
 *   @b Description
 *   @n Queues bytes for transmission from a master to slave device
 *      (in-between calls to beginTransmission() and endTransmission()).
 *
 *   @b Arguments
 *   @verbatim
 *      char *string      <- String to tbe written
     @endverbatim
 *
 *   <b> Return Value </b>unsigned int
 *   @li 0 if any error
 *   @li Number of bytes written
 *
 *  ===========================================================================
 */
unsigned int TwoWire::write(char *string)
{
    unsigned int loopIndex;
	unsigned int bytesWritten;
	unsigned int length;

	bytesWritten = 0;

    if((isInitialized == 1) && (string != NULL))
	{
	    length = strlen(string);

		if(transmitting)
		{
		    for(loopIndex = 0; loopIndex < length; ++loopIndex)
		    {
		        bytesWritten += write((unsigned int)string[loopIndex]);
			}
		}
		else
		{
		    /* Not supported in master mode */
		}
	}

	return (bytesWritten);
}

/** ===========================================================================
 *   @n@b write()
 *
 *   @b Description
 *   @n Queues bytes for transmission from a master to slave device
 *      (in-between calls to beginTransmission() and endTransmission()).
 *
 *   @b Arguments
 *   @verbatim
 *      unsigned int *data      <- Poiter to array of data to be written
 *      unsigned int quantity   <- Number of bytes to be written
     @endverbatim
 *
 *   <b> Return Value </b>unsigned int
 *   @li 0 if any error
 *   @li Number of bytes written
 *
 *  ===========================================================================
 */
unsigned int TwoWire::write(unsigned int *data, unsigned int quantity)
{
    unsigned int loopIndex;
	unsigned int bytesWritten;

	bytesWritten = 0;

    if((isInitialized == 1) && (quantity != 0) && (data != NULL))
	{
		if(transmitting)
		{
		    for(loopIndex = 0; loopIndex < quantity; ++loopIndex)
		    {
		        bytesWritten += write(data[loopIndex]);
			}
		}
		else
		{
		    /* Not supported in master mode */
		}
	}

	return (bytesWritten);
}

/** ===========================================================================
 *   @n@b available()
 *
 *   @b Description
 *   @n Returns the number of bytes available for retrieval with receive().
 *      This should be called on a master device after a call to requestFrom().
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>unsigned int
 *   @li Number of bytes available for reading
 *
 *  ===========================================================================
 */
unsigned int TwoWire::available(void)
{
    return (rxBufferLength - rxBufferIndex);
}

/** ===========================================================================
 *   @n@b read()
 *
 *   @b Description
 *   @n Reads a byte that was transmitted from a slave device to a master
 *      after a call to requestFrom().
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>int
 *   @li -1 if buffer is empty or if module is uninitialized
 *   @li Otherwise value which is read
 *
 *  ===========================================================================
 */
int TwoWire::read(void)
{
    int value = -1;

    if(isInitialized == 1)
	{
	    if(rxBufferIndex < rxBufferLength)
	    {
	        value = rxBuffer[rxBufferIndex];
	        ++rxBufferIndex;
	    }
	}

    return (value);
}
