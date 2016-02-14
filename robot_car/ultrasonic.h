#ifndef fan_h
#define fan_h

class ultrasonic{
 public:
   ultrasonic();
   void SETUP();
   bool measure();
   
};


extern ultrasonic us_sensor;

#endif
