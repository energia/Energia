/*
  Directory Browse Demo

  In this demo a file handle to the root directory is obtained. The
  contents of the root directory and its subsequent sub-directories are
  queried recursively and are displayed on the Serial.

   Note: SD Library requires SD card to be formatted in a specific
         format for proper operation. It is recommended to use
         SD formatter from SD card org or HP format tool for
         formatting the SD card
*/

#include "SD.h"

void display(void *Handle)
{
    File *parentHandle;
    File childHandle;
    char fileName[15];
    int  filecount = 0;
    int  directorycount = 0;

    parentHandle = (File *)Handle;

    while (1)
    {
        /* Open next file in current directory using File.openNextFile() API */
        childHandle = parentHandle->openNextFile();
        if (childHandle)
        {
            if (childHandle.isDirectory())
            {
                Serial.print("\n\rDirectory Name:");
                childHandle.getName(fileName);
                Serial.println(fileName);
                Serial.print("  Contents of the Directory:");
                Serial.print(fileName);
                Serial.println(" ");

                /* Since its a directory display the contents under the
                   respective directory */
                display(&childHandle);
                directorycount++;
            }
            else
            {
                Serial.print("File Name: ");
                childHandle.getName(fileName);
                Serial.print(fileName);
                Serial.print("\tSize: ");
                Serial.print(childHandle.size());
                Serial.println(" Bytes");
                filecount++;
            }

            childHandle.close();
        }
        else
        {
            Serial.print("  No more Files Under the directory:");
            parentHandle->getName(fileName);
            Serial.println(fileName);
            Serial.print("  File Count: ");
            Serial.print(filecount);
            Serial.print("\tDirectory Count: ");
            Serial.println(directorycount);
            Serial.println(" ");
            break;
        }
    }
}

void setup()
{
    Bool status;
    File fileHandle;

    status = SD.begin();
    if (TRUE == status)
    {
        /* Get a File handle to the Root directory */
        fileHandle = SD.open("/");
        if (fileHandle)
        {
            Serial.println("  Contents of the Root Directory are:");

            display(&fileHandle);
        }
    }
    else
    {
        Serial.println("Error in Initializing SD Module");
    }

    fileHandle.close();

    Serial.println("\r\n End of Directory Browse Demo");
}

void loop()
{
}
