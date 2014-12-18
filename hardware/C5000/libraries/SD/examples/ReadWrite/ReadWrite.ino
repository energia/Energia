/*
  File Read Write Demo

  This demo continuously reads data from serial monitor and writes
  it on to a file "transfer.txt" on the SD card. The demo stops reading data
  from serial monitor when the user types "$end$" string.

Note: SD Library requires SD card to be formatted in a specific
         format for proper operation. It is recommended to use
         SD formatter from SD card org or HP format tool for
         formatting the SD card
 */

#include "SD.h"

void setup()
{
    Bool          status;
    File          fileHandle;
    char          readString[513];
    char          compareString[6];
    unsigned long fileSize;
    int           index;
    int           bytesRead;

    strcpy (compareString, "$end$");

    status = SD.begin();
    if (TRUE == status)
     {
        fileHandle = SD.open("transfer.txt", FILE_WRITE);
        if (fileHandle)
        {
            Serial.println("\r\nEnter the Data to write to the file:");
            Serial.println("Enter $end$ to stop writing data to the file");

            index = 0;
            while (1)
            {
                /* Reading data continuously from serial till user enters
                   "$end$" */
                readString[index++] = Serial.read();
                readString[index]   = '\0';
                if (strstr(readString, compareString) != 0)
                {
                    readString[index - strlen(compareString)] = '\0';

                    /* Write the data entered by the User on Serial using
                       File.write(char *printString) */
                    fileHandle.write(readString);
                    break;
                }

                if (512 == index)
                {
                    readString[index] = '\0';
                    /* Write the data entered by the User on Serial using
                       File.write(char *printString) */
                       fileHandle.write(readString);

                    index = 0;
                }
            }

            /* Displaying File contents before exiting the demo */
            fileSize  = fileHandle.size();
            Serial.print("\r\nSize of the file after Writing the data that was entered is: ");
            Serial.println(fileSize);

            fileHandle.seek(0);
            Serial.println("\r\n   The contents of the file are:");
            for (index = 0; index < fileSize; )
            {
                /* Read the data entered written to the file using
                   File.read(char *readString, length) */
                if ((fileSize - index) > 512)
                {
                    bytesRead = fileHandle.read(readString, 512);
                }
                else
                {
                    bytesRead = fileHandle.read(readString, (fileSize - index));
                }

                if (0 == bytesRead)
                {
                    Serial.println("\r\nError in reading from the file");
                    break;
                }
                else
                {
                    readString[bytesRead] = '\0';
                    Serial.print(readString);
                }

                index += bytesRead;
            }

            fileHandle.close();
        }
        else
        {
            Serial.println("\n Error in opening File \"transfer.txt\"");
        }
    }
    else
    {
        Serial.println("\r\nError in Initializing SD Module");
    }

    Serial.println("\r\n\r\n  End of File Read Write Demo");
}

void loop()
{
}
