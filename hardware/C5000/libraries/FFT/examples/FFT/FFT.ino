/*
  Example sketch to demonstrate functionality of FFT DSP API library.
  FFT transform is computed for audio received from Audio input port.
  IFFT is computed for FFT output in order to get the audio signal
  into time domain. The resulting signal is sent to the Audio output.

*/

#include "FFT.h"
#include "Audio.h"

/** Circular Buffer Size */
#define CIRCULAR_BUFFER_SIZE (4u)
/** Size of the Block of data. Number of samples that will be processed by
    FFT-filtering */
#define SINGLE_BUFFER_SIZE   (I2S_DMA_BUF_LEN)
/** Size of the Overlap buffer, used by FFT-filtering algorithm */
#define OVERLAP_SIZE         (1024)

/** Buffer to hold the co-efficients used for FFT-filtering algorithm */
long coeff32[I2S_DMA_BUF_LEN];

/** Buffer containing the left channel audio samples, that will be sent as
    input to FFT-filtering algorithm */
#pragma DATA_ALIGN(32)
short fftBufL[CIRCULAR_BUFFER_SIZE][SINGLE_BUFFER_SIZE];

/** Buffer containing the right channel audio samples, that will be sent as
    input to FFT-filtering algorithm */
#pragma DATA_ALIGN(32)
short fftBufR[CIRCULAR_BUFFER_SIZE][SINGLE_BUFFER_SIZE];

/** Buffers to hold the Frequency domain overlap buffers for left and right
    channels, used by the FFT-filtering algorithm */
#pragma DATA_ALIGN(32)
short overlapL[OVERLAP_SIZE];
short overlapR[OVERLAP_SIZE];

/** Variable to hold the index of the circular buffer, where the next input
    audio samples must to be copied */
int fftCodecIndex = 0;
/** Variable to hold the index of the circular buffer, where the next input
    audio samples must sent for FFT-filtering algorithm */
int fftProcessIndex = 0;

/** Variable to indicate whether a particular buffer (input audio samples) is
    ready for FFT-filtering */
volatile int readyForFFT[CIRCULAR_BUFFER_SIZE] = {0};
/** Variable to indicate that a particular buffer (input audio samples) has
    been processed by FFT-filtering */
volatile int fftbufAvailable[CIRCULAR_BUFFER_SIZE] = {0};

/** Variable to switch between the data buffers of the Audio library */
int writeBufIndex;

/**
 * API to copy 16 bit integer elements from one buffer to an another buffer
 */
void copyBuf16(short *input, short *output, int dataLength)
{
    unsigned short index;

    for(index = 0; index < dataLength; index++)
    {
        output[index] = input[index];
    }
}

/**
 * Interrupt Service Routine, which will be called when the audio samples have
 * been completely transferred from/to the Audio Codec
 */
interrupt void dmaIsr(void)
{
    unsigned short ifrValue;

    /* Clear the DMA interrupt */
    ifrValue = DMA.getInterruptStatus();
    if ((ifrValue >> DMA_CHAN_ReadR) & 0x01)
    {
        copyBuf16((short *)AudioC.audioInLeft[AudioC.activeInBuf], fftBufL[fftProcessIndex], I2S_DMA_BUF_LEN);
        copyBuf16((short *)AudioC.audioInRight[AudioC.activeInBuf], fftBufR[fftProcessIndex], I2S_DMA_BUF_LEN);
        readyForFFT[fftProcessIndex] = 1;
    }
    else if ((ifrValue >> DMA_CHAN_WriteR) & 0x01)
    {
        if (fftbufAvailable[fftCodecIndex])
        {
            writeBufIndex = (AudioC.activeOutBuf == FALSE)? TRUE: FALSE;
            copyBuf16(fftBufL[fftCodecIndex], (short *)AudioC.audioOutLeft[writeBufIndex], I2S_DMA_BUF_LEN);
            copyBuf16(fftBufR[fftCodecIndex], (short *)AudioC.audioOutRight[writeBufIndex], I2S_DMA_BUF_LEN);
            fftbufAvailable[fftCodecIndex] = 0;

            fftCodecIndex++;

            if (CIRCULAR_BUFFER_SIZE == fftCodecIndex)
            {
                fftCodecIndex = 0;
            }
        }
    }

    AudioC.isrDma();

    if (readyForFFT[fftProcessIndex])
    {
	    /* Process FFT, filtering and IFFT of the input samples */

        /* Left Channel */
        FFTransform.FFT_filter(fftBufL[fftProcessIndex], fftBufL[fftProcessIndex], 
                               overlapL, I2S_DMA_BUF_LEN);

        /* Right Channel */
        FFTransform.FFT_filter(fftBufR[fftProcessIndex], fftBufR[fftProcessIndex], 
                               overlapR, I2S_DMA_BUF_LEN);

        fftbufAvailable[fftProcessIndex] = 1;
        readyForFFT[fftProcessIndex] = 0;
        fftProcessIndex++;

        if (CIRCULAR_BUFFER_SIZE == fftProcessIndex)
        {
            fftProcessIndex = 0;
        }
    }

}

/**
 * Initializes Audio and FFT library, along with the buffers used in this demo
 */
void setup() {
    int status;
    int index;

    for (index = 0; index < CIRCULAR_BUFFER_SIZE; index++)
    {
        readyForFFT[index]     = 0;
        fftbufAvailable[index] = 0;
    }

    for (index = 0; index < OVERLAP_SIZE; index++)
    {
    	overlapL[index] = 0;
    	overlapR[index] = 0;
    }

    FFTransform.FFT_init();

    Serial.print("\n FFT TEST!\n");

    status = AudioC.Audio(TRUE);
    if (status != 0)
    {
        Serial.print("\n Audio Init failed!\n");
    }
    else
    {
        Serial.print("\n Audio Init Done!\n");
    }

    AudioC.attachIntr((INTERRUPT_IsrPtr)dmaIsr);
}

void loop() {
}
