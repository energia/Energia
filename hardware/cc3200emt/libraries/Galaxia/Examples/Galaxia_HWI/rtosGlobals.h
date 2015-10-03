///
/// @file		rtosGlobals.h
/// @brief		Global variables for Energia MT project
///
/// @details	<#details#>
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		20/06/2015 17:06
/// @version    101
///
/// @copyright	(c) Rei Vilo, 2015
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
/// @n
///

// PUSH1 managed by HWI, actually = Energia interrupt

#ifndef rtosGlobals_h
#define rtosGlobals_h


// Core library
#include "Energia.h"


// Include application, user and local libraries
#include "Semaphore.h"
#include "SWI.h"
#include "HWI.h"
#include "Event.h"


// Prototypes


// Define variables and constants
Semaphore mySemaphore;
SWI mySWI;
HWI myHWI;
uint32_t chrono;
Event myEvent;

// SWI function
void functionSWI()
{
//    Serial.println("\tSWI");
    chrono = millis();
    myEvent.send();
}

// HWI function
void functionHWI()
{
//    Serial.println("\tHWI");
    mySWI.post();
}

// Add optional rtosSetup function
void rtosSetup()
{
    Serial.begin(115200);

    mySemaphore.begin(1);
    mySWI.begin(functionSWI);
    myEvent.begin();
    
    mySemaphore.waitFor();
    Serial.println("rtosSetup");
    mySemaphore.post();
    
    // Solution 3: HWI
    pinMode(PUSH1, INPUT_PULLUP);
    myHWI.begin(PUSH1, functionHWI, FALLING);
}



#endif
