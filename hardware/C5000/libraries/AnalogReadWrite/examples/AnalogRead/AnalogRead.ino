/*
 * Analog Read
 * Reads analog pin data from A0 pin contnuosly and displays it on the serial
 * console.
 */

void setup()
{
    Serial.println("\r\nThe Read data is:");
}

void loop()
{
    // Read anlog pin and send the value to serial monitor	
    Serial.println(analogRead(A0), HEX);
}

