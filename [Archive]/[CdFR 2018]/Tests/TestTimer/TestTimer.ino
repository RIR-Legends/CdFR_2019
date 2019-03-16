#include "TimerOne.h"

int TIMER = 0;

 void callback()
{
  TIMER++;
}

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(1000000);
  Timer1.start();     //set the clock to zero
  //Timer1.attachInterrupt(callback);
  Timer1.attachInterrupt(callback);
}


 
void loop()
{
  Serial.println(TIMER);
  
}
