/*
 * Serial.parseInt() Demo
 *
 * This demo keeps reading data from serial, until the User enters a float value
 * followed by a non-numeric character or the serial.read() API times out
 * waiting for the User input
 */

void setup()
{
    long  longVal;

    Serial.println(" Serial.parseInt() Demo!");

    /* Ask for the input (integer value) from the User */
    Serial.println("\r\nEnter an integer value ending with a non-numeric character (eg: 125a):");
    longVal = Serial.parseInt();

    Serial.print("The value you entered is : ");
    Serial.println(longVal);

    Serial.println("\r\nEnd of Serial.parseInt() Demo!");
    Serial.end();
}

void loop()
{
}
