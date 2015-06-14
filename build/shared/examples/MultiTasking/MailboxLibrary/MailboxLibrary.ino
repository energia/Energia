///
/// @mainpage	EMT-mailbox-template
///
/// @details	Mailbox library for Energia MT
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		Jun 14, 2015 17:18
/// @version	101
///
/// @copyright	(c) Rei Vilo, 2015
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
///


///
/// @file		EMT_mailbox_template.ino
/// @brief		Main sketch
///
/// @details	RTOS mailbox as an object
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		Jun 14, 2015 17:18
/// @version	101
///
/// @copyright	(c) Rei Vilo, 2015
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
/// @n
///


// Core library for code-sense - IDE-based
#   include "Energia.h"

// Include application, user and local libraries
#include "Mailbox.h"
#include "rtosGlobals.h"

// Prototypes


// Define variables and constants
myMessage_t message1;


// Add setup code
void setup()
{
    Serial.begin(115200);
    Serial.println("begin");
    
    mySemaphore.begin(1);
    myMailbox.begin();
}

// Add loop code
void loop()
{
    message1.chrono = millis();
    strcpy(message1.buffer, "from 1");
    
    mySemaphore.waitFor();
    Serial.print("1 > Posted\t");
    Serial.print(millis(), DEC);
    Serial.print("\t: =(");
    Serial.print(message1.chrono, DEC);
    Serial.print(", ");
    Serial.print(message1.buffer);
    Serial.println(")");
    
    myMailbox.post(message1);
    
    mySemaphore.post();
    
    delay(1000);
}
