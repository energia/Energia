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
#define I2S_DMA_BUF_LEN        (512)
/** DMA left read channel */
#define DMA_CHAN_ReadL         (CSL_DMA_CHAN4)
/** DMA right read channel */
#define DMA_CHAN_ReadR         (CSL_DMA_CHAN5)
/** DMA left write channel */
#define DMA_CHAN_WriteL        (CSL_DMA_CHAN6)
/** DMA right write channel */
#define DMA_CHAN_WriteR        (CSL_DMA_CHAN7)

/**
  * \brief Audio Class
  *
  * Contains prototypes for functions in Audio library
  *
  * Address of audio data buffers is stored in the below pointers
  *	audioInLeft - Holds the adress of Audio input (read from codec) data
  *	              buffers for left channel
  *	audioInRight - Holds the adress of Audio input (read from codec) data
  *	              buffers for right channel
  *	audioOutLeft - Holds the adress of Audio output (write to codec) data
  *	              buffers for left channel
  *	audioInRight - Holds the adress of Audio output (write to codec) data
  *	              buffers for right channel
  *
  *	All the components described above are array of two pointers pointing
  *	to the two data buffers of given audio channel. When one data buffer
  *	is being used by audio module, other buffer can be used for data
  *	processing.
  *
  *	Index of the buffers being used by audio module are indicated by
  *	activeInBuf - Index of the buffer being used for audio input
  *	              audioInLeft[activeInBuf] indcates left channel buffer
  *	              audioInRight[activeInBuf] indcates right channel buffer
  *	activeOutBuf - Index of the buffer being used for audio output
  *	              audioOutLeft[activeOutBuf] indcates left channel buffer
  *	              audioOutRight[activeOutBuf] indcates right channel buffer
  *
  *	Data read from codec can accessed using the data buffer pointers
  *	'audioInLeft', audioInRight and index 'activeInBuf'
  *
  *	When Audio library is configured to operate with same data buffers
  *	for read and write operation (initialized using Audio(void)),
  *	audioInLeft and audioOutLeft points to same buffers and audioInRight
  *	and audioInRight points to same buffers.
  *
  *	When Audio library is configured to operate with independent data
  *	buffers for read and write operation (initialized using Audio(int process)),
  *	applications need to take care of copying the data from audio input
  *	buffers (audioInLeftxx) to audio output buffers (audioOutxx) in DMA ISR.
  *
  */
class AudioClass {
		static int isInitialized;
		int init();
		int I2SDmaReadLeft(void);
		int I2SDmaReadRight(void);
		int I2SDmaWriteLeft(void);
		int I2SDmaWriteRight(void);

	public:
		int Audio(void);
		int Audio(int process);
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
	    void attachIntr(INTERRUPT_IsrPtr function);
	    void detachIntr(void);
		int  read(void);
		int  write(void);
		void isrDma(void);
		int setInputGain(int lgain, int rgain);
		int setOutputVolume(int volume);
		int setOutputVolume(int lvolume, int rvolume);
		int audioMute(void);
		int audioUnmute(void);

		int HPL_RConF_Routing(int left);
		int HPR_RConF_Routing(int left, int right);
		int LOL_RConF_Routing(int left, int right);
		int LOR_RConF_Routing(int right);
};

extern AudioClass AudioC;

/**< Audio class instance extern which can used by application programs
 *   to access Audio DSP APIs
 */
#ifdef __cplusplus
}
#endif

#endif //_AUDIO_H_


