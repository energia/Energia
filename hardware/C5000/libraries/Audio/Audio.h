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
/** @file Audio.h
 *
 *  @brief Audio library header file
 *
 */

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Buffer length */
#define I2S_DMA_BUF_LEN        (512)  // Must be power of 2
/** DMA left read channel */
#define DMA_CHAN_ReadL         (CSL_DMA_CHAN4)
/** DMA right read channel */
#define DMA_CHAN_ReadR         (CSL_DMA_CHAN5)
/** DMA left write channel */
#define DMA_CHAN_WriteL        (CSL_DMA_CHAN6)
/** DMA right write channel */
#define DMA_CHAN_WriteR        (CSL_DMA_CHAN7)

#define SAMPLING_RATE_8_KHZ  (8000u)  /**< Sampling Rate as 8 kHz  */
#define SAMPLING_RATE_11_KHZ (11025u) /**< Sampling Rate as 11 kHz */
#define SAMPLING_RATE_12_KHZ (12000u) /**< Sampling Rate as 12 kHz */
#define SAMPLING_RATE_16_KHZ (16000u) /**< Sampling Rate as 16 kHz */
#define SAMPLING_RATE_22_KHZ (22050u) /**< Sampling Rate as 22 kHz */
#define SAMPLING_RATE_24_KHZ (24000u) /**< Sampling Rate as 24 kHz */
#define SAMPLING_RATE_32_KHZ (32000u) /**< Sampling Rate as 32 kHz */
#define SAMPLING_RATE_44_KHZ (44100u) /**< Sampling Rate as 44 kHz */
#define SAMPLING_RATE_48_KHZ (48000u) /**< Sampling Rate as 48 kHz */

#define CHANNEL_MONO   (1)  /**< Macro to indicate the Channel type as Mono   */
#define CHANNEL_STEREO (2)  /**< Macro to indicate the Channel type as Stereo */

/**
  * \brief Audio Class
  *
  * Contains prototypes for functions in Audio library
  *
  * Address of audio data buffers is stored in the below pointers
  *    audioInLeft - Holds the adress of Audio input (read from codec) data
  *                  buffers for left channel
  *    audioInRight - Holds the adress of Audio input (read from codec) data
  *                  buffers for right channel
  *    audioOutLeft - Holds the adress of Audio output (write to codec) data
  *                  buffers for left channel
  *    audioInRight - Holds the adress of Audio output (write to codec) data
  *                  buffers for right channel
  *
  *    All the components described above are array of two pointers pointing
  *    to the two data buffers of given audio channel. When one data buffer
  *    is being used by audio module, other buffer can be used for data
  *    processing.
  *
  *    Index of the buffers being used by audio module are indicated by
  *    activeInBuf - Index of the buffer being used for audio input
  *                  audioInLeft[activeInBuf] indcates left channel buffer
  *                  audioInRight[activeInBuf] indcates right channel buffer
  *    activeOutBuf - Index of the buffer being used for audio output
  *                  audioOutLeft[activeOutBuf] indcates left channel buffer
  *                  audioOutRight[activeOutBuf] indcates right channel buffer
  *
  *    Data read from codec can accessed using the data buffer pointers
  *    'audioInLeft', audioInRight and index 'activeInBuf'
  *
  *    When Audio library is configured to operate with same data buffers
  *    for read and write operation (initialized using Audio(void)),
  *    audioInLeft and audioOutLeft points to same buffers and audioInRight
  *    and audioInRight points to same buffers.
  *
  *    When Audio library is configured to operate with independent data
  *    buffers for read and write operation (initialized using Audio(int process)),
  *    applications need to take care of copying the data from audio input
  *    buffers (audioInLeftxx) to audio output buffers (audioOutxx) in DMA ISR.
  *
  */
class AudioClass {
        static int isInitialized;
        int init();
        int I2SDmaReadLeft(void);
        int I2SDmaReadRight(void);
        int I2SDmaWriteLeft(void);
        int I2SDmaWriteRight(void);
        int bufferSize;

    public:
        int Audio(void);
        int Audio(int process, int buffer_size = I2S_DMA_BUF_LEN);
        /** Audio input - left channel */
        Uint16 *audioInLeft[2];
        /** Audio input - right channel */
        Uint16 *audioInRight[2];
        /** Audio output - left channel */
        Uint16 *audioOutLeft[2];
        /** Audio output - right channel */
        Uint16 *audioOutRight[2];
        /** Active input buffer */
        unsigned short activeInBuf;
        /** Active output buffer */
        unsigned short activeOutBuf;
        /** Left sample */
        int sampleLeft;
        /** Right sample */
        int sampleRight;
        int  close();
        void attachIntr(void *function);
        void detachIntr(void);
        int  read(void);
        int  write(void);
        void isrDma(void);
        int setInputGain(int lgain, int rgain);
        int setOutputVolume(int volume);
        int setOutputVolume(int lvolume, int rvolume);
        int audioMute(void);
        int audioUnmute(void);
        int setSamplingRate(long);

        int dacSetFirstOrderIirFilter(long N0, long N1, long D1);
        int dacSetFirstOrderIirFilter(long LN0, long LN1, long LD1, long RN0, long RN1, long RD1);
        int dacSetBiquadIirFilter(int filter, long LN0, long LN1, long LN2, long LD1, long LD2, long RN0, long RN1, long RN2, long RD1, long RD2);
        int dacSetBiquadIirFilter(int filter, long N0, long N1, long N2, long D1, long D2);

        int adcSetFirstOrderIirFilter(long N0, long N1, long D1);
        int adcSetFirstOrderIirFilter(long LN0, long LN1, long LD1, long RN0, long RN1, long RD1);
        int adcSetBiquadIirFilter(int filter, long LN0, long LN1, long LN2, long LD1, long LD2, long RN0, long RN1, long RN2, long RD1, long RD2);
        int adcSetBiquadIirFilter(int filter, long N0, long N1, long N2, long D1, long D2);
        int adcSet25TapFirFilter(const long *filterLeft, const long *filterRight);
        int adcSet25TapFirFilter(const long *filter);
        
        int adcSetAdaptiveFilterMode(int mode);
        int adcAdaptiveFilterSwitch(void);
        
        int dacSetAdaptiveFilterMode(int mode);
        int dacAdaptiveFilterSwitch(void);
        
        int dacPowerUp(void);
        int dacPowerDown(void);
        int adcPowerUp(void);
        int adcPowerDown(void);
        
        // Codec register access functions
        static int rset( Uint16 regnum, Uint16 regval);
        static int rset24bit( Uint16 regnum, Uint32 regval );
        static int rget( Uint16 page, Uint16 regnum, Uint16 *regval);
        static int codecConfig(Uint16 configStruct[][2], int noOfElems);
        
        int HPL_RConF_Routing(int left);
        int HPR_RConF_Routing(int left, int right);
        int LOL_RConF_Routing(int left, int right);
        int LOR_RConF_Routing(int right);

        ~AudioClass(void); // Destructor
};

extern AudioClass AudioC;

/**< Audio class instance extern which can used by application programs
 *   to access Audio DSP APIs
 */
#ifdef __cplusplus
}
#endif

#endif //_AUDIO_H_

