#include "Elevator.h"
#include <TimerOne.h>


int NbTick = 0;
bool State = false;
bool MoteurAvance = false;


Elevator::Elevator(){
  ENA = ENABLE;
  DIR = DIRECTION;
  PUL = IMPULL;

  SWT = SWITCHBUTE;
}

void Elevator::Setup(){

  Timer1.initialize(800);
  Timer1.attachInterrupt(UnTick);

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
