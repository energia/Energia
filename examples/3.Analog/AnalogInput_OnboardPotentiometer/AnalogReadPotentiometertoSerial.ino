/*
  AnalogReadSerial
  Enables on-board potentiometer on P8.0 and reads an
  analog input from on-board potentiometer on A5(P6.5); 
  prints the result to the serial monitor.
  
  Hardware Required:
  * MSP-EXP430F5529 (Not the F5529 LP)
    http://www.ti.com/tool/msp-exp430f5529

  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(POT_ENABLE, OUTPUT);    // set P8.0 to output
  digitalWrite(POT_ENABLE, HIGH); // set P8.0 high to enable Potentiometer
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin A5:
  int sensorValue = analogRead(A5);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(100); // delay in between reads for stability
}
