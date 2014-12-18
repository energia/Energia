//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
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

/** @file core.cpp (was ezdsp5535.c)
 *
 *  @brief Board Setup and functions.
 *
 */

#include "core.h"
#include "csl_i2c.h"
#include "tistdtypes.h"

/** I2C address */
#define CSL_I2C_OWN_ADDR		(0x2F)
/** I2C bus frequency */
#define CSL_I2C_BUS_FREQ		(100)
/** IO expander address */
#define CSL_I2C_TCA6416_ADDR	(0x20)

/**
 *  csl_wait(delay)
 *
 *      Wait in a software loop for 'delay' loops.
 *
 *      Uint32 delay  <- Number of delay loops
 */
void csl_wait(Uint32 delay)
{
    volatile Uint32 index;

    for (index = 0; index < delay; index++)
	{
        asm("\tNOP");
	}
}

/**
 *
 *  csl_waitusec(usec)
 *
 *      Wait in a software loop for 'usec' microseconds.
 *      Note: CPU Clock is assumed as 150MHz for C5517 and 100MHz for C5535
 *
 *      Uint32 usec  <- Time in microseconds
 */
void csl_waitusec(Uint32 usec)
{
#ifdef CHIP_C5517
    csl_wait((Uint32)usec * 9);
#else
    csl_wait((Uint32)usec * 6);
#endif
}

/**
 *  csl_init()
 *
 *      Initialize the C5000 board.
 */
Int16 csl_init()
{
    /* Enable clocks to all peripherals */
    CSL_SYSCTRL_REGS->PCGCR1 = 0x0000;
    CSL_SYSCTRL_REGS->PCGCR2 = 0x0000;

	/* Take the CPU and ports out of idle state */
	*(ioport volatile int *)0x0001 = 0x000E;
	asm("\tidle");

    return 0;
}

/**
 *  delay(msecs)
 *
 *      Wait in a software loop for 'msecs' milliseconds.
 *
 *      Uint32 msecs  <- Time in milliseconds
 */
void delay(Uint32 msecs)
{
	csl_waitusec(msecs * 1000);
}

/**
 *
 *  delayMicroseconds(usecs)
 *
 *      Wait in a software loop for 'usecs' microseconds.
 *
 *      Uint32 usecs  <- Time in microseconds
 */
void delayMicroseconds(Uint32 usecs)
{
	csl_waitusec(usecs);
}

/**
 *
 *  delayMilliseconds(msecs)
 *
 *      Wait in a software loop for 'msecs' milliseconds.
 *
 *      Uint32 msecs  <- Time in milliseconds
 */
void delayMilliseconds(Uint32 msecs)
{
	csl_waitusec(msecs * 1000);
}

/**
 *  delaySeconds(sec)
 *
 *      Wait in a software loop for 'sec' seconds.
 *
 *      Uint32 sec  <- Time in seconds
 */
void delaySeconds(Uint32 sec)
{
	csl_waitusec(sec * 1000 * 1000);
}

/**
 *  ioExpander_Setup()
 *
 *      Initialize the IO Expander
 */
Int16 ioExpander_Setup(void)
{
	Int16 		 status;
	CSL_I2cSetup i2cSetup;
    Uint32       sysClk;

    sysClk = getCpuClock();
    sysClk = sysClk / 1000;

	/* Initialize I2C module */
	status = I2C_init(CSL_I2C0);
	if(status != CSL_SOK)
	{
		return(status);
	}

	/* Setup I2C module */
	i2cSetup.addrMode    = CSL_I2C_ADDR_7BIT;
	i2cSetup.bitCount    = CSL_I2C_BC_8BITS;
	i2cSetup.loopBack    = CSL_I2C_LOOPBACK_DISABLE;
	i2cSetup.freeMode    = CSL_I2C_FREEMODE_DISABLE;
	i2cSetup.repeatMode  = CSL_I2C_REPEATMODE_DISABLE;
	i2cSetup.ownAddr     = CSL_I2C_OWN_ADDR;
	i2cSetup.sysInputClk = sysClk;
	i2cSetup.i2cBusFreq  = CSL_I2C_BUS_FREQ;

	status = I2C_setup(&i2cSetup);
	if(status != CSL_SOK)
	{
		return(status);
	}

	return status;
}

/**
 *  ioExpander_Write(port, pin, wValue)
 *
 *      Write a value to a particular pin of a particular port, of the IO
 *      Expander
 *
 *      Uint16 port   <-- Port number of the IO Expander
 *      Uint16 pin    <-- Pin number of the above port
 *      Uint16 wValue <-- Value that is to be written
 */
Int16 ioExpander_Write(Uint16 port, Uint16 pin, Uint16 wValue)
{
	Int16 	 status;
	Uint16 	 i2cWriteBuf[2];
	Uint16 	 i2cReadBuf[1];
	Uint16	 configOld;
	Uint16	 driveOld;
	volatile Uint16 delay;

    /*Read Old Config*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x06; /*Port0 Config Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x07; /*Port1 Config Cmd*/
	}

	for(delay=0; delay<0xFFFF; delay++);

	status = I2C_write(i2cWriteBuf, 1, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
		return(status);
	}

	for(delay=0; delay<0xFFFF; delay++);

	status = I2C_read(i2cReadBuf, 1, CSL_I2C_TCA6416_ADDR,
	                  i2cWriteBuf, 1, TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
	                  CSL_I2C_MAX_TIMEOUT, FALSE);
	if(status != CSL_SOK)
	{
		return(status);
	}

	configOld = i2cReadBuf[0];

    /*Read Old Drive*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x02; /*Port0 Output Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x03; /*Port1 Output Cmd*/
	}

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_write(i2cWriteBuf, 1, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
		return(status);
	}

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_read(i2cReadBuf, 1, CSL_I2C_TCA6416_ADDR,
	                  i2cWriteBuf, 1, TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
	                  CSL_I2C_MAX_TIMEOUT, FALSE);
	if(status != CSL_SOK)
	{
		return(status);
	}

	driveOld = i2cReadBuf[0];

    /*Configure pin as OUT*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x06; /*Port0 Config Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x07; /*Port1 Config Cmd*/
	}
	i2cWriteBuf[1] = configOld;
	i2cWriteBuf[1] &= (~((Uint16)0x1 << pin)); /*1-IN, 0-OUT*/;

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_write(i2cWriteBuf, 2, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
		return(status);
	}

    /*Drive pin*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x02; /*Port0 Output Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x03; /*Port1 Output Cmd*/
	}
	i2cWriteBuf[1] = driveOld;
	if(wValue)
	{
		i2cWriteBuf[1] |= ((Uint16)0x1 << pin);
	}
	else
	{
		i2cWriteBuf[1] &= (~((Uint16)0x1 << pin));
	}

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_write(i2cWriteBuf, 2, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
		return(status);
	}

	return status;
}

/**
 *  ioExpander_Read(port, pin, &rValue)
 *
 *      Read a value from a particular pin of a particular port, of the IO
 *      Expander
 *
 *      Uint16 port   <-- Port number of the IO Expander
 *      Uint16 pin    <-- Pin number of the above port
 *      Uint16 rValue <-- Variable to hold the Value that will be read
 */
CSL_Status ioExpander_Read(Uint16 port, Uint16 pin, Uint16 *rValue)
{
	CSL_Status 	status;
	Uint16		i2cWriteBuf[2];
	Uint16 		i2cReadBuf[1];
	Uint16		configOld;
	volatile    Uint16 delay;

    /*Read Old Config*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x06; /*Port0 Config Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x07; /*Port1 Config Cmd*/
	}

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_read(i2cReadBuf, 1, CSL_I2C_TCA6416_ADDR,
	                  i2cWriteBuf, 1, TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
	                  CSL_I2C_MAX_TIMEOUT, FALSE);
	if(status != CSL_SOK)
	{
#if 0
		printf("I2C Read Failed!!\n");
#endif
		return(status);
	}

	configOld = i2cReadBuf[0];

    /*Read pin*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x00; /*Port0 Input Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x01; /*Port1 Input Cmd*/
	}

	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_read(i2cReadBuf, 1, CSL_I2C_TCA6416_ADDR,
	                  i2cWriteBuf, 1, TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
	                  CSL_I2C_MAX_TIMEOUT, FALSE);
	if(status != CSL_SOK)
	{
#if 0
		printf("I2C Read Failed!!\n");
#endif
		return(status);
	}

	*rValue = (i2cReadBuf[0] >> pin) & 0x1;

	/*Set new config*/
	if(0 == port)
	{
		i2cWriteBuf[0] = 0x06; /*Port0 Config Cmd*/
	}
	else if(1 == port)
	{
		i2cWriteBuf[0] = 0x07; /*Port1 Config Cmd*/
	}

	i2cWriteBuf[1] = configOld;
	for(delay=0; delay<0xFFFF; delay++);
	status = I2C_write(i2cWriteBuf, 2, CSL_I2C_TCA6416_ADDR,
						TRUE, ((CSL_I2C_START) | (CSL_I2C_STOP)),
						CSL_I2C_MAX_TIMEOUT);
	if(status != CSL_SOK)
	{
#if 0
		printf("I2C Write Failed!!\n");
#endif
		return(status);
	}

	return status;
}

/**
 *  xfOn()
 *
 *     API to switch ON the XF LED
 */
void xfOn()
{
    asm("	BIT(ST1, #13) = #1");
}

/**
 *  xfOn()
 *
 *     API to switch OFF the XF LED
 */
void xfOff()
{
    asm("	BIT(ST1, #13) = #0");
}

/**
 *  boot_update()
 *
 *     API to update the boatloader on the SD Card
 */
void boot_update()
{
    updateBootLoader();
}

/** ===========================================================================
 *   @n@b RTC_getAlarm
 *
 *   @b Description
 *   @n It get the RTC registers value related to Alarm Field.
 *
 *   @b Arguments
 *   @verbatim
            pGetRtcAlarm      Pointer to RTC Alarm structure.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK
 *   @li                    CSL_ESYS_INVPARAMS  - Congig Parameter is invalid.
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Passed Parameter will be updated with RTC Alarm related Registers value.
 *
 *   @b Example
 *   @verbatim

            CSL_RtcAlarm       pGetRtcAlarm;
            CSL_status         status;

            status = RTC_getAlarm(&pGetRtcAlarm);
            ...
     @endverbatim
 *  ===========================================================================
 */
CSL_Status RTC_getAlarm (CSL_RtcAlarm     *pGetRtcAlarm)
{
    if (NULL == pGetRtcAlarm)
    {
		return CSL_ESYS_INVPARAMS;
    }
    else
    {
        pGetRtcAlarm->mSecs = RTC_bcdToDec(CSL_RTC_REGS->RTCMILA);
        pGetRtcAlarm->secs  = RTC_bcdToDec(CSL_RTC_REGS->RTCSECA);
        pGetRtcAlarm->mins  = RTC_bcdToDec(CSL_RTC_REGS->RTCMINA);
        pGetRtcAlarm->hours = RTC_bcdToDec(CSL_RTC_REGS->RTCHOURA);
        pGetRtcAlarm->day   = RTC_bcdToDec(CSL_RTC_REGS->RTCDAYA);
        pGetRtcAlarm->month = RTC_bcdToDec(CSL_RTC_REGS->RTCMONTHA);
        pGetRtcAlarm->year  = RTC_bcdToDec(CSL_RTC_REGS->RTCYEARA);

		return CSL_SOK;
    }
}

/**
 *  SPI_setLoopBackMode()
 *
 *     API to set the Loop back mode value of the SPI Peripheral
 */
void SPI_setLoopBackMode(int value)
{
#ifdef CHIP_C5517
    CSL_FINS(CSL_SPI_REGS->SPIDCRU, SPI_SPIDCRU_LPBK, value);
#else
    CSL_FINS(CSL_SPI_REGS->SPIDCR2, SPI_SPIDCR2_LPBK, value);
#endif
}

/**
    createBuffer(unsigned short size_bytes)

    Function to create a buffer dynamically
    Note: Any buffer created dynamically should be deleted using
    deleteBuffer() when the buffer is no longer needed

	unsigned short size_bytes <- size of buffer
  */
void* createBuffer(unsigned short size_bytes)
{
    return(malloc(size_bytes));
}

/**
    createBuffer(unsigned short size_bytes)

    Function to delete a buffer dynamically

	void *buf <- buffer pointer
  */
void deleteBuffer(void *buf)
{
    free(buf);
}

/**
    setSarGPODir(CSL_SarHandleObj *SarHandle,
                  int              gpoPinNumber,
                  int              direction)

    Function to set a particular GPO pin direction

	CSL_SarHandleObj *SarHandle   <- SAR handle
    int              gpoPinNumber <- GPIO pin number
    int              direction    <- GPIO direction
  */
void setSarGPODir(CSL_SarHandleObj *SarHandle,
                  int              gpoPinNumber,
                  int              direction)
{
	Uint16 valueToWrite;

	if (direction == 1)
	{
		SarHandle->baseAddr->SARGPOCTRL |= (1 << (gpoPinNumber + 4));
	}
	else
	{
		valueToWrite = ~(1 << (gpoPinNumber + 4));
		SarHandle->baseAddr->SARGPOCTRL &= valueToWrite;
	}
}

/**
    void setSarGPOValue(CSL_SarHandleObj *SarHandle,
                    int              gpoPinNumber,
                    int              value)

    Function to set a particular GPO pin value

	CSL_SarHandleObj *SarHandle   <- SAR handle
    int              gpoPinNumber <- GPIO pin number
    int              value        <- value to be set
  */
void setSarGPOValue(CSL_SarHandleObj *SarHandle,
                    int              gpoPinNumber,
                    int              value)
{
	Uint16 valueToWrite;

	if (value == 1)
	{
		SarHandle->baseAddr->SARGPOCTRL |= (1 << gpoPinNumber);
	}
	else
	{
		valueToWrite = ~(1 << gpoPinNumber);
		SarHandle->baseAddr->SARGPOCTRL &= valueToWrite;
	}
}

/**
 *  \brief  Function to calculate the clock at which system is running
 *
 *  \return   System clock value in KHz
 */
#if (defined(CHIP_C5505_C5515) || defined(CHIP_C5504_C5514))

Uint32 getCpuClock(void)
{
	Bool      pllRDBypass;
	Bool      pllOutDiv;
	Uint32    sysClk;
	Uint16    pllM;
	Uint16    pllRD;
	Uint16    pllOD;

	pllM = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR1, SYS_CGCR1_M);

	pllRD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDRATIO);
	pllOD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_ODRATIO);

	pllRDBypass = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDBYPASS);
	pllOutDiv   = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIVEN);

	if(CSL_FEXT(CSL_SYSCTRL_REGS->CCR2, SYS_CCR2_CLKSELSTAT) == CSL_SYS_CCR2_CLKSELSTAT_CLKIN)
	{
		sysClk = PLL_SRC_CLKIN;
	}
	else
	{
		sysClk = PLL_SRC_RTCIN;
	}

	if (0 == pllRDBypass)
	{
		sysClk = sysClk/(pllRD + 4);
	}

	sysClk = (sysClk * (pllM + 4));

	if (1 == pllOutDiv)
	{
		sysClk = sysClk/(pllOD + 1);
	}

	/* Return the value of system clock in KHz */
	return(sysClk/1000);
}

#elif (defined(CHIP_C5517))

Uint32 getCpuClock(void)
{
	Uint32    sysClk;
	float    Multiplier;
	Uint16    OD;
	Uint16    OD2;
	Uint16    RD, RefClk;
	Uint32	  temp1, temp2, temp3, vco;

	temp2 =  PLL_CNTL2;
	temp3 =  (temp2 & 0x8000) <<1 ;
	temp1 = temp3 + PLL_CNTL1;
	Multiplier = temp1/256 +1;
	RD = (PLL_CNTL2 & 0x003F) ;

	RefClk = 12000/(RD+1);

	vco = Multiplier * (Uint32)RefClk;

	OD = (PLL_CNTL4 & 0x7);

	sysClk = vco/(OD+1);

	OD2 = ((PLL_CNTL4 >> 10) & 0x1F) ;

	if (PLL_CNTL3 & 0x8000)	// PLL Bypass
		sysClk = RefClk;
	else
		sysClk = vco/(OD+1);

	if ((PLL_CNTL4 & 0x0020) == 0)	/* OutDiv2 */
		sysClk = sysClk / ( 2*(OD2+1));

	/* Return the value of system clock in KHz */
	return(sysClk);
}

#else

Uint32 getCpuClock(void)
{
	Bool      pllRDBypass;
	Bool      pllOutDiv;
	Bool      pllOutDiv2;
	Uint32    sysClk;
	Uint16    pllVP;
	Uint16    pllVS;
	Uint16    pllRD;
	Uint16    pllVO;
	Uint16    pllDivider;
	Uint32    pllMultiplier;

	pllVP = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR1, SYS_CGCR1_MH);
	pllVS = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_ML);

	pllRD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDRATIO);
	pllVO = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_ODRATIO);

	pllRDBypass = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDBYPASS);
	pllOutDiv   = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIVEN);
	pllOutDiv2  = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIV2BYPASS);

	pllDivider = ((pllOutDiv2) | (pllOutDiv << 1) | (pllRDBypass << 2));

	if(CSL_FEXT(CSL_SYSCTRL_REGS->CCR2, SYS_CCR2_CLKSELSTAT) == CSL_SYS_CCR2_CLKSELSTAT_CLKIN)
	{
		pllMultiplier = ((Uint32)PLL_SRC_CLKIN * ((pllVP << 2) + pllVS + 4));
	}
	else
	{
		pllMultiplier = ((Uint32)PLL_SRC_RTCIN * ((pllVP << 2) + pllVS + 4));
	}

	switch(pllDivider)
	{
		case CSL_PLL_DIV_000:
		case CSL_PLL_DIV_001:
			sysClk = pllMultiplier / (pllRD + 4);
		break;

		case CSL_PLL_DIV_002:
			sysClk = pllMultiplier / ((pllRD + 4) * (pllVO + 4) * 2);
		break;

		case CSL_PLL_DIV_003:
			sysClk = pllMultiplier / ((pllRD + 4) * 2);
		break;

		case CSL_PLL_DIV_004:
		case CSL_PLL_DIV_005:
			sysClk = pllMultiplier;
		break;

		case CSL_PLL_DIV_006:
			sysClk = pllMultiplier / ((pllVO + 4) * 2);
		break;

		case CSL_PLL_DIV_007:
			sysClk = pllMultiplier / 2;
		break;
	}

	/* Return the value of system clock in KHz */
	return(sysClk/1000);
}
#endif

/**
 *  SAR_A2DMeasParamSet (hSar, param, chanNo)
 *
 *      Function to initialize the device registers according to the type of
 *      A/D conversion and the channel number.
 *
 *      SAR_Handle       hSar   <-- Pointer to SAR Object structure
 *      CSL_SARMeasParam param  <-- Enum variable for type of A/D conversion
 *      CSL_SarChanSel   chanNo <-- Pointer to the channel number
 */
Int16 setSarA2DMeasParam (SAR_Handle       hSar,
                          CSL_SARMeasParam param,
                          CSL_SarChanSel   chanNo)
{
    if ((NULL == hSar)             ||
        (param != CSL_KEYPAD_MEAS) ||
        (chanNo < CSL_SAR_CHAN_0)  ||
        (chanNo >= CSL_SAR_NO_CHAN))
    {
        return (CSL_ESYS_BADHANDLE);
    }

#if (defined(CHIP_C5517))
	CSL_FINS (hSar->baseAddr->SARCTRL, SAR_SARCTRL_CHSEL, chanNo);
	/* Enabling SAR A/D AVddMeas bit */
	CSL_FINST (hSar->baseAddr->SARPINCTRL, SAR_SARPINCTRL_AVDDMEAS, CLEAR);

	/* Disabling SAR A/D GndSwOn bit */
	CSL_FINST (hSar->baseAddr->SARPINCTRL, SAR_SARPINCTRL_GNDON, CLEAR);
	/* Disabling SAR A/D Half bit */
	CSL_FINST (hSar->baseAddr->SARPINCTRL, SAR_SARPINCTRL_HALF, CLEAR);
#else
	CSL_FINS (hSar->baseAddr->SARCTRL, ANACTRL_SARCTRL_CHSEL, chanNo);
	/* Enabling SAR A/D AVddMeas bit */
	CSL_FINST (hSar->baseAddr->SARPINCTRL, ANACTRL_SARPINCTRL_AVDDMEAS, CLEAR);

	/* Disabling SAR A/D GndSwOn bit */
	CSL_FINST (hSar->baseAddr->SARPINCTRL, ANACTRL_SARPINCTRL_GNDON, CLEAR);
	/* Disabling SAR A/D Half bit */
	CSL_FINST (hSar->baseAddr->SARPINCTRL, ANACTRL_SARPINCTRL_HALF, CLEAR);
#endif

    return (CSL_SOK);
}

/**
 *  Function to copy one buffer to another buffer of type int
 *
 *  input    Input buffer
 *  output   Output buffer
 *  size     Size of the buffer in words
 */
void copyShortBuf(void *input, void *output, unsigned short size)
{
	int  *src;
	int  *dest;
	unsigned short index;

	src  = (int*)input;
	dest = (int*)output;

    for (index = 0; index < size; index++)
    {
        dest[index] = src[index];
    }
}

/**
 *  Function to copy one buffer to another buffer of type long
 *
 *  input    Input buffer
 *  output   Output buffer
 *  size     Size of the buffer in double words
 */
void copyLongBuf(void *input, void *output, unsigned short size)
{
	long *src;
	long *dest;
	unsigned short index;

	src  = (long*)input;
	dest = (long*)output;

    for (index = 0; index < size; index++)
    {
        dest[index] = src[index];
    }
}

/**
 *  Function to fill data buffer of type int with given value
 *
 *  buf    Data buffer pointer
 *  value  Value to be filled in buffer
 *  size   Size of the buffer in words
 */
void fillShortBuf(void *buf, int value, unsigned short size)
{
	int  *dataBuf;
	unsigned short index;

	dataBuf = (int*)buf;

    for (index = 0; index < size; index++)
    {
        dataBuf[index] = value;
    }
}

/**
 *  Function to fill data buffer of type long with given value
 *
 *  buf    Data buffer pointer
 *  value  Value to be filled in buffer
 *  size   Size of the buffer in double words
 */
void fillLongBuf(void *buf, long value, unsigned short size)
{
	long *dataBuf;
	unsigned short index;

	dataBuf = (long*)buf;

    for (index = 0; index < size; index++)
    {
        dataBuf[index] = value;
    }
}
