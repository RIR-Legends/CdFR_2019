#include "ForeArm.h"

ForeArm::ForeArm(){
  Dynamixel.begin(1000000,15);  // Inicialize the servo at 1Mbps and Pin Control 2
}

void ForeArm::MoveTo(double pDX1, double pDX2){
	Dynamixel.move(1, pDX1);
  Dynamixel.move(2, pDX2);
}

void ForeArm::InitDynamixel(){
  MoveTo(850,180);
}

void ForeArm::DeploiementSaisieFloor(){
  MoveTo(525,515); 
}

void ForeArm::DeploiementDrop(){
   MoveTo(820,515); 
}

void ForeArm::ParquetG(){
  MoveTo(500,180); 
  
}

void ForeArm::ParquetD(){
  MoveTo(500,860);
  
}

void ForeArm::BrasTransport(){
  MoveTo(200,515);
  
}

void ForeArm::DeploiementSaisieWall(){
   MoveTo(820,515); 
}

void ForeArm::DeploiementOutWall(){
   MoveTo(820,515); 
}
