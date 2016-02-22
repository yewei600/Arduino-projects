#include "Arduino.h"
#include "motor.h"

#define FORWARD 0
#define BACKWARD 1

const int cLeft1 = 2; // connected to pin 7 on the H-bridge
const int cLeft2 = 3; // connected to pin 2 on the H-bridge
const int cRight1 = 5; // connected to pin 10 on the H-bridge
const int cRight2 = 6; // connected to pin 15 on the H-bridge
const int enLeft = 10;   // connected to pin 1 on the H-bridge
const int enRight = 11;  // connected to pin 9 on the H-bridge

// create some variables to hold values from your inputs
int onOffSwitchState = 0;  // current state of the On/Off switch
int previousOnOffSwitchState = 0; // previous position of the on/off switch
int directionSwitchState = 0;  // current state of the direction switch
int previousDirectionSwitchState = 0;  // previous state of the direction switch

int motorend = 0; // Turns the motor on/off
int motorSpeed = 0; // speed of the motor
int motorDirection = 1; // current direction of the motor


motor::motor(int cPin1, int cPin2,int enPin){ 
   this->cPin1=cPin1;
   this->cPin2=cPin2;
   this->enPin=enPin;
}

void motor::SETUP(){
  Serial.begin(9600);
  // intialize the inputs and outputs
  pinMode(cPin1, OUTPUT);
  pinMode(cPin2, OUTPUT);
  pinMode(enPin, OUTPUT);

  // pull the en pin LOW to start
  digitalWrite(enPin, LOW);
}

void motor::spin(int dir,int spd=0){
 
  // change the direction the motor spins by talking
  // to the c pins on the H-Bridge
  if (dir == FORWARD) {
    analogWrite(cPin1, spd);
    digitalWrite(cPin2, LOW);
  }
  else if(dir ==BACKWARD) {
    digitalWrite(cPin1, LOW);
    analogWrite(cPin2, spd);
  }
  
    //analogWrite(enPin, HIGH);
   digitalWrite(enPin, HIGH); 
}


void motor::stopspin(){  
   //analogWrite(enPin,0);
   digitalWrite(enPin, LOW);
   //Serial.println("disabled");
}

motor mLeft = motor(cLeft1,cLeft2,enLeft);
motor mRight = motor(cRight1,cRight2,enRight);
