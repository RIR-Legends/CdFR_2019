#include "Elevator.h"

int Elevator::NbTick = 0;

int Elevator::Position = 0;

int Elevator::ENA = ENABLE;
int Elevator::DIR = DIRECTION;
int Elevator::PUL = IMPULL;
int Elevator::SWT = SWITCHBUTE;

Elevator::Elevator(){
  
}

void Elevator::Setup(){

  digitalWrite(ENA, LOW);
  digitalWrite(DIR, LOW);
  digitalWrite(PUL, LOW);
  
}


void Elevator::Move(int nbTick, bool sens){
  digitalWrite(ENA, HIGH);
  digitalWrite(DIR,sens); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < nbTick; x++) {
    digitalWrite(PUL,HIGH); 
    delayMicroseconds(600); 
    digitalWrite(PUL,LOW); 
    delayMicroseconds(600); 
  } 
}

void Elevator::InitialPosition(){
  bool switchState = digitalRead(SWT);
  digitalWrite(ENA, HIGH);
  digitalWrite(DIR,LOW); // Enables the motor to move in a particular direction
  while(switchState == true){
    digitalWrite(PUL,HIGH); 
    delayMicroseconds(600); 
    digitalWrite(PUL,LOW); 
    delayMicroseconds(600); 
    switchState = digitalRead(SWT);
   }
   Position = 0;
}

int Elevator::getPosition(){
  return Position;
}

void Elevator::MoveTo(int destination){
  if (Position > destination){
    Move(Position-destination, LOW);
    Position = destination;
  }
  if (Position < destination){
    Move(destination-Position, HIGH);
    Position = destination;
  }
}

void Elevator::GoToFloor(int floorNb){
  switch(floorNb){
    case 0:
       MoveTo(1600);
       delay(500);
       MoveTo(1652);
    break;
    case 1:
       MoveTo(1270);
    break;
    case 2:
       MoveTo(1010);
    break;
    case 3:
       MoveTo(748);
    break;
    case 4:
       MoveTo(490);
    break;
    case 5:
       MoveTo(236);
    break;
      case 6:
       MoveTo(50);
    break;
      case 7:
       MoveTo(0);
    break;
  }
}

void Elevator::GoOut(int floorNb){
  GoToFloor(floorNb+1);
}

void Elevator::GetPaletFloor(){
  GoToFloor(0);
}

void Elevator::GetOutPalet(){
  MoveTo(1200);
}

void Elevator::Transport(){
  MoveTo(150);
}

void Elevator::GetPaletWall(){
  MoveTo(1500);
}

void Elevator::GetOutPaletWall(){
  MoveTo(800);
}
