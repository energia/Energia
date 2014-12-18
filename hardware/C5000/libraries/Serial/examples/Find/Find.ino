/*
 * Serial.find() Demo
 *
 * This demo first reads a string of length 5 and then keeps reading data from
 * serial, until the User types the first string or the serial.read() API times
 * out waiting for the User input
 */

void setup()
{
    Bool  result;
    char  targetString[50];

    Serial.println(" Serial.find() Demo!");

    /* Ask for the target string from the User */
    Serial.println("\r\nEnter the string to find (5 characters):");
    Serial.readBytes(targetString, 5);

    targetString[5] = '\0';

    Serial.println("Enter string in which the previous string should be looked for");
    result = Serial.find(targetString);
    if (result == TRUE)
    {
        Serial.println("\r\nString found");
    }
    else
    {
        Serial.println("\r\nTimeout: String not found");
    }

    Serial.println("\r\nEnd of Serial.find() Demo!!");

    Serial.end();
}

void loop()
{
}
