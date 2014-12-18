/*
 * Serial.readBytes() Demo
 *
 * This demo reads a string of length 5 from the Serial and displays it back on
 * the Serial
 */
void setup()
{
    char  readString[50];

    Serial.println("\r\nSerial.readBytes() Demo!\r\n");

    Serial.println("\r\nEnter a string of length 5 bytes:");

    Serial.readBytes(readString, 5);
    Serial.print("The string you entered is: ");
    Serial.write(readString, 5);

    Serial.println("\r\n\r\nEnd of Serial.readbytes() Demo!!");

    Serial.end();
}

void loop()
{
}
