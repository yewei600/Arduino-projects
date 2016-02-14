const int cLeft1 = 2; // connected to pin 7 on the H-bridge
const int cLeft2 = 3; // connected to pin 2 on the H-bridge
const int cRight1 = 4; // connected to pin 10 on the H-bridge
const int cRight2 = 5; // connected to pin 15 on the H-bridge
const int enLeft = 9;   // connected to pin 1 on the H-bridge
const int enRight = 8;
int d;
String incoming;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(cLeft1, OUTPUT);
  pinMode(cLeft2, OUTPUT);
  pinMode(cRight1, OUTPUT);
  pinMode(cRight2, OUTPUT);
  
  pinMode(enLeft, OUTPUT);
  pinMode(enRight, OUTPUT);
  
  Serial.println("select which motor to spin and what direction\n 0:left motor 1:right motor 0:one way 1:other way  ");

}

void loop() {
    
    while(!Serial.available()){       
    }
    
    incoming=Serial.readStringUntil('CR');
    
    Serial.print("received: ");
    Serial.println("%s",incoming);
    
    
   

}
