/*
  File Size Demo

  Demo to find the size of a file using File.size() API. This demo finds the
  file size of the first file under root.

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
    char fileName[15];

    status = SD.begin();

    if (TRUE == status)
    {
        fileHandle = SD.open("/");
        if (fileHandle)
        {
            while (fileHandle)
            {
                if (!fileHandle.isDirectory())
                {
                    Serial.print("File Name: ");
                    fileHandle.getName(fileName);
                    Serial.print(fileName);

                     /* Get the size of the file using File.size() */
                    Serial.print("\tSize: ");
                    Serial.print(fileHandle.size());
                    Serial.println(" Bytes");
                    break;
                }

                /* Open next file in current directory using openNextFile() */
                fileHandle = fileHandle.openNextFile();
            }
            fileHandle.close();
        }
        else
        {
            Serial.println("\r\n  Error in opening  Root Directory");
        }
    }
    else
    {
        Serial.println("\r\n  Error in Initializing SD Module");
    }

    Serial.println("\r\n  End of File Size Demo");
}

void loop()
{
}
