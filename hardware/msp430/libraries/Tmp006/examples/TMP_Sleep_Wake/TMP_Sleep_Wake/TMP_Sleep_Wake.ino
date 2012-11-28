#include <Tmp006.h>

void setup()
{ // Initalizes the TMP006 for operation and for I2C communication
  TMP006_Init(Eight);  // Takes 8 averaged samples for measurement
  TMP006_Sleep(); // TMP006 enters sleep mode
  TMP006_Wakeup(); // TMP006 wakes up without need to reconfigure
}


void loop()
{
  
}

