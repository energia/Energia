#include <Tmp006.h>

void setup()
{ // Initalizes the TMP006 for operation and for I2C communication
  TMP006_Init(Eight);  // Takes 8 averaged samples for measurement
}

void loop()
{
  //Prints the temperature 
  Print_Temp(Enable); // Enable: Prints temperature (c) and raw register values
                      // Disable: Prints just the temperature (c)
  
}

