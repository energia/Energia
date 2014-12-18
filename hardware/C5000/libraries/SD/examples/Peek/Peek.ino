/*
  File.peek() demo

  Demo keep reading the same character from a file using File.peek() API

  Note: SD Library requires SD card to be formatted in a specific
           format for proper operation. It is recommended to use
           SD formatter from SD card org or HP format tool for
           formatting the SD card
*/

#include "SD.h"

void setup()
{
    Bool status;
    File fileHandle;

    status = SD.begin();
    if(TRUE == status)
    {
        fileHandle = SD.open("Peek.txt", FILE_WRITE);
        if (fileHandle)
        {
            fileHandle.print("Hello");
            fileHandle.seek(0);

            /* Read the character using of File.peek() API */
            Serial.print("Peek result is: ");
            Serial.println(fileHandle.peek());

            /* Any number of calls to File.peek() will return the same
               character */
            Serial.print("Peek result is: ");
            Serial.println(fileHandle.peek());
            fileHandle.close();
        }
        else
        {
            Serial.println("Error in opening file \"Peek.txt\"");
        }
    }
    else
    {
        Serial.println("\nError in Initializing SD Module");
    }

    Serial.println("\r\n  End of File.peek() Demo");
}

void loop()
{
}
