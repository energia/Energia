/*
 * Wire Demo
 *
 * Toggles LEDs connected to IO expander in sequence
 */

unsigned int cmd[2];
int ledValue = 0;
int ledState = 0;
void setup()
{    
    cmd[0] = 0x06;  // Command for IO expander configuration
    cmd[1] = 0x00;
    Wire.beginTransmission(0x21);  // 0x21 is the address of IO expander for which LED are connected
    Wire.write((unsigned int *)cmd,2);  //Configures IO expander port 0 pins as output
    Wire.endTransmission();
    delay(1000);  // Delay of 1sec
}

void loop()
{
 
    /* Below logic ensures 3 LEDs connected to IO expander are toggled in sequence
       LED0 (pin 0) - Will be ON when 'ledValue' is '0'
       LED1 (pin 1) - Will be ON when 'ledValue' is '1'
       LED2 (pin 2) - Will be ON when 'ledValue' is '2'
     */	
    ledState = ((ledValue / 2) << 6) | ((ledValue % 2) << 1) | (!ledValue);
    
    cmd[0] = 0x02;
    cmd[1] = ledState;
    Wire.beginTransmission(0x21);
    Wire.write((unsigned int *)cmd,2);  
    Wire.endTransmission();
   
    delay(1000);  // Delay of 1sec 
    
    ledValue++;
    ledValue = ledValue % 3;   // Value 'ledValue' never goes beyond 3
}