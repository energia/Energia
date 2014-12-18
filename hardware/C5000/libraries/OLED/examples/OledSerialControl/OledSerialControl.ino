/*
  OLED Library

  Program which gives a menu list to the User to try out the different OLED
  APIs
*/

#include <OLED.h>

void setup() {
    int  stopPgm;
    int  userOption;
    char displayStr[13];

    Serial.println("\n OLED Library APIs TEST!");

    disp.oledInit();          /* Initialize the OLED module */
    disp.clear();             /* Clears the entire display screen */
    disp.setline(0);          /* Set the current display line to Line0 */
    disp.setOrientation(1);   /* Set orientation of the LCD to horizontal */

    stopPgm = 0;

    do
    {
        Serial.println(" ");
        Serial.println("----------------------------------");
        Serial.println("            OLED MENU             ");
        Serial.println("----------------------------------");
        Serial.println("00: Display a string in Line 0");
        Serial.println("01: Display a string in Line 1");
        Serial.println("02: Scroll Line 0 to Left");
        Serial.println("03: Scroll Line 0 to Right");
        Serial.println("04: Scroll Line 1 to Left");
        Serial.println("05: Scroll Line 1 to Right");
        Serial.println("06: Scroll both Line 0 & 1 to Left");
        Serial.println("07: Scroll both Line 0 & 1 to Right");
        Serial.println("08: To Stop Scrolling");
        Serial.println("09: To Flip");
        Serial.println("10: To Clear Line 0");
        Serial.println("11: To Clear Line 1");
        Serial.println("12: To Clear Screen");
        Serial.println("13: To exit");
        Serial.println("----------------------------------");
        Serial.println("Enter your choice");

        /* Read User Option, which will be in the format 00,01,02,...,13 */
        userOption = Serial.read() - '0';
        userOption *= 10;
        userOption += Serial.read() - '0';
        Serial.print("Option Entered: ");
        Serial.print(userOption);
        Serial.println("\r\n");

        switch (userOption)
        {
            case 0:
            case 1:
                /* Turns off automatic scrolling of the LCD */
                disp.noAutoscroll();

                /* Clear the requested Line of the display screen */
                disp.clear(userOption);

                /* Read string from Serial monitor untill User enters '$'
		           character or length of string has reached 12 characters */
                Serial.println("\r\nEnter the String (Max 12 characters or enter '$' at the end)");
                Serial.readBytesUntil('$', displayStr, 12);

                /* Set the current display line as requested by the User */
                disp.setline(userOption);

                /* Displays the string entered by User on Serial monitor */
                disp.print(displayStr);
                break;

            case 2:
                disp.scrollDisplayLeft(0);
                /* Scroll Line0 of display screen to left */
                break;

            case 3:
                disp.scrollDisplayRight(0);
                /* Scroll Line0 of display screen to right */
                break;

            case 4:
                disp.scrollDisplayLeft(1);
                /* Scroll Line1 of display screen to left */
                break;

            case 5:
                disp.scrollDisplayRight(1);
                /* Scroll Line1 of display screen to right */
                break;

            case 6:
                disp.scrollDisplayLeft();
                /* Scroll entire display screen to left */
                break;

            case 7:
                disp.scrollDisplayRight();
                /* Scroll entire display screen to right */
                break;

            case 8:
                disp.noAutoscroll();
                /* Turns off automatic scrolling of the LCD */
                break;

            case 9:
                disp.flip();
                /* Flips the screen vertically */
                break;

            case 10:
                disp.clear(0);
                /* Clears Line0 of the display screen */
                break;

            case 11:
                disp.clear(1);
                /* Clears Line1 of the display screen */
                break;

            case 12:
                disp.clear();
                /* Clears the entire display screen */
                break;

            case 13:
                Serial.println("Exiting the Program");
                stopPgm = 1;
                break;

            default:
                Serial.println("Invalid option!!");
                break;
        }
    } while (0 == stopPgm);
}

void loop() {
}