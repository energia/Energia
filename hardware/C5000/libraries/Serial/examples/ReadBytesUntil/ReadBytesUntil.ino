/*
 * Serial.readBytesUntil() Demo
 *
 * This demo reads a string from serial, until the User types a string of
 * length 50 or types the terminating character ('@')
 */

void setup()
{
    char  readString[50];

    Serial.println("\r\nSerial.readBytesUntil() Demo!\r\n");

    Serial.println("\r\nEnter a string of maximum length 50 bytes. Press '@' to stop:");

    Serial.readBytesUntil('@', readString, 50);
    Serial.print("You entered: ");
    Serial.write(readString);

    Serial.println("\r\n\r\nEnd of Serial.readbytesUntil() Demo!");

    Serial.end();
}

void loop()
{
}
