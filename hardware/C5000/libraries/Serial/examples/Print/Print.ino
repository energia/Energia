/*
 * Serial.println() Demo
 *
 * This demo prints a character, float value, integer and a string to the
 * Serial, using the respective variations of Serial.println() APIs
 */

void setup()
{
    char  charVal;
    float floatVal;
    long  longVal;
    char  writeString[50];

    Serial.println(" Serial.println() Demo!\r\n");

    Serial.println(" Printing a character on Serial using Serial.println(char) API");
    Serial.println(" Output should be 'A'");

    charVal = 'A';
    Serial.println(charVal);

    Serial.println("\r\n Printing a floating point value on Serial using Serial.println(float) API");
    Serial.println(" Output should be 523.21");

    floatVal = 523.21;
    Serial.println(floatVal);

    Serial.print("\r\n Printing a floating point value with 5 digits after ");
    Serial.println("decimal point on Serial using Serial.println(float, noOfDecDigits) API");
    Serial.println(" Output should be 10.34035");

    floatVal = 10.340354;
    Serial.println(floatVal, 5);

    Serial.println("\r\n Printing a 32 bit integer value on Serial using Serial.println(long) API");
    Serial.println(" Output should be 987654321");

    longVal = 987654321;
    Serial.println(longVal);

    Serial.println("\r\n Printing a String on Serial using Serial.println(String) API");
    Serial.println(" Output should be 'Hello'");

    strcpy(writeString, "Hello");
    Serial.println(writeString);

    Serial.println("\r\nEnd of Serial.println() Demo!");

    Serial.end();
}

void loop()
{
}
