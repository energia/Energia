/*
 * Audio Loopback demo:
 * Audio library reads data from codec audio IN and sends the 
 * data to codec audio OUT which can be listened on headphone.
 *
 * For any data processing on audio data, use the pointers
 * AudioC.audioInLeft and AudioC.audioInRight. Audio data will
 * be available in these buffers when dmaIsr is triggered.
 * Buffer having the data read from codec will be indicated by
 * the index 'activeInBuf'
 */

#include "Audio.h"
#include "OLED.h"

interrupt void dmaIsr(void)
{
    // Copies audio samples received from audio In to the audio Out of the Codec
    AudioC.isrDma();
}

void setup()
{
    int status;
    
    //Initialize OLED module for status display
    disp.oledInit();
    disp.clear();
    disp.flip();
    disp.setline(1);
    
    // Initialize audio modules
    status = AudioC.Audio();
    /* Here, Audio library is configured for loopback mode.
       Calling AudioC.Audio() with out any argument sets the Loopback mode. It
       gives control to the Audio library to directly copy any audio samples
       coming through Audio IN back to the Audio Out of the Codec */
       
    if(status == 0)
    {  
        disp.print("Audio ON");

        //Enable interrupts and start audio data transfer
	AudioC.attachIntr(dmaIsr);    
    }
}

void loop()
{
}
