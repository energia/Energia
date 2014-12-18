/*
 * Serial.parseFloat() Demo
 *
 * This demo keeps reading data from serial, until the User enters a float value
 * followed by a non-numeric character or the serial.read() API times out
 * waiting for the User input
 */

void setup()
{
    float floatVal;

    Serial.println(" Serial.parseFloat() Demo!");

    /* Ask for the input (float value) from the User */
    Serial.println("\r\nEnter a float value ending with a non-numeric character (eg: 12.93a):");
    floatVal = Serial.parseFloat();

    Serial.print("The value you entered is : ");
    Serial.println(floatVal);

    Serial.println("\r\nEnd of Serial.parseFloat() Demo!");

    Serial.end();
}

void loop()
{
}
