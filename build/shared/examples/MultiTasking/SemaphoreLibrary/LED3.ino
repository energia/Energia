///
/// @file		LED1.ino
/// @brief		Task for Energia MT
/// @details	<#details#>
/// @n
/// @n @b		Project EMT-event
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
///
/// @date		05/06/2015 21:20
/// @version	<#version#>
///
/// @copyright	(c) Rei Vilo, 2015
/// @copyright	<#license#>
///
/// @see		ReadMe.txt for references
///



// Core library for code-sense - IDE-based
#if defined(EMBEDXCODE)
#if defined(ENERGIA) && defined(__MSP432P401R__) // LaunchPad MSP432 on Energia MT only
#include "Energia.h"
#else
#error LaunchPad MSP432 on Energia MT only
#endif
#endif // end IDE

// Include application, user and local libraries
#include "rtosGlobals.h"


// Prototypes


// Define variables and constants
int value3 = 0;


// Setup
void LED3_setup()
{
    Serial.begin(115200);
    pinMode(BLUE_LED, OUTPUT);
}

// Loop
void LED3_loop()
{
    // ONE only
    uint32_t events = myEvent3.waitFor(Event_Id_03);
    // AND
    // uint32_t events = myEvent2.waitFor(Event_Id_02 + Event_Id_03, Event_Id_NONE);
    // OR
    //uint32_t events = myEvent2.waitFor(Event_Id_NONE, Event_Id_02 + Event_Id_03);
    
    value3 = 1 - value3;
    digitalWrite(GREEN_LED, value3);

#if defined(optionSemaphore)
    mySemaphore.waitFor();
#endif

    Serial.print(millis(), DEC);
    Serial.println("\t: myEvent3.waitFor   3 = B");
    
#if defined(optionSemaphore)
    mySemaphore.post();
#endif
}

