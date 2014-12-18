/*
 * SPI and Arduino Communication demo
 * This code should be flashed to the Arduino Uno board
 *
 * Sends data (value 0-2) to the DSP Shield to blink that particular LED on the DSP Shield
 *
 * If value sent is 0, LED0 will be ON on DSP Shield
 * If value sent is 1, LED1 will be ON on DSP Shield
 * If value sent is 2, LED2 will be ON on DSP Shield
 */

#include <SPI.h>

/* Configures Arduino as Slave for SPI communication with DSP Shield */
void setup (void)
{
  /* Value should be sent on master in slave out (MISO) line */
  pinMode(MISO, OUTPUT);

  /* Configure SPI for Slave mode */
  SPCR |= _BV(SPE);
}

/* Main loop - Send the value to DSP Shield to blink the LED */
void loop (void)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        /* Send the value */
        SPDR = i;

        /* Wait for the DSP Shield to read the data that was sent */
        while (!(SPSR & _BV(SPIF)))
            ;
    }
}
