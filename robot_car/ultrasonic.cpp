#include "Arduino.h"
#include "ultrasonic.h"

const int buzzer = 11;
const int triggerPin = 12; //triggering on pin 12
const int echoPin = 13; //echo on pin 13
int duration, distance;

//ultrasonic

ultrasonic::ultrasonic(){
    
}

void ultrasonic::SETUP(){
    Serial.begin(9600); //we'll start serial comunication, so we can see the distance on the serial monitor Serial.println("Tech Ponder's UltraSonic Sensor Tutorial");   
    pinMode(triggerPin, OUTPUT); //defining pins   
    pinMode(echoPin, INPUT);  
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer,LOW); 
}

bool ultrasonic::measure(){
   int duration, distance; //Adding duration and distance
    
    digitalWrite(triggerPin, HIGH); //triggering the wave(like blinking an LED)
    
    delay(10);
    
    digitalWrite(triggerPin, LOW);
    
    duration = pulseIn(echoPin, HIGH); //a special function for listening and waiting for the wave
    
    distance = (duration/2) / 29.1; //transforming the number to cm(if you want inches, you have to change the 29.1 with a suitable number
    
    delay(1000);
    
    Serial.print(distance); //printing the numbers
    
    Serial.print("cm"); //and the unit
    
    Serial.println(" "); //just printing to a new line
    
    if (distance < 5){
        
        digitalWrite(buzzer,HIGH);
        
        Serial.println("Buzzer On");
        
        return true;
    }else{
      digitalWrite(buzzer,LOW); 
      Serial.println("Buzzer off");
      return false;
      
    }   
}

ultrasonic us_sensor = ultrasonic();








