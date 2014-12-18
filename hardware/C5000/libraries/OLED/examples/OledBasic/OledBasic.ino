/*
  OLED Library

  Displays Welcome and DSP SHIELD on OLED screen
  Starts scrolling the display after 5 secs
  Scroll direction will be changed between left and right for every 10secs
*/

#include <OLED.h>

void setup() {

    disp.oledInit();          /* Initialize the OLED module */
    disp.clear();             /* Clears the entire display screen */
    disp.setline(0);          /* Set the current display line to Line0 */
    disp.setOrientation(1);   /* Set orientation of the LCD to horizontal */

    disp.print("Welcome");    /* Displays string "Welcome" on Line0 of the
                                 display screen */

    disp.setline(1);          /* Set the current display line to Line1 */
    disp.print("DSP SHIELD"); /* Displays string "DSP SHIELD" on Line1 of the
                                 display screen */
    delaySeconds(5);
}

void loop()
{
    disp.scrollDisplayRight(); /* Scroll entire display screen to right */
    delaySeconds(10);          /* Give delay of 10 msecs between right and left
                                  scrolling */
    disp.scrollDisplayLeft();  /* Scroll entire display screen to left */
    delaySeconds(10);          /* Give delay of 10 msecs between left and right
                                  scrolling */
}
