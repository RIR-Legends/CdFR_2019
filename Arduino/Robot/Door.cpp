#include "Door.h"

Door::Door(){
  Dynamixel.begin(1000000,15);  // Inicialize the servo at 1Mbps and Pin Control 2
}

void Door::MoveToR(double position){
	Dynamixel.move(4,position);
}

void Door::MoveToL(double position){
	Dynamixel.move(3,position);
}

void Door::InitDoor(){
	MoveToR(400);
	MoveToL(950);
}

void Door::OpenR(){
	MoveToR(750);
}

void Door::OpenL(){
	MoveToL(600);
}

void Door::CloseR(){
	MoveToR(400);
}

void Door::CloseL(){
	MoveToL(900);
}

void Door::OpenAll(){
  OpenR();
  OpenL();
}

void Door::CloseAll(){
  CloseR();
  CloseL();
}
