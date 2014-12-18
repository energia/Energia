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
/** @file Audio.cpp
 *
 *  @brief Audio implementation
 *
 */

#include "Audio.h"

/**
 * Class identifier declaration
 */
AudioClass AudioC;

#pragma DATA_SECTION("audio_buffers");
#pragma DATA_ALIGN(1024);//I2S_DMA_BUF_LEN);
/** DMA left channel buffer */
//Uint16 i2sDmaLeftBuff1[2][I2S_DMA_BUF_LEN];
Uint16 **i2sDmaLeftBuff1;

#pragma DATA_SECTION("audio_buffers");
#pragma DATA_ALIGN(1024);//I2S_DMA_BUF_LEN);
/** DMA right channel buffer */
//Uint16 i2sDmaRightBuff1[2][I2S_DMA_BUF_LEN];
Uint16 **i2sDmaRightBuff1;

#pragma DATA_SECTION("audio_buffers");
#pragma DATA_ALIGN(1024);//I2S_DMA_BUF_LEN);
/** DMA left channel buffer 2 */
//Uint16 i2sDmaLeftBuff2[2][I2S_DMA_BUF_LEN];
Uint16 **i2sDmaLeftBuff2;
#pragma DATA_SECTION("audio_buffers");
#pragma DATA_ALIGN(1024);//I2S_DMA_BUF_LEN);
/** DMA right channel buffer 2 */
//Uint16 i2sDmaRightBuff2[2][I2S_DMA_BUF_LEN];
Uint16 **i2sDmaRightBuff2;

/** Defining the static variables */
int AudioClass::isInitialized = 0;

/** CODEC configurations to set Sampling Rate as 8KHz */
static const Uint16 CodecConfig_SamplingRate_8k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0xA1},     // p & r values
    {6,  0x07},     // j value
    {7,  0x06},     // D (MSB) value
    {8,  0x90},     // D (LSB) value
    {11, 0x86},     // NDAC value
    {12, 0x87},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x86},     // NADC value
    {19, 0x87},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0x9C},     // BCLK value
};

/** CODEC configurations to set Sampling Rate as 11.05KHz */
static const Uint16 CodecConfig_SamplingRate_11k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0xA1},     // p & r values
    {6,  0x07},     // j value
    {7,  0x02},     // D (MSB) value
    {8,  0x30},     // D (LSB) value
    {11, 0x85},     // NDAC value
    {12, 0x86},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x85},     // NADC value
    {19, 0x86},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0x98},     // BCLK value
};

/** CODEC configurations to set Sampling Rate as 12KHz */
static const Uint16 CodecConfig_SamplingRate_12k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0x91},     // p & r values
    {6,  0x07},     // j value
    {7,  0x06},     // D (MSB) value
    {8,  0x90},     // D (LSB) value
    {11, 0x87},     // NDAC value
    {12, 0x88},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x87},     // NADC value
    {19, 0x88},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0xA0},     // BCLK value
};

/** CODEC configurations to set Sampling Rate as 16KHz */
static const Uint16 CodecConfig_SamplingRate_16k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0x91},     // p & r values
    {6,  0x07},     // j value
    {7,  0x06},     // D (MSB) value
    {8,  0x90},     // D (LSB) value
    {11, 0x86},     // NDAC value
    {12, 0x87},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x86},     // NADC value
    {19, 0x87},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0x9C},     // BCLK value
};

/** CODEC configurations to set Sampling Rate as 22.05KHz */
static const Uint16 CodecConfig_SamplingRate_22k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0x91},     // p & r values
    {6,  0x07},     // j value
    {7,  0x02},     // D (MSB) value
    {8,  0x30},     // D (LSB) value
    {11, 0x85},     // NDAC value
    {12, 0x86},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x85},     // NADC value
    {19, 0x86},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0x98},     // BCLK value
};

/** CODEC configurations to set Sampling Rate as 24KHz */
static const Uint16 CodecConfig_SamplingRate_24k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0x91},     // p & r values
    {6,  0x07},     // j value
    {7,  0x06},     // D (MSB) value
    {8,  0x90},     // D (LSB) value
    {11, 0x84},     // NDAC value
    {12, 0x87},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x84},     // NADC value
    {19, 0x87},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0x9C},     // BCLK value
};

/** CODEC configurations to set Sampling Rate as 32KHz */
static const Uint16 CodecConfig_SamplingRate_32k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0x91},     // p & r values
    {6,  0x07},     // j value
    {7,  0x06},     // D (MSB) value
    {8,  0x90},     // D (LSB) value
    {11, 0x83},     // NDAC value
    {12, 0x87},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x83},     // NADC value
    {19, 0x87},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0x9C},     // BCLK value
};

/** CODEC configurations to set Sampling Rate as 44.1KHz */
static const Uint16 CodecConfig_SamplingRate_44k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0x91},     // p & r values
    {6,  0x07},     // j value
    {7,  0x02},     // D (MSB) value
    {8,  0x30},     // D (LSB) value
    {11, 0x85},     // NDAC value
    {12, 0x83},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x85},     // NADC value
    {19, 0x83},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0x8C},     // BCLK value
};

/** CODEC configurations to set Sampling Rate as 48KHz */
static const Uint16 CodecConfig_SamplingRate_48k[][2] = {
    {0,  0x00},     // Select Page 0
    {5,  0x91},     // p & r values
    {6,  0x07},     // j value
    {7,  0x06},     // D (MSB) value
    {8,  0x90},     // D (LSB) value
    {11, 0x82},     // NDAC value
    {12, 0x87},     // MDAC value
    {13, 0x00},     // DOSR (MSB) value
    {14, 0x80},     // DPSR (LSB) value
    {18, 0x82},     // NADC value
    {19, 0x87},     // MADC value
    {20, 0x80},     // AOSR (LSB) value
    {30, 0x9C},     // BCLK value
};

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

    if ((data != NULL)  && (quantity != 0))
    {
        status = Wire.beginTransmission(address);
        if (status == CSL_SOK)
        {
            status = Wire.write((unsigned int*)data, (unsigned int)quantity);
            if (status == quantity)
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

    csl_waitusec(0xFFF);

    return (status);
}

/** ===========================================================================
 *   @n@b rset
 *
 *   @b Description
 *   @n Function to send commands to codec.
 *
 *   @b Arguments
 *   @verbatim
 *      regnum    - Codec register number
 *      regval    - Value to be written
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - writes are successful
 *   @li                    CSL_ESYS_FAIL       - writes are not successful
 *
 *  ===========================================================================
 */
int AudioClass::rset(Uint16 regnum, Uint16 regval)
{
    CSL_Status status;

    Uint16 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Device Register
    cmd[1] = regval;                // 8-bit Register Data

    status = writeI2C(I2C_CODEC_ADDR, cmd, 2);

    return (status);
}

int readI2C(Uint16 address, Uint16 regnum, Uint16 *data, Uint16 quantity) //more general purpose I2C Readback function.
{
    CSL_Status status;
    Uint16     i2cWriteBuf[2];
    i2cWriteBuf[0] = regnum;

    status = Wire.requestFrom(address, quantity, (unsigned int *)i2cWriteBuf, 1);
    
    if (status != CSL_SOK) //check for bad transmission
    {
        Wire.endTransmission();
        Wire.begin();
        return (status);
    }

    for(int i = 0; (i < quantity) && Wire.available(); i++)
    {
      int value = Wire.read();
      data[i] = value;
    }
    return (status);
}

int AudioClass::rget( Uint16 page, Uint16 regnum, Uint16 *regval) //AIC3204/6 specific register readback function.
{
    Wire.endTransmission();
    Wire.begin();
    CSL_Status status;

    Uint16 cmd;
 
    rset(0,page); //switch to the selected page.

    status = readI2C(I2C_CODEC_ADDR, regnum, regval, 1); //I2C_CODEC_ADDR

    return (status);
}

int AudioClass::rset24bit( Uint16 regnum, Uint32 regval )
{
    CSL_Status status;

    status |= rset(regnum + 0, (regval >> 16) & 0xFF);
    status |= rset(regnum + 1, (regval >>  8) & 0xFF);
    status |= rset(regnum + 2, regval & 0xFF);
    
    return (status);
}


/** ===========================================================================
 *   @n@b Audio
 *
 *   @b Description
 *   @n Function initializes Audio Module.
 *
 *      This function is for enabling the audio loopback for routing data received
 *      from audio input to the audio output without much processing of the audio
 *      data received. Calling this function enables audio library to use same
 *      data buffers for audio input and output channels. While audio input
 *      process is filling one buffer, audio output process will empty other buffer.
 *      Using this function for audio module configuration is recommended for the
 *      applications which requires little or no processing of the audio input
 *      data. Calling this function requires NO buffer copying in the DMA ISR
 *      for routing the audio input data to audio output which will be taken care
 *      by audio library internally.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Initializations are successful
 *   @li                    CSL_ESYS_FAIL       - Initializations are not successful
 *
 *  ===========================================================================
 */
int AudioClass::Audio(void)
{
    CSL_Status status;
    
    bufferSize = I2S_DMA_BUF_LEN;
    
    i2sDmaLeftBuff1 = new Uint16*[2];
    i2sDmaRightBuff1 = new Uint16*[2];
    i2sDmaLeftBuff2 = new Uint16*[2];
    i2sDmaRightBuff2 = new Uint16*[2];
    
    i2sDmaLeftBuff1[0] = new Uint16[bufferSize];
    i2sDmaLeftBuff1[1] = new Uint16[bufferSize];
    i2sDmaRightBuff1[0] = new Uint16[bufferSize];
    i2sDmaRightBuff1[1] = new Uint16[bufferSize];
    i2sDmaLeftBuff2[0] = new Uint16[bufferSize];
    i2sDmaLeftBuff2[1] = new Uint16[bufferSize];
    i2sDmaRightBuff2[0] = new Uint16[bufferSize];
    i2sDmaRightBuff2[1] = new Uint16[bufferSize];
    
    status = CSL_SOK;

    if (!this->isInitialized)
    {
    /* Initialize the DMA transfer buffers */
        audioOutLeft[0] = &i2sDmaLeftBuff1[1][0];
        audioOutLeft[1] = &i2sDmaLeftBuff1[0][0];

        audioOutRight[0] = &i2sDmaRightBuff1[1][0];
        audioOutRight[1] = &i2sDmaRightBuff1[0][0];

        status = init();
    }

    return (status);
}

/** ===========================================================================
 *   @n@b Audio
 *
 *   @b Description
 *   @n Function initializes Audio Module.
 *
 *      This function is for enabling the audio loopback for routing data received
 *      from audio input to the audio output with processing involved on the audio
 *      input data. Calling this function with 'process' parameter set to 'TRUE'
 *      enables audio library to use independent data buffers for audio input and
 *      output channels. Using this function for audio module configuration is
 *      recommended for the applications which requires complex processing of the
 *      audio input data. Calling this function requires copying of the processed
 *      audio data to audio output buffers in the DMA ISR. Application should
 *      read the audio input data on the DMA read right channel interrupt and
 *      copy the processed audio data to audio output data buffers on DMA write
 *      right channel interrupt.
 *
 *      Note: Calling this function with 'process' parameter set to 'FALSE' is
 *      same as calling the function Audio(void).
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Initializations are successful
 *   @li                    CSL_ESYS_FAIL       - Initializations are not successful
 *
 *  ===========================================================================
 */
int AudioClass::Audio(int process, int buffer_size)
{
    CSL_Status status;

    status = CSL_SOK;

    bufferSize = buffer_size;

    i2sDmaLeftBuff1 = new Uint16*[2];
    i2sDmaRightBuff1 = new Uint16*[2];
    i2sDmaLeftBuff2 = new Uint16*[2];
    i2sDmaRightBuff2 = new Uint16*[2];
    
    i2sDmaLeftBuff1[0] = new Uint16[bufferSize];
    i2sDmaLeftBuff1[1] = new Uint16[bufferSize];
    i2sDmaRightBuff1[0] = new Uint16[bufferSize];
    i2sDmaRightBuff1[1] = new Uint16[bufferSize];
    i2sDmaLeftBuff2[0] = new Uint16[bufferSize];
    i2sDmaLeftBuff2[1] = new Uint16[bufferSize];
    i2sDmaRightBuff2[0] = new Uint16[bufferSize];
    i2sDmaRightBuff2[1] = new Uint16[bufferSize]; 
    
    if (!this->isInitialized)
    {
    /* Initialize the DMA transfer buffers */
        if (process == TRUE)
        {
            audioOutLeft[0] = &i2sDmaLeftBuff2[0][0];
            audioOutLeft[1] = &i2sDmaLeftBuff2[1][0];

            audioOutRight[0] = &i2sDmaRightBuff2[0][0];
            audioOutRight[1] = &i2sDmaRightBuff2[1][0];
        }
        else
        {
            audioOutLeft[0] = &i2sDmaLeftBuff1[1][0];
            audioOutLeft[1] = &i2sDmaLeftBuff1[0][0];

            audioOutRight[0] = &i2sDmaRightBuff1[1][0];
            audioOutRight[1] = &i2sDmaRightBuff1[0][0];
        }

        status = init();
    }

    return (status);
}

AudioClass::~AudioClass(void) //destructor
{
    delete i2sDmaLeftBuff1[0];
    delete i2sDmaLeftBuff1[1];
    delete i2sDmaRightBuff1[0];
    delete i2sDmaRightBuff1[1];
    delete i2sDmaLeftBuff2[0];
    delete i2sDmaLeftBuff2[1];
    delete i2sDmaRightBuff2[0];
    delete i2sDmaRightBuff2[1];
    
    delete i2sDmaLeftBuff1;
    delete i2sDmaRightBuff1;
    delete i2sDmaLeftBuff2;
    delete i2sDmaRightBuff2;
}

/** ===========================================================================
 *   @n@b init
 *
 *   @b Description
 *   @n Function initializes Audio Module.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Initializations are successful
 *   @li                    CSL_ESYS_FAIL       - Initializations are not successful
 *
 *  ===========================================================================
 */
int AudioClass::init(void)
{
    CSL_Status status;
    Uint16     index;

    status = CSL_SOK;

    DBG_MSG_PRINT("\n Audio Module Initialization\n");

    activeInBuf  = 0;
    activeOutBuf = 0;

    audioInLeft[0] = &i2sDmaLeftBuff1[0][0];
    audioInLeft[1] = &i2sDmaLeftBuff1[1][0];

    audioInRight[0] = &i2sDmaRightBuff1[0][0];
    audioInRight[1] = &i2sDmaRightBuff1[1][0];

    //status = Wire.begin();  //Note; Wire init will be done in main.cpp
    if (status == CSL_SOK)
    {
        /*    Software Reset */
        rset(0, 0);         // Select Page 0
        rset(1, 0x01);      // Software Reset

        adcPowerDown();
        dacPowerDown();
        adcSetAdaptiveFilterMode(TRUE);
        dacSetAdaptiveFilterMode(TRUE);

        rset(0, 1);         // Select Page 1
        
        /* Disable crude AVDD generation from DVDD */
        rset(1, 0x08);

        rset(2, 0x01);      // enable Analog LDO for C5535 eZdsp

/*    Clock and Interface Settings: Master Mode
 *    running off of 12 MHz MCLK
 *  AIC3204 PLL is not used and turned off
 *  THIS IS NEEDED WHETHER RECORD OR PLAYBACK - DAC_MOD_CLK is routed to ADC_MOD_CLK */

        rset(0, 0);         // Select Page 0

        rset(27,0x0D);      // BCLK and WCLK is set as op to AIC3204(Master)
        rset(4, 0x03);      // codec_clkin <- MCLK

        rset(5,  0x91);     // p & r values
        rset(6,  0x07);     // j value
        rset(7,  0x06);     // D (MSB) value
        rset(8,  0x90);     // D (LSB) value
        rset(11, 0x82);     // NDAC value
        rset(12, 0x87);     // MDAC value
        rset(13, 0x00);     // DOSR (MSB) value
        rset(14, 0x80);     // DPSR (LSB) value
        rset(18, 0x82);     // NADC value
        rset(19, 0x87);     // MADC value
        rset(20, 0x80);     // AOSR (LSB) value
        rset(30, 0x9C);     // BCLK value

        /* Configure DAC Channel */
        /* DISABLE DAC DURING RECORD */
        rset(0, 1);         // Select Page 1
        rset(20,0x25);      // 14Feb2012 - Added to avoid pop during the start-up
        rset(10,0x00);      // 0.9 V Common mode and HPL/R are powered by AVDD not LDOIN (HPVDD)
        //rset(3,0x08);     // Put LDAC in lowest power mode PTM_P1 (page 27 & 35 of AIC3204 datasheet)
        //rset(4,0x08);     // Put RDAC in lowest power mode PTM_P1 (page 27 & 35 of AIC3204 datasheet)
        rset(12,0x08);      // LDAC AFIR routed to HPL
        rset(13,0x08);      // RDAC AFIR routed to HPR

        /* Route LDAC/RDAC to LOL/LOR */
        rset(14, 0x08);
        rset(15, 0x08);

        rset(0, 0);         // Select Page 0
        //rset(60,0x07);    // Put DACs in lowest power mode PRB_P7 (page 35 of AIC3204 datasheet)
        rset(63,0xD4);      // Power up left,right data paths and set channel

        rset(0, 1);         // Select Page 1
        rset(16,0x00);      // Unmute HPL , 0dB gain
        rset(17,0x00);      // Unmute HPR , 0dB gain
        /* Unmute LOL/LOR driver, 0dB Gain */
        rset(9, 0x3C);      // Power up HPL,HPR

        rset(0, 0);         // Select Page 0
        rset(64,0x02);      // Left and right DACs will have independent volume control
        rset(65,0x00);      // Left DAC volume

        /*    Configure ADC Channel */
        /*  DISABLE ADC DURING PLAYBACK */

        rset(0, 0);         // Select Page 0
        rset(20,0x80);      // AOSR for AOSR = 64 decimal or 0x0040 for decimation filters 1 to 6
                            // MADC is powered down and ADC_MOD_CLK <- DAC_MOD_CLK by default in  Pg 0 - Reg 19

        /* PRB_P2 and PRB_R2 selected */
        rset(60, 0x02);
        rset(61, 0x02);
        

        rset(00, 0x01);     // Select Page 1
#if 1
        rset(51, 0x48);     // power up Mic Bias using LDO-IN
        rset(52, 0x30);     // Route IN2L to LEFT_P with 40K input impedance
        rset(54, 0x40);     // Route CM1L to LEFT_M with 10K input impedance
        rset(55, 0x30);     // Route IN2L to RIGHT_P with 40K input impedance
        rset(57, 0x40);     // Route CM1R to RIGHT_M with 10K input impedance
#else
        rset(51, 0x68);     // power up micBIAS, micBIAS = 2.5V (CM = 0.9V)
        rset(52, 0x10);     // Route IN2L to LEFT_P with 10K input impedance
        rset(54, 0x40);     // Route CM1L to LEFT_M with 10K input impedance
        rset(55, 0x01);     // Route IN2L to RIGHT_P with 10K input impedance
        rset(57, 0x40);     // Route CM1R to RIGHT_M with 10K input impedance
#endif
        rset(59, 0x00);     // Unmute Left MICPGA, Gain selection of 0dB
        rset(60, 0x00);     // Unmute Right MICPGA, Gain selection of 0dB

        rset(0, 0);         // Select Page 0
        rset(81, 0xC0);     // Power up LADC/RADC only
        rset(82, 0x00);     // Unmute LADC/RADC only 0dB gain

        delayMilliseconds(3000);

        /* Initialize I2S */
        status = I2S.init();
        if (status != CSL_SOK)
        {
        DBG_MSG_PRINT("\n I2S init failed \n");
            return (CSL_ESYS_FAIL);
        }

        /* Enable I2S */
        I2S.enable();

        /* Initialize DMA buffers with zeroes */
        for(index = 0; index < bufferSize; index++)
        {
            i2sDmaLeftBuff1[0][index] = 0;
            i2sDmaRightBuff1[0][index] = 0;

            i2sDmaLeftBuff1[1][index] = 0;
            i2sDmaRightBuff1[1][index] = 0;

            i2sDmaLeftBuff2[0][index] = 0;
            i2sDmaRightBuff2[0][index] = 0;

            i2sDmaLeftBuff2[1][index] = 0;
            i2sDmaRightBuff2[1][index] = 0;
        }

        /* Initialize DMA */
        status = DMA.init();
        if (status != CSL_SOK)
        {
            DBG_MSG_PRINT("\n DMA init failed");
            return (CSL_ESYS_FAIL);
        }

        /* Open DMA channels for read and write of Left and Right audio channels */
        status = DMA.openChannel(DMA_CHAN_ReadL);
        if (status == CSL_SOK)
        {
            status = DMA.openChannel(DMA_CHAN_ReadR);
            if (status == CSL_SOK)
            {
                status = DMA.openChannel(DMA_CHAN_WriteL);
                if (status == CSL_SOK)
                {
                    status = DMA.openChannel(DMA_CHAN_WriteR);
                    if (status == CSL_SOK)
                    {
                        isInitialized = 1;
                    }
                    else
                    {
                        DBG_MSG_PRINT("\n DMA open write right channel failed");
                        return (CSL_ESYS_FAIL);
                    }
                }
                else
                {
                    DBG_MSG_PRINT("\n DMA open write left channel failed");
                    return (CSL_ESYS_FAIL);
                }
            }
            else
            {
                DBG_MSG_PRINT("\n DMA open read right channel failed");
                return (CSL_ESYS_FAIL);
            }
        }
        else
        {
            DBG_MSG_PRINT("\n DMA open read left channel failed");
            return (CSL_ESYS_FAIL);
        }
    }
    else
    {
        DBG_MSG_PRINT("\n DMA channel open failed \n");
        return (CSL_ESYS_FAIL);
    }

    return (status);
}

/** ===========================================================================
 *   @n@b close
 *
 *   @b Description
 *   @n Function to close Audio module.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - close is successful
 *   @li                    CSL_ESYS_FAIL       - close is not successful
 *
 *  ===========================================================================
 */
int AudioClass::close(void)
{
    CSL_Status status;

    status = I2S.close();    // Disable I2S
    rset(1, 0x01);           // Reset codec

    return (status);
}

/** ===========================================================================
 *   @n@b I2SDmaReadLeft
 *
 *   @b Description
 *   @n Function to configure DMA read left channel transfers.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - DMA configuration is successful
 *   @li                    CSL_ESYS_FAIL       - DMA configuration is not
 *                                                successful
 *
 *  ===========================================================================
 */
int AudioClass::I2SDmaReadLeft(void)
{
    CSL_Status    status;
    DMAConfig     dmaConfig;

    /* Configure DMA channel for I2S2 left channel read
     * DMA interrupt is disabled for this left channel, whereas interrupt is
     * enabled for right channel. User can check the status of Right DMA channel
     * to find out whether the Audio samples are received from the codec or not
     */
    dmaConfig.enablePingPong   = 0;
    dmaConfig.enableAutoReload = 0;
    dmaConfig.burstLen         = DMA_BURST_1WORD;
    dmaConfig.dmaEvent         = DMA_EVENT_I2S2_RX;
    dmaConfig.enableDmaInt     = 0;
    dmaConfig.chanDir          = DMA_CHANNEL_DIRECTION_READ;
    dmaConfig.dataLen          = bufferSize* 2;
    dmaConfig.destAddr         = audioInLeft[activeInBuf];
#ifdef CHIP_C5517
    dmaConfig.srcAddr          = (unsigned short *)&CSL_I2S2_REGS->I2SRXLTL;
#else
    dmaConfig.srcAddr          = (unsigned short *)&CSL_I2S2_REGS->I2SRXLT0;
#endif

    status = DMA.configChannel(DMA_CHAN_ReadL, dmaConfig);

    return (status);
}

/** ===========================================================================
 *   @n@b I2SDmaReadRight
 *
 *   @b Description
 *   @n Function to configure DMA read right channel transfers.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - DMA configuration is successful
 *   @li                    CSL_ESYS_FAIL       - DMA configuration is not successful
 *
 *  ===========================================================================
 */
int AudioClass::I2SDmaReadRight(void)
{
    CSL_Status      status;
    DMAConfig       dmaConfig;

    /* Configure DMA ch1 for I2S right channel read
     * DMA interrupt is disabled for the left channel, whereas interrupt is
     * enabled for this right channel. User can check the status of Right DMA
     * channel to find out whether the Audio samples are received from the codec
     * or not
     */
    dmaConfig.enablePingPong   = 0;
    dmaConfig.enableAutoReload = 0;
    dmaConfig.burstLen         = DMA_BURST_1WORD;
    dmaConfig.dmaEvent         = DMA_EVENT_I2S2_RX;
    dmaConfig.enableDmaInt     = 1;
    dmaConfig.chanDir          = DMA_CHANNEL_DIRECTION_READ;
    dmaConfig.dataLen          = bufferSize * 2;
    dmaConfig.destAddr         = audioInRight[activeInBuf];
#ifdef CHIP_C5517
    dmaConfig.srcAddr          = (unsigned short *)&CSL_I2S2_REGS->I2SRXRTL;
#else
    dmaConfig.srcAddr          = (unsigned short *)&CSL_I2S2_REGS->I2SRXRT0;
#endif

    status = DMA.configChannel(DMA_CHAN_ReadR, dmaConfig);

    return (status);
}

/** ===========================================================================
 *   @n@b read
 *
 *   @b Description
 *   @n Function to perform DMA read of left and right channels.
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
int AudioClass::read(void)
{
    CSL_Status status;

    status = AudioC.I2SDmaReadLeft();
    if (status != CSL_SOK)
    {
        DBG_MSG_PRINT("\n DMA read left config failed !\n");
        DBG_MSG_PRINT((long)status);
    }
    status = AudioC.I2SDmaReadRight();
    if (status != CSL_SOK)
    {
        DBG_MSG_PRINT("\n DMA read right config failed !\n");
        DBG_MSG_PRINT((long)status);
    }

    status = DMA.start(DMA_CHAN_ReadL);
    if (status != CSL_SOK)
    {
        DBG_MSG_PRINT("\n DMA read left start failed !\n");
    }
    status = DMA.start(DMA_CHAN_ReadR);
    if (status != CSL_SOK)
    {
        DBG_MSG_PRINT("\n DMA read right start failed !\n");
    }

    return (status);
}

/** ===========================================================================
 *   @n@b I2SDmaWriteLeft
 *
 *   @b Description
 *   @n Function to configure DMA write left channel transfers.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - DMA configuration is successful
 *   @li                    CSL_ESYS_FAIL       - DMA configuration is not successful
 *
 *  ===========================================================================
 */
int AudioClass::I2SDmaWriteLeft(void)
{
    CSL_Status      status;
    DMAConfig       dmaConfig;

    /* Configure DMA channel4 for I2S2 left channel read
     * DMA interrupt is disabled for this left channel, whereas interrupt is
     * enabled for the right channel. User can check the status of Right DMA
     * channel to find out whether the Audio samples are transmitted to the
     * codec or not
     */
    dmaConfig.enablePingPong   = 0;
    dmaConfig.enableAutoReload = 0;
    dmaConfig.burstLen         = DMA_BURST_1WORD;
    dmaConfig.dmaEvent         = DMA_EVENT_I2S2_TX;
    dmaConfig.enableDmaInt     = 0;
    dmaConfig.chanDir          = DMA_CHANNEL_DIRECTION_WRITE;
    dmaConfig.dataLen          = bufferSize * 2;
#ifdef CHIP_C5517
    dmaConfig.destAddr         = (unsigned short *)&CSL_I2S2_REGS->I2STXLTL;
#else
    dmaConfig.destAddr         = (unsigned short *)&CSL_I2S2_REGS->I2STXLT0;
#endif
    dmaConfig.srcAddr          = audioOutLeft[activeOutBuf];

    status = DMA.configChannel(DMA_CHAN_WriteL, dmaConfig);

    return (status);
}

/** ===========================================================================
 *   @n@b I2SDmaWriteRight
 *
 *   @b Description
 *   @n Function to configure DMA write right channel transfers.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - DMA configuration is successful
 *   @li                    CSL_ESYS_FAIL       - DMA configuration is not successful
 *
 *  ===========================================================================
 */
int AudioClass::I2SDmaWriteRight(void)
{
    CSL_Status      status;
    DMAConfig       dmaConfig;

    /* Configure DMA ch1 for I2S right channel read
     * DMA interrupt is disabled for the left channel, whereas interrupt is
     * enabled for this right channel. User can check the status of Right DMA
     * channel to find out whether the Audio samples are transmitted to the
     * codec or not
     */
    dmaConfig.enablePingPong   = 0;
    dmaConfig.enableAutoReload = 0;
    dmaConfig.burstLen         = DMA_BURST_1WORD;
    dmaConfig.dmaEvent         = DMA_EVENT_I2S2_TX;
    dmaConfig.enableDmaInt     = 1;
    dmaConfig.chanDir          = DMA_CHANNEL_DIRECTION_WRITE;
    dmaConfig.dataLen          = bufferSize * 2;
#ifdef CHIP_C5517
    dmaConfig.destAddr         = (unsigned short *)&CSL_I2S2_REGS->I2STXRTL;
#else
    dmaConfig.destAddr         = (unsigned short *)&CSL_I2S2_REGS->I2STXRT0;
#endif
    dmaConfig.srcAddr          = audioOutRight[activeOutBuf];

    status = DMA.configChannel(DMA_CHAN_WriteR, dmaConfig);

    return (status);
}

/** ===========================================================================
 *   @n@b write
 *
 *   @b Description
 *   @n Function to perform DMA writes of left and right channels.
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
int AudioClass::write(void)
{
    CSL_Status status;

    status = AudioC.I2SDmaWriteLeft();
    if (status != CSL_SOK)
    {
        DBG_MSG_PRINT("\n DMA write left config failed !\n");
    }
    status = AudioC.I2SDmaWriteRight();
    if (status != CSL_SOK)
    {
        DBG_MSG_PRINT("\n DMA write right config failed !\n");
    }

    status = DMA.start(DMA_CHAN_WriteL);
    if (status != CSL_SOK)
    {
        DBG_MSG_PRINT("\n DMA write left start failed !\n");
    }
    status = DMA.start(DMA_CHAN_WriteR);
    if (status != CSL_SOK)
    {
        DBG_MSG_PRINT("\n DMA write right start failed !\n");
    }

    return (status);
}

/** ===========================================================================
 *   @n@b attachInterrupt
 *
 *   @b Description
 *   @n Function to assign ISR fot DMA interrupt.
 *
 *   @b Arguments
 *   @verbatim
 *        function - ISR function pointer
     @endverbatim
 *
 *   <b> Return Value </b>
 *    @n None
 *
 *  ===========================================================================
 */
void AudioClass::attachIntr(void *function)
{
    attachInterrupt(INTERRUPT_DMA, (INTERRUPT_IsrPtr)function, 0);
    enableInterrupt(INTERRUPT_DMA);

    /* Start the Audio module */
    read();
    write();
}

/** ===========================================================================
 *   @n@b detachInterrupt
 *
 *   @b Description
 *   @n Function to detach ISR function pointer from the DMA interrupt.
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
void AudioClass::detachIntr(void)
{
    disableInterrupt(INTERRUPT_DMA);
    detachInterrupt(INTERRUPT_DMA);
}

/** ===========================================================================
 *   @n@b isrDma
 *
 *   @b Description
 *   @n DMA ISR for DMA interrupts.
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
void AudioClass::isrDma(void)
{
    Uint16 ifrValue;

    /* Read the DMA interrupt */
    ifrValue = DMA.readInterruptStatus();
    /* Clear DMA interrupt status */
    DMA.clearInterruptStatus(ifrValue);

    /* Reset interrupt value stored */
    DMA.resetInterruptStatus();

    if ((ifrValue >> DMA_CHAN_ReadR) & 0x01)
    {
        /* Configure DMA for Read left channel */
        activeInBuf = (activeInBuf == FALSE)? TRUE: FALSE;
        AudioC.I2SDmaReadLeft();

        /* Configure DMA for Read right channel */
        AudioC.I2SDmaReadRight();

        DMA.start(DMA_CHAN_ReadL);
        DMA.start(DMA_CHAN_ReadR);
    }
    else if ((ifrValue >> DMA_CHAN_WriteR) & 0x01)
    {
        /* Configure DMA for Write left channel */
        activeOutBuf = (activeOutBuf == FALSE)? TRUE: FALSE;
        AudioC.I2SDmaWriteLeft();

        /* Configure DMA for Write right channel */
        AudioC.I2SDmaWriteRight();

        DMA.start(DMA_CHAN_WriteL);
        DMA.start(DMA_CHAN_WriteR);
    }
}

/** ===========================================================================
 *   @n@b setInputGain
 *
 *   @b Description
 *   @n Function to set ADC gain for left and right channels independently.
 *
 *      The ADC gain value will be in the range of 0.0dB to 47.5dB, a
 *      increase in 1% ADC gain (left/right) will result in increasing the ADC
 *      gain (left/right) by 0.5dB or 1dB
 *
 *   @b Arguments
 *   @verbatim
 *      lgain - ADC gain value for left channel in terms of percentage(0 - 100)
 *      rgain - ADC gain value for right channel in terms of percentage(0 - 100)
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Gain setting successful
 *   @li                    CSL_ESYS_FAIL       - Gain setting is not successful
 *
 *  ===========================================================================
 */
int AudioClass::setInputGain(int lgain, int rgain)
{
    CSL_Status      status;

    if ((lgain >= 0) && (lgain <= 100) &&
       (rgain >= 0) && (rgain <= 100))
    {
        /* ADC gain register values will be in the range of 0 to 95(i.e. 0.0dB
           to 47.5dB respectively), hence multiply the lgain and rgain
           percentage values (range 0-100) by 0.95 to get the corresponding left
           and right ADC gain register values
        */
        lgain = lgain * 0.95;
        rgain = rgain * 0.95;
    }
    else
    {
        return (CSL_ESYS_FAIL);
    }

    /* Select Page 1 */
    status = rset(0, 1);
    if (status == CSL_SOK)
    {
        /* Write the gain registers */
        status = rset(59, lgain);
        if (status == CSL_SOK)
        {
            status = rset(60, rgain);
        }
        /* Small delay to allow the gain change */
        delayMilliseconds(10);
    }

    return (status);
}

/** ===========================================================================
 *   @n@b setOutputVolume
 *
 *   @b Description
 *   @n Function to set DAC volume with left channel controlling both left and right.
 *
 *      The DAC volume value will be in the range of :
 *      -63.5dB, -63.0dB, ......, -0.5dB, 0.0dB, +0.5dB, ......, +23.5dB, +24dB.
 *      A increase in 1% Volume (left/right) will result in increasing the DAC
 *      Volume (left/right) by 1.5dB or 2dB
 *
 *   @b Arguments
 *   @verbatim
 *      volume - DAC volume value in terms of percentage(0 - 100)
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Volume setting successful
 *   @li                    CSL_ESYS_FAIL       - Volume setting is not successful
 *
 *  ===========================================================================
 */
int AudioClass::setOutputVolume(int volume)
{
    CSL_Status      status;
    float           vol;

    /* DAC volume register values will be in the range of 0 to 48(for 0.0dB to
       +24dB respectively) and 255 down to 129 (for -0.5dB to -63.5dB
       respectively). Hence the percentages will be in the range of 73% to 100%
       for 0.0dB to +24dB respectively and 0% to 72% for -0.5dB to -63.5dB
       respectively.
       The range of DAC volume (left or right) register values consists of a
       total 176 values (i.e, 0-48: 49 nos and 129-255: 127 nos), hence divide
       the percentage with 0.568(i.e, 100/176 = 0.568).
    */
    if ((volume >= 0) && (volume <= 72))
    {
        vol = 72 - volume;
        vol = vol / 0.568;
        vol = 255 - vol;
    }
    else if ((volume > 72) && (volume <= 100))
    {
        vol = volume - 72;
        vol = (vol / 0.568) - 1;
    }
    else
    {
        return (CSL_ESYS_FAIL);
    }

    /* Select Page 0 */
    status = rset(0, 0);
    if (status == CSL_SOK)
    {
        /* Left channel controlling both channels */
        status = rset(64, 2);
        if (status == CSL_SOK)
        {
            rset(65, (int)vol);
        }
        /* Small delay to allow the gain change */
        delayMilliseconds(10);
    }

    return (status);
}

/** ===========================================================================
 *   @n@b setOutputVolume
 *
 *   @b Description
 *   @n Function to set DAC volume with left and right independent control.
 *
 *   @b Arguments
 *   @verbatim
 *      lvolume - DAC volume value for left channel
 *      rvolume - DAC volume value for right channel
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Volume setting successful
 *   @li                    CSL_ESYS_FAIL       - Volume setting is not successful
 *
 *  ===========================================================================
 */
int AudioClass::setOutputVolume(int lvolume, int rvolume)
{
    CSL_Status      status;
    float           lvol;
    float           rvol;

    /* DAC volume register values will be in the range of 0 to 48(for 0.0dB to
       +24dB respectively) and 255 down to 129 (for -0.5dB to -63.5dB
       respectively). Hence the percentages will be in the range of 73% to 100%
       for 0.0dB to +24dB respectively and 0% to 72% for -0.5dB to -63.5dB
       respectively.
       The range of DAC volume (left or right) register values consists of a
       total 176 values (i.e, 0-48: 49 nos and 129-255: 127 nos), hence divide
       the percentage with 0.568(i.e, 100/176 = 0.568).
    */
    if ((lvolume >= 0) && (lvolume <= 100) &&
       (rvolume >= 0) && (rvolume <= 100))
    {
        if (lvolume <= 72)
        {
            lvol = 72 - lvolume;
            lvol = lvol / 0.568;
            lvol = 255 - lvol;
        }
        else
        {
            lvol = lvolume - 72;
            lvol = (lvol / 0.568) - 1;
        }

        if (rvolume <= 72)
        {
            rvol = 72 - rvolume;
            rvol = rvol / 0.568;
            rvol = 255 - rvol;
        }
        else
        {
            rvol = rvolume - 72;
            rvol = (rvol / 0.568) - 1;
        }
    }
    else
    {
        status = CSL_ESYS_FAIL;

        return (status);
    }

    Serial.println(lvol);
    Serial.println(rvol);

    /* Select Page 0 */
    status = rset(0, 0);
    if (status == CSL_SOK)
    {
        /* Left and right channels have independent control */
        status = rset(64, 0);
        if (status == CSL_SOK)
        {
            rset(65, (int)lvol);
            rset(66, (int)rvol);
        }
        /* Small delay to allow the gain change */
        delayMilliseconds(10);
    }

    return (status);
}

/** ===========================================================================
 *   @n@b audioMute
 *
 *   @b Description
 *   @n Function to mute audio.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Muting successful
 *   @li                    CSL_ESYS_FAIL       - Muting is not successful
 *
 *  ===========================================================================
 */
int AudioClass::audioMute(void)
{
    CSL_Status      status;

    /* Select Page 0 */
    status = rset(0, 0);
    if (status == CSL_SOK)
    {
        /* Unmute audio */
        status = rset(64, 0x0C);

        /* Small delay to allow the mute setting */
        delayMilliseconds(10);
    }

    return (status);
}

/** ===========================================================================
 *   @n@b audioUnmute
 *
 *   @b Description
 *   @n Function to unmute audio.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Muting successful
 *   @li                    CSL_ESYS_FAIL       - Muting is not successful
 *
 *  ===========================================================================
 */
int AudioClass::audioUnmute(void)
{
    CSL_Status      status;

    /* Select Page 0 */
    status = rset(0, 0);
    if (status == CSL_SOK)
    {
        /* Unmute audio */
        status = rset(64, 0x00);

        /* Small delay to allow the mute setting */
        delayMilliseconds(10);
    }

    return (status);
}

int AudioClass::dacSetFirstOrderIirFilter(long LN0, long LN1, long LD1, long RN0, long RN1, long RD1)
{
    CSL_Status status = CSL_SOK;

    status |= rset(0, 46);         // Set 1st order IIR coefficients, Left channel
    status |= rset24bit(28, LN0);
    status |= rset24bit(32, LN1);
    status |= rset24bit(36, LD1);
        
    status |= rset(0, 46);         // Set 1st order IIR coefficients, Right channel
    status |= rset24bit(40, RN0);
    status |= rset24bit(44, RN1);
    status |= rset24bit(48, RD1);

    return (status);
}

int AudioClass::dacSetFirstOrderIirFilter(long N0, long N1, long D1)
{
    return (dacSetFirstOrderIirFilter(N0, N1, D1, N0, N1, D1));
}

int AudioClass::dacSetBiquadIirFilter(int filter, long LN0, long LN1, long LN2, long LD1, long LD2, long RN0, long RN1, long RN2, long RD1, long RD2)
{
    CSL_Status status = CSL_SOK;
    
    if (filter == 1)
    {
        status |= rset(0, 44);         // Set biquad coefficients, Left channel
        status |= rset24bit( 12, LN0);
        status |= rset24bit( 16, LN1);
        status |= rset24bit( 20, LN2);
        status |= rset24bit( 24, LD1);
        status |= rset24bit( 28, LD2);
            
        status |= rset(0, 45);         // Set biquad coefficients, Right channel
        status |= rset24bit( 20, RN0);
        status |= rset24bit( 24, RN1);
        status |= rset24bit( 28, RN2);
        status |= rset24bit( 32, RD1);
        status |= rset24bit( 36, RD2);
    }
    else if (filter == 2)
    {
        status |= rset(0, 44);         // Set biquad coefficients, Left channel
        status |= rset24bit(32, LN0);
        status |= rset24bit(36, LN1);
        status |= rset24bit(40, LN2);
        status |= rset24bit(44, LD1);
        status |= rset24bit(48, LD2);
            
        status |= rset(0, 45);         // Set biquad coefficients, Right channel
        status |= rset24bit( 40, RN0);
        status |= rset24bit( 44, RN1);
        status |= rset24bit( 48, RN2);
        status |= rset24bit( 52, RD1);
        status |= rset24bit( 56, RD2);
    }
    else if (filter == 3)
    {
        status |= rset(0, 44);         // Set biquad coefficients, Left channel
        status |= rset24bit( 52, LN0);
        status |= rset24bit( 56, LN1);
        status |= rset24bit( 60, LN2);
        status |= rset24bit( 64, LD1);
        status |= rset24bit( 68, LD2);
            
        status |= rset(0, 45);         // Set biquad coefficients, Right channel
        status |= rset24bit( 60, RN0);
        status |= rset24bit( 64, RN1);
        status |= rset24bit( 68, RN2);
        status |= rset24bit( 72, RD1);
        status |= rset24bit( 76, RD2);
    }
    else if (filter == 4)
    {
        status |= rset(0, 44);         // Set biquad coefficients, Left channel
        status |= rset24bit( 72, LN0);
        status |= rset24bit( 76, LN1);
        status |= rset24bit( 80, LN2);
        status |= rset24bit( 84, LD1);
        status |= rset24bit( 88, LD2);
            
        status |= rset(0, 45);         // Set biquad coefficients, Right channel
        status |= rset24bit( 80, RN0);
        status |= rset24bit( 84, RN1);
        status |= rset24bit( 88, RN2);
        status |= rset24bit( 92, RD1);
        status |= rset24bit( 96, RD2);
    }
    else if (filter == 5)
    {
        status |= rset(0, 44);         // Set biquad coefficients, Left channel
        status |= rset24bit( 92, LN0);
        status |= rset24bit( 96, LN1);
        status |= rset24bit(100, LN2);
        status |= rset24bit(104, LD1);
        status |= rset24bit(108, LD2);   
        
        status |= rset(0, 45);         // Set biquad coefficients, Right channel
        status |= rset24bit(100, RN0);
        status |= rset24bit(104, RN1);
        status |= rset24bit(108, RN2);
        status |= rset24bit(112, RD1);
        status |= rset24bit(116, RD2);
    }
    else if (filter == 6)
    {
        status |= rset(0, 44);         // Set biquad coefficients, Left channel
        status |= rset24bit(112, LN0);
        status |= rset24bit(116, LN1);
        status |= rset24bit(120, LN2);
        status |= rset24bit(124, LD1);
        status |= rset(0, 45);
        status |= rset24bit(  8, LD2);   
        
                                      // Set biquad coefficients, Right channel
        status |= rset24bit(120, RN0);
        status |= rset24bit(124, RN1);
        status |= rset(0, 46);
        status |= rset24bit(  8, RN2);
        status |= rset24bit( 12, RD1);
        status |= rset24bit( 16, RD2);
    }
    return (status);
}

int AudioClass::dacSetBiquadIirFilter(int filter, long N0, long N1, long N2, long D1, long D2)
{
    return (adcSetBiquadIirFilter(filter, N0, N1, N2, D1, D2, N0, N1, N2, D1, D2));
}

int AudioClass::adcSetFirstOrderIirFilter(long LN0, long LN1, long LD1, long RN0, long RN1, long RD1)
{
    CSL_Status status = CSL_SOK;

    status |= rset(0, 8);         // Set 1st order IIR coefficients, Left channel
    status |= rset24bit(24, LN0);
    status |= rset24bit(28, LN1);
    status |= rset24bit(32, LD1);
        
    status |= rset(0, 9);         // Set 1st order IIR coefficients, Right channel
    status |= rset24bit(32, RN0);
    status |= rset24bit(36, RN1);
    status |= rset24bit(40, RD1);

    return (status);
}

int AudioClass::adcSetFirstOrderIirFilter(long N0, long N1, long D1)
{
    return (adcSetFirstOrderIirFilter(N0, N1, D1, N0, N1, D1));
}

int AudioClass::adcSetBiquadIirFilter(int filter, long LN0, long LN1, long LN2, long LD1, long LD2, long RN0, long RN1, long RN2, long RD1, long RD2)
{
    CSL_Status status = CSL_SOK;
    
    if (filter == 1)
    {
        status |= rset(0, 8);         // Set biquad coefficients, Left channel
        status |= rset24bit( 36, LN0);
        status |= rset24bit( 40, LN1);
        status |= rset24bit( 44, LN2);
        status |= rset24bit( 48, LD1);
        status |= rset24bit( 52, LD2);
            
        status |= rset(0, 9);         // Set biquad coefficients, Right channel
        status |= rset24bit( 44, RN0);
        status |= rset24bit( 48, RN1);
        status |= rset24bit( 52, RN2);
        status |= rset24bit( 56, RD1);
        status |= rset24bit( 60, RD2);
    }
    else if (filter == 2)
    {
        status |= rset(0, 8);         // Set biquad coefficients, Left channel
        status |= rset24bit(56, LN0);
        status |= rset24bit(60, LN1);
        status |= rset24bit(64, LN2);
        status |= rset24bit(68, LD1);
        status |= rset24bit(72, LD2);
            
        status |= rset(0, 9);         // Set biquad coefficients, Right channel
        status |= rset24bit( 64, RN0);
        status |= rset24bit( 68, RN1);
        status |= rset24bit( 72, RN2);
        status |= rset24bit( 76, RD1);
        status |= rset24bit( 80, RD2);
    }
    else if (filter == 3)
    {
        status |= rset(0, 8);         // Set biquad coefficients, Left channel
        status |= rset24bit( 76, LN0);
        status |= rset24bit( 80, LN1);
        status |= rset24bit( 84, LN2);
        status |= rset24bit( 88, LD1);
        status |= rset24bit( 92, LD2);
            
        status |= rset(0, 9);         // Set biquad coefficients, Right channel
        status |= rset24bit( 84, RN0);
        status |= rset24bit( 88, RN1);
        status |= rset24bit( 92, RN2);
        status |= rset24bit( 96, RD1);
        status |= rset24bit(100, RD2);
    }
    else if (filter == 4)
    {
        status |= rset(0, 8);         // Set biquad coefficients, Left channel
        status |= rset24bit( 96, LN0);
        status |= rset24bit(100, LN1);
        status |= rset24bit(104, LN2);
        status |= rset24bit(108, LD1);
        status |= rset24bit(112, LD2);
            
        status |= rset(0, 9);         // Set biquad coefficients, Right channel
        status |= rset24bit(104, RN0);
        status |= rset24bit(108, RN1);
        status |= rset24bit(112, RN2);
        status |= rset24bit(116, RD1);
        status |= rset24bit(120, RD2);
    }
    else if (filter == 5)
    {
        status |= rset(0, 8);         // Set biquad coefficients, Left channel
        status |= rset24bit(116, LN0);
        status |= rset24bit(120, LN1);
        status |= rset24bit(124, LN2);
        status |= rset(0, 9);
        status |= rset24bit(  8, LD1);
        status |= rset24bit( 12, LD2);   
        
                                      // Set biquad coefficients, Right channel
        status |= rset24bit(124, RN0);
        status |= rset(0, 10);
        status |= rset24bit(  8, RN1);
        status |= rset24bit( 12, RN2);
        status |= rset24bit( 16, RD1);
        status |= rset24bit( 20, RD2);
    }
    return (status);
}

int AudioClass::adcSetBiquadIirFilter(int filter, long N0, long N1, long N2, long D1, long D2)
{
    return (adcSetBiquadIirFilter(filter, N0, N1, N2, D1, D2, N0, N1, N2, D1, D2));
}

int AudioClass::adcSet25TapFirFilter(const long *filterLeft, const long *filterRight)
{
    CSL_Status status = CSL_SOK;

    // Set FIR coefficients, Left channel
    // Taps 0 - 22
    status |= rset(0, 8);
    for (int n = 0; n < 23; n++)
    {
      status |= rset24bit( 36 + 4 * n, filterLeft[n]);
    }
    // Taps 23-24
    status |= rset(0, 9);
    status |= rset24bit(  8, filterLeft[23]);
    status |= rset24bit( 12, filterLeft[24]);
    
    // Set FIR coefficients, Right channel
    // Taps 0 - 20
    status |= rset(0, 9);
    for (int n = 0; n < 21; n++)
    {
      status |= rset24bit( 44 + 4 * n, filterLeft[n]);
    }
    // Taps 21-24
    status |= rset(0, 10);
    status |= rset24bit(  8, filterLeft[21]);
    status |= rset24bit( 12, filterLeft[22]);
    status |= rset24bit( 16, filterLeft[23]);
    status |= rset24bit( 20, filterLeft[24]);
 
    return(status);
}

int AudioClass::adcSet25TapFirFilter(const long *filter)
{
  return(adcSet25TapFirFilter(filter, filter));
}

int AudioClass::dacSetAdaptiveFilterMode(int mode)
{
    CSL_Status      status;

    status = rset(0, 44);
    if (mode == TRUE)
      status |= rset(1, 0x04);
    else
      status |= rset(1, 0x00);
      
    return (status);
}


int AudioClass::adcSetAdaptiveFilterMode(int mode)
{
    CSL_Status      status;

    status = rset(0, 8);
    if (mode == TRUE)
      status |= rset(1, 0x04);
    else
      status |= rset(1, 0x00);
      
    return (status);
}


int AudioClass::dacAdaptiveFilterSwitch(void)
{
    CSL_Status      status;

    status = rset(0, 44);
    status |= rset(1, 0x05);
    
    return (status);
}

int AudioClass::adcAdaptiveFilterSwitch(void)
{
    CSL_Status      status;

    status = rset(0, 8);
    status |= rset(1, 0x05);
    
    return (status);
}

int AudioClass::dacPowerDown(void) 
{
    CSL_Status      status;

    status = rset(0, 0);
    status |= rset(63, 0x14);
    
    return(status);
}
    
int AudioClass::adcPowerDown(void) 
{
    CSL_Status      status;

    status = rset(0, 0);
    status |= rset(81, 0x00);
    
    return(status);
}
    
int AudioClass::dacPowerUp(void)
{
    CSL_Status      status;

    status = rset(0, 0);
    status |= rset(63, 0xD4);
    
    return(status);
}
    
int AudioClass::adcPowerUp(void)
{
    CSL_Status      status;

    status = rset(0, 0);
    status |= rset(81, 0xC0);
    
    return(status);
}
    
        
/** ===========================================================================
 *   @n@b codecConfig
 *
 *   @b Description
 *   @n Function to configure the codec with the specified config values.
 *
 *   @b Arguments
 *   @verbatim
 *      configStruct  - Structure containing the Codec Configurations
 *      noOfElems     - No of Codec Configurations
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Setting Codec Configurations
 *                                                is successful
 *   @li                    CSL_ESYS_FAIL       - Setting Codec Configurations
 *                                                is not successful
 *
 *  ===========================================================================
 */
int AudioClass::codecConfig(Uint16 configStruct[][2], int noOfElems)
{
    int index;
    int status;

    status = CSL_SOK;
    for (index = 0; index < noOfElems; index++)
    {
        status |= rset(configStruct[index][0],  configStruct[index][1]);
    }

    return (status);
}

/** ===========================================================================
 *   @n@b setSamplingRate
 *
 *   @b Description
 *   @n Function to set Sampling Rate for Audio IN/OUT.
 *
 *   @b Arguments
 *   @verbatim
 *      samplingRate - Sampling Rate that is to be set
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Setting Sampling rate successful
 *   @li                    CSL_ESYS_FAIL       - Setting Sampling rate is not
 *                                                successful
 *
 *  ===========================================================================
 */
int AudioClass::setSamplingRate(long samplingRate)
{
    int    status;
    Uint16 (*configStruct)[2];
    int    noOfElems;

    status = CSL_SOK;
    switch (samplingRate)
    {
        case SAMPLING_RATE_8_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_8k;
            noOfElems = sizeof(CodecConfig_SamplingRate_8k) /
                        sizeof(CodecConfig_SamplingRate_8k[0]);
            break;

        case SAMPLING_RATE_11_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_11k;
            noOfElems = sizeof(CodecConfig_SamplingRate_11k) /
                        sizeof(CodecConfig_SamplingRate_11k[0]);
            break;

        case SAMPLING_RATE_12_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_12k;
            noOfElems = sizeof(CodecConfig_SamplingRate_12k) /
                        sizeof(CodecConfig_SamplingRate_12k[0]);
            break;

        case SAMPLING_RATE_16_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_16k;
            noOfElems = sizeof(CodecConfig_SamplingRate_16k) /
                        sizeof(CodecConfig_SamplingRate_16k[0]);
            break;

        case SAMPLING_RATE_22_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_22k;
            noOfElems = sizeof(CodecConfig_SamplingRate_22k) /
                        sizeof(CodecConfig_SamplingRate_22k[0]);
            break;

        case SAMPLING_RATE_24_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_24k;
            noOfElems = sizeof(CodecConfig_SamplingRate_24k) /
                        sizeof(CodecConfig_SamplingRate_24k[0]);
            break;

        case SAMPLING_RATE_32_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_32k;
            noOfElems = sizeof(CodecConfig_SamplingRate_32k) /
                        sizeof(CodecConfig_SamplingRate_32k[0]);
            break;

        case SAMPLING_RATE_44_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_44k;
            noOfElems = sizeof(CodecConfig_SamplingRate_44k) /
                        sizeof(CodecConfig_SamplingRate_44k[0]);
            break;

        case SAMPLING_RATE_48_KHZ:
            configStruct = (Uint16 (*)[2])CodecConfig_SamplingRate_48k;
            noOfElems = sizeof(CodecConfig_SamplingRate_48k) /
                        sizeof(CodecConfig_SamplingRate_48k[0]);
            break;

        default:
            status = CSL_ESYS_FAIL;
            break;

    }

    if (CSL_SOK == status)
    {
        status = codecConfig(configStruct, noOfElems);
    }

    return (status);
}

/** ===========================================================================
 *   @n@b HPL_RConF_Routing
 *
 *   @b Description
 *   @n Function to select the HPL Routing of the Audio Codec.
 *
 *   @b Arguments
 *   @verbatim
 *      left - value of the left channel configuration that is to be set for the
 *             HPL routing register in order to select the desired routing to
 *             HPL
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Selecting the desired HPL
 *                                                routing successful
 *   @li                    CSL_ESYS_FAIL       - Selecting the desired HPL
 *                                                routing is not successful
 *
 *  ===========================================================================
 */
int AudioClass::HPL_RConF_Routing(int left)
{
    int status;
    Uint16 value;

    if (left)
    {
        value = 0x08;
    }
    else
    {
        value = 0x00;
    }

    status = rset(0, 1);       /* Select Page 1 */
    status |= rset(12, value);

    return (status);
}

/** ===========================================================================
 *   @n@b HPR_RConF_Routing
 *
 *   @b Description
 *   @n Function to select the HPR Routing of the Audio Codec.
 *
 *   @b Arguments
 *   @verbatim
 *      left - value of the left channel configuration that is to be set for the
 *             HPR routing register in order to select the desired routing to
 *             HPR
 *      right - value of the right channel configuration that is to be set for
 *              the HPR routing register in order to select the desired routing
 *              to HPR
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Selecting the desired HPR
 *                                                routing successful
 *   @li                    CSL_ESYS_FAIL       - Selecting the desired HPR
 *                                                routing is not successful
 *
 *  ===========================================================================
 */
int AudioClass::HPR_RConF_Routing(int left, int right)
{
    int status;
    Uint16 value = 0;

    if (left)
    {
        value |= 0x10;
    }

    if (right)
    {
        value |= 0x08;
    }

    status = rset(0, 1);       /* Select Page 1 */
    status |= rset(13, value);

    return (status);
}

/** ===========================================================================
 *   @n@b LOL_RConF_Routing
 *
 *   @b Description
 *   @n Function to select the LOL Routing of the Audio Codec.
 *
 *   @b Arguments
 *   @verbatim
 *      left - value of the left channel configuration that is to be set for the
 *             LOL routing register in order to select the desired routing to
 *             LOL
 *      right - value of the right channel configuration that is to be set for
 *              the LOL routing register in order to select the desired routing
 *              to LOL
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Selecting the desired LOL
 *                                                routing successful
 *   @li                    CSL_ESYS_FAIL       - Selecting the desired LOL
 *                                                routing is not successful
 *
 *  ===========================================================================
 */
int AudioClass::LOL_RConF_Routing(int left, int right)
{
    int status;
    Uint16 value = 0;

    if (right)
    {
        value |= 0x10;
    }

    if (right)
    {
        left |= 0x08;
    }

    status = rset(0, 1);       /* Select Page 1 */
    status |= rset(14, value);

    return (status);
}

/** ===========================================================================
 *   @n@b LOR_RConF_Routing
 *
 *   @b Description
 *   @n Function to select the LOR Routing of the Audio Codec.
 *
 *   @b Arguments
 *   @verbatim
 *      right - value of the right channel configuration that is to be set for
 *              the LOR routing register in order to select the desired routing
 *              to LOR
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Selecting the desired LOR
 *                                                routing successful
 *   @li                    CSL_ESYS_FAIL       - Selecting the desired LOR
 *                                                routing is not successful
 *
 *  ===========================================================================
 */
int AudioClass::LOR_RConF_Routing(int right)
{
    int status;
    Uint16 value;

    if (right)
    {
        value = 0x08;
    }
    else
    {
        value = 0x00;
    }

    status = rset(0, 1);       /* Select Page 1 */
    status |= rset(15, value);

    return (status);
}