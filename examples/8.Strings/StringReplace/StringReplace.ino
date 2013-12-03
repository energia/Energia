/*
  String replace()
 
 Examples of how to replace characters or substrings of a string
 
 created 27 July 2010
 by Tom Igoe
 
 http://arduino.cc/en/Tutorial/StringReplace
 
 This example code is in the public domain. 
 */

void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.println("\n\nString  replace:");
}

void loop() {
  // you can use replace() on single characters:
  String normalString = "bookkeeper";
  Serial.println("normal: " + normalString);
  String leetString = normalString;
  leetString.replace('o', '0');
  leetString.replace('e', '3');
  Serial.println("l33tspeak: " + leetString);
  
  String stringOne = "<html><head><body>";
  Serial.println(stringOne);
  // replace() changes all instances of one substring with another:
  String stringTwo = stringOne;
  stringTwo.replace("<", "</");
  Serial.println(stringTwo);

  // do nothing while true:
  while(true);
}