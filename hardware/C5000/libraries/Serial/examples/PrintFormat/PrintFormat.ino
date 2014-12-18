/*
 * Serial Print Format Demo
 *
 * This demo prints an integer in various numeric format such as: binary,
 * decimal, octal and hexadecimal using Serial.println(value, format) API
 */

void setup()
{
    long longVal;

    Serial.println("\r\nSerial Print Format Demo!\r\n");

    Serial.println(" Printing an integer '125' in Binary format using print(long, format) API");
    longVal = 125;
    Serial.println(longVal, BIN);

    Serial.println("\r\n Printing an integer '0x7F' in Decimal format using print(long, format) API");
    longVal = 0x7F;
    Serial.println(longVal, DEC);

    Serial.println("\r\n Printing an integer '125' in Octal format using print(long, format) API");
    longVal = 125;
    Serial.println(longVal, OCT);

    Serial.println("\r\n Printing an integer '98765' in Hexdecimal format using print(long, format) API");
    longVal = 98765;
    Serial.println(longVal, HEX);

    Serial.println("\r\nEnd of Serial Print Format Demo!");

    Serial.end();
}

void loop()
{
}
