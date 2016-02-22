#ifndef motor_h
#define motor_h

class motor{ 
   public:
      int cPin1;
      int cPin2;
      int enPin;
      motor(int cPin1, int cPin2,int enPin);
      void SETUP();
      void spin(int dir,int spd);
      void stopspin();
  
};


extern motor mLeft;
extern motor mRight;
#endif
