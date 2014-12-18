/*
 * Time instance 1 demo:
 * Verifies whether the GPT1 is decrementing the counter or not.
 * GPT is configured with a count value of 0xFFFF and pre-scaler divider
 * value of 256. GPT1 is started and counter value is read. After few
 * cycles of delay GPT1 counter value is read again. Both the counter values
 * are compared to verify whether the second count value is less
 * than the first counter value or not and the test passes if it is true.
 *
 *  This sketch dmonstrates usage of function Timer.configTimer
 */

#include <Timers.h>

void setup() {
    GPT_Config              hwConfig;
    unsigned long           timeCnt1;
    unsigned long           timeCnt2;
    volatile unsigned short delay;

    Serial.print("\nGPT - Example for configTimer() \n");

    // Open the GPT module for GPT 0 instance 
    Timer.selectTimer(GPT0);

    // Configure GPT module 
    hwConfig.autoLoad    = TRUE;
    hwConfig.ctrlTim     = TRUE;
    hwConfig.preScaleDiv = GPT_PRE_SC_DIV_7;
    hwConfig.prdLow      = 0xFFFF;
    hwConfig.prdHigh     = 0x0000;

    Timer.configTimer(hwConfig);

    // Start the Timer 
    Timer.start();

    // Read the Timer Count 
    timeCnt1 = Timer.read();

    // Give Some Delay 
    delayMilliseconds(100);

    // Read the Timer Count Again 
    timeCnt2 = Timer.read();

    // Compare the timer count to verify whether the timer is counting or not 
    if(timeCnt2 >= timeCnt1)
    {
        Serial.print("GPT Time Count Compare Failed\n");
    }
    else
    {
        Serial.print("GPT Time Count Compare Successful\n");
    }

    // Stop The Timer 
    Timer.stop();

    // Close the GPT module 
    Timer.close();

    Serial.print("\nEnd of Example!\n");
}

void loop() {
}
