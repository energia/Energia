/*
  SD.exists() Demo

  This demo checks whether the file "DEMO.TXT" exists under the root directory
  on the Card, using SD.exists() API

   Note: SD Library requires SD card to be formatted in a specific
         format for proper operation. It is recommended to use
         SD formatter from SD card org or HP format tool for
         formatting the SD card
*/

#include "SD.h"

void setup()
{
    Bool status;

    status = SD.begin();
    if (TRUE == status)
    {
        /* Check whether the file "DEMO.TXT" exists or not under root
           directory */
        if (SD.exists("DEMO.TXT"))
        {
            Serial.println("File \"DEMO.TXT\" exists under Root directory");
        }
        else
        {
            Serial.println("File \"DEMO.TXT\" doesn't exist under Root directory");
        }
    }

    else
    {
        Serial.println("\r\nError in Initializing SD Module");
    }

    Serial.println("\r\n End of SD.exists() Demo");
}
void loop()
{
}
