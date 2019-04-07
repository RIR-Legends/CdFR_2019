#include "Elevator.h"
#include <TimerOne.h>

int Elevator::NbTick = 0;
bool Elevator::State = false; 
bool Elevator::MoteurAvance = false; 

int Elevator::ENA = ENABLE;
int Elevator::DIR = DIRECTION;
int Elevator::PUL = IMPULL;
int Elevator::SWT = SWITCHBUTE;


Elevator::Elevator(){

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

int Elevator::RetournTimer(){
  return NbTick;
}
