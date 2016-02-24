//https://www.arduino.cc/en/Reference/StringLength
#include <SoftwareSerial.h>

String str="testing";
String emptyStr="";

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 
 Serial.print("length of string is ");
 Serial.println(str.length());
 
 Serial.print("length of an empty string is ");
 Serial.print(emptyStr.length());
 
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
