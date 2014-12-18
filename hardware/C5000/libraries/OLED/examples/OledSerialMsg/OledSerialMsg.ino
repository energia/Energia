/*
  OLED and Serial Library Example

  Reads Messages from the Serial port and Displays on the LCD

  Note: 1. Length of Messages is limited to 12 characters because of the LCD
           size
        2. If the User wants to send a message lesser than 12 characters, enter
           '$' at the end of the message.
*/

#include <OLED.h>

#define MSG_LENGTH (12)

void setup()
{
    disp.oledInit();        /* Initialize the OLED module */
    disp.setline(0);        /* Set the current display line to Line0 */
    disp.setOrientation(1);    /* Set orientation of the LCD to horizontal */
    disp.clear();            /* Clears the entire display screen */
}

void loop()
{
    char readChar;
    int  index;
    char dispString[MSG_LENGTH + 1];

    Serial.println("\r\nEnter the message which is to be displayed on the LCD");

    index = 0;
    do
    {
		/* Loop to read string from Serial monitor untill user enters '$'
		   character or length of string has reached 12 characters */
        readChar = Serial.read();
        dispString[index++] = readChar;
    } while ((readChar != '$') && (index < MSG_LENGTH));

    if (readChar == '$')
    {
        dispString[index - 1] = '\0';
    }

    Serial.print("The message entered is: ");
    Serial.println(dispString);

    Serial.println("Displaying message on LCD");
    disp.clear();           /* Clears the entire display screen */
    disp.print(dispString); /* Displays the string entered by User on Serial
                               monitor */
}
