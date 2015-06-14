///
/// @mainpage	EMT-mailbox
///
/// @details	Mailbox library for Energia MT
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		Jun 14, 2015 12:39
/// @version	101
///
/// @copyright	(c) Rei Vilo, 2015
/// @copyright	CC = BY SA NC
///
/// @see		ReadMe.txt for references
///


///
/// @file		EMT_mailbox.ino
/// @brief		Main sketch
///
/// @details	RTOS mailbox as an object
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Rei Vilo
/// @author		http://embeddedcomputing.weebly.com
/// @date		Jun 14, 2015 12:39
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
myMessage_t message2;


// Add setup code
void MailboxSender2_setup()
{
    //    Serial.begin(115200);
    //
    //    myMailbox.begin();
    
    delay(100);
}

// Add loop code
void MailboxSender2_loop()
{
    message2.chrono = millis();
    strcpy(message2.buffer, "from 2");
    
    mySemaphore.waitFor();
    Serial.print("2 > Posted\t");
    Serial.print(millis(), DEC);
    Serial.print("\t: =(");
    Serial.print(message2.chrono, DEC);
    Serial.print(", ");
    Serial.print(message2.buffer);
    Serial.println(")");
    
    myMailbox.post(message2);
    
    mySemaphore.post();
    
    delay(800);
}
