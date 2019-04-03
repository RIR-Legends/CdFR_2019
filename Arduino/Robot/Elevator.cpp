#include "Elevator.h"


State = false;
int NbTick = 0;
bool moteurAvance = false;


Elevator::Elevator(){
  ENA = ENABLE;
  DIR = DIRECTION;
  PUL = IMPULL;

  SWT = SWITCHBUTE;
}

void Elevator::Setup(){

  Timer1.initialize(800);
  Timer1.attachInterrupt(UnTick());
  
}

void Elevator::Untick(){
  NbTick++;
  if(moteurAvance){
    if (State)
      digitalWrite(PUL, HIGH);
    else
      digitalWrite(PUL, LOW);
    State = !State;
  }
  
}
