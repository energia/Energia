/*
  OLED Library

  Program to demonstrate the Use of all print APIs of OLED library used for
  Displaying
*/

#include <OLED.h>

void setup() {
    long value;

    Serial.println("\r\nLCD Print API Demo!");

    disp.oledInit();        /* Initialize the OLED module */
    disp.setOrientation(1); /* Set orientation of the LCD to horizontal */

    disp.clear();           /* Clears the entire display screen */
    Serial.println("\r\nDisplaying a String on the LCD");
    disp.setline(0);        /* Set the current display line to Line0 */
    disp.print("Dsp Shield");
    delaySeconds(5);

    disp.clear();           /* Clears the entire display screen */
    Serial.println("\r\nDisplaying a Character 'M' on the LCD");
    disp.setline(0);        /* Set the current display line to Line0 */
    disp.print('M');
    delaySeconds(5);

    disp.clear();           /* Clears the entire display screen */
    Serial.println("\r\nDisplaying an integer value '1234567' on the LCD");
    disp.setline(0);        /* Set the current display line to Line0 */
    value = 1234567;
    disp.print(value);
    delaySeconds(5);

    disp.clear();           /* Clears the entire display screen */
    Serial.println("\r\nDisplaying Hexadecimal equivalent of '1234567' on the LCD");
    disp.setline(0);        /* Set the current display line to Line0 */
    value = 1234567;
    disp.print(value, HEXADECIMAL);
    delaySeconds(5);

    disp.clear();           /* Clears the entire display screen */
    Serial.println("\r\nDisplaying Octal equivalent of '1234567' on the LCD");
    disp.setline(0);        /* Set the current display line to Line0 */
    value = 1234567;
    disp.print(value, OCTAL);
    delaySeconds(5);

    disp.clear();
    Serial.println("\r\nDisplaying Binary equivalent of '123' on the LCD");
    disp.setline(0);        /* Set the current display line to Line0 */
    value = 123;
    disp.print(value, BINARY);

    Serial.println("\r\nLCD Print API Demo Completed!");
}

void loop()
{
}
