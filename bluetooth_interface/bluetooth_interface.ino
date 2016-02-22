#include <SoftwareSerial.h>


// ARDUINO AT MODE (i.e. config mode)
//have different commands.   use at+help  for help

//VCC to 5V

SoftwareSerial mySerial(8, 9); // RX, TX

void setup() {

Serial.begin(9600);


Serial.println("Enter AT commands:");

mySerial.begin(9600);

}

void loop()

{

if (mySerial.available()){
  Serial.write(mySerial.read());
}

if (Serial.available()){
  mySerial.write(Serial.read());
}

}
