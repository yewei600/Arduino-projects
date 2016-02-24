#ifndef bluetooth_h
#define bluetooth_h

#include "SoftwareSerial.h"

class bluetooth{
   public:
     void SETUP();
     void set_bluetooth_baudrate();
     void gotMessage(String message);
     void parseReadBuffer();
     void parseWriteBuffer();
     
      
};




#endif
