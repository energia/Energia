/*
  File and Folder creation Demo

  This demo creates the directory path "DIR1/DIR2/DIR3/DIR4/DIR5" and creates
  4 files under each directory in the path created before.

     In the first part of this demo, a directories chain with path as
  'DIR1/DIR2/DIR3/DIR4/DIR5' is created.
     In the second part, 4 files are created under each directory in the
  directory path 'DIR1/DIR2/DIR3/DIR4/DIR5' and some data is written in these
  files.

   Note: SD Library requires SD card to be formatted in a specific
         format for proper operation. It is recommended to use
         SD formatter from SD card org or HP format tool for
         formatting the SD card
*/

#include "SD.h"

void setup()
{
    Bool status;
    Bool dirCreation;

    Serial.println("  Directories and Files creation demo:\r\n");

    status = SD.begin();
    if (TRUE == status)
    {
        /* Create the directory path using mkdir(char *dirPath)*/
        dirCreation = SD.mkdir("DIR1/DIR2/DIR3/DIR4/DIR5");
        if (TRUE == dirCreation)
        {
            Serial.println("Directories \"DIR1/DIR2/DIR3/DIR4/DIR5\" created sucessfully");
        }
        else
        {
            Serial.println("Directories \"DIR1/DIR2/DIR3/DIR4/DIR5\" creation unsucessful");
            return;
        }

        createFiles();

        Serial.println("\r\n  End of Files and Folders creation Demo");
    }
    else
    {
        Serial.println("Error in initializing the SD module");
    }
}

void createFiles()
{
    int  indexI;
    int  indexJ;
    int  noOfBytesWritten;
    char writeBuffer[50];
    char fileName[50];
    char filePath[50];
    File childHandle;
    int  counter;

    filePath[0] = '\0';
    counter = 1;

    /* Create 4 files under each directory in the path
       'DIR1/DIR2/DIR3/DIR4/DIR5' */
    for (indexI = 0; indexI < 5; indexI++)
    {
        sprintf(filePath, "%sDIR%d/", filePath, (indexI + 1));
        for (indexJ = 0; indexJ < 4; indexJ++)
        {
            sprintf (fileName, "%sdir%d.txt", filePath, counter);
            sprintf (writeBuffer, "dir%d.txt: File under directory DIR%d", counter, (indexI + 1));

            childHandle = SD.open(fileName, FILE_WRITE);
            if (childHandle)
            {
                noOfBytesWritten = childHandle.print(writeBuffer);
                childHandle.close();

                if (0 == noOfBytesWritten)
                {
                    return;
                }
                counter++;
            }
        }
    }
}

void loop()
{
}
