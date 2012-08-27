
#include <Touch.h>

//
// Test the TouchPin class of Touch Library
// 
// Created by Anton Smeenk
// 
// This example code is in the public domain.
// 
 
 
TouchPin pin5 = TouchPin(5);
TouchPin pin6 = TouchPin(6);
TouchPin pin7 = TouchPin(7);
TouchPin pin8 = TouchPin(8);
TouchPin pin9 = TouchPin(9);
TouchPin pin10 = TouchPin(10);

TouchSlider3 slider = TouchSlider3();  // default postion is first 3 (egisterd) touchpins

void setup() {
  pinMode(RED_LED, OUTPUT);     
  pinMode(GREEN_LED, OUTPUT);
  Touch.registerPin(&pin5);  
  Touch.registerPin(&pin6);  
  Touch.registerPin(&pin7);  
  Touch.registerPin(&pin8);  
  Touch.registerPin(&pin9);  
  Touch.registerPin(&pin10);
  
  wait4push();
  Serial.begin(9600);
  Serial.print("\n\n\n*** Test TouchPin class \n"); 
  Serial.print("Press Reset before downloading new program!\n"); 

}

void loop() {
  Touch.scheduler();  // must be called about every 10 ms
  long now = millis(); 

  if ((now % 100) == 0 ){
    Serial.print("\ndelta 8:"); 
    Serial.print(pin8.getDelta()); 
    Touch.scheduler();
    Serial.print("\t 8:"); 
    Serial.print(pin8.isPressed()); 
    Touch.scheduler();
    Serial.print("\t bits:"); 
    Serial.print(Touch.getBits(),HEX); 
    Touch.scheduler();
    Serial.print("\t slider:"); 
    Serial.print(slider.getPos()); 
    
  }
  if ((now %100) == 99){
    digitalWrite(RED_LED, HIGH);   // set the LED on
  }  
  if ((now %100)== 61){
    digitalWrite(RED_LED, LOW);   // set the LED off
  }
}

void wait4push(){
    pinMode(PUSH2, INPUT_PULLUP);
    while (digitalRead(PUSH2)==HIGH) {
      digitalWrite(RED_LED, HIGH);   // set the LED on
      delay(50);  
      digitalWrite(GREEN_LED, HIGH);   // set the LED on
      delay(50);  
      digitalWrite(RED_LED, LOW);   // set the LED on
      delay(50);  
      digitalWrite(GREEN_LED, LOW);   // set the LED on
      delay(50);  
    }
    //debounce
    delay(10);  
    while (digitalRead(PUSH2)==LOW) {
      delay(100);  
    }
    delay(10);  

}



