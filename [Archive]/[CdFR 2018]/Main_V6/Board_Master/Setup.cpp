#include "Setup.h"

void Setup::SetTurbine(Servo turb){
  turb.attach(PINTURBINE); 
}

void Setup::SetPompes(){
  pinMode(POMPE1,OUTPUT);
  pinMode(POMPE2,OUTPUT);
  pinMode(POMPE3,OUTPUT);
  pinMode(POMPE4,OUTPUT);
  pinMode(POMPE5,OUTPUT);
}
