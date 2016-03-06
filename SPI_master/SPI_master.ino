/*
SS    10
MOSI  11
MISO  12
SCK   13
*/


#include <SPI.h>

int cnt =0;

void setup (void)
{

  digitalWrite(SS, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup


void loop (void)
{

  char c;
  char array[] = "Hello World\n";

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10

  // send test string
  SPI.transfer(array,12);

  // disable Slave Select
  digitalWrite(SS, HIGH);

  delay (1000);  // 1 seconds delay 
}  // end of loop
