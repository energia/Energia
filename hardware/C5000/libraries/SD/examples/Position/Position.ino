/*
  File Cursor Position demo

  Demo to print the current position of the file file cursor using File.seek()
  and File.position() APIs

  Note: SD Library requires SD card to be formatted in a specific
           format for proper operation. It is recommended to use
           SD formatter from SD card org or HP format tool for
           formatting the SD card
*/


#include "SD.h"

void setup()
{
    Bool          result;
    long          position;
    unsigned long fileSize;
    File          fileHandle;

    result = SD.begin();
    if (TRUE == result)
    {
        fileHandle = SD.open("Position.txt", FILE_WRITE);
        if (fileHandle)
        {
            fileHandle.print(12345);
            fileHandle.close();

            fileHandle = SD.open("Position.txt");

            /* Seek to the beginning of the file and display the current
               position */
            Serial.println("  Seeking to the beginning of the file");
            result = fileHandle.seek(0);

            position = fileHandle.position();
            Serial.print("Current Position is: ");
            Serial.println(position);


            /* Seek to the end of the file and display the current position */
            Serial.println("\r\n  Seeking to the end of the file");
            fileSize = fileHandle.size();
            result = fileHandle.seek(fileSize - 1);

            position = fileHandle.position();
            Serial.print("Current Position is: ");
            Serial.println(position);

            Serial.print("\r\nFile Size is: ");
            Serial.println(fileSize);

            fileHandle.close();
        }
        else
        {
            Serial.println("Error in opening file \"Position.txt\"");
        }
    }
    else
    {
        Serial.println("\r\nError in Initializing SD Module");
    }

    Serial.println("\r\n End of File Cursor Position Demo");
}

void loop()
{
}
