
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


//////////////////////////////////////////////////////////////////////////////////////////////////////
// Set to match your hardware
int RX_PIN = 7;
int TX_PIN = 8;

// Serial interface for the BlueSMiRF
SoftwareSerial bluetooth(RX_PIN, TX_PIN);

// Send and receive buffers
String bluetooth_rx_buffer = "";
String bluetooth_tx_buffer = "";

bool goForward = false;
bool goBackward = false;


// Delimiter used to separate messages
char DELIMITER = '\n';
//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
 
  us_sensor.SETUP();
  mLeft.SETUP();
  mRight.SETUP();
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  bluetooth.begin(9600);
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("Initialized.");
  delay(1000);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void carDirection(int dir){
  if(dir==FORWARD){
    mLeft.spin(FORWARD);
    mRight.spin(FORWARD);     
  }
  else if(dir==BACKWARD){
    mLeft.spin(BACKWARD);
    mRight.spin(BACKWARD); 
  }
}

void carStop(){
     mLeft.stopspin();
     mRight.stopspin();   
}

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
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Called when a complete message is received.
 */
void gotMessage(String message) {
  
  //Serial.println("[RECV] " + message);
 // bluetooth.println("The number version "+toInt(message));
  // Do something!
  
  //robot control logic
  if(message=="left"){
    //carStop();
    carTurn(ForwardLEFT);
    Serial.println("received left!!!!");
  }
  else if(message=="right"){
    //carStop();
    carTurn(ForwardRIGHT);  
    Serial.println("received right!!!");  
  }
  else if(message=="forward"){
       carDirection(FORWARD);
  }
  else if(message=="backward"){
      carDirection(BACKWARD);
  }
  else if(message="stop"){
     carStop();
  }
  
}

/**
 * Finds complete messages from the rx buffer.
 */
void parseReadBuffer() {
  
  // Find the first delimiter in the buffer
  int inx = bluetooth_rx_buffer.indexOf(DELIMITER);
  
  // If there is none, exit
  if (inx == -1) return;
  
  // Get the complete message, minus the delimiter
  String s = bluetooth_rx_buffer.substring(0, inx);
  
  // Remove the message from the buffer
  bluetooth_rx_buffer = bluetooth_rx_buffer.substring(inx + 1);
  
  // Process the message
  gotMessage(s);
}

void parseWriteBuffer() {
  
  // Find the first delimiter in the buffer
  int inx = bluetooth_tx_buffer.indexOf(DELIMITER);
  
  // If there is none, exit
  if (inx == -1) return;
  
  // Get the complete message, including the delimiter
  String message = bluetooth_tx_buffer.substring(0, inx + 1);
  
  // Remove the message from the buffer
  bluetooth_tx_buffer = bluetooth_tx_buffer.substring(inx + 1);
  
  // Send off the message
  bluetooth.print(message);
  Serial.print("[SENT] " + message);
  
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


/*
-if receive bt command, act on that command
- list of different commands
*/
void loop() {
  
  // Forward anything received via USB to bluetooth
  if(Serial.available()) {
    
    while(Serial.available()) {
      bluetooth_tx_buffer += (char)Serial.read();
    }
    
    // Look for complete messages
    parseWriteBuffer();
  }
  
  // Add bytes received over bluetooth to the buffer
  if(bluetooth.available()) {
    
    while(bluetooth.available()) {
      bluetooth_rx_buffer += (char)bluetooth.read();
    }
    // Look for complete messages
    parseReadBuffer();
  }
  
/*  if(goForward){
   carDirection(FORWARD); 
  }
  else if(goBackward){
   carDirection(BACKWARD); 
  }
  */
}




