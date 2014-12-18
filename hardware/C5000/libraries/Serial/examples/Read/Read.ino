/*
 * Serial Read and Write Demo
 *
 * This demo read a single character from the Serial and displays it back on
 * the Serial
 */

void setup()
{
    char  charVal;

    Serial.println("\r\nSerial Read and Write Demo!\r\n");

    Serial.println("Enter a Character (1 byte):");

    charVal = Serial.read();
    Serial.print("You entered: ");
    Serial.println(charVal);

    Serial.println("\r\nEnd of Serial Read and Write Demo!");

    Serial.end();
}

void loop()
{
}
