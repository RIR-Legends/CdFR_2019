#include <Servo.h>

#define PINTURBINE 6

Servo Turbine;

void setup(){
  Turbine.attach(PINTURBINE);
  delay(1000);
}

void loop(){
  Turbine.write(170);
  delay(1000);
  Turbine.write(90);
  delay(1000);
}

