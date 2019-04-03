#include "Elevator.h"
#include <TimerOne.h>





Elevator::Elevator(){
  ENA = ENABLE;
  DIR = DIRECTION;
  PUL = IMPULL;

  SWT = SWITCHBUTE;

  NbTick = 0;
  State = false;
  MoteurAvance = false;
}

void Elevator::Setup(){

  Timer1.initialize(800);
  Timer1.attachInterrupt(Elevator::UnTick);

  digitalWrite(ENA, HIGH);
  digitalWrite(DIR, LOW);
  digitalWrite(PUL, LOW);
  
}

void Elevator::UnTick(){
  NbTick++;
  if(MoteurAvance){
    if (State)
      digitalWrite(PUL, HIGH);
    else
      digitalWrite(PUL, LOW);
    State = !State;
  }
  
}
