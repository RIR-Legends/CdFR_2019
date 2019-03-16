#include "DX.h"

Dynamixels::Dynamixels(){
  Dynamixel.begin(1000000,10);
}

void Dynamixels::Parking(){
  Dynamixel.setMaxTorque(3,1023);
  Dynamixel.moveSpeed(3,350,600);
  Dynamixel.setMaxTorque(2,1023);
  Dynamixel.moveSpeed(2,900,200);
  delay(400);
  Dynamixel.setPunch(1,1023); //limite du courant (0-1023)
  Dynamixel.setMaxTorque(1,1023); 
  Dynamixel.moveSpeed(1,1000,500); 
  
  delay(500);
}

void Dynamixels::PositionPrise(){
  //sortie du bras
  Dynamixel.setPunch(1,80); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,300,100);
  delay(600);
  Dynamixel.moveSpeed(2,320,100);
  delay(200);
  Dynamixel.moveSpeed(3,333,100);
  delay(500);
}

void Dynamixels::DescenteMain(){
  Dynamixel.setPunch(1,10); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,380,100);
  delay(200);
  Dynamixel.moveSpeed(2,360,100);
  delay(200);
  Dynamixel.moveSpeed(3,333,100);
  delay(500);
}
void Dynamixels::Transport(){
  Dynamixel.setPunch(1,80); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,300,100);
  delay(600);
  Dynamixel.moveSpeed(2,350,100);
  delay(200);
  Dynamixel.moveSpeed(3,333,100);
  delay(500);
  
}

void Dynamixels::PositionDepose(){
   Dynamixel.setPunch(1,80); //limite du courant (0-1023)
  Dynamixel.moveSpeed(1,300,100);
  delay(1000);
  Dynamixel.moveSpeed(2,800,100);
  delay(1000);
  Dynamixel.moveSpeed(1,500,100);
  delay(500);
}

void Dynamixels::Rotation45(){
  Dynamixel.moveSpeed(3,487,600);
  delay(300);
}

