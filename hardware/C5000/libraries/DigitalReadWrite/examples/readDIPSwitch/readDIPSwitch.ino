/*
 * DIP switch read demo
 *
 *  This program reads the DIP switch states on SW1 and displays on
 *  serial monitor
 *
 *  Note: This demo is specific for C5535 DSP shield.
 *  May not work/compile for other platforms
 */

unsigned int pinVal;

void setup()
{
    // Read the state of SW1
    pinVal = digitalRead(SW1);
    if (pinVal)
    {
        Serial.print("DIP Switch SW1 is ON\n");
    }
    else
    {
        Serial.print("DIP Switch SW1 is OFF\n");
    }

    // Read the state of SW2	
    pinVal = digitalRead(SW2);
    if (pinVal)
    {
        Serial.print("DIP Switch SW2 is ON\n");
    }
    else
    {
        Serial.print("DIP Switch SW2 is OFF\n");
    }

    // Read the state of SW3
    pinVal = digitalRead(SW3);
    if (pinVal)
    {
        Serial.print("DIP Switch SW3 is ON\n");
    }
    else
    {
        Serial.print("DIP Switch SW3 is OFF\n");
    }

    // Read the state of SW4 
    pinVal = digitalRead(SW4);
    if (pinVal)
    {
        Serial.print("DIP Switch SW4 is ON\n");
    }
    else
    {
        Serial.print("DIP Switch SW4 is OFF\n");
    }
}

void loop()
{
}
