/*
  File.print() Demo

  This demo writes a character, string, integer value, float value and an
  integer value in different formats (binary, decimal, octal and hexadecimal)
  to a file, using the respective variations of the File.println() API.

  Note: SD Library requires SD card to be formatted in a specific
           format for proper operation. It is recommended to use
           SD formatter from SD card org or HP format tool for
           formatting the SD card
*/

#include "SD.h"

void setup()
{
    Bool   status;
    char   charvalue;
    char   String[10];
    int    intvalue;
    long   longvalue;
    float  floatvalue;
    double doublevalue;
    File   fileHandle;

    strcpy(String, "Hello");

    status = SD.begin();
    if (TRUE == status)
    {
        fileHandle = SD.open("Print.txt", FILE_WRITE);
        if (fileHandle)
        {
            /* Writing a character to the file */
            charvalue = 'A';
            fileHandle.println("char Character: ");
            fileHandle.println(charvalue);

            /* Writing a String to the file */
            fileHandle.println("\r\n");
            fileHandle.println("char *String: ");
            fileHandle.println(String);

            /* Writing an ineteger to the file */
            intvalue = 1234;
            fileHandle.println("\r\n");
            fileHandle.println("Int value: ");
            fileHandle.println(intvalue);

            /* Writing a floating point value to the file */
            floatvalue = 45.90;
            fileHandle.println("\r\n");
            fileHandle.println("Float value: ");
            fileHandle.println(floatvalue);

            /* Writing a long integer value to the file */
            longvalue = 987654321;
            fileHandle.println("\r\n");
            fileHandle.println("Long value: ");
            fileHandle.println(longvalue);

            /* Writing a double precision float value to the file */
            doublevalue = 123456.976;
            fileHandle.println("\r\n");
            fileHandle.println("Double value: ");
            fileHandle.println(doublevalue);

            /* Writing a 32 bit integer in decimal format to the file */
            fileHandle.println("\r\n");
            fileHandle.println("Decimal value: ");
            fileHandle.println(longvalue, FILE_DEC);

            /* Writing a 32 bit integer in octal format to the file */
            fileHandle.println("\r\n");
            fileHandle.println("Octal value: ");
            fileHandle.println(longvalue, FILE_OCT);

            /* Writing a 32 bit integer in hexa decimal format to the file */
            fileHandle.println("\r\n");
            fileHandle.println("HexaDecimal value: ");
            fileHandle.println(longvalue, FILE_HEX);

            /* Writing a 32 bit integer in binary format to the file */
            fileHandle.println("\r\n");
            fileHandle.println("Binary value: ");
            fileHandle.println(longvalue, FILE_BIN);

            fileHandle.close();

            Serial.println("\r\n End of File.print() Demo");
        }
        else
        {
           Serial.println("Error in opening/creating file \"Print.txt\"");
        }
    }
    else
    {
        Serial.println("\r\nError in Initializing SD Module");
    }
}

void loop()
{
}
