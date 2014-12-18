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
/** @file OLED.cpp
 *
 *  @brief OLED implementation
 *
 */

#include "OLED.h"

/**
 * Class identifier declaration
 */
OLED disp;

/************ low level data pushing commands **********/
/** ===========================================================================
 *   @n@b handleErrors(status)
 *
 *   @b Description
 *   @n Handles errors returned by CSL APIs
 *
 *   @b Arguments
 *   @verbatim
 *       CSL_Status status  <- return status of the CSL_API
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
static void handleErrors(CSL_Status status)
{

}

/** ===========================================================================
 *   @n@b writeI2C
 *
 *   @b Description
 *   @n Function to perform I2C writes.
 *
 *   @b Arguments
 *   @verbatim
 *      address    - Address of the I2C slave module
 *      data       - pointer to the data to be written
 *      quantity   - Number of data words written
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - I2C writes are successful
 *   @li                    CSL_ESYS_FAIL       - I2C writes are not successful
 *   @li                    CSL_ESYS_INVPARAMS  - if the input parameters
 *                                                are invalid
 *
 *  ===========================================================================
 */
static int writeI2C(Uint16 address, Uint16 *data, Uint16 quantity)
{
    CSL_Status status;

	if((data != NULL)  && (quantity != 0))
	{
	    status = Wire.beginTransmission(address);
		if(status == CSL_SOK)
		{
		    status = Wire.write((unsigned int*)data, (unsigned int)quantity);
	        if(status == quantity)
			{
			    status = Wire.endTransmission();
			}
			else
			{
			    status = CSL_ESYS_FAIL;
			}
		}
		else
		{
		    status = CSL_ESYS_FAIL;
		}
    }
	else
	{
	    status = CSL_ESYS_INVPARAMS;
	}

	return status;
}

/**
 *  Int16 send(Uint16 comdat, Uint16 data)
 *
 *      Sends 2 bytes of data to the OSD9616
 *
 *      comdat :  0x00  => Command
 *                0x40  => Data
 *      data   :  Data to be sent
 *
 *  Returns
 *      0 => Success
 *      1 => Fail
 */
static int send(Uint16 comdat, Uint16 data)
{
    Uint16 cmd[2];
    CSL_Status status;

    cmd[0] = comdat & 0x00FF;     // Specifies whether data is Command or Data
    cmd[1] = data;                // Command / Data
    csl_waitusec(1000);

    status = writeI2C(I2C_LCD_ADDR, cmd, 2);
	if(status != CSL_SOK)
	{
        handleErrors(status);
	}
	csl_waitusec(0xFFF);

	return status;
}

/**
 *  Int16 multiSend(Uint16* data, Uint16 len)
 *
 *      Sends multiple bytes of data to the OSD9616
 *
 *      *data :  Pointer to start of I2C transfer
 *       len  :  Length of I2C transaction
 *
 *  Returns
 *      0 => Success
 *      1 => Fail
 */
static int multiSend(Uint16 *data, Uint16 len)
{
    Uint16 x;
    Uint16 cmd[10];
    CSL_Status status;

    for(x=0;x<len;x++)               // Command / Data
    {
    	cmd[x] = data[x];
    }

    csl_waitusec(1000);

    status = writeI2C(I2C_LCD_ADDR, cmd, len);
	if(status != CSL_SOK)
	{
        handleErrors(status);
	}

	csl_waitusec(0xFFF);

    return status;
}

/** ===========================================================================
 *   @n@b oledInit()
 *
 *   @b Description
 *   @n Function initializes I2C Module and also LCD.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::oledInit(void)
{
	/*
	 *  Font data for Century Gothic 8pt
	 */

	/* Character bitmaps for Century Gothic 8pt */
	row = 0;
	totalcols = 0;
	init();
	FontBitmap = &arial_8ptBitmaps[0];
    FontDescriptors = &arial_8ptDescriptors[0];
    FontInfo = &arial_8ptFontInfo;

}
/** ===========================================================================
 *   @n@b init()
 *
 *   @b Description
 *   @n Function initializes I2C Module and also LCD.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::init()
{
    Uint16 cmd[10];

    /* Note: Wire initialization will be done in main.cpp */
    /* Initialize OSD9616 display */
    send(0x00,0x00); // Set low column address
    send(0x00,0x10); // Set high column address

    send(0x00,0xae); // Turn off oled panel

    send(0x00,0xd5); // Set display clock divide ratio/oscillator frequency
    send(0x00,0x80); // Set divide ratio

    cmd[0] = 0x00;   // Set multiplex ratio(1 to 16)
    cmd[1] = 0xa8;
    cmd[2] = 0x0f;
    multiSend(cmd, 3);

    send(0x00,0xd3); // Set display offset
    send(0x00,0x00); // Not offset

    send(0x00,0x40); // Set Display start line address

    cmd[0] = 0x00;  //--set DC-DC enable
    cmd[1] = 0x8d; // Set Charge Pump
    cmd[2] = 0x14;
    multiSend(cmd, 3);

    send(0x00,0xa1); // Set segment re-map 95 to 0
    send(0x00,0xc8); // Set COM Output Scan Direction

    cmd[0] = 0x00;  // Set com pins hardware configuration
    cmd[1] = 0xda;
    cmd[2] = 0x02;
    multiSend(cmd, 3);

    cmd[0] = 0x00;  // Set contrast control register
    cmd[1] = 0x81;
    cmd[2] = 0xaf;
    multiSend(cmd, 3);

    cmd[0] = 0x00;  // Set pre-charge period
    cmd[1] = 0xd9;
    cmd[2] = 0xf1;
    multiSend(cmd, 3);

    send(0x00,0xdb); // Set vcomh
    send(0x00,0x20); // 0.83*vref

    send(0x00,0xa4); // Set entire display on/off
    send(0x00,0xa6); // Set normal display

    send(0x00,0xaf); // Turn on oled panel

	dir = 0;
}

/** ===========================================================================
 *   @n@b setOrientation()
 *
 *   @b Description
 *   @n Function to set the orientation of LCD.
 *
 *   @b Arguments
 *   @verbatim
 *     int newDir      <- Direction of orientation
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::setOrientation(int newDir)
{
	if(newDir == 0)
	{	/* Set divide ratio */
		send(0x00,0xC8);
		dir = 1;
	}
	else if(newDir == 1)
	{	/* Set divide ratio */
		send(0x00,0xC0);
		dir = 0;
	}
}

/** ===========================================================================
 *   @n@b flip()
 *
 *   @b Description
 *   @n Flips the screen vertically
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::flip()
{
	if(dir == 0)
	{   /* Set divide ratios */
		send(0x00,0xC0);
		send(0x00,0xA1);
		dir = 1;
	}
	else if(dir == 1)
	{   /* Set divide ratios */
		send(0x00,0xC8);
		send(0x00,0xA1);
		dir = 0;
	}
}

/** ===========================================================================
 *   @n@b begin()
 *
 *   @b Description
 *   @n Specifies the dimensions (width and height) of the display.
 *
 *   @b Arguments
 *   @verbatim
 *      Uint8 cols      <- Number of columns
 *      Uint8 rows      <- Number of rows
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::begin(void)
{
}

/** ===========================================================================
 *   @n@b printchar(character)
 *
 *   @b Description
 *   @n Prints a character to the LCD
 *
 *   @b Arguments
 *   @verbatim
 *     unsigned char character      <- Character to be printed
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
int OLED::printchar(unsigned char a)
{
	Int16 i, n;

	n = (int) a - 0x20;

	for(i=0;i<(FontDescriptors[n].widthBits);i++)
    {
		if(totalcols > 127)
		{
			return 0;
		}
		else
		{
			totalcols++;
		}
		send(0x40,FontBitmap[FontDescriptors[n].offset + i]);
    }
	if(totalcols > 127)
	{
		return 0;
	}
	else
	{
		totalcols++;
	}
	send(0x40,0x00);
	if(totalcols > 127)
	{
		return 0;
	}
	else
	{
		totalcols++;
	}
	send(0x40,0x00);  // 2 Spaces
    send(0x00,0x2e);  // Deactivate Scrolling
	return 1;

}

/** ===========================================================================
 *   @n@b setline(line)
 *
 *   @b Description
 *   @n Sets the start line for the display
 *
 *   @b Arguments
 *   @verbatim
 *     int line      <- Line number
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::setline(int line)
{
    if(line == 0)
	{
		/* Write to page 1 */
		send(0x00,0x00);   // Set low column address
		send(0x00,0x10);   // Set high column address
		send(0x00,0xb0+1); // Set page for page 1
    }
	else if(line == 1)
	{
	    /* Write to page 0 */
		send(0x00,0x00);   // Set low column address
		send(0x00,0x10);   // Set high column address
		send(0x00,0xb0+0); // Set page for page 0

	}
	totalcols = 0;
	row = line;
}

/** ===========================================================================
 *   @n@b setRolling(int row, int status)
 *
 *   @b Description
 *   @n Sets the rolling parameters
 *
 *   @b Arguments
 *   @verbatim
 *     int row      <- Row number
 *     int status   <- Status of rolling
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::setRolling(int row, int status)
{
	if(row == 0)
	{
		if(status == 0)
		{
			rolling0 = 0;
		}
		else
		{
			rolling0 = 1;
		}
	}
	else if(row == 1)
	{
		if(status == 0)
		{
			rolling1 = 0;
		}
		else
		{
			rolling1 = 1;
		}
	}
}

/** ===========================================================================
 *   @n@b print(string[])
 *
 *   @b Description
 *   @n Prints a string to the LCD
 *
 *   @b Arguments
 *   @verbatim
 *      char *printString      <- Pointer to the string to be printed
     @endverbatim
 *
 *   <b> Return Value </b>  Returns the number of bytes written to LCD
 *   @li                    strLen   - Length of the string written to LCD
 *
 *  ===========================================================================
 */
int OLED::print(char string[])
{
    int i = 0;

	while(string[i] != '\0')
    {
      if(printchar(string[i]) == 0) {break;}
	  i++;
    }

    return(i);
}

/** ===========================================================================
 *   @n@b write(character)
 *
 *   @b Description
 *   @n Writes a character to the LCD
 *
 *   @b Arguments
 *   @verbatim
 *      char character      <- Character to be printed
     @endverbatim
 *
 *   <b> Return Value </b>  Returns the number of bytes written to LCD
 *   @li                    1   - In case of char only 1 byte is written to LCD
 *
 *  ===========================================================================
 */
void OLED::write(unsigned char byte)
{
	send(0x40,byte);
	totalcols++;
	if(totalcols > 127)
	{
		totalcols = 0;
		send(0x00,0x00);     // Set low column address
		send(0x00,0x10);     // Set high column address
		send(0x00,0xb0+row); // Set page for page 0 to page 5
	}
}

/** ===========================================================================
 *   @n@b clear()
 *
 *   @b Description
 *   @n Clears the LCD screen and positions the cursor in the upper-left corner
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::clear(void)
{
	Int16 i;
	totalcols = 0;
	//This part is to initialize and blank the LCD.
	/* Initialize OLED display */
	send(0x00,0x2e);  // Deactivate Scrolling

    /* Write to page 0 */
    send(0x00,0x00);   // Set low column address
    send(0x00,0x10);   // Set high column address
    send(0x00,0xb0+0); // Set page for page 0 to page 5

    for(i=0;i<128;i++)
    {
    	send(0x40,0x00);
    }

    /* Write to page 1*/
    send(0x00,0x00);   // Set low column address
    send(0x00,0x10);   // Set high column address
    send(0x00,0xb0+1); // Set page for page 0 to page 5

    for(i=0;i<128;i++)
    {
    	send(0x40,0x00);
    }

	/* Set cursor to upper left corner */
    send(0x00,0x00);   // Set low column address
    send(0x00,0x10);   // Set high column address
    send(0x00,0xb0+1); // Set page for page 0 to page 5
	row = 0;
}

/** ===========================================================================
 *   @n@b clear(page)
 *
 *   @b Description
 *   @n Clears the LCD screen and positions the cursor in the upper-left corner
 *
 *   @b Arguments
 *   @verbatim
 *      int page    <- Page number
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::clear(int page)
{
	Int16 i;
	totalcols = 0;
	if(page == 0)
	{
		//This part is to initialize and blank the LCD.
		/* Initialize OLED display */
		send(0x00,0x2e);  // Deactivate Scrolling

		/* Write to page 0 */
		send(0x00,0x00);   // Set low column address
		send(0x00,0x10);   // Set high column address
		send(0x00,0xb0+1); // Set page for page 0 to page 5

		for(i=0;i<128;i++)
		{
			send(0x40,0x00);
		}
	}
	else if(page == 1)
	{
	   /* Write to page 1*/
		send(0x00,0x00);   // Set low column address
		send(0x00,0x10);   // Set high column address
		send(0x00,0xb0+0); // Set page for page 0 to page 5

		for(i=0;i<128;i++)
		{
			send(0x40,0x00);
		}
	}
	if(row == 0)
	{
		/* Write to page 0 */
		send(0x00,0x00);   // Set low column address
		send(0x00,0x10);   // Set high column address
		send(0x00,0xb0+0); // Set page for page 0 to page 5
	}

}

/** ===========================================================================
 *   @n@b scrollDisplayLeft()
 *
 *   @b Description
 *   @n Scrolls the contents of the display (text and cursor) to the left
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::scrollDisplayLeft(void)
{

	Uint16 cmd[10]; // For multibyte commands

    // These commands scroll the display without changing the RAM
    /* Set vertical and horizontal scrolling */
    cmd[0] = 0x00;
    cmd[1] = 0x27;  // Vertical and Right Horizontal Scroll 26 = left, 27 = right, 29 = vl, 2A = vr
    cmd[2] = 0x00;  // Dummy byte
    cmd[3] = 0x00;  // Define start page address
    cmd[4] = 0x00;  // Set time interval between each scroll step as 5 frames
    cmd[5] = 0x01;  // Define end page address
    cmd[6] = 0x00;  // Dummy byte
    cmd[7] = 0xFF;  // Dummy byte
    multiSend(cmd, 8);
    send(0x00,0x2f);
}

/** ===========================================================================
 *   @n@b scrollDisplayLeft()
 *
 *   @b Description
 *   @n Scrolls the contents of a particular line, of the display (text and
 *      cursor) to the left
 *
 *   @b Arguments
 *   @verbatim
 *     int line      <- Line number
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::scrollDisplayLeft(int line)
{

	Uint16 cmd[10]; // For multibyte commands

    if ((0 == line) || (1 == line))
    {
        // These commands scroll the display without changing the RAM
        /* Set vertical and horizontal scrolling */
        cmd[0] = 0x00;
        cmd[1] = 0x27;  // Vertical and Right Horizontal Scroll 26 = left, 27 = right, 29 = vl, 2A = vr
        cmd[2] = 0x00;  // Dummy byte
        cmd[3] = !line; // Define start page address
        cmd[4] = 0x00;  // Set time interval between each scroll step as 5 frames
        cmd[5] = !line; // Define end page address
        cmd[6] = 0x00;  // Dummy byte
        cmd[7] = 0xFF;  // Dummy byte
        multiSend(cmd, 8);
        send(0x00,0x2f);
	}
}

/** ===========================================================================
 *   @n@b autoscroll()
 *
 *   @b Description
 *   @n Turns on automatic scrolling of the LCD
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::autoscroll(void)
{
	Uint16 cmd[10];    // For multibyte commands

    /* Set vertical and horizontal scrolling */
    cmd[0] = 0x00;
    cmd[1] = 0x2A;  // Vertical and Right Horizontal Scroll 26 = left, 27 = right, 29 = vl, 2A = vr
    cmd[2] = 0x00;  // Dummy byte
    cmd[3] = 0x00;  // Define start page address
    cmd[4] = 0x00;  // Set time interval between each scroll step as 5 frames
    cmd[5] = 0x01;  // Define end page address
    cmd[6] = 0x01;  // Vertical scrolling offset
    multiSend(cmd, 7);
    send(0x00,0x2f);

    /* Keep first 8 rows from vertical scrolling  */
    cmd[0] = 0x00;
    cmd[1] = 0xa3;  // Set Vertical Scroll Area
    cmd[2] = 0x08;  // Set No. of rows in top fixed area
    cmd[3] = 0x08;  // Set No. of rows in scroll area
    multiSend(cmd, 4);
}

/** ===========================================================================
 *   @n@b autoscroll()
 *
 *   @b Description
 *   @n Turns off automatic scrolling of the LCD
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::noAutoscroll(void)
{
	send(0x40,0x00);
	send(0x40,0x00);  // 2 Spaces
    send(0x00,0x2e);  // Deactivate Scrolling
}

/** ===========================================================================
 *   @n@b scrollDisplayRight()
 *
 *   @b Description
 *   @n Scrolls the contents of the display (text and cursor) to the right
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::scrollDisplayRight(void)
{
	Uint16 cmd[10];    // For multibyte commands

    /* Set horizontal scrolling */
    cmd[0] = 0x00;
    cmd[1] = 0x26;  // Vertical and Left Horizontal Scroll 26 = left, 27 = right, 29 = vl, 2A = vr
    cmd[2] = 0x00;  // Dummy byte
    cmd[3] = 0x00;  // Define start page address
    cmd[4] = 0x00;  // Set time interval between each scroll step as 5 frames
    cmd[5] = 0x01;  // Define end page address
    cmd[6] = 0x00;  // Dummy byte
    cmd[7] = 0xFF;  // Dummy byte
    multiSend(cmd, 8);
    send(0x00,0x2f);
}

/** ===========================================================================
 *   @n@b scrollDisplayRight(line)
 *
 *   @b Description
 *   @n Scrolls the contents of a particular line, of the display (text and
 *      cursor) to the right
 *
 *   @b Arguments
 *   @verbatim
 *     int line      <- Line number
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::scrollDisplayRight(int line)
{
	Uint16 cmd[10];    // For multibyte commands

    if ((0 == line) || (1 == line))
    {
        /* Set horizontal scrolling */
        cmd[0] = 0x00;
        cmd[1] = 0x26;  // Vertical and Left Horizontal Scroll 26 = left, 27 = right, 29 = vl, 2A = vr
        cmd[2] = 0x00;  // Dummy byte
        cmd[3] = !line; // Define start page address
        cmd[4] = 0x00;  // Set time interval between each scroll step as 5 frames
        cmd[5] = !line; // Define end page address
        cmd[6] = 0x00;  // Dummy byte
        cmd[7] = 0xFF;  // Dummy byte
        multiSend(cmd, 8);
        send(0x00,0x2f);
	}
}

/** ===========================================================================
 *   @n@b noDisplay()
 *
 *   @b Description
 *   @n Turns off the LCD display
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::noDisplay()
{
    send(0x00,0xae); // Turn off oled panel
}

/** ===========================================================================
 *   @n@b display()
 *
 *   @b Description
 *   @n Turns on the LCD display
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::display()
{
    send(0x00,0xaf); // Turn on oled panel
}

/** ===========================================================================
 *   @n@b print(character)
 *
 *   @b Description
 *   @n Prints a character to the LCD
 *
 *   @b Arguments
 *   @verbatim
 *      char character      <- Character to be printed
     @endverbatim
 *
 *   <b> Return Value </b>  Returns the number of bytes written to LCD
 *   @li                    1   - In case of char only 1byte is written to LCD
 *
 *  ===========================================================================
 */
int OLED::print(char character)
{
    Int16 numChars;
    numChars = disp.printchar(character);

    return(numChars);
}

/** ===========================================================================
 *   @n@b print(value)
 *
 *   @b Description
 *   @n Prints a value to the LCD
 *
 *   @b Arguments
 *   @verbatim
 *      long value      <- Value to be printed
     @endverbatim
 *
 *   <b> Return Value </b>  Returns the number of bytes written to LCD
 *   @li                    strLen   - Length of the string written to LCD
 *
 *  ===========================================================================
 */
int OLED::print(long value)
{
    char   printString[20];
    Int16  index;
    Int32  modValue;
    Int32  tempValue;

    index     = 0;
    modValue  = 1;
    tempValue = value;

    while (tempValue >= 10)
    {
        tempValue /= 10;
        modValue *= 10;
    }

    while ((value > 0) || (modValue > 0))
    {
        printString[index] = ((value / modValue) + '0');
        value %= modValue;
        modValue /= 10;
        index++;
    }
    printString[index] = '\0';

    disp.print(printString);

    return(index);
}

/**
 *
 *  convertDecToBinOct(value, convString, base)
 *
 *  API to Convert a Decimal value to either Binary or Octal Form
 *
 *  int value        <-- The integer value that is to be converted
 *  char *convString <-- Character String to hold the converted value
 *  int base         <-- Indicates the base to which the decimal value needs to be converted
 */
static void convertDecToBinOct (long value, char *convString, int base)
{
    int  index;
    int  strLength;
    char tempChar;

    if (value != 0)
    {
        index = 0;
        while (value > 0)
        {
            convString[index] = (value % base) + '0';

            value /= base;
            index++;
        }
        convString[index] = '\0';

        strLength = index;
        index     = 0;
        while (index < (strLength / 2))
        {
            tempChar = convString[index];
            convString[index] = convString[strLength - index - 1];
            convString[strLength - index - 1] = tempChar;
            index++;
        }
    }
    else
    {
        convString[0] = '0';
        convString[1] = '\0';
    }
}

/**
 *
 *  convertDecToBinOct(value, convString, base)
 *
 *  API to Convert a Decimal value to Hexadecimal Form
 *
 *  int value        <-- The integer value that is to be converted
 *  char *convString <-- Character String to hold the converted hexadecimal value
 */
static void convertDecToHex (long value, char *convString)
{
    int  index;
    int  tempvalue;
    char tempChar;
    int  strLength;

    if (value != 0)
    {
        index = 0;
        while (value > 0)
        {
            tempvalue = (value % 16);

            if ((tempvalue >= 0) && (tempvalue <= 9))
            {
                convString[index] = tempvalue + '0';
            }
            else /* 'A' to 'F' Hexadecimal value */
            {
                tempvalue = tempvalue - 10;
                convString[index] = tempvalue + 'A';
            }

            value /= 16;
            index++;
        }
        convString[index] = '\0';

        strLength = index;
        index     = 0;
        while (index < (strLength / 2))
        {
            tempChar = convString[index];
            convString[index] = convString[strLength - index - 1];
            convString[strLength - index - 1] = tempChar;
            index++;
        }

        index = 0;
        strLength += 2;
        convString[strLength] = '\0';
        while (index < strLength) /* Prefixing 0x to the Hexadecimal value */
        {
            convString[strLength - index] = convString[strLength - 2 - index];
            index++;
        }
    }
    else
    {
        convString[2] = '0';
        convString[3] = '\0';
    }

    convString[0] = '0';
    convString[1] = 'x';
}

/** ===========================================================================
 *   @n@b print(value, base)
 *
 *   @b Description
 *   @n Prints a value to the LCD
 *
 *   @b Arguments
 *   @verbatim
 *      long value      <- Value to be printed
 *      int base        <- Base of the value printed
     @endverbatim
 *
 *   <b> Return Value </b>  Returns the number of bytes written to LCD
 *   @li                    strLen   - Length of the string written to LCD
 *
 *  ===========================================================================
 */
int OLED::print(long value, int base)
{
    long           strLen;
    char           printString[20];

    strLen = 0;

    switch (base)
    {
        case BINARY:
            convertDecToBinOct (value, printString, 2);
            break;

        case DECIMAL:
            strLen = this->print(value);
            break;

        case OCTAL:
            convertDecToBinOct (value, printString, 8);
            break;

        case HEXADECIMAL:
            convertDecToHex (value, printString);
            break;

        default:
        	break;
    }

    if (base != DECIMAL)
    {
        strLen = this->print(printString);
    }

    return(strLen);
}

/** ===========================================================================
 *   @n@b resetCursor(line)
 *
 *   @b Description
 *   @n Resets the cursor position to the beginning in a given line
 *
 *   @b Arguments
 *   @verbatim
 *      int line    <- line number
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void OLED::resetCursor(int line)
{
	totalcols = 0;
	if(line == 0)
	{
		/* Write to line 0 */
		send(0x00,0x00);   // Set low column address
		send(0x00,0x10);   // Set high column address
		send(0x00,0xb0+1); // Set page for page 0 to page 5
	}
	else if(line == 1)
	{
	   /* Write to line 1*/
		send(0x00,0x00);   // Set low column address
		send(0x00,0x10);   // Set high column address
		send(0x00,0xb0+0); // Set page for page 0 to page 5
	}
}

