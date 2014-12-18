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

/** @file Serial_lib.cpp
 *
 *  @brief Serial implementation
 *
 */

#include <Serial_lib.h>
#include <core.h>

/** Defining the static variables */
int SerialClass::isInitialized = 0;
CSL_UartObj SerialClass::uartObj;
long SerialClass::timeOut = 0;

/** Defining a global Serial Class Object which can be used by the User
    Application */
SerialClass Serial;

/**
 *
 *  SerialClass Serial
 *
 *  Serial Class Constructor.
 *
 */
SerialClass::SerialClass()
{
}

/**
 *
 *  uartIoExpander()
 *
 *  Configure IO Expander for UART
 */
static int uartIoExpander (void)
{
    int retStatus;

#ifdef CHIP_C5517
    /* Set ARD_UART_CNTRL1 to 1 */
    retStatus = ioExpander_Setup();
    if (0 == retStatus)
    {
        retStatus = ioExpander_Write(1, 4, 1);
        if (0 == retStatus)
        {
            retStatus = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_1);
        }
    }
#else

#ifdef C5535_EZDSP
    retStatus = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_1);
#else
    retStatus = ioExpander_Setup();
    if (0 == retStatus)
    {
#ifdef C55X_STANDALONE_MODE
        retStatus = ioExpander_Write(1, 2, 1); /* For Standalone Mode */
        if (0 == retStatus)
        {
            retStatus = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_1);
        }
#else
        retStatus = ioExpander_Write(1, 2, 0); /* For Stacked Mode */
        retStatus |= ioExpander_Write(1, 3, 1);
        retStatus |= ioExpander_Write(1, 4, 1);
        retStatus |= ioExpander_Write(1, 5, 1);
        if (0 == retStatus)
        {
            retStatus = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_1);
        }
#endif
    }
#endif

#endif

    return (retStatus);
}

/**
 *
 *  begin(baudRate)
 *
 *  Configure UART with the given baud rate
 *      long baudRate    <- Baud Rate to be set
 */
void SerialClass::begin(long baudRate)
{
    Baudrate_Config baudConfig;

    if (0 == this->isInitialized) /* If the instance is not initialized */
    {
        baudConfig.data     = 8;
        baudConfig.parity   = 0;
        baudConfig.stopBits = 0;

        this->begin (baudRate, &baudConfig);
    }
}

/**
 *  checkBaudRate(baudRate)
 *
 *  API to check whether the baud rate requested by the user is supported or not
 *      long baudRate    <- Baud Rate to be checked
 */
static Bool checkBaudRate(long baudRate)
{
    Bool retValue;

    retValue = FALSE;

    switch (baudRate)
    {
        case 300:
        case 1200:
        case 2400:
        case 4800:
        case 9600:
        case 19200:
        case 38400:
        case 57600:
        case 115200:
            retValue = TRUE;
            break;
    }

    return (retValue);
}

/**
 *  checkConfigParams(baudConfig)
 *
 *  API to check whether the serial port configurations requested by the user
 *  are supported or not
 *      Baudrate_Config baudConfig  <- Config Structure, UART configurations
 */
static Bool checkConfigParams(Baudrate_Config *baudConfig)
{
    if (NULL == baudConfig)
    {
        return (FALSE);
    }

    if ((baudConfig->data != 5) &&
        (baudConfig->data != 6) &&
        (baudConfig->data != 7) &&
        (baudConfig->data != 8))
    {
        return (FALSE);
    }

    if ((baudConfig->parity != CSL_UART_DISABLE_PARITY) &&
        (baudConfig->parity != CSL_UART_ODD_PARITY)     &&
        (baudConfig->parity != CSL_UART_EVEN_PARITY)    &&
        (baudConfig->parity != CSL_UART_MARK_PARITY)    &&
        (baudConfig->parity != CSL_UART_SPACE_PARITY))
    {
        return (FALSE);
    }

    if ((baudConfig->stopBits != 0) &&
        (baudConfig->stopBits != 1))
    {
        return (FALSE);
    }

    return (TRUE);
}

/**
 *
 *  begin(baudRate, &baudConfig)
 *
 *  Configure UART with the given baud rate
 *      long            baudRate    <- Baud Rate to be set
 *      Baudrate_Config baudConfig  <- Config Structure, used to configure UART
 */
void SerialClass::begin(long baudRate, Baudrate_Config *baudConfig)
{
    CSL_UartSetup  uartSetup;
    CSL_UartHandle uartHandle;
    int            result;

    /* If the instance is not initialized and Baudrate config structure is
       valid */
    if ((0 == this->isInitialized) && (NULL != baudConfig))
    {
        if ((FALSE == checkBaudRate(baudRate)) ||
            (FALSE == checkConfigParams(baudConfig)))
        {
            return;
        }

        result = uartIoExpander();
        if (0 == result)
        {
            result = UART_init(&(this->uartObj), CSL_UART_INST_0, UART_POLLED);
            if (0 == result)
            {
                uartHandle = (CSL_UartHandle)&(this->uartObj);

                uartSetup.clkInput       = getCpuClock();
                /* getCpuClock() API will return CPU clock in terms of kHz */
                uartSetup.clkInput      *= 1000;
                uartSetup.baud           = baudRate;
                uartSetup.wordLength     = baudConfig->data;
                uartSetup.stopBits       = baudConfig->stopBits;
                uartSetup.parity         = baudConfig->parity;
                uartSetup.fifoControl    = CSL_UART_FIFO_DMA1_DISABLE_TRIG14;
                uartSetup.loopBackEnable = CSL_UART_NO_LOOPBACK;
                uartSetup.afeEnable      = CSL_UART_NO_AFE;
                uartSetup.rtsEnable      = CSL_UART_NO_RTS;

                result = UART_setup(uartHandle, &uartSetup);
                if (0 == result)
                {
                    this->isInitialized = 1;
                    this->timeOut       = 0;
                }
            }

        }
    }
}

/**
 *
 *  end()
 *
 *  API to end UART Communication
 */
void SerialClass::end(void)
{
    this->isInitialized    = 0;
    this->timeOut          = 0;
    this->uartObj.uartRegs = (CSL_UartRegsOvly)NULL;
    this->uartObj.sysAddr  = (CSL_SysRegsOvly)NULL;

        ioExpander_Write(1, 2, 0); /* For Stacked Mode */
        ioExpander_Write(1, 3, 1);
        ioExpander_Write(1, 4, 0);
        ioExpander_Write(1, 5, 1);    
}

/**
 *
 *  readNcharacters()
 *
 *  Function to read a desired number of charcters from the Serial Port
 *
 *  CSL_UartHandle uartHandle <-- CSL Uart Handle
 *  char           *buffer    <-- Buffer to store the read characters
 *  int            charLength <-- Number of characters to read
 *  Uint32         timeOut    <-- Timeout for the Serial Read function
 */
static int readNcharacters(CSL_UartHandle uartHandle,
                           char           *buffer,
                           int            charLength,
                           Uint32         timeOut)
{
    int index;
    int status;

    if ((NULL == buffer) || (NULL == uartHandle) || (0 == charLength))
    {
        return (-1);
    }

    for (index = 0; index < charLength; index++)
    {
        status = UART_fgetc (uartHandle, &buffer[index], timeOut);
        if (CSL_SOK != status)
        {
            break;
        }
    }

    return (status);
}

/**
 *
 *  find()
 *
 *  API to read data from the serial until the string of given length is found
 *
 *  char *target <-- Buffer to hold the terminating String
 */
Bool SerialClass::find(char *target)
{
    int            targetStrLength;
    int            status;
    char           *buffer;
    char           *temp;
    int            bufferIndex;
    CSL_UartHandle uartHandle;

    targetStrLength = strlen (target);
    uartHandle      = (CSL_UartHandle)&(this->uartObj);

     /* If the instance is not initialized and the argument is not NULL */
    if ((0 == this->isInitialized) || (NULL == target))
    {
        return (FALSE);
    }

    /* Buffer to hold intermediate characters that are read */
    buffer = new char[targetStrLength + 1];
    if (NULL == buffer)
    {
        return (FALSE);
    }
    bufferIndex = 0;
    temp        = (char *)NULL;
    buffer[targetStrLength] = '\0';

    while (1)
    {
        /* Start reading the characters */
        while (bufferIndex < targetStrLength)
        {
            status = readNcharacters (uartHandle, &buffer[bufferIndex],
                                      targetStrLength - bufferIndex,
                                      this->timeOut);
            if (CSL_SOK != status)
            {
                delete (buffer);
                return (FALSE);
            }

            /* Compare whether the string read is same as the 'target' string */
            temp = strstr(buffer, target);
            if (NULL != temp)
            {
                delete (buffer);
                return (TRUE);
            }

            /* Search for the 1st character of the 'target' string */
            temp = strchr(&buffer[1], target[0]);
            if (NULL == temp)
            {
                bufferIndex = 0;
            }
            else
            {
                strcpy(buffer, temp);
                bufferIndex = strlen(buffer);
            }
        }
    }
}

/**
 *
 *  findUntil()
 *
 *  API to read data from the serial until the string of given length is found
 *  or the terminating string is found
 *
 *  char *target   <-- Buffer to hold the read String
 *  char* terminal <-- String which indicates to stop reading from the serial
 */
Bool SerialClass::findUntil(char *target, char* terminal)
{
    char           character;
    char           *buffer;
    int            bufferIndex;
    int            bufferLen;
    int            targetOrTerm;
    int            index;
    int            targetStrLen;
    int            termStrLen;
    int            status;
    CSL_UartHandle uartHandle;

    targetStrLen = strlen(target);
    termStrLen   = strlen(terminal);
    bufferIndex  = 0;
    targetOrTerm = 0;
    uartHandle   = (CSL_UartHandle)&(this->uartObj);

     /* If the instance is not initialized and the arguments are not NULL */
    if ((0 == this->isInitialized) || (NULL == target) || (NULL == terminal))
    {
        return (FALSE);
    }

    bufferLen = targetStrLen > termStrLen?targetStrLen:termStrLen;
    /* Buffer to hold intermediate characters that are read */
    buffer    = new char[bufferLen + 1];
    if (NULL == buffer)
    {
        return (FALSE);
    }

    while (1)
    {
        if (targetOrTerm)
        {
            index     = bufferIndex - 1;
            character = buffer[index];

            bufferIndex  = 0;
            targetOrTerm = 0;
        }
        else
        {
            /* Search for the 1st character of either target or terminal
               string */
            while (1)
            {
                index = 0;

                status = UART_fgetc (uartHandle, &character, this->timeOut);
                if (CSL_SOK != status)
                {
                    delete (buffer);
                    return (FALSE);
                }

                if ((character == target[0]) || (character == terminal[0]))
                {
                    break;
                }
            }
        }

        /* If the read character matches both target and terminal string */
        if ((character == target[index]) && (character == terminal[index]))
        {
            index++;

            while (1) /* Search for the next characters */
            {
                status = UART_fgetc (uartHandle, &character, this->timeOut);
                if (CSL_SOK != status)
                {
                    delete (buffer);
                    return (FALSE);
                }

                if ((character == target[index]) && (character == terminal[index]))
                {
                    index++;

                    if (index == targetStrLen)
                    {
                        delete (buffer);
                        return (TRUE); /* Target String Found */
                    }
                }
                else
                {
                    break;
                }
            }
        }

        /* If the read character matches the target string */
        if (character == target[index])
        {
            index++;

            if (index == targetStrLen)
            {
                delete (buffer);
                return (TRUE);
            }

            while (1) /* Search for the target string */
            {
                status = UART_fgetc (uartHandle, &character, this->timeOut);
                if (CSL_SOK != status)
                {
                    delete (buffer);
                    return (FALSE);
                }

                if (character == terminal[bufferIndex])
                {
                    buffer[bufferIndex] = character;
                    bufferIndex++;
                    targetOrTerm = 2;
                }
                else if (bufferIndex != termStrLen)
                {
                    bufferIndex  = 0;
                    targetOrTerm = 0;
                }

                if (character == target[index])
                {
                    index++;

                    if (index == targetStrLen)
                    {
                        delete (buffer);
                        return (TRUE); /* Target String Found */
                    }
                }
                else
                {
                    break;
                }
            }
        }
        /* If the read character matches the terminal string */
        else if (character == terminal[index])
        {
            index++;

            if (index == termStrLen)
            {
                delete (buffer);
                return (FALSE);
            }

            while (1) /* Search for the terminal string */
            {
                status = UART_fgetc (uartHandle, &character, this->timeOut);
                if (CSL_SOK != status)
                {
                    delete (buffer);
                    return (FALSE);
                }

                if (character == target[bufferIndex])
                {
                    buffer[bufferIndex] = character;
                    bufferIndex++;
                    targetOrTerm = 1;
                }
                else if (bufferIndex != targetStrLen)
                {
                    bufferIndex  = 0;
                    targetOrTerm = 0;
                }

                if (character == terminal[index])
                {
                    index++;

                    if (index == termStrLen)
                    {
                        delete (buffer);
                        return (FALSE); /* Terminal String Found */
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
        }
    }
}

/**
 *
 *  flush()
 *
 *  API that Waits for the transmission of outgoing serial data to complete
 *
 */
void SerialClass::flush(void)
{
    CSL_UartHandle uartHandle;
    int            eventId;

    uartHandle = (CSL_UartHandle)&(this->uartObj);

    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        do
        {
            /* Wait until the Transmitter Register is Empty */
            eventId = UART_getEventId (uartHandle);
        } while (1 != eventId);
    }
}

/**
 *
 *  parseFloat()
 *
 *  API that returns the first valid floating point number, read from the Serial
 *
 */
float SerialClass::parseFloat(void)
{
    long           decimalPart;
    float          readFloat;
    float          fractionPart;
    long           lengthFractionalPart;
    char           character;
    int            status;
    CSL_UartHandle uartHandle;

    uartHandle = (CSL_UartHandle)&(this->uartObj);

    while (1)
    {
        decimalPart          = 0;
        readFloat            = 0;
        lengthFractionalPart = 0;

        /* Read the first Digit */
        status = UART_fgetc (uartHandle, &character, this->timeOut);
        if (CSL_SOK != status)
        {
            return (-1);
        }

        /* Check whether the read character is a digit (This will be the 1st
           digit) */
        if ((character >= '0') && (character <= '9'))
        {
            decimalPart += (character - '0');
            fractionPart = 0;

            while (1) /* Start reading the next digits */
            {
                status = UART_fgetc (uartHandle, &character, this->timeOut);
                if (CSL_SOK != status)
                {
                    return (-1);
                }

                if ((character >= '0') && (character <= '9'))
                {
                    /* In this block we are converting character to integer value */
                    decimalPart *= 10;
                    decimalPart += (character - '0');

                    if (lengthFractionalPart)
                    {
                        lengthFractionalPart *= 10;
                    }

                    /* Have we reached the maximum supported value by the
                       data type - 'long' */
                    if ((decimalPart < 0) || (lengthFractionalPart < 0))
                    {
                        return (-1);
                    }
                }
                else if ('.' == character)
                {
                    /* Decimal Point found, read the mantissa (fractional) part */
                    if (0 == lengthFractionalPart)
                    {
                        readFloat            = (float)decimalPart;
                        lengthFractionalPart = 1;
                        decimalPart          = 0;
                    }
                    else /* If the Floating Point value is read */
                    {
                        fractionPart  = (float)decimalPart;
                        fractionPart /= lengthFractionalPart;
                        readFloat    += fractionPart;
                        return (readFloat);
                    }
                }
                else /* If the Floating Point value is read */
                {
                    if (lengthFractionalPart != 0)
                    {
                        fractionPart  = (float)decimalPart;
                        fractionPart /= lengthFractionalPart;
                        readFloat    += fractionPart;
                        return (readFloat);
                    }
                }
            }
        }
    }
}

/**
 *
 *  parseInt()
 *
 *  API that returns the first valid Integer, read from the Serial
 *
 */
long SerialClass::parseInt(void)
{
    long           readInteger;
    char           character;
    int            status;
    CSL_UartHandle uartHandle;

    uartHandle = (CSL_UartHandle)&(this->uartObj);

    while (1)
    {
        readInteger = 0;

        /* Read the first Digit */
        status = UART_fgetc (uartHandle, &character, this->timeOut);
        if (CSL_SOK != status)
        {
            return (-1);
        }

        /* Check whether the read character is a digit (This will be the 1st
           digit) */
        if ((character >= '0') && (character <= '9'))
        {
            readInteger += (character - '0');

            while (1) /* Start reading the next digits */
            {
                status = UART_fgetc (uartHandle, &character, this->timeOut);
                if (CSL_SOK != status)
                {
                    return (-1);
                }

                if ((character >= '0') && (character <= '9'))
                {
                    /* In this block we are converting character to integer value */
                    readInteger *= 10;
                    readInteger += (character - '0');

                    /* Have we Reached the maximum value */
                    if (readInteger < 0)
                    {
                        return (-1);
                    }
                }
                else
                {
                    return (readInteger);
                }
            }
        }
    }
}

/**
 *
 *  print(value)
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text
 *
 *  int value <-- Integer value that is to be printed on the serial
 */
long SerialClass::print(int value)
{
    return (this->print((long)value));
}

/**
 *
 *  print(value)
 *
 *  API to Print an unsigned integer to the serial port as human-readable
 *  ASCII text
 *
 *  unsigned int value <-- Unsigned integer value that is to be printed on
 *                         the serial
 */
long SerialClass::print(unsigned int value)
{
    return (this->print((unsigned long)value));
}

/**
 *
 *  print(value)
 *
 *  API to Print a short to the serial port as human-readable ASCII text
 *
 *  short value <-- Short value that is to be printed on the serial
 */
long SerialClass::print(short value)
{
    return (this->print((long)value));
}

/**
 *
 *  print(value)
 *
 *  API to Print an unsigned short to the serial port as human-readable
 *  ASCII text
 *
 *  unsigned short value <-- Unsigned short value that is to be printed on
 *                           the serial
 */
long SerialClass::print(unsigned short value)
{
    return (this->print((unsigned long)value));
}

/**
 *
 *  print(value)
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text
 *
 *  long value <-- Integer value that is to be printed on the serial
 */
long SerialClass::print(long value)
{
    char           valAsString[20];
    int            status;
    int            length;
    CSL_UartHandle uartHandle;

    if (0 == this->isInitialized)
    {
        return (0);
    }

    /* sprintf() will return the no of characters written to the string */
    length = sprintf(valAsString, "%ld", value);

    uartHandle = (CSL_UartHandle)&(this->uartObj);

    status = UART_write (uartHandle, valAsString, length, this->timeOut);
    if (0 == status)
    {
        return (length);
    }
    else
    {
        return (0);
    }
}

/**
 *
 *  print(value)
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text
 *
 *  unsigned long value <-- Integer value that is to be printed on the serial
 */
long SerialClass::print(unsigned long value)
{
    long           length;
    int            status;
    char           valAsString[20];
    CSL_UartHandle uartHandle;

    /* sprintf() will return the no of characters written to the string */
    length = sprintf(valAsString, "%lu", value);

    uartHandle = (CSL_UartHandle)&(this->uartObj);

    status = UART_write (uartHandle, valAsString, length, this->timeOut);
    if (0 == status)
    {
        return (length);
    }
    else
    {
        return (0);
    }
}

/**
 *
 *  print(value)
 *
 *  API to Print a Floating Point Value to the serial port as human-readable ASCII text
 *
 *  float value <-- Floating Point value that is to be printed on the serial
 */
long SerialClass::print(float value)
{
    return (this->print(value, 2));
}

/**
 *
 *  print(value)
 *
 *  API to Print a Double Precision Floating Point Value to the serial port as
 *  human-readable ASCII text
 *
 *  double value <-- Double Precision Floating Point value that is to be printed
 *                   on the serial
 */
long SerialClass::print(double value)
{
    return (this->print(value, 2));
}

/**
 *
 *  print(character)
 *
 *  API to Print a character to the serial port as human-readable ASCII text
 *
 *  char character <-- Character value that is to be printed on the serial
 */
long SerialClass::print(char character)
{
    char           printString[2];
    CSL_UartHandle uartHandle;
    int            status;

    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        printString[0] = character;
        printString[1] = '\0';

        uartHandle = (CSL_UartHandle)&(this->uartObj);

        status = UART_write (uartHandle, printString, 1, this->timeOut);
        if (0 == status)
        {
            return (1);
        }
    }

    return (0);
}

/**
 *
 *  print(printString)
 *
 *  API to Print a String to the serial port as human-readable ASCII text
 *
 *  char *printString <-- The String that is to be printed on the serial
 */
long SerialClass::print(char *printString)
{
    CSL_UartHandle uartHandle;
    int            status;

    /* If the instance is initialized and the argument is not NULL */
    if ((1 == this->isInitialized) && (NULL != printString))
    {
        uartHandle = (CSL_UartHandle)&(this->uartObj);

        status = UART_write (uartHandle, printString, strlen(printString), this->timeOut);
        if (0 == status)
        {
            return (strlen(printString));
        }
    }

    return (0);
}

/**
 *
 *  convertDecimalToBase(value, convString, base)
 *
 *  API to Convert a negative/positive Decimal value of 16 bit integer to
 *  Binary, Octal or Hexadecimal Form
 *
 *  int value        <-- The integer value that is to be converted
 *  char *convString <-- Character String to hold the converted hexadecimal
 *                       value
 *  int base         <-- Indicates the base to which the decimal value needs
 *                       to be converted
 */
static void convertDecimalToBase (int value, char *convString, int base)
{
    unsigned long convValue;
    int           index;
    int           rightShift;
    int           shiftDecrement;
    int           mask;
    int           temp;

    index     = 0;
    convValue = (unsigned long)value;

    /* Grouping of 4 bits of the Number will give the Hexadecimal value
       Grouping of 3 bits of the Number will give the Octal value
       Grouping of 1 bit of the Number will give the Binary value
       Ex: For a number 1234 (which is stored as 10011010010 in memory)
       Grouping of 4 bits gives (100 1101 0010): 0x4D2 (Hexadecimal)
       Grouping of 3 bits gives (10 011 010 010): 2322  (Octal)
       Grouping of 1 bit gives  (10011010010):10011010010 (Binary)
       */
    if (16 == base)
    {
        rightShift     = 12;
        shiftDecrement = 4;
        mask           = 0x0F;

        convString[index++] = '0';
        convString[index++] = 'x';
    }
    else if (8 == base)
    {
        rightShift     = 15;
        shiftDecrement = 3;
        mask           = 7;
    }
    else
    {
        rightShift     = 15;
        shiftDecrement = 1;
        mask           = 1;
    }

    while (rightShift >= 0)
    {
        temp = (convValue >> rightShift) & mask;

        if ((temp >= 0) && (temp <= 9))
        {
            convString[index++] = '0' + temp;
        }
        else /* 0xA - 0xF for Hexadecimal format */
        {
            convString[index++] = 'A' + (temp - 10);
        }

        rightShift -= shiftDecrement;
    }

    convString[index] = '\0';
}

/**
 *
 *  convertDecimalToBase(value, convString, base)
 *
 *  API to Convert a negative/positive Decimal value of 32 bit integer to
 *  Binary, Octal or Hexadecimal Form
 *
 *  long value       <-- The integer value that is to be converted
 *  char *convString <-- Character String to hold the converted hexadecimal
 *                       value
 *  int base         <-- Indicates the base to which the decimal value needs
 *                       to be converted
 */
static void convertDecimalToBase (long value, char *convString, int base)
{
    unsigned long convValue;
    int           index;
    int           rightShift;
    int           shiftDecrement;
    int           mask;
    int           temp;

    index     = 0;
    convValue = (unsigned long)value;

    /* Grouping of 4 bits of the Number will give the Hexadecimal value
       Grouping of 3 bits of the Number will give the Octal value
       Grouping of 1 bit of the Number will give the Binary value
       Ex: For a number 1234 (which is stored as 10011010010 in memory)
       Grouping of 4 bits gives (100 1101 0010): 0x4D2 (Hexadecimal)
       Grouping of 3 bits gives (10 011 010 010): 2322  (Octal)
       Grouping of 1 bit gives  (10011010010):10011010010 (Binary)
       */
    if (16 == base)
    {
        rightShift     = 28;
        shiftDecrement = 4;
        mask           = 0x0F;

        convString[index++] = '0';
        convString[index++] = 'x';
    }
    else if (8 == base)
    {
        rightShift     = 30;
        shiftDecrement = 3;
        mask           = 7;
    }
    else
    {
        rightShift     = 31;
        shiftDecrement = 1;
        mask           = 1;
    }

    while (rightShift >= 0)
    {
        temp = (convValue >> rightShift) & mask;

        if ((temp >= 0) && (temp <= 9))
        {
            convString[index++] = '0' + temp;
        }
        else /* 0xA - 0xF for Hexadecimal format */
        {
            convString[index++] = 'A' + (temp - 10);
        }

        rightShift -= shiftDecrement;
    }

    convString[index] = '\0';
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Integer of 16 bits to the serial port as human-readable
 *  ASCII text, in either Binary, Decimal, Octal or Hexadecimal Form
 *
 *  int value  <-- Integer value that is to be printed on the serial
 *  int format <-- The format in which the value needs to be printed
 */
long SerialClass::print(int value, int format)
{
    long           returnValue;
    char           printString[50];
    CSL_UartHandle uartHandle;
    int            status;

    returnValue = 0;

    if (1 == this->isInitialized)
    {
        switch (format)
        {
            case BIN:
                convertDecimalToBase (value, printString, 2);
                break;

            case DEC:
                returnValue = this->print((long)value);
                break;

            case OCT:
                convertDecimalToBase (value, printString, 8);
                break;

            case HEX:
                convertDecimalToBase (value, printString, 16);
                break;

            default:
                return (returnValue);
        }

        /* If the format is "DEC" call to this->print(value) would have printed
           the integer on the Serial */
        if (DEC != format)
        {
            uartHandle = (CSL_UartHandle)&(this->uartObj);

            status = UART_write (uartHandle, printString, strlen(printString), this->timeOut);
            if (0 == status)
            {
                returnValue = strlen(printString);
            }
        }
    }

    return (returnValue);
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Unsigned Integer of 16 bits to the serial port as
 *  human-readable ASCII text, in either Binary, Decimal, Octal or Hexadecimal
 *  Form
 *
 *  unsigned int value  <-- Integer value that is to be printed on the serial
 *  int format          <-- The format in which the value needs to be printed
 */
long SerialClass::print(unsigned int value, int format)
{
    return (this->print((int)value, format));
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Integer of 16 bits to the serial port as human-readable
 *  ASCII text, in either Binary, Decimal, Octal or Hexadecimal Form
 *
 *  short value  <-- Integer value that is to be printed on the serial
 *  int format   <-- The format in which the value needs to be printed
 */
long SerialClass::print(short value, int format)
{
    return (this->print((int)value, format));
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Unsigned Integer of 16 bits to the serial port as
 *  human-readable ASCII text, in either Binary, Decimal, Octal or Hexadecimal
 *  Form
 *
 *  unsigned short value  <-- Integer value that is to be printed on the serial
 *  int format            <-- The format in which the value needs to be printed
 */
long SerialClass::print(unsigned short value, int format)
{
    return (this->print((int)value, format));
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Unsigned Integer of 32 bits to the serial port as
 *  human-readable ASCII text, in either Binary, Decimal, Octal or
 *  Hexadecimal Form
 *
 *  unsigned long value  <-- Integer value that is to be printed on the serial
 *  int format           <-- The format in which the value needs to be printed
 */
long SerialClass::print(unsigned long value, int format)
{
    return (this->print((long)value, format));
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Integer of 32 bits to the serial port as human-readable
 *  ASCII text, in either Binary, Decimal, Octal or Hexadecimal Form
 *
 *  long value  <-- Integer value that is to be printed on the serial
 *  int  format <-- The format in which the value needs to be printed
 */
long SerialClass::print(long value, int format)
{
    long           returnValue;
    char           printString[50];
    CSL_UartHandle uartHandle;
    int            status;

    returnValue = 0;

    if (1 == this->isInitialized)
    {
        switch (format)
        {
            case BIN:
                convertDecimalToBase (value, printString, 2);
                break;

            case DEC:
                returnValue = this->print(value);
                break;

            case OCT:
                convertDecimalToBase (value, printString, 8);
                break;

            case HEX:
                convertDecimalToBase (value, printString, 16);
                break;

            default:
                return (returnValue);
        }

        /* If the format is "DEC" call to this->print(value) would have printed
           the integer on the Serial */
        if (DEC != format)
        {
            uartHandle = (CSL_UartHandle)&(this->uartObj);

            status = UART_write (uartHandle, printString, strlen(printString), this->timeOut);
            if (0 == status)
            {
                returnValue = strlen(printString);
            }
        }
    }

    return (returnValue);
}

/**
 *
 *  print(value, noOfDecDigits)
 *
 *  API to Print a Floating Point Value to the serial port as human-readable
 *  ASCII text
 *
 *  float value         <-- Floating Point value that is to be printed on the serial
 *  int   noOfDecDigits <-- No of digits to print after the decimal point.
 */
long SerialClass::print(float value, int noOfDecDigits)
{
    char           valAsString[30];
    char           format[10];
    int            length;
    int            status;
    CSL_UartHandle uartHandle;

    if ((0 == this->isInitialized) || (value < 0) ||
        (noOfDecDigits < 0) || (noOfDecDigits > 7))
    {
        return (0);
    }

    /* Format specifier to print the requested no of digits after the decimal
       point */
    sprintf(format, "%%.%df", noOfDecDigits);

    /* sprintf() will return the no of characters written to the string */
    length = sprintf(valAsString, format, value);

    uartHandle = (CSL_UartHandle)&(this->uartObj);

    status = UART_write (uartHandle, valAsString, length, this->timeOut);
    if (0 == status)
    {
        return (length);
    }
    else
    {
        return (0);
    }
}

/**
 *
 *  print(value, noOfDecDigits)
 *
 *  API to Print a Double Precision Floating Point Value to the serial port as
 *  human-readable ASCII text
 *
 *  double value        <-- Double Precision Floating Point value that is to be
 *                          printed on the serial
 *  int   noOfDecDigits <-- No of digits to print after the decimal point.
 */
long SerialClass::print(double value, int noOfDecDigits)
{
    char           valAsString[30];
    char           format[10];
    int            length;
    int            status;
    CSL_UartHandle uartHandle;

    if ((0 == this->isInitialized) || (value < 0) ||
        (noOfDecDigits < 0) || (noOfDecDigits > 15))
    {
        return (0);
    }

    /* Format specifier to print the requested no of digits after the decimal
       point */
    sprintf(format, "%%.%df", noOfDecDigits);

    /* sprintf() will return the no of characters written to the string */
    length = sprintf(valAsString, format, value);

    uartHandle = (CSL_UartHandle)&(this->uartObj);

    status = UART_write (uartHandle, valAsString, length, this->timeOut);
    if (0 == status)
    {
        return (length);
    }
    else
    {
        return (0);
    }
}

/**
 *
 *  println(value)
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  int value <-- Integer value that is to be printed on the serial
 */
long SerialClass::println(int value)
{
    return (this->println((long)value));
}

/**
 *
 *  println(value)
 *
 *  API to Print an unsigned integer to the serial port as human-readable
 *  ASCII text, followed by a new line ("\r\n")
 *
 *  unsigned int value <-- Unsigned integer value that is to be printed
 *                         on the serial
 */
long SerialClass::println(unsigned int value)
{
    return (this->println((unsigned long)value));
}

/**
 *
 *  println(value)
 *
 *  API to Print a short to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  short value <-- Short value that is to be printed on the serial
 */
long SerialClass::println(short value)
{
    return (this->println((long)value));
}

/**
 *
 *  println(value)
 *
 *  API to Print an unsigned short to the serial port as human-readable
 *  ASCII text, followed by a new line ("\r\n")
 *
 *  unsigned short value <-- Unsigned short value that is to be printed
 *                           on the serial
 */
long SerialClass::println(unsigned short value)
{
    return (this->println((unsigned long)value));
}

/**
 *
 *  println(value)
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  long value <-- Integer value that is to be printed on the serial
 */
long SerialClass::println(long value)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(value);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  println(value)
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  unsigned long value <-- Integer value that is to be printed on the serial
 */
long SerialClass::println(unsigned long value)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(value);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  println(value)
 *
 *  API to Print a Floating Point Value to the serial port as human-readable
 *  ASCII text, followed by a new line ("\r\n")
 *
 *  float value <-- Floating Point value that is to be printed on the serial
 */
long SerialClass::println(float value)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(value);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  println(value)
 *
 *  API to Print a Double Precision Floating Point Value to the serial port as
 *  human-readable ASCII text, followed by a new line ("\r\n")
 *
 *  double value <-- Double Precision Floating Point value that is to be printed
 *                   on the serial
 */
long SerialClass::println(double value)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(value);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  println(value)
 *
 *  API to Print a character to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  char character <-- Character value that is to be printed on the serial
 */
long SerialClass::println(char character)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(character);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  println(printString)
 *
 *  API to Print an String to the serial port as human-readable ASCII text,
 *  followed by a new line ("\r\n")
 *
 *  char *printString <-- The String that is to be printed on the serial
 */
long SerialClass::println(char *printString)
{
    long returnValue;

    returnValue = 0;

    /* If the instance is initialized and the argument is not NULL */
    if ((1 == this->isInitialized) && (NULL != printString))
    {
        returnValue = this->print(printString);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Integer of 16 bits to the serial port as human-readable
 *  ASCII text, in either Binary, Decimal, Octal or Hexadecimal Form, followed
 *  by a new line ("\r\n")
 *
 *  int value  <-- Integer value that is to be printed on the serial
 *  int format <-- The format in which the value needs to be printed
 */
long SerialClass::println(int value, int format)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(value, format);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Unsigned Integer of 16 bits to the serial port as
 *  human-readable ASCII text, in either Binary, Decimal, Octal or Hexadecimal
 *  Form, followed by a new line ("\r\n")
 *
 *  unsigned int value  <-- Integer value that is to be printed on the serial
 *  int format          <-- The format in which the value needs to be printed
 */
long SerialClass::println(unsigned int value, int format)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print((int)value, format);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Integer of 16 bits to the serial port as human-readable
 *  ASCII text, in either Binary, Decimal, Octal or Hexadecimal Form, followed
 *  by a new line ("\r\n")
 *
 *  short value  <-- Integer value that is to be printed on the serial
 *  int format   <-- The format in which the value needs to be printed
 */
long SerialClass::println(short value, int format)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print((int)value, format);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Unsigned Integer of 16 bits to the serial port as
 *  human-readable ASCII text, in either Binary, Decimal, Octal or Hexadecimal
 *  Form, followed by a new line ("\r\n")
 *
 *  unsigned short value  <-- Integer value that is to be printed on the serial
 *  int format            <-- The format in which the value needs to be printed
 */
long SerialClass::println(unsigned short value, int format)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print((int)value, format);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  print(value, format)
 *
 *  API to Print an Unsigned Integer of 32 bits to the serial port as
 *  human-readable ASCII text, in either Binary, Decimal, Octal or
 *  Hexadecimal Form, followed by a new line ("\r\n")
 *
 *  unsigned long value  <-- Integer value that is to be printed on the serial
 *  int format           <-- The format in which the value needs to be printed
 */
long SerialClass::println(unsigned long value, int format)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print((long)value, format);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  println(value, format)
 *
 *  API to Print an Integer to the serial port as human-readable ASCII text,
 *  in either Binary, Decimal, Octal or Hexadecimal Form, followed by a new
 *  line ("\r\n")
 *
 *  long value  <-- Integer value that is to be printed on the serial
 *  int  format <-- The format in which the value needs to be printed
 */
long SerialClass::println(long value, int format)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(value, format);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  println(value, noOfDecDigits)
 *
 *  API to Print a Floating Point Value to the serial port as human-readable
 *  ASCII text, followed by a new line ("\r\n")
 *
 *  float value         <-- Floating Point value that is to be printed on the serial
 *  int   noOfDecDigits <-- No of digits to print after the decimal point.
 */
long SerialClass::println(float value, int noOfDecDigits)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(value, noOfDecDigits);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  println(value, noOfDecDigits)
 *
 *  API to Print a Double Precision Floating Point Value to the serial port as
 *  human-readable ASCII text, followed by a new line ("\r\n")
 *
 *  double value        <-- Double Precision Floating Point value that is to be
 *                          printed on the serial
 *  int   noOfDecDigits <-- No of digits to print after the decimal point.
 */
long SerialClass::println(double value, int noOfDecDigits)
{
    long returnValue;

    returnValue = 0;
    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        returnValue = this->print(value, noOfDecDigits);
        if (returnValue != 0)
        {
            returnValue += this->print("\r\n");
        }
    }

    return (returnValue);
}

/**
 *
 *  read()
 *
 *  API that reads incoming character from the Serial
 *
 */
int SerialClass::read(void)
{
    char           character;
    int            status;
    CSL_UartHandle uartHandle;

    character  = -1;
    uartHandle = (CSL_UartHandle)&(this->uartObj);

    if (1 == this->isInitialized) /* If the instance is initialized */
    {
        status = UART_fgetc (uartHandle, &character, this->timeOut);
        if (0 != status)
        {
            character  = -1;
        }
    }

    return (character);
}

/**
 *
 *  readBytes(buffer, length)
 *
 *  API that reads incoming string of the requested length from the Serial
 *
 * char *buffer <-- Buffer to hold the read characters
 * int length   <-- Length of the String, to read
 */
int SerialClass::readBytes(char *buffer, int length)
{
    CSL_UartHandle uartHandle;
    int            status;

    status = -1;

    /* If the instance is initialized and the argument is not NULL */
    if ((1 == this->isInitialized) && (NULL != buffer) && (length > 0))
    {
        uartHandle = (CSL_UartHandle)&(this->uartObj);

        status = UART_read(uartHandle, buffer, length, this->timeOut);
        if (0 == status)
        {
            buffer[length] = '\0';
        }
        else
        {
            buffer[0] = '\0';
        }
    }

    return (status);
}

/**
 *
 *  readBytesUntil(termChar, buffer, length)
 *
 *  API that reads incoming string of the requested length from the Serial.
 *  The API terminates if the terminator character is detected or the
 *  string of determined length has been read
 *
 * char termChar <-- Character to indicate to terminate reading from the serial
 * char *buffer  <-- Buffer to hold the read characters
 * int length    <-- Length of the String, to read
 */
int SerialClass::readBytesUntil(char termChar, char *buffer, int length)
{
    int            status;
    int            index;
    char           character;
    char           *destString;
    CSL_UartHandle uartHandle;

    index      = 0;
    destString = buffer;
    uartHandle = (CSL_UartHandle)&(this->uartObj);

    /* If the instance is not initialized and the argument is NULL */
    if ((0 == this->isInitialized) || (NULL == buffer) || (length < 0))
    {
        return (-1);
    }

    while (index < length)
    {
        status = UART_fgetc (uartHandle, &character, this->timeOut);
        if (CSL_SOK != status)
        {
            buffer[0] = '\0';
            return (status);
        }

        if (character == termChar)
        {
            break;
            /* Terminating character read, hence return the string which is
               read till now */
        }

        *destString = character;
        index++;
        destString++;
    }

    *destString = '\0';

    return (status);
}

/**
 *
 *  setTimeout(newTimeOutVal)
 *
 *  API to set the Time Out value for Serial read and write operations
 *
 * long newTimeOutVal   <-- The new Time Out value
 */
void SerialClass::setTimeout(long newTimeOutVal)
{
    if ((1 == this->isInitialized) && (newTimeOutVal >= 0))
    {
        this->timeOut = newTimeOutVal;
    }
}

/**
 *
 *  write(value)
 *
 *  API to Write an Integer to the serial port as human-readable ASCII text
 *
 *  int value <-- Integer value that is to be printed on the serial
 */
int SerialClass::write(int value)
{
    int returnStatus;

    returnStatus = 0;
    if ((1 == this->isInitialized) && (value >= 0))
    {
        returnStatus = this->print((long)value);
    }

    return (returnStatus);
}

/**
 *
 *  write(string)
 *
 *  API to Write a String to the serial port as human-readable ASCII text
 *
 *  char *string <-- The String that is to be printed on the serial
 */
int SerialClass::write(char *string)
{
    int returnStatus;

    returnStatus = 0;

    /* If the instance is initialized and the argument is not NULL */
    if ((1 == this->isInitialized) && (NULL != string))
    {
        returnStatus = this->print (string);
    }

    return (returnStatus);
}

/**
 *
 *  write(string, length)
 *
 *  API to Write a String to the serial port as human-readable ASCII text, of
 *  desired  length
 *
 *  char *string <-- The String that is to be printed on the serial
 *  int  length  <-- Length of the String to be written to the serial
 */
int SerialClass::write(char *string, int length)
{
    CSL_UartHandle uartHandle;
    int            status;

    /* If the instance is initialized and the argument is not NULL */
    if ((1 == this->isInitialized) && (NULL != string))
    {
        uartHandle = (CSL_UartHandle)&(this->uartObj);

        status = UART_write (uartHandle, string, length, this->timeOut);
        if (0 == status)
        {
            return (length);
        }
    }

    return (0);
}
