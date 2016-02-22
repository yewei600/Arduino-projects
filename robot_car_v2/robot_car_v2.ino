
#include "ultrasonic.h"
#include "motor.h"
#include <SoftwareSerial.h>

#define FORWARD 0
#define BACKWARD 1
#define ForwardLEFT 0
#define ForwardRIGHT 1
#define BackLEFT 2
#define BackRIGHT 3

#define LWheel 0
#define RWheel 1
#define BothWheel 2

SoftwareSerial BT(8, 9); // RX, TX

int cnt=0;
char cmd;

void setup() {
  Serial.begin(9600);
  us_sensor.SETUP();
  mLeft.SETUP();
  mRight.SETUP();
  
  bluetoothSETUP(); 
 
 //testing
 pinMode(3, OUTPUT);
  pinMode(5, OUTPUT); 
}

void bluetoothSETUP(){
   //bluetooth stuff
  Serial.println("Enter AT commands:");
  BT.begin(9600);  
}

void carDirection(int dir,int spd){
  if(dir==FORWARD){
    mLeft.spin(FORWARD,spd);
    mRight.spin(FORWARD,spd);     
  }
  else if(dir==BACKWARD){
    mLeft.spin(BACKWARD,spd);
    mRight.spin(BACKWARD,spd); 
  }
}

void carStop(){
     mLeft.stopspin();
     mRight.stopspin();   
}

/*
void carTurn(int dir){
   if(dir==ForwardLEFT){
    mLeft.stopspin();
    mRight.spin(FORWARD);
   } 
   else if(dir==ForwardRIGHT){
     mLeft.spin(FORWARD);
     mRight.stopspin();
   }
   else if(dir==BackLEFT){
     mLeft.spin(BACKWARD);
     mRight.stopspin();
   }
   else if(dir==BackRIGHT){
     mLeft.stopspin();
     mRight.spin(BACKWARD);
   }
   delay(500);
   carStop();
}*/

void loop() {
 
 
////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////// 
/*
  use this version to debug the MULTI SPEED FUNCTION !!!
*/
////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////// 
  
  carDirection(FORWARD,50);
  
//  cnt+=50;
  //cnt=cnt%255;
  Serial.println(cnt);
  delay(1000);
  
  
  
}




